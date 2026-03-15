#include "admin.h"
#include "resources.h"
#include <iostream>
using namespace std;

// ---------- Constructors ----------
Admin::Admin() : User()
{
    type = "admin";
}

Admin::Admin(int ID, string username, string password,
             string name, string address, double balance)
    : User(ID, "admin", username, password, name, address, balance)
{
}

// ---------- Role Rules ----------
int Admin::getDailyLimit() const { return 0; }    // Admin does not borrow
double Admin::getFineRate() const { return 0.0; } // No fines for admin

// ---------- Admin Operations ----------
void Admin::printAllCustomersReport(vector<User *> &users)
{
    // TODO: implement
}

void Admin::addResource(vector<LibraryResource *> &resources)
{
    // TODO: implement
}

void Admin::removeResource(vector<LibraryResource *> &resources)
{
    // TODO: implement
}

void Admin::updateResource(vector<LibraryResource *> &resources)
{
    // TODO: implement
}

void Admin::printIssuedResources(vector<LibraryResource *> &resources)
{
    // TODO: implement
}

void Admin::printOverdueResources(vector<LibraryResource *> &resources)
{
    // TODO: implement
}

// ---------- Display ----------
void Admin::displayInfo() const
{
    cout << "ID: " << userID << endl;
    cout << "Name: " << name << endl;
    cout << "Role: Admin" << endl;
}