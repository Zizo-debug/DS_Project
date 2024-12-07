#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include <iomanip>
#include <conio.h>
#include <stack>
using namespace std;

int currUserId = 0;

class Restaurants;

bool isValidPassword(const string& password) {
    if (password.length() < 8 || password.length() > 12) {
        cout << "Password must be within 8 and 12 characters long.\n";
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false, hasSpace = false;

    for (char ch : password) {
        if (ch >= 'A' && ch <= 'Z') {
            hasUpper = true;
        }
        else if (ch >= 'a' && ch <= 'z') {
            hasLower = true;
        }
        else if (ch >= '0' && ch <= '9') {
            hasDigit = true;
        }
        else if (ch == ' ') {
            hasSpace = true;
        }
        else {
            hasSpecial = true;
        }
    }

    if (!hasUpper) {
        cout << "Password must include at least one uppercase letter.\n";
    }
    if (!hasLower) {
        cout << "Password must include at least one lowercase letter.\n";
    }
    if (!hasDigit) {
        cout << "Password must include at least one number.\n";
    }
    if (!hasSpecial) {
        cout << "Password must include at least one special character.\n";
    }

    return hasUpper && hasLower && hasDigit && hasSpecial && !hasSpace;
}

string getPasswordInput(bool forConfirmation = false) {
    string password;
    char ch;
    if (forConfirmation) {
        cout << "Confirm password: ";
    }
    else {
        cout << "Enter your password: ";
    }
    while (true) {
        ch = _getch(); // Capture a single character without displaying it

        if (ch == '\r') { // Enter key (carriage return indicates end of input)
            cout << endl;
            break;
        }
        else if (ch == '\b') { // Backspace
            if (!password.empty()) {
                cout << "\b \b"; // Move back, overwrite with space, and move back again
                password.pop_back();
            }
        }
        else {
            cout << "*"; // Display asterisk for each typed character
            password += ch;
        }
    }

    return password;
}

class Employee {
private:
    static int IdCounter;
    int id;
    string name;
    string email;
    string password;
    Restaurants* workplace;
    string getHiddenPassword() {
        string hiddenPassword;
        char ch;
        while ((ch = getchar()) != '\n') {
            if (ch == '\b') { // Handle backspace for password input
                if (!hiddenPassword.empty()) {
                    hiddenPassword.pop_back();
                    cout << "\b \b"; // Move back, overwrite with space, and move back again
                }
            }
            else {
                hiddenPassword.push_back(ch);
                cout << ' '; // Mask input with ''
            }
        }
        cout << endl;
        return hiddenPassword;
    }

public:
    Employee(const string& name = "", const string& email = "", const string& password = "", Restaurants* work = nullptr) {
        id = IdCounter++;
        this->name = name;
        this->email = email;
        this->password = password;
        this->workplace = work;
    }
    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    string getEmail() {
        return email;
    }
    string getPassword() {
        return password;
    }
    void setName(string& newName) {
        name = newName;
    }
    void setEmail(string& newEmail) {
        email = newEmail;
    }
    void setPassword(string& newPassword) {
        password = newPassword;
    }
    bool login(string inputEmail, string inputPassword) {
        return email == inputEmail && password == inputPassword;
    }
    int hashById(int tableSize) {
        return id % tableSize;
    }
    //manager sign up
    Employee* managerSignUp() {
        string name, email, password;

        cout << "Enter employee name: ";
        getline(cin, name);
        if (name.empty()) {
            cout << "Name cannot be empty.\n";
            return nullptr;
        }

        cout << "Enter employee email: ";
        getline(cin, email);

        do {
            cout << "Enter employee password: ";
            getline(cin, password);
            if (!isValidPassword(password)) {
                cout << "Please enter a valid password.\n";
            }
        } while (!isValidPassword(password));

        // Create and return the new Employee object
        Restaurants* work = nullptr; // Assign workplace if needed
        Employee* newEmployee = new Employee(name, email, password, work);
        cout << "Employee account created successfully with ID: " << newEmployee->getId() << endl;
        return newEmployee;
    }
    string secureInputPassword() {
        string password;
        char ch;
        cout << "Enter Password: ";
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // Handle backspace
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Remove the character from display
                }
            }
            else {
                password.push_back(ch);
                cout << '*'; // Show asterisks instead of the actual password
            }
        }
        cout << endl;
        return password;
    }
    void editName() {
        cout << "Current name: " << name << "\nEnter new name: ";
        string newName;
        getline(cin, newName);
        if (!newName.empty()) {
            setName(newName);
            cout << "Name updated successfully to: " << name << endl;
        }
        else {
            cout << "Name update canceled.\n";
        }
    }
    bool isValidPassword(const string& password) {
        if (password.length() < 8 || password.length() > 12) {
            cout << "Password length must be between 8 and 12 characters.\n";
            return false;
        }

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;

        // Check for each condition
        for (char ch : password) {
            if (isupper(ch)) hasUpper = true;
            else if (islower(ch)) hasLower = true;
            else if (isdigit(ch)) hasDigit = true;
            else if (ispunct(ch)) hasSpecial = true;
        }

        // Verify all conditions are met
        if (!hasUpper) {
            cout << "Password must contain at least one uppercase letter.\n";
            return false;
        }
        if (!hasLower) {
            cout << "Password must contain at least one lowercase letter.\n";
            return false;
        }
        if (!hasDigit) {
            cout << "Password must contain at least one digit.\n";
            return false;
        }
        if (!hasSpecial) {
            cout << "Password must contain at least one special character.\n";
            return false;
        }

        return true;
    }


    void resetPassword() {
        cout << "Enter current password: ";
        string currentPassword = getHiddenPassword();

        if (currentPassword == password) {
            cout << "Enter new password: ";
            string newPassword = getHiddenPassword();

            cout << "Confirm new password: ";
            string confirmPassword = getHiddenPassword();

            if (newPassword == confirmPassword) {
                setPassword(newPassword);
                cout << "Password reset successfully.\n";
            }
            else {
                cout << "Passwords do not match. Password reset failed.\n";
            }
        }
        else {
            cout << "Incorrect current password. Password reset failed.\n";
        }
    }
};


class EmployeeHashMap {
private:
    static const int MAP_SIZE = 10; // Fixed size for simplicity
    Employee* hashMap[MAP_SIZE]; // Array of Employee pointers
    int currentSize;


    int hashFunction(int id) const {
        return id % MAP_SIZE;
    }

    int probe(int hash, int i) const {
        return (hash + i) % MAP_SIZE;
    }

public:
    EmployeeHashMap() {
        // Initialize hashMap with nullptrs
        for (int i = 0; i < MAP_SIZE; i++) {
            hashMap[i] = nullptr;
        }
        currentSize = 0;
    }

