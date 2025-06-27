# C++-Language-Project-2.
1.**Major Project Description: Vehicle Rental System (VRS)**

**Project Title:** Vehicle Rental System (VRS)

**Objective:**
To develop a user-friendly and efficient desktop-based application in C++ that manages the end-to-end vehicle rental process, including vehicle and user management, trip booking, and fare calculation. The system ensures smooth coordination between customers and the service provider for renting vehicles.

**Modules:**

1. **Vehicle Management**

   * Add, view, and edit vehicle details.
   * Store information like registration number, type, company, model, price per km, and PUC expiry.
   * Data stored persistently in `vehicles.txt`.

2. **User Management**

   * Add and view user details.
   * Store user name, 10-digit contact number, and email.
   * Data saved in `users.txt`.

3. **Trip Management**

   * Book, start, and complete trips.
   * Manage trip details including trip ID, start/end dates, odometer readings, fare, and status.
   * Calculate fare based on distance traveled and vehicle rate.
   * Data handled through `trips.txt`.

**Core Features:**

* Data Validation:

  * Date validation using custom `validDate()` function supporting both 1- and 2-digit day/month entries.
  * Contact number validation (10 digits).
* Enum-based trip status: NotStarted, InProgress, Completed.
* Console-based interface using C++ standard and Windows-specific headers (`<conio.h>`, `system("cls")`).
* ASCII box output for better visual messages.

**User Flow:**

* Users can register and provide contact information.
* Admin can add and manage vehicles.
* Trips can be booked with a registered user and an available vehicle.
* Admin can start a trip (mark InProgress), complete it by providing end odometer reading and end date, and fare is auto-calculated.

**Data Handling:**

* Text-based file storage for all modules: `vehicles.txt`, `users.txt`, `trips.txt`.
* Loading and saving done via file streams.

**Technologies Used:**

* Programming Language: C++
* File Handling: Text files
* Platform: Windows (console-based)

**Conclusion:**
The Vehicle Rental System effectively manages all critical operations involved in vehicle booking and monitoring. It is modular, user-oriented, and handles persistent storage through simple yet reliable file operations, making it ideal for small rental businesses or academic demonstration.
