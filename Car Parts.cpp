#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype> // لاستخدام isalpha
#include <iomanip> // لإدارة عرض الجداول

using namespace std;

// تعريف الهيكل (struct) لتمثيل المستخدم
struct User {
    string username;
    string password;
    string usertype; // "admin", "employee", "customer"
    string phonenumber;
    string gender;   // ذكر أو أنثى
    bool isactive;
};

// تعريف الهيكل (struct) لتمثيل قطع الغيار
struct Product {
    int id;
    string name;
    double price;
    int quantity;
};

// تعريف الهيكل (struct) لتمثيل الفاتورة
struct Invoice {
    string customerUsername;
    vector<Product> products;
    double totalAmount;
};

// متغيرات عامة
vector<User> users;
vector<Product> products;
vector<Invoice> invoices;
User currentUser;

// دالة لعرض جدول المستخدمين
void displayUsersTable(const vector<User>& users) {
    if (users.empty()) {
        cout << "No users available!" << endl;
        return;
    }

    // عرض الجدول مع حواف
    cout << "┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
    cout << "│ Username      │ Type          │ Gender        │ Phone         │ Active        │" << endl;
    cout << "├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤" << endl;

    for (const User& user : users) {
        cout << "│ " << setw(13) << left << user.username << "│ "
            << setw(13) << left << user.usertype << " │ "
            << setw(13) << left << user.gender << " │ "
            << setw(13) << left << user.phonenumber << " │ "
            << setw(13) << left << (user.isactive ? "Yes" : "No") << " │" << endl;
    }

    cout << "└───────────────┴───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
}

// دالة لعرض جدول المنتجات
void displayProductsTable(const vector<Product>& products) {
    if (products.empty()) {
        cout << "No products available!" << endl;
        return;
    }

    // استخدام مؤشر للوصول إلى عناصر vector<Product>
    const Product* productPtr = products.data();
    cout << "\n\n\t\t___________________________________" << endl;
    cout << "\t\t|        Display Products          |" << endl;
    cout << "\t\t|__________________________________|" << endl;
    cout << "┌───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
    cout << "│ ID            │ Name          │ Price         │ Quantity      │" << endl;
    cout << "├───────────────┼───────────────┼───────────────┼───────────────┤" << endl;

    for (size_t i = 0; i < products.size(); ++i) {
        cout << "│ " << setw(13) << left << productPtr[i].id << " │ "
            << setw(13) << left << productPtr[i].name << " │ "
            << setw(13) << left << productPtr[i].price << " │ "
            << setw(13) << left << productPtr[i].quantity << " │" << endl;
    }

    cout << "└───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
}
// دالة لعرض جدول الفواتير
void displayInvoicesTable(const vector<Invoice>& invoices) {
    if (invoices.empty()) {
        cout << "No invoices available!" << endl;
        return;
    }

    // عرض الجدول مع حواف
    cout << "┌───────────────┬───────────────┬───────────────┐" << endl;
    cout << "│ Customer       │ Total Amount  │ Products      │" << endl;
    cout << "├───────────────┼───────────────┼───────────────┤" << endl;

    for (const Invoice& invoice : invoices) {
        cout << "│ " << setw(13) << left << invoice.customerUsername << " │ "
            << setw(13) << left << invoice.totalAmount << " │ ";

        // عرض المنتجات في الفاتورة
        string productsList;
        for (const Product& product : invoice.products) {
            productsList += product.name + " (" + to_string(product.quantity) + "), ";
        }
        if (!productsList.empty()) {
            productsList = productsList.substr(0, productsList.length() - 2); // إزالة الفاصلة الأخيرة
        }

        cout << setw(13) << left << productsList << " │" << endl;
    }

    cout << "└───────────────┴───────────────┴───────────────┘" << endl;
}

