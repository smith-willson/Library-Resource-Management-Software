#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <vector>
#include "users.h"
using namespace std;

class LibraryResource; // Forward declaration for resource operations

// --------------------- Admin Class ---------------------
class Admin : public User
{
    string department;

public:
    // ---------- Constructors ----------
    Admin() : User()
    {
        type = "admin";
        department = "Unknown";
    }

    Admin(int ID, string username, string password,
          string name, string address, double balance,
          string department)
        : User(ID, "admin", username, password, name, address, balance)
    {
        this->department = department;
    }

    // ---------- Role Rules ----------
    int getDailyLimit() const override { return 0; }    // Admin does not borrow
    double getFineRate() const override { return 0.0; } // No fines for admin

    // ---------- Admin Operations ----------
    void printAllCustomersReport(vector<User *> &users);          // Report of all users and history
    void addResource(vector<LibraryResource *> &resources);       // Add new resource
    void removeResource(vector<LibraryResource *> &resources);    // Remove existing resource
    void updateResource(vector<LibraryResource *> &resources);    // Update resource details
    void printIssuedResources(vector<LibraryResource *> &resources);  // Currently issued
    void printOverdueResources(vector<LibraryResource *> &resources); // Overdue resources

    // ---------- Display ----------
    void displayInfo() const override
    {
        cout << "ID: " << userID << endl;
        cout << "Name: " << name << endl;
        cout << "Role: Admin" << endl;
        cout << "Department: " << department << endl;
    }
};

#endif