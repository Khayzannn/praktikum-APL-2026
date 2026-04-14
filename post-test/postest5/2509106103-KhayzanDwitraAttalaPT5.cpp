#include <iostream>
#include <string>
#include <iomanip>
#include <utility>
#include <limits>

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

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidDriverIndex(int index, int totalDrivers) {
    return index >= 0 && index < totalDrivers;
}

bool isValidTeamIndex(int index, int totalTeams) {
    return index >= 0 && index < totalTeams;
}

bool isContractActiveInYear(const Contract &contract, int year) {
    return contract.startYear <= year && contract.endYear >= year;
}


int partitionName(Driver drivers[], int low, int high) {
    string pivot = drivers[high].name;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (drivers[j].name < pivot) {
            i++;
            swap(drivers[i], drivers[j]);
        }
    }

    swap(drivers[i + 1], drivers[high]);
    return i + 1;
}

void quickSortByName(Driver drivers[], int low, int high) {
    if (low < high) {
        int pivot = partitionName(drivers, low, high);
        quickSortByName(drivers, low, pivot - 1);
        quickSortByName(drivers, pivot + 1, high);
    }
}

int partitionNationality(Driver drivers[], int low, int high) {
    string pivot = drivers[high].nationality;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (drivers[j].nationality < pivot) {
            i++;
            swap(drivers[i], drivers[j]);
        }
    }

    swap(drivers[i + 1], drivers[high]);
    return i + 1;
}

void quickSortByNationality(Driver drivers[], int low, int high) {
    if (low < high) {
        int pivot = partitionNationality(drivers, low, high);
        quickSortByNationality(drivers, low, pivot - 1);
        quickSortByNationality(drivers, pivot + 1, high);
    }
}

int partitionBirthYear(Driver drivers[], int low, int high) {
    int pivot = drivers[high].birthYear;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (drivers[j].birthYear > pivot) {
            i++;
            swap(drivers[i], drivers[j]);
        }
    }

    swap(drivers[i + 1], drivers[high]);
    return i + 1;
}

void quickSortByBirthYear(Driver drivers[], int low, int high) {
    if (low < high) {
        int pivot = partitionBirthYear(drivers, low, high);
        quickSortByBirthYear(drivers, low, pivot - 1);
        quickSortByBirthYear(drivers, pivot + 1, high);
    }
}

int partitionAge(Driver drivers[], int low, int high) {
    int pivotAge = CURRENT_YEAR - drivers[high].birthYear;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        int ageJ = CURRENT_YEAR - drivers[j].birthYear;
        if (ageJ > pivotAge) {
            i++;
            swap(drivers[i], drivers[j]);
        }
    }

    swap(drivers[i + 1], drivers[high]);
    return i + 1;
}

void quickSortByAge(Driver drivers[], int low, int high) {
    if (low < high) {
        int pivot = partitionAge(drivers, low, high);
        quickSortByAge(drivers, low, pivot - 1);
        quickSortByAge(drivers, pivot + 1, high);
    }
}


int partitionContractByDriverName(Contract contracts[], int low, int high, Driver drivers[]) {
    string pivot = drivers[contracts[high].driverIndex].name;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (drivers[contracts[j].driverIndex].name < pivot) {
            i++;
            swap(contracts[i], contracts[j]);
        }
    }

    swap(contracts[i + 1], contracts[high]);
    return i + 1;
}

void quickSortContractByDriverName(Contract contracts[], int low, int high, Driver drivers[]) {
    if (low < high) {
        int pivot = partitionContractByDriverName(contracts, low, high, drivers);
        quickSortContractByDriverName(contracts, low, pivot - 1, drivers);
        quickSortContractByDriverName(contracts, pivot + 1, high, drivers);
    }
}

int partitionContractByTeamName(Contract contracts[], int low, int high, Team teams[]) {
    string pivot = teams[contracts[high].teamIndex].name;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (teams[contracts[j].teamIndex].name < pivot) {
            i++;
            swap(contracts[i], contracts[j]);
        }
    }

    swap(contracts[i + 1], contracts[high]);
    return i + 1;
}

void quickSortContractByTeamName(Contract contracts[], int low, int high, Team teams[]) {
    if (low < high) {
        int pivot = partitionContractByTeamName(contracts, low, high, teams);
        quickSortContractByTeamName(contracts, low, pivot - 1, teams);
        quickSortContractByTeamName(contracts, pivot + 1, high, teams);
    }
}

int partitionContractByStartYear(Contract contracts[], int low, int high) {
    int pivot = contracts[high].startYear;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (contracts[j].startYear > pivot) {
            i++;
            swap(contracts[i], contracts[j]);
        }
    }

    swap(contracts[i + 1], contracts[high]);
    return i + 1;
}

