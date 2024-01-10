#include "Employee.hpp"
#include "loan.hpp"
#include "functions.hpp"
#include "message.hpp"
#include "transaction.hpp"
#include <cstddef>
#include <fstream>
#include<iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>

Employee:: Employee()
{

}
Employee::Employee(int type , std::string n , std::string dob , std::string doj , long salary , long phone_number , std::string pass) : type(type) , name(n) , id(++n_employees), date_of_birth(dob) , date_of_join(doj) , pass(pass), salary(salary) , phone_number(phone_number)
{

}

std::string Employee::getName() const
{
  return name;
}
int Employee::getId() const
{
  return id;
}
std::string Employee::getDob() const
{
  return date_of_birth;
}
std::string Employee::getDoj() const
{
  return date_of_join;
}
std::string Employee::getPass() const
{
  return pass;
}
long Employee::getSalary() const
{
  return salary;
}
long Employee::getPhone() const
{
  return phone_number;
}

void Employee::setName(std::string n)
{
  name = n;
}
void Employee::setId(int _id)
{
  id = _id;
}
void Employee::setDob(std::string dob)
{
  date_of_birth = dob;
}
void Employee::setDoj(std::string doj)
{
  date_of_join = doj;
}
void Employee::setSalary(long sal)
{
  salary = sal;
}
void Employee::setPhone(long phone)
{
  phone_number = phone;
}

void Employee::show()
{
  std::cout << "Name : " << getName() <<"\n";
  std::cout << "ID : " << getId() <<"\n";
  std::cout << "Date of birth : " << getDob() <<"\n";
  std::cout << "Date of join : " << getDoj() <<"\n";
  std::cout << "Salary : " << getSalary() <<"\n";
  std::cout << "Phone : " << getPhone() <<"\n";
}

