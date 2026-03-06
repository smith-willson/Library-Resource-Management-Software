#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <string>
#include "Users.h"
#include "Resources.h"
#include "sqlite3.h"

using namespace std;

struct BorrowRecord {
    LibraryResource* resource;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
    double fine;

    BorrowRecord(LibraryResource* res, int durationDays)
        : resource(res), fine(0), returnDate(0) {
        borrowDate = time(0);
        dueDate = borrowDate + durationDays * 24 * 60 * 60;
    }

    void markReturned(User* user) {
        returnDate = time(0);
        if(difftime(returnDate, dueDate) > 0)
            fine = difftime(returnDate, dueDate)/(60*60*24) * user->getFineRate();
    }
};

class Library {
    string libraryName;
    sqlite3* db;
    vector<User*> users;
    vector<LibraryResource*> resources;
    vector<BorrowRecord> borrowHistory;

public:
    Library(string name, sqlite3* database) : libraryName(name), db(database) {}

    void addUser(User* user) { users.push_back(user); cout << "Added user: " << user->getUsername() << endl; }
    void addResource(LibraryResource* res) { resources.push_back(res); cout << "Added resource: " << res->getTitle() << endl; }

    void borrowResource(User* user, LibraryResource* res) {
        if(user->getBalance() < 0) { cout << "Cannot borrow. Negative balance.\n"; return; }
        user->borrowResource(res);
        borrowHistory.push_back(BorrowRecord(res, user->getBorrowDuration()));
    }

    void returnResource(User* user, LibraryResource* res) {
        user->returnResource(res);
        for(auto& rec : borrowHistory)
            if(rec.resource == res && rec.returnDate == 0) rec.markReturned(user);
    }

    void showUsers() const {
        for(auto u : users) u->displayInfo();
    }

    void showResources() const {
        for(auto r : resources) r->displayInfo();
    }

    void showBorrowHistory() const {
        for(auto rec : borrowHistory)
            cout << rec.resource->getTitle() << " borrowed on " << ctime(&rec.borrowDate) << endl;
    }
};

#endif // LIBRARY_H