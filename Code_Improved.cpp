#include <iostream>
#include <vector>
using namespace std;
// Class to represent a Date with day, month, and year attributes.
class Date {
public:
Date(int day, int month, int year) : day(day), month(month), year(year) {}
private:
int day;
int month;
int year;
};
// Class to represent an Address with street, city, state, and zip code
attributes.
class Address {
public:
Address(string street, string city, string state, string zip)
: street(street), city(city), state(state), zip(zip) {}
private:
string street;
string city;
string state;
string zip;
};
// Class to represent a Customer with name, Date of Birth (DOB), and Address.
class Customer {
public:
Customer(string name, Date dob, Address address)
: name(name), dob(dob), address(address) {}
private:
string name;
Date dob;
Address address;
};
// Class to represent a financial Transaction with amount, date, and
description.
class Transaction {
public:
Transaction(double amount, Date date, string description)
: amount(amount), date(date), description(description) {}
private:
double amount;
Date date;
string description;
};
// Class to represent a generic Account with account number, customer
information, and balance.
class Account {
public:
double balance;
Account(int accountNumber, Customer customer)
: accountNumber(accountNumber), customer(customer), balance(0.0) {}
void deposit(double amount) {
balance += amount;
}
virtual void withdraw(double amount) {
if (balance >= amount)
balance -= amount;
else
cout << "Insufficient balance." << endl;
}
double getBalance() const {
return balance;
}
int getAccountNumber() const {
return accountNumber;
}
private:
int accountNumber;
Customer customer;
};
// Class to represent a Savings Account, inherits from Account.
class SavingsAccount : public Account {
public:
SavingsAccount(int accountNumber, Customer customer, double interestRate)
: Account(accountNumber, customer), interestRate(interestRate) {}
// Add interest to the account balance based on the interest rate.
void addInterest() {
double interest = getBalance() * interestRate;
deposit(interest);
}
private:
double interestRate;
};
// Class to represent a Checking Account, inherits from Account.
class CheckingAccount : public Account {
public:
CheckingAccount(int accountNumber, Customer customer, double
overdraftLimit)
: Account(accountNumber, customer), overdraftLimit(overdraftLimit) {}
// Override the withdraw method to handle overdraft.
void withdraw(double amount) override {
if (getBalance() + overdraftLimit >= amount)
balance -= amount;
else
cout << "Exceeded overdraft limit." << endl;
}
private:
double overdraftLimit;
};
// Class to represent a Bank with a name and a collection of accounts.
class Bank {
public:
Bank(string name) : name(name) {}
void addAccount(Account* account) {
accounts.push_back(account);
}
// List account numbers and balances.
void listAccounts() {
for (const auto& account : accounts) {
cout << "Account Number: " << account->getAccountNumber() << ",

Balance: " << account->getBalance() << endl;
}
}
private:
string name;
vector<Account*> accounts;
};
int main() {
// Create a Bank object with the name "MyBank".
Bank bank("MyBank");
// Create Customer and Account objects.
Customer customer1("John Doe", Date(15, 3, 1985), Address("123 Main St",
"Anytown", "CA", "12345"));
Customer customer2("Jane Smith", Date(21, 7, 1990), Address("456 Elm St",
"Othercity", "NY", "67890"));
// Create Savings and Checking Accounts.
SavingsAccount savings1(101, customer1, 0.05);
CheckingAccount checking1(102, customer2, 1000);
// Add accounts to the bank.
bank.addAccount(&savings1);
bank.addAccount(&checking1);
// Deposit initial amounts into the accounts.
savings1.deposit(5000);
checking1.deposit(3000);
// Add interest to the savings account.
savings1.addInterest();
cout << "Account Balances:" << endl;
bank.listAccounts();
// Withdraw money from accounts.
savings1.withdraw(2000);
checking1.withdraw(5000);
cout << "Account Balances after withdrawals:" << endl;
bank.listAccounts();
return 0;
}

