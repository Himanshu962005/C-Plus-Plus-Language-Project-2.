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

2.**Project Title: Modern Tic Tac Toe with AI (Console Edition)**

**Project Description:**
This project is a fully featured and modernized console-based implementation of the classic Tic Tac Toe game, developed in C++. It supports a dynamic board size (N x N) and a customizable win condition (K in a row), enhancing replayability and challenge.

**Key Features:**

1. **Dynamic Board Size & Win Condition:**

   * Players can choose any board size (N > 2) and a win condition (K <= N), making the game scalable from simple 3x3 boards to larger, more complex setups.

2. **AI Opponent with Difficulty Levels:**

   * The game offers two AI modes:

     * *Easy Mode:* The AI selects moves randomly.
     * *Hard Mode:* Uses the Minimax algorithm to make intelligent decisions, making it a challenging opponent.

3. **Colored Output for Enhanced UX:**

   * Human ('X') moves are displayed in **blue**, AI ('O') in **red**, and winning moves are highlighted in **green** using ANSI color codes.

4. **Sound Feedback:**

   * Winning and draw outcomes trigger distinct beeps for auditory feedback.

5. **Scoreboard System:**

   * The system keeps track of human wins, AI wins, and draws.
   * Scores are auto-saved to a file (`score.txt`) and loaded on each launch.

6. **Clear Console UI:**

   * Screen is cleared between moves and results using `system("cls")` for a clean interface.

**Technical Summary:**

* Language: C++
* Platform: Windows Console
* Key Concepts: Minimax Algorithm, File I/O, ANSI Color Codes, Vector Data Structure
* Files:

  * `Game3.cpp` (Source Code)
  * `Game3.exe` (Executable Binary)
  * `score.txt` (Auto-generated Score Record)

**Target Audience:**
This project is aimed at beginner to intermediate level programmers and students who want to understand game development logic, AI implementation with Minimax, and interactive console-based applications in C++.

**Learning Outcomes:**

* Implement AI using the Minimax algorithm
* Handle dynamic memory and board logic using STL
* Manage user input, validation, and interface design in console apps
* Use sound and color to enhance interactivity
* Practice modular coding, debugging, and file handling

**Conclusion:**
The project showcases a complete and engaging gaming experience using fundamental and advanced C++ programming concepts. It blends strategic gameplay with technical depth and provides an excellent foundation for exploring AI in games.
