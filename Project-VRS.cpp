#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <conio.h>
using namespace std;

// Vehicle Management.
class Vehicle
{
public:
    string regNo, type, company, model, pucExpiry;
    double pricePerKm;
    Vehicle(string r = "", string t = "", string c = "", string m = "", double p = 0, string d = "")
        : regNo(r), type(t), company(c), model(m), pricePerKm(p), pucExpiry(d) {}
};

// User Management.
class User
{
public:
    string name, contact, email;
    User(string n = "", string c = "", string e = "") : name(n), contact(c), email(e) {}
};

// Trip Management.
enum class TripStatus
{
    NotStarted,
    InProgress,
    Completed
};

class Trip
{
public:
    int id;
    string userContact, startDate, endDate, vehicleReg;
    double startOdo, endOdo, fare;
    TripStatus status;
    Trip(int i = 0, string u = "", string s = "", string e = "", string v = "",
         double so = 0, double eo = 0, double f = 0, TripStatus st = TripStatus::NotStarted)
        : id(i), userContact(u), startDate(s), endDate(e), vehicleReg(v),
          startOdo(so), endOdo(eo), fare(f), status(st) {}
};

// Check if a String contains only digits (for contact number).
bool isNumber(const string &s)
{
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return !s.empty();
}

// Revised ValidDate : Allows 1 or 2 - Digit Day/Month.
bool validDate(const string &date)
{
    // Find first slash.
    size_t p1 = date.find('/');
    if (p1 == string::npos)
        return false; // No Slash Found.

    // Find second slash after first.
    size_t p2 = date.find('/', p1 + 1);
    if (p2 == string::npos)
        return false; // Only One Slash Found.

    // Extract day, month, year substrings.
    string ds = date.substr(0, p1);
    string ms = date.substr(p1 + 1, p2 - p1 - 1);
    string ys = date.substr(p2 + 1);

    // All parts must be non-empty and numeric.
    if (ds.empty() || ms.empty() || ys.size() != 4)
        return false;
    if (!isNumber(ds) || !isNumber(ms) || !isNumber(ys))
        return false;

    // Convert to integers.
    int d = stoi(ds);
    int m = stoi(ms);
    int y = stoi(ys);

    // Month must be 1..12.
    if (m < 1 || m > 12)
        return false;

    // Determine max days in month (account for leap year in Feb).
    int maxd = 31;
    if (m == 4 || m == 6 || m == 9 || m == 11)
        maxd = 30;
    else if (m == 2)
    {
        bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        maxd = leap ? 29 : 28;
    }

    // Day must be 1..maxd.
    if (d < 1 || d > maxd)
        return false;

    return true; // All Checks Passed.
}

// Utility: Print a message in an ASCII box.
void printBox(const string &line1, const string &line2 = "", const string &line3 = "")
{
    int width = max({line1.length(), line2.length(), line3.length()}) + 4;

    cout << "+" << string(width - 2, '-') << "+" << endl;
    if (!line1.empty())
        cout << "| " << line1 << string(width - 3 - line1.length(), ' ') << "|\n";

    // Print an empty line (spacer) if line2 is empty and line3 is not empty
    if (line2.empty() && !line3.empty())
        cout << "| " << string(width - 3, ' ') << "|\n";
    else if (!line2.empty())
        cout << "| " << line2 << string(width - 3 - line2.length(), ' ') << "|\n";

    if (!line3.empty())
        cout << "| " << line3 << string(width - 3 - line3.length(), ' ') << "|\n";

    cout << "+" << string(width - 2, '-') << "+" << endl;
}

// Load all vehicles from file.
vector<Vehicle> loadVehicles()
{
    vector<Vehicle> vehicles;
    ifstream fin("vehicles.txt");
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        // Format: reg|type|company|model|price|puc.
        vector<string> fields;
        size_t prev = 0, pos;
        while ((pos = line.find('|', prev)) != string::npos)
        {
            fields.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        fields.push_back(line.substr(prev));
        if (fields.size() != 6)
            continue;
        Vehicle v;
        v.regNo = fields[0];
        v.type = fields[1];
        v.company = fields[2];
        v.model = fields[3];
        v.pricePerKm = stod(fields[4]);
        v.pucExpiry = fields[5];
        vehicles.push_back(v);
    }
    fin.close();
    return vehicles;
}

