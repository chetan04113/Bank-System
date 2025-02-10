#include<iostream>
#include<vector>
using namespace std;

class InsufficientBalanceException : public exception {
public:
    const char* what() const throw() {
        return "Insufficient balance!";
    }
};

class Bank {
private:
    string id;
    int password;
    int balance;
    vector<int> transactions;

public:
    Bank() : balance(0) {} 

    void createAccount() {
        string confirmPassword;
        cout << "Enter your user ID: ";
        cin >> id;
        cout << "Enter your password: ";
        cin >> password;
        cout << "Confirm your password: ";
        cin >> confirmPassword;

        if (to_string(password) != confirmPassword) {
            cout << "Passwords do not match. Try again!\n";
        } else {
            cout << "Account created successfully!\n";
        }
    }

    bool login() {
        string userId;
        int pass;
        cout << "Enter your user ID: ";
        cin >> userId;
        cout << "Enter your password: ";
        cin >> pass;

        if (userId == id && pass == password) {
            cout << "Login successful!\n";
            return true;
        } else {
            cout << "Invalid credentials.\n";
            return false;
        }
    }

    void deposit() {
        int amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        balance += amount;
        transactions.push_back(amount);
        cout << "Amount deposited successfully!\n";
    }

    void checkBalance() {
        cout << "Available Balance: " << balance << "\n";
    }

    void withdraw() {
        int amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        try {
            if (amount > balance) {
                throw InsufficientBalanceException();
            }
            balance -= amount;
            transactions.push_back(-amount);
            cout << "Withdrawal successful!\n";
        } catch (InsufficientBalanceException &e) {
            cout << e.what() << "\n";
        }
    }
};

int main() {
    Bank user;
    int choice;
    while (true) {
        cout << "\n1. Create Account\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                user.createAccount();
                break;
            case 2:
                if (user.login()) {
                    int option;
                    do {
                        cout << "\n1. Deposit\n2. Check Balance\n3. Withdraw\n4. Logout\nEnter your choice: ";
                        cin >> option;
                        switch (option) {
                            case 1:
                                user.deposit();
                                break;
                            case 2:
                                user.checkBalance();
                                break;
                            case 3:
                                user.withdraw();
                                break;
                            case 4:
                                cout << "Logging out...\n";
                                break;
                            default:
                                cout << "Invalid choice!\n";
                        }
                    } while (option != 4);
                }
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
                break;
        }
    }
    return 0;
}
