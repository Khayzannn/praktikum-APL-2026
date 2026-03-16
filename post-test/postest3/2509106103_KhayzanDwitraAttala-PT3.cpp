#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int MAX_USERS = 20;
const int MAX_DRIVERS = 50;
const int MAX_CONTRACTS = 100;
const int NUM_TEAMS = 11;
const int CURRENT_YEAR = 2026;

struct User {
    string username;
    string password;
};

struct Driver {
    string name;
    string nationality;
    int birthYear;
    string status;
};

struct Team {
    string name;
    bool active;
};

struct Contract {
    int driverIndex;
    int teamIndex;
    int season;
    string status;
    int startYear;
    int endYear;
};

void tampilJudul(string judul);
void tampilJudul(string judul, int garis);
void tampilGaris(int jumlah);

void menuAwal(User users[], int &userCount,
              Driver drivers[], int &driverCount,
              Team teams[], int teamCount,
              Contract contracts[], int &contractCount);

void menuAdmin(Driver drivers[], int &driverCount,
               Team teams[], int teamCount,
               Contract contracts[], int &contractCount);

void registerUser(User users[], int &userCount);
bool login(User users[], int userCount, int percobaan);

void listPembalap(Driver drivers[], int driverCount);
void listPembalapRekursif(Driver drivers[], int driverCount, int index);
void listTim(Team teams[], int teamCount);
void listKontrak(Contract contracts[], int contractCount,
                 Driver drivers[], Team teams[]);

void tambahPembalap(Driver drivers[], int &driverCount);
void editPembalap(Driver drivers[], int driverCount);
void hapusPembalap(Driver drivers[], int &driverCount,
                   Contract contracts[], int &contractCount);

void tambahKontrak(Contract contracts[], int &contractCount,
                   Driver drivers[], int driverCount,
                   Team teams[], int teamCount);

void editKontrak(Contract contracts[], int contractCount,
                 Driver drivers[], int driverCount,
                 Team teams[], int teamCount);

void hapusKontrak(Contract contracts[], int &contractCount,
                  Driver drivers[], Team teams[]);

void tampilGaris(int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << "=";
    }
    cout << "\n";
}

void tampilJudul(string judul) {
    cout << "\n";
    tampilGaris(50);
    cout << judul << "\n";
    tampilGaris(50);
}

void tampilJudul(string judul, int garis) {
    cout << "\n";
    tampilGaris(garis);
    cout << judul << "\n";
    tampilGaris(garis);
}

void registerUser(User users[], int &userCount) {
    tampilJudul("REGISTER ADMIN");
    cout << "Username baru : ";
    getline(cin, users[userCount].username);
    cout << "Password baru : ";
    getline(cin, users[userCount].password);

    userCount++;
    cout << "Register berhasil.\n";
}

bool login(User users[], int userCount, int percobaan) {
    string username, password;

    cout << "Username : ";
    getline(cin, username);
    cout << "Password : ";
    getline(cin, password);

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login berhasil.\n";
            return true;
        }
    }

    percobaan++;

    if (percobaan == 3) {
        cout << "Anda salah memasukkan username atau password sebanyak 3 kali. Program berhenti.\n";
        exit(0);
    }

    cout << "Username atau password salah. Coba lagi.\n";
    return login(users, userCount, percobaan);
}

void listPembalapRekursif(Driver drivers[], int driverCount, int index) {
    if (index == driverCount) {
        return;
    }

    int umur = CURRENT_YEAR - drivers[index].birthYear;

    cout << "| "
         << setw(3)  << left << index + 1
         << "| " << setw(25) << left << drivers[index].name
         << "| " << setw(15) << left << drivers[index].nationality
         << "| " << setw(11) << left << drivers[index].birthYear
         << "| " << setw(5)  << left << umur
         << "| " << setw(12) << left << drivers[index].status
         << "|\n";

    listPembalapRekursif(drivers, driverCount, index + 1);
}

void listPembalap(Driver drivers[], int driverCount) {
    if (driverCount == 0) {
        cout << "Belum ada pembalap yang di tambahkan\n";
        return;
    }

    tampilJudul("DATA PEMBALAP LENGKAP", 86);
    cout << "+----+--------------------------+----------------+-------------+-------+-------------+\n";
    cout << "| No | Nama                     | Negara         | Tahun Lahir | Umur  | Status      |\n";
    cout << "+----+--------------------------+----------------+-------------+-------+-------------+\n";

    listPembalapRekursif(drivers, driverCount, 0);

    cout << "+----+--------------------------+----------------+-------------+-------+-------------+\n";
}