// Save all vehicles to file.
void saveVehicles(const vector<Vehicle> &vehicles)
{
    ofstream fout("vehicles.txt", ios::trunc);
    for (const auto &v : vehicles)
    {
        fout << v.regNo << "|" << v.type << "|" << v.company << "|"
             << v.model << "|" << v.pricePerKm << "|" << v.pucExpiry << "\n";
    }
    fout.close();
}

// Load all users from file.
vector<User> loadUsers()
{
    vector<User> users;
    ifstream fin("users.txt");
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        // Format: contact|name|email.
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos)
            continue;
        User u;
        u.contact = line.substr(0, pos1);
        u.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        u.email = line.substr(pos2 + 1);
        users.push_back(u);
    }
    fin.close();
    return users;
}

// Save all users to file.
void saveUsers(const vector<User> &users)
{
    ofstream fout("users.txt", ios::trunc);
    for (const auto &u : users)
    {
        fout << u.contact << "|" << u.name << "|" << u.email << "\n";
    }
    fout.close();
}

// Load all trips from file.
vector<Trip> loadTrips()
{
    vector<Trip> trips;
    ifstream fin("trips.txt");
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;
        // Format: id|contact|startDate|endDate|vehReg|startOdo|endOdo|fare|status.
        vector<string> fields;
        size_t prev = 0, pos;
        while ((pos = line.find('|', prev)) != string::npos)
        {
            fields.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        fields.push_back(line.substr(prev));
        if (fields.size() != 9)
            continue;
        Trip t;
        t.id = stoi(fields[0]);
        t.userContact = fields[1];
        t.startDate = fields[2];
        t.endDate = fields[3];
        t.vehicleReg = fields[4];
        t.startOdo = stod(fields[5]);
        t.endOdo = stod(fields[6]);
        t.fare = stod(fields[7]);
        string st = fields[8];
        if (st == "NotStarted")
            t.status = TripStatus::NotStarted;
        else if (st == "InProgress")
            t.status = TripStatus::InProgress;
        else if (st == "Completed")
            t.status = TripStatus::Completed;
        trips.push_back(t);
    }
    fin.close();
    return trips;
}

// Save all trips to file.
void saveTrips(const vector<Trip> &trips)
{
    ofstream fout("trips.txt", ios::trunc);
    for (const auto &t : trips)
    {
        string st;
        if (t.status == TripStatus::NotStarted)
            st = "NotStarted";
        else if (t.status == TripStatus::InProgress)
            st = "InProgress";
        else if (t.status == TripStatus::Completed)
            st = "Completed";
        fout << t.id << "|" << t.userContact << "|" << t.startDate << "|"
             << t.endDate << "|" << t.vehicleReg << "|" << t.startOdo << "|"
             << t.endOdo << "|" << t.fare << "|" << st << "\n";
    }
    fout.close();
}