// دالة للتحقق من صحة رقم الهاتف
bool isValidPhoneNumber(const string& phone) {
    if (phone.length() != 9 || (phone.substr(0, 2) != "77" && phone.substr(0, 2) != "71" && phone.substr(0, 2) != "78" && phone.substr(0, 2) != "73"))
        return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// دالة للتحقق من صحة اسم المستخدم (يجب أن يحتوي على اسم ولقب)
bool isValidUsername(const string& username) {
    // التحقق من أن الاسم يحتوي على مسافة واحدة على الأقل
    size_t spacePos = username.find(' ');
    if (spacePos == string::npos) {
        return false; // لا يوجد مسافة
    }

    // التحقق من أن المسافة ليست في البداية أو النهاية
    if (spacePos == 0 || spacePos == username.length() - 1) {
        return false; // مسافة في البداية أو النهاية
    }

    // التحقق من أن الاسم لا يحتوي على أرقام أو رموز
    for (char c : username) {
        if (!isalpha(c) && c != ' ') { // يسمح بالمسافات بين الكلمات
            return false;
        }
    }
    return true;
}

// دالة لطلب إدخال رقم هاتف صحيح
string getValidPhoneNumber() {
    string phone;
    while (true) {
        cout << "Enter phone number (must start with 77, 71, 78, or 73 and be 9 digits): ";
        cin >> phone;
        if (isValidPhoneNumber(phone)) {
            return phone;
        }
        else {
            cout << "Invalid phone number! Please try again." << endl;
        }
    }
}

// دالة لطلب إدخال اسم مستخدم صحيح (يجب أن يحتوي على اسم ولقب)
string getValidUsername() {
    string username;
    while (true) {
        cout << "Enter username (must contain first name and last name): ";
        cin.ignore(); // تجاهل الأحرف المتبقية في buffer
        getline(cin, username); // السماح بإدخال الاسم الكامل
        if (isValidUsername(username)) {
            return username;
        }
        else {
            cout << "Invalid username! Please enter both first name and last name (letters and spaces only)." << endl;
        }
    }
}

// دالة لطلب إدخال رقم صحيح (للسعر والكمية)
int getValidNumber(const string& prompt) {
    int number;
    while (true) {
        cout << prompt;
        cin >> number;
        if (cin.fail()) {
            cin.clear(); // إعادة تعيين حالة الإدخال
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تجاهل الإدخال الخاطئ
            cout << "Invalid input! Please enter a valid number." << endl;
        }
        else {
            return number;
        }
    }
}

// دالة لطلب إدخال سعر صحيح
double getValidPrice() {
    double price;
    while (true) {
        cout << "Enter product price: ";
        cin >> price;
        if (cin.fail() || price <= 0) {
            cin.clear(); // إعادة تعيين حالة الإدخال
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تجاهل الإدخال الخاطئ
            cout << "Invalid price! Please enter a valid positive number." << endl;
        }
        else {
            return price;
        }
    }
}

// دالة لطلب إدخال جنس صحيح (male/female)
string getValidGender() {
    string gender;
    while (true) {
        cout << "Enter gender (male/female): ";
        cin >> gender;
        if (gender == "male" || gender == "female") {
            return gender;
        }
        else {
            cout << "Invalid gender! Please enter 'male' or 'female'." << endl;
        }
    }
}

// دالة لطلب إدخال نوع مستخدم صحيح (admin/employee/customer)
string getValidUserType() {
    string usertype;
    while (true) {
        cout << "Enter user type (admin/employee/customer): ";
        cin >> usertype;
        if (usertype == "admin" || usertype == "employee" || usertype == "customer") {
            return usertype;
        }
        else {
            cout << "Invalid user type! Please enter 'admin', 'employee', or 'customer'." << endl;
        }
    }
}

// دالة لتسجيل مستخدم جديد
void registerUser(string usertype) {
    User newUser;
    newUser.username = getValidUsername();

    // التحقق من عدم تكرار اسم المستخدم
    for (const User& user : users) {
        if (user.username == newUser.username) {
            cout << "Username already exists! Please choose a different username." << endl;
            return;
        }
    }

    cout << "Enter password: ";
    cin >> newUser.password;
    newUser.usertype = usertype;

    // طلب إدخال رقم هاتف صحيح
    newUser.phonenumber = getValidPhoneNumber();

    // طلب إدخال جنس صحيح
    newUser.gender = getValidGender();

    newUser.isactive = true;
    users.push_back(newUser);
    cout << "User registered successfully!" << endl;
}

// دالة لتسجيل الدخول
bool login() {
    string username, password;
    cout << "Enter username: ";
    cin.ignore(); // تجاهل الأحرف المتبقية في buffer
    getline(cin, username); // السماح بإدخال الاسم الكامل
    cout << "Enter password: ";
    cin >> password;

    for (User& user : users) {
        if (user.username == username && user.password == password) {
            if (user.isactive) {
                currentUser = user;
                cout << "Login successful! Welcome, " << currentUser.username << endl;
                return true;
            }
            else {
                cout << "User is not active! Please contact the admin." << endl;
                return false;
            }
        }
    }

    cout << "Invalid username or password! Please try again." << endl;
    return false;
}

// دالة لإضافة منتج (للموظف أو المدير)
void addProduct() {
    if (currentUser.usertype != "admin" && currentUser.usertype != "employee") {
        cout << "You do not have permission to add products!" << endl;
        return;
    }

    Product newProduct;
    newProduct.id = getValidNumber("Enter product ID: ");
    cout << "Enter product name: ";
    cin.ignore(); // تجاهل الأحرف المتبقية في buffer
    getline(cin, newProduct.name); // السماح بإدخال الاسم الكامل
    newProduct.price = getValidPrice();
    newProduct.quantity = getValidNumber("Enter product quantity: ");

    products.push_back(newProduct);
    cout << "Product added successfully!" << endl;
}

// دالة لحذف منتج (للموظف أو المدير)
void deleteProduct() {
    if (currentUser.usertype != "admin" && currentUser.usertype != "employee") {
        cout << "You do not have permission to delete products!" << endl;
        return;
    }

    int productId = getValidNumber("Enter product ID to delete: ");

    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == productId) {
            products.erase(it);
            cout << "Product deleted successfully!" << endl;
            return;
        }
    }

    cout << "Product not found!" << endl;
}

