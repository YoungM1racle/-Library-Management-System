#include "Library.h"

// Constructor
Library::Library(int initialCapacity) : userCount(0), capacity(initialCapacity), totalRevenue(0)
{
}

// Destructor
Library::~Library()
{
    for (int i = 0; i < userCount; i++)
    {
        delete users[i];
    }
    delete[] users;
}

void Library::addUser(int id, const string &name)
{
    if (userCount == 0)
    {
        users = new User *[capacity];
        users[0] = new User(id, name);
        userCount++;
        totalRevenue += 5;
        return;
    }
    if (userCount == capacity)
    {
        capacity *= 2;
        User **new_users = new User *[capacity];
        for (int i = 0; i < userCount; i++)
            new_users[i] = users[i];
        new_users[userCount++] = new User(id, name);
        delete[] users;
        users = new_users;
        totalRevenue += 5;
        return;
    }
    users[userCount++] = new User(id, name);
    totalRevenue += 5;
    return;
}

void Library::upgradeUserSlots(int userId, int additionalSlots)
{
    User *the_user;
    bool isfound = 0;
    for (int i = 0; i < userCount; i++)
    {
        if (userId == users[i]->getUserId())
        {
            the_user = users[i];
            isfound = true;
            break;
        }
    }
    if (!isfound)
    {
        cout << "User ID " << userId << " not found." << endl;
        return;
    }
    the_user->updateMaxBooks(additionalSlots);
    totalRevenue += additionalSlots;
    cout << "User ID " << userId << " upgraded by " << additionalSlots << " slots." << endl;
}

double Library::getTotalRevenue() const
{
    return totalRevenue;
}

void Library::displayUsers() const
{
    for (int i = 0; i < userCount; i++)
    {
        cout << "User ID: " << users[i]->getUserId()
             << ", Name: " << users[i]->getUserName()
             << ", Borrowed Books: " << users[i]->getNumBooksBorrowed()
             << ", Max Books: " << users[i]->getMaxBooks() << endl;
    }
}

User *Library::getUserById(int userId) const
{
    User *the_user;
    bool isfound = 0;
    for (int i = 0; i < userCount; i++)
    {
        if (userId == users[i]->getUserId())
        {
            the_user = users[i];
            isfound = true;
            return the_user;
        }
    }
    return nullptr;
}

void Library::addNewBook(Book *book)
{
    if (totalRevenue < 2)
    {
        cout << "Insufficient funds to add the book " << book->getTitle() << "." << endl;
        return;
    }
    Book *the_book = libraryInventory.searchList(book->getId());
    if (the_book == nullptr)
    {
        libraryInventory.insertBook(book);
        cout << "Book " << "'" << book->getTitle() << "' added to the library." << endl;
        totalRevenue -= 2;
        return;
    }
    if (totalRevenue < 2 * book->getInventoryCount())
    {
        cout << "Insufficient funds to add the book " << book->getTitle() << "." << endl;
        return;
    }
    for (int i =0 ;i< book->getInventoryCount();i++)
        libraryInventory.insertBook(the_book);
    cout << "Book " << "'" << book->getTitle() << "' added to the library." << endl;
    totalRevenue -= 2 * book->getInventoryCount();
}

void Library::removeBook(int bookId)
{
    if (libraryInventory.searchList(bookId) == nullptr)
    {
        cout << "Book with ID " << bookId << " not found in the library." << endl;
        return;
    }
    Book *the_book = libraryInventory.searchList(bookId);
    int copies = the_book->getInventoryCount();
    totalRevenue += copies;
    for (int i = 0; i < copies; i++)
        libraryInventory.removeBook(the_book);
}

void Library::displayBooks() const
{
    // cout<<"There are "<< libraryInventory.countBooks()<<" books in the library. They are:"<<endl;
    libraryInventory.displayBooks();
}

BookList &Library::getLibraryInventory()
{
    return libraryInventory;
}