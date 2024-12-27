#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    int bookID;
    string title;
    string author;
    int copies;

    Book(int id, const string& t, const string& a, int c)
        : bookID(id), title(t), author(a), copies(c) {}

    void displayDetails() const {
        cout << "ID: " << bookID << ", Title: " << title
             << ", Author: " << author << ", Copies: " << copies << endl;
    }
};

class Member {
public:
    int memberID;
    string name;
    vector<Book*> borrowedBooks;

    Member(int id, const string& n) : memberID(id), name(n) {}

    void borrowBook(Book* book) {
        if (book->copies > 0) {
            book->copies--;
            borrowedBooks.push_back(book);
            cout << name << " borrowed " << book->title << endl;
        } else {
            cout << "Sorry, " << book->title << " is not available." << endl;
        }
    }

    void returnBook(Book* book) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            book->copies++;
            borrowedBooks.erase(it);
            cout << name << " returned " << book->title << endl;
        } else {
            cout << name << " did not borrow " << book->title << endl;
        }
    }

    void displayBorrowedBooks() const {
        if (!borrowedBooks.empty()) {
            cout << name << " has borrowed:" << endl;
            for (const auto& book : borrowedBooks) {
                cout << "- " << book->title << endl;
            }
        } else {
            cout << name << " has not borrowed any books." << endl;
        }
    }
};

class Library {
public:
    vector<Book> books;
    vector<Member> members;

    void addBook() {
        int id, copies;
        string title, author;
        cout << "Enter Book ID, Title, Author, and Copies: ";
        cin >> id;
        cin.ignore();
        getline(cin, title);
        getline(cin, author);
        cin >> copies;
        books.emplace_back(id, title, author, copies);
        cout << "Book '" << title << "' added to the library." << endl;
    }

    void addMember() {
        int id;
        string name;
        cout << "Enter Member ID and Name: ";
        cin >> id;
        cin.ignore();
        getline(cin, name);
        members.emplace_back(id, name);
        cout << "Member '" << name << "' added to the library." << endl;
    }

    void displayBooks() const {
        cout << "Books in Library:" << endl;
        for (const auto& book : books) {
            book.displayDetails();
        }
    }

    Book* findBook(int id) {
        for (auto& book : books) {
            if (book.bookID == id) {
                return &book;
            }
        }
        return nullptr;
    }

    Member* findMember(int id) {
        for (auto& member : members) {
            if (member.memberID == id) {
                return &member;
            }
        }
        return nullptr;
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Display Books\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Display Borrowed Books\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;
        case 2:
            library.addMember();
            break;
        case 3:
            library.displayBooks();
            break;
        case 4: {
            int memberID, bookID;
            cout << "Enter Member ID and Book ID: ";
            cin >> memberID >> bookID;
            Member* member = library.findMember(memberID);
            Book* book = library.findBook(bookID);
            if (member && book) {
                member->borrowBook(book);
            } else {
                cout << "Invalid Member ID or Book ID." << endl;
            }
            break;
        }
        case 5: {
            int memberID, bookID;
            cout << "Enter Member ID and Book ID: ";
            cin >> memberID >> bookID;
            Member* member = library.findMember(memberID);
            Book* book = library.findBook(bookID);
            if (member && book) {
                member->returnBook(book);
            } else {
                cout << "Invalid Member ID or Book ID." << endl;
            }
            break;
        }
        case 6: {
            int memberID;
            cout << "Enter Member ID: ";
            cin >> memberID;
            Member* member = library.findMember(memberID);
            if (member) {
                member->displayBorrowedBooks();
            } else {
                cout << "Invalid Member ID." << endl;
            }
            break;
        }
        case 7:
            cout << "Exiting the system." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