// دالة لتعديل منتج (للموظف أو المدير)
void modifyProduct() {
    if (currentUser.usertype != "admin" && currentUser.usertype != "employee") {
        cout << "You do not have permission to modify products!" << endl;
        return;
    }

    int productId = getValidNumber("Enter product ID to modify: ");

    for (Product& product : products) {
        if (product.id == productId) {
            cout << "Enter new product name: ";
            cin.ignore(); // تجاهل الأحرف المتبقية في buffer
            getline(cin, product.name); // السماح بإدخال الاسم الكامل
            product.price = getValidPrice();
            product.quantity = getValidNumber("Enter new product quantity: ");
            cout << "Product modified successfully!" << endl;
            return;
        }
    }

    cout << "Product not found!" << endl;
}

// دالة لعرض منتج واحد (للموظف أو المدير)
void displayProduct() {
    if (currentUser.usertype != "admin" && currentUser.usertype != "employee") {
        cout << "You do not have permission to view products!" << endl;
        return;
    }

    int productId = getValidNumber("Enter product ID to display: ");

    for (const Product& product : products) {
        if (product.id == productId) {
            cout << "\n\n\t\t___________________________________" << endl;
            cout << "\t\t|      Display Product             |" << endl;
            cout << "\t\t|__________________________________|" << endl;
            cout << "┌───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
            cout << "│ ID            │ Name          │ Price         │ Quantity      │" << endl;
            cout << "├───────────────┼───────────────┼───────────────┼───────────────┤" << endl;
            cout << "│ " << setw(13) << left << product.id << " │ "
                << setw(13) << left << product.name << " │ "
                << setw(13) << left << product.price << " │ "
                << setw(13) << left << product.quantity << " │" << endl;
            cout << "└───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
            return;
        }
    }

    cout << "Product not found!" << endl;
}

// دالة لعرض جميع المنتجات
void displayProducts() {
    displayProductsTable(products);
}

