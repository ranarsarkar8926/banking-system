#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <cstdlib> 
#include <ctime> 
using namespace std;
class BankAccount
{
private:
    int accountNumber;
    string accountHolderName;
    float balance;
    string atmPin;
public:
    BankAccount(int accNum, string name, string pin, float bal = 0.0)
    {
        accountNumber = accNum;
        accountHolderName = name;
        balance = bal;
        atmPin = pin;
    }
    void displayDetails() const
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }
    void deposit(float amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited $" << amount << ". New Balance: $" << balance << endl;
        }
        else
        {
            cout << "Invalid deposit amount!" << endl;
        }
    }
    bool withdraw(float amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrew $" << amount << ". Remaining Balance: $" << balance << endl;
            return true;
        }
        else
        {
            cout << "Invalid withdrawal amount!" << endl;
            return false;
        }
    }
    void setAtmPin(string pin)
    {
        atmPin = pin;
        cout << "ATM PIN set successfully." << endl;
    }
    bool verifyAtmPin(string pin) const
    {
        return pin == atmPin;
    }

    float getBalance() const
    {
        return balance;
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }
};
class Bank
{
private:
    vector<BankAccount> accounts;
    unordered_set<int> usedAccountNumbers; 
    int generateUniqueAccountNumber()
    {
        int accNum;
        do
        {
            accNum = rand() % 900000 + 100000;
        } while (usedAccountNumbers.find(accNum) != usedAccountNumbers.end());
        usedAccountNumbers.insert(accNum);
        return accNum;
    }

public:
    Bank()
    {
        srand(time(0)); 
    }
    void createAccount(string name, string pin, float initialDeposit = 0.0)
    {
        int accNum = generateUniqueAccountNumber();
        BankAccount newAccount(accNum, name, pin, initialDeposit);
        accounts.push_back(newAccount);
        cout << "Account created successfully! Your Account Number is: " << accNum << endl;
    }
    void displayAccount(int accNum)
    {
        for (const auto &acc : accounts)
        {
            if (acc.getAccountNumber() == accNum)
            {
                acc.displayDetails();
                return;
            }
        }
        cout << "Account not found!" << endl;
    }
    void depositToAccount(int accNum, float amount)
    {
        for (auto &acc : accounts)
        {
            if (acc.getAccountNumber() == accNum)
            {
                acc.deposit(amount);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }
    void withdrawFromAccount(int accNum, float amount)
    {
        for (auto &acc : accounts)
        {
            if (acc.getAccountNumber() == accNum)
            {
                acc.withdraw(amount);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }
    void setAtmPinForAccount(int accNum, string pin)
    {
        for (auto &acc : accounts)
        {
            if (acc.getAccountNumber() == accNum)
            {
                acc.setAtmPin(pin);
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void atmLogin(int accNum, string pin)
    {
        for (auto &acc : accounts)
        {
            if (acc.getAccountNumber() == accNum)
            {
                if (acc.verifyAtmPin(pin))
                {
                    atmOperations(acc);
                }
                else
                {
                    cout << "Invalid ATM PIN!" << endl;
                }
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void atmOperations(BankAccount &account)
    {
        int choice;
        float amount;
        do
        {
            cout << "\n*** ATM Menu ***\n";
            cout << "1. Check Balance\n";
            cout << "2. Withdraw\n";
            cout << "3. Exit ATM\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Balance: $" << account.getBalance() << endl;
                break;

            case 2:
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                account.withdraw(amount);
                break;

            case 3:
                cout << "Exiting ATM...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
            }
        } while (choice != 3);
    }
};

bool validatePin(string pin)
{
    if (pin.length() != 4)
        return false;
    for (char ch : pin)
    {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

int main()
{
    Bank bank;
    int choice, accNum;
    string name, pin;
    float amount;

    do
    {
        cout << "\n*** Bank Management System ***\n";
        cout << "1. Bank Authority\n";
        cout << "2. User (ATM)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int subChoice;
            cout << "\n*** Bank Authority Menu ***\n";
            cout << "1. Create Account\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Display Account\n";
            cout << "5. Set ATM PIN\n";
            cout << "Enter your choice: ";
            cin >> subChoice;

            switch (subChoice)
            {
            case 1:
                cout << "Enter Account Holder Name: ";
                cin.ignore();
                getline(cin, name);

                do
                {
                    cout << "Set 4-digit ATM PIN: ";
                    cin >> pin;
                } while (!validatePin(pin));

                cout << "Enter Initial Deposit: ";
                cin >> amount;

                bank.createAccount(name, pin, amount);
                break;

            case 2:
                cout << "Enter 6-digit Account Number: ";
                cin >> accNum;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                bank.depositToAccount(accNum, amount);
                break;

            case 3:
                cout << "Enter 6-digit Account Number: ";
                cin >> accNum;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                bank.withdrawFromAccount(accNum, amount);
                break;

            case 4:
                cout << "Enter 6-digit Account Number: ";
                cin >> accNum;
                bank.displayAccount(accNum);
                break;

            case 5:
                cout << "Enter 6-digit Account Number: ";
                cin >> accNum;

                do
                {
                    cout << "Set 4-digit ATM PIN: ";
                    cin >> pin;
                } while (!validatePin(pin));

                bank.setAtmPinForAccount(accNum, pin);
                break;

            default:
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 2:
            cout << "Enter 6-digit Account Number: ";
            cin >> accNum;
            cout << "Enter 4-digit ATM PIN: ";
            cin >> pin;
            bank.atmLogin(accNum, pin);
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
