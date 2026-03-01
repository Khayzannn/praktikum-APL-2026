#include <iostream>
#include <string>
using namespace std;

void menu() {
    int pilihan;

    do {
        cout << "====================================\n";
        cout << "          MENU KONVERSI WAKTU       \n";
        cout << "====================================\n";
        cout << "[1] Jam ke Menit dan Detik\n";
        cout << "[2] Menit ke Jam dan Detik\n";
        cout << "[3] Detik ke Jam dan Menit\n";
        cout << "[4] Keluar\n";
        cout << "====================================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int jamInput;
                cout << "Masukkan jumlah jam: ";
                cin >> jamInput;
                int menit = jamInput * 60;
                int detik = jamInput * 3600;
                cout << jamInput << " jam = " << menit << " menit dan " << detik << " detik\n\n";
                break;
            }
            case 2: {
                int menitInput;
                cout << "Masukkan jumlah menit: ";
                cin >> menitInput;
                int jam = menitInput / 60;
                int detik = menitInput * 60;
                cout << menitInput << " menit = " << jam << " jam dan " << detik << " detik\n\n";
                break;
            }
            case 3: {
                int detikInput;
                cout << "Masukkan jumlah detik: ";
                cin >> detikInput;
                int jam = detikInput / 3600;
                int sisaDetik = detikInput % 3600;
                int menit = sisaDetik / 60;
                cout << detikInput << " detik = " << jam << " jam dan " << menit << " menit\n\n";
                break;
            }
            case 4:
                cout << "Terima kasih telah menggunakan program ini\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n\n";
        }
    } while (pilihan != 4);
}

int main() {
    const string username = "Attala";
    const string password = "103";
    string usernameInput, passwordInput;
    int percobaan = 0;
    int maxPercobaan = 3;

    while (percobaan < maxPercobaan) {
        cout << "Masukkan username: ";
        getline(cin, usernameInput);  
        cout << "Masukkan password: ";
        getline(cin, passwordInput);

        if (usernameInput == username && passwordInput == password) {
            cout << "Login berhasil! Selamat datang, " << username << "!" << endl << endl;
            menu();
            break;
        } else {
            percobaan++;
            cout << "Login gagal! Percobaan ke-" << percobaan << endl << endl;
            if (percobaan == maxPercobaan) {
                cout << "Anda telah mencapai batas percobaan. Program keluar." << endl;
            }
        }
    }

    return 0;
}
