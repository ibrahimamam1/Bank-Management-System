#include "bank.hpp"
#include "customer.hpp"
#include "functions.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

Bank::Bank(){}

int Bank::getNumberOfCustomer()
{
  return customer_list.size();
}
int Bank::getNumberOfEmployees()
{
  return number_of_employees;
}
void Bank::setNumberOfCustomer(int n)
{
  number_of_customers = n;
}
void Bank::setNumberOfEmployee(int n)
{
  number_of_employees = n;
}

void Bank::menu()
{
  std::cout << "\t\tWelcome to Bank Management System\n";
  std::cout << "1) Login\n";
  std::cout << "2) Create Account\n";

  int choice;
  std::cin >> choice;

  switch(choice)
  {
    case 1:
      login();
      break;
    case 2:
      createAccount();
      break;  
  }
}

void Bank::createAccount()
{
  clear_screen();
  std::string name;
  std::string dob;
  long phone;
  std::string pass;

  std::cin.ignore();
  std::cout << "Enter Your name : ";
  getline(std::cin , name);
  std::cout << "Enter Your date of Birth : ";
  std::getline(std::cin , dob);
  std::cout << "Enter Your phone Number : ";
  std::cin >> phone;
  std::cout << "Choose a password : ";
  std::cin >> pass;

  std::cout << "\t\tChoose account type\n";
  std::cout << "\t\t1) Saving\n";
  std::cout << "\t\t2) Current\n";

  int acc = getNumberOfCustomer()+1;
  Customer* c;
  int choice;
  std::cin >> choice;
  if(choice == 1)
  {
    c = new Saving(1 ,name , acc , dob , phone , pass);
    customer_list.push_back(c);
  }
  else 
  {
    c = new Current(2 , name ,acc, dob , phone , pass);
    customer_list.push_back(c);
  }  
  c->customerMenu();   
}
  

void Bank::login()
{
  clear_screen();
  std::cout << "1)Customer\n";
  std::cout << "2)Employee\n";

  int choice;
  std::cin >> choice;

  std::string name;
  std::string pass;
  bool matchFound = false;

  while (1)
  {
    std::cout << "Enter name : ";
    std::cin >> name;
    std::cout << "Enter pass : ";
    std::cin >> pass;

    size_t i=0;
    switch (choice) 
    {
      case 1:
      {
        for(i=0; i<customer_list.size() && !matchFound; i++)
        {
          if(customer_list[i]->getName() == name && customer_list[i]->getPass() == pass)
            matchFound = true;
        }
        if(matchFound) customer_list[i-1]->customerMenu();
        break;
      }
      case 2:
      {
        for(i=0; i<employee_list.size() && !matchFound; i++)
        {
          if(employee_list[i]->getName() == name && employee_list[i]->getPass() == pass)
            matchFound = true;
        }
        if(matchFound) employee_list[i-1]->employeeMenu();
        break;
      }
    }
    if(matchFound) break;
    else std::cout << "Incorrect user name or password\n";
  }
}
void Bank::loadCustomerAccounts()
{
  std::string filename = "db/bank/customer_accounts.txt";
  std::ifstream infile(filename);
  while (infile.good())
  {
    int type;
    std::string name;
    long account_number;
    std::string day;
    std::string month;
    std::string year;
    long phone;
    long balance;
    bool isFreezed;
    int n_report;
    std::string pass;

    infile >> type >> name >> account_number >> day >> month >> year >> phone >> balance >> isFreezed >> n_report >> pass;
    std::string dob = day + " " + month + " " + " " + year;
      if(type == 1)
      customer_list.push_back(new Saving(type , name , account_number , dob , phone , pass , balance , isFreezed , n_report));
      else 
      customer_list.push_back(new Current(type , name , account_number , dob , phone , pass , balance , isFreezed , n_report)); 
  }
  infile.close(); 
}
void Bank::loadEmployeeAccounts()
{
  std::string filename = "db/bank/employee_accounts.txt";
  std::ifstream infile(filename);
  while (infile.good())
  {
    int type;
    std::string name;
    std::string day;
    std::string month;
    std::string year;
    long phone;
    long salary;
    std::string pass;

    infile >> type >> name  >> day >> month >> year;
    std::string dob = day + " " + month + " " + " " + year;
    infile >> day >> month >> year >> salary >> phone >> pass;
    std::string doj = day + " " + month + " " + " " + year;

    if(type == 1)
      employee_list.push_back(new Worker(type , name , dob , doj, salary , phone , pass));
    else 
      employee_list.push_back(new Manager(type , name , dob , doj, salary , phone , pass));
  } 
  infile.close();
}

void Bank::processTransfers()
{
  std::string filename = "db/customer/transfers.txt";
  std::ifstream infile(filename);
  while(infile.good())
  {
    long account_number , amount;
    infile >> account_number >> amount;
    for(size_t i=0; i<customer_list.size(); i++)
    {
      if(customer_list[i]->getAccountNumber() == account_number)
      {
        customer_list[i]->deposit(amount);
      }
    }
  }
  infile.close();
  
  // Open the file in output mode with truncation to clear its content
  std::ofstream outfile(filename, std::ios::trunc);
  outfile.close();
}

void Bank::freezeAccount()
{
  std::string filename = "db/customer/reportedTransaction.txt";
  std::ifstream infile(filename);
  while(infile.good())
  {
    long acc_num;
    infile >> acc_num;

    for(size_t i =0; i<customer_list.size(); i++)
    {
      if(customer_list[i]->getAccountNumber() == acc_num) 
      {
        customer_list[i]->incrementReport();
        if(customer_list[i]->getReportedTransactions() >= 5)
          customer_list[i]->setFreezeStatus(true);
        break;
      }
    }
  }
  infile.close();
}
void Bank::saveAllCustomers()
{
  std::string filename = "db/bank/customer_accounts.txt";
  std::ofstream outfile(filename);

  for(size_t i=0; i<customer_list.size(); i++)
  {
    if(customer_list[i]->getName().length() > 1)
      outfile << customer_list[i]->getAccountType() << " "<< customer_list[i]->getName() << " " << customer_list[i]->getAccountNumber() << " " <<customer_list[i]->getDateOfBirth() << " " << customer_list[i]->getPhoneNumber() << " " << customer_list[i]->getBalance() << " " << customer_list[i]->getFreezeStatus() << " " << customer_list[i]->getReportedTransactions() << " " << customer_list[i]->getPass() <<"\n";
  }
  
  outfile.close();
}
Bank::~Bank()
{
  
}