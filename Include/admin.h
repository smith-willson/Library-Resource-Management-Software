#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <vector>
#include "Users.h"
using namespace std;

class LibraryResource; // Forward declaration for resource operations

// --------------------- Admin Class ---------------------
class Admin : public User
{
public:
    // ---------- Constructors ----------
    Admin();
    Admin(int ID, string username, string password,
          string name, string address, double balance);

    // ---------- Role Rules ----------
    int getDailyLimit() const override;    // Admin does not borrow
    double getFineRate() const override;   // No fines for admin

    // ---------- Admin Operations ----------
    void printAllCustomersReport(vector<User *> &users);              // Report of all users and history
    void addResource(vector<LibraryResource *> &resources);           // Add new resource
    void removeResource(vector<LibraryResource *> &resources);        // Remove existing resource
    void updateResource(vector<LibraryResource *> &resources);        // Update resource details
    void printIssuedResources(vector<LibraryResource *> &resources);  // Currently issued
    void printOverdueResources(vector<LibraryResource *> &resources); // Overdue resources

    // ---------- Display ----------
    void displayInfo() const override;
};

#endif