void listTim(Team teams[], int teamCount) {
    tampilJudul("DAFTAR TIM", 56);
    cout << "+----+--------------------------------+------------+\n";
    cout << "| No | Nama Tim                       | Status     |\n";
    cout << "+----+--------------------------------+------------+\n";

    for (int i = 0; i < teamCount; i++) {
        cout << "| "
             << setw(3)  << left << i + 1
             << "| " << setw(31) << left << teams[i].name
             << "| " << setw(10) << left << (teams[i].active ? "Active" : "Inactive")
             << "|\n";
    }

    cout << "+----+--------------------------------+------------+\n";
}

void listKontrak(Contract contracts[], int contractCount,
                 Driver drivers[], Team teams[]) {
    if (contractCount == 0) {
        cout << "Belum ada kontrak yang di tambahkan\n";
        return;
    }

    tampilJudul("DAFTAR KONTRAK", 104);
    cout << "+----+--------------------------+--------------------------+--------+------------+------------+------------+\n";
    cout << "| No | Driver                   | Team                     | Season | Status     | Start Year | End Year   |\n";
    cout << "+----+--------------------------+--------------------------+--------+------------+------------+------------+\n";

    for (int i = 0; i < contractCount; i++) {
        cout << "| "
             << setw(3)  << left << i + 1
             << "| " << setw(25) << left << drivers[contracts[i].driverIndex].name
             << "| " << setw(25) << left << teams[contracts[i].teamIndex].name
             << "| " << setw(7)  << left << contracts[i].season
             << "| " << setw(10) << left << contracts[i].status
             << "| " << setw(10) << left << contracts[i].startYear
             << "| " << setw(10) << left << contracts[i].endYear
             << "|\n";
    }

    cout << "+----+--------------------------+--------------------------+--------+------------+------------+------------+\n";
}

void tambahPembalap(Driver drivers[], int &driverCount) {
    int pilihanStatus;

    tampilJudul("TAMBAH PEMBALAP");
    cout << "Nama        : ";
    getline(cin, drivers[driverCount].name);
    cout << "Negara      : ";
    getline(cin, drivers[driverCount].nationality);
    cout << "Tahun lahir : ";
    cin >> drivers[driverCount].birthYear;
    cin.ignore();

    cout << "Pilih status:\n";
    cout << "1. Aktif\n";
    cout << "2. Tidak Aktif\n";
    cout << "Pilihan     : ";
    cin >> pilihanStatus;
    cin.ignore();

    if (pilihanStatus == 1) {
        drivers[driverCount].status = "Aktif";
    } else {
        drivers[driverCount].status = "Tidak Aktif";
    }

    driverCount++;
    cout << "Pembalap berhasil ditambahkan.\n";
}

void editPembalap(Driver drivers[], int driverCount) {
    if (driverCount == 0) {
        cout << "Belum ada pembalap yang di tambahkan\n";
        return;
    }

    int pilih, pilihanStatus;

    listPembalap(drivers, driverCount);
    cout << "Pilih nomor pembalap yang ingin diedit : ";
    cin >> pilih;
    cin.ignore();

    pilih--;

    cout << "Nama baru        : ";
    getline(cin, drivers[pilih].name);
    cout << "Negara baru      : ";
    getline(cin, drivers[pilih].nationality);
    cout << "Tahun lahir baru : ";
    cin >> drivers[pilih].birthYear;
    cin.ignore();

    cout << "Pilih status baru:\n";
    cout << "1. Aktif\n";
    cout << "2. Tidak Aktif\n";
    cout << "Pilihan          : ";
    cin >> pilihanStatus;
    cin.ignore();

    if (pilihanStatus == 1) {
        drivers[pilih].status = "Aktif";
    } else {
        drivers[pilih].status = "Tidak Aktif";
    }

    cout << "Pembalap berhasil diedit.\n";
}

void hapusPembalap(Driver drivers[], int &driverCount,
                   Contract contracts[], int &contractCount) {
    if (driverCount == 0) {
        cout << "Belum ada pembalap yang di tambahkan\n";
        return;
    }

    int pilih;

    listPembalap(drivers, driverCount);
    cout << "Pilih nomor pembalap yang ingin dihapus : ";
    cin >> pilih;
    cin.ignore();

    pilih--;

    for (int i = 0; i < contractCount; ) {
        if (contracts[i].driverIndex == pilih) {
            for (int j = i; j < contractCount - 1; j++) {
                contracts[j] = contracts[j + 1];
            }
            contractCount--;
        } else {
            if (contracts[i].driverIndex > pilih) {
                contracts[i].driverIndex--;
            }
            i++;
        }
    }

    for (int i = pilih; i < driverCount - 1; i++) {
        drivers[i] = drivers[i + 1];
    }

    driverCount--;
    cout << "Pembalap berhasil dihapus.\n";
}