    // Insert an Employee into the hash table
    bool signup(const string& name, const string& email, const string& password) {
        if (currentSize >= MAP_SIZE) {
            cout << "Hash table is full!" << endl;
            return false;
        }

        for (int i = 0; i < MAP_SIZE; i++) {
            if (hashMap[i] && hashMap[i]->getEmail() == email) {
                cout << "Email already exists!" << endl;
                return false;
            }
        }

        Employee* newEmployee = new Employee(name, email, password);
        int hashIndex = hashFunction(newEmployee->getId());
        int i = 0;

        // Find the next available slot using linear probing possibly ideally the first spot we check
        while (hashMap[probe(hashIndex, i)] != nullptr) {
            i++;
            if (i >= MAP_SIZE) {
                delete newEmployee;
                cout << "Hash table is full!" << endl;
                return false;
            }
        }

        hashMap[probe(hashIndex, i)] = newEmployee;
        currentSize++;
        cout << "Signup successful! Your ID is: " << newEmployee->getId() << endl;
        currUserId = newEmployee->getId();
        return true;
    }

    bool login(int id, const string& email, const string& password) {
        int indexOfId = hashFunction(id);
        for (int i = 0; i < MAP_SIZE; i++) {
            int indexToCheck = (indexOfId + i) % MAP_SIZE;
            //find id match starting with its hashed id (where it should be)
            if (hashMap[indexToCheck] && !(hashMap[indexToCheck]->getId() == id)) {
                continue;
            }
            //if id match found check if email and password are correct
            if (hashMap[indexToCheck] && hashMap[indexToCheck]->getEmail() == email && hashMap[indexToCheck]->getPassword() == password) {
                cout << "Login successful!" << endl;
                return true;
            }
            //if id match was found but the id did not match the email and password then login failed
            break;
        }
        cout << "Invalid email or password!" << endl;
        return false;
    }
    string getHiddenPassword() {
        string hiddenPassword;
        char ch;
        while ((ch = getchar()) != '\n') {
            if (ch == '\b') { // Handle backspace for password input
                if (!hiddenPassword.empty()) {
                    hiddenPassword.pop_back();
                    cout << "\b \b"; // Move back, overwrite with space, and move back again
                }
            }
            else {
                hiddenPassword.push_back(ch);
                cout << ' '; // Mask input with ''
            }
        }
        cout << endl;
        return hiddenPassword;
    }
    void resetPassword() {
        int id;
        string currentPassword, newPassword;

        cout << "Enter your ID: ";
        cin >> id;
        cin.ignore();

        Employee* employee = getEmployee(id);
        if (!employee) {
            cout << "Employee not found!" << endl;
            return;
        }

        cout << "Old password confirmation:\n";
        currentPassword = getPasswordInput(false);
        if (employee->getPassword() != currentPassword) {
            cout << "Incorrect password!" << endl;
            return;
        }
        cout << "Employee password: " << employee->getPassword();

        cout << "\nNew password:\n";
        newPassword = getPasswordInput(false);

        employee->setPassword(newPassword);
        cout << "Password reset successful!" << endl;
    }
    // Display the hash table
    void display() {
        for (int i = 0; i < MAP_SIZE; i++) {
            if (hashMap[i] != nullptr) {
                cout << "Index " << i << ": " << hashMap[i]->getName() << " (ID: " << hashMap[i]->getId() << ")\n";
            }
            else {
                cout << "Index " << i << ": [empty]\n";
            }
        }
    }

    Employee* getEmployee(int id) {
        int hash = hashFunction(id);
        int i = 0;

        while (i < MAP_SIZE) {
            int index = probe(hash, i);
            if (hashMap[index] == nullptr) {
                return nullptr;
            }
            if (hashMap[index]->getId() == id) {
                return hashMap[index];
            }
            i++;
        }
        return nullptr;
    }
};


int Employee::IdCounter = 10000;



class Customer {
private:
    static int custIdCounter;
    int id;
    string name;
    string email;
    string password;

public:
    Customer(const string& name = "", const string& email = "", const string& password = "") {
        id = custIdCounter++;
        this->name = name;
        this->email = email;
        this->password = password;
    }

    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    string getEmail() {
        return email;
    }
    string getPassword() {
        return password;
    }

    void setName(string& newName) {
        name = newName;
    }
    void setEmail(string& newEmail) {
        email = newEmail;
    }
    void setPassword(string& newPassword) {
        password = newPassword;
    }
};

int Customer::custIdCounter = 10000;

class CustomerManagement {
private:
    static const int MAP_SIZE = 10;
    Customer* hashMap[MAP_SIZE];
    int currentSize;

    int hashFunction(int id) const {
        return id % MAP_SIZE;
    }

    int probe(int hash, int i) const {
        return (hash + i) % MAP_SIZE;
    }

public:
    CustomerManagement() : currentSize(0) {
        for (int i = 0; i < MAP_SIZE; i++) {
            hashMap[i] = nullptr;
        }
    }

    ~CustomerManagement() {
        for (int i = 0; i < MAP_SIZE; i++) {
            delete hashMap[i];
        }
    }

    bool signup(const string& name, const string& email, const string& password) {
        if (currentSize >= MAP_SIZE) {
            cout << "Hash table is full!" << endl;
            return false;
        }

        for (int i = 0; i < MAP_SIZE; i++) {
            if (hashMap[i] && hashMap[i]->getEmail() == email) {
                cout << "Email already exists!" << endl;
                return false;
            }
        }

        Customer* newCustomer = new Customer(name, email, password);
        int hashIndex = hashFunction(newCustomer->getId());
        int i = 0;

        // Find the next available slot using linear probing possibly ideally the first spot we check
        while (hashMap[probe(hashIndex, i)] != nullptr) {
            i++;
            if (i >= MAP_SIZE) {
                delete newCustomer;
                cout << "Hash table is full!" << endl;
                return false;
            }
        }

        hashMap[probe(hashIndex, i)] = newCustomer;
        currentSize++;
        cout << "Signup successful! Your ID is: " << newCustomer->getId() << endl;
        currUserId = newCustomer->getId();
        return true;
    }

    bool login(int id, const string& email, const string& password) {
        int indexOfId = hashFunction(id);
        for (int i = 0; i < MAP_SIZE; i++) {
            int indexToCheck = (indexOfId + i) % MAP_SIZE;
            //find id match starting with its hashed id (where it should be)
            if (hashMap[indexToCheck] && !(hashMap[indexToCheck]->getId() == id)) {
                continue;
            }
            //if id match found check if email and password are correct
            if (hashMap[indexToCheck] && hashMap[indexToCheck]->getEmail() == email && hashMap[indexToCheck]->getPassword() == password) {
                cout << "Login successful!" << endl;
                currUserId = id;
                return true;
            }
            //if id match was found but the id did not match the email and password then login failed
            break;
        }
        cout << "Invalid email or password!" << endl;
        return false;
    }

