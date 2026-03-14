#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <string>
using namespace std;

class Library;         // Forward declaration for Library interactions

// --------------------- Base User Class ---------------------
class User
{
protected:

    int userID;
    string type;       // Stores derived class type: "student", "teacher", "staff", "premium", "admin"
    string username;
    string password;
    string name;
    string address;
    double balance;

public:
    // ---------- Constructors ----------
    User()
    {
        userID = 0;
        type = "unknown";
        username = "Unknown";
        password = "123";
        name = "Unknown";
        address = "Unknown";
        balance = 0.0;
    }

    User(int ID, string type, string username, string password,
         string name, string address, double balance)
    {
        userID = ID;
        this->type = type;
        this->username = username;
        this->password = password;
        this->name = name;
        this->address = address;
        this->balance = balance;
    }

    // ---------- Getters ----------
    int getUserID() const { return userID; }
    string getType() const { return type; }
    string getUsername() const { return username; }
    string getName() const { return name; }
    double getBalance() const { return balance; }

    // ---------- Setters ----------
    void setAddress(const string &addr) { address = addr; }
    void setPassword(const string &pass) { password = pass; }
    void updateBalance(double amount) { balance += amount; } // Positive or negative

    // ---------- Authentication ----------
    bool login(string user, string pass) { return (username == user && password == pass); }

    // ---------- Role-based Borrowing ----------
    virtual int getDailyLimit() const = 0;  // Max resources per day
    virtual double getFineRate() const = 0; // Fine per overdue day

    // ---------- Library Interaction ----------
    bool borrowResource(Library &lib, int resourceID); // Borrow resource via library
    bool returnResource(Library &lib, int resourceID); // Return resource via library

    // ---------- Display ----------
    virtual void displayInfo() const = 0;

    virtual ~User() {}
};

// --------------------- Student Class ---------------------
class Student : public User
{
    string department;
    int rollNo;

public:
    // ---------- Constructors ----------
    Student() : User()
    {
        type = "student";
        department = "Unknown";
        rollNo = 0;
    }

    Student(int ID, string username, string password,
            string name, string address, double balance,
            string department, int rollNo)
        : User(ID, "student", username, password, name, address, balance)
    {
        this->department = department;
        this->rollNo = rollNo;
    }

    // ---------- Role Rules ----------
    int getDailyLimit() const override { return 2; }     // Max 2 resources/day
    double getFineRate() const override { return 10.0; } // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override
    {
        cout << "ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Role: Student" << endl;
        cout << "Department: " << department << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "Balance: " << balance << endl;
    }
};

// --------------------- Teacher Class ---------------------
class Teacher : public User
{
    string department;
    string designation;

public:
    // ---------- Constructors ----------
    Teacher() : User()
    {
        type = "teacher";
        department = "Unknown";
        designation = "Unknown";
    }

    Teacher(int ID, string username, string password,
            string name, string address, double balance,
            string department, string designation)
        : User(ID, "teacher", username, password, name, address, balance)
    {
        this->department = department;
        this->designation = designation;
    }

    // ---------- Role Rules ----------
    int getDailyLimit() const override { return 3; }     // Max 3 resources/day
    double getFineRate() const override { return 20.0; } // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override
    {
        cout << "ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Role: Teacher" << endl;
        cout << "Department: " << department << endl;
        cout << "Designation: " << designation << endl;
        cout << "Balance: " << balance << endl;
    }
};

// --------------------- Staff Class ---------------------
class Staff : public User
{
    string position;

public:
    // ---------- Constructors ----------
    Staff() : User() 
    { 
        type = "staff";
        position = "Unknown"; 
    }

    Staff(int ID, string username, string password,
          string name, string address, double balance,
          string position)
        : User(ID, "staff", username, password, name, address, balance)
    {
        this->position = position;
    }

    // ---------- Role Rules ----------
    int getDailyLimit() const override { return 4; }    // Max 4 resources/day
    double getFineRate() const override { return 5.0; } // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override
    {
        cout << "ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Role: Staff" << endl;
        cout << "Position: " << position << endl;
        cout << "Balance: " << balance << endl;
    }
};

// --------------------- Premium Member Class ---------------------
class PremiumMember : public User
{
    string membershipLevel;

public:
    // ---------- Constructors ----------
    PremiumMember() : User() 
    { 
        type = "premium";
        membershipLevel = "Gold"; 
    }

    PremiumMember(int ID, string username, string password,
                  string name, string address, double balance,
                  string level)
        : User(ID, "premium", username, password, name, address, balance)
    {
        membershipLevel = level;
    }

    // ---------- Role Rules ----------
    int getDailyLimit() const override { return 5; }    // Max 5 resources/day
    double getFineRate() const override { return 3.0; } // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override
    {
        cout << "ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Role: Premium Member" << endl;
        cout << "Membership Level: " << membershipLevel << endl;
        cout << "Balance: " << balance << endl;
    }
};

#endif