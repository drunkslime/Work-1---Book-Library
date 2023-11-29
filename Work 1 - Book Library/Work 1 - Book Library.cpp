#include <iostream>
#include <sstream>
using namespace std;

struct library {
    char title[50], author[50], style[20];
    int code; int quantity;
    float price;
    library* next;
};

void listBooks(library* l) {
    if (l == NULL) {
        cout << "Library is empty." << endl;
        return;
    }

    library* p = l;

    while (p != NULL) {
        cout << p->code << "\t" << p->title << "\n";
        cout << "\t" << p->author << "\n";
        cout << "\t" << p->style << "\n";
        cout.precision(4); // set output for float to 2 floating numbers
        cout << "\t" << p->quantity << ": " << p->price << "€" << "\n";
        cout << endl;
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

    do // do-while loop to give user infinite amount of attempts just to make sure that it gets int value in the end
    {
        string temp;
        cout << "\nWhat's the ID for this book? ";
        cin >> temp;
        istringstream iss(temp); // inserted by <sstream>, attempts to convert into int

        if (iss >> p->code) { // if convertion  succeeded, eventually applies converted value into p->code and breaks the loop
            p->code = stoi(temp); //stoi = string to int
            break;
        }
        else { cout << "Invalid input. Please enter a valid integer.\n"; }
    } while (true);

    do // same here
    {
        string temp;
        cout << "\nHow much books do you want to insert? ";
        cin >> temp;
        istringstream iss(temp);

        if (iss >> p->quantity) {
            p->quantity = stoi(temp);
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

/*library* removeBook(library* l) {

}*/

bool searchBook(library* l) {
    library* p = l;
    char title_search[50]{};
    cout << "What title do you search for? ";
    cin.ignore();
    cin.getline(title_search, sizeof(title_search));
    while (p != NULL)
    {
        if (strcmp(p->title, title_search) == 0) {
            return true;
        }
        p = p->next;
    }
    return false;
}

int countBooks(library* l) {
    library* p = l;
    int count = 0;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

int main()
{
    cout << "Welcome to Library..." << endl;
    library* bookList{}; // create a list and initiate it
    char answer[10]{};
    do {
        cout << "Which of the actions: insert, list, remove, find, count and dismiss, do you wish to perform?" << endl;
        cin >> answer;
        switch (tolower(answer[0])) //take in only one first letter of user's input as an indicator of needed command to allow us use a more comfortable switch-case system
        {
        case ('i'): // Insert command case
            bookList = insertBook(bookList);
            break;
        case ('l'): // List command case
            listBooks(bookList);
            break;
        case ('r'): // Remove command case
            cout << "Removed" << endl;
            break;
        case ('f'): // Find command case
            if (searchBook(bookList)) {
                cout << "Book found." << endl;
            }
            else {
                cout << "Book not found." << endl;
            }
            break;
        case ('c'): // Count command case
            if (countBooks(bookList) != 0 and countBooks(bookList) != 1) {
                cout << "There's " << countBooks(bookList) << " books in the library." << endl;
            }
            else if (countBooks(bookList) == 1) {
                cout << "There's " << countBooks(bookList) << " book in the library." << endl;
            }
            else {
                cout << "Library is empty." << endl;
            }
            break;
        default: // Error case if user entered invalid command
            cout << "Unvalid option. Retry." << endl;
            continue;
        }
    } while (tolower(answer[0]) != 'd'); // Dissmissing a programm if user gave such command
}