    Customer* getCustomer(int id) {
        int hash = hashFunction(id);
        int i = 0;

        while (i < MAP_SIZE) {
            int index = probe(hash, i);
            if (hashMap[index] == nullptr) {
                return nullptr;
            }
            if (hashMap[index]->getId() == id) {
                return hashMap[index];
            }
            i++;
        }
        return nullptr;
    }

    string getHiddenPassword() {
        string hiddenPassword;
        char ch;
        while ((ch = getchar()) != '\n') {
            if (ch == '\b') { // Handle backspace for password input
                if (!hiddenPassword.empty()) {
                    hiddenPassword.pop_back();
                    cout << "\b \b"; // Move back, overwrite with space, and move back again
                }
            }
            else {
                hiddenPassword.push_back(ch);
                cout << ' '; // Mask input with ''
            }
        }
        cout << endl;
        return hiddenPassword;
    }
    void resetPassword() {
        int id;
        string currentPassword, newPassword;

        cout << "Enter your ID: ";
        cin >> id;
        cin.ignore();

        Customer* customer = getCustomer(id);
        if (!customer) {
            cout << "Customer not found!" << endl;
            return;
        }

        cout << "Old password confirmation:\n";
        currentPassword = getPasswordInput(false);
        if (customer->getPassword() != currentPassword) {
            cout << "Incorrect password!" << endl;
            return;
        }
        cout << "Customer password: " << customer->getPassword();

        cout << "\nNew password:\n";
        newPassword = getPasswordInput(false);

        customer->setPassword(newPassword);
        cout << "Password reset successful!" << endl;
    }

    void displayAllCustomers() {
        cout << "\nCustomer List:" << endl;
        for (int i = 0; i < MAP_SIZE; i++) {
            if (hashMap[i] != nullptr) {
                cout << "ID: " << hashMap[i]->getId()
                    << ", Name: " << hashMap[i]->getName()
                    << ", Email: " << hashMap[i]->getEmail() << endl;
            }
        }
    }
};

//Restaurants
string getPasswordInput(bool forConfirmation);

int generateAutoID()
{
    static int i = 9999;
    i++;
    return i;
}

//Dishes
class Dishes
{
public:
    int ID;
    string name;
    string type;
    double Price;
    Dishes* left;
    Dishes* right;
    Dishes()
    {
        ID = generateAutoID();
        name = "";
        type = "";
        Price = 0;
        left = nullptr;
        right = nullptr;
    }
    Dishes(string n, string t, double p)
    {
        ID = generateAutoID();
        name = n;
        type = t;
        Price = p;
        left = nullptr;
        right = nullptr;
    }
    string getDetails()
    {
        cout << "Name: " << name << endl << "Type: " << type << endl << "Price: " << Price << endl;
    }

};
//Menu
struct Menu {
    int ID;
    string name;
    int totalDishes;
    Dishes* root;
    Menu(string n)
    {
        ID = generateAutoID();
        name = n;
        totalDishes = 0;
        root = nullptr;
    }
    Dishes* getRoot()
    {
        return root;
    }
    void setRoot(Dishes* r)
    {
        root = r;
    }
    Dishes* addDishToMenu(Dishes* root, string name, string type, double price)
    {
        if (!root)
        {
            totalDishes++;
            return new Dishes(name, type, price);
        }

        if (name < root->name)
        {
            root->left = addDishToMenu(root->left, name, type, price);

            totalDishes++;
        }

        else if (name > root->name)
        {
            totalDishes++;
            root->right = addDishToMenu(root->right, name, type, price);

        }

        return root;
    }
    //edit
    void edit(Dishes* root, string name, string type) {
        if (!root) {
            cout << "Dish not found.\n";
            return;
        }

        // Search for the dish
        if (name < root->name) {
            edit(root->left, name, type);
        }
        else if (name > root->name) {
            edit(root->right, name, type);
        }
        else if (root->type != type) {
            // Found name but type doesn't match
            cout << "Dish with name '" << name << "' found, but type mismatch.\n";
        }
        else {
            // Dish found, allow editing
            cout << "Editing dish: " << root->name << " (" << root->type << ")\n";
            cout << "Current price: $" << root->Price << endl;

            // Update dish details
            cout << "Enter new name (or press Enter to keep unchanged): ";
            string newName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, newName);
            if (!newName.empty())
                root->name = newName;

            cout << "Enter new type (or press Enter to keep unchanged): ";
            string newType;
            getline(cin, newType);
            if (!newType.empty())
                root->type = newType;

            cout << "Enter new price (or press Enter to keep unchanged): ";
            string priceInput;
            getline(cin, priceInput);
            if (!priceInput.empty()) {
                double newPrice = stod(priceInput); // Convert input to double
                root->Price = newPrice;
            }

            cout << "Dish updated successfully!\n";
        }
    }

    //delete
    Dishes* findMin(Dishes* root) {
        while (root && root->left)
            root = root->left;
        return root;
    }
    Dishes* deleteDishHelper(Dishes* root, string name, string type) {
        if (!root) {
            cout << "Dish not found.\n";
            return nullptr;
        }

        if (name < root->name) {
            root->left = deleteDishHelper(root->left, name, type);
        }
        else if (name > root->name) {
            root->right = deleteDishHelper(root->right, name, type);
        }
        else if (root->type != type) {
            cout << "Dish with name '" << name << "' found, but type mismatch.\n";
            return root;
        }
        else {
            if (!root->left && !root->right) {
                // Case 1: No children
                delete root;
                totalDishes--;
                return nullptr;
            }
            else if (!root->left) {
                // Case 2: One child (right)
                Dishes* temp = root->right;
                delete root;
                totalDishes--;
                return temp;
            }
            else if (!root->right) {
                // Case 2: One child (left)
                Dishes* temp = root->left;
                delete root;
                totalDishes--;
                return temp;
            }
            else {
                // Case 3: Two children
                Dishes* temp = findMin(root->right); // Find in-order successor
                root->name = temp->name;          // Copy successor's data
                root->type = temp->type;
                root->Price = temp->Price;
                root->right = deleteDishHelper(root->right, temp->name, temp->type); // Delete successor
                totalDishes--;
            }
        }

        return root;
    }

    void deleteDish(Dishes* root, string name, string type) {
        root = deleteDishHelper(root, name, type);


    }

    void displayMenu(Dishes* root)
    {
        if (!root)
            return;

        displayMenu(root->left);
        cout << "Dish: " << root->name << ", Price: $" << root->Price << endl;
        displayMenu(root->right);
    }

    Dishes* returnDish(string name) {

    }
};

struct Order {
    int ID;
    Dishes* dishList;
    double totalCost;
    string type; // Premium, Express, or Normal
    Customer* customer;
    Employee* employee;

