# Car Parts Manager System

## Introduction

This project is a Console Application developed using C++ to manage a car parts store. The system aims to provide an interactive interface for managing users (admins, employees, and customers), products (car parts), and invoices, applying different permissions for each user type to ensure organized operations and data security.

## Key Features

The system offers a comprehensive set of functionalities to efficiently manage car parts store operations:

*   **User Management:** The system provides a mechanism for registering new users (customers) and logging in for all user types (admin, employee, customer). The admin has full privileges, including adding employees, viewing users by type or gender, activating or deactivating user accounts, and removing users. Input validation for fields like phone number and username is implemented to ensure data accuracy.
*   **Product (Car Parts) Management:** Employees and admins can add new car parts, delete existing ones, modify their details (name, price, quantity), and view details of a specific part or a list of all available parts. The system also provides functionality to search for a part using its name or ID.
*   **Sales and Invoice Management:** Logged-in customers can view the list of available car parts and purchase the items they need. The system automatically updates the stock quantity and generates an invoice for the purchase, including details of the purchased items and the total amount. Customers can also view their past invoice history.
*   **User Permissions:** The system implements a Role-Based Access Control model. The admin has the highest level of permissions, followed by the employee who can manage products, and finally the customer who can view products, purchase them, and view their invoices.
*   **Data Persistence:** User, product, and invoice data are saved in separate text files (`users.txt`, `products.txt`, `invoices.txt`), ensuring data persistence between application sessions.
*   **Interactive Interface:** The system relies on a structured and user-friendly text-based command-line interface, with clear menus for each user type to guide them through available operations.
*   **System Statistics:** The admin can view basic statistics about the system, such as the number of registered users, the number of products in stock, and the number of invoices generated.

## Technologies Used

*   **Programming Language:** C++
*   **Data Storage:** Text Files

## How to Compile and Run

To compile and run this project, you will need a C++ compiler (like G++ or Clang) or an Integrated Development Environment (IDE) that supports C++ (like Visual Studio).

1.  **Get the Code:** Download or clone the project files.
2.  **Compile:** Open a terminal or command prompt, navigate to the directory containing the `Car Parts.cpp` file. Compile the code using your C++ compiler. For example, using G++:
    ```bash
    g++ "Car Parts.cpp" -o CarPartsManager -std=c++11
    ```
3.  **Run:** After successful compilation, an executable file will be created (e.g., `CarPartsManager.exe` on Windows or `CarPartsManager` on Linux). Run this file:
    ```bash
    ./CarPartsManager
    ```
4.  **Data Files:** Ensure that the `users.txt`, `products.txt`, and `invoices.txt` files are present in the same directory as the executable. The program reads data from and writes data to these files. If they don't exist, the program might create them or you might encounter errors.
5.  **Interact with the System:** Follow the on-screen instructions to register, log in, and perform various operations based on the user type.

## Project Structure

*   `Car Parts.cpp`: The main source file containing all the program logic.
*   `users.txt`: File for storing user data.
*   `products.txt`: File for storing car parts data.
*   `invoices.txt`: File for storing invoice data.
*   Other files: The project might contain IDE-specific files like solution (`.sln`) or project (`.vcxproj`) files if developed using Visual Studio.

## Additional Notes

*   When running the program for the first time with no registered users, the system will prompt you to register an admin account first.
*   The code includes basic input validation (e.g., for phone numbers, prices, quantities), but it could be further enhanced.

---

