#include "Library.h"
#include <iostream>
using namespace std;

// ===================== BorrowRecord =====================

// calculates due date from borrow duration
Library::BorrowRecord::BorrowRecord(int uid, LibraryResource *res, int durationDays)
    : userID(uid), resource(res), fine(0.0), returnDate(0)
{
    borrowDate = time(0);
    dueDate = borrowDate + durationDays * 24 * 60 * 60;
}

// marks returned and deducts fine if overdue
void Library::BorrowRecord::markReturned(User *user)
{
    returnDate = time(0);
    if (difftime(returnDate, dueDate) > 0)
    {
        int daysLate = static_cast<int>(difftime(returnDate, dueDate) / (60 * 60 * 24));
        fine = daysLate * user->getFineRate();
        user->updateBalance(-fine);
    }
}

// ===================== Library =====================

// ---------- Constructor ----------
// vectors start empty, FileHandler fills them from CSV
Library::Library(string name) : libraryName(name) {}

// ---------- Destructor ----------
// frees all heap memory on program exit
Library::~Library()
{
    for (auto user : users)
        delete user;

    for (auto res : resources)
        delete res;
}

// ---------- Resource Management ----------
void Library::addResource(LibraryResource *res)
{
    resources.push_back(res);
    cout << "Resource \"" << res->getTitle() << "\" added to " << libraryName << endl;
}

void Library::showResources() const
{
    cout << "\nResources in " << libraryName << ":\n";
    for (auto res : resources)
    {
        res->displayInfo();
        cout << "-----------------------\n";
    }
}

// ---------- User Management ----------
void Library::addUser(User *user)
{
    users.push_back(user);
    cout << "User \"" << user->getName() << "\" added to " << libraryName << endl;
}

void Library::showUsers() const
{
    cout << "\nUsers of " << libraryName << ":\n";
    for (auto user : users)
    {
        user->displayInfo();
        cout << "-----------------------\n";
    }
}

// ---------- Borrowing Logic ----------

// checks daily limit and availability before borrowing
bool Library::borrowResource(User *user, LibraryResource *res, int durationDays)
{
    int countToday = 0;
    time_t now = time(0);

    // count active borrows by this user in last 24 hours
    for (auto &record : borrowHistory)
    {
        if (record.userID == user->getUserID() &&
            record.returnDate == 0 &&
            difftime(now, record.borrowDate) <= 24 * 60 * 60)
        {
            countToday++;
        }
    }

    if (countToday >= user->getDailyLimit())
    {
        cout << user->getName() << " has reached the daily borrow limit of "
             << user->getDailyLimit() << " resources.\n";
        return false;
    }

    if (!res->isAvailable())
    {
        cout << "Resource \"" << res->getTitle() << "\" is not available.\n";
        return false;
    }

    res->borrowResource();
    borrowHistory.push_back(BorrowRecord(user->getUserID(), res, durationDays));

    cout << user->getName() << " successfully borrowed \"" << res->getTitle() << "\".\n";
    return true;
}

// ---------- Returning Logic ----------

// finds active borrow record and marks it returned
bool Library::returnResource(User *user, LibraryResource *res)
{
    for (auto &record : borrowHistory)
    {
        if (record.userID == user->getUserID() &&
            record.resource == res &&
            record.returnDate == 0)
        {
            record.markReturned(user);
            res->returnResource();

            cout << user->getName() << " returned \"" << res->getTitle() << "\".\n";

            if (record.fine > 0)
                cout << "Overdue! Fine of " << record.fine << " applied.\n";

            return true;
        }
    }

    cout << user->getName() << " has not borrowed \"" << res->getTitle() << "\".\n";
    return false;
}

// ---------- Borrow History ----------
void Library::showBorrowHistory() const
{
    cout << "\nBorrow History:\n";
    for (auto &record : borrowHistory)
    {
        cout << "Resource : " << record.resource->getTitle() << endl;
        cout << "Borrowed : " << ctime(&record.borrowDate);

        if (record.returnDate != 0)
        {
            cout << "Returned : " << ctime(&record.returnDate);
            cout << "Fine     : " << record.fine << endl;
        }
        else
            cout << "Status   : Not Returned Yet\n";

        cout << "-----------------------\n";
    }
}

// ---------- Getters ----------
string Library::getLibraryName() const { return libraryName; }
vector<User *> &Library::getUsers() { return users; }
vector<LibraryResource *> &Library::getResources() { return resources; }
vector<Library::BorrowRecord> &Library::getBorrowHistory() { return borrowHistory; }