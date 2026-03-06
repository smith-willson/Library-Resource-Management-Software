#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <vector>
#include "Resources.h"
#include "Users.h"

using namespace std;

// Administrative manager class for handling reports and resource management.
// Renamed to avoid clashing with the user-role Admin defined in Users.h.
class AdminManager
{
private:
    string password;

protected:
    int adminID;
    string username;
    string name;

    static int idCounter;

public:
    AdminManager();

    AdminManager(string name, string username, string password);

    int getAdminID() const;
    string getUsername() const;
    string getName() const;

    void setName(string n);
    void setUsername(string u);
    void setPassword(string p);

    bool login(string user, string pass);

    void printAllCustomersReport(vector<User*> &users);

    void addResource(vector<LibraryResource*> &resources);
    void removeResource(vector<LibraryResource*> &resources);
    void updateResource(vector<LibraryResource*> &resources);

    void printIssuedResources(vector<LibraryResource*> &resources);
    void printOverdueResources(vector<LibraryResource*> &resources);
};

#endif