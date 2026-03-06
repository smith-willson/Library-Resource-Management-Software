#ifndef USERS_H
#define USERS_H

#include <string>
#include <ctime>
#include "Resources.h"

using namespace std;

// ---------------- Base User ----------------
class User {
protected:
    string username, password;
    string firstName, lastName, address;
    double balance;
    int maxBorrowLimit;
    string borrowedResources[10];

    struct BorrowingHistory {
        string resource;
        string borrowDate;
        string returnDate;
        string dueDate;
        time_t dueDateRaw;
    } borrowingHistory[10];

public:
    User() : balance(0.0), maxBorrowLimit(2) {}
    User(string user, string pass, double bal, string fname, string lname, string addr)
        : username(user), password(pass), balance(bal), firstName(fname), lastName(lname), address(addr) {}

    virtual ~User() {}
    string getUsername() const { return username; }
    double getBalance() const { return balance; }
    void setBalance(double b) { balance = b; }

    virtual void borrowResource(LibraryResource* r) = 0;
    virtual void returnResource(LibraryResource* r) = 0;
    virtual void displayInfo() = 0;

    virtual double getFineRate() const = 0;
    virtual int getBorrowLimit() const = 0;
    virtual int getBorrowDuration() const = 0;

    BorrowingHistory* getBorrowHistory() { return borrowingHistory; }
    string* getBorrowedResources() { return borrowedResources; }
};

// ---------------- Student ----------------
class Student : public User {
    int rollNo;
    string department;
    int batch;

public:
    Student(string user, string pass, double bal, string fname, string lname, string addr,
            int roll, string dept, int b)
        : User(user, pass, bal, fname, lname, addr), rollNo(roll), department(dept), batch(b) { maxBorrowLimit = 2; }

    int getBorrowLimit() const override { return maxBorrowLimit; }
    int getBorrowDuration() const override { return 14; }
    double getFineRate() const override { return 5.0; }

    void borrowResource(LibraryResource* r) override;
    void returnResource(LibraryResource* r) override;
    void displayInfo() override;
};

// ---------------- Teacher ----------------
class Teacher : public User {
    int employeeID;
    string department, designation;

public:
    Teacher(string user, string pass, double bal, string fname, string lname, string addr,
            int id, string dept, string desig)
        : User(user, pass, bal, fname, lname, addr), employeeID(id), department(dept), designation(desig) { maxBorrowLimit = 5; }

    int getBorrowLimit() const override { return maxBorrowLimit; }
    int getBorrowDuration() const override { return 30; }
    double getFineRate() const override { return 2.0; }

    void borrowResource(LibraryResource* r) override;
    void returnResource(LibraryResource* r) override;
    void displayInfo() override;
};

// ---------------- Staff ----------------
class Staff : public User {
    int staffID;
    string department, position;

public:
    Staff(string user, string pass, double bal, string fname, string lname, string addr,
          int id, string dept, string pos)
        : User(user, pass, bal, fname, lname, addr), staffID(id), department(dept), position(pos) { maxBorrowLimit = 3; }

    int getBorrowLimit() const override { return maxBorrowLimit; }
    int getBorrowDuration() const override { return 21; }
    double getFineRate() const override { return 3.0; }

    void borrowResource(LibraryResource* r) override;
    void returnResource(LibraryResource* r) override;
    void displayInfo() override;
};

// ---------------- Admin ----------------
class Admin : public User {
    int adminID;

public:
    Admin(string user, string pass, double bal, string fname, string lname, string addr, int id)
        : User(user, pass, bal, fname, lname, addr), adminID(id) { maxBorrowLimit = 0; }

    int getBorrowLimit() const override { return 0; }
    int getBorrowDuration() const override { return 0; }
    double getFineRate() const override { return 0; }

    void borrowResource(LibraryResource* r) override {}
    void returnResource(LibraryResource* r) override {}
    void displayInfo() override;
};

#endif // USERS_H