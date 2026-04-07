#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_DRIVERS = 50;
const int MAX_USERS = 20;
const int MAX_TEAMS = 11;
const int MAX_CONTRACTS = 100;
const int CURRENT_YEAR = 2026;

struct Driver {
    string name;
    string nationality;
    int birthYear;
    string status;
};

struct User {
    string username;
    string password;
};

struct Team {
    string name;
};

struct Contract {
    int driverIndex;
    int teamIndex;
    int startYear;
    int endYear;
};

void initDriverF1(Driver *d, int *count) {
    string nama[] = {
        "Charles Leclerc","Lewis Hamilton","George Russell","Kimi Antonelli",
        "Lando Norris","Oscar Piastri","Fernando Alonso","Lance Stroll",
        "Esteban Ocon","Oliver Bearman","Max Verstappen","Sergio Perez",
        "Arvid Lindblad","Pierre Gasly","Valtteri Bottas","Isack Hadjar",
        "Nico Hulkenberg","Gabriel Bortoletto","Liam Lawson","Alexander Albon",
        "Carlos Sainz","Franco Colapinto"
    };

    string negara[] = {
        "Monaco","UK","UK","Italy",
        "UK","Australia","Spain","Canada",
        "France","UK","Netherlands","Mexico",
        "Sweden","France","Finland","France",
        "Germany","Brazil","New Zealand","Thailand",
        "Spain","Argentina"
    };

    int tahun[] = {
        1997,1985,1998,2006,
        1999,2001,1981,1998,
        1996,2005,1997,1990,
        2004,1996,1989,2003,
        1987,2004,2002,1996,
        1994,2003
    };

    for (int i = 0; i < 22; i++) {
        d[i] = {nama[i], negara[i], tahun[i], "Aktif"};
    }

    *count = 22;
}

void initTeams(Team *t, int *count) {
    string nama[] = {
        "Scuderia Ferrari HP","Mercedes AMG Petronas","McLaren Mastercard",
        "Oracle Red Bull Racing","Visa Cash App Racing Bulls","BWT Alpine",
        "Aston Martin Aramco","Audi Revolut","Atlassian Williams",
        "Cadillac","HAAS TGR"
    };

    for (int i = 0; i < 11; i++) {
        t[i].name = nama[i];
    }

    *count = 11;
}

void initDefaultUser(User *u, int *count) {
    u[0] = {"Attol","2509106103"};
    *count = 1;
}

void initKontrakDefault(Contract *c, int *cc) {
    int teamMap[22] = {
        0,0,1,1,2,2,6,6,10,10,3,9,4,5,9,3,7,7,4,8,8,5
    };

    for (int i = 0; i < 22; i++) {
        c[i] = {i, teamMap[i], 2025, 2027};
    }

    *cc = 22;
}

void registerUser(User *u, int *count) {
    if (*count >= MAX_USERS) {
        cout << "Jumlah user sudah penuh!\n";
        return;
    }

    cout << "Username: ";
    getline(cin, u[*count].username);
    cout << "Password: ";
    getline(cin, u[*count].password);
    (*count)++;

    cout << "Registrasi berhasil!\n";
}

bool loginUser(User *u, int count) {
    string us, pw;
    cout << "Username: ";
    getline(cin, us);
    cout << "Password: ";
    getline(cin, pw);

    for (int i = 0; i < count; i++) {
        if (u[i].username == us && u[i].password == pw) {
            return true;
        }
    }

    cout << "Login gagal!\n";
    return false;
}

string getTeamName(int idx, Contract *c, int cc, Team *t, Driver *d) {
    if (d[idx].status == "Free Agent") return "Free Agent";
    if (d[idx].status == "Tidak Aktif") return "-";

    for (int j = 0; j < cc; j++) {
        if (c[j].driverIndex == idx && c[j].endYear >= CURRENT_YEAR) {
            return t[c[j].teamIndex].name;
        }
    }

    return "Free Agent";
}

