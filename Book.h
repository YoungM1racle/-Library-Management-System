#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    int bookId;
    string title;
    string author;
    int inventoryCount;
    double rating;
    int ratingCount;

public:
    // Default constructor
    Book();

    // Constructor
    Book(int id, const string &t, const string &a, int invcount = 1, double rating = 0.0, int ratcount = 0);

    // Member functions
    int getId() const;
    int getInventoryCount() const;
    void changeInventoryCount(int c);
    string getTitle() const;
    string getAuthor() const;
    double getRating() const;
    void addRating(double newRating);
};

#endif
