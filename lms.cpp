#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Book Structure 
struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    bool isReserved;
};

//  User Structure 
struct User {
    int id;
    string name;
    vector<int> issuedBooks;
    vector<int> reservedBooks;
    double fineAmount; // Track fines for overdue books
};

//  Library Class 
class Library {
    vector<Book> books;
    vector<User> users;

public:
    // Add a new book to the library
    void addBook(int id, string title, string author) {
        books.push_back({id, title, author, false, false});
        cout << "Book added: " << title << endl;
    }

    // Register a new user
    void addUser(int id, string name) {
        users.push_back({id, name, {}, {}, 0.0});
        cout << "User added: " << name << endl;
    }

    // Issue a book to a user
    void issueBook(int userId, int bookId) {
        for (auto &book : books) {
            if (book.id == bookId && !book.isIssued && !book.isReserved) {
                book.isIssued = true;
                for (auto &user : users) {
                    if (user.id == userId) {
                        user.issuedBooks.push_back(bookId);
                        cout << "Book issued to " << user.name << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book not available for issue!" << endl;
    }

    // Return a book
    void returnBook(int userId, int bookId, bool isLate = false) {
        for (auto &book : books) {
            if (book.id == bookId && book.isIssued) {
                book.isIssued = false;
                for (auto &user : users) {
                    if (user.id == userId) {
                        auto it = find(user.issuedBooks.begin(), user.issuedBooks.end(), bookId);
                        if (it != user.issuedBooks.end()) {
                            user.issuedBooks.erase(it);
                            cout << "Book returned by " << user.name << endl;
                            if (isLate) {
                                user.fineAmount += 50.0; // Example fine
                                cout << "Late return! Fine added: 50 INR" << endl;
                            }
                            return;
                        }
                    }
                }
            }
        }
        cout << "Return failed!" << endl;
    }

    // Reserve a book
    void reserveBook(int userId, int bookId) {
        for (auto &book : books) {
            if (book.id == bookId && !book.isIssued && !book.isReserved) {
                book.isReserved = true;
                for (auto &user : users) {
                    if (user.id == userId) {
                        user.reservedBooks.push_back(bookId);
                        cout << "Book reserved by " << user.name << endl;
                        return;
                    }
                }
            }
        }
        cout << "Reservation failed!" << endl;
    }

    // Show library report
    void showReport() {
        cout << "\n--- Library Report ---\n";
        for (auto &book : books) {
            cout << "Book ID: " << book.id << " | Title: " << book.title
                 << " | Author: " << book.author
                 << " | Status: " << (book.isIssued ? "Issued" : (book.isReserved ? "Reserved" : "Available")) << endl;
        }
        cout << "\n--- User Report ---\n";
        for (auto &user : users) {
            cout << "User ID: " << user.id << " | Name: " << user.name
                 << " | Fine: " << user.fineAmount << " INR" << endl;
        }
    }
};

//  Main Function 
int main() {
    Library lib;
    int choice;

    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Add User\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Reserve Book\n";
        cout << "6. Show Report\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            lib.addBook(id, title, author);
        }
        else if (choice == 2) {
            int id;
            string name;
            cout << "Enter User ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter User Name: ";
            getline(cin, name);
            lib.addUser(id, name);
        }
        else if (choice == 3) {
            int userId, bookId;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Book ID: ";
            cin >> bookId;
            lib.issueBook(userId, bookId);
        }
        else if (choice == 4) {
            int userId, bookId;
            char late;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Book ID: ";
            cin >> bookId;
            cout << "Was the book returned late? (y/n): ";
            cin >> late;
            lib.returnBook(userId, bookId, (late == 'y' || late == 'Y'));
        }
        else if (choice == 5) {
            int userId, bookId;
            cout << "Enter User ID: ";
            cin >> userId;
            cout << "Enter Book ID: ";
            cin >> bookId;
            lib.reserveBook(userId, bookId);
        }
        else if (choice == 6) {
            lib.showReport();
        }

    } while (choice != 7);

    cout << "Exiting Library Management System..." << endl;
    return 0;
}
