#include <iostream>
#include <sstream> //for converting string to int, or attempting to do so
#include <iomanip> //to use setprecision()
using namespace std;

struct library {
    char title[50], author[50], style[20];
    int code; int quantity;
    float price;
    library* next;
};

int nextBookID = 0, removedID = 0;


void listBooks(library* l) {
    if (l == NULL) {
        cout << "Library is empty." << endl;
        return;
    }

    library* p = l;

    while (p != NULL) {

        cout << p->code << "\t" << p->title << "\n"
                << "\t" << p->author << "\n"
                << "\t" << p->style << "\n"
                << "\t" << p->quantity << ": " << fixed << setprecision(2) << p->price << "€\n" // fixed and setprecision() to format floating-point in p->price
                << endl;
        p = p->next;
    }
}

library* insertBook(library* l) {
    library* p = new library;

    // simply getting user input into each variable of struct

    cout << "What book do you wish to insert? ";
    cin.ignore();
    cin.getline(p->title, sizeof(p->title));

    cout << "\nWho's the author? ";
    cin.getline(p->author, sizeof(p->author));

    cout << "\nWhat style is it written in? ";
    cin.getline(p->style, sizeof(p->style));

    if (removedID == 0 or removedID == nextBookID) {
        nextBookID++;
        p->code = nextBookID;
        removedID = 0;
    }
    else if(removedID < nextBookID){
        p->code = removedID;
        removedID = 0;
    }

    do // do-while loop to give user infinite amount of attempts just to make sure that it gets int value in the end
    {
        string temp;
        cout << "\nHow much books do you want to insert? ";
        cin >> temp;
        istringstream iss(temp); // inserted by <sstream>, attempts to convert into int

        if (iss >> p->quantity) {  // if convertion  succeeded, eventually applies converted value into p->code and breaks the loop
            p->quantity = stoi(temp); //stoi = string to int
            break;
        }
        else { cout << "Invalid input. Please enter a valid integer.\n"; }
    } while (true);

    do // same here
    {
        string temp;
        cout << "\nWhat will the price be? ";
        cin >> temp;
        istringstream iss(temp);

        if (iss >> p->price) {
            p->price = stof(temp); //stof = string to float
            break;
        }
        else { cout << "Invalid input. Please enter a valid integer.\n"; }
    } while (true);

    p->next = l;
    l = p;

    return l; // returns list
}

library* removeBook(library* l) {
    library* p = l, * prev = NULL;
    char search[50];
    cin.ignore();
    cout << "What book you want to remove from library? ";
    cin.getline(search, sizeof(search));
    while (p != NULL){
        if (strcmp(p->title, search) == 0) {
            removedID = p->code;
            if (prev != NULL) {

                prev->next = p->next;
                cout << search << " has been successfully removed from the library." << endl;
                delete p;

                return l;
            }
            else {

                l = p->next;
                cout << search << " has been successfully removed from the library." << endl;
                delete p;

                return l;
            }
        }
        prev = p;
        p = p->next;
    }
    cout << search << " has been not found in the library." << endl;
    return l;
}

void searchBook(library* l) {
    library* p = l;
    char title_search[50]{};
    cout << "What title do you search for? ";
    cin.ignore();
    cin.getline(title_search, sizeof(title_search));
    while (p != NULL)
    {
        if (strcmp(p->title, title_search) == 0) {
            cout << title_search << " has been found.\n"
                << p->code << "\t" << p->title << "\n"
                << "\t" << p->author << "\n"
                << "\t" << p->style << "\n"
                << "\t" << p->quantity << ": " << fixed << setprecision(2) << p->price << "€\n" // fixed and setprecision() to format floating-point in p->price
                << endl;
            return;
        }
        p = p->next;
    }
    cout << title_search << " has been not found in the library." << endl;
    return;
}

void countBooks(library* l) {
    library* p = l;
    int countTitles = 0, countQuantity = 0;
    while (p != NULL) {
        countTitles++;
        countQuantity += p->quantity;
        p = p->next;
    }
    if (countQuantity > 0) {
        cout << "There " << (countTitles == 1 ? "is" : "are") << " " << countTitles << " distinct title" << (countTitles == 1 ? "" : "s") // using ternary operators (condition ? true_value : false_value) to make single/plural handling shorter and easier
            << " and " << countQuantity << " book" << (countQuantity == 1 ? "" : "s") << " in the library." << endl;
    }
    else {
        cout << "Library is empty." << endl;
    }
    return;
}

int main()
{
    cout << "Welcome to Library..." << endl;
    library* bookList{}; // create a list and initiate it
    char answer[10]{};
    do {
        cout << "Which of the actions: insert, list, remove, find, count and dismiss, do you wish to perform?" << endl;
        cin >> answer;
        cout << endl;
        switch (tolower(answer[0])) //take in only one first letter of user's input as an indicator of needed command to allow us use a more comfortable switch-case system
        {
        case ('i'): // Insert command case
            bookList = insertBook(bookList);
            break;
        case ('l'): // List command case
            listBooks(bookList);
            break;
        case ('r'): // Remove command case
            bookList = removeBook(bookList);
            break;
        case ('f'): // Find command case
            searchBook(bookList);
            break;
        case ('c'): // Count command case
            countBooks(bookList);
            break;
        case ('d'):
            break;
        default: // Error case if user entered invalid command
            cout << "Unvalid option. Retry." << endl;
            continue;
        }
    } while (tolower(answer[0]) != 'd'); // Dissmissing a programm if user gave such command
    // Cleaning up the memory
    while (bookList != nullptr) {
        library* temp = bookList;
        bookList = bookList->next;
        delete temp;
    }
}