// دالة للبحث عن منتج باستخدام الاسم أو الـ ID
void searchProduct() {
    if (currentUser.usertype != "admin" && currentUser.usertype != "employee") {
        cout << "You do not have permission to search products!" << endl;
        return;
    }

    cout << "1. Search by ID\n2. Search by name\n";
    int choice = getValidNumber("Enter your choice: ");

    if (choice == 1) {
        int productId = getValidNumber("Enter product ID: ");
        for (const Product& product : products) {
            if (product.id == productId) {
                cout << "┌───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
                cout << "│ ID            │ Name          │ Price         │ Quantity      │" << endl;
                cout << "├───────────────┼───────────────┼───────────────┼───────────────┤" << endl;
                cout << "│ " << setw(13) << left << product.id << " │ "
                    << setw(13) << left << product.name << " │ "
                    << setw(13) << left << product.price << " │ "
                    << setw(13) << left << product.quantity << " │" << endl;
                cout << "└───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
                return;
            }
        }
        cout << "Product not found!" << endl;
    }
    else if (choice == 2) {
        string name;
        cout << "Enter product name: ";
        cin.ignore(); // تجاهل الأحرف المتبقية في buffer
        getline(cin, name); // السماح بإدخال الاسم الكامل

        bool found = false;
        for (const Product& product : products) {
            if (product.name == name) {
                cout << "┌───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
                cout << "│ ID            │ Name          │ Price         │ Quantity      │" << endl;
                cout << "├───────────────┼───────────────┼───────────────┼───────────────┤" << endl;
                cout << "│ " << setw(13) << left << product.id << " │ "
                    << setw(13) << left << product.name << " │ "
                    << setw(13) << left << product.price << " │ "
                    << setw(13) << left << product.quantity << " │" << endl;
                cout << "└───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Product not found!" << endl;
        }
    }
    else {
        cout << "Invalid choice!" << endl;
    }
}

// دالة لشراء قطع غيار (للعميل)
void purchaseProduct() {
    if (currentUser.usertype != "customer") {
        cout << "You do not have permission to purchase products!" << endl;
        return;
    }

    // عرض جميع المنتجات المتاحة
    displayProducts();
    if (products.empty()) {
        cout << "No products available to purchase!" << endl;
        return;
    }

    int productId = getValidNumber("Enter product ID to purchase: ");
    d:
    int quantity = getValidNumber("Enter quantity: ");

    for (Product& product : products) {
        if (product.id == productId) {
            if (product.quantity >= quantity) {
                // تحديث كمية المنتج
                product.quantity -= quantity;

                // إنشاء فاتورة جديدة
                Invoice newInvoice;
                newInvoice.customerUsername = currentUser.username;
                newInvoice.products.push_back(product);
                newInvoice.totalAmount = product.price * quantity;
                invoices.push_back(newInvoice);

                // عرض تفاصيل الفاتورة
                cout << "┌───────────────────────────────────────────────────────┐" << endl;
                cout << "│                      Purchase Invoice                 │" << endl;
                cout << "├───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
                cout << "│ ID            │ Name          │ Price         │ Quantity      │" << endl;
                cout << "├───────────────┼───────────────┼───────────────┼───────────────┤" << endl;
                cout << "│ " << setw(13) << product.id << " │ "
                    << setw(13) << product.name << " │ "
                    << setw(13) << product.price << " │ "
                    << setw(13) << quantity << " │" << endl;
                cout << "└───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
                cout << "│ Total Amount: " << setw(42) << newInvoice.totalAmount << " │" << endl;
                cout << "└───────────────────────────────────────────────────────┘" << endl;

                cout << "Purchase successful! Thank you for your purchase." << endl;
                return;
            }
            else {
                cout << "Insufficient quantity! Available quantity: " << product.quantity << endl;
                goto d;
                return;
            }
        }
    }

    cout << "Product not found!" << endl;
}
// دالة لعرض جميع الفواتير الخاصة بالعميل
void displayInvoices() {
    if (currentUser.usertype != "customer") {
        cout << "You do not have permission to view invoices!" << endl;
        return;
    }

    if (invoices.empty()) {
        cout << "No invoices available!" << endl;
        return;
    }

    cout << "Invoices for customer: " << currentUser.username << endl;
    for (const Invoice& invoice : invoices) {
        if (invoice.customerUsername == currentUser.username) {
            cout << "\n\n\t\t___________________________________" << endl;
            cout << "\t\t|      Display Invoices        |" << endl;
            cout << "\t\t|__________________________________|" << endl;
            cout << "┌───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
            cout << "│ ID            │ Name          │ Price         │ Quantity      │" << endl;
            cout << "├───────────────┼───────────────┼───────────────┼───────────────┤" << endl;

            for (const Product& product : invoice.products) {
                cout << "│ " << setw(13) << product.id << " │ "
                    << setw(13) << product.name << " │ "
                    << setw(13) << product.price << " │ "
                    << setw(13) << product.quantity << " │" << endl;
            }

            cout << "└───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
            cout << "Total Amount: " << invoice.totalAmount << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

// دالة لإضافة موظف (للمدير فقط)
void addEmployee() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to add employees!" << endl;
        return;
    }

    registerUser("employee");
}

// دالة لعرض المستخدمين حسب النوع (للمدير فقط)
void displayUsersByType() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to view users!" << endl;
        return;
    }

    string type;
    cout << "Enter user type (admin, employee, customer): ";
    cin >> type;
    cout << "\n\n\t\t___________________________________" << endl;
    cout << "\t\t|      Display Users By Type        |" << endl;
    cout << "\t\t|__________________________________|" << endl;
    cout << "┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐" << endl;
    cout << "│ Username      │ Type          │ Gender        │ Phone         │ Active        │" << endl;
    cout << "├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤" << endl;

    for (const User& user : users) {
        if (user.usertype == type) {
            cout << "│ " << setw(13) << user.username << " │ "
                << setw(13) << user.usertype << " │ "
                << setw(13) << user.gender << " │ "
                << setw(13) << user.phonenumber << " │ "
                << setw(13) << (user.isactive ? "Yes" : "No") << " │" << endl;
        }
    }

    cout << "└───────────────┴───────────────┴───────────────┴───────────────┴───────────────┘" << endl;
}
// دالة لعرض المستخدمين حسب النوع (للمدير فقط)
void displayUsersByGender() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to view users!" << endl;
        return;
    }

    string type;
    cout << "Enter user type ( Male , Female ): ";
    cin >> type;

    cout << "Username\tType\tGender\tPhone\tActive" << endl;
    for (const User& user : users) {
        if (user.gender == type) {
            cout << user.username << "\t" << user.usertype << "\t" << user.gender << "\t" << user.phonenumber << "\t" << (user.isactive ? "Yes" : "No") << endl << endl;
        }
    }
}

