#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <utility>

using namespace std;

const int MAX_DRIVERS = 50;
const int MAX_USERS = 20;
const int MAX_TEAMS = 11;
const int MAX_CONTRACTS = 100;
const int CURRENT_YEAR = 2026;
const int RADIX_CHAR_RANGE = 27;

// ================= STRUCT =================

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

// ================= ERROR CLASS =================

class F1Exception : public runtime_error {
public:
    F1Exception(const string &message) : runtime_error(message) {}
};

// ================= HELPER =================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void line(char symbol = '=') {
    cout << string(80, symbol) << '\n';
}

void title(const string &text) {
    cout << "\n";
    line('=');
    cout << ">> " << text << '\n';
    line('=');
}

int readInt(const string &prompt, int minValue, int maxValue) {
    int value;

    cout << prompt;
    cin >> value;

    if (cin.fail()) {
        clearInput();
        throw F1Exception("Input harus berupa angka!");
    }

    clearInput();

    if (value < minValue || value > maxValue) {
        throw F1Exception("Input berada di luar batas yang diperbolehkan!");
    }

    return value;
}

string readText(const string &prompt) {
    string text;

    cout << prompt;
    getline(cin, text);

    if (text.empty()) {
        throw F1Exception("Input tidak boleh kosong!");
    }

    return text;
}

int getAge(const Driver &driver) {
    return CURRENT_YEAR - driver.birthYear;
}

string toUpperCase(string text) {
    for (string::size_type i = 0; i < text.length(); i++) {
        text[i] = static_cast<char>(
            toupper(static_cast<unsigned char>(text[i]))
        );
    }
    return text;
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

// ================= RADIX HELPER =================

int getRadixCharValueFromLeft(const string &text, int posFromLeft) {
    int length = static_cast<int>(text.length());

    if (posFromLeft < 0 || posFromLeft >= length) {
        return 0;
    }

    unsigned char c = static_cast<unsigned char>(
        text[static_cast<string::size_type>(posFromLeft)]
    );

    c = static_cast<unsigned char>(toupper(c));

    if (c >= 'A' && c <= 'Z') {
        return static_cast<int>(c - 'A' + 1);
    }

    return 0;
}

int getMaxNameLengthDrivers(Driver drivers[], int totalDrivers) {
    int maxLen = 0;

    for (int i = 0; i < totalDrivers; i++) {
        int len = static_cast<int>(drivers[i].name.length());

        if (len > maxLen) {
            maxLen = len;
        }
    }

    return maxLen;
}

int getMaxNameLengthContractsByDriver(Contract contracts[], int totalContracts, Driver drivers[]) {
    int maxLen = 0;

    for (int i = 0; i < totalContracts; i++) {
        int len = static_cast<int>(drivers[contracts[i].driverIndex].name.length());

        if (len > maxLen) {
            maxLen = len;
        }
    }

    return maxLen;
}

int getMaxNameLengthContractsByTeam(Contract contracts[], int totalContracts, Team teams[]) {
    int maxLen = 0;

    for (int i = 0; i < totalContracts; i++) {
        int len = static_cast<int>(teams[contracts[i].teamIndex].name.length());

        if (len > maxLen) {
            maxLen = len;
        }
    }

    return maxLen;
}

// ================= QUICK SORT ASCENDING =================

int partitionNationalityAsc(Driver drivers[], int low, int high) {
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

void quickSortNationalityAsc(Driver drivers[], int low, int high) {
    if (low < high) {
        int pivot = partitionNationalityAsc(drivers, low, high);
        quickSortNationalityAsc(drivers, low, pivot - 1);
        quickSortNationalityAsc(drivers, pivot + 1, high);
    }
}

int partitionAgeAsc(Driver drivers[], int low, int high) {
    int pivot = getAge(drivers[high]);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (getAge(drivers[j]) < pivot) {
            i++;
            swap(drivers[i], drivers[j]);
        }
    }

    swap(drivers[i + 1], drivers[high]);
    return i + 1;
}

void quickSortAgeAsc(Driver drivers[], int low, int high) {
    if (low < high) {
        int pivot = partitionAgeAsc(drivers, low, high);
        quickSortAgeAsc(drivers, low, pivot - 1);
        quickSortAgeAsc(drivers, pivot + 1, high);
    }
}

int partitionContractStartYearAsc(Contract contracts[], int low, int high) {
    int pivot = contracts[high].startYear;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (contracts[j].startYear < pivot) {
            i++;
            swap(contracts[i], contracts[j]);
        }
    }

    swap(contracts[i + 1], contracts[high]);
    return i + 1;
}

