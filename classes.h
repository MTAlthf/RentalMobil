#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Car {
public:
    int id;
    string licensePlate;
    string model;
    string category;
    bool available;
    string startDate;
    string endDate;

    Car(int id, string plate, string model, string category, bool available);
};

class Customer {
public:
    string fullName;
    string phoneNumber;
    string address;
    string idNumber; // KTP
    string userId;
    string password;

    Customer(string fullName, string phoneNumber, string address, string idNumber, string userId, string password);
};

class Booking {
public:
    string customerName;
    int carId;
    string startDate;
    string endDate;
    bool paymentStatus;
    bool returned;

    Booking(string customer, int carId, string start, string end);
};

extern vector<Car> cars;
extern vector<Customer> customers;
extern vector<Booking> bookings;

void registerCustomer();
bool loginCustomer(string& currentCustomer);
void showAllCars();
void bookCar(string customer);
void viewBookings(string customer);
void paymentMenu(string customer);
void returnCar(string customer);
void cancelBooking(string customer);
void menuUtama(string currentCustomer);

#endif
