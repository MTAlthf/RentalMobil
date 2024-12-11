#include "classes.h"

void menuUtama(string currentCustomer) {
    int choice;
    while (true) {
        cout << "\n=== Menu Utama ===\n";
        cout << "1. Pesan Mobil\n";
        cout << "2. Lihat Pemesanan\n";
        cout << "3. Menu Pembayaran\n";
        cout << "4. Pengembalian Mobil\n";
        cout << "5. Pembatalan Pemesanan\n";
        cout << "6. Logout\n";
        cout << "Pilih menu: ";
        cin >> choice;

        if (choice == 1) {
            bookCar(currentCustomer);
        } else if (choice == 2) {
            viewBookings(currentCustomer);
        } else if (choice == 3) {
            paymentMenu(currentCustomer);
        } else if (choice == 4) {
            returnCar(currentCustomer);
        } else if (choice == 5) {
            cancelBooking(currentCustomer);
        } else if (choice == 6) {
            cout << "Logout berhasil!\n";
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

int main() {
    string currentCustomer;

    while (true) {
        int choice;
        cout << "=== Menu ===\n";
        cout << "1. Registrasi\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Pilih menu: ";
        cin >> choice;

        if (choice == 1) {
            registerCustomer();
        } else if (choice == 2) {
            if (loginCustomer(currentCustomer)) {
                cout << "Selamat datang, " << currentCustomer << "!\n";
                menuUtama(currentCustomer);
            }
        } else if (choice == 3) {
            cout << "Terima kasih telah menggunakan layanan kami. Sampai jumpa!\n";
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