void quickSortContractStartYearAsc(Contract contracts[], int low, int high) {
    if (low < high) {
        int pivot = partitionContractStartYearAsc(contracts, low, high);
        quickSortContractStartYearAsc(contracts, low, pivot - 1);
        quickSortContractStartYearAsc(contracts, pivot + 1, high);
    }
}

int partitionContractEndYearAsc(Contract contracts[], int low, int high) {
    int pivot = contracts[high].endYear;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (contracts[j].endYear < pivot) {
            i++;
            swap(contracts[i], contracts[j]);
        }
    }

    swap(contracts[i + 1], contracts[high]);
    return i + 1;
}

void quickSortContractEndYearAsc(Contract contracts[], int low, int high) {
    if (low < high) {
        int pivot = partitionContractEndYearAsc(contracts, low, high);
        quickSortContractEndYearAsc(contracts, low, pivot - 1);
        quickSortContractEndYearAsc(contracts, pivot + 1, high);
    }
}

// ================= BUBBLE SORT DESCENDING =================

void bubbleSortAgeDesc(Driver drivers[], int totalDrivers) {
    for (int i = 0; i < totalDrivers - 1; i++) {
        for (int j = 0; j < totalDrivers - i - 1; j++) {
            if (getAge(drivers[j]) < getAge(drivers[j + 1])) {
                swap(drivers[j], drivers[j + 1]);
            }
        }
    }
}

void bubbleSortBirthYearDesc(Driver drivers[], int totalDrivers) {
    for (int i = 0; i < totalDrivers - 1; i++) {
        for (int j = 0; j < totalDrivers - i - 1; j++) {
            if (drivers[j].birthYear < drivers[j + 1].birthYear) {
                swap(drivers[j], drivers[j + 1]);
            }
        }
    }
}

void bubbleSortContractStartYearDesc(Contract contracts[], int totalContracts) {
    for (int i = 0; i < totalContracts - 1; i++) {
        for (int j = 0; j < totalContracts - i - 1; j++) {
            if (contracts[j].startYear < contracts[j + 1].startYear) {
                swap(contracts[j], contracts[j + 1]);
            }
        }
    }
}

void bubbleSortContractEndYearDesc(Contract contracts[], int totalContracts) {
    for (int i = 0; i < totalContracts - 1; i++) {
        for (int j = 0; j < totalContracts - i - 1; j++) {
            if (contracts[j].endYear < contracts[j + 1].endYear) {
                swap(contracts[j], contracts[j + 1]);
            }
        }
    }
}

// ================= RADIX SORT NAMA DRIVER =================

void countingSortDriversByName(Driver drivers[], int totalDrivers, int posFromLeft) {
    Driver output[MAX_DRIVERS];
    int count[RADIX_CHAR_RANGE] = {0};

    for (int i = 0; i < totalDrivers; i++) {
        int key = getRadixCharValueFromLeft(drivers[i].name, posFromLeft);
        count[key]++;
    }

    for (int i = 1; i < RADIX_CHAR_RANGE; i++) {
        count[i] += count[i - 1];
    }

    for (int i = totalDrivers - 1; i >= 0; i--) {
        int key = getRadixCharValueFromLeft(drivers[i].name, posFromLeft);
        output[count[key] - 1] = drivers[i];
        count[key]--;
    }

    for (int i = 0; i < totalDrivers; i++) {
        drivers[i] = output[i];
    }
}

void radixSortDriversByName(Driver drivers[], int totalDrivers) {
    int maxLen = getMaxNameLengthDrivers(drivers, totalDrivers);

    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortDriversByName(drivers, totalDrivers, pos);
    }
}

// ================= RADIX SORT KONTRAK =================

void countingSortContractsByDriverName(Contract contracts[], int totalContracts, Driver drivers[], int posFromLeft) {
    Contract output[MAX_CONTRACTS];
    int count[RADIX_CHAR_RANGE] = {0};

    for (int i = 0; i < totalContracts; i++) {
        int key = getRadixCharValueFromLeft(drivers[contracts[i].driverIndex].name, posFromLeft);
        count[key]++;
    }

    for (int i = 1; i < RADIX_CHAR_RANGE; i++) {
        count[i] += count[i - 1];
    }

    for (int i = totalContracts - 1; i >= 0; i--) {
        int key = getRadixCharValueFromLeft(drivers[contracts[i].driverIndex].name, posFromLeft);
        output[count[key] - 1] = contracts[i];
        count[key]--;
    }

    for (int i = 0; i < totalContracts; i++) {
        contracts[i] = output[i];
    }
}