Worker::Worker(int type , std::string n , std::string dob , std::string doj , long salary , long phone_number , std::string pass) : Employee(type , n , dob , doj , salary , phone_number , pass){};
void Worker::validateLoanRequest()
{
  size_t choice;
  //first read all Loan request from file;
  std::string filename = "db/customer/loanRequest.txt";
  std::ifstream infile(filename , std::ios::app);

  std::vector<Loan> loans;
  while(infile.good())
  {
    std::string c_name;
    long acc_num;
    long amount;
    infile >> c_name >> acc_num >> amount;
    loans.push_back(Loan(c_name , acc_num , amount));
  }

  clear_screen();
  std::cout 
  << std::left << std::setw(20) << "#"
  << std::left << std::setw(20) << "Customer Name"
  << std::setw(20) << "Account Number"
  << std::setw(20) << "Loan Amount" << std::endl;

  while(1)
  {
    clear_screen();
    for(size_t i=0; i<loans.size()-1; i++)
    {
      std::cout<<std::left << std::setw(20) << i+1;
      loans[i].show();
    }

    std::cout << "Press Loan Number to view more information\n";
    std::cout << "Press 0 to go back\n";
    std::cin >>choice;
    if(choice == 0) break;
    else
    {
      clear_screen();
      while(1)
      {
        clear_screen();
        std::cout 
        << std::left << std::setw(20) << "Customer Name : " << loans[choice-1].getCustomerName() << "\n"
        << std::setw(20) << "Account Number : "  << loans[choice-1].getCustomerAccountNumber() << "\n"
        << std::setw(20) << "Loan Amount : "  << loans[choice-1].getAmount()<< std::endl;

        std::cout << "\n\n\n\tPress 1 to view account History\n";
        std::cout << "\tPress 2 to Approve Loan\n";
        std::cout << "\tPress 3 to Decline Loan\n";
        std::cout << "\tPress 0 to go back\n";

        int option;
        std::cin >> option;

        if (option == 1)
        {
          viewTransactionHistory(loans[choice-1].getCustomerName());
          std::cout << "Press 0 to go back\n";
          int op;
          std::cin >> op;
        }
        else if (option == 2) 
        {
          //first initiate transfer to account
          std::string filename;
          filename = "db/customer/transfers.txt"; 
    
          std::ofstream outfile(filename , std::ios::app);
          outfile << loans[choice-1].getCustomerAccountNumber() << " " << loans[choice-1].getAmount() <<"\n";
          outfile.close();

          //Bank class will handle the deposit into appropriate account

          //Remove request from loan requests
          loans.erase(loans.begin() + choice - 1);
          //write new loan array to file
          filename = "db/customer/loanRequest.txt";
          outfile.open(filename);
          for(size_t i=0; i<loans.size(); i++)
          {
            outfile <<loans[i].getCustomerName() << " "<< loans[i].getCustomerAccountNumber() << " " << loans[i].getAmount() <<"\n";
          }
          outfile.close();

          std::cout << "Loan approved\n";
          Message msg(this->getName() , loans[choice-1].getCustomerName() , "Approved Loan Request" , "Dear Customer Your Loan Request have been approved. Your accound has been credited. Thanks for your fidelity\n" , time(NULL));
          msg.send();
          std::cout << "Press 0 to go back\n";

          int op;
          std::cin >> op;
          break;

        }
        else if (option == 3) 
        {
          //Remove request from loan requests
          loans.erase(loans.begin() + choice - 1);
          //write new loan array to file
          filename = "db/customer/loanRequest.txt";
          std::ofstream outfile(filename);
          for(size_t i=0; i<loans.size(); i++)
          {
            outfile <<loans[i].getCustomerName() << " "<< loans[i].getCustomerAccountNumber() << " " << loans[i].getAmount() <<"\n";
          }
          outfile.close();

          std::cout << "Loan Declined\n";
          Message msg(this->getName() , loans[choice-1].getCustomerName() , "Loan Request Denied" , "Dear Customer Your Loan Request have been declined. For more information contact us. Thanks for your fidelity\n" , time(NULL));
          msg.send();
          std::cout << "Press 0 to go back\n";

          int op;
          std::cin >> op;
          break;

        }
        else if (option == 0) break;

      }
    }   
  }
  
}
void Worker::viewTransactionHistory(std::string c_name)
{
  //open transaction file , read it and print it
  std::string filename;
  filename = "db/customer/transactions/";
  filename += c_name;
  filename += ".txt";

  std::ifstream infile(filename);
  if(!infile.is_open())
  {
    std::cout << "No transaction History\n";
  }
  else
  {
    Transaction* transactions[100];
    int n = 0;
    while(infile.good())
    {
      int type;
      long amount;
      long acc_num;
      time_t date;

      infile >> type >> acc_num >> amount >> date;
      transactions[n++] = new Transaction(c_name , type , amount , acc_num , date);
    }
    std::cout 
    << std::left << std::setw(30) << "\n\nAccount Number "
    << std::setw(30) << "Transaction Type  "
    << std::setw(30) << "Amount " 
    << std::setw(30) << "Date " <<std::endl;

    for(int i=0; i < n; i++)
    {
      transactions[i]->show();
      std::cout << std::endl;
    }
    std::cout<<"\n\tPress 1 to report a transaction\n";
    std::cout << "\n\n\t\tPress 0 to go Back\n";
    int c;
    std::cin >> c;
    if(c == 1)
    {
      std::cout << "Choose transaction number to report : ";
      int number;
      std::cin >> number;
      transactions[number-1]->report();
      std::cout << "\n\tTransaction Reported\n";
    }
  }
}

void Worker::sendMessageToCustomer()
{
  clear_screen();
  std::string c_name;
  std::string subject;
  std::string message;

  std::cout << "Enter Customer Name : \n";
  std::cin >> c_name;
  std::cin.ignore();
 
  std::cout << "Enter Subject : \n";
  std::getline(std::cin , subject);
  
  std::cout << "Enter Message : \n";
  std::getline(std::cin , message);

  Message msg(this->getName() , c_name , subject , message , time(NULL));
  msg.send(); 
  return;

}

void Worker::employeeMenu()
{
  while(1)
  {
    clear_screen();
    std::cout << "Bank Management System\n\n";
    std::cout << "---------------------\n\n";
    std::cout << "1) Check Loan Requests\n";
    std::cout << "2) View Customer Transaction History\n";
    std::cout << "3) Contact Customer\n";
    std::cout << "4) EXit\n";

    int option;
    std::cin >> option;

    switch(option)
    {
      case 1:
      {
        validateLoanRequest();
        break;
      }  
      case 2:
      {
        std::cout << "Enter Customer Name : ";
        std::string c_name;
        std::cin >> c_name;
        viewTransactionHistory(c_name);
        std::cout << "\n\n\t\tPress 0 to go Back\n";
        int c;
        std::cin >> c;
        break;
      }
      case 3:
      {
        sendMessageToCustomer();
        std::cout << "\n\nMessage Sent\n";
        std::cout << "\n\n\t\tPress 0 to go Back\n";
        char c;
        std::cin >> c;
        break;
      }
      case 4:
      {
        return;
      }      
    }
  }
}

