#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
#include "User.h"
#include "BookList.h"
using namespace std;

class Library
{
private:
    User **users;
    int userCount;
    int capacity;
    double totalRevenue;
    BookList libraryInventory;

public:
    // Constructor
    Library(int initialCapacity = 10);

    // Destructor
    ~Library();

    // Member functions
    void addUser(int id, const string &name);
    void upgradeUserSlots(int userId, int additionalSlots);
    double getTotalRevenue() const;
    void displayUsers() const;
    User *getUserById(int userId) const;
    void addNewBook(Book *book);
    void removeBook(int bookId);
    void displayBooks() const;

    BookList &getLibraryInventory();
};

#endif