void radixSortContractsByDriverName(Contract contracts[], int totalContracts, Driver drivers[]) {
    int maxLen = getMaxNameLengthContractsByDriver(contracts, totalContracts, drivers);

    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortContractsByDriverName(contracts, totalContracts, drivers, pos);
    }
}

void countingSortContractsByTeamName(Contract contracts[], int totalContracts, Team teams[], int posFromLeft) {
    Contract output[MAX_CONTRACTS];
    int count[RADIX_CHAR_RANGE] = {0};

    for (int i = 0; i < totalContracts; i++) {
        int key = getRadixCharValueFromLeft(teams[contracts[i].teamIndex].name, posFromLeft);
        count[key]++;
    }

    for (int i = 1; i < RADIX_CHAR_RANGE; i++) {
        count[i] += count[i - 1];
    }

    for (int i = totalContracts - 1; i >= 0; i--) {
        int key = getRadixCharValueFromLeft(teams[contracts[i].teamIndex].name, posFromLeft);
        output[count[key] - 1] = contracts[i];
        count[key]--;
    }

    for (int i = 0; i < totalContracts; i++) {
        contracts[i] = output[i];
    }
}

void radixSortContractsByTeamName(Contract contracts[], int totalContracts, Team teams[]) {
    int maxLen = getMaxNameLengthContractsByTeam(contracts, totalContracts, teams);

    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortContractsByTeamName(contracts, totalContracts, teams, pos);
    }
}

// ================= INIT DATA =================

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
    int map[22] = {
        0, 0, 1, 1, 2, 2, 6, 6, 10, 10, 3,
        9, 4, 5, 9, 3, 7, 7, 4, 8, 8, 5
    };

    for (int i = 0; i < 22; i++) {
        contracts[i].driverIndex = i;
        contracts[i].teamIndex = map[i];
        contracts[i].startYear = 2025;
        contracts[i].endYear = 2027;
    }

    totalContracts = 22;
}

// ================= DISPLAY =================

void displayDrivers(Driver drivers[], int totalDrivers) {
    title("LIST DRIVER FORMULA 1");

    cout << left
         << setw(4)  << "No"
         << setw(25) << "Nama"
         << setw(15) << "Negara"
         << setw(12) << "Lahir"
         << setw(8)  << "Umur"
         << setw(12) << "Status" << '\n';

    line('-');

    for (int i = 0; i < totalDrivers; i++) {
        cout << left
             << setw(4)  << i + 1
             << setw(25) << drivers[i].name
             << setw(15) << drivers[i].nationality
             << setw(12) << drivers[i].birthYear
             << setw(8)  << getAge(drivers[i])
             << setw(12) << drivers[i].status << '\n';
    }
}

void displayTeams(Team teams[], int totalTeams) {
    title("LIST TEAM");

    for (int i = 0; i < totalTeams; i++) {
        cout << setw(3) << i + 1 << ". " << teams[i].name << '\n';
    }
}

void displayContracts(Contract contracts[], int totalContracts, Driver drivers[], Team teams[]) {
    title("LIST SEMUA KONTRAK");

    cout << left
         << setw(4)  << "No"
         << setw(25) << "Driver"
         << setw(18) << "Team"
         << setw(10) << "Mulai"
         << setw(10) << "Selesai"
         << setw(12) << "2026" << '\n';

    line('-');

    if (totalContracts == 0) {
        cout << "Belum ada data kontrak.\n";
        return;
    }

    for (int i = 0; i < totalContracts; i++) {
        string status2026 = isContractActiveInYear(contracts[i], CURRENT_YEAR) ? "Aktif" : "Tidak";

        cout << left
             << setw(4)  << i + 1
             << setw(25) << drivers[contracts[i].driverIndex].name
             << setw(18) << teams[contracts[i].teamIndex].name
             << setw(10) << contracts[i].startYear
             << setw(10) << contracts[i].endYear
             << setw(12) << status2026 << '\n';
    }
}