    Order(Dishes* list = nullptr, double cost = 0, string t = "", Customer* customer = nullptr, Employee* employee = nullptr)
        : dishList(list), totalCost(cost), type(t), customer(customer), employee(employee) {
        static int nextID = 10000; // Auto-generate 5-digit IDs
        ID = nextID++;
       
    }
    
    Order(const Order& other)
        : ID(other.ID), // Copy ID directly
        totalCost(other.totalCost), // Copy totalCost directly
        type(other.type), // Copy type directly
        customer(other.customer), // Shallow copy Customer pointer
        employee(other.employee)  // Shallow copy Employee pointer
    {
        // Deep copy the binary tree representing the dish list
        dishList = copyTree(other.dishList);
    }

    Dishes* copyTree(Dishes* node) {
        if (node == nullptr) {
            return nullptr;
        }
        Dishes* newNode = new Dishes(*node); // Assume Dishes has a copy constructor
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    void addDish(Dishes* newDish) {
        // If the tree is empty, the new dish becomes the root
        if (dishList == nullptr) {
            dishList = newDish;
        }
        else {
            // signUp the dish into the binary tree based on ID
            Dishes* current = dishList;
            Dishes* parent = nullptr;
            while (current != nullptr) {
                parent = current;
                if (newDish->ID < current->ID) {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            if (newDish->ID < parent->ID) {
                parent->left = newDish;
            }
            else {
                parent->right = newDish;
            }
        }
        // Update the total cost of the order
        totalCost += newDish->Price;
    }

    // Adjust cost based on type
    void setExtraCost() {
        if (type == "Premium") {
            totalCost += 500; // Add flat Rs. 500 for premium orders
        }
        else if (type == "Express") {
            totalCost += totalCost * 0.1; // Add 10% extra cost for express orders

        }
    }

    void displayDishList(Dishes* root) const
    {
        if (!root)
            return;

        displayDishList(root->left);
        cout << "Dish: " << root->name << ", Price: $" << root->Price << endl;
        displayDishList(root->right);
    }

    void displayOrder() const {

        cout << "Im here";
        cout << "Order ID: " << ID << "\n"
            << "Type: " << type << "\n"
            << "Customer ID: " << (customer ? customer->getId() : -1) << "\n"
            << "Employee ID: " << (employee ? employee->getId() : -1) << "\n"
            << "Total Cost: " << totalCost << "\n";
            displayDishList(this->dishList);
            cout<<"Extra cost(Order type) = ";
            if(type == "Premium")
            {
                cout<<500;
            }
            else if(type == "Express")
            {
                cout<<totalCost*0.1;
            }
            else
            {
                cout<<"NA";
            }
    
    }

    ~Order() {
        clearTree(dishList);
    }

    void clearTree(Dishes* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }
};

// Node class for the queue
class Node {
public:
    Order data;
    Node* next;

    Node(Order order) : data(order), next(nullptr) {}
};

// Queue class definition
class Queue {
private:
    Node* frontNode;
    Node* backNode;


    // Helper function to copy another queue
    void copyFrom(const Queue& other) {
        if (other.frontNode == nullptr) {
            frontNode = backNode = nullptr;
            return;
        }
        Node* temp = other.frontNode;
        while (temp != nullptr) {
            push(temp->data); // Reuse the push function to add nodes
            temp = temp->next;
        }
    }

    // Helper function to clear the queue
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }


public:
    // Constructor
    Queue() : frontNode(nullptr), backNode(nullptr) {}

    // Destructor
    ~Queue() {
        clear();
    }

    // Copy constructor
    Queue(const Queue& other) : frontNode(nullptr), backNode(nullptr) {
        copyFrom(other);
    }

    // Assignment operator
    Queue& operator=(const Queue& other) {
        if (this != &other) { // Avoid self-assignment
            clear();          // Clear the current queue
            copyFrom(other);  // Copy from the other queue
        }
        return *this;
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return frontNode == nullptr;
    }

    // Push an order to the queue
    void push(const Order& order) {
        Node* newNode = new Node(order);
        if (isEmpty()) {
            frontNode = backNode = newNode;
        }
        else {
            backNode->next = newNode;
            backNode = newNode;
        }
    }

    // Pop an order from the front of the queue
    void pop() {
        if (isEmpty()) {
            cout << "Queue is empty, cannot pop!" << endl;
            return;
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) { // Queue is now empty
            backNode = nullptr;
        }
        delete temp;
    }

    // Get the front order in the queue
    Order front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty, no front element!");
        }
        return frontNode->data;
    }
};

class OrderQueue {
private:
    Queue orders;

public:
    OrderQueue()
    {

    }
    void addOrder(Order* newOrder) {
        if (newOrder == nullptr) {
            cout << "Error: newOrder is null." << endl;
            return;
        }
        newOrder->setExtraCost();
        cout << (*newOrder).ID << "\nyes3";
        orders.push(*newOrder); //enqueue
        cout << orders.front().ID;
        cout << "Order added successfully with ID: " << newOrder->ID << "\n";
    }

    // Cancel the first order of a specific type
    void cancelOrder(int orderID) {
        Queue tempQueue;
        bool orderCanceled = false;

        while (!orders.isEmpty()) {
            Order currentOrder = orders.front();
            orders.pop();
            if (!orderCanceled && currentOrder.ID == orderID) {
                cout << "Order with ID " << currentOrder.ID << " canceled.\n";
                orderCanceled = true;
            }
            else {
                tempQueue.push(currentOrder);
            }
        }

        // Restore remaining orders to the main queue
        orders = tempQueue;

        if (!orderCanceled) {
            cout << "No order with ID " << orderID << " to cancel.\n";
        }
    }

    // Process the highest-priority order
    Order processOrder() {
        if (orders.isEmpty()) {
            cout << "No orders to process.\n";
            Order o1 = NULL;
            return o1;
        }

        queue<Order> tempQueue;
        Order* highestPriorityOrder = new Order();

        // Find the highest-priority order
        while (!orders.isEmpty()) {
            Order currentOrder = orders.front();

            if (!highestPriorityOrder ||
                (currentOrder.type == "Premium" && highestPriorityOrder->type != "Premium") ||
                (currentOrder.type == "Express" && highestPriorityOrder->type == "Normal")) {
                if (highestPriorityOrder) {
                    tempQueue.push(*highestPriorityOrder);
                }
                highestPriorityOrder = &currentOrder;
            }
            else {
                tempQueue.push(currentOrder);
            }

            orders.pop();
        }

        // Process the highest-priority order
        if (highestPriorityOrder) {
            cout << "Processing Order:\n";
            highestPriorityOrder->displayOrder();
        }

        return *highestPriorityOrder;

        while (!tempQueue.empty()) {
            orders.push(tempQueue.front());
            tempQueue.pop();
        }
    }