void listPembalap(Driver *d, int dc, Contract *c, int cc, Team *t) {
    cout << "\n";
    cout << left << setw(4) << "No"
         << setw(25) << "Nama"
         << setw(15) << "Negara"
         << setw(8) << "Umur"
         << setw(15) << "Status"
         << setw(28) << "Tim" << endl;

    cout << string(95, '=') << endl;

    for (int i = 0; i < dc; i++) {
        cout << setw(4) << i + 1
             << setw(25) << d[i].name
             << setw(15) << d[i].nationality
             << setw(8) << CURRENT_YEAR - d[i].birthYear
             << setw(15) << d[i].status
             << setw(28) << getTeamName(i, c, cc, t, d)
             << endl;
    }
}

void listKontrak(Contract *c, int cc, Driver *d, Team *t) {
    cout << "\n=== LIST KONTRAK ===\n";
    for (int i = 0; i < cc; i++) {
        cout << i + 1 << ". "
             << d[c[i].driverIndex].name << " - "
             << t[c[i].teamIndex].name
             << " (" << c[i].startYear << "-" << c[i].endYear << ")\n";
    }
}

void hapusKontrakDriver(Contract *c, int *cc, int driverIdx) {
    for (int i = 0; i < *cc; i++) {
        if (c[i].driverIndex == driverIdx) {
            for (int j = i; j < *cc - 1; j++) {
                c[j] = c[j + 1];
            }
            (*cc)--;
            i--;
        }
    }
}

void tambahPembalap(Driver *d, int *dc) {
    if (*dc >= MAX_DRIVERS) {
        cout << "Data driver penuh!\n";
        return;
    }

    cout << "Nama: ";
    getline(cin, d[*dc].name);

    cout << "Negara: ";
    getline(cin, d[*dc].nationality);

    cout << "Tahun lahir: ";
    cin >> d[*dc].birthYear;
    cin.ignore();

    cout << "Status (Aktif/Tidak Aktif/Free Agent): ";
    getline(cin, d[*dc].status);

    (*dc)++;
    cout << "Driver berhasil ditambahkan!\n";
}

void editPembalap(Driver *d, int dc, Contract *c, int cc, Team *t) {
    listPembalap(d, dc, c, cc, t);

    int i;
    cout << "\nPilih driver yang ingin diedit: ";
    cin >> i;
    cin.ignore();

    if (i < 1 || i > dc) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    i--;

    cout << "Nama baru: ";
    getline(cin, d[i].name);

    cout << "Negara baru: ";
    getline(cin, d[i].nationality);

    cout << "Tahun lahir baru: ";
    cin >> d[i].birthYear;
    cin.ignore();

    cout << "Status baru (Aktif/Tidak Aktif/Free Agent): ";
    getline(cin, d[i].status);

    if (d[i].status == "Free Agent" || d[i].status == "Tidak Aktif") {
        hapusKontrakDriver(c, &cc, i);
    }

    cout << "Data driver berhasil diupdate!\n";
}

void hapusPembalap(Driver *d, int *dc, Contract *c, int *cc, Team *t) {
    listPembalap(d, *dc, c, *cc, t);

    int idx;
    cout << "\nPilih driver yang ingin dihapus: ";
    cin >> idx;
    cin.ignore();

    if (idx < 1 || idx > *dc) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    idx--;

    hapusKontrakDriver(c, cc, idx);

    for (int i = idx; i < *dc - 1; i++) {
        d[i] = d[i + 1];
    }
    (*dc)--;

    for (int i = 0; i < *cc; i++) {
        if (c[i].driverIndex > idx) {
            c[i].driverIndex--;
        }
    }

    cout << "Driver berhasil dihapus!\n";
}

void transferDriverKeTim(Contract *c, int *cc, int driverIdx, int teamIdx, int startYear, int endYear) {
    for (int i = 0; i < *cc; i++) {
        if (c[i].driverIndex == driverIdx && c[i].endYear >= CURRENT_YEAR) {
            for (int j = i; j < *cc - 1; j++) {
                c[j] = c[j + 1];
            }
            (*cc)--;
            i--;
        }
    }

    c[*cc] = {driverIdx, teamIdx, startYear, endYear};
    (*cc)++;
}

