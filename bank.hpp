#ifndef BANK_HPP
#define BANK_HPP

#include "customer.hpp"
#include "Employee.hpp"
#include <vector>

class Bank
{
  std::vector<Customer*>customer_list;
  std::vector<Employee*>employee_list;
  static int number_of_customers;
  static int number_of_employees;

  public:
    Bank();
    ~Bank();

    int getNumberOfCustomer();
    int getNumberOfEmployees();
    void setNumberOfCustomer(int n);
    void setNumberOfEmployee(int n);


    void loadCustomerAccounts();
    void loadEmployeeAccounts();
    void processTransfers();
    void saveAllCustomers();
    void freezeAccount();
    void menu();
    void login();
    void createAccount();

};

#endif