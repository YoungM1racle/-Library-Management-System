#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Book.h"
#include "BookList.h"
using namespace std;

class User
{
private:
    int userId;
    string name;
    int numBooksBorrowed;
    int maxBooks;
    Book **booksBorrowed;

public:
    // default constructor
    User();

    // constructor
    User(int id, const string &n, int numBooksBorrowed = 0, int maxBooks = 5);

    ~User();

    // Member functions
    void borrowBook(Book *book);
    void returnBook(Book *book);
    int getNumBooksBorrowed() const;
    int getUserId() const;
    string getUserName() const;
    int getMaxBooks() const;
    void viewBorrowedBooks() const;
    void giveRating(BookList &list, int bookId, double newRating);
    void updateMaxBooks(int additionalSlots);
};

#endif
