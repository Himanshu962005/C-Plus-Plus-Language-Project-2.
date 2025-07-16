#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <iomanip>
using namespace std;

void waitAndClear()
{
    cout << "Press Enter to continue...";
    cin.get();
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Structure to represent a food item.
struct FoodItem
{
    string name;
    double price;
};

// Structure to represent a food stall.
struct Stall
{
    string name;
    string id; // used as username for login.
    string mobile;
    string email;
    string uniqueID;
    int type; // 1:South-Indian.,2:Continental.,3:Chinese.,4:Thailand.,5:Multiple.
    string password;
    string recovery;
    vector<FoodItem> menu;
};

// Function prototypes.
void loadStalls(const string &filename, vector<Stall> &stalls);
void saveStalls(const string &filename, const vector<Stall> &stalls);
void adminPortal(vector<Stall> &stalls);
void foodStallPortal(vector<Stall> &stalls);
void customerPortal(const vector<Stall> &stalls);
void addSingleStall(vector<Stall> &stalls);
void addMultipleStalls(vector<Stall> &stalls);
void viewStalls(const vector<Stall> &stalls);
void deleteStall(vector<Stall> &stalls);
void stallMenu(Stall &stall, vector<Stall> &stalls);
void viewProfile(const Stall &stall);
void viewMenu(const Stall &stall);
void addFoodItem(Stall &stall);
void deleteFoodItem(Stall &stall);
void modifyProfile(Stall &stall);

// Utility function to get food type name from code.
string getFoodTypeName(int type)
{
    switch (type)
    {
    case 1:
        return "South-Indian";
    case 2:
        return "Continental";
    case 3:
        return "Chinese";
    case 4:
        return "Thailand";
    case 5:
        return "Multiple";
    default:
        return "Unknown";
    }
}

// Function to load stalls from file.
void loadStalls(const string &filename, vector<Stall> &stalls)
{
    stalls.clear();
    ifstream fin(filename);
    if (!fin)
        return; // No file yet.
    string line;
    while (true)
    {
        Stall s;
        if (!getline(fin, s.name))
            break;
        if (s.name.empty())
        {
            if (!getline(fin, s.name))
                break;
        }
        if (!getline(fin, s.id))
            break;
        if (!getline(fin, s.mobile))
            break;
        if (!getline(fin, s.email))
            break;
        if (!getline(fin, s.uniqueID))
            break;
        string typeStr;
        if (!getline(fin, typeStr))
            break;
        s.type = stoi(typeStr);
        if (!getline(fin, s.password))
            break;
        if (!getline(fin, s.recovery))
            break;
        string itemsCountStr;
        if (!getline(fin, itemsCountStr))
            break;
        int itemsCount = stoi(itemsCountStr);
        s.menu.clear();
        for (int i = 0; i < itemsCount; ++i)
        {
            string itemLine;
            if (!getline(fin, itemLine))
                break;

            // Each item line format : Name|Price.
            size_t delimPos = itemLine.find("|");
            if (delimPos != string::npos)
            {
                FoodItem item;
                item.name = itemLine.substr(0, delimPos);
                item.price = stod(itemLine.substr(delimPos + 1));
                s.menu.push_back(item);
            }
        }
        stalls.push_back(s);

        // Read blank line separator if present.
        getline(fin, line);
    }
    fin.close();
}

// Function to save stalls to file.
void saveStalls(const string &filename, const vector<Stall> &stalls)
{
    ofstream fout(filename);
    for (const Stall &s : stalls)
    {
        fout << s.name << '\n';
        fout << s.id << '\n';
        fout << s.mobile << '\n';
        fout << s.email << '\n';
        fout << s.uniqueID << '\n';
        fout << s.type << '\n';
        fout << s.password << '\n';
        fout << s.recovery << '\n';
        fout << s.menu.size() << '\n';
        for (const FoodItem &item : s.menu)
        {
            fout << item.name << "|" << item.price << '\n';
        }
        fout << '\n'; // blank line to separate records.
    }
    fout.close();
}

// Admin portal.
void adminPortal(vector<Stall> &stalls)
{
    const string adminUser = "Himanshu"; // Permanent admin user.
    const string adminPass = "09062005"; // Permanent admin password.

    // Admin login.
    string username, password;
    cout << "Enter the Username : ";
    cin >> username;
    cout << "Enter the Password : ";
    cin >> password;
    if (username != adminUser || password != adminPass)
    {
        cout << "Invalid admin credentials!\n";
        return;
    }
    waitAndClear();
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {
        cout << "+---------------------------------------------+" << endl;
        cout << "|          Welcome To Admin Panel             |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "| Press 1 to Add Single Food Stall Record.    |" << endl;
        cout << "| Press 2 to Add Multiple Food Stall Records. |" << endl;
        cout << "| Press 3 to View All Food Stall Records.     |" << endl;
        cout << "| Press 4 to Delete a Food Stall Record.      |" << endl;
        cout << "| Press 5 to Logout.                          |" << endl;
        cout << "+---------------------------------------------+" << endl;
        cout << "Enter Your Choice : ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
            addSingleStall(stalls);
            break;
        case 2:
            addMultipleStalls(stalls);
            break;
        case 3:
            viewStalls(stalls);
            break;
        case 4:
            deleteStall(stalls);
            break;
        case 5:
            cout << "Logging out of admin portal...\n";
            system("cls||clear");
            return;
        default:
            cout << "Invalid choice.\n";
        }
        cout << "Press y to continue; otherwise n : ";
        cin >> cont;
        waitAndClear();
    }
    system("cls||clear");
}