void tambahKontrak(Contract contracts[], int &contractCount,
                   Driver drivers[], int driverCount,
                   Team teams[], int teamCount) {
    int d, t, pilihanStatus;

    tampilJudul("TAMBAH KONTRAK");

    listPembalap(drivers, driverCount);
    cout << "Pilih nomor driver : ";
    cin >> d;
    cin.ignore();

    listTim(teams, teamCount);
    cout << "Pilih nomor team   : ";
    cin >> t;
    cin.ignore();

    contracts[contractCount].driverIndex = d - 1;
    contracts[contractCount].teamIndex = t - 1;

    cout << "Season             : ";
    cin >> contracts[contractCount].season;
    cin.ignore();

    cout << "Pilih status kontrak:\n";
    cout << "1. Rumor\n";
    cout << "2. Resmi\n";
    cout << "Pilihan            : ";
    cin >> pilihanStatus;
    cin.ignore();

    if (pilihanStatus == 1) {
        contracts[contractCount].status = "Rumor";
    } else {
        contracts[contractCount].status = "Resmi";
    }

    cout << "Start Year         : ";
    cin >> contracts[contractCount].startYear;
    cin.ignore();
    cout << "End Year           : ";
    cin >> contracts[contractCount].endYear;
    cin.ignore();

    contractCount++;
    cout << "Kontrak berhasil ditambahkan.\n";
}

void editKontrak(Contract contracts[], int contractCount,
                 Driver drivers[], int driverCount,
                 Team teams[], int teamCount) {
    if (contractCount == 0) {
        cout << "Belum ada kontrak yang di tambahkan\n";
        return;
    }

    int pilih, d, t, pilihanStatus;

    listKontrak(contracts, contractCount, drivers, teams);
    cout << "Pilih nomor kontrak yang ingin diedit : ";
    cin >> pilih;
    cin.ignore();

    pilih--;

    listPembalap(drivers, driverCount);
    cout << "Driver baru : ";
    cin >> d;
    cin.ignore();

    listTim(teams, teamCount);
    cout << "Team baru   : ";
    cin >> t;
    cin.ignore();

    contracts[pilih].driverIndex = d - 1;
    contracts[pilih].teamIndex = t - 1;

    cout << "Season baru         : ";
    cin >> contracts[pilih].season;
    cin.ignore();

    cout << "Pilih status kontrak baru:\n";
    cout << "1. Rumor\n";
    cout << "2. Resmi\n";
    cout << "Pilihan             : ";
    cin >> pilihanStatus;
    cin.ignore();

    if (pilihanStatus == 1) {
        contracts[pilih].status = "Rumor";
    } else {
        contracts[pilih].status = "Resmi";
    }

    cout << "Start Year baru     : ";
    cin >> contracts[pilih].startYear;
    cin.ignore();
    cout << "End Year baru       : ";
    cin >> contracts[pilih].endYear;
    cin.ignore();

    cout << "Kontrak berhasil diedit.\n";
}

void hapusKontrak(Contract contracts[], int &contractCount,
                  Driver drivers[], Team teams[]) {
    if (contractCount == 0) {
        cout << "Belum ada kontrak yang di tambahkan\n";
        return;
    }

    int pilih;

    listKontrak(contracts, contractCount, drivers, teams);
    cout << "Pilih nomor kontrak yang ingin dihapus : ";
    cin >> pilih;
    cin.ignore();

    pilih--;

    for (int i = pilih; i < contractCount - 1; i++) {
        contracts[i] = contracts[i + 1];
    }

    contractCount--;
    cout << "Kontrak berhasil dihapus.\n";
}