void quickSortContractByStartYear(Contract contracts[], int low, int high) {
    if (low < high) {
        int pivot = partitionContractByStartYear(contracts, low, high);
        quickSortContractByStartYear(contracts, low, pivot - 1);
        quickSortContractByStartYear(contracts, pivot + 1, high);
    }
}

int partitionContractByEndYear(Contract contracts[], int low, int high) {
    int pivot = contracts[high].endYear;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (contracts[j].endYear > pivot) {
            i++;
            swap(contracts[i], contracts[j]);
        }
    }

    swap(contracts[i + 1], contracts[high]);
    return i + 1;
}

void quickSortContractByEndYear(Contract contracts[], int low, int high) {
    if (low < high) {
        int pivot = partitionContractByEndYear(contracts, low, high);
        quickSortContractByEndYear(contracts, low, pivot - 1);
        quickSortContractByEndYear(contracts, pivot + 1, high);
    }
}

void initializeDrivers(Driver drivers[], int &totalDrivers) {
    string names[] = {
        "Charles Leclerc", "Lewis Hamilton", "George Russell", "Kimi Antonelli",
        "Lando Norris", "Oscar Piastri", "Fernando Alonso", "Lance Stroll",
        "Esteban Ocon", "Oliver Bearman", "Max Verstappen", "Sergio Perez",
        "Arvid Lindblad", "Pierre Gasly", "Valtteri Bottas", "Isack Hadjar",
        "Nico Hulkenberg", "Gabriel Bortoletto", "Liam Lawson", "Alexander Albon",
        "Carlos Sainz", "Franco Colapinto"
    };

    string countries[] = {
        "Monaco", "UK", "UK", "Italy",
        "UK", "Australia", "Spain", "Canada",
        "France", "UK", "Netherlands", "Mexico",
        "Sweden", "France", "Finland", "France",
        "Germany", "Brazil", "New Zealand", "Thailand",
        "Spain", "Argentina"
    };

    int birthYears[] = {
        1997, 1985, 1998, 2006,
        1999, 2001, 1981, 1998,
        1996, 2005, 1997, 1990,
        2004, 1996, 1989, 2003,
        1987, 2004, 2002, 1996,
        1994, 2003
    };

    for (int i = 0; i < 22; i++) {
        drivers[i].name = names[i];
        drivers[i].nationality = countries[i];
        drivers[i].birthYear = birthYears[i];
        drivers[i].status = "Aktif";
    }

    totalDrivers = 22;
}

void initializeTeams(Team teams[], int &totalTeams) {
    string names[] = {
        "Ferrari", "Mercedes", "McLaren", "Red Bull", "RB",
        "Alpine", "Aston Martin", "Audi", "Williams", "Cadillac", "Haas"
    };

    for (int i = 0; i < 11; i++) {
        teams[i].name = names[i];
    }

    totalTeams = 11;
}

void initializeUsers(User users[], int &totalUsers) {
    users[0].username = "Attol";
    users[0].password = "2509106103";
    totalUsers = 1;
}

void initializeContracts(Contract contracts[], int &totalContracts) {
    int map[22] = {0, 0, 1, 1, 2, 2, 6, 6, 10, 10, 3, 9, 4, 5, 9, 3, 7, 7, 4, 8, 8, 5};

    for (int i = 0; i < 22; i++) {
        contracts[i].driverIndex = i;
        contracts[i].teamIndex = map[i];
        contracts[i].startYear = 2025;
        contracts[i].endYear = 2027;
    }

    totalContracts = 22;
}


void registerUser(User users[], int &totalUsers) {
    if (totalUsers >= MAX_USERS) {
        cout << "Kapasitas user penuh!\n";
        return;
    }

    cout << "Username: ";
    getline(cin, users[totalUsers].username);

    cout << "Password: ";
    getline(cin, users[totalUsers].password);

    totalUsers++;
    cout << "Registrasi berhasil!\n";
}

bool loginUser(User users[], int totalUsers) {
    string username, password;

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    getline(cin, password);

    for (int i = 0; i < totalUsers; i++) {
        if (users[i].username == username && users[i].password == password) {
            return true;
        }
    }

    cout << "Login gagal!\n";
    return false;
}