// Food Stall portal.
void foodStallPortal(vector<Stall> &stalls)
{
    system("cls||clear");
    cout << "+---------------------------------+" << endl;
    cout << "|Welcome to Food Stall Login Page.|" << endl;
    cout << "+---------------------------------+" << endl;
    cout << "Enter the Login ID : ";
    string id, password;
    cin >> id;
    cout << "Enter the Login Password : ";
    cin >> password;

    // Find the stall with this id.
    int index = -1;
    for (int i = 0; i < (int)stalls.size(); i++)
    {
        if (stalls[i].id == id && stalls[i].password == password)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "\nYour Login Credentials are In-Correct\n";
        cout << "Press 1 to Re-Cover Password & 2 to Re-Attempt Login\n";
        cout << "Enter the Choice : ";
        int ch;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ch == 1)
        {
            string recoveryId, keyword;
            cout << "\nEnter the Stall Login ID : ";
            cin >> recoveryId;
            cout << "Enter the Unique Keyword (Provided by Admin) : ";
            cin.ignore();
            getline(cin, keyword);
            bool recovered = false;
            for (const Stall &s : stalls)
            {
                if (s.id == recoveryId && s.recovery == keyword)
                {
                    cout << "\nYou are a Valid user.\n";
                    cout << "Your Password is : " << s.password << "\n";
                    cout << "Please Exit and Login Again.\n";
                    recovered = true;
                    break;
                }
            }
            if (!recovered)
            {
                cout << "Recovery Failed! Invalid ID or Keyword.\n";
            }
            waitAndClear();
        }
        else if (ch == 2)
        {

            // Clear the screen immediately for Re-Attempt
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
        }
        return;
    }

    // Stall login success.
    Stall &stall = stalls[index];
    stallMenu(stall, stalls);
}