void menuAdmin(Driver drivers[], int &driverCount,
               Team teams[], int teamCount,
               Contract contracts[], int &contractCount) {
    int pilih;

    do {
        tampilJudul("MENU ADMIN");
        cout << "+-----------------------------------+\n";
        cout << "| 1.  List Tim                      |\n";
        cout << "| 2.  List Pembalap                 |\n";
        cout << "| 3.  Tambah Pembalap               |\n";
        cout << "| 4.  Edit Pembalap                 |\n";
        cout << "| 5.  Hapus Pembalap                |\n";
        cout << "| 6.  List Kontrak                  |\n";
        cout << "| 7.  Tambah Kontrak                |\n";
        cout << "| 8.  Edit Kontrak                  |\n";
        cout << "| 9.  Hapus Kontrak                 |\n";
        cout << "| 10. Logout                        |\n";
        cout << "+-----------------------------------+\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: listTim(teams, teamCount); break;
            case 2: listPembalap(drivers, driverCount); break;
            case 3: tambahPembalap(drivers, driverCount); break;
            case 4: editPembalap(drivers, driverCount); break;
            case 5: hapusPembalap(drivers, driverCount, contracts, contractCount); break;
            case 6: listKontrak(contracts, contractCount, drivers, teams); break;
            case 7: tambahKontrak(contracts, contractCount, drivers, driverCount, teams, teamCount); break;
            case 8: editKontrak(contracts, contractCount, drivers, driverCount, teams, teamCount); break;
            case 9: hapusKontrak(contracts, contractCount, drivers, teams); break;
            case 10: cout << "Logout.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 10);
}

void menuAwal(User users[], int &userCount,
              Driver drivers[], int &driverCount,
              Team teams[], int teamCount,
              Contract contracts[], int &contractCount) {
    int pilih;

    do {
        cout << "+-------------------------------------------+\n";
        cout << "|      SELAMAT DATANG DI BURSA TRANSFER F1  |\n";
        cout << "+-------------------------------------------+\n";

        tampilJudul("MENU AWAL");
        cout << "+-----------------------------------+\n";
        cout << "| 1.  Register Admin                |\n";
        cout << "| 2.  Login Admin                   |\n";
        cout << "| 3.  Keluar                        |\n";
        cout << "+-----------------------------------+\n";
        cout << "Pilihan : ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                registerUser(users, userCount);
                break;
            case 2:
                if (login(users, userCount, 0)) {
                    menuAdmin(drivers, driverCount, teams, teamCount, contracts, contractCount);
                }
                break;
            case 3:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 3);
}

int main() {
    User users[MAX_USERS] = {
        {"Attol", "2509106103"}
    };
    int userCount = 1;

    Driver drivers[MAX_DRIVERS] = {
        {"Charles Leclerc","Monaco",1997,"Aktif"},
        {"Lewis Hamilton","UK",1985,"Aktif"},
        {"George Russell","UK",1998,"Aktif"},
        {"Kimi Antonelli","Italy",2006,"Aktif"},
        {"Lando Norris","UK",1999,"Aktif"},
        {"Oscar Piastri","Australia",2001,"Aktif"},
        {"Fernando Alonso","Spain",1981,"Aktif"},
        {"Lance Stroll","Canada",1998,"Aktif"},
        {"Esteban Ocon","France",1996,"Aktif"},
        {"Oliver Bearman","UK",2005,"Aktif"},
        {"Isack Hadjar","France",2003,"Aktif"},
        {"Max Verstappen","Netherlands",1997,"Aktif"},
        {"Carlos Sainz Jr.","Spain",1994,"Aktif"},
        {"Alexander Albon","UK",1996,"Aktif"},
        {"Valtteri Bottas","Finland",1989,"Aktif"},
        {"Sergio Perez","Mexico",1990,"Aktif"},
        {"Nico Hulkenberg","Germany",1987,"Aktif"},
        {"Gabriel Bortoleto","Brazil",2004,"Aktif"},
        {"Pierre Gasly","France",1996,"Aktif"},
        {"Franco Colapinto","Argentina",1999,"Aktif"},
        {"Liam Lawson","New Zealand",2002,"Aktif"},
        {"Arvid Lindblad","Sweden",2004,"Aktif"}
    };
    int driverCount = 22;

    Team teams[NUM_TEAMS] = {
        {"Scuderia Ferrari HP",true},
        {"Mercedes AMG-Petronas",true},
        {"Oracle RedBull Racing",true},
        {"McLaren Mastercard",true},
        {"Aston Martin Aramco",true},
        {"BWT Alpine",true},
        {"Atlassian Williams",true},
        {"TGR Haas",true},
        {"VCAB Racing Bull",true},
        {"Audi Revolut",true},
        {"Cadillac",true}
    };

    Contract contracts[MAX_CONTRACTS];
    int contractCount = 0;

    menuAwal(users, userCount, drivers, driverCount, teams, NUM_TEAMS, contracts, contractCount);

    return 0;
}