    // Display all orders (optional, for debugging)
    void displayAllOrders() {
        if (orders.isEmpty()) {
            cout << "No orders in the queue.\n";
            return;
        }

        Queue tempQueue = orders; // Copy queue to display without modifying
        while (!tempQueue.isEmpty()) {
            Order currentOrder = tempQueue.front();
            tempQueue.pop();
            currentOrder.displayOrder();
            cout << "----------------------\n";
        }
    }
};

//Linked list
class Restaurants {
public:
    int ID;
    string name;
    string type;
    Menu* menu;
    Employee* Manager;
    OrderQueue* orders;
    Restaurants* next;
    Restaurants()
    {
        ID = generateAutoID();
        name = "FAST CAFE";
        type = "Cafe";
        menu = new Menu(name);
        orders = nullptr;
        Manager = nullptr;
        next = nullptr;
    }
    Restaurants(string n, string t, Menu* m, Employee* Man)
    {
        ID = generateAutoID();
        name = n;
        type = t;
        menu = m;
        orders = new OrderQueue();
        Manager = Man;
        next = nullptr;
    }
};
class RestaurantClass {
private:
    Restaurants* head;
public:
    Restaurants* getHead()
    {
        return head;
    }
    RestaurantClass()
    {
        head = nullptr;
    }
    RestaurantClass(string n, string t, Menu* m, Employee* Man)
    {
        head = new Restaurants(n, t, m, Man);
    }
    //works
    void addAtEnd(string n, string t, Menu* m, Employee* Man)
    {
        //create node
        Restaurants* newNode = new Restaurants(n, t, m, Man);
        //if no element
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Restaurants* temp = head;
        //traverse till end
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        //assign node
        temp->next = newNode;
    }
    void deleteRestaurant(string RestaurantName) {
        if (!getHead()) {
            cout << "The list is empty. Nothing to delete." << endl;
            return;
        }

        // Check if the head node is the one to delete
        if (head->name == RestaurantName) {
            Restaurants* temp = getHead();
            head = head->next;
            delete temp;
            cout << "Restaurant with name " << RestaurantName << " deleted." << endl;
            return;
        }

        // Search for the node to delete
        Restaurants* current = head;
        Restaurants* previous = nullptr;

        while (current && current->name != RestaurantName) {
            previous = current;
            current = current->next;
        }

        // If the node was not found
        if (!current) {
            cout << "Restaurant with name " << RestaurantName << " not found." << endl;
            return;
        }

        previous->next = current->next;
        delete current;
        cout << "Restaurant with name " << RestaurantName << " deleted." << endl;
    }
    void editRestaurant() {
        if (!head) {
            cout << "The list is empty. No restaurant to edit." << endl;
            return;
        }

        // Ask for the restaurant name to edit
        cout << "Enter the name of the restaurant you want to edit: ";
        string searchName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, searchName);

        // Search for the restaurant
        Restaurants* current = head;
        while (current && current->name != searchName) {
            current = current->next;
        }

        if (!current) {
            cout << "Restaurant with name \"" << searchName << "\" not found." << endl;
            return;
        }

        // Restaurant found, begin editing
        cout << "Editing restaurant: " << current->name << endl;

        // Update name
        cout << "Enter new name (or press Enter to keep unchanged): ";
        string newName;
        getline(cin, newName);
        if (!newName.empty()) {
            current->name = newName;
        }

        // Update type
        cout << "Enter new type (or press Enter to keep unchanged): ";
        string newType;
        getline(cin, newType);
        if (!newType.empty()) {
            current->type = newType;
        }



        cout << "Restaurant details updated successfully!" << endl;
    }
    Restaurants* searchRestaurantByName(string RestaurantName) {
        if (!head) {
            cout << "The restaurant list is empty." << endl;
            return nullptr;
        }

        Restaurants* current = head;
        while (current != nullptr) {
            if (current->name == RestaurantName) {
                return current; // Return the restaurant if found
            }
            current = current->next;
        }

        // If restaurant not found
        cout << "Restaurant with name \"" << RestaurantName << "\" not found." << endl;
        return nullptr;
    }
    void display()
    {
        Restaurants* temp = head;
        while (temp != nullptr)
        {
            cout << "Restaurant ID: " << temp->ID << endl << "Restaurant Name: " << temp->name << endl << "Restaurant Type: " << temp->type << endl;
            temp = temp->next;
        }
    }

    Restaurants* findName(string name = "") {
        Restaurants* temp = head;
        while (temp != nullptr) {
            if (temp->name == name) {
                return temp;
            }
        }
        return nullptr;
    }
};

struct promotions {
    static int idCounter;
    int id;
    string name;
    int discount;
    int limit;

    promotions(string Inputname = "", int Inputdiscount = 0, int Inputlimit = 0) {
        id = idCounter++;
        name = Inputname;
        discount = Inputdiscount;
        limit = Inputlimit;
    }
};

int promotions::idCounter = 10000;

class promotionsStack {
private:
    stack<promotions> ps;
public:
    void addPromotion(const promotions& promotion) {
        ps.push(promotion);
    }

    bool applyDiscount(Order*& order) {
        if (ps.empty()) {
            cout << "No active promotions to apply!" << endl;
            return false;
        }

        promotions& currentPromo = ps.top();

        int discountAmount = (currentPromo.discount * order->totalCost) / 100;
        order->totalCost -= discountAmount;
        currentPromo.limit--;

        cout << "Applied " << currentPromo.name << " promotion! Discount: " << discountAmount << " Remaining Limit: " << currentPromo.limit << endl;

        if (currentPromo.limit == 0) {
            cout << currentPromo.name << " promotion expired." << endl;
            ps.pop();
        }

        return true;
    }

    void removePromotion() {
        ps.pop();
    }

    bool hasPromotions() const {
        return !ps.empty();
    }

    void displayTopPromotion() const {
        if (ps.empty()) {
            cout << "No active promotions." << endl;
            return;
        }
        const promotions& topPromo = ps.top();
        cout << "Top Promotion: " << topPromo.name << " | Discount: " << topPromo.discount << "% | Remaining Uses: " << topPromo.limit << endl;
    }
};


struct Review {
    int reviewId;
    static int reviewIdCounter;
    string reviewText;
    int rating;
    int customerId; //Id of customer who added review
    Dishes* reviewableDish;
    Restaurants* reviewableRestaurant;

    void createReview(const string& type, Restaurants* r = nullptr, Dishes* d = nullptr) {
        if (type == "restaurant") {
            reviewableRestaurant = r;
            reviewableDish = nullptr;
        }
        else if (type == "dish") {
            reviewableRestaurant = nullptr;
            reviewableDish = d;
        }
        else {
            cout << "Invalid type. No review created." << endl;
            reviewableRestaurant = nullptr;
            reviewableDish = nullptr;
        }
    }

    Review(const string& text = "", int rate = 0, string type = "restaurant", Restaurants* r = nullptr, Dishes* d = nullptr, int custId = 10000) {
        reviewId = reviewIdCounter++;
        reviewText = text;
        rating = rate;
        customerId = custId;
        createReview(type, r, d);
    }
};