// Customer portal with multiple options.
void customerPortal(const vector<Stall> &stalls)
{
    system("cls||clear");
    cout << "+--------------------------------------------+" << endl;
    cout << "|             Customer Portal                |" << endl;
    cout << "+--------------------------------------------+" << endl;
    if (stalls.empty())
    {
        cout << "No food stalls available.\n";
        waitAndClear();
        return;
    }
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {
        system("cls||clear");

        // Display guest menu options.
        cout << "+--------------------------------------------+" << endl;
        cout << "|               Guest Menu                   |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| Press 1 to View all Food Stalls and Menus. |" << endl;
        cout << "| Press 2 to Search a Stall by ID.           |" << endl;
        cout << "| Press 3 to Search Stalls by Food Type.     |" << endl;
        cout << "| Press 4 to Return to Main Menu.            |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "Enter Your Choice : ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 4)
        {
            // Exit guest portal
            return;
        }
        switch (choice)
        {
        case 1:
        {
            // View all stalls and their menus
            system("cls||clear");
            cout << "+--------------------------------------------+" << endl;
            cout << "|       All Food Stalls and Their Menus      |" << endl;
            cout << "+--------------------------------------------+" << endl;
            for (const Stall &s : stalls)
            {
                cout << "Stall ID   : " << s.id << "\n";
                cout << "Name       : " << s.name << "\n";
                cout << "Food Type  : " << getFoodTypeName(s.type) << "\n";
                if (s.menu.empty())
                {
                    cout << "Menu Items : (No items in the menu)\n";
                }
                else
                {
                    cout << "Menu Items :\n";
                    int cnt = 1;
                    for (const FoodItem &item : s.menu)
                    {
                        cout << "    " << cnt++ << ". " << item.name
                             << " - INR " << item.price << "\n";
                    }
                }
            }
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 2:
        {
            // Search stall by ID and show its menu
            cout << "Enter Stall ID to search : ";
            string searchId;
            cin >> searchId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found = false;
            system("cls||clear");
            for (const Stall &s : stalls)
            {
                if (s.id == searchId)
                {
                    found = true;
                    cout << "+-------------------------------------+" << endl;
                    cout << "|         Stall Menu Details          |" << endl;
                    cout << "+-------------------------------------+" << endl;
                    cout << "Stall ID   : " << s.id << "\n";
                    cout << "Stall Name : " << s.name << "\n";
                    cout << "E-Mail ID  : " << s.email << "\n";
                    cout << "Mobile No. : " << s.mobile << "\n";
                    cout << "Food Type  : " << getFoodTypeName(s.type) << "\n";
                    cout << "\n+-------------------------------------+" << endl;
                    cout << "|             Menu Items              |" << endl;
                    cout << "+-------------------------------------+" << endl;
                    if (s.menu.empty())
                    {
                        cout << "No items in the menu.\n";
                    }
                    else
                    {
                        cout << "Menu :\n";
                        int cnt = 1;
                        for (const FoodItem &item : s.menu)
                        {
                            cout << "  " << cnt++ << ". " << item.name
                                 << " - INR " << item.price << "\n";
                        }
                    }
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                cout << "\nStall ID not found.\n";
            }
            break;
        }
        case 3:
        {
            // Search stalls by food type
            cout << "\nFood Stall Food Options Possible are :\n";
            cout << "1.South-Indian.\n2.Continental.\n3.Chinese.\n4.Thailand.\n5.Multiple.\n";
            cout << "Enter food type number to search : ";
            int typeChoice;
            cin >> typeChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool any = false;
            for (const Stall &s : stalls)
            {
                if (s.type == typeChoice)
                {
                    if (!any)
                    {
                        system("cls||clear");
                        cout << "+-------------------------------------+" << endl;
                        cout << "|       Stalls matching the type      |" << endl;
                        cout << "+-------------------------------------+" << endl;
                    }
                    any = true;
                    cout << "\nStall ID   : " << s.id << "\n";
                    cout << "Name       : " << s.name << "\n";
                    if (s.menu.empty())
                    {
                        cout << "(No items in the menu)\n";
                    }
                    else
                    {
                        int cnt = 1;
                        cout << "Menu :\n";
                        for (const FoodItem &item : s.menu)
                        {
                            cout << "  " << cnt++ << ". " << item.name
                                 << " - INR " << item.price << "\n";
                        }
                    }
                }
            }
            if (!any)
            {
                cout << "\nNo stalls found for the selected food type.\n";
            }
            waitAndClear();
            break;
        }
        default:
            cout << "Invalid choice.\n";
        }
        system("cls||clear");
        cout << "Press y to return to Customer Portal; otherwise n : ";
        cin >> cont;
        system("cls||clear");
        waitAndClear();
    }
}

// Function to add a single stall.
void addSingleStall(vector<Stall> &stalls)
{
    system("cls||clear");
    Stall s;
    cout << "+------------------------+" << endl;
    cout << "|Enter the Stall Details.|" << endl;
    cout << "+------------------------+" << endl;
    cout << "Enter the Food Stall Name : ";
    getline(cin, s.name);
    if (s.name.empty())
    {
        getline(cin, s.name); // handle leftover newline
    }
    cout << "Enter the Food Stall ID : ";
    cin >> s.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Check duplicate ID
    for (const Stall &st : stalls)
    {
        if (st.id == s.id)
        {
            cout << "Stall ID already exists. Aborting add.\n";
            waitAndClear();
            return;
        }
    }
    cout << "Enter the Food Stall Mobile Number : ";
    getline(cin, s.mobile);
    cout << "Enter the E-Mail ID : ";
    getline(cin, s.email);
    cout << "Enter the Stall Unique ID : ";
    getline(cin, s.uniqueID);
    cout << "\nFood Stall Food Options Possible are :\n";
    cout << "1.South-Indian.\n2.Continental.\n3.Chinese.\n4.Thailand.\n5.Multiple.\n";
    cout << "\nEnter the Food Stall Food Options Type (Unique Number) : ";
    cin >> s.type;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int itemCount;
    cout << "Enter the Total Food menu Items : ";
    cin >> itemCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    s.menu.clear();
    for (int i = 0; i < itemCount; ++i)
    {
        FoodItem item;
        cout << "\nEnter the Food Item : " << i + 1 << " Name : ";
        getline(cin, item.name);
        cout << "Enter the Price of Food : " << i + 1 << " INR : ";
        cin >> item.price;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        s.menu.push_back(item);
    }
    cout << "\nCreate Your Login Password : ";
    getline(cin, s.password);
    cout << "Enter the Unique Keyword to Recover Password : ";
    getline(cin, s.recovery);
    cout << "\nPlease note your Username is ID, i.e. " << s.id << "\n";
    stalls.push_back(s);
    saveStalls("stalls.txt", stalls);
    cout << "Record Entered Successfully...\n";
}

// Function to add multiple stalls.
void addMultipleStalls(vector<Stall> &stalls)
{
    char more = 'y';
    while (more == 'y' || more == 'Y')
    {
        addSingleStall(stalls);
        cout << "Press y to add more stalls; otherwise n : ";
        cin >> more;
        waitAndClear();
    }
}

// Function to view all stalls.
void viewStalls(const vector<Stall> &stalls)
{
    system("cls||clear");
    if (stalls.empty())
    {
        cout << "No food stalls to display.\n";
        return;
    }
    for (const Stall &s : stalls)
    {
        cout << "\n+--------------------------------------------------+" << endl;
        cout << "|                Food Stall Details                |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "Food Stall Name       : " << s.name << "" << endl;
        cout << "Food Stall ID         : " << s.id << "" << endl;
        cout << "Food Stall Mobile No. : " << s.mobile << "" << endl;
        cout << "Food Stall E-Mail ID  : " << s.email << "" << endl;
        cout << "Food Stall Unique ID  : " << s.uniqueID << "" << endl;
        cout << "Food Stall Food Type  : " << getFoodTypeName(s.type) << "" << endl;
        cout << "Food Stall Food Menu Total Items : " << s.menu.size() << " " << endl;
        cout << "\n+-------------------------------------------+" << endl;
        for (int i = 0; i < (int)s.menu.size(); ++i)
        {
            cout << "|Food Item " << i + 1 << " : " << s.menu[i].name
                 << " :: Price : " << s.menu[i].price << "|" << endl;
        }
        cout << "+--------------------------------------------+" << endl;
    }
}

// Function to delete a stall by ID.
void deleteStall(vector<Stall> &stalls)
{
    cout << "\nEnter the Food Stall ID to delete : ";
    string delId;
    cin >> delId;
    bool found = false;
    for (auto it = stalls.begin(); it != stalls.end(); ++it)
    {
        if (it->id == delId)
        {
            stalls.erase(it);
            found = true;
            break;
        }
    }
    if (found)
    {
        saveStalls("stalls.txt", stalls);
        cout << "Record Deleted Successfully...\n";
    }
    else
    {
        cout << "Stall ID not found.\n";
    }
}

// Food stall operations menu.
void stallMenu(Stall &stall, vector<Stall> &stalls)
{
    char cont = 'y';
    while (cont == 'y' || cont == 'Y')
    {
        system("cls||clear");
        cout << "+---------------------------------------------------+----------------------+" << endl;
        cout << "|             Welcome to Food Stall Panel           | Your UserId is : " << stall.id << " |" << endl;
        cout << "+---------------------------------------------------+----------------------+" << endl;
        cout << "|Press 1 to View Your Profile.                      |" << endl;
        cout << "|Press 2 to Know Your Menu (with Price).            |" << endl;
        cout << "|Press 3 to Add a Food Item.                        |" << endl;
        cout << "|Press 4 to Delete a Food Item.                     |" << endl;
        cout << "|Press 5 to Modify Your Profile.                    |" << endl;
        cout << "|Press 6 to Logout.                                 |" << endl;
        cout << "+---------------------------------------------------+" << endl;
        cout << "Enter Your Choice : ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
            viewProfile(stall);
            break;
        case 2:
            viewMenu(stall);
            break;
        case 3:
            addFoodItem(stall);
            saveStalls("stalls.txt", stalls);
            break;
        case 4:
            deleteFoodItem(stall);
            saveStalls("stalls.txt", stalls);
            break;
        case 5:
            modifyProfile(stall);
            saveStalls("stalls.txt", stalls);
            break;
        case 6:
            system("cls||clear");
            cout << "Logging out of food stall portal...\n";
            waitAndClear();
            return;
        default:
            cout << "Invalid choice.\n";
        }
        cout << "\nThank You! ";
        cout << "Press y to continue; otherwise n : ";
        cin >> cont;
    }
    system("cls||clear");
    waitAndClear();
}