void displayAllEmployee() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to view employees!" << endl;
        return;
    }

    if (users.empty()) {
        cout << "No employees available!" << endl;
        return;
    }

    // عرض الجدول مع الحدود
    cout << "\n\n\t\t___________________________________" << endl;
    cout << "\t\t|      Display All Employee        |" << endl;
    cout << "\t\t|__________________________________|" << endl;
    cout << "________________________________________________________________________________" << endl;
    cout << "|  Username    | Type          | Gender        | Phone         | Active         | " << endl;
    cout << "|_______________________________________________________________________________|" << endl;

    for (const User& user : users) {
        if (user.usertype == "employee") {
            cout << "| " << setw(13) << user.username << " | "
                << setw(13) << user.usertype << " | "
                << setw(13) << user.gender << " | "
                << setw(13) << user.phonenumber << " | "
                << setw(13) << (user.isactive ? "Yes" : "No") << " |" << endl;
        }
    }

    cout << "|_______________|_______________|_______________|_______________|_______________|\n" <<endl<< endl;
}
// دالة لإزالة مستخدم (للمدير فقط)
void removeUser() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to remove users!" << endl;
        return;
    }

    string username;
    cout << "Enter username to remove: ";
    cin.ignore(); // تجاهل الأحرف المتبقية في buffer
    getline(cin, username); // السماح بإدخال الاسم الكامل

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->username == username) {
            users.erase(it);
            cout << "User removed successfully!" << endl;
            return;
        }
    }

    cout << "User not found!" << endl;
}

// دالة  لتفعيل مستخدم (للمدير فقط)
void toggleUserActive() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to toggle user active status!" << endl;
        return;
    }

    string username;
    cout << "Enter username to toggle active status: ";
    cin.ignore(); // تجاهل الأحرف المتبقية في buffer
    getline(cin, username); // السماح بإدخال الاسم الكامل

    for (User& user : users) {
        if (user.username == username) {
			if (user.isactive == false) {
				user.isactive = true;
               cout << "User Is active  successfully!" << endl << endl;
			
			}
			else {
				
				cout << "User Is active !" << endl << endl;
			}
            return;

        }
    }

    cout << "User not found!" << endl;
}

// دالة لإيقاف  مستخدم (للمدير فقط)
void toggleUserNoActive() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to toggle user active status!" << endl;
        return;
    }

    string username;
    cout << "Enter username to toggle active status: ";
    cin.ignore(); // تجاهل الأحرف المتبقية في buffer
    getline(cin, username); // السماح بإدخال الاسم الكامل

    for (User& user : users) {
        if (user.username == username) {
			if (user.isactive == true) {
				user.isactive = false;
            cout << "User  Is  unactive !" << endl << endl;
			
			}
			else {
				cout << "User Is unactive !" << endl << endl;
			}
            return;

        }
    }

    cout << "User not found!" << endl;
}


// دالة لعرض عدد السجلات (للمدير فقط)
void displayStatistics() {
    if (currentUser.usertype != "admin") {
        cout << "You do not have permission to view statistics!" << endl;
        return;
    }

    cout << "Number of users: " << users.size() << endl;
    cout << "Number of products: " << products.size() << endl;
    cout << "Number of invoices: " << invoices.size() << endl << endl;
}

