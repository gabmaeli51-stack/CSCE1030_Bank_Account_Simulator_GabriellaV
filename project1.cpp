#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

// Constants and Global Arrays
const int MAX_TXN = 100;
enum AccountType { CHECKING, SAVINGS, STUDENT };

char gTxnType[MAX_TXN];
double gTxnAmount[MAX_TXN];
string gTxnMemo[MAX_TXN];
int gTxnCount = 0;

// --- 1. PROTOTYPES ---
void printHeader();
bool isValidName(const string& name);
string readValidName();
AccountType chooseAccountType();
string accountTypeToString(AccountType t);
bool isValidPin(const string& p);
bool setOrChangePin(string& pin, bool& pinSet);
bool requirePinForAction(string& pin, bool& pinSet);
void recordTransaction(char type, double amount, const string& memo);
void deposit(double& balance, string& pin, bool& pinSet);
void withdraw(double& balance, AccountType type, string& pin, bool& pinSet);
void printRecentTransactions(int maxToShow);
void showDetails(const string& holder, AccountType type, double balance, bool pinSet);
void viewTransactionsByType();

// --- 2. MAIN ENGINE ---
int main() {
    printHeader(); 

    string name = readValidName(); 

    double balance;
    cout << "Enter initial balance: $";
    cin >> balance;

    cin.ignore(100, '\n'); 

    AccountType type = chooseAccountType(); 

    int choice;
    string pin = "";
    bool pinSet = false;

    do {
        cout << "\n------------------------------------------------------------" << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Account Type:   " << accountTypeToString(type) << endl;
        cout << "Balance:        $" << fixed << setprecision(2) << balance << endl;
        cout << "------------------------------------------------------------" << endl;
        
        cout << endl;
        cout << "1) Deposit (PIN required)\n2) Withdraw (PIN required)\n3) Show Account Details\n";
        cout << "4) Set/Change PIN (4-6 digits)\n5) Exit\n6) View Transactions by Type\n";
        cout << "Select an option (1-6): ";
        
        //This prevents infinite loops if user enters non-integer input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            choice = 0; // Triggers the 'Invalid selection' else block
        }

        if (choice == 1) {
            deposit(balance, pin, pinSet);
        } else if (choice == 2) {
            withdraw(balance, type, pin, pinSet);
        } else if (choice == 3) {
            showDetails(name, type, balance, pinSet);
        } else if (choice == 4) {
            cout << endl;
            setOrChangePin(pin, pinSet);
        } else if (choice == 6) {
            viewTransactionsByType();
        } else if (choice == 5) {
            char confirm;
            cout << "Are you sure you want to exit? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                cout << "Thank you for using the Bank Account Simulator. Goodbye!" << endl;
                break; 
            } else {
                choice = 0; 
            }
        } else {
            // 
            cout << "Invalid selection. Please enter 1-6." << endl;
        }

    } while (choice != 5);

    return 0;
}

// --- 3. FUNCTION IMPLEMENTATIONS ---

void printHeader() {
    cout << "+-------------------------------------------------+" << endl;
    cout << "|        Computer Science and Engineering         |" << endl;
    cout << "|         CSCE 1030 - Computer Science I          |" << endl;
    cout << "| Gabriella Vazquez  gv0244  gvazquez@my.unt.edu  |" << endl;
    cout << "+-------------------------------------------------+" << endl;
    cout << "\n============================================================" << endl;
    cout << "             Bank Account Simulator (Console)                 " << endl;
    cout << "============================================================" << endl;
}

bool isValidName(const string& name) {
    if (name.length() == 0) return false;
    for (int i = 0; i < (int)name.length(); i++) {
        if (!isalpha(name[i]) && !isdigit(name[i]) && !isspace(name[i])) return false;
    }
    return true;
}

string readValidName() {
    string n;
    cout << "Enter account holder name: ";
    getline(cin, n);
    while (!isValidName(n)) {
        cout << "Name can only contain letters, digits, and spaces. Try again: ";
        getline(cin, n);
    }
    return n;
}

AccountType chooseAccountType() {
    int choice;
    do {
        cout << "\nChoose account type:" << endl;
        cout << "1) Checking" << endl;
        cout << "2) Savings" << endl;
        cout << "3) Student" << endl;
        cout << "Enter (1-3): ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            choice = 0; 
        }
        if (choice == 1) return CHECKING;
        if (choice == 2) return SAVINGS;
        if (choice == 3) return STUDENT;
        cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
    } while (true);
}

string accountTypeToString(AccountType t) {
    if (t == CHECKING) return "Checking";
    if (t == SAVINGS) return "Savings";
    return "Student";
}

bool isValidPin(const string& p) {
    if (p.length() < 4 || p.length() > 6) return false;
    for (int i = 0; i < (int)p.length(); i++) {
        if (!isdigit(p[i])) return false;
    }
    return true;
}