void transferDriver(Driver *d, int dc, Team *t, int tc, Contract *c, int *cc) {
    int dr, pilihanStatus;

    cout << "\n=== LIST DRIVER ===\n";
    listPembalap(d, dc, c, *cc, t);

    cout << "\nPilih driver: ";
    cin >> dr;

    if (dr < 1 || dr > dc) {
        cin.ignore();
        cout << "Pilihan driver tidak valid!\n";
        return;
    }

    dr--;

    cout << "\n=== PILIH STATUS DRIVER ===\n";
    cout << "1. Aktif (transfer ke tim)\n";
    cout << "2. Free Agent\n";
    cout << "3. Tidak Aktif\n";
    cout << "Pilih: ";
    cin >> pilihanStatus;

    if (pilihanStatus == 1) {
        int tm, startYear, endYear;

        cout << "\n=== LIST TIM ===\n";
        for (int i = 0; i < tc; i++) {
            cout << i + 1 << ". " << t[i].name << endl;
        }

        cout << "\nPilih tim baru: ";
        cin >> tm;

        if (tm < 1 || tm > tc) {
            cin.ignore();
            cout << "Pilihan tim tidak valid!\n";
            return;
        }

        cout << "Masukkan tahun mulai kontrak: ";
        cin >> startYear;

        cout << "Masukkan tahun selesai kontrak: ";
        cin >> endYear;
        cin.ignore();

        if (endYear < startYear) {
            cout << "Tahun selesai tidak boleh lebih kecil dari tahun mulai!\n";
            return;
        }

        transferDriverKeTim(c, cc, dr, tm - 1, startYear, endYear);
        d[dr].status = "Aktif";

        cout << "Transfer berhasil!\n";
        cout << "Kontrak baru: " << startYear << "-" << endYear << endl;
    }
    else if (pilihanStatus == 2) {
        cin.ignore();
        hapusKontrakDriver(c, cc, dr);
        d[dr].status = "Free Agent";
        cout << "Driver sekarang berstatus Free Agent!\n";
    }
    else if (pilihanStatus == 3) {
        cin.ignore();
        hapusKontrakDriver(c, cc, dr);
        d[dr].status = "Tidak Aktif";
        cout << "Driver sekarang berstatus Tidak Aktif!\n";
    }
    else {
        cin.ignore();
        cout << "Pilihan status tidak valid!\n";
    }
}

void menu(Driver *d, int *dc, Team *t, int tc, Contract *c, int *cc) {
    int p;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. List Driver\n";
        cout << "2. Tambah Driver\n";
        cout << "3. Edit Driver\n";
        cout << "4. Hapus Driver\n";
        cout << "5. List Kontrak\n";
        cout << "6. Transfer Driver\n";
        cout << "7. Logout\n";
        cout << "Pilih: ";

        cin >> p;
        cin.ignore();

        switch (p) {
            case 1:
                listPembalap(d, *dc, c, *cc, t);
                break;
            case 2:
                tambahPembalap(d, dc);
                break;
            case 3:
                editPembalap(d, *dc, c, *cc, t);
                break;
            case 4:
                hapusPembalap(d, dc, c, cc, t);
                break;
            case 5:
                listKontrak(c, *cc, d, t);
                break;
            case 6:
                transferDriver(d, *dc, t, tc, c, cc);
                break;
            case 7:
                cout << "Logout berhasil.\n";
                break;
            default:
                cout << "Menu tidak valid!\n";
        }
    } while (p != 7);
}

int main() {
    Driver d[MAX_DRIVERS];
    User u[MAX_USERS];
    Team t[MAX_TEAMS];
    Contract c[MAX_CONTRACTS];

    int dc = 0, uc = 0, tc = 0, cc = 0;

    initDefaultUser(u, &uc);
    initDriverF1(d, &dc);
    initTeams(t, &tc);
    initKontrakDefault(c, &cc);

    int p;
    do {
        cout << "\n1. Register\n2. Login\n3. Keluar\nPilih: ";
        cin >> p;
        cin.ignore();

        if (p == 1) {
            registerUser(u, &uc);
        }
        else if (p == 2) {
            if (loginUser(u, uc)) {
                menu(d, &dc, t, tc, c, &cc);
            }
        }
        else if (p == 3) {
            cout << "Program selesai.\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (p != 3);

    return 0;
}