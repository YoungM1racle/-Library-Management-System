#include "BookList.h"
#include "Book.h"

BookList::BookList() : head(nullptr)
{
}

BookList::BookList(const BookList &other)
{
    if (other.head == nullptr)
    {
        head = nullptr;
        return;
    }

    head = new Node(other.head->data);
    Node *temp = head;
    for (Node *p = other.head->next; p != nullptr; p = p->next)
    {
        temp->next = new Node(p->data);
        temp = temp->next;
    }
}

BookList::~BookList()
{
    Node *curr = head;
    Node *temp = nullptr;
    while (curr != nullptr)
    {
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
}

bool BookList::isEmpty() const
{
    return (head == nullptr);
}

void BookList::insertBook(Book *book)
{
    Node *p, *prev;
    if (head == nullptr)
    {
        head = new Node(book);
        return;
    }
    for (p = head; p != nullptr; prev = p, p = p->next)
    {
        if (p->data->getTitle() == book->getTitle())
        {
            p->data->changeInventoryCount(1);
            return;
        }
    }
    p = new Node(book);
    prev->next = p;
}

void BookList::removeBook(Book *book)
{
    if (head == nullptr)
        return;
    bool isfound = 0;
    Node *p;
    Node *prev = nullptr;
    for (p = head; p != nullptr; prev = p, p = p->next)
    {
        if (p->data->getTitle() == book->getTitle())
        {
            isfound = 1;
            break;
        }
        // break;
    }
    if (!isfound)
        return;
    if (p->data->getInventoryCount() > 1)
    {
        p->data->changeInventoryCount(-1);
        return;
    }
    Node *temp = p;
    prev->next = p->next;
    delete temp;
}

void BookList::displayBooks() const
{
    cout << "Library Book Details:" << endl;
    if (head == nullptr)
    {
        cout << "The book list is empty." << endl;
    }
    for (Node *p = head; p != nullptr; p = p->next)
    {
        cout << "ID: " << p->data->getId()
             << " - Title: " << p->data->getTitle()
             << " - Author: " << p->data->getAuthor()
             << " - Rating: " << p->data->getRating() << endl;
    }
}

void BookList::sortBooks(SortCriteria criteria)
{
    switch (criteria)
    {
    case BY_RATING:
    {
        cout << "Books sorted in decending order of ratings:" << endl;
        // Node *temp = nullptr;
        for (Node *p = head; p != nullptr; p = p->next)
        {
            for (Node *q = p; q != nullptr; q = q->next)
            {
                if (q->data->getRating() > p->data->getRating())
                {
                    Book *temp;
                    temp = p->data;
                    p->data = q->data;
                    q->data = temp;
                }
            }
        }
        break;
    }

    case BY_TITLE:
    {
        // cout << "Books sorted in alphabetical order:" << endl;
        //  Node *temp = nullptr;
        for (Node *p = head; p != nullptr; p = p->next)
        {
            for (Node *q = p->next; q != nullptr; q = q->next)
            {

                if (q->data->getTitle() < p->data->getTitle())
                {
                    Book *temp;
                    temp = p->data;
                    p->data = q->data;
                    q->data = temp;
                }
            }
        }
    }
    }
}

Book *BookList::searchList(int bookId) const
{
    for (Node *p = head; p != nullptr; p = p->next)
    {
        if (p->data->getId() == bookId)
            return p->data;
    }
    return nullptr;
}

int BookList::countBooks() const
{
    int sum = 0;
    for (Node *p = head; p != nullptr; p = p->next)
    {
        sum += p->data->getInventoryCount();
    }
    return sum;
}

void BookList::rateBook(int bookId, double newRating)
{
    if (searchList(bookId) == nullptr)
    {
        cout << "Book with ID " << bookId << " not found." << endl;
        return;
    }
    searchList(bookId)->addRating(newRating);
    cout << "Rating updated for Book " << bookId << ". New Rating: " << searchList(bookId)->getRating() << endl;
}

Book *BookList::getBookWithMaxRating() const
{
    if (head == nullptr)
    {
        cout << "The book list is empty." << endl;
        return nullptr;
    }
    Book temp;
    Book *MAX = &temp;
    for (Node *p = head; p != nullptr; p = p->next)
    {
        if (MAX->getRating() < p->data->getRating())
        {
            MAX = p->data;
        }
    }
    return MAX;
}

Book *BookList::getBookWithMinRating() const
{
    if (head == nullptr)
    {
        cout << "The book list is empty." << endl;
        return nullptr;
    }
    Book temp(0, "", "", 1, 5.0, 1);
    Book *MIN = &temp;
    for (Node *p = head; p != nullptr; p = p->next)
    {
        if (MIN->getRating() > p->data->getRating())
        {
            MIN = p->data;
        }
    }
    return MIN;
}

void BookList::reverseBooksByRating()
{
    Node *curr = head;
    Node *prev = nullptr, *next = nullptr;
    while (curr != nullptr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}