bool setOrChangePin(string& pin, bool& pinSet) {
    string p1, p2;
    bool match = false;
    do {
        cout << "Set PIN (4-6 digits): ";
        cin >> p1;
        while (!isValidPin(p1)) {
            cout << "Invalid PIN. Enter 4-6 digits: ";
            cin >> p1;
        }
        cout << "Confirm PIN: ";
        cin >> p2;
        if (p1 == p2) {
            pin = p1;
            pinSet = true;
            match = true;
            cout << "PIN set." << endl << endl;
        } else {
            cout << "PIN mismatch." << endl << endl; 
        }
    } while (!match);
    return true; 
}

bool requirePinForAction(string& pin, bool& pinSet) {
    cout << endl; 
    if (!pinSet) {
        cout << "No PIN set. Create one to continue." << endl;
        setOrChangePin(pin, pinSet);
        return true; 
    } else {
        string attempt;
        cout << "Enter PIN: ";
        cin >> attempt;
        if (attempt != pin) {
            cout << "Incorrect PIN." << endl;
            return false;
        }
        return true;
    }
}

void recordTransaction(char type, double amount, const string& memo) {
    if (gTxnCount < MAX_TXN) {
        gTxnType[gTxnCount] = type;
        gTxnAmount[gTxnCount] = amount;
        gTxnMemo[gTxnCount] = memo;
        gTxnCount++;
    } else {
        for (int i = 1; i < MAX_TXN; i++) {
            gTxnType[i-1] = gTxnType[i];
            gTxnAmount[i-1] = gTxnAmount[i];
            gTxnMemo[i-1] = gTxnMemo[i];
        }
        gTxnType[MAX_TXN-1] = type;
        gTxnAmount[MAX_TXN-1] = amount;
        gTxnMemo[MAX_TXN-1] = memo;
    }
}

void deposit(double& balance, string& pin, bool& pinSet) {
    if (!requirePinForAction(pin, pinSet)) {
        cout << "Deposit canceled." << endl; 
        return;
    }
    double amt; 
    string m;
    cout << "Enter deposit amount: $"; 
    cin >> amt;
    cin.ignore(100, '\n'); 
    cout << "Enter memo: "; 
    getline(cin, m);
    balance += amt;
    recordTransaction('D', amt, m);
    cout << "Deposited $" << fixed << setprecision(2) << amt 
         << ". New balance: $" << balance << endl; 
}

void withdraw(double& balance, AccountType type, string& pin, bool& pinSet) {
    if (!requirePinForAction(pin, pinSet)) {
        cout << "Withdrawal canceled." << endl;
        return;
    }
    double amt; 
    string m;
    cout << "Enter withdrawal amount: $"; 
    cin >> amt;
    cin.ignore(100, '\n'); 
    cout << "Enter memo: "; 
    getline(cin, m);
    if (balance - amt >= 0) {
        balance -= amt;
        recordTransaction('W', amt, m);
        cout << "Withdrew $" << fixed << setprecision(2) << amt 
             << ". New balance: $" << balance << endl; 
    } else if (type == CHECKING) {
        balance = (balance - amt) - 35.0;
        recordTransaction('W', amt, m);
        recordTransaction('F', 35.0, "Overdraft Fee");
        cout << "Overdraft! Fee $35.00 applied." << endl;
        cout << "New balance: $" << fixed << setprecision(2) << balance << endl;
    } else {
        cout << "Withdrawal denied. Insufficient funds." << endl;
    }
}

void printRecentTransactions(int maxToShow) {
    int count = 0;
    for (int i = gTxnCount - 1; i >= 0 && count < maxToShow; i--) {
        string lbl = (gTxnType[i] == 'D') ? "Deposit " : (gTxnType[i] == 'W') ? "Withdraw" : "Fee     ";
        cout << " [" << lbl << "] $" << fixed << setprecision(2) << gTxnAmount[i] << " | " << gTxnMemo[i] << endl;
        count++;
    }
}

void showDetails(const string& holder, AccountType type, double balance, bool pinSet) {
    cout << "================ Account Details ================" << endl;
    cout << "Holder: " << holder << endl;
    cout << "Type:   " << accountTypeToString(type) << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    cout << "PIN:    " << (pinSet ? "(set)" : "(not set)") << endl;
    cout << "---------------- Recent Transactions (" << gTxnCount << ") ---------------" << endl;
    printRecentTransactions(10); 
    cout << "------------------------------------------------------------------" << endl;
    cout << "================================================" << endl;
}

void viewTransactionsByType() {
    char s;
    cout << "Show which transactions? (D=Deposit, W=Withdraw, F=Fee): ";
    cin >> s;
    s = toupper(s);
    string typeName = (s == 'D') ? "Deposit" : (s == 'W') ? "Withdraw" : "Fee";

    cout << "---------------- Transactions of type " << typeName << " ----------------" << endl;
    bool f = false;
    for (int i = gTxnCount - 1; i >= 0; i--) {
        if (gTxnType[i] == s) {
            string lbl = (gTxnType[i] == 'D') ? "Deposit " : (gTxnType[i] == 'W') ? "Withdraw" : "Fee     ";
            cout << " [" << lbl << "] $" << fixed << setprecision(2) << gTxnAmount[i] << " | " << gTxnMemo[i] << endl;
            f = true;
        }
    }
    if (!f) cout << "(No transactions found)" << endl;
    cout << "------------------------------------------------------------------" << endl;
}