#include <iostream>
#include <vector>
#include <string>

// ======================
// Book Class Definition
// ======================
class Book {
private:
    std::string name;
    std::string author;
    bool borrowed;

public:
    // Constructor
    Book(const std::string& n, const std::string& a)
        : name(n), author(a), borrowed(false) {}

    // Getters
    std::string getName() const { return name; }
    std::string getAuthor() const { return author; }
    bool isBorrowed() const { return borrowed; }

    // Setter for borrow status
    void setBorrowed(bool status) { borrowed = status; }
};

// ======================
// Library Class Definition
// ======================
class Library {
private:
    std::vector<Book> books;

public:
    // Add a new Book to the library
    void addBook(const std::string& name, const std::string& author) {
        books.emplace_back(name, author);
        std::cout << "Book added successfully!\n";
    }

    // Borrow a Book by index
    bool borrowBook(size_t index) {
        if (index >= books.size()) {
            std::cout << "Invalid book index.\n";
            return false;
        }
        if (books[index].isBorrowed()) {
            std::cout << "Book is already borrowed.\n";
            return false;
        }
        books[index].setBorrowed(true);
        std::cout << "Book borrowed successfully!\n";
        return true;
    }

    // Return a Book by index
    bool returnBook(size_t index) {
        if (index >= books.size()) {
            std::cout << "Invalid book index.\n";
            return false;
        }
        if (!books[index].isBorrowed()) {
            std::cout << "Book is not currently borrowed.\n";
            return false;
        }
        books[index].setBorrowed(false);
        std::cout << "Book returned successfully!\n";
        return true;
    }

    // Display all Books
    void displayBooks() const {
        if (books.empty()) {
            std::cout << "No books in the library.\n";
            return;
        }
        std::cout << "\nAll Books:\n";
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << i << ". "
                      << books[i].getName()
                      << " by " << books[i].getAuthor()
                      << " [" << (books[i].isBorrowed() ? "Borrowed" : "Available") << "]\n";
        }
    }

    // Display only Borrowed Books
    void displayBorrowedBooks() const {
        bool found = false;
        std::cout << "\nBorrowed Books:\n";
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].isBorrowed()) {
                std::cout << i << ". "
                          << books[i].getName()
                          << " by " << books[i].getAuthor() << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books are currently borrowed.\n";
        }
    }

    // Get number of books in the library
    size_t bookCount() const { return books.size(); }
};

// =========================
// Executor Class Definition
// =========================
class Executor {
private:
    Library library;  // Library instance to manage books

    // Displays the main menu
    void showMenu() const {
        std::cout << "\n====== Library Tracker Menu ======\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Borrow Book\n";
        std::cout << "3. Return Book\n";
        std::cout << "4. Display All Books\n";
        std::cout << "5. Display Borrowed Books\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
    }

public:
    // Runs the program interactively
    void run() {
        int choice;
        std::cout << "===== Welcome to the Library Tracker System =====\n";
        do {
            showMenu();
            std::cin >> choice;
            std::cin.ignore(); // To consume the leftover newline character

            switch (choice) {
                case 1: {
                    std::string name, author;
                    std::cout << "Enter book name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter author: ";
                    std::getline(std::cin, author);
                    library.addBook(name, author);
                    break;
                }
                case 2: {
                    library.displayBooks();
                    if (library.bookCount() == 0) break;
                    std::cout << "Enter book index to borrow: ";
                    size_t idx;
                    std::cin >> idx;
                    library.borrowBook(idx);
                    std::cin.ignore();
                    break;
                }
                case 3: {
                    library.displayBooks();
                    if (library.bookCount() == 0) break;
                    std::cout << "Enter book index to return: ";
                    size_t idx;
                    std::cin >> idx;
                    library.returnBook(idx);
                    std::cin.ignore();
                    break;
                }
                case 4:
                    library.displayBooks();
                    break;
                case 5:
                    library.displayBorrowedBooks();
                    break;
                case 0:
                    std::cout << "Exiting Library Tracker. Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        } while (choice != 0);
    }
};

// ==============
// Main Function
// ==============
int main() {
    Executor executor;
    executor.run();
    return 0;
}