void displayActiveContracts2026(Contract contracts[], int totalContracts, Driver drivers[], Team teams[]) {
    title("LIST KONTRAK AKTIF TAHUN 2026");

    cout << left
         << setw(4)  << "No"
         << setw(25) << "Driver"
         << setw(18) << "Team"
         << setw(10) << "Mulai"
         << setw(10) << "Selesai" << '\n';

    line('-');

    int nomor = 1;

    for (int i = 0; i < totalContracts; i++) {
        if (isContractActiveInYear(contracts[i], CURRENT_YEAR)) {
            cout << left
                 << setw(4)  << nomor
                 << setw(25) << drivers[contracts[i].driverIndex].name
                 << setw(18) << teams[contracts[i].teamIndex].name
                 << setw(10) << contracts[i].startYear
                 << setw(10) << contracts[i].endYear << '\n';
            nomor++;
        }
    }

    if (nomor == 1) {
        cout << "Tidak ada kontrak aktif pada tahun 2026.\n";
    }
}

void displayFoundDriver(const Driver &driver, int index) {
    title("DATA DRIVER DITEMUKAN");

    cout << "Index       : " << index << '\n';
    cout << "Nama        : " << driver.name << '\n';
    cout << "Negara      : " << driver.nationality << '\n';
    cout << "Tahun Lahir : " << driver.birthYear << '\n';
    cout << "Umur        : " << getAge(driver) << '\n';
    cout << "Status      : " << driver.status << '\n';
}

// ================= SEARCH =================

int fibonacciSearchByName(Driver drivers[], int totalDrivers, const string &target) {
    string targetUpper = toUpperCase(target);

    int fib2 = 0;
    int fib1 = 1;
    int fib = fib1 + fib2;

    while (fib < totalDrivers) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1;

    while (fib > 1) {
        int i = offset + fib2;

        if (i >= totalDrivers) {
            i = totalDrivers - 1;
        }

        string current = toUpperCase(drivers[i].name);

        if (current < targetUpper) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (current > targetUpper) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && offset + 1 < totalDrivers &&
        toUpperCase(drivers[offset + 1].name) == targetUpper) {
        return offset + 1;
    }

    return -1;
}

int binarySearchByAge(Driver drivers[], int totalDrivers, int targetAge) {
    int left = 0;
    int right = totalDrivers - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int age = getAge(drivers[mid]);

        if (age == targetAge) {
            return mid;
        } else if (age < targetAge) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void linearSearchByBirthYear(Driver drivers[], int totalDrivers, int targetYear) {
    bool found = false;

    title("HASIL SEARCH TAHUN LAHIR");

    for (int i = 0; i < totalDrivers; i++) {
        if (drivers[i].birthYear == targetYear) {
            found = true;
            displayFoundDriver(drivers[i], i);
        }
    }

    if (!found) {
        throw F1Exception("Driver dengan tahun lahir tersebut tidak ditemukan!");
    }
}

// ================= USER =================

void registerUser(User users[], int &totalUsers) {
    if (totalUsers >= MAX_USERS) {
        throw F1Exception("Kapasitas user sudah penuh!");
    }

    string username = readText("Username baru : ");
    string password = readText("Password baru : ");

    users[totalUsers].username = username;
    users[totalUsers].password = password;

    totalUsers++;

    cout << "Registrasi berhasil!\n";
}

bool loginUser(User users[], int totalUsers) {
    string username = readText("Username : ");
    string password = readText("Password : ");

    for (int i = 0; i < totalUsers; i++) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login berhasil!\n";
            return true;
        }
    }

    throw F1Exception("Username atau password salah!");
}

// ================= MENU SORT DRIVER =================

void sortDriverMenu(Driver drivers[], int totalDrivers) {
    title("SORT DRIVER");

    cout << "1. Umur Descending        - Bubble Sort\n";
    cout << "2. Negara Ascending       - Quick Sort\n";
    cout << "3. Tahun Lahir Descending - Bubble Sort\n";
    cout << "4. Nama Ascending         - Radix Sort\n";

    int choice = readInt("Pilih sort : ", 1, 4);

    switch (choice) {
        case 1:
            bubbleSortAgeDesc(drivers, totalDrivers);
            break;
        case 2:
            quickSortNationalityAsc(drivers, 0, totalDrivers - 1);
            break;
        case 3:
            bubbleSortBirthYearDesc(drivers, totalDrivers);
            break;
        case 4:
            radixSortDriversByName(drivers, totalDrivers);
            break;
    }

    displayDrivers(drivers, totalDrivers);
}

// ================= MENU SORT KONTRAK =================

