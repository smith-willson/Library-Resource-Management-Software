#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Resources.h"
#include "Users.h"
using namespace std;

// --------------------- Borrow Record ---------------------
struct BorrowRecord
{
    LibraryResource* resource; // Pointer to borrowed resource
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
    double fine;

    BorrowRecord(LibraryResource* res, int durationDays)
        : resource(res), fine(0.0), returnDate(0)
    {
        borrowDate = time(0);
        dueDate = borrowDate + durationDays * 24 * 60 * 60;
    }

    // Mark resource as returned and calculate fine if overdue
    void markReturned(User* user)
    {
        returnDate = time(0);
        if (difftime(returnDate, dueDate) > 0)
        {
            int daysLate = static_cast<int>(difftime(returnDate, dueDate) / (60 * 60 * 24));
            fine = daysLate * user->getFineRate();
            // user->updateBalance(-fine);
        }
    }
};

// --------------------- Library Class ---------------------
class Library
{
private:
    string libraryName;
    vector<LibraryResource*> resources;          // All resources
    vector<User*> users;                         // All users
    vector<BorrowRecord> borrowHistory;          // Tracks all borrowings

public:
    // ---------- Constructor ----------
    Library(string name) : libraryName(name) {}

    // ---------- Resource Management ----------
    void addResource(LibraryResource* res)
    {
        resources.push_back(res);
        cout << "Resource \"" << res->getTitle() << "\" added to " << libraryName << endl;
    }

    void showResources() const
    {
        cout << "Resources in " << libraryName << ":"<<endl;
        for (auto res : resources)
        {
            res->displayInfo();
            cout << "-----------------------"<<endl;
        }
    }

    // ---------- User Management ----------
    void addUser(User* user)
    {
        users.push_back(user);
        cout << "User \"" << user->getFullName() << "\" added to " << libraryName << endl;
    }

    void showUsers() const
    {
        cout << "Users of " << libraryName << ":"<<endl;
        for (auto user : users)
        {
            user->displayInfo();
            cout << "-----------------------"<<endl;
        }
    }

    // ---------- Borrowing Logic ----------
    bool borrowResource(User* user, LibraryResource* res, int durationDays = 10)
    {
    if (user->getBalance() < 0)
        {
            cout << "Cannot borrow resource. Outstanding balance: " << user->getBalance() << endl;
            return false;
        }
        for (int i = 0; i < user->getBorrowLimit(); i++)
        {
            if (user->getBorrowResources(i).empty())
            {
                if (res->borrowResource())
                {
                    cout << "Successfully borrowed " << res->getTitle() << endl;
                    user->setBorrowResource(i, res->getTitle());
                    cout << "Borrowed: " << res->getTitle() << endl;
                    time_t now = time(0);
                    char buf[80];
                    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
                    string borrowDate = buf;

                    // --- Set Due Date ---
                    time_t due = now + (durationDays * 24 * 60 * 60); // days in seconds
                    strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&due));
                    string dueDate = buf;

                    // --- Set Return Date initially ---
                    string returnDate = "Not returned yet";
                    user->setBorrowingHistory(i, res->getTitle(), borrowDate, dueDate, returnDate, due);
                }
                else
                {
                    cout << "Failed to borrow " << res->getTitle() << ". No copies available." << endl;
                }
                return;
            }
        }
        cout << "Cannot borrow more resources. Maximum limit reached." << endl;
    }

    // ---------- Returning Logic ----------
    bool returnResource(User* user, LibraryResource* res,float fineRate = 5.0)
    {
        for (int i = 0; i < user->getBorrowLimit(); i++)
        {
            if (user->getBorrowResources(i) == res->getTitle())
            {
                // Mark resource as returned in the library system
                res->returnResource();
                cout << "Successfully returned " << res->getTitle() << endl;

                // Clear from borrowed list
                user->setBorrowResource(i, "");

                // --- Set Return Date ---
                time_t now = time(0);
                char buf[80];
                strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
                string returnDate = "Returned on: " + string(buf);

                // --- Fine Calculation ---
                // Instead of parsing dueDate string, store dueDate as time_t in BorrowingHistory
                // Let's assume you add: time_t dueDateRaw; in BorrowingHistory struct
                time_t dueDate = user->getBorrowingDueDate(i);

                if (difftime(now, dueDate) > 0)
                {
                    // Overdue: calculate fine
                    int daysLate = static_cast<int>(difftime(now, dueDate) / (60 * 60 * 24));
                    double finePerDay = fineRate; // Example fine rate
                    double fine = daysLate * finePerDay;

                    user->setBalance(user->getBalance() - fine);
                    cout << "Resource was overdue by " << daysLate
                         << " days. Fine of " << fine
                         << " deducted. New balance: " << user->getBalance() << endl;
                }

                return;
            }
        }
        cout << "You have not borrowed " << res->getTitle() << endl;
    }

    // ---------- Borrow History ----------
    void showBorrowHistory() const
    {
        cout << "Borrow History:"<<endl;
        for (auto record : borrowHistory)
        {
            cout << "Resource: " << record.resource->getTitle()
                 << ", Borrowed: " << ctime(&record.borrowDate);
            if (record.returnDate != 0)
                cout << ", Returned: " << ctime(&record.returnDate)
                     << ", Fine: " << record.fine << endl;
            else
                cout << ", Not Returned Yet" << endl;
        }
    }

    // ---------- Getters ----------
    string getLibraryName() const { return libraryName; }
};

#endif
