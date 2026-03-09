#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct User {
    string username;
    string password;
    bool isAdmin;
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

const int NUM_DRIVERS = 22;
Driver drivers[NUM_DRIVERS] = {
    {"Charles Leclerc","Monaco",1997,"Active"},
    {"Lewis Hamilton","UK",1985,"Active"},
    {"George Russel","UK",1998,"Active"},
    {"Kimi Antonelli","Italy",2006,"Active"},
    {"Lando Norris","UK",1999,"Active"},
    {"Oscar Piastri","Australia",2001,"Active"},
    {"Max Verstappen","Netherlands",1997,"Active"},
    {"Isack Hadjar","France",2003,"Active"},
    {"Fernando Alonso","Spain",1981,"Active"},
    {"Lance Stroll","Canada",2000,"Active"},
    {"Pierre Gasly","France",1996,"Active"},
    {"Franco Colapinto","Argentina",2003,"Active"},
    {"Carlos Sainz","Spain",1994,"Active"},
    {"Alex Albon","Thailand",1996,"Active"},
    {"Esteban Ocon","France",1996,"Active"},
    {"Oliver Bearman","UK",2005,"Active"},
    {"Liam Lawson","NZ",2002,"Active"},
    {"Arvid Lindblad","Sweden",2004,"Active"},
    {"Nico Hulkenberg","Germany",1987,"Active"},
    {"Gabriel Bortoleto","Brazil",2004,"Active"},
    {"Sergio Perez","Mexico",1989,"Active"},
    {"Valteri Bottas","Finland",1989,"Active"}
};

const int NUM_TEAMS = 11;
Team teams[NUM_TEAMS] = {
    {"Scuderia Ferrari HP",true},
    {"Mercedes AMG-Petronas",true},
    {"Oracle RedBull Racing",true},
    {"McLaren Mastercard",true},
    {"Aston Martin Aramco",true},
    {"BWT Alpine",true},
    {"Atlassian Williams",true},
    {"TGR Haas",true},
    {"VCAB RB",true},
    {"Audi Revolut",true},
    {"Cadillac",true}
};

Contract contracts[100];
int contractsCount = 0;

User users[50];
int usersCount = 0;
int currentUserIndex = -1;

void listDrivers() {
    cout << "\n=== Daftar Pembalap ===\n";
    cout << left << setw(5) << "No" << setw(25) << "Nama" << setw(15) << "Kebangsaan"
         << setw(5) << "Umur" << setw(10) << "Status" << "\n";
    cout << string(65,'-') << "\n";
    for(int i=0;i<NUM_DRIVERS;i++){
        int age = 2026 - drivers[i].birthYear;
        cout << setw(5) << (i+1)
             << setw(25) << drivers[i].name
             << setw(15) << drivers[i].nationality
             << setw(5) << age
             << setw(10) << drivers[i].status << "\n";
    }
}

void listTeams() {
    cout << "\n=== Daftar Tim ===\n";
    cout << left << setw(5) << "No" << setw(30) << "Nama" << setw(10) << "Status" << "\n";
    cout << string(45,'-') << "\n";
    for(int i=0;i<NUM_TEAMS;i++){
        cout << setw(5) << (i+1)
             << setw(30) << teams[i].name
             << setw(10) << (teams[i].active?"Active":"Inactive") << "\n";
    }
}

void listContracts() {
    if(contractsCount==0){ cout << "Belum ada kontrak.\n"; return; }
    cout << "\n=== Daftar Kontrak ===\n";
    cout << left << setw(5) << "No" << setw(25) << "Driver" << setw(25) << "Team"
         << setw(8) << "Season" << setw(10) << "Status"
         << setw(10) << "Start" << setw(10) << "End" << "\n";
    cout << string(93,'-') << "\n";
    for(int i=0;i<contractsCount;i++){
        cout << setw(5) << (i+1)
             << setw(25) << drivers[contracts[i].driverIndex].name
             << setw(25) << teams[contracts[i].teamIndex].name
             << setw(8) << contracts[i].season
             << setw(10) << contracts[i].status
             << setw(10) << contracts[i].startYear
             << setw(10) << contracts[i].endYear << "\n";
    }
}

void registerUser(bool isAdmin) {
    cin.ignore();
    string username, password;
    cout << "Masukkan username baru: ";
    getline(cin, username);
    cout << "Masukkan password baru: ";
    getline(cin, password);
    users[usersCount++] = User{username,password,isAdmin};
    cout << "Registrasi berhasil.\n";
}

bool loginUser() {
    cin.ignore();
    string username,password;
    int attempts = 0;
    while(attempts < 3){
        cout << "Username: "; getline(cin, username);
        cout << "Password: "; getline(cin, password);
        for(int i=0;i<usersCount;i++){
            if(users[i].username==username && users[i].password==password){
                currentUserIndex = i;
                cout << "Login berhasil! Selamat datang, " << username << "\n";
                return true;
            }
        }
        attempts++;
        cout << "Login gagal ("<<attempts<<"/3)\n";
        if(attempts==3){
            cout << "Anda salah 3 kali. Program berhenti.\n";
            exit(0);
        }
    }
    return false;
}