void displayDrivers(Driver drivers[], int totalDrivers) {
    cout << "\n=== LIST DRIVER ===\n";
    cout << left
         << setw(4)  << "No"
         << setw(25) << "Nama"
         << setw(15) << "Negara"
         << setw(12) << "Tahun Lahir"
         << setw(8)  << "Umur"
         << setw(15) << "Status" << '\n';

    cout << string(79, '=') << '\n';

    for (int i = 0; i < totalDrivers; i++) {
        cout << left
             << setw(4)  << i + 1
             << setw(25) << drivers[i].name
             << setw(15) << drivers[i].nationality
             << setw(12) << drivers[i].birthYear
             << setw(8)  << (CURRENT_YEAR - drivers[i].birthYear)
             << setw(15) << drivers[i].status
             << '\n';
    }
}

void displayTeams(Team teams[], int totalTeams) {
    cout << "\n=== LIST TEAM ===\n";
    for (int i = 0; i < totalTeams; i++) {
        cout << i + 1 << ". " << teams[i].name << '\n';
    }
}

void displayAllContracts(Contract contracts[], int totalContracts, Driver drivers[], Team teams[]) {
    cout << "\n=== LIST SEMUA KONTRAK ===\n";
    cout << left
         << setw(4)  << "No"
         << setw(25) << "Driver"
         << setw(20) << "Tim"
         << setw(12) << "Mulai"
         << setw(12) << "Selesai"
         << setw(15) << "Status 2026"
         << '\n';

    cout << string(88, '=') << '\n';

    for (int i = 0; i < totalContracts; i++) {
        string status2026 = isContractActiveInYear(contracts[i], CURRENT_YEAR) ? "Aktif" : "Tidak Aktif";

        cout << left
             << setw(4)  << i + 1
             << setw(25) << drivers[contracts[i].driverIndex].name
             << setw(20) << teams[contracts[i].teamIndex].name
             << setw(12) << contracts[i].startYear
             << setw(12) << contracts[i].endYear
             << setw(15) << status2026
             << '\n';
    }

    if (totalContracts == 0) {
        cout << "Belum ada data kontrak.\n";
    }
}

void displayActiveContracts2026(Contract contracts[], int totalContracts, Driver drivers[], Team teams[]) {
    cout << "\n=== LIST KONTRAK AKTIF TAHUN " << CURRENT_YEAR << " ===\n";
    cout << left
         << setw(4)  << "No"
         << setw(25) << "Driver"
         << setw(20) << "Tim"
         << setw(12) << "Mulai"
         << setw(12) << "Selesai"
         << '\n';

    cout << string(73, '=') << '\n';

    int nomor = 1;
    for (int i = 0; i < totalContracts; i++) {
        if (isContractActiveInYear(contracts[i], CURRENT_YEAR)) {
            cout << left
                 << setw(4)  << nomor
                 << setw(25) << drivers[contracts[i].driverIndex].name
                 << setw(20) << teams[contracts[i].teamIndex].name
                 << setw(12) << contracts[i].startYear
                 << setw(12) << contracts[i].endYear
                 << '\n';
            nomor++;
        }
    }

    if (nomor == 1) {
        cout << "Tidak ada kontrak aktif pada tahun " << CURRENT_YEAR << ".\n";
    }
}


void sortDriversMenu(Driver drivers[], int totalDrivers) {
    int sortChoice;

    cout << "\n=== SORT DRIVER BY ===\n";
    cout << "1. Umur (Descending)\n";
    cout << "2. Negara (A-Z)\n";
    cout << "3. Tahun lahir (Descending)\n";
    cout << "4. Nama (A-Z)\n";
    cout << "Pilih: ";
    cin >> sortChoice;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid!\n";
        return;
    }

    switch (sortChoice) {
        case 1:
            quickSortByAge(drivers, 0, totalDrivers - 1);
            break;
        case 2:
            quickSortByNationality(drivers, 0, totalDrivers - 1);
            break;
        case 3:
            quickSortByBirthYear(drivers, 0, totalDrivers - 1);
            break;
        case 4:
            quickSortByName(drivers, 0, totalDrivers - 1);
            break;
        default:
            cout << "Pilihan sort tidak valid!\n";
            return;
    }

    displayDrivers(drivers, totalDrivers);
}


