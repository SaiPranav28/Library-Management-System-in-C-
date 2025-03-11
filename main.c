#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 50
#define MAX_BOOKS 100

// Structure to represent a book
typedef struct {
    int bookID;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int year;
    int availableCopies;
} Book;

// Function declarations
void addBook();
void displayBooks();
void searchBook();
void deleteBook();
void modifyBook();
void saveBooksToFile();
void loadBooksFromFile();
void displayBook(Book book);

// Global array of books
Book books[MAX_BOOKS];
int bookCount = 0;

int main() {
    int choice;

    // Load books from file at the start
    loadBooksFromFile();

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search for Book\n");
        printf("4. Modify Book Details\n");
        printf("5. Delete Book\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                modifyBook();
                break;
            case 5:
                deleteBook();
                break;
            case 6:
                saveBooksToFile();
                printf("Changes saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;

    printf("\nEnter book ID: ");
    scanf("%d", &newBook.bookID);
    getchar();  // to capture the newline character

    printf("Enter book title: ");
    fgets(newBook.title, MAX_TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;  // Remove newline character

    printf("Enter author name: ");
    fgets(newBook.author, MAX_AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;  // Remove newline character

    printf("Enter publication year: ");
    scanf("%d", &newBook.year);

    printf("Enter number of available copies: ");
    scanf("%d", &newBook.availableCopies);

    books[bookCount] = newBook;
    bookCount++;

    printf("Book added successfully!\n");
}

void displayBooks() {
    if (bookCount == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\nList of Books:\n");
    for (int i = 0; i < bookCount; i++) {
        displayBook(books[i]);
    }
}

void searchBook() {
    int searchID;
    printf("\nEnter the book ID to search: ");
    scanf("%d", &searchID);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == searchID) {
            printf("\nBook found:\n");
            displayBook(books[i]);
            return;
        }
    }

    printf("Book with ID %d not found.\n", searchID);
}

void modifyBook() {
    int searchID;
    printf("\nEnter the book ID to modify: ");
    scanf("%d", &searchID);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == searchID) {
            printf("\nBook found. Modify details:\n");

            printf("Enter new title: ");
            getchar();  // to capture the newline character
            fgets(books[i].title, MAX_TITLE_LEN, stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;  // Remove newline character

            printf("Enter new author: ");
            fgets(books[i].author, MAX_AUTHOR_LEN, stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;  // Remove newline character

            printf("Enter new publication year: ");
            scanf("%d", &books[i].year);

            printf("Enter new number of available copies: ");
            scanf("%d", &books[i].availableCopies);

            printf("Book details updated successfully!\n");
            return;
        }
    }

    printf("Book with ID %d not found.\n", searchID);
}

void deleteBook() {
    int searchID;
    printf("\nEnter the book ID to delete: ");
    scanf("%d", &searchID);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == searchID) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }

            bookCount--;
            printf("Book with ID %d deleted successfully!\n", searchID);
            return;
        }
    }

    printf("Book with ID %d not found.\n", searchID);
}

void saveBooksToFile() {
    FILE *file = fopen("library.dat", "wb");
    if (!file) {
        printf("Error opening file to save data.\n");
        return;
    }

    fwrite(&bookCount, sizeof(int), 1, file);
    fwrite(books, sizeof(Book), bookCount, file);

    fclose(file);
    printf("Books data saved successfully.\n");
}

void loadBooksFromFile() {
    FILE *file = fopen("library.dat", "rb");
    if (!file) {
        printf("No existing data found, starting fresh.\n");
        return;
    }

    fread(&bookCount, sizeof(int), 1, file);
    fread(books, sizeof(Book), bookCount, file);

    fclose(file);
}

void displayBook(Book book) {
    printf("\nBook ID: %d\n", book.bookID);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);
    printf("Available Copies: %d\n", book.availableCopies);
    printf("------------------------------\n");
}
