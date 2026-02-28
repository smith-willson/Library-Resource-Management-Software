#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <vector>
#include "Resources.h"
#include "Users.h"
using namespace std;

class Admin
{
private:
    string password;

protected:
    int adminID;
    string username;
    string name;
    static int idCounter; // shared counter to auto-generate unique IDs

public:
    // default constructor
    Admin() : adminID(++idCounter), username(""), password(""), name("") {}

    // parameterized constructor
    Admin(string name, string username, string password)
    {
        this->name = name;
        this->username = username;
        this->password = password;
        adminID = ++idCounter;
    }

    // getters
    int getAdminID() const { return adminID; }
    string getUsername() const { return username; }
    string getName() const { return name; }

    // setters
    void setName(string n) { name = n; }
    void setUsername(string u) { username = u; }
    void setPassword(string p) { password = p; }

    bool login(string user, string pass)
    {
        return (username == user && password == pass);
    }

    // print report of all customers and their borrowing history
    void printAllCustomersReport(vector<User *> &users);

    // add, update, remove resources
    void addResource(vector<LibraryResource *> &resources);
    void removeResource(vector<LibraryResource *> &resources);
    void updateResource(vector<LibraryResource *> &resources);

    // print currently issued and overdue resources
    void printIssuedResources(vector<LibraryResource *> &resources);
    void printOverdueResources(vector<LibraryResource *> &resources);
};

int Admin::idCounter = 0;

#endif // ADMIN_H