void sortContractsMenu(Contract contracts[], int totalContracts, Driver drivers[], Team teams[]) {
    int sortChoice;
    int filterChoice;

    cout << "\n=== SORT KONTRAK BY ===\n";
    cout << "1. Nama Driver (A-Z)\n";
    cout << "2. Nama Tim (A-Z)\n";
    cout << "3. Tahun Mulai (Descending)\n";
    cout << "4. Tahun Selesai (Descending)\n";
    cout << "Pilih: ";
    cin >> sortChoice;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid!\n";
        return;
    }

    switch (sortChoice) {
        case 1:
            quickSortContractByDriverName(contracts, 0, totalContracts - 1, drivers);
            break;
        case 2:
            quickSortContractByTeamName(contracts, 0, totalContracts - 1, teams);
            break;
        case 3:
            quickSortContractByStartYear(contracts, 0, totalContracts - 1);
            break;
        case 4:
            quickSortContractByEndYear(contracts, 0, totalContracts - 1);
            break;
        default:
            cout << "Pilihan sort tidak valid!\n";
            return;
    }

    cout << "\n=== TAMPILKAN KONTRAK ===\n";
    cout << "1. Semua kontrak\n";
    cout << "2. Hanya kontrak aktif tahun 2026\n";
    cout << "Pilih: ";
    cin >> filterChoice;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid!\n";
        return;
    }

    switch (filterChoice) {
        case 1:
            displayAllContracts(contracts, totalContracts, drivers, teams);
            break;
        case 2:
            displayActiveContracts2026(contracts, totalContracts, drivers, teams);
            break;
        default:
            cout << "Pilihan tampilan tidak valid!\n";
            break;
    }
}


void addDriver(Driver drivers[], int &totalDrivers) {
    if (totalDrivers >= MAX_DRIVERS) {
        cout << "Data driver penuh!\n";
        return;
    }

    clearInput();

    cout << "Nama: ";
    getline(cin, drivers[totalDrivers].name);

    cout << "Negara: ";
    getline(cin, drivers[totalDrivers].nationality);

    cout << "Tahun lahir: ";
    cin >> drivers[totalDrivers].birthYear;

    if (cin.fail()) {
        clearInput();
        cout << "Input tahun lahir tidak valid!\n";
        return;
    }

    clearInput();

    cout << "Status: ";
    getline(cin, drivers[totalDrivers].status);

    totalDrivers++;
    cout << "Driver berhasil ditambahkan!\n";
}


void editDriver(Driver drivers[], int totalDrivers) {
    if (totalDrivers == 0) {
        cout << "Tidak ada data driver.\n";
        return;
    }

    displayDrivers(drivers, totalDrivers);

    int choice;
    cout << "Pilih nomor driver yang ingin diedit: ";
    cin >> choice;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid!\n";
        return;
    }

    int index = choice - 1;
    if (!isValidDriverIndex(index, totalDrivers)) {
        cout << "Nomor driver tidak valid!\n";
        return;
    }

    clearInput();

    cout << "Nama baru: ";
    getline(cin, drivers[index].name);

    cout << "Negara baru: ";
    getline(cin, drivers[index].nationality);

    cout << "Tahun lahir baru: ";
    cin >> drivers[index].birthYear;

    if (cin.fail()) {
        clearInput();
        cout << "Input tahun lahir tidak valid!\n";
        return;
    }

    clearInput();

    cout << "Status baru: ";
    getline(cin, drivers[index].status);

    cout << "Data driver berhasil diupdate!\n";
}


void deleteDriverContracts(Contract contracts[], int &totalContracts, int driverIndex) {
    for (int i = 0; i < totalContracts; i++) {
        if (contracts[i].driverIndex == driverIndex) {
            for (int j = i; j < totalContracts - 1; j++) {
                contracts[j] = contracts[j + 1];
            }
            totalContracts--;
            i--;
        }
    }
}

void adjustContractDriverIndexes(Contract contracts[], int totalContracts, int deletedDriverIndex) {
    for (int i = 0; i < totalContracts; i++) {
        if (contracts[i].driverIndex > deletedDriverIndex) {
            contracts[i].driverIndex--;
        }
    }
}

void deleteDriver(Driver drivers[], int &totalDrivers, Contract contracts[], int &totalContracts) {
    if (totalDrivers == 0) {
        cout << "Tidak ada data driver.\n";
        return;
    }

    displayDrivers(drivers, totalDrivers);

    int choice;
    cout << "Pilih nomor driver yang ingin dihapus: ";
    cin >> choice;

    if (cin.fail()) {
        clearInput();
        cout << "Input tidak valid!\n";
        return;
    }

    int index = choice - 1;
    if (!isValidDriverIndex(index, totalDrivers)) {
        cout << "Nomor driver tidak valid!\n";
        return;
    }

    deleteDriverContracts(contracts, totalContracts, index);
    adjustContractDriverIndexes(contracts, totalContracts, index);

    for (int i = index; i < totalDrivers - 1; i++) {
        drivers[i] = drivers[i + 1];
    }

    totalDrivers--;
    cout << "Driver berhasil dihapus!\n";
}


