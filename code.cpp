#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std; // Add the using namespace directive
class Date {
public:
Date(int day, int month, int year) : day(day), month(month), year(year) {}
private:
int day;
int month;
int year;
};
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
class Customer {
public:
Customer(string name, Date dob, Address address)
: name(name), dob(dob), address(address) {}
private:
string name;
Date dob;
Address address;
};
class Transaction {
public:
Transaction(double amount, Date date, string description)
: amount(amount), date(date), description(description) {}
private:

double amount;
Date date;
string description;
};
class Account {
public:
double balance;
Account(int accountNumber, Customer customer)
: accountNumber(accountNumber), customer(customer) {
balance = 0.0;
}
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
class SavingsAccount : public Account {
public:
SavingsAccount(int accountNumber, Customer customer, double interestRate)
: Account(accountNumber, customer), interestRate(interestRate) {}
void addInterest() {
double interest = getBalance() * interestRate;
deposit(interest);
}

private:
double interestRate;
};
class CheckingAccount : public Account{
public:
CheckingAccount(int accountNumber, Customer customer, double
overdraftLimit)
: Account(accountNumber, customer), overdraftLimit(overdraftLimit) {}
void withdraw(double amount) override {
if (getBalance() + overdraftLimit >= amount)
balance -= amount;
else
cout << "Exceeded overdraft limit." << endl;
}
private:
double overdraftLimit;
};
class Bank {
public:
Bank(string name) : name(name) {}
void addAccount(Account* account) {
accounts.push_back(account);
}
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
Bank bank("MyBank");
Customer customer1("John Doe", Date(15, 3, 1985), Address("123 Main St",
"Anytown", "CA", "12345"));
Customer customer2("Jane Smith", Date(21, 7, 1990), Address("456 Elm St",
"Othercity", "NY", "67890"));

SavingsAccount savings1(101, customer1, 0.05);
CheckingAccount checking1(102, customer2, 1000);
bank.addAccount(&savings1);
bank.addAccount(&checking1);
savings1.deposit(5000);
checking1.deposit(3000);
savings1.addInterest();
cout << "Account Balances:" << endl;
bank.listAccounts();
savings1.withdraw(2000);
checking1.withdraw(5000);
cout << "Account Balances after withdrawals:" << endl;
bank.listAccounts();
return 0;
}
