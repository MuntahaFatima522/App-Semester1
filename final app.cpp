#include <iostream>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <iomanip>
using namespace std;

void setColor(int color); // sets the colour of output on console

void printHeader(); // prints header in main menu
void Header();      // prints header in sub menu
char Menu();        // displays main menu

bool adminLogin();  // checks the login of admin
char adminMenu();   // displays admin menu
int adminOptions(); // displays admin options
int adminEnd();     // appears at last of each admin option

int studentLogin();   // checks the login of students
char studentMenu();   // displays student menu
int studentOptions(); // displays student options
int studentEnd();     // appears at last of each student option

int Registeration();                    // registers new students
bool checkPassword(string StudentPass); // checks the validity of password while registeration

bool addBook();          // allows admin to add books
string searchBook();     // allows both admin and students to search book
string displayBooks();   // allows both admin ad students to display available book
bool deleteBook();       // allows admin to delete books
bool issueBook();        // allows admin to issue books
string displayHistory(); // allows admin to display the history of the issurd books

bool borrowBook();          // allows student to borrow book
bool displayStudentBooks(); // allows student to display their borrowed books
bool returnBook();          // allows students to return their borrowed books

bool checkValidity(string word); // checks the vlidity of student ID while login

string getField(string record, int field); // gets the record to separate them in fields
void readStudentData();                    // reads data from students file
void readBookData();                       // reads data from books file
void readStudentBookData();                // reads data from the file in which information of issued books and students is stored

int Last();
bool checkNumberValidity(string word);
int convertInInteger(string word);

int studentIndex;            // keeps track on which student has logged in to display his menu
const int maxBooks = 500;    // maximum books liabrary can keep
const int maxStudents = 500; // maximum students that can register

string books[maxBooks];      // stores the names of books
int booksQuantity[maxBooks]; // stores the copies of books

string students[maxStudents][2]; // stores two fields i.e. id and password

string studentBooks[maxStudents];      // stores the book borrowed by students
int studentBooksQuantity[maxStudents]; // stores the copies of books borrowed

string studentsBookID[maxStudents];            // stores the ID of students who have borrowed books
string studentBorrowedBooks[maxStudents];      // reads the data of borrowed books from StudentBook File
int studentBorrowedBooksQuantity[maxStudents]; // reads the data of borrowed books copies from StudentBook File

int BookIdx = 0;     // keeps track on books index after reading file
int StudentIdx = 0;  // keeps track on student index after reading file
int borrowedIdx = 0; // keeps track on borrowed book after reading the file