void addContract(Driver drivers[], int totalDrivers,
                 Team teams[], int totalTeams,
                 Contract contracts[], int &totalContracts) {
    if (totalContracts >= MAX_CONTRACTS) {
        cout << "Data kontrak penuh!\n";
        return;
    }

    int driverChoice, teamChoice, startYear, endYear;

    displayDrivers(drivers, totalDrivers);
    cout << "Pilih driver: ";
    cin >> driverChoice;

    if (cin.fail()) {
        clearInput();
        cout << "Input driver tidak valid!\n";
        return;
    }

    int driverIndex = driverChoice - 1;
    if (!isValidDriverIndex(driverIndex, totalDrivers)) {
        cout << "Pilihan driver tidak valid!\n";
        return;
    }

    displayTeams(teams, totalTeams);
    cout << "Pilih tim: ";
    cin >> teamChoice;

    if (cin.fail()) {
        clearInput();
        cout << "Input tim tidak valid!\n";
        return;
    }

    int teamIndex = teamChoice - 1;
    if (!isValidTeamIndex(teamIndex, totalTeams)) {
        cout << "Pilihan tim tidak valid!\n";
        return;
    }

    cout << "Tahun mulai: ";
    cin >> startYear;
    if (cin.fail()) {
        clearInput();
        cout << "Input tahun mulai tidak valid!\n";
        return;
    }

    cout << "Tahun selesai: ";
    cin >> endYear;
    if (cin.fail()) {
        clearInput();
        cout << "Input tahun selesai tidak valid!\n";
        return;
    }

    if (endYear < startYear) {
        cout << "Tahun selesai tidak boleh lebih kecil dari tahun mulai!\n";
        return;
    }

    contracts[totalContracts].driverIndex = driverIndex;
    contracts[totalContracts].teamIndex = teamIndex;
    contracts[totalContracts].startYear = startYear;
    contracts[totalContracts].endYear = endYear;
    totalContracts++;

    drivers[driverIndex].status = "Aktif";

    cout << "Kontrak berhasil ditambahkan!\n";
}


void transferDriver(Driver drivers[], int totalDrivers,
                    Team teams[], int totalTeams,
                    Contract contracts[], int &totalContracts) {
    addContract(drivers, totalDrivers, teams, totalTeams, contracts, totalContracts);
}


void adminMenu(Driver drivers[], int &totalDrivers,
               Team teams[], int totalTeams,
               Contract contracts[], int &totalContracts) {
    int choice;

    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. List Driver\n";
        cout << "2. Tambah Driver\n";
        cout << "3. Edit Driver\n";
        cout << "4. Hapus Driver\n";
        cout << "5. List Kontrak\n";
        cout << "6. Tambah / Transfer Kontrak\n";
        cout << "7. Logout\n";
        cout << "Pilih: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Input tidak valid!\n";
            continue;
        }

        switch (choice) {
            case 1:
                sortDriversMenu(drivers, totalDrivers);
                break;
            case 2:
                addDriver(drivers, totalDrivers);
                break;
            case 3:
                editDriver(drivers, totalDrivers);
                break;
            case 4:
                deleteDriver(drivers, totalDrivers, contracts, totalContracts);
                break;
            case 5:
                if (totalContracts > 0) {
                    sortContractsMenu(contracts, totalContracts, drivers, teams);
                } else {
                    cout << "Tidak ada data kontrak.\n";
                }
                break;
            case 6:
                transferDriver(drivers, totalDrivers, teams, totalTeams, contracts, totalContracts);
                break;
            case 7:
                cout << "Logout...\n";
                break;
            default:
                cout << "Menu belum tersedia.\n";
        }

    } while (choice != 7);
}


int main() {
    Driver drivers[MAX_DRIVERS];
    User users[MAX_USERS];
    Team teams[MAX_TEAMS];
    Contract contracts[MAX_CONTRACTS];

    int totalDrivers = 0;
    int totalUsers = 0;
    int totalTeams = 0;
    int totalContracts = 0;

    initializeDrivers(drivers, totalDrivers);
    initializeTeams(teams, totalTeams);
    initializeUsers(users, totalUsers);
    initializeContracts(contracts, totalContracts);

    int choice;

    do {
        cout << "\n=== MENU AWAL ===\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Input tidak valid!\n";
            continue;
        }

        clearInput();

        if (choice == 1) {
            registerUser(users, totalUsers);
        } else if (choice == 2) {
            if (loginUser(users, totalUsers)) {
                adminMenu(drivers, totalDrivers, teams, totalTeams, contracts, totalContracts);
            }
        } else if (choice == 3) {
            cout << "Program selesai.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }

    } while (choice != 3);

    return 0;
}