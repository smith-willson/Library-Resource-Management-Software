#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <string>
using namespace std;

class Library; // Forward declaration for Library interactions

// --------------------- Base User Class ---------------------
class User
{
protected:
    int userID;
    string type;      // Stores derived class type: "student", "teacher", "staff", "premium"
    string username;
    string password;
    string name;
    string address;
    double balance;

public:
    // ---------- Constructors ----------
    User();
    User(int ID, string type, string username, string password,
         string name, string address, double balance);

    // ---------- Getters ----------
    int getUserID() const;
    string getType() const;
    string getUsername() const;
    string getName() const;
    double getBalance() const;
    string getAddress() const;
    string getPassword() const;

    // ---------- Setters ----------
    void setAddress(const string &addr);
    void setPassword(const string &pass);
    void updateBalance(double amount); // Positive or negative

    // ---------- Authentication ----------
    bool login(string user, string pass);

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
    Student();
    Student(int ID, string username, string password,
            string name, string address, double balance,
            string department, int rollNo);

    // ---------- Getters ----------
    string getDepartment() const;
    int getRollNo() const;

    // ---------- Role Rules ----------
    int getDailyLimit() const override;  // Max 2 resources/day
    double getFineRate() const override; // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override;
};

// --------------------- Teacher Class ---------------------
class Teacher : public User
{
    string department;
    string designation;

public:
    // ---------- Constructors ----------
    Teacher();
    Teacher(int ID, string username, string password,
            string name, string address, double balance,
            string department, string designation);

    // ---------- Getters ----------
    string getDepartment() const;
    string getDesignation() const;

    // ---------- Role Rules ----------
    int getDailyLimit() const override;  // Max 3 resources/day
    double getFineRate() const override; // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override;
};

// --------------------- Staff Class ---------------------
class Staff : public User
{
    string position;

public:
    // ---------- Constructors ----------
    Staff();
    Staff(int ID, string username, string password,
          string name, string address, double balance,
          string position);

    // ---------- Getters ----------
    string getPosition() const;

    // ---------- Role Rules ----------
    int getDailyLimit() const override;  // Max 4 resources/day
    double getFineRate() const override; // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override;
};

// --------------------- Premium Member Class ---------------------
class PremiumMember : public User
{
    string membershipLevel;

public:
    // ---------- Constructors ----------
    PremiumMember();
    PremiumMember(int ID, string username, string password,
                  string name, string address, double balance,
                  string level);

    // ---------- Getters ----------
    string getMembershipLevel() const;

    // ---------- Role Rules ----------
    int getDailyLimit() const override;  // Max 5 resources/day
    double getFineRate() const override; // Fine per overdue day

    // ---------- Display ----------
    void displayInfo() const override;
};

#endif