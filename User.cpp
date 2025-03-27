#include "User.h"
#include "Book.h"

User::User() : userId(0), name(""), numBooksBorrowed(0), maxBooks(5), booksBorrowed(nullptr)
{
}

User::User(int id, const string &n, int borrow, int max) : userId(id), name(n), numBooksBorrowed(borrow), maxBooks(max), booksBorrowed(nullptr)
{
}

User::~User()
{
    if (booksBorrowed != nullptr)
    {
        for (int i = 0; booksBorrowed[i] != nullptr; ++i)
        {
            delete booksBorrowed[i];
        }
        delete[] booksBorrowed;
    }
}

void User::borrowBook(Book *book)
{
    if (numBooksBorrowed == maxBooks)
    {
        cout << "You cannot borrow more books." << endl;
        return;
    }
    if (book->getInventoryCount() == 0)
    {
        cout << "This book is currently unavailable." << endl;
        return;
    }
    if (numBooksBorrowed == 0)
    {
        booksBorrowed = new Book *[maxBooks];
        for (int i = 0; i < maxBooks; i++)
            booksBorrowed[i] = nullptr;
    }
    int i;
    // cout<<"1";
    //Book* the_book = 
    for (i = 0; booksBorrowed[i] != nullptr; i++)
    {
        if (booksBorrowed[i]->getTitle() == book->getTitle())
        {
            booksBorrowed[i]->changeInventoryCount(1);
            book->changeInventoryCount(-1);
            numBooksBorrowed++;
            cout << "Successfully borrowed: " << book->getTitle() << endl;
            return;
        }
    }
    booksBorrowed[i] = new Book(book->getId(), book->getTitle(), book->getAuthor());
    numBooksBorrowed++;
    cout << "Successfully borrowed: " << book->getTitle() << endl;
    book->changeInventoryCount(-1);
}

void User::returnBook(Book *book)
{
    bool isfound = false;
    int index = 0;
    for (int i = 0; i < numBooksBorrowed; i++)
    {
        if (booksBorrowed[i]->getTitle() == book->getTitle())
        {
            isfound = true;
            index = i;
            break;
        }
    }
    if (!isfound)
    {
        cout << "This book was not borrowed by you." << endl;
        return;
    }
    if (booksBorrowed[index]->getInventoryCount() == 1)
    {
        book->changeInventoryCount(1);
        numBooksBorrowed--;
        cout << "Successfully returned: " << book->getTitle() << endl;
        delete booksBorrowed[index];
        for (int i = index; i < maxBooks - 2; i++)
        {
            booksBorrowed[i] = booksBorrowed[i + 1];
        }
        booksBorrowed[maxBooks - 1] = nullptr;
        return;
    }
    booksBorrowed[index]->changeInventoryCount(-1);
    book->changeInventoryCount(1);
    numBooksBorrowed--;
    cout << "Successfully returned: " << book->getTitle() << endl;
}

int User::getNumBooksBorrowed() const
{
    return numBooksBorrowed;
}

int User::getUserId() const
{
    return userId;
}

string User::getUserName() const
{
    return name;
}

int User::getMaxBooks() const
{
    return maxBooks;
}

void User::viewBorrowedBooks() const
{
    if (numBooksBorrowed == 0)
    {
        cout << name << " has not borrowed any books." << endl;
        return;
    }
    cout << name << "'s Borrowed Books:" << endl;
    /*for (int i = 0 ; booksBorrowed[i]!=nullptr ; i++)
        for(int j = i + 1 ; booksBorrowed[j]!= nullptr;j++)
        {
            Book* temp;
            if(booksBorrowed[i]->getTitle()<booksBorrowed[j]->getTitle())
            {
                temp = booksBorrowed[i];
                booksBorrowed[i] = booksBorrowed[j];
                booksBorrowed[j] = temp;
            }
        }*/
    for (int i = 0; booksBorrowed[i] != nullptr; i++)
    {
        cout << booksBorrowed[i]->getTitle() << " (x" << booksBorrowed[i]->getInventoryCount() << ")" << endl;
    }
}

void User::giveRating(BookList &list, int bookId, double newRating)
{
    if (numBooksBorrowed == maxBooks)
    {
        cout << "User is blocked and cannot rate books." << endl;
        return;
    }
    Book *book = list.searchList(bookId);
    book->addRating(newRating);
}

void User::updateMaxBooks(int additionalSlots)
{
    if (additionalSlots <= 0)
    {
        cout << "Invalid number of additional Slots." << endl;
        return;
    }
    maxBooks += additionalSlots;
    cout << "Max books updated to: " << maxBooks << endl;
}