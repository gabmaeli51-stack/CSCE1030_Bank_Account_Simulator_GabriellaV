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

// --- Function Prototypes ---
void printHeader();
bool isValidName(const string& name);
string readValidName();
AccountType chooseAccountType();
string accountTypeToString(AccountType t);

int main() {
    // 1. Show the Banner
    printHeader();

    // 2. Setup Variables
    string name;
    double balance;
    
    // 3. Get Initial Info
    name = readValidName(); 
    
    cout << "Enter initial balance: $";
    cin >> balance;

    AccountType type = chooseAccountType();

    // Just a placeholder to show it works
    cout << "\nAccount Setup Complete for " << name << "!" << endl;
    cout << "Account Type: " << accountTypeToString(type) << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;

    return 0;
}

// --- Function Implementations ---

void printHeader() {
    cout << "+--------------------------------------------------------+" << endl;
    cout << "|          Computer Science and Engineering              |" << endl;
    cout << "|           CSCE 1030 - Computer Science I               |" << endl;
    cout << "| Gabriella Vazquez  gv0244  gabriellavazquez@my.unt.edu |" << endl;
    cout << "+--------------------------------------------------------+" << endl;
    cout << "\n============================================================" << endl;
    cout << "Bank Account Simulator (Console)" << endl;
    cout << "============================================================" << endl;
}

bool isValidName(const string& name) {
    if (name.length() == 0) return false;
    for (int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && !isdigit(name[i]) && !isspace(name[i])) return false;
    }
    return true;
}

string readValidName() {
    string n;
    cout << "Enter account holder name: ";
    // Use cin.ignore() only if there was a cin >> before this
    // Since this is the first input, we might not need it, but let's be safe
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
        cout << "Choose account type:\n1) Checking\n2) Savings\n3) Student\nEnter (1-3): ";
        cin >> choice;
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