void sortContractMenu(Contract contracts[], int totalContracts, Driver drivers[], Team teams[]) {
    title("SORT KONTRAK");

    cout << "1. Nama Driver Ascending  - Radix Sort\n";
    cout << "2. Nama Team Ascending    - Radix Sort\n";
    cout << "3. Tahun Mulai Descending - Bubble Sort\n";
    cout << "4. Tahun Akhir Descending - Bubble Sort\n";
    cout << "5. Tahun Mulai Ascending  - Quick Sort\n";
    cout << "6. Tahun Akhir Ascending  - Quick Sort\n";

    int choice = readInt("Pilih sort : ", 1, 6);

    switch (choice) {
        case 1:
            radixSortContractsByDriverName(contracts, totalContracts, drivers);
            break;
        case 2:
            radixSortContractsByTeamName(contracts, totalContracts, teams);
            break;
        case 3:
            bubbleSortContractStartYearDesc(contracts, totalContracts);
            break;
        case 4:
            bubbleSortContractEndYearDesc(contracts, totalContracts);
            break;
        case 5:
            quickSortContractStartYearAsc(contracts, 0, totalContracts - 1);
            break;
        case 6:
            quickSortContractEndYearAsc(contracts, 0, totalContracts - 1);
            break;
    }

    cout << "\n1. Tampilkan semua kontrak\n";
    cout << "2. Tampilkan kontrak aktif 2026\n";

    int displayChoice = readInt("Pilih tampilan : ", 1, 2);

    if (displayChoice == 1) {
        displayContracts(contracts, totalContracts, drivers, teams);
    } else {
        displayActiveContracts2026(contracts, totalContracts, drivers, teams);
    }
}

// ================= MENU SEARCH DRIVER =================

void searchDriverMenu(Driver drivers[], int totalDrivers) {
    title("SEARCH DRIVER");

    cout << "1. Nama Driver - Fibonacci Search\n";
    cout << "2. Umur        - Binary Search\n";
    cout << "3. Tahun Lahir - Linear Search\n";

    int choice = readInt("Pilih search : ", 1, 3);

    if (choice == 1) {
        string target = readText("Masukkan nama driver : ");

        Driver temp[MAX_DRIVERS];

        for (int i = 0; i < totalDrivers; i++) {
            temp[i] = drivers[i];
        }

        radixSortDriversByName(temp, totalDrivers);

        int index = fibonacciSearchByName(temp, totalDrivers, target);

        if (index == -1) {
            throw F1Exception("Driver dengan nama tersebut tidak ditemukan!");
        }

        displayFoundDriver(temp[index], index);
    } else if (choice == 2) {
        int age = readInt("Masukkan umur : ", 1, 100);

        Driver temp[MAX_DRIVERS];

        for (int i = 0; i < totalDrivers; i++) {
            temp[i] = drivers[i];
        }

        quickSortAgeAsc(temp, 0, totalDrivers - 1);

        int index = binarySearchByAge(temp, totalDrivers, age);

        if (index == -1) {
            throw F1Exception("Driver dengan umur tersebut tidak ditemukan!");
        }

        displayFoundDriver(temp[index], index);
    } else if (choice == 3) {
        int year = readInt("Masukkan tahun lahir : ", 1900, CURRENT_YEAR);
        linearSearchByBirthYear(drivers, totalDrivers, year);
    }
}

// ================= CRUD DRIVER =================

void addDriver(Driver drivers[], int &totalDrivers) {
    if (totalDrivers >= MAX_DRIVERS) {
        throw F1Exception("Data driver sudah penuh!");
    }

    string name = readText("Nama driver : ");
    string country = readText("Negara      : ");
    int birthYear = readInt("Tahun lahir : ", 1900, CURRENT_YEAR);
    string status = readText("Status      : ");

    drivers[totalDrivers].name = name;
    drivers[totalDrivers].nationality = country;
    drivers[totalDrivers].birthYear = birthYear;
    drivers[totalDrivers].status = status;

    totalDrivers++;

    cout << "Driver berhasil ditambahkan!\n";
}

void editDriver(Driver drivers[], int totalDrivers) {
    if (totalDrivers == 0) {
        throw F1Exception("Tidak ada data driver untuk diedit!");
    }

    displayDrivers(drivers, totalDrivers);

    int choice = readInt("Pilih nomor driver yang diedit : ", 1, totalDrivers);
    int index = choice - 1;

    drivers[index].name = readText("Nama baru        : ");
    drivers[index].nationality = readText("Negara baru      : ");
    drivers[index].birthYear = readInt("Tahun lahir baru : ", 1900, CURRENT_YEAR);
    drivers[index].status = readText("Status baru      : ");

    cout << "Data driver berhasil diedit!\n";
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
        throw F1Exception("Tidak ada data driver untuk dihapus!");
    }

    displayDrivers(drivers, totalDrivers);

    int choice = readInt("Pilih nomor driver yang dihapus : ", 1, totalDrivers);
    int index = choice - 1;

    deleteDriverContracts(contracts, totalContracts, index);
    adjustContractDriverIndexes(contracts, totalContracts, index);

    for (int i = index; i < totalDrivers - 1; i++) {
        drivers[i] = drivers[i + 1];
    }

    totalDrivers--;

    cout << "Driver berhasil dihapus!\n";
}