int main()
{
    
    setColor(3);
    printHeader();
    char option;
    option = Menu();
    system("cls");
    Header();
    if (option == '1')
    {
        setColor(3);

        cout << "You have entered option 1 i.e. Admin." << endl;
        cout << "--------------------------------------------------" << endl;
        cout << endl;
        if (adminLogin())
        {
            char key;
            system("cls");
            Header();
            setColor(3);
            cout << "ADMIN LOGIN >" << endl;
            cout << "----------------" << endl
                 << endl;
            cout << "Congratulations!!!! You have successfully logged in as admin..." << endl;
            cout << "------------------------------------------------------------------" << endl
                 << endl;
            cout << "Press 'm' to display menu..";
            cin >> key;
            if (key == 'm' || key == 'M')
            {
                adminOptions();
            }
            else
            {
                char option;
                cout << endl;
                setColor(3);
                cout << "Wrong option..." << endl
                     << endl;
                cout << "--------------------------------------------------" << endl;
                cout << "Choose one of the following options: " << endl;
                cout << "1. Main Menu." << endl;
                cout << "2. Exit." << endl;
                cout << "--------------------------------------------------" << endl;
                cout << "Your option: ";
                cin >> option;

                if (option == '1')
                {
                    main();
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            char option;
            cout << endl;
            setColor(3);
            cout << "Wrong Password..." << endl
                 << endl;
            cout << "Choose one of the following options: " << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "1. Main Menu." << endl;
            cout << "2. Exit." << endl;
            cout << "--------------------------------------------------" << endl;

            cout << "Your option: ";
            cin >> option;

            if (option == '1')
            {
                main();
            }
            else
            {
                return 0;
            }
        }
    }
    else if (option == '2')
    {
        setColor(3);

        cout << "You have entered option 2 i.e. Student." << endl;
        cout << "--------------------------------------------------" << endl

             << endl;
        studentLogin();
        /*linked with registeration() and not possible to write code in loop for proper functionality
        (because break and continue statements were not working prperly due to lengthy code) thats why remaining code is not in main().*/
    }
    else if (option == '3')
    {
        setColor(3);

        cout << "You have entered option 3 i.e. Not Registered." << endl;
        cout << "--------------------------------------------------" << endl

             << endl;
        Registeration();
        /*to write remaining code in main();the same code was repeating alot and furthermore,the code was not running properly
        effecting the efficiency of my application*/
    }
    else if (option == '4')
    {
        return 0;
    }
    else
    {
        char option;
        cout << endl;
        setColor(3);
        cout << "Wrong option..." << endl
             << endl;
        cout << "Choose one of the following options: " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Main Menu." << endl;
        cout << "2. Exit." << endl;
        cout << "--------------------------------------------------" << endl;

        cout << "Your option: ";
        cin >> option;

        if (option == '1')
        {
            main();
        }
        else
        {
            return 0;
        }
    }
}

void printHeader()
{
    system("cls");
    setColor(3);
    cout << "                                         _      _____ ____  _____            _______     __                                     " << endl;
    cout << "                                        | |    |_   _|  _ \\|  __ \\     /\\   |  __ \\ \\   / /                                " << endl;
    cout << "                                        | |      | | | |_) | |__) |   /  \\  | |__) \\ \\_/ /                                   " << endl;
    cout << "                                        | |      | | |  _ <|  _  /   / /\\ \\ |  _  / \\   /                                    " << endl;
    cout << "                                        | |____ _| |_| |_) | | \\ \\  / ____ \\| | \\ \\  | |                                   " << endl;
    cout << "                                __  __  |______|_____|____/|_| _\\_\\/_/____\\_\\_| _\\_\\_|_|_ _   _ _______                   " << endl;
    setColor(14);
    cout << "                               |  \\/  |   /\\   | \\ | |   /\\   / ____|  ____|  \\/  |  ____| \\ | |__   __|                  " << endl;
    cout << "                               | \\  / |  /  \\  |  \\| |  /  \\ | |  __| |__  | \\  / | |__  |  \\| |  | |                     " << endl;
    cout << "                               | |\\/| | / /\\ \\ | . ` | / /\\ \\| | |_ |  __| | |\\/| |  __| | . ` |  | |                     " << endl;
    cout << "                               | |  | |/ ____ \\| |\\  |/ ____ \\ |__| | |____| |  | | |____| |\\  |  | |                       " << endl;
    cout << "                               |_|  |_/_/   _\\_\\_|_\\_/_/____\\_\\_____|______|_| _|_|______|_| \\_|  |_|                     " << endl;
    setColor(3);
    cout << "                                           / ____\\ \\   / / ____|__   __|  ____|  \\/  |                                       " << endl;
    cout << "                                          | (___  \\ \\_/ / (___    | |  | |__  | \\  / |                                       " << endl;
    cout << "                                           \\___ \\  \\   / \\___ \\   | |  |  __| | |\\/| |                                    " << endl;
    cout << "                                           ____) |  | |  ____) |  | |  | |____| |  | |                                          " << endl;
    cout << "                                          |_____/   |_| |_____/   |_|  |______|_|  |_|                                          " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    setColor(7);
}

void Header()
{
    setColor(14);
    cout << "                               -----<<<< LIBRARY MANAGEMENT SYSTEM >>>>-----           " << endl;
    cout << endl;
    cout << endl;
    setColor(7);
}

char Menu()
{
    setColor(3);
    char option;
    cout << "Select one of the following options wordber: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1.\t Admin" << endl;
    cout << "2.\t Student" << endl;
    cout << "3.\t Not Registered" << endl;
    cout << "4.\t Exit." << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Your option: ";
    cin >> option;

    return option;
}

bool adminLogin()
{
    setColor(3);
    cout << "ADMIN LOGIN > " << endl;
    cout << "----------------" << endl
         << endl;
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    if (password == "admin_pass123")
    {
        return true;
    }
    else
    {
        return false;
    }
}

char adminMenu()
{
    setColor(3);
    cout << "ADMIN MENU >" << endl;
    cout << "----------------" << endl
         << endl;
    char option;

    cout << "Select one of the following options: " << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "1. Search for a book." << endl;
    cout << "2. Add a book." << endl;
    cout << "3. Delete a book." << endl;
    cout << "4. Display all books." << endl;
    cout << "5. Issue a book." << endl;
    cout << "6. Display History." << endl;
    cout << "7. Exit." << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Your option: ";
    cin >> option;
    return option;
}

int adminOptions()
{
    setColor(3);
    system("cls");
    Header();
    char option;
    option = adminMenu();
    system("cls");
    Header();
    if (option == '1')
    {
        cout << searchBook();

        adminEnd();
    }
    else if (option == '2')
    {

        if (addBook())
        {

            cout << "Book has been added successfully..." << endl;
        }
        else if (BookIdx >= maxBooks)
        {

            cout << "No more books can be added!!Delete some unnecesssary books to add new ones..." << endl;
        }
        adminEnd();
    }
    else if (option == '3')
    {
        if (deleteBook() == true)
        {

            cout << "Book has been deleted successfully..." << endl;
        }
        adminEnd();
    }
    else if (option == '4')
    {
        cout << displayBooks();
        adminEnd();
    }
    else if (option == '5')
    {

        if (issueBook())
        {
            cout << "Book has been issued successfully..." << endl;
        }
        adminEnd();
    }
    else if (option == '6')
    {
        cout << displayHistory();
        adminEnd();
    }
    else if (option == '7')
    {
        return 0;
    }
    else
    {
        setColor(3);
        cout << "Wrong option...";
        adminEnd();
    }
    return 0;
}

int adminEnd()
{
    char op;
    cout << endl
         << endl;
    setColor(3);

    cout << "Choose an option: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1. Main Menu " << endl;
    cout << "2. Admin Menu " << endl;
    cout << "3. Exit " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Your option: ";
    cin >> op;
    system("cls");
    Header();
    if (op == '1')
    {
        main();
    }
    else if (op == '2')
    {
        adminOptions();
    }
    else if (op == '3')
    {
        return 0;
    }
    else
    {
        char option;
        cout << endl;
        cout << "Wrong option..." << endl
             << endl;
        cout << "Choose one of the following options: " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Main Menu." << endl;
        cout << "2. Exit." << endl;
        cout << "--------------------------------------------------" << endl;

        cout << "Your option: ";
        cin >> option;

        if (option == '1')
        {
            main();
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int studentLogin()
{
    setColor(3);
    cout << "STUDENT LOGIN >" << endl;
    cout << "----------------" << endl
         << endl;
    readStudentData(); // reads the data from student file
    string ID;
    bool isIDPresent = false;
    cout << "Enter Student ID: ";
    cin.ignore();
    getline(cin, ID);
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < StudentIdx; i++)
    {
        if (ID == students[i][0])
        {
            isIDPresent = true;
            break;
        }
    }
    if (!isIDPresent)
    {
        setColor(3);

        cout << "This ID is not registered.." << endl
             << endl;
        char option;
        cout << "Select one of the following options: " << endl;
        cout << "--------------------------------------------------" << endl;

        cout << "1. Again Log-in." << endl;
        cout << "2. Register." << endl;
        cout << "3. Exit." << endl;
        cout << "--------------------------------------------------" << endl;

        cout << "Your option: ";
        cin >> option;
        system("cls");
        Header();
        if (option == '1')
        {
            studentLogin();
        }
        else if (option == '2')
        {
            Registeration();
        }
        else if (option == '3')
        {
            return 0;
        }
        else
        {
            setColor(3);

            char option;
            cout << endl;
            cout << "Wrong option..." << endl
                 << endl;
            cout << "Choose one of the following options: " << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "1. Main Menu." << endl;
            cout << "2. Exit." << endl;
            cout << "--------------------------------------------------" << endl;

            cout << "Your option: ";
            cin >> option;

            if (option == '1')
            {
                main();
            }
            else
            {
                return 0;
            }
        }
    }
    else
    {
        setColor(3);

        string password;
        cout << "Enter password: ";
        cin >> password;
        cout << "--------------------------------------------------" << endl;
        bool successfulLogin = false;
        for (int i = 0; i < StudentIdx; i++)
        {
            if (ID == students[i][0] && password == students[i][1])
            {
                successfulLogin = true;
                studentIndex = i;
                break;
            }
        }
        if (successfulLogin)
        {
            setColor(3);

            char key;
            system("cls");
            Header();
        setColor(3);
            cout << "STUDENT LOGIN >" << endl;
            cout << "----------------" << endl
                 << endl;
            cout << "|  Welcome  " << students[studentIndex][0] << "!!!  |" << endl;
            cout << endl
                 << endl;
            cout << "Congratulations!!!! You have successfully logged in as " << students[studentIndex][0] << endl;
            cout << "------------------------------------------------------------------" << endl
                 << endl;
            cout << "Press 'm' to display menu..";
            cin >> key;
            if (key == 'm' || key == 'M')
            {
                studentOptions();
            }
            else
            {
                setColor(3);

                char option;
                cout << endl;
                cout << "Wrong option.." << endl
                     << endl;
                cout << "Choose one of the following options: " << endl;
                cout << "--------------------------------------------------" << endl;
                cout << "1. Main Menu." << endl;
                cout << "2. Exit." << endl;
                cout << "--------------------------------------------------" << endl;

                cout << "Your option: ";
                cin >> option;
                if (option == '1')
                {
                    main();
                }
                else
                {
                    return 0;
                }
            }
        }
        else
        {
            system("cls");
            Header();
            setColor(3);

            cout << "STUDENT LOGIN >" << endl;
            cout << "----------------" << endl
                 << endl;
            char option;
            cout << "Incorrect password..." << endl
                 << endl;

            cout << "Select one of the following options: " << endl;
            cout << "--------------------------------------------------" << endl;

            cout << "1. Again Log-in." << endl;
            cout << "2. Register." << endl;
            cout << "3. Exit." << endl;
            cout << "--------------------------------------------------" << endl;

            cout << "Your option: ";
            cin >> option;
            system("cls");
            Header();
            if (option == '1')
            {
                studentLogin();
            }
            else if (option == '2')
            {
                Registeration();
            }
            else if (option == '3')
            {
                return 0;
            }
            else
            {
                char option;
                cout << endl;
                setColor(3);

                cout << "Wrong option..." << endl
                     << endl;
                cout << "Choose one of the following options: " << endl;
                cout << "--------------------------------------------------" << endl;
                cout << "1. Main Menu." << endl;
                cout << "2. Exit." << endl;
                cout << "--------------------------------------------------" << endl;

                cout << "Your option: ";
                cin >> option;

                if (option == '1')
                {
                    main();
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    return 0;
}

char studentMenu()
{
    setColor(3);
    char option;
    cout << "STUDENT MENU >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "Select one of the following options: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1. Search for a book." << endl;
    cout << "2. Borrow a book." << endl;
    cout << "3. Return a book." << endl;
    cout << "4. Display all books." << endl;
    cout << "5. Display my borrowed books." << endl;
    cout << "6. Exit." << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Your option: ";
    cin >> option;
    return option;
}

int studentOptions()
{
    setColor(3);

    system("cls");
    Header();
    char option;
    option = studentMenu();
    system("cls");
    Header();
    if (option == '1')
    {
        cout << searchBook();
        studentEnd();
    }
    else if (option == '2')
    {

        if (borrowBook())
        {
            cout << "Book has been borrowed successfully..." << endl;
        }
        studentEnd();
    }
    else if (option == '3')
    {
        if (returnBook())
        {
            cout << "Book has been returned successfully..." << endl;
        }

        studentEnd();
    }
    else if (option == '4')
    {

        cout << displayBooks();
        studentEnd();
    }
    else if (option == '5')
    {
        if (displayStudentBooks())
        {
            cout << endl
                 << "Your borrowed books have been displayed..." << endl;
        }
        else
        {
            cout << endl;
            cout << "You have not borrowed any book..." << endl;
        }

        studentEnd();
    }
    else if (option == '6')
    {
        return 0;
    }
    else
    {
        setColor(3);
        cout << "Wrong option...";
        studentEnd();
    }
    return 0;
}

int studentEnd()
{
    char op;
    cout << endl
         << endl;
    setColor(3);

    cout << "Choose an option: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1. Main Menu " << endl;
    cout << "2. Student Menu " << endl;
    cout << "3. Exit " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Your option: ";
    cin >> op;
    system("cls");
    Header();
    if (op == '1')
    {
        main();
    }
    else if (op == '2')
    {
        studentOptions();
    }
    else if (op == '3')
    {
        return 0;
    }
    else
    {
        char option;
        cout << endl;
        cout << "Wrong option..." << endl
             << endl;
        cout << "Choose one of the following options: " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Main Menu." << endl;
        cout << "2. Exit." << endl;
        cout << "--------------------------------------------------" << endl;

        cout << "Your option: ";
        cin >> option;

        if (option == '1')
        {
            main();
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int Registeration()
{
    setColor(3);

    cout << "REGISTERATION >" << endl;
    cout << "----------------" << endl
         << endl;
    bool isValid = true;
    if (StudentIdx < maxStudents)
    {

        readStudentData();
        cout << "Choose your ID: ";
        cin.ignore();
        getline(cin, students[StudentIdx][0]);
        string ID = students[StudentIdx][0];
        for (int i = 0; i < StudentIdx; i++)
        {
            if (ID == students[i][0])
            {
                cout << "This ID already exists..Choose another one..." << endl;
                isValid = false;
                break;
            }
        }
        if (!checkValidity(ID))
        {
            cout << "This ID is not proper..." << endl;
            cout << "Try again..." << endl
                 << endl;
            isValid = false;
        }
        if (!isValid)
        {
            char option;
            cout << "Select one of the following options: " << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "1. Again Register." << endl;
            cout << "2. Exit." << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "Your option: ";
            cin >> option;
            if (option == '1')
            {
                system("cls");
                Header();
                Registeration();
            }
            else
            {
                return 0;
            }
        }
        else
        {
            cout << "Choose your password: ";
            cin >> students[StudentIdx][1];
            string password = students[StudentIdx][1];
            bool result = checkPassword(password);
            for (int i = 0; i < StudentIdx; i++)
            {
                if (password == students[i][1])
                {
                    cout << "This Password already exists..Choose another one..." << endl;
                    char option;
                    cout << "Select one of the following options: " << endl;
                    cout << "--------------------------------------------------" << endl;

                    cout << "1. Again Register." << endl;
                    cout << "2. Exit." << endl;
                    cout << "--------------------------------------------------" << endl;

                    cout << "Your option: ";
                    cin >> option;
                    if (option == '1')
                    {
                        system("cls");
                        Header();
                        Registeration();
                    }
                    else
                    {
                        return 0;
                    }
                    break;
                }
            }
            if (result == true)
            {
                system("cls");
                Header();
        setColor(3);

                cout << "REGISTERATION >" << endl;
                cout << "----------------" << endl
                     << endl;
                cout << "Strong password!!!!Successfully registered..." << endl;
                fstream StudentFile;
                StudentFile.open("StudentFile.txt", ios::app);
                StudentFile << ID << "," << password << endl;
                StudentFile.close();
                StudentIdx++;
                char option;
                cout << "Select one of the following options: " << endl;
                cout << "--------------------------------------------------" << endl;

                cout << "1.  Log in." << endl;
                cout << "2. Main menu." << endl;
                cout << "3.  Exit." << endl;
                cout << "--------------------------------------------------" << endl;

                cout << "Your option: ";
                cin >> option;
                system("cls");
                Header();
                if (option == '1')
                {
                    studentLogin();
                }
                else if (option == '2')
                {
                    main();
                }
                else if (option == '3')
                {
                    return 0;
                }
                else
                {
                    char option;
                    cout << endl;
                    cout << "Wrong option..." << endl
                         << endl;
                    cout << "Choose one of the following options: " << endl;
                    cout << "--------------------------------------------------" << endl;
                    cout << "1. Main Menu." << endl;
                    cout << "2. Exit." << endl;
                    cout << "--------------------------------------------------" << endl;

                    cout << "Your option: ";
                    cin >> option;

                    if (option == '1')
                    {
                        main();
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
            else
            {
                system("cls");
                Header();
        setColor(3);

                cout << "REGISTERATION >" << endl;
                cout << "----------------" << endl
                     << endl;
                cout << "Password is not strong..." << endl;
                char option;
                cout << "Select one of the following options: " << endl;
                cout << "--------------------------------------------------" << endl;

                cout << "1. Again Register." << endl;
                cout << "2. Exit." << endl;
                cout << "--------------------------------------------------" << endl;

                cout << "Your option: ";
                cin >> option;
                if (option == '1')
                {
                    system("cls");
                    Header();
                    Registeration();
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    else
    {
        setColor(3);

        cout << "You cannot register..." << endl;
    }
    return 0;
}

bool checkPassword(string StudentPass)
{
    bool hasDigit = false;
    bool hasAlphabet = false;
    bool hasCharacter = false;
    for (int x = 0; StudentPass[x] != '\0'; x++)
    {
        if (StudentPass[x] >= '0' && StudentPass[x] <= '9')
        {
            hasDigit = true;
        }
        if ((StudentPass[x] >= 'A' && StudentPass[x] <= 'Z') || (StudentPass[x] >= 'a' && StudentPass[x] <= 'z'))
        {
            hasAlphabet = true;
        }
        if (StudentPass[x] == '/' || StudentPass[x] == '_' || StudentPass[x] >= '.' || StudentPass[x] == '@' || StudentPass[x] == '*' || StudentPass[x] == '+' || StudentPass[x] == '-' || StudentPass[x] == '&' || StudentPass[x] == '^' || StudentPass[x] == '!' || StudentPass[x] == '%' || StudentPass[x] == '#' || StudentPass[x] == ';' || StudentPass[x] == '>' || StudentPass[x] == '<')
        {
            hasCharacter = true;
        }
    }

    return (hasDigit && hasAlphabet && hasCharacter);
}

bool addBook()
{
    BookIdx = 0;
    readBookData();
    string addBook;
    string quantity;
    int addBookQuantity;
    bool isPresent = false;
    int index;
    bool result = false;
    setColor(3);
    cout << "You have entered option 2 (to add a book)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "ADD BOOK >" << endl;
    cout << "----------------" << endl
         << endl;
    if (BookIdx < maxBooks)
    {
        cout << "Enter the name of the book you want to add: ";
        cin >> addBook;
        cout << "--------------------------------------------------" << endl;

        if (checkValidity(addBook))
        {
            cout << "Enter the copies of book you want to add: ";
            cin >> quantity;
            cout << "--------------------------------------------------" << endl
                 << endl;
            if (checkNumberValidity(quantity))
            {
                addBookQuantity = convertInInteger(quantity);
                for (int i = 0; i < BookIdx; i++)
                {
                    if (addBook == books[i])
                    {
                        isPresent = true;
                        index = i;
                        break;
                    }
                }
                if (isPresent)
                {
                    booksQuantity[index] = booksQuantity[index] + addBookQuantity;
                    fstream BooksFile;
                    BooksFile.open("BooksFile.txt", ios::out);
                    for (int i = 0; i < BookIdx; i++)
                    {
                        BooksFile << books[i] << "," << booksQuantity[i] << endl;
                    }
                    BooksFile.close();
                }
                else
                {
                    books[BookIdx] = addBook;
                    booksQuantity[BookIdx] = addBookQuantity;
                    fstream BooksFile;
                    BooksFile.open("BooksFile.txt", ios::app);
                    BooksFile << books[BookIdx] << "," << booksQuantity[BookIdx] << endl;
                    BooksFile.close();
                    BookIdx++;
                }
                result = true;
            }

            else
            {
                cout << "Enter only numeric data for copies of books..." << endl;
            }
        }

        else
        {
            cout << "Enter proper book name..." << endl;
            Last();
        }
    }

    return result;
}

string searchBook()
{
    setColor(3);

    BookIdx = 0;
    readBookData();
    int index;
    string bookName;
    string result;
    cout << "You have entered option 1 (to search for a book)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "SEARCH BOOK >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "Enter the name of the book you want to search: ";
    cin >> bookName;
    cout << "--------------------------------------------------" << endl
         << endl;
    if (checkValidity(bookName))
    {
        bool isPresent = false;
        for (int i = 0; i < BookIdx; i++)
        {
            if (bookName == books[i])
            {
                index = i;
                isPresent = true;
                break;
            }
        }
        if (isPresent == true)
        {
            result = "Yes!!! " + to_string(booksQuantity[index]) + " copies of this book are available..";
        }
        else
        {
            result = "No!!! this book is not available..";
        }
    }
    else
    {
        cout << "Enter proper book name..." << endl;
        Last();
    }
    return result;
}

bool deleteBook()
{
    setColor(3);

    BookIdx = 0;
    readBookData();
    string deleteBook;
    int deleteBookQuantity;
    string quantity;
    bool deleted = false;
    bool isPresent = false;
    cout << "You have entered option 3 (to delete a book)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "DELETE BOOK >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "Enter the name of the book you want to delete: ";
    cin >> deleteBook;
    cout << "--------------------------------------------------" << endl;
    if (checkValidity(deleteBook))
    {
        cout << "Enter the copies of book you want to delete: ";
        cin >> quantity;
        cout << "--------------------------------------------------" << endl
             << endl;
        if (checkNumberValidity(quantity))
        {
            int i;
            deleteBookQuantity = convertInInteger(quantity);
            for (int y = 0; y < BookIdx; y++)
            {
                if (deleteBook == books[y])
                {
                    isPresent = true;
                    i = y;
                    break;
                }
            }
            if (isPresent)
            {
                booksQuantity[i] = booksQuantity[i] - deleteBookQuantity;
                if (booksQuantity[i] <= 0)
                {
                    books[i] = "0";
                }
                deleted = true;
            }
            else
            {
                cout << "Book not found..." << endl;
            }
            fstream BooksFile;
            BooksFile.open("BooksFile.txt", ios::out);
            for (int j = 0; j < BookIdx; j++)
            {
                if (books[j] != "0") // Skip books marked for deletion
                {
                    BooksFile << books[j] << "," << booksQuantity[j] << endl;
                }
            }
            BooksFile.close();
        }
        else
        {
            cout << "Enter only numeric data for copies of books..." << endl;
        }
    }
    else
    {
        cout << "Enter proper book name..." << endl;
        Last();
    }
    return deleted;
}

string displayBooks()
{
    setColor(3);

    BookIdx = 0;
    readBookData();
    cout << "You have entered option 4 (to display all books)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "DISPLAY BOOKS >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "All available books are: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << left << setw(15) << "Book Name" << setw(15) << "    :    " << setw(15) << "Copies" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < BookIdx; i++)
    {
        cout << left << setw(15) << books[i] << setw(15) << "    :    " << setw(15) << booksQuantity[i] << endl;
        cout << "--------------------------------------------------" << endl;
    }
    string result = "\nAll available books have been displayed..\n";
    return result;
}

bool issueBook()
{
    setColor(3);

    BookIdx = 0;
    StudentIdx = 0;
    readStudentData();
    readBookData();
    string issueBook;
    string issueStudent;
    bool issued = false;
    int issueBookQuantity;
    string quantity;
    cout << "You have entered option 5 (to issue a book)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "ISSUE BOOK >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "Enter the name of the book you want to issue: ";
    cin >> issueBook;
    cout << "--------------------------------------------------" << endl;
    if (checkValidity(issueBook))
    {
        bool isBookPresent = false;
        for (int i = 0; i < BookIdx; i++)
        {
            if (issueBook == books[i])
            {
                isBookPresent = true;
                break;
            }
        }
        if (isBookPresent)
        {
            cout << "Enter the copies of the book you want to issue: ";
            cin >> quantity;
            cout << "--------------------------------------------------" << endl;
            if (checkNumberValidity(quantity))
            {
                issueBookQuantity = convertInInteger(quantity);
                cout << "Enter the name of student to whom the book is being issued: ";
                cin.ignore();

                getline(cin, issueStudent);
                cout << "--------------------------------------------------" << endl
                     << endl;
                bool isStudentPresent = false;
                for (int i = 0; i < StudentIdx; i++)
                {
                    if (issueStudent == students[i][0])
                    {
                        isStudentPresent = true;
                        break;
                    }
                }
                if (isStudentPresent)
                {
                    bool isAlreadyIssued = false;
                    for (int i = 0; i < BookIdx; i++)
                    {
                        if (issueBook == books[i])
                        {
                            for (int j = 0; j < StudentIdx; j++)
                            {
                                int x;
                                if (issueStudent == students[j][0])
                                {
                                    borrowedIdx = 0;
                                    readStudentBookData();
                                    for (int index = 0; index < borrowedIdx; index++)
                                    {
                                        if (issueStudent == studentsBookID[index] && issueBook == studentBorrowedBooks[index])
                                        {
                                            isAlreadyIssued = true;
                                            x = index;
                                            break;
                                        }
                                    }
                                    if (isAlreadyIssued)
                                    {
                                        if (booksQuantity[i] >= issueBookQuantity)
                                        {
                                            booksQuantity[i] = booksQuantity[i] - issueBookQuantity;
                                            studentBorrowedBooksQuantity[x] += issueBookQuantity;
                                        }
                                        else
                                        {
                                            cout << "Only " << booksQuantity[i] << " of this book are available which have been issued..." << endl;
                                            cout << "-------------------------------------------------------------------------------------" << endl;

                                            studentBorrowedBooksQuantity[x] += booksQuantity[i];
                                            booksQuantity[i] = 0;
                                        }
                                        if (booksQuantity[i] == 0)
                                        {
                                            books[i] = "0";
                                        }
                                        fstream BooksFile;
                                        BooksFile.open("BooksFile.txt", ios::out);
                                        for (int k = 0; k < BookIdx; k++)
                                        {
                                            if (books[k] != "0") // Skip books marked for deletion
                                            {
                                                BooksFile << books[k] << "," << booksQuantity[k] << endl;
                                            }
                                        }
                                        BooksFile.close();
                                        fstream StudentBook;
                                        StudentBook.open("StudentBook.txt", ios::out);
                                        for (int y = 0; y < borrowedIdx; y++)
                                        {
                                            StudentBook << studentsBookID[y] << "," << studentBorrowedBooks[y] << "," << studentBorrowedBooksQuantity[y] << endl;
                                        }
                                        StudentBook.close();
                                        issued = true;
                                        break;
                                    }
                                    else
                                    {
                                        studentBooks[j] = issueBook;
                                        if (booksQuantity[i] >= issueBookQuantity)
                                        {
                                            booksQuantity[i] = booksQuantity[i] - issueBookQuantity;
                                            studentBooksQuantity[j] = issueBookQuantity;
                                        }
                                        else
                                        {
                                            cout << "Only " << booksQuantity[i] << " of this book are available which have been issued.." << endl;
                                            cout << "-------------------------------------------------------------------------------------" << endl;

                                            studentBooksQuantity[i] = booksQuantity[i];
                                            booksQuantity[i] = 0;
                                        }
                                        if (booksQuantity[i] == 0)
                                        {
                                            books[i] = "0";
                                        }
                                        fstream BooksFile;
                                        BooksFile.open("BooksFile.txt", ios::out);
                                        for (int k = 0; k < BookIdx; k++)
                                        {
                                            if (books[k] != "0") // Skip books marked for deletion
                                            {
                                                BooksFile << books[k] << "," << booksQuantity[k] << endl;
                                            }
                                        }
                                        BooksFile.close();
                                        fstream StudentBook;
                                        StudentBook.open("StudentBook.txt", ios::app);
                                        StudentBook << students[j][0] << "," << studentBooks[j] << "," << studentBooksQuantity[j] << endl;
                                        StudentBook.close();
                                        issued = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (issued)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    cout << "This student is not registered..." << endl;
                    Last();
                }
            }

            else
            {
                cout << "Enter only numeric data for copies of books..." << endl;
            }
        }
        else if (!isBookPresent)
        {
            cout << "This book is not available..." << endl;
        }
    }
    else
    {
        cout << "Enter proper book name..." << endl;
        Last();
    }
    return issued;
}

string displayHistory()
{
    setColor(3);

    borrowedIdx = 0;
    readStudentBookData();
    cout << "You have entered option 7 (to display history)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl
         << endl;
    cout << "DISPLAY HISTORY >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << left << setw(15) << "Student" << setw(15) << "Book" << setw(15) << "Copies" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < borrowedIdx; i++)
    {
        cout << left << setw(15) << studentsBookID[i] << setw(15) << studentBorrowedBooks[i] << setw(15) << studentBorrowedBooksQuantity[i] << endl;
        cout << "---------------------------------------------------" << endl;
    }

    string result = "\n\nHistory has been displayed...\n";
    return result;
}

bool borrowBook()
{
    setColor(3);

    BookIdx = 0;
    readBookData();
    string borrowBook;
    int borrowBookQuantity;
    string quantity;
    bool borrowed = false;
    cout << "You have entered option 2 (to borrow a book)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "BORROW BOOK >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "Enter the name of the book you want to borrow: ";
    cin >> borrowBook;
    cout << "--------------------------------------------------" << endl;
    if (checkValidity(borrowBook))
    {
        bool isBookPresent = false;
        for (int i = 0; i < BookIdx; i++)
        {
            if (borrowBook == books[i])
            {
                isBookPresent = true;
                break;
            }
        }
        if (isBookPresent)
        {
            cout << "Enter the number of copies you want to borrow: ";
            cin >> quantity;
            cout << "--------------------------------------------------" << endl
                 << endl;
            if (checkNumberValidity(quantity))
            {
                borrowBookQuantity = convertInInteger(quantity);
                string borrowStudent = students[studentIndex][0];
                bool isAlreadyBorrowed = false;
                for (int i = 0; i < BookIdx; i++)
                {
                    if (borrowBook == books[i])
                    {
                        borrowedIdx = 0;
                        readStudentBookData();
                        int x;
                        for (int index = 0; index < borrowedIdx; index++)
                        {
                            if (borrowStudent == studentsBookID[index] && borrowBook == studentBorrowedBooks[index])
                            {
                                isAlreadyBorrowed = true;
                                x = index;
                                break;
                            }
                        }
                        if (isAlreadyBorrowed)
                        {
                            if (booksQuantity[i] >= borrowBookQuantity)
                            {
                                booksQuantity[i] = booksQuantity[i] - borrowBookQuantity;
                                studentBorrowedBooksQuantity[x] += borrowBookQuantity;
                            }
                            else
                            {
                                cout << "Only " << booksQuantity[i] << " of this book are available which have been borrowed..." << endl;
                                cout << "-------------------------------------------------------------------------------------" << endl;

                                studentBorrowedBooksQuantity[x] += booksQuantity[i];
                                booksQuantity[i] = 0;
                            }
                            if (booksQuantity[i] == 0)
                            {
                                books[i] = "0";
                            }
                            fstream BooksFile;
                            BooksFile.open("BooksFile.txt", ios::out);
                            for (int k = 0; k < BookIdx; k++)
                            {
                                if (books[k] != "0") // Skip books marked for deletion
                                {
                                    BooksFile << books[k] << "," << booksQuantity[k] << endl;
                                }
                            }
                            BooksFile.close();
                            fstream StudentBook;
                            StudentBook.open("StudentBook.txt", ios::out);
                            for (int y = 0; y < borrowedIdx; y++)
                            {
                                StudentBook << studentsBookID[y] << "," << studentBorrowedBooks[y] << "," << studentBorrowedBooksQuantity[y] << endl;
                            }
                            StudentBook.close();
                            borrowed = true;
                            break;
                        }
                        else
                        {
                            studentBooks[studentIndex] = borrowBook;
                            if (booksQuantity[i] >= borrowBookQuantity)
                            {
                                booksQuantity[i] = booksQuantity[i] - borrowBookQuantity;
                                studentBooksQuantity[studentIndex] = borrowBookQuantity;
                            }
                            else
                            {
                                cout << "Only " << booksQuantity[i] << " of this book are available which have been borrowed..." << endl;
                                cout << "-------------------------------------------------------------------------------------" << endl;

                                studentBooksQuantity[studentIndex] = booksQuantity[i];
                                booksQuantity[i] = 0;
                            }
                            if (booksQuantity[i] == 0)
                            {
                                books[i] = "0";
                            }
                            fstream BooksFile;
                            BooksFile.open("BooksFile.txt", ios::out);
                            for (int k = 0; k < BookIdx; k++)
                            {
                                if (books[k] != "0") // Skip books marked for deletion
                                {
                                    BooksFile << books[k] << "," << booksQuantity[k] << endl;
                                }
                            }
                            BooksFile.close();
                            fstream StudentBook;
                            StudentBook.open("StudentBook.txt", ios::app);
                            StudentBook << students[studentIndex][0] << "," << studentBooks[studentIndex] << "," << studentBooksQuantity[studentIndex] << endl;
                            StudentBook.close();
                            borrowed = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << "Enter only numeric data for copies of books..." << endl;
            }
        }
        else
        {
            cout << "This book is not available..." << endl;
        }
    }
    else
    {
        cout << "Enter proper book name..." << endl;
        Last();
    }
    return borrowed;
}

bool returnBook()
{
    setColor(3);

    bool isReturned = false;
    borrowedIdx = 0;
    BookIdx = 0;
    readBookData();
    readStudentBookData();
    bool isPresent = false;
    int index;
    string returnBook;
    int returnBookQuantity;
    string quantity;
    bool isBookBorrowed = false;
    cout << "You have entered option 3 (to return a book)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "RETURN BOOK >" << endl;
    cout << "----------------" << endl
         << endl;

    cout << "Enter the name of book you want to return: ";
    cin >> returnBook;
    cout << "--------------------------------------------------" << endl;
    if (checkValidity(returnBook))
    {
        cout << "Enter the copies of book you want to return: ";
        cin >> quantity;
        cout << "--------------------------------------------------" << endl
             << endl;
        if (checkNumberValidity(quantity))
        {
            int x;
            returnBookQuantity = convertInInteger(quantity);
            for (int y = 0; y < borrowedIdx; y++)
            {
                if (studentsBookID[y] == students[studentIndex][0])
                {
                    if (studentBorrowedBooks[y] == returnBook)
                    {
                        isBookBorrowed = true;
                        x = y;
                        break;
                    }
                }
            }
            if (isBookBorrowed)
            {
                for (int i = 0; i < BookIdx; i++)
                {
                    if (returnBook == books[i])
                    {
                        index = i;
                        isPresent = true;
                        break;
                    }
                }
                if (isPresent)
                {
                    if (returnBookQuantity <= studentBorrowedBooksQuantity[x])
                    {
                        booksQuantity[index] = booksQuantity[index] + returnBookQuantity;
                        studentBorrowedBooksQuantity[x] = studentBorrowedBooksQuantity[x] - returnBookQuantity;
                    }
                    else
                    {
                        cout << "You have " << studentBorrowedBooksQuantity[x] << " copies of the books which have been returned..." << endl;
                        cout << "-------------------------------------------------------------------------------------------------------------" << endl;

                        booksQuantity[index] = booksQuantity[index] + studentBorrowedBooksQuantity[x];
                        studentBorrowedBooksQuantity[x] = 0;
                    }
                }
                else
                {
                    if (returnBookQuantity <= studentBorrowedBooksQuantity[x])
                    {
                        books[BookIdx] = returnBook;
                        booksQuantity[BookIdx] = returnBookQuantity;
                        BookIdx++;
                        studentBorrowedBooksQuantity[x] = studentBorrowedBooksQuantity[x] - returnBookQuantity;
                    }
                    else
                    {
                        cout << "You have " << studentBorrowedBooksQuantity[x] << " copies of the books which have been returned..." << endl;
                        cout << "-------------------------------------------------------------------------------------------------------------" << endl;

                        books[BookIdx] = returnBook;
                        booksQuantity[BookIdx] = studentBorrowedBooksQuantity[x];
                        BookIdx++;
                        studentBorrowedBooksQuantity[x] = 0;
                    }
                }
                if (studentBorrowedBooksQuantity[x] == 0)
                {
                    studentBorrowedBooks[x] = "0";
                }
                fstream BooksFile;
                BooksFile.open("BooksFile.txt", ios::out);
                for (int k = 0; k < BookIdx; k++)
                {
                    if (books[k] != "0") // Skip books marked for deletion
                    {
                        BooksFile << books[k] << "," << booksQuantity[k] << endl;
                    }
                }
                BooksFile.close();
                fstream StudentBook;
                StudentBook.open("StudentBook.txt", ios::out);
                for (int x = 0; x < borrowedIdx; x++)
                {
                    if (studentBorrowedBooks[x] != "0" && studentBorrowedBooksQuantity[x] != 0)
                    {
                        StudentBook << studentsBookID[x] << "," << studentBorrowedBooks[x] << "," << studentBorrowedBooksQuantity[x] << endl;
                    }
                }
                StudentBook.close();

                isReturned = true;
            }
            else
            {
                cout << "You have not borrowed this book..." << endl;
            }
        }
        else
        {
            cout << "Enter only numeric data for copies of books..." << endl;
        }
    }

    else
    {
        cout << "Enter proper book name..." << endl;
        Last();
    }

    return isReturned;
}

bool displayStudentBooks()
{
    setColor(3);

    borrowedIdx = 0;
    readStudentBookData();
    bool displayed = false;
    cout << "You have entered option 5 (to display your borrowed books)..." << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
    cout << "DISPLAY YOUR BORROWED BOOKS >" << endl;
    cout << "----------------" << endl
         << endl;
    cout << "Your borrowed books are: " << endl
         << endl;
    cout << "--------------------------------------------------" << endl;
    cout << left << setw(15) << "Book Name" << setw(15) << " : " << setw(15) << "Copies" << endl;
    cout << "--------------------------------------------------" << endl;
    for (int i = 0; i < borrowedIdx; i++)
    {
        if (studentsBookID[i] == students[studentIndex][0])
        {
            cout << left << setw(15) << studentBorrowedBooks[i] << setw(15) << " : " << setw(15) << studentBorrowedBooksQuantity[i] << endl;
            cout << "--------------------------------------------------" << endl;
            displayed = true;
        }
    }
    return displayed;
}

int Last()
{
    setColor(3);

    char option;
    cout << endl
         << endl;
    cout << "Choose one of the following options: " << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "1. Main Menu." << endl;
    cout << "2. Exit." << endl;
    cout << "--------------------------------------------------" << endl;

    cout << "Your option: ";
    cin >> option;

    if (option == '1')
    {
        main();
    }
    else
    {
        return 0;
    }
}
bool checkValidity(string word)
{
    bool result = true;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (!((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || (word[i] == ' ')))
        {
            result = false;
        }
    }
    return result;
}

string getField(string record, int field)
{
    int commaCount = 1;
    string item;
    int length = record.length();
    for (int x = 0; x < length; x++)
    {
        if (record[x] == ',')
        {
            commaCount++;
        }
        else if (commaCount == field)
        {
            item += record[x];
        }
    }
    return item;
}

void readStudentData()
{
    string record;
    fstream StudentFile;
    StudentFile.open("StudentFile.txt", ios::in);
    while (!(StudentFile.eof()))
    {
        getline(StudentFile, record);
        students[StudentIdx][0] = getField(record, 1);
        students[StudentIdx][1] = getField(record, 2);
        StudentIdx++;
    }
}
void readStudentBookData()
{
    string record;
    fstream StudentBook;
    StudentBook.open("StudentBook.txt", ios::in);
    while (!(StudentBook.eof()))
    {
        getline(StudentBook, record);
        studentsBookID[borrowedIdx] = getField(record, 1);
        studentBorrowedBooks[borrowedIdx] = getField(record, 2);
        string quantity = getField(record, 3);
        try
        {
            studentBorrowedBooksQuantity[borrowedIdx] = stoi(quantity);
        }
        catch (const invalid_argument &e)
        {
            continue;
        }
        borrowedIdx++;
    }
}

void readBookData()
{
    string record;
    fstream BooksFile;
    BooksFile.open("BooksFile.txt", ios::in);
    while (!(BooksFile.eof()))
    {
        getline(BooksFile, record);
        books[BookIdx] = getField(record, 1);
        string quantity = getField(record, 2);
        try
        {
            booksQuantity[BookIdx] = stoi(quantity);
        }
        catch (const invalid_argument &e)
        {
            continue;
        }
        BookIdx++;
    }
    BooksFile.close();
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool checkNumberValidity(string num)
{
    bool result = true;
    for (int i = 0; num[i] != '\0'; i++)
    {
        if (!((num[i] >= '0' && num[i] <= '9')))
        {
            result = false;
        }
    }
    return result;
}

int convertInInteger(string num)
{
    int result;
    result = stoi(num);
    return result;
}