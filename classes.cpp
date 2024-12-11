#include "classes.h"

Car::Car(int id, string plate, string model, string category, bool available)
    : id(id), licensePlate(plate), model(model), category(category), available(available), startDate(""), endDate("") {}

Customer::Customer(string fullName, string phoneNumber, string address, string idNumber, string userId, string password)
    : fullName(fullName), phoneNumber(phoneNumber), address(address), idNumber(idNumber), userId(userId), password(password) {}

Booking::Booking(string customer, int carId, string start, string end)
    : customerName(customer), carId(carId), startDate(start), endDate(end), paymentStatus(false), returned(false) {}

vector<Car> cars = {
    Car(1, "SUV001", "Toyota Fortuner", "SUV", true),
    Car(2, "SUV002", "Honda CR-V", "SUV", true),
    Car(3, "SUV003", "Mitsubishi Pajero Sport", "SUV", true),
    Car(4, "SED001", "Toyota Camry", "Sedan", false), 
    Car(5, "SED002", "Honda Accord", "Sedan", true),
    Car(6, "SED003", "BMW 3 Series", "Sedan", false), 
    Car(7, "HAT001", "Toyota Yaris", "Hatchback", true),
    Car(8, "HAT002", "Honda Jazz", "Hatchback", true),
    Car(9, "ELEC001", "Tesla Model 3", "Listrik", true),
    Car(10, "SED004", "Mazda 6", "Sedan", true),
    Car(11, "SUV004", "Ford Everest", "SUV", true),
    Car(12, "SUV005", "Isuzu MU-X", "SUV", true),
    Car(13, "HAT003", "Suzuki Swift", "Hatchback", true),
    Car(14, "SED005", "Mercedes-Benz E-Class", "Sedan", true),
    Car(15, "SED006", "Audi A6", "Sedan", true)
};

vector<Customer> customers;
vector<Booking> bookings;

void registerCustomer() {
    string fullName, phoneNumber, address, idNumber, userId, password;
    char agreement;

    cout << "=== Registrasi Akun ===\n";
    cout << "Masukkan Nama Lengkap: ";
    cin.ignore(); 
    getline(cin, fullName);
    cout << "Masukkan Nomor Telepon: ";
    getline(cin, phoneNumber);
    cout << "Masukkan Alamat: ";
    getline(cin, address);
    cout << "Masukkan Nomor KTP: ";
    getline(cin, idNumber);

    cout << "Apakah Anda menyetujui untuk memberikan data ini? (y/n): ";
    cin >> agreement;

    if (agreement != 'y' && agreement != 'Y') {
        cout << "Registrasi dibatalkan.\n";
        return;
    }

    cout << "Buat User ID: ";
    cin >> userId;
    cout << "Buat Password: ";
    cin >> password;

    customers.emplace_back(fullName, phoneNumber, address, idNumber, userId, password);
    cout << "Registrasi berhasil! Silakan login menggunakan User ID Anda.\n";
}

bool loginCustomer(string& currentCustomer) {
    string userId, password;
    cout << "Masukkan User ID: ";
    cin >> userId;
    cout << "Masukkan Password: ";
    cin >> password;

    for (auto& customer : customers) {
        if (customer.userId == userId && customer.password == password) {
            currentCustomer = customer.fullName;
            return true;
        }
    }

    cout << "User ID atau Password salah. Silakan coba lagi.\n";
    return false;
}

void showAllCars() {
    cout << "Daftar Semua Mobil:\n";
    int index = 1;
    for (auto& car : cars) {
        cout << index++ << ". " << car.model 
             << " (ID: " << car.id 
             << ", Plat: " << car.licensePlate 
             << ", Tersedia: " << (car.available ? "Ya" : "Tidak") << ")\n";
    }
}

void bookCar(string customer) {
    showAllCars();

    int choice;
    cout << "Pilih ID mobil yang ingin dipesan: ";
    cin >> choice;

    int carIndex = -1;
    for (size_t i = 0; i < cars.size(); ++i) {
        if (cars[i].id == choice) {
            carIndex = i;
            break;
        }
    }

    if (carIndex == -1 || !cars[carIndex].available) {
        cout << "Mobil tidak tersedia atau pilihan tidak valid.\n";
        return;
    }

    cout << "\nDetail Mobil yang Anda Pilih:\n";
    cout << "Model: " << cars[carIndex].model << "\n";
    cout << "Kategori: " << cars[carIndex].category << "\n";
    cout << "Harga Sewa: Rp 500,000 per hari\n";
    cout << "Kapasitas: 5 orang\n";
    cout << "Fitur: AC, Power Steering, Audio System, Airbag\n";

    char confirmation;
    cout << "Apakah Anda ingin memesan mobil ini? (y/n): ";
    cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y') {
        string startDate, endDate;
        cout << "Masukkan tanggal mulai (YYYY-MM-DD): ";
        cin >> startDate;
        cout << "Masukkan tanggal akhir (YYYY-MM-DD): ";
        cin >> endDate;

        cars[carIndex].available = false;
        bookings.emplace_back(customer, cars[carIndex].id, startDate, endDate);
        cout << "Mobil berhasil dipesan!\n";
    } else {
        cout << "Kembali ke menu daftar mobil.\n";
    }
}

