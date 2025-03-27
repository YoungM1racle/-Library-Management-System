#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <iostream>
#include <string>
#include "Book.h"
using namespace std;

enum SortCriteria
{
    BY_RATING,
    BY_TITLE
};

class BookList
{
private:
    struct Node
    {
        Book *data;
        Node *next;
        Node(Book *book) : data(book), next(nullptr) {}
    };

    Node *head;

public:
    // constructor
    BookList();

    // deep copy constructor
    BookList(const BookList &other);

    // destructor
    ~BookList();

    // Member functions
    bool isEmpty() const;
    void insertBook(Book *book);
    void removeBook(Book *book);
    void displayBooks() const;
    void sortBooks(SortCriteria criteria);
    Book *searchList(int bookId) const;
    int countBooks() const;
    void rateBook(int bookId, double newRating);
    Book *getBookWithMaxRating() const;
    Book *getBookWithMinRating() const;
    void reverseBooksByRating();
};

#endif