#include "customer.hpp"
#include "Employee.hpp"
#include "transaction.hpp"
#include<iostream>
#include "bank.hpp"

using namespace std;

int Bank::number_of_customers;
int Bank::number_of_employees;
int Employee::n_employees = 0;
int Transaction::n_transactions = 0;
int main()
{
  Bank bank;
  bank.loadCustomerAccounts();
  bank.setNumberOfCustomer(bank.getNumberOfCustomer());
  bank.loadEmployeeAccounts();
  bank.menu();
  bank.processTransfers(); // make all pending transfers
  bank.saveAllCustomers(); // save all customers information
}