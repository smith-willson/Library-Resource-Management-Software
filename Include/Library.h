#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Resources.h"
#include "Users.h"
using namespace std;

// Manages all library operations — resources, users, and borrowing
class Library
{
private:

    // Tracks a single borrowing transaction
    struct BorrowRecord
    {
        int userID;                // who borrowed
        LibraryResource *resource; // what was borrowed
        time_t borrowDate;
        time_t dueDate;
        time_t returnDate;         // 0 if not yet returned
        double fine;

        // calculates due date from borrow duration
        BorrowRecord(int uid, LibraryResource *res, int durationDays);

        // marks returned and deducts fine if overdue
        void markReturned(User *user);
    };

    string libraryName;
    vector<LibraryResource *> resources; // all resources
    vector<User *> users;                // all registered users
    vector<BorrowRecord> borrowHistory;  // full borrow history

public:
    // vectors start empty, FileHandler fills them from CSV
    Library(string name);

    // ---------- Resource Management ----------
    void addResource(LibraryResource *res);
    void showResources() const;

    // ---------- User Management ----------
    void addUser(User *user);
    void showUsers() const;

    // ---------- Borrowing Logic ----------
    bool borrowResource(User *user, LibraryResource *res, int durationDays = 10); // checks daily limit and availability before borrowing
    
    // ---------- Returning Logic ----------
    bool returnResource(User *user, LibraryResource *res); // finds active borrow record and marks it returned

    // ---------- Borrow History ----------
    void showBorrowHistory() const;

    // ---------- Getters ----------
    // return by reference so FileHandler can fill vectors directly
    string getLibraryName() const;
    vector<User *> &getUsers();
    vector<LibraryResource *> &getResources();
    vector<BorrowRecord> &getBorrowHistory();

    // ---------- Destructor ----------
    ~Library(); // frees all heap memory
};

#endif