// Get next trip ID (one more than current max).
int getNextTripID()
{
    auto trips = loadTrips();
    int maxId = 0;
    for (const auto &t : trips)
    {
        if (t.id > maxId)
            maxId = t.id;
    }
    return maxId + 1;
}
void waitAndClear()
{
    cout << "Press Enter to continue...";
    cin.get();
    system("cls||clear");
}
int main()
{
    system("cls");
    system("clear||cls");
    printBox("Welcome to Vehicle Management System");
    waitAndClear(); // Wait for key press.
    system("clear||cls");
    vector<Vehicle> vehicles = loadVehicles();
    vector<User> users = loadUsers();
    vector<Trip> trips = loadTrips();

    while (true)
    {
        // Display Main Menu.
        cout << "+-----------------------------------------+" << endl;
        cout << "|          Vehicle Management             |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "| 1. Add new vehicle.                     |" << endl;
        cout << "| 2. View vehicle details.                |" << endl;
        cout << "| 3. Edit vehicle details.                |" << endl;
        cout << "| 4. Add new user.                        |" << endl;
        cout << "| 5. View user.                           |" << endl;
        cout << "| 6. Add new trip.                        |" << endl;
        cout << "| 7. Start trip.                          |" << endl;
        cout << "| 8. View trip.                           |" << endl;
        cout << "| 9. Complete trip.                       |" << endl;
        cout << "| 10. Exit.                               |" << endl;
        cout << "+-----------------------------------------+" << endl;
        cout << "Enter your choice : ";

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            // Add New Vehicle.
            Vehicle v;
            cout << "Enter Registration Number : ";
            getline(cin, v.regNo);
            cout << "Enter Vehicle Type (Bike/Car/Tourer) : ";
            getline(cin, v.type);
            cout << "Enter Company Name : ";
            getline(cin, v.company);
            cout << "Enter Model Name : ";
            getline(cin, v.model);
            cout << "Enter Price per km : ";
            cin >> v.pricePerKm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter PUC Expiration Date (dd/mm/yyyy) : ";
            getline(cin, v.pucExpiry);
            while (!validDate(v.pucExpiry))
            {
                cout << "Invalid date format. Enter date as dd/mm/yyyy : ";
                getline(cin, v.pucExpiry);
            }
            vehicles.push_back(v);
            saveVehicles(vehicles);
            printBox("Vehicle added successfully");
            waitAndClear();
        }
        else if (choice == 2)
        {
            // View Vehicle Details.
            cout << "Enter Registration Number : ";
            string reg;
            getline(cin, reg);
            bool found = false;
            for (const auto &v : vehicles)
            {
                if (v.regNo == reg)
                {
                    cout << "\nVehicle details\n";
                    cout << "Registration No : " << v.regNo << endl;
                    cout << "Type : " << v.type << endl;
                    cout << "Company : " << v.company << endl;
                    cout << "Model : " << v.model << endl;
                    cout << "Price per km : " << v.pricePerKm << endl;
                    cout << "PUC Expiry Date : " << v.pucExpiry << endl;
                    found = true;
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                printBox("Vehicle not found");
            }
        }
        else if (choice == 3)
        {
            // Edit Vehicle Details.
            cout << "Enter Registration Number : ";
            string reg;
            getline(cin, reg);
            bool found = false;
            for (auto &v : vehicles)
            {
                if (v.regNo == reg)
                {
                    found = true;
                    cout << "\nEditing vehicle " << reg << endl;
                    cout << "Enter new Vehicle Type (Bike/Car/Tourer) : ";
                    getline(cin, v.type);
                    cout << "Enter new Company Name : ";
                    getline(cin, v.company);
                    cout << "Enter new Model Name : ";
                    getline(cin, v.model);
                    cout << "Enter new Price per km : ";
                    cin >> v.pricePerKm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter new PUC Expiration Date (dd/mm/yyyy) : ";
                    getline(cin, v.pucExpiry);
                    while (!validDate(v.pucExpiry))
                    {
                        cout << "Invalid date format. Enter date as dd/mm/yyyy : ";
                        getline(cin, v.pucExpiry);
                    }
                    saveVehicles(vehicles);
                    printBox("Vehicle Details Updated");
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                printBox("Vehicle not found");
            }
        }
        else if (choice == 4)
        {
            // Add New User.
            User u;
            cout << "Enter User Name : ";
            getline(cin, u.name);
            cout << "Enter Contact Number : ";
            getline(cin, u.contact);
            while (!isNumber(u.contact) || u.contact.size() != 10)
            {
                cout << "Invalid contact. Enter 10-digit number : ";
                getline(cin, u.contact);
            }
            cout << "Enter Email (optional) : ";
            getline(cin, u.email);
            users.push_back(u);
            saveUsers(users);
            printBox("User added successfully");
            waitAndClear();
        }
        else if (choice == 5)
        {
            // View User Details.
            cout << "Enter Contact Number : ";
            string contact;
            getline(cin, contact);
            bool found = false;
            for (const auto &u : users)
            {
                if (u.contact == contact)
                {
                    cout << "\nUser Details\n";
                    cout << "Name : " << u.name << endl;
                    cout << "Contact : " << u.contact << endl;
                    cout << "Email : " << u.email << endl;
                    found = true;
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                printBox("User not found");
            }
        }
        else if (choice == 6)
        {
            // Add New Trip.
            Trip t;
            t.id = getNextTripID();
            cout << "Enter User Contact : ";
            getline(cin, t.userContact);
            bool userExists = false;
            for (const auto &u : users)
            {
                if (u.contact == t.userContact)
                {
                    userExists = true;
                    break;
                }
            }
            if (!userExists)
            {
                printBox("User not found");
                continue;
            }
            cout << "Enter Vehicle Registration No : ";
            getline(cin, t.vehicleReg);
            bool vehExists = false;
            for (const auto &v : vehicles)
            {
                if (v.regNo == t.vehicleReg)
                {
                    vehExists = true;
                    break;
                }
            }
            if (!vehExists)
            {
                printBox("Vehicle not found");
                continue;
            }
            cout << "Enter Start Date (dd/mm/yyyy) : ";
            getline(cin, t.startDate);
            while (!validDate(t.startDate))
            {
                cout << "Invalid date. Enter dd/mm/yyyy : ";
                getline(cin, t.startDate);
            }
            cout << "Enter starting odometer reading : ";
            cin >> t.startOdo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            t.endOdo = 0;
            t.fare = 0;
            t.status = TripStatus::NotStarted;
            t.endDate = "";
            trips.push_back(t);
            saveTrips(trips);
            printBox("Trip added successfully");
            waitAndClear();
        }
        else if (choice == 7)
        {
            // Start Trip.
            cout << "Enter Trip ID : ";
            int tid;
            cin >> tid;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found = false;
            for (auto &t : trips)
            {
                if (t.id == tid)
                {
                    found = true;
                    if (t.status != TripStatus::NotStarted)
                    {
                        printBox("Trip cannot be started");
                    }
                    else
                    {
                        t.status = TripStatus::InProgress;
                        saveTrips(trips);
                        printBox("Trip started");
                    }
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                printBox("Trip not found");
            }
        }
        else if (choice == 8)
        {
            // View Trip Details.
            cout << "Enter Trip ID : ";
            int tid;
            cin >> tid;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found = false;
            for (const auto &t : trips)
            {
                if (t.id == tid)
                {
                    found = true;
                    cout << "\nTrip Details\n";
                    cout << "Trip ID : " << t.id << endl;
                    cout << "User Contact : " << t.userContact << endl;
                    cout << "Vehicle Reg : " << t.vehicleReg << endl;
                    cout << "Start Date : " << t.startDate << endl;
                    cout << "End Date : " << t.endDate << endl;
                    cout << "Start Odometer : " << t.startOdo << endl;
                    cout << "End Odometer : " << t.endOdo << endl;
                    cout << "Fare : " << t.fare << endl;
                    cout << "Status : ";
                    if (t.status == TripStatus::NotStarted)
                        cout << "Not Started";
                    if (t.status == TripStatus::InProgress)
                        cout << "In Progress";
                    if (t.status == TripStatus::Completed)
                        cout << "Completed";
                    cout << endl;
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                printBox("Trip not found");
            }
        }
        else if (choice == 9)
        {
            // Complete Trip.
            cout << "Enter Trip ID : ";
            int tid;
            cin >> tid;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool found = false;
            for (auto &t : trips)
            {
                if (t.id == tid)
                {
                    found = true;
                    if (t.status != TripStatus::InProgress)
                    {
                        printBox("Trip cannot be completed");
                    }
                    else
                    {
                        cout << "Enter ending odometer reading : ";
                        cin >> t.endOdo;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        double distance = t.endOdo - t.startOdo;
                        double rate = 0;
                        for (const auto &v : vehicles)
                        {
                            if (v.regNo == t.vehicleReg)
                            {
                                rate = v.pricePerKm;
                                break;
                            }
                        }
                        t.fare = distance * rate;
                        t.status = TripStatus::Completed;
                        cout << "Enter End Date (dd/mm/yyyy): ";
                        getline(cin, t.endDate);
                        while (!validDate(t.endDate))
                        {
                            cout << "Invalid date. Enter dd/mm/yyyy : ";
                            getline(cin, t.endDate);
                        }
                        saveTrips(trips);
                        cout << "Total fare : " << t.fare << endl;
                    }
                    printBox("Trip completed successfully");
                    waitAndClear();
                    break;
                }
            }
            if (!found)
            {
                printBox("Trip not found");
            }
        }
        else if (choice == 10)
        {
            printBox("Exiting application");
            waitAndClear();
            break;
        }
        else
        {
            printBox("Invalid choice");
        }
        cout << endl;
    }
    return 0;
}