Manager::Manager(int type , std::string n , std::string dob , std::string doj , long salary , long phone_number , std::string pass) : Employee(type , n , dob , doj , salary , phone_number , pass){};
void Manager::employeeMenu()
{
  while(1)
  {
    clear_screen();
    std::cout << "Bank Management System\n\n";
    std::cout << "---------------------\n\n";
    std::cout << "1) Print Customer List\n";
    std::cout << "2) Print Employee List\n";
    std::cout << "3) Print All Transactions\n";
    std::cout << "4) EXit\n";

    int option;
    std::cin >> option;

    switch(option)
    {
      case 1:
      {
        printCustomerList();
        std::cout << "\n\n\t\tPress 0 to go Back\n";
        int c;
        std::cin >> c;
        break;
      }  
      case 2:
      {
        printEmployeeList();
        std::cout << "\n\n\t\tPress 0 to go Back\n";
        int c;
        std::cin >> c;
        break;
      }
      case 3:
      {
        std::cout << "Enter Customer Name : ";
        std::string c_name;
        std::cin >> c_name;
        viewRecords(c_name);
        std::cout << "\n\n\t\tPress 0 to go Back\n";
        int c;
        std::cin >> c;
        break;
      }
      case 4:
      {
        return;
      }      
    }
  }
}
void Manager::printCustomerList()
{
  std::string filename = "db/bank/customer_accounts.txt";
  std::ifstream infile(filename);
  std::cout 
  <<std::left<< std::setw(20) << "Type" << std::setw(20) << "Name" << std::setw(20) << "Account Number"
  << std::setw(20) << "Date of Birth" << std::setw(20) << "Phone" << std::setw(20) << "Balance"
  << std::setw(20) << "Is Freezed" << std::setw(20) << "Number of Reports"
  << "\n\n";

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
    
    if(name.length() > 1)
    {
      std::cout 
      <<std::left<< std::setw(20) << ((type == 1) ? "Saving" : "Current") 
      << std::setw(20) << name 
      << std::setw(20) << account_number
      << std::setw(20) << dob 
      << std::setw(20) << phone 
      << std::setw(20) << balance
      << std::setw(20) << ((isFreezed == 1) ? "True" : "False") 
      << std::setw(20) << n_report 
      << std::endl;
    }    
  }
  infile.close(); 
}

void Manager::printEmployeeList()
{
  std::string filename = "db/bank/employee_accounts.txt";
  std::ifstream infile(filename);

  std::cout 
  <<std::left<< std::setw(20) << "Role" << std::setw(20) << "Name" << std::setw(20) << "Date of birth"
  << std::setw(20) << "Date of join" << std::setw(20) << "Salary" << std::setw(20) << "Phone"
  << "\n\n";;

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
    if(name.length() > 1)
    {
      std::cout 
      <<std::left<< std::setw(20) << ((type == 1) ? "Worker" : "Manager") 
      << std::setw(20) << name 
      << std::setw(20) << dob;
    }
    infile >> day >> month >> year >> salary >> phone >> pass;
    if(name.length() > 1)
    {
      std::string doj = day + " " + month + " " + " " + year;
      std::cout<< std::setw(20) << doj 
      << std::setw(20) << salary
      << std::setw(20) << phone
      << std::endl;
    }  
  } 
  infile.close();
}

void Manager::viewRecords(std::string c_name)
{
  std::string filename;
  filename = "db/customer/transactions/";
  filename += c_name;
  filename += ".txt";

  std::ifstream infile(filename);
  if(!infile.is_open())
  {
    std::cout << "No transaction History\n";
  }
  else
  {
    Transaction* transactions[100];
    int n = 0;
    while(infile.good())
    {
      int type;
      long amount;
      long acc_num;
      time_t date;

      infile >> type >> acc_num >> amount >> date;
      transactions[n++] = new Transaction(c_name , type , amount , acc_num , date);
    }
    std::cout 
    << std::left << std::setw(30) << "\n\nAccount Number "
    << std::setw(30) << "Transaction Type  "
    << std::setw(30) << "Amount " 
    << std::setw(30) << "Date " <<std::endl;

    for(int i=0; i < n; i++)
    {
      transactions[i]->show();
      std::cout << std::endl;
    }
    std::cout<<"\n\tPress 1 to report a transaction\n";
    std::cout << "\n\n\t\tPress 0 to go Back\n";
    int c;
    std::cin >> c;
    if(c == 1)
    {
      std::cout << "Choose transaction number to report : ";
      int number;
      std::cin >> number;
      transactions[number-1]->report();
      std::cout << "\n\tTransaction Reported\n";
    }
  }
}