int Review::reviewIdCounter = 10000;

class ReviewHeap {
private:
    static const int MAX_SIZE = 100;
    Review heap[MAX_SIZE];
    int size;
    bool isMaxHeap;

    void HeapUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (compare(heap[index], heap[parent])) {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void HeapDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int selected = index;

            if (left < size && compare(heap[left], heap[selected])) {
                selected = left;
            }
            if (right < size && compare(heap[right], heap[selected])) {
                selected = right;
            }
            if (selected == index) {
                break;
            }

            swap(heap[index], heap[selected]);
            index = selected;
        }
    }

    bool compare(const Review& a, const Review& b) const {
        return isMaxHeap ? a.rating > b.rating : a.rating < b.rating;
    }

public:
    ReviewHeap(bool maxHeap) {
        size = 0;
        isMaxHeap = maxHeap;
    }

    void add(const Review& review) {
        if (size == MAX_SIZE) {
            cout << "Heap is full. Cannot add more reviews.\n";
            return;
        }
        heap[size] = review;
        HeapUp(size);
        size++;
    }

    void removeTop() {
        if (size == 0) {
            cout << "Heap is empty. Cannot remove top review.\n";
            return;
        }
        heap[0] = heap[--size];
        HeapDown(0);
    }

    Review getTop() const {
        if (size == 0) {
            cout << "Heap is empty.\n";
            return Review();
        }
        return heap[0];
    }

    bool viewReviewsByCustId(int custId) {
        for (int i = 0; i < size; i++) {
            if (custId == heap[i].customerId) {
                cout << i + 1 << ". " << heap[i].reviewText << " (Rating: " << heap[i].rating << ")\n";
            }
        }
    }

    bool removeByCustomerId(int customerId, int reviewId) {
        for (int i = 0; i < size; i++) {
            if (heap[i].customerId == customerId && heap[i].reviewId == reviewId) {
                heap[i] = heap[--size];
                HeapDown(i);
                return true;
            }
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    void displayTop(int count) const {
        int limit = min(count, size);
        for (int i = 0; i < limit; i++) {
            cout << i + 1 << ". " << heap[i].reviewText
                << " (Rating: " << heap[i].rating << ")\n";
        }
    }
};

class Reviews {
private:
    ReviewHeap goodReviews;
    ReviewHeap badReviews;

public:
    Reviews() : goodReviews(true), badReviews(false) {}

    void addReview(const string& reviewText, int rating, string type = "", Restaurants* r = nullptr, Dishes* d = nullptr, int custId = 10000) {
        if (rating >= 3) {
            goodReviews.add(Review(reviewText, rating, type, r, d, custId));
        }
        else {
            badReviews.add(Review(reviewText, rating, type, r, d, custId));
        }
    }

    void viewReviews(bool good, int count) {
        if (good) {
            cout << "Top " << count << " Good Reviews:\n";
            goodReviews.displayTop(count);
        }
        else {
            cout << "Top " << count << " Bad Reviews:\n";
            badReviews.displayTop(count);
        }
    }

    bool editReview(int customerId, int reviewId, const string& newText, int newRating, string type = "", Restaurants* r = nullptr, Dishes* d = nullptr) {
        // remove from good reviews first
        bool found = goodReviews.removeByCustomerId(customerId, reviewId);

        // If not in good reviews, check bad reviews
        if (!found) {
            found = badReviews.removeByCustomerId(customerId, reviewId);
        }

        // Add updated review if found
        if (found) {
            addReview(newText, newRating, type, r, d, customerId);
        }
        else {
            cout << "Review not found for customer ID: " << customerId << endl;
        }

        return found;
    }

    bool viewOwnReviews(int customerId) {
        goodReviews.viewReviewsByCustId(customerId);
        badReviews.viewReviewsByCustId(customerId);
    }

    void deleteTopReview(bool good) {
        if (good) {
            goodReviews.removeTop();
        }
        else {
            badReviews.removeTop();
        }
    }

    bool deleteOwnReview(int customerId, int reviewId) {
        bool found = goodReviews.removeByCustomerId(customerId, reviewId);

        if (!found) {
            found = badReviews.removeByCustomerId(customerId, reviewId);
        }

        if (!found) {
            cout << "Review not found for customer ID: " << customerId << endl;
        }
        return found;
    }

};

EmployeeHashMap EmployeeManagement;
 OrderQueue orderQueue;

void displayMainMenu(CustomerManagement& customerManagement, RestaurantClass& restaurantManager, Reviews& reviewSystem, promotionsStack& promoManager) {
    int n = 0;
    int choice;
    static Dishes* root = nullptr;
    do {
        cout << "\n========== RESTAURANT MANAGEMENT SYSTEM ==========\n";
        cout << "=================== MAIN MENU ====================\n\n";

        // Customer Section
        cout << "CUSTOMER MANAGEMENT:\n";
        cout << "1.  Customer Signup\n";
        cout << "2.  Customer Login\n";
        cout << "3.  Reset Customer Password\n";
        cout << "4.  View All Customers\n\n";

        // Employee Section
        cout << "EMPLOYEE MANAGEMENT:\n";
        cout << "5.  Manager Signup\n";
        cout << "6.  Manager Login\n";
        cout << "7.  Reset Manager Password\n\n";

        // Restaurant Management
        cout << "RESTAURANT OPERATIONS:\n";
        cout << "8.  Add New Restaurant\n";
        cout << "9.  Edit Restaurant\n";
        cout << "10. Delete Restaurant\n";
        cout << "11. Display Restaurants\n\n";

        // Menu Management
        cout << "MENU OPERATIONS:\n";
        cout << "12. Add Dish to Menu\n";
        cout << "13. Edit Dish\n";
        cout << "14. Delete Dish\n";
        cout << "15. Display Menu\n\n";

        // Order Management
        cout << "ORDER MANAGEMENT:\n";
        cout << "16. Create New Order\n";
        cout << "17. Cancel Order\n";
        cout << "18. Process Order\n";
        cout << "19. View All Orders\n\n";

        // Promotions
        cout << "PROMOTIONS:\n";
        cout << "20. Add Promotion\n";
        cout << "21. View Current Promotion\n";

        // Reviews
        cout << "REVIEW SYSTEM:\n";
        cout << "23. Add Review\n";
        cout << "24. View Good Reviews\n";
        cout << "25. View Bad Reviews\n";
        cout << "26. Edit Own Review\n";
        cout << "27. Delete Own Review\n\n";

        // System Utilities
        cout << "SYSTEM UTILITIES:\n";
        cout << "0.  Exit System\n\n";

        if (n == 0) {
            choice = 1;
            n++;
        }

        else if (n == 1) {
            choice = 5;
            n++;
        }

        else if (n == 2) {
            choice = 8;
            n++;
        }

        else if (n == 3) {
            choice = 4;
            n++;
        }

        else if (n == 4) {
            EmployeeManagement.display();
            n++;
        }

        else if (n == 5) {
            choice = 11;
            n++;
        }

        else {
            cout << "Enter your choice: ";
            cin >> choice;
        }

        // Switch case for different functionalities
        switch (choice) {
        case 1: { // Customer Signup
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choice: " << choice << endl;
            string name = "azfaar", email = "azfaar@gmail.com";
            string password = "Police@21";
            string confirmPassword = "Police@21";
            //cout << "Customer Signup\n";
            //cout << "Enter Name: ";
            //cin.ignore();
            //getline(cin, name);
            //cout << "Enter Email: ";
            //getline(cin, email);
            //do {
            //    if (!(password == confirmPassword)){
            //        cout << "\nError! Passwords do not match. Please try again.";
            //    }
            //    do {
            //        password = getPasswordInput();
            //    } while (!isValidPassword(password));
            //    confirmPassword = getPasswordInput(true);
            //}while(!(password == confirmPassword));

            customerManagement.signup(name, email, password);
            break;
        }

        case 2: { // Customer Login
            int id;
            string email, password;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choice: " << choice << endl;
            cout << "Customer Login\n";
            cout << "Enter Customer ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Email: ";
            getline(cin, email);
            password = getPasswordInput();

            customerManagement.login(id, email, password);
            break;
        }

        case 3: { // Reset Customer Password
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choice: " << choice << endl;
            customerManagement.resetPassword();
            break;
        }

        case 4: { // View All Customers
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            customerManagement.displayAllCustomers();

            break;
        }

        case 5: { // Manager Signup
            string name = "ammar", email = "ammar@gmail.com", password = "Ammar.3";
            //cout << "Manager Signup\n";
            //cout << "Enter Name: ";
            //getline(cin, name);
            //cout << "Enter Email: ";
            //getline(cin, email);
            //do {
            //  password = getPasswordInput();
            //} while (!isValidPassword(password));
            Employee* e1;
            EmployeeManagement.signup(name, email, password);
            break;
        }
        case 6: { // Manager Login
            int id;
            string email, password;
            cout << "Manager Login\n";
            cout << "Enter Manager ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter Email: ";
            getline(cin, email);
            password = getPasswordInput();
            EmployeeManagement.login(id, email, password);
            break;
        }
        case 7: { // Reset Manager Password
            EmployeeManagement.resetPassword();
            break;
        }
        case 8: { // Add New Restaurant
            string name = "howdy", cuisine = "FastFood";
            int capacity = 30;
            //cout << "Add New Restaurant\n";
//
            //// Restaurant Basic Details
            //cout << "Enter Restaurant Name: ";
            //cin.ignore();
            //getline(cin, name);
//
            //cout << "Enter Cuisine Type: ";
            //getline(cin, cuisine);
//
            //cout << "Enter Restaurant Capacity: ";
            //cin >> capacity;
            //cin.ignore();

            // Create a new menu for the restaurant
            Menu* newMenu = new Menu(name);

            // Populate the menu with dishes
            int dishCount = 1;
            //cout << "How many dishes would you like to add to the menu? ";
            //cin >> dishCount;
            //cin.ignore();

            for (int i = 0; i < dishCount; i++) {
                string dishName = "n", dishType = "t";
                double dishPrice = 2;

                //cout << "\nEnter details for Dish #" << (i + 1) << ":\n";
//
                //cout << "Dish Name: ";
                //getline(cin, dishName);
//
                //cout << "Dish Type (Appetizer/Main Course/Dessert/Beverage): ";
                //getline(cin, dishType);
//
                //cout << "Dish Price: ";
                //cin >> dishPrice;
                //cin.ignore();

                // Add dish to the menu
                newMenu->root = newMenu->addDishToMenu(newMenu->root, dishName, dishType, dishPrice);
            }

            // Optional: Display the newly created menu
            //cout << "\nMenu for " << name << ":\n";
            //newMenu->displayMenu(newMenu->root);
            // Add the restaurant with its new menu
            restaurantManager.addAtEnd(name, cuisine, newMenu, nullptr);

            cout << "Restaurant added successfully!\n";
            break;
        }
        case 9: { // Edit Restaurant
            string restaurant;
            cout << "Edit Restaurant\n";
            restaurantManager.editRestaurant();
            break;
        }
        case 10: { // Delete Restaurant
            string restaurant;
            cout << "Delete Restaurant\n";
            cout << "Enter Restaurant Name to Delete: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, restaurant);
            restaurantManager.deleteRestaurant(restaurant);
            break;
        }
        case 11: { // Display Restaurants
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            restaurantManager.display();
            break;
        }
        case 12: { // Add Dish to Menu
            string dishName, description;
            string rName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            double price;
            cout << "Add Dish to Menu\n";
            cout << "Enter Dish Name: ";
            getline(cin, dishName);
            cout << "Enter Dish Type: ";
            getline(cin, description);
            cout << "Enter Dish Price: ";
            cin >> price;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter restaurant name: " << endl;
            restaurantManager.display();
            getline(cin, rName);
            Restaurants* r1 = restaurantManager.findName(rName);
            r1->menu->addDishToMenu(r1->menu->getRoot(), dishName, description, price);
            break;
        }
        case 13: { // Edit Dish
            string dishName, description;
            string restaurant;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            double p;
            cout << "Enter Restaurant name: ";
            restaurantManager.display();
            getline(cin, restaurant);
            Restaurants* r = restaurantManager.searchRestaurantByName(restaurant);
            cout << "Edit Dish\n";
            cout << "Enter Dish Name: ";
            getline(cin, dishName);
            cout << "Enter Dish Type: ";
            getline(cin, description);
            cout << "Enter price: ";
            cin >> p;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            r->menu->edit(r->menu->getRoot(), dishName, description);
            break;
        }
        case 14: { // Delete Dish
            string dishName, description;
            string restaurant;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Delete Dish\n";
            cout << "Enter Restaurant name: ";
            restaurantManager.display();
            getline(cin, restaurant);
            Restaurants* r = restaurantManager.searchRestaurantByName(restaurant);
            cout << "Enter Dish Name: ";
            getline(cin, dishName);
            cout << "Enter Dish Type: ";
            getline(cin, description);
            r->menu->deleteDish(r->menu->getRoot(), dishName, description);
            break;
        }
        case 15: { // Display Menu
            string restaurantName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Display Menu\n";
            cout << "Enter Restaurant name: ";
            getline(cin, restaurantName);
            Restaurants* r1 = restaurantManager.findName(restaurantName);
            r1->menu->displayMenu(r1->menu->getRoot());
            break;
        }
        case 16: { // Create New Order
            //int customerId = 10000; // Later set to currently logged in customer
            //
            //if (!customerManagement.getCustomer(customerId)) {
            //    
            //    break;
            //}
            //Customer* c1 = customerManagement.getCustomer(customerId);
           
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           string restaurant;
             cout << "Enter Restaurant name: ";
            getline(cin, restaurant);
            Restaurants* r = restaurantManager.searchRestaurantByName(restaurant);
            //int employeeId = 10000;// Later set to currently logged in employee
            //if (!EmployeeManagement.getEmployee(employeeId)) {
            //    break;
            //}
            //Employee* e1 = EmployeeManagement.getEmployee(employeeId);
          //
            //cout << "Enter type of order (Premium,Express or Normal): ";
            //string type;
            //getline(cin, type);
            //Order* order1 = new Order(nullptr, 0, type, c1, e1);
            //cout << "Display order: " << endl;
            //cout << "Create New Order\n";

            Customer* customer = nullptr;
            Employee* employee = nullptr;
            Order* order1 = new Order(nullptr, 0, "Premium", customer, employee);
            // Collect dishes for the order
            while (true) {
                string dishName, dishType;
                double dishPrice;
                cout << "Add Dish to Order\n";
                cout << "Enter Dish Name: ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, dishName);
                cout << "Enter Dish Type: ";
                getline(cin, dishType);
                cout << "Enter Dish Price: ";
                cin >> dishPrice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                order1->addDish(new Dishes(dishName, dishType, dishPrice));
               // order1->displayOrder();
                cout << "continue? (1=yes,0=no)";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    continue;
                }
                else {
                    break;
                }
            }

            Dishes* dishes = nullptr;

            r->orders->addOrder(order1);
            r->orders->displayAllOrders();
            
            
          //  orderQueue.addOrder(order1);
           // orderQueue.displayAllOrders();

            break;
        }
        case 17: { // Cancel Order
           
            /*cin.ignore();
            string restaurantName = "";
            cout << "Enter restaurant name to cancel order from : ";
            cin >> restaurantName;
            */
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
           string restaurant;
             cout << "Enter Restaurant name: ";
            getline(cin, restaurant);
            Restaurants* r = restaurantManager.searchRestaurantByName(restaurant);
             int orderId;
            cout << "Cancel Order\n";
            
            cout << "Enter Order ID to Cancel: ";
            cin >> orderId;
            Restaurants* r1 = restaurantManager.findName(restaurant);
            r1->orders->cancelOrder(orderId);
            break;
        }
        case 18: { // Process Order
            int orderId;
            cout << "Process Order\n";
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string restaurantName = "";
            cout << "Enter restaurant name: ";
            cin >> restaurantName;
            Restaurants* r1 = restaurantManager.findName(restaurantName);
            cout << "Enter Order ID to Process: ";
            cin >> orderId;
            cin.ignore();
            Order currOrder = r1->orders->processOrder();
            //promoManager.applyDiscount(currOrder);
            cout << "The total payable amount is " << currOrder.totalCost;
          //  cout << "Thank you for buying from " << r1->name;
            break;
        }
        case 19:
        {

            string restaurantName;
             cout << "Enter restaurant name: ";
            cin >> restaurantName;
            Restaurants* r1 = restaurantManager.findName(restaurantName);
            r1->orders->displayAllOrders();
            break;
        }
        case 20: { // Add Promotion
            string promoName;
            int discount;
            int limit;
            cout << "Add Promotion\n";
            cout << "Enter Promo Name: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, promoName);
            cout << "Enter Discount Percentage: ";
            cin >> discount;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Enter Promo Limit: ";
            cin >> limit;
            promotions p1(promoName, discount, limit);
            promoManager.addPromotion(p1);
            break;
        }
        case 21: { // View Current Promotion
            promoManager.displayTopPromotion();
            break;
        }
               //Discount should be applied in case 18 i.e when processing order
               // case 22: { // Apply Promotion to Order
               // 	int orderId;
               // 	string promoCode;
               // 	cout << "Apply Promotion to Order\n";
               // 	cout << "Enter Order ID: ";
               // 	cin >> orderId;
               // 	cin.ignore();
               // 	cout << "Enter Promo Code: ";
               // 	getline(cin, promoCode);
               // 	promoManager.applyPromotion(orderId, promoCode);
               // 	break;
               // }
        case 23: { // Add Review
            int custId = 10000;
            int rating;
            string comment, restaurantName;
            cout << "Add Review\n";
            cout << "Enter Restaurant Name: ";
            cin >> restaurantName;
            if (!restaurantManager.findName(restaurantName)) {
                cout << "Error, No such restaurant exists.";
                break;
            }
            cin.ignore();
            cout << "Enter Rating (1-5): ";
            cin >> rating;
            cin.ignore();
            cout << "Enter Review Comment: ";
            getline(cin, comment);

            Restaurants* r1 = restaurantManager.findName(restaurantName);
            reviewSystem.addReview(comment, rating, "restaurant", r1, nullptr, custId);
            break;
        }
        case 24: { // View Good Reviews
            reviewSystem.viewReviews(true, 5);
            break;
        }
        case 25: { // View Bad Reviews
            reviewSystem.viewReviews(false, 5);
            break;
        }
        case 26: { // Edit Own Review
            int custId = 10000; //later add customer id which is of current customer
            int reviewId = 10000;
            int newRating;
            string type;
            string newComment;
            string restaurantName;
            cout << "Edit Own Review\n";
            cout << "Enter Review ID to Edit: ";
            cin >> reviewId;
            cin.ignore();
            cout << "Enter New Comment: ";
            getline(cin, newComment);
            cout << "Enter New Rating: ";
            cin >> newRating;
            cout << "Enter Restaurant Name: ";
            cin >> restaurantName;
            Restaurants* r1 = restaurantManager.findName(restaurantName);
            cout << "Enter review type (restaurant or dish) : ";
            cin >> type;
            reviewSystem.editReview(custId, reviewId, newComment, newRating, type, r1);
            break;
        }
        case 27: { // Delete Own Review
            int custId = 10000;
            int reviewId;
            cout << "Delete Own Review\n";
            cout << "Enter Review ID to Delete: ";
            cin >> reviewId;
            cin.ignore();
            reviewSystem.deleteOwnReview(custId, reviewId);
            break;
        }
        case 0: {
            cout << "Exiting Restaurant Management System. Goodbye!\n";
            return;
        }

        default: {
            cout << "Invalid choice. Please try again.\n";
        }
        }
        // Pause after each operation
        //cout << "\nPress Enter to continue...";
        //cin.ignore();
        //cin.get();
    } while (true);
}

int main() {
    // Initialize necessary managers
    CustomerManagement customerManagement;
    RestaurantClass restaurantManager;
    Reviews reviewSystem;
    promotionsStack promoManager;

    // Display main menu and pass necessary managers
    displayMainMenu(customerManagement, restaurantManager, reviewSystem, promoManager);

    return 0;
}