// Function to view stall profile.
void viewProfile(const Stall &stall)
{
    system("cls||clear");
    cout << "+-----------------------------+" << endl;
    cout << "|   Food Stall Profile        |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "Food Stall Name         : " << stall.name << "" << endl;
    cout << "Food Stall Mobile No.   : " << stall.mobile << "" << endl;
    cout << "Food Stall E-Mail ID    : " << stall.email << "" << endl;
    cout << "Food Stall Unique ID    : " << stall.uniqueID << "" << endl;
    cout << "Food Stall Food Type    : " << getFoodTypeName(stall.type) << "" << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

// Function to view stall menu.
void viewMenu(const Stall &stall)
{
    cout << "\nFood Stall " << stall.name << " Menu Items (with prices) :\n";
    if (stall.menu.empty())
    {
        cout << "No items in the menu.\n";
    }
    else
    {
        for (int i = 0; i < (int)stall.menu.size(); ++i)
        {
            cout << "Food Item : " << i + 1 << " : " << stall.menu[i].name
                 << " :: Price : " << stall.menu[i].price << "\n";
        }
    }
    cout << "Press Enter to continue...";
    cin.get();
}

// Function to add a food item to stall.
void addFoodItem(Stall &stall)
{
    FoodItem item;
    cout << "\nEnter New Food Item Name : ";
    getline(cin, item.name);
    cout << "Enter Price for " << item.name << " INR: ";
    cin >> item.price;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    stall.menu.push_back(item);
    cout << "Food item added successfully.\n";
}

// Function to delete a food item from stall.
void deleteFoodItem(Stall &stall)
{
    if (stall.menu.empty())
    {
        cout << "No items to delete.\n";
        return;
    }
    cout << "\nEnter the Food Item number to delete : ";
    int idx;
    cin >> idx;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (idx < 1 || idx > (int)stall.menu.size())
    {
        cout << "Invalid item number.\n";
    }
    else
    {
        stall.menu.erase(stall.menu.begin() + (idx - 1));
        cout << "Food item deleted successfully.\n";
    }
}

// Function to modify stall profile.
void modifyProfile(Stall &stall)
{
    system("cls||clear");
    cout << "+-----------------------------+" << endl;
    cout << "|   Modify Stall Profile      |" << endl;
    cout << "+-----------------------------+" << endl;
    cout << "1.Food Stall Name : " << stall.name << endl;
    cout << "2.Mobile Number   : " << stall.mobile << endl;
    cout << "3.E-Mail ID       : " << stall.email << endl;
    cout << "4.Unique ID       : " << stall.uniqueID << endl;
    cout << "5.Food Type       : " << getFoodTypeName(stall.type) << endl;
    cout << "6.Exit" << endl;
    cout << "\nEnter the field number to edit : ";
    int field;
    cin >> field;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (field)
    {
    case 1:
        cout << "Enter new Food Stall Name : ";
        getline(cin, stall.name);
        cout << "Profile updated successfully.\n";
        break;
    case 2:
        cout << "Enter new Mobile Number : ";
        getline(cin, stall.mobile);
        cout << "Profile updated successfully.\n";
        break;
    case 3:
        cout << "Enter new E-Mail ID : ";
        getline(cin, stall.email);
        cout << "Profile updated successfully.\n";
        break;
    case 4:
        cout << "Enter new Unique ID : ";
        getline(cin, stall.uniqueID);
        cout << "Profile updated successfully.\n";
        break;
    case 5:
    {
        cout << "Food Stall Food Options Possible are :\n";
        cout << "1.South-Indian\n2.Continental\n3.Chinese\n4.Thailand\n5.Multiple\n";
        cout << "Enter new Food Type (number) : ";
        int newType;
        cin >> newType;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (newType >= 1 && newType <= 5)
        {
            stall.type = newType;
            cout << "Profile updated successfully.\n";
        }
        else
        {
            cout << "Invalid food type selected.\n";
        }
        break;
    }
    case 6:
        system("cls||clear");
        return;
    default:
        cout << "Invalid choice.\n";
    }

    // No pause here; stallMenu will prompt to continue.
}

// Main function.
int main()
{
    system("cls");
    vector<Stall> stalls;
    loadStalls("stalls.txt", stalls);
    cout << "+----------------------------------------+ " << endl;
    cout << "|Welcome to Food Court Management System.| " << endl;
    cout << "+----------------------------------------+ " << endl;
    waitAndClear();
    system("clear||cls");
    bool running = true;
    while (running)
    {
        cout << "+--------------------------------------------+" << endl;
        cout << "|        Food Court Management System        |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "| Press 1 for Admin Portal.                  |" << endl;
        cout << "| Press 2 for Food Stall Portal.             |" << endl;
        cout << "| Press 3 for Customer Portal.               |" << endl;
        cout << "| Press 4 to Exit.                           |" << endl;
        cout << "+--------------------------------------------+" << endl;
        cout << "Enter Your Choice : ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
            adminPortal(stalls);
            break;
        case 2:
            foodStallPortal(stalls);
            break;
        case 3:
            customerPortal(stalls);
            break;
        case 4:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    cout << "Thank you for using the system.\n";
    getch();
    return 0;
}