void addContract() {
    listDrivers();
    cout << "Pilih nomor driver: "; int d; cin >> d; cin.ignore(); d--;
    listTeams();
    cout << "Pilih nomor team: "; int t; cin >> t; cin.ignore(); t--;
    cout << "Season: "; int s; cin >> s; cin.ignore();
    cout << "Status (Rumor/Resmi): "; string status; getline(cin,status);
    cout << "Start Year: "; int start; cin >> start; cin.ignore();
    cout << "End Year: "; int end; cin >> end; cin.ignore();
    contracts[contractsCount++] = Contract{d,t,s,status,start,end};
    cout << "Kontrak berhasil ditambahkan.\n";
}

void editContract() {
    if(contractsCount==0){ cout<<"Belum ada kontrak.\n"; return;}
    listContracts();
    cout << "Pilih nomor kontrak untuk diedit: "; int idx; cin >> idx; cin.ignore(); idx--;
    if(idx<0 || idx>=contractsCount){ cout<<"Nomor salah\n"; return;}

    listDrivers();
    cout << "Driver baru (0=tidak diubah): "; int d; cin >> d; cin.ignore();
    if(d>0 && d<=NUM_DRIVERS) contracts[idx].driverIndex=d-1;

    listTeams();
    cout << "Team baru (0=tidak diubah): "; int t; cin >> t; cin.ignore();
    if(t>0 && t<=NUM_TEAMS) contracts[idx].teamIndex=t-1;

    cout << "Season baru (0=tidak diubah): "; int s; cin >> s; cin.ignore();
    if(s>0) contracts[idx].season=s;

    cout << "Status baru (kosong=tidak diubah): "; string status; getline(cin,status);
    if(!status.empty()) contracts[idx].status=status;

    cout << "Start Year baru (0=tidak diubah): "; int start; cin >> start; cin.ignore();
    if(start>0) contracts[idx].startYear=start;

    cout << "End Year baru (0=tidak diubah): "; int end; cin >> end; cin.ignore();
    if(end>0) contracts[idx].endYear=end;

    cout << "Kontrak berhasil diperbarui.\n";
}

void deleteContract() {
    if(contractsCount==0){ cout<<"Belum ada kontrak.\n"; return;}
    listContracts();
    cout << "Pilih nomor kontrak untuk dihapus: "; int idx; cin >> idx; cin.ignore(); idx--;
    if(idx<0 || idx>=contractsCount){ cout<<"Nomor salah\n"; return;}
    for(int i=idx;i<contractsCount-1;i++) contracts[i]=contracts[i+1];
    contractsCount--;
    cout << "Kontrak berhasil dihapus.\n";
}

void adminMenu() {
    while(true){
        cout << "\n=== MENU ADMIN ===\n"
             << "1. List Tim\n2. List Pembalap\n3. List Kontrak\n"
             << "4. Tambah Kontrak\n5. Edit Kontrak\n6. Hapus Kontrak\n7. Logout\nPilihan: ";
        int ch; cin >> ch; cin.ignore();
        switch(ch){
            case 1: listTeams(); break;
            case 2: listDrivers(); break;
            case 3: listContracts(); break;
            case 4: addContract(); break;
            case 5: editContract(); break;
            case 6: deleteContract(); break;
            case 7: return;
            default: cout << "Pilihan salah, silakan coba lagi.\n";
        }
    }
}

void userMenu() {
    while(true){
        cout << "\n=== MENU PENGGUNA ===\n"
             << "1. List Tim\n2. List Pembalap\n3. List Kontrak\n4. Logout\nPilihan: ";
        int ch; cin >> ch; cin.ignore();
        switch(ch){
            case 1: listTeams(); break;
            case 2: listDrivers(); break;
            case 3: listContracts(); break;
            case 4: return;
            default: cout << "Pilihan salah, silakan coba lagi.\n";
        }
    }
}

int main() {
    users[usersCount++] = User{"Attol","2509106103",true};

    while(true){
        cout << "\n=== SISTEM F1 TRANSFER ===\n1. Register Pengguna\n2. Login\n3. Keluar\nPilihan: ";
        int ch; cin >> ch; cin.ignore();
        switch(ch){
            case 1: {
                cout << "Apakah admin? (y/n): "; string resp; getline(cin, resp);
                bool isAdmin = (resp=="y" || resp=="Y");
                registerUser(isAdmin);
                break;
            }
            case 2:
                if(loginUser()){
                    if(users[currentUserIndex].isAdmin) adminMenu();
                    else userMenu();
                }
                break;
            case 3: return 0;
            default: cout << "Pilihan salah, silakan coba lagi.\n";
        }
    }
}