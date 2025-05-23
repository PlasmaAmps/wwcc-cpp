#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Author class
class Author {
private:
    string name;
    int birthYear;

public:
    Author(string name, int birthYear) : name(name), birthYear(birthYear) {}

    string getName() const { return name; }
    int getBirthYear() const { return birthYear; }
};

// Book class
class Book {
private:
    string title;
    int publicationYear;
    string isbn;
    Author author;

public:
    Book(string title, int publicationYear, string isbn, Author author)
        : title(title), publicationYear(publicationYear), isbn(isbn), author(author) {}

    string getTitle() const { return title; }
    int getPublicationYear() const { return publicationYear; }
    string getISBN() const { return isbn; }
    Author getAuthor() const { return author; }

    void display() const {
        cout << "\"" << title << "\" (" << publicationYear << ")\n";
        cout << "   Author: " << author.getName() << " (born " << author.getBirthYear() << ")\n";
        cout << "   ISBN: " << isbn << "\n";
    }
};

// Library class
class Library {
private:
    string name;
    string address;
    vector<Book> books;

    string toLower(const string& str) const {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

public:
    Library(string name, string address) : name(name), address(address) {}

    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayCatalog() const {
        cout << "\nLibrary: " << name << "\nAddress: " << address << "\n\nCATALOG:\n";
        if (books.empty()) {
            cout << "No books in the catalog.\n";
        } else {
            for (size_t i = 0; i < books.size(); ++i) {
                cout << i + 1 << ". ";
                books[i].display();
                cout << "\n";
            }
        }
    }

    void searchByAuthor(const string& authorName) const {
        cout << "\nBooks by \"" << authorName << "\":\n";
        bool found = false;
        for (const Book& book : books) {
            if (toLower(book.getAuthor().getName()).find(toLower(authorName)) != string::npos) {
                cout << "- \"" << book.getTitle() << "\" (" << book.getPublicationYear() << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No books found by that author.\n";
        }
    }

    void searchByTitle(const string& titleKeyword) const {
        cout << "\nBooks with title containing \"" << titleKeyword << "\":\n";
        bool found = false;
        for (const Book& book : books) {
            if (toLower(book.getTitle()).find(toLower(titleKeyword)) != string::npos) {
                cout << "- \"" << book.getTitle() << "\" (" << book.getPublicationYear() << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No books found with that title keyword.\n";
        }
    }
};

// Main function
int main() {
    cout << "LIBRARY MANAGEMENT SYSTEM\n-------------------------\n";

    // Create authors
    Author fitzgerald("F. Scott Fitzgerald", 1896);
    Author lee("Harper Lee", 1926);
    Author orwell("George Orwell", 1903);

    // Create books
    Book book1("The Great Gatsby", 1925, "9780743273565", fitzgerald);
    Book book2("To Kill a Mockingbird", 1960, "9780061120084", lee);
    Book book3("1984", 1949, "9780451524935", orwell);
    Book book4("Animal Farm", 1945, "9780451526342", orwell);

    // Create library
    Library myLibrary("Central City Library", "123 Main Street, Central City");

    // Add books
    myLibrary.addBook(book1);
    myLibrary.addBook(book2);
    myLibrary.addBook(book3);
    myLibrary.addBook(book4);

    // User menu
    int choice;
    string input;
    do {
        cout << "\nMENU:\n";
        cout << "1. View Library Catalog\n";
        cout << "2. Search by Author\n";
        cout << "3. Search by Title\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore();  // clear newline from buffer

        switch (choice) {
        case 1:
            myLibrary.displayCatalog();
            break;
        case 2:
            cout << "Enter author name to search: ";
            getline(cin, input);
            myLibrary.searchByAuthor(input);
            break;
        case 3:
            cout << "Enter title keyword to search: ";
            getline(cin, input);
            myLibrary.searchByTitle(input);
            break;
        case 4:
            cout << "Exiting... Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}