void viewBookings(string customer) {
    cout << "\n=== Data Pemesanan ===\n";
    bool found = false;
    for (auto& booking : bookings) {
        if (booking.customerName == customer) {
            found = true;
            cout << "Mobil: " << cars[booking.carId - 1].model << "\n";
            cout << "ID Mobil: " << booking.carId << "\n";
            cout << "Tanggal Mulai: " << booking.startDate << "\n";
            cout << "Tanggal Akhir: " << booking.endDate << "\n";
            cout << "Status Pembayaran: " << (booking.paymentStatus ? "Sudah Dibayar" : "Belum Dibayar") << "\n";
            cout << "Status Pengembalian: " << (booking.returned ? "Sudah Dikembalikan" : "Belum Dikembalikan") << "\n";
            cout << "---------------------------------\n";
        }
    }

    if (!found) {
        cout << "Tidak ada data pemesanan.\n";
    }

    cout << "1. Kembali ke menu sebelumnya\n";
    int backOption;
    cin >> backOption;
}
void paymentMenu(string customer) {
    cout << "\n=== Menu Pembayaran ===\n";
    bool hasUnpaidBookings = false;

    for (auto& booking : bookings) {
        if (booking.customerName == customer && !booking.paymentStatus) {
            hasUnpaidBookings = true;
            break;
        }
    }

    if (!hasUnpaidBookings) {
        cout << "Tidak ada pemesanan yang perlu dibayar.\n";
        return;
    }

    cout << "Daftar Mobil yang Belum Dibayar:\n";
    int index = 1;
    int totalAmount = 0;
    for (auto& booking : bookings) {
                if (booking.customerName == customer && !booking.paymentStatus) {
            cout << index++ << ". " << cars[booking.carId - 1].model 
                 << " (Tanggal Mulai: " << booking.startDate
                 << ", Tanggal Akhir: " << booking.endDate << ")\n";
            totalAmount += 500000; 
        }
    }

    cout << "Jumlah yang harus dibayar: Rp " << totalAmount << endl;
    cout << "Rekening Admin:\n";
    cout << " - BNI: 123-456-789\n";
    cout << " - BRI: 987-654-321\n";
    cout << " - Mandiri: 555-666-777\n";

    cout << "Apakah Anda ingin melakukan pembayaran? (y/n): ";
    char paymentChoice;
    cin >> paymentChoice;

    if (paymentChoice == 'y' || paymentChoice == 'Y') {
        cout << "Pilih metode pembayaran:\n";
        cout << "1. BNI\n";
        cout << "2. BRI\n";
        cout << "3. Mandiri\n";
        int paymentMethod;
        cin >> paymentMethod;
        cout << "Pembayaran berhasil!\n";

        for (auto& booking : bookings) {
            if (booking.customerName == customer && !booking.paymentStatus) {
                booking.paymentStatus = true;
            }
        }
    }
}

void returnCar(string customer) {
    cout << "\n=== Menu Pengembalian Mobil ===\n";
    bool hasBookings = false;

    for (auto& booking : bookings) {
        if (booking.customerName == customer && !booking.returned) {
            hasBookings = true;
            cout << "Mobil: " << cars[booking.carId - 1].model 
                 << " (ID Mobil: " << booking.carId 
                 << ", Tanggal Mulai: " << booking.startDate
                 << ", Tanggal Akhir: " << booking.endDate << ")\n";
        }
    }

    if (!hasBookings) {
        cout << "Tidak ada mobil yang perlu dikembalikan.\n";
        return;
    }

    cout << "Masukkan ID mobil yang ingin dikembalikan: ";
    int carId;
    cin >> carId;

    bool carFound = false;

    for (auto& booking : bookings) {
        if (booking.customerName == customer && booking.carId == carId && !booking.returned) {
            booking.returned = true;
            carFound = true;
            for (auto& car : cars) {
                if (car.id == carId) {
                    car.available = true;
                    cout << "Mobil berhasil dikembalikan!\n";
                    break;
                }
            }
            break;
        }
    }

    if (!carFound) {
        cout << "Mobil tidak ditemukan atau sudah dikembalikan.\n";
    }
}

void cancelBooking(string customer) {
    cout << "\n=== Menu Pembatalan Pemesanan ===\n";
    bool hasBookings = false;

    for (auto& booking : bookings) {
        if (booking.customerName == customer && !booking.paymentStatus) {
            hasBookings = true;
            cout << "Mobil: " << cars[booking.carId - 1].model 
                 << " (ID Mobil: " << booking.carId 
                 << ", Tanggal Mulai: " << booking.startDate
                 << ", Tanggal Akhir: " << booking.endDate << ")\n";
        }
    }

    if (!hasBookings) {
        cout << "Tidak ada pemesanan yang perlu dibatalkan.\n";
        return;
    }

    cout << "Masukkan ID mobil yang ingin dibatalkan: ";
    int carId;
    cin >> carId;

    bool bookingFound = false;

    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if (it->customerName == customer && it->carId == carId && !it->paymentStatus) {
            bookingFound = true;
            for (auto& car : cars) {
                if (car.id == carId) {
                    car.available = true;
                    bookings.erase(it);
                    cout << "Pemesanan berhasil dibatalkan!\n";
                    return;
                }
            }
        }
    }

    if (!bookingFound) {
        cout << "Mobil tidak ditemukan atau pemesanan sudah dibatalkan.\n";
    }
}