// دالة لحفظ البيانات في ملفات
void saveData() {
    ofstream userFile("users.txt");
    for (const User& user : users) {
        userFile << user.username << " " << user.password << " " << user.usertype << " " << user.phonenumber << " " << user.gender << " " << user.isactive << endl;
    }
    userFile.close();

    ofstream productFile("products.txt");
    for (const Product& product : products) {
        productFile << product.id << " " << product.name << " " << product.price << " " << product.quantity << endl;
    }
    productFile.close();

    ofstream invoiceFile("invoices.txt");
    for (const Invoice& invoice : invoices) {
        invoiceFile << invoice.customerUsername << " " << invoice.totalAmount << endl;
        for (const Product& product : invoice.products) {
            invoiceFile << product.id << " " << product.name << " " << product.price << " " << product.quantity << endl;
        }
    }
    invoiceFile.close();
}

// دالة لتحميل البيانات من الملفات
void loadData() {
    ifstream userFile("users.txt");
    User user;
    while (userFile >> user.username >> user.password >> user.usertype >> user.phonenumber >> user.gender >> user.isactive) {
        users.push_back(user);
    }
    userFile.close();

    ifstream productFile("products.txt");
    Product product;
    while (productFile >> product.id >> product.name >> product.price >> product.quantity) {
        products.push_back(product);
    }
    productFile.close();

    ifstream invoiceFile("invoices.txt");
    Invoice invoice;
    while (invoiceFile >> invoice.customerUsername >> invoice.totalAmount) {
        Product product;
        while (invoiceFile >> product.id >> product.name >> product.price >> product.quantity) {
            invoice.products.push_back(product);
        }
        invoices.push_back(invoice);
    }
    invoiceFile.close();
}

// الدالة الرئيسية
int main() {
    loadData();

    // إذا لم يكن هناك مدير، يتم إنشاء مدير لأول مرة
    if (users.empty()) {
        cout << "No admin found. Please register an admin account." << endl;
        registerUser("admin");
    }

    while (true) {
        cout << "1. Login\n2. Register (Customer)\n3. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            if (login()) {
                while (true) {
                    if (currentUser.usertype == "admin") {
                        cout << "1. Add Employee\n2. Display Users by Type\n3. Display Users By Gender\n4. Remove User\n5. Active User \n6. UnActive User\n7. Display Statistics\n8. Display All Employee\n9. Logout\n";
                        int adminChoice;
                        cin >> adminChoice;
                        if (adminChoice == 1) addEmployee();
                        else if (adminChoice == 2) displayUsersByType();
                        else if (adminChoice == 3) displayUsersByGender();
                        else if (adminChoice == 4) removeUser();
                        else if (adminChoice == 5) toggleUserActive();
                        else if (adminChoice == 6) toggleUserNoActive();
                        else if (adminChoice == 7) displayStatistics();
                        else if (adminChoice == 8) displayAllEmployee();
                        else if (adminChoice == 9) break;
                    }
                    else if (currentUser.usertype == "employee") {
                        cout << "1. Add Product\n2. Delete Product\n3. Modify Product\n4. Display Product\n5. Display Products\n6. Search Product\n7. Logout\n";
                        int employeeChoice;
                        cin >> employeeChoice;
                        if (employeeChoice == 1) addProduct();
                        else if (employeeChoice == 2) deleteProduct();
                        else if (employeeChoice == 3) modifyProduct();
                        else if (employeeChoice == 4) displayProduct();
                        else if (employeeChoice == 5) displayProducts();
                        else if (employeeChoice == 6) searchProduct();
                        else if (employeeChoice == 7) break;
                    }
                    else if (currentUser.usertype == "customer") {
                        cout << "1. Display Products\n2. Purchase Product\n3. Display Invoices\n4. Logout\n";
                        int customerChoice;
                        cin >> customerChoice;
                        if (customerChoice == 1) displayProducts();
                        else if (customerChoice == 2) purchaseProduct();
                        else if (customerChoice == 3) displayInvoices();
                        else if (customerChoice == 4) break;
                    }
                }
            }
        }
        else if (choice == 2) {
            registerUser("customer");
        }
        else if (choice == 3) {
            saveData();
            break;
        }
    }

    return 0;
}