// ================= KONTRAK =================

void addContract(Driver drivers[], int totalDrivers,
                 Team teams[], int totalTeams,
                 Contract contracts[], int &totalContracts) {
    if (totalContracts >= MAX_CONTRACTS) {
        throw F1Exception("Data kontrak sudah penuh!");
    }

    if (totalDrivers == 0) {
        throw F1Exception("Tidak ada driver yang tersedia!");
    }

    if (totalTeams == 0) {
        throw F1Exception("Tidak ada team yang tersedia!");
    }

    displayDrivers(drivers, totalDrivers);
    int driverChoice = readInt("Pilih driver : ", 1, totalDrivers);

    displayTeams(teams, totalTeams);
    int teamChoice = readInt("Pilih team   : ", 1, totalTeams);

    int startYear = readInt("Tahun mulai   : ", 2000, 2100);
    int endYear = readInt("Tahun selesai : ", startYear, 2100);

    contracts[totalContracts].driverIndex = driverChoice - 1;
    contracts[totalContracts].teamIndex = teamChoice - 1;
    contracts[totalContracts].startYear = startYear;
    contracts[totalContracts].endYear = endYear;

    totalContracts++;

    drivers[driverChoice - 1].status = "Aktif";

    cout << "Kontrak berhasil ditambahkan!\n";
}

// ================= MENU ADMIN =================

void adminMenu(Driver drivers[], int &totalDrivers,
               Team teams[], int totalTeams,
               Contract contracts[], int &totalContracts) {
    int choice = 0;

    do {
        try {
            title("MENU ADMIN - F1 MANAGEMENT SYSTEM");

            cout << "1. List Driver\n";
            cout << "2. Search Driver\n";
            cout << "3. Tambah Driver\n";
            cout << "4. Edit Driver\n";
            cout << "5. Hapus Driver\n";
            cout << "6. List Kontrak\n";
            cout << "7. Tambah / Transfer Kontrak\n";
            cout << "8. Logout\n";

            choice = readInt("Pilih menu : ", 1, 8);

            switch (choice) {
                case 1:
                    sortDriverMenu(drivers, totalDrivers);
                    break;
                case 2:
                    searchDriverMenu(drivers, totalDrivers);
                    break;
                case 3:
                    addDriver(drivers, totalDrivers);
                    break;
                case 4:
                    editDriver(drivers, totalDrivers);
                    break;
                case 5:
                    deleteDriver(drivers, totalDrivers, contracts, totalContracts);
                    break;
                case 6:
                    if (totalContracts == 0) {
                        throw F1Exception("Tidak ada data kontrak!");
                    }
                    sortContractMenu(contracts, totalContracts, drivers, teams);
                    break;
                case 7:
                    addContract(drivers, totalDrivers, teams, totalTeams, contracts, totalContracts);
                    break;
                case 8:
                    cout << "Logout berhasil.\n";
                    break;
            }
        } catch (const F1Exception &error) {
            cout << "\nERROR: " << error.what() << '\n';
        } catch (const exception &error) {
            cout << "\nSYSTEM ERROR: " << error.what() << '\n';
        }

    } while (choice != 8);
}

// ================= MAIN =================

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

    int choice = 0;

    do {
        try {
            title("WELCOME TO F1 MANAGEMENT SYSTEM");

            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Keluar\n";

            choice = readInt("Pilih menu : ", 1, 3);

            if (choice == 1) {
                registerUser(users, totalUsers);
            } else if (choice == 2) {
                if (loginUser(users, totalUsers)) {
                    adminMenu(drivers, totalDrivers, teams, totalTeams, contracts, totalContracts);
                }
            } else if (choice == 3) {
                cout << "\nProgram selesai. Terima kasih!\n";
            }
        } catch (const F1Exception &error) {
            cout << "\nERROR: " << error.what() << '\n';
        } catch (const exception &error) {
            cout << "\nSYSTEM ERROR: " << error.what() << '\n';
        }

    } while (choice != 3);

    return 0;
}