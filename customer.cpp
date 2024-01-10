#include"customer.hpp"
#include "functions.hpp"
#include "loan.hpp"
#include "message.hpp"
#include "transaction.hpp"
#include <bits/types/time_t.h>
#include <ctime>
#include <fstream>
#include<iostream>
#include <string>
#include <iomanip>
#include <vector>

Customer::Customer(){}
Customer::Customer(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass) : account_type(acc_type) ,  name(n) , account_number(acc) , date_of_birth(dob), phone_number(phone) , pass(pass) , balance(5000) , minimum_deposit(1000) , minimum_withdrawal(500) , isFreezed(false) , reported_transactions(0)
{
 
}
Customer::Customer(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass , long balance , bool isFreezed , int n_report) : account_type(acc_type) ,  name(n) , account_number(acc) , date_of_birth(dob), phone_number(phone) , pass(pass) , balance(balance) , minimum_deposit(1000) , minimum_withdrawal(500) , isFreezed(isFreezed) , reported_transactions(n_report)
{
 
}
int Customer::getAccountType() const
{
  return account_type;
}
std::string Customer::getName() const
{
  return name;
}
long Customer::getAccountNumber() const
{
  return account_number;
}
std::string Customer::getDateOfBirth() const
{
  return date_of_birth;
}
long Customer::getPhoneNumber() const
{
  return phone_number;
}
std::string Customer::getPass() const
{
  return pass;
}
long Customer::getBalance() const
{
  return balance;
}
long Customer::getMinimumDeposit() const
{
  return minimum_deposit;
}
long Customer::getMinimumWithdrawal() const
{
  return minimum_withdrawal;
}
double Saving::getTransferFee() const
{
  return transfer_fee;
}
bool Customer::getFreezeStatus() const
{
  return isFreezed;
}
int Customer::getReportedTransactions() const
{
  return reported_transactions;
}

void Customer::setAccountType(int acc_t)
{
  account_type = acc_t;
}
void Customer::setName(std::string n)
{
  name = n;
}
void Customer::setAccountNumber(long acc)
{
  account_number = acc;
}
void Customer::setDateOfBirth(std::string dob)
{
  date_of_birth = dob;
}
void Customer::setPhoneNumber(long phone)
{
  phone_number = phone;
}
void Customer::setBalance(long bal)
{
  balance = bal;
}
void Customer::setPass(std::string p)
{
  pass = p;
}
void Customer::setFreezeStatus(bool freeze)
{
  isFreezed = freeze;
}
void Customer::incrementReport()
{
  reported_transactions++;
}

void Customer::checkBalance()
{
  clear_screen();
  std::cout << "Current Balance : " << balance << std::endl;
}
void Customer::viewHistory()
{
  //open transaction file , read it and print it
  std::string filename;
  filename = "db/customer/transactions/";
  filename += this->getName();
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
      transactions[n++] = new Transaction(this->getName(), type , amount , acc_num , date);
      
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
    }
  }  
}
void Customer::requestLoan(long amount)
{
  if(this->isFreezed) throw ACCOUNT_FREEZED();
  if(amount > 100000 || amount < 10000) throw INVALID_AMOUNT();
  
  Loan loan(this->getName() , this->getAccountNumber() , amount);
  loan.request();
}

void Customer::customerMenu()
{
  while(1)
  {
    clear_screen();
    std::cout << "Bank Management System\n\n";
    std::cout << "---------------------\n\n";
    std::cout << "1) Check Balance\n";
    std::cout << "2) Deposit\n";
    std::cout << "3) withdrawal\n";
    std::cout << "4) Transfer\n";
    std::cout << "5) Request Loan\n";
    std::cout << "6) View History\n";
    std::cout << "7) Inbox\n";
    std::cout << "8) EXit\n";

    int option;
    std::cin >> option;

    switch(option)
    {
      case 1:
      {
        this->checkBalance();
        std::cout << "\n\n\t\tPress 2 to go Back\n";
        char c;
        std::cin >> c;
        break;
      }  
      case 2:
      {
        std::cout << "Enter Amount : ";
        long amount;
        std::cin >> amount;
        try
        {
          this->deposit(amount);
          std::cout << "\n--Deposit succesfull--\n";
        }
        catch(Saving::ACCOUNT_FREEZED)
        {
          std::cout << "This Accound is Freezed , please Contact Support\n";
        }
        catch(Saving::INVALID_AMOUNT)
        {
          std::cout << "This Amount is invalid , please enter valid amount\n";
        }
        std::cout << "\n\n\t\tPress 2 to go Back\n";
        char c;
        std::cin >> c;
        break;
      }
      case 3:
      {
        std::cout << "Enter Amount : ";
        long amount;
        std::cin >> amount;
        try
        {
          this->withdrawal(amount);
          std::cout << "\n--Withdrawal succesfull--\n";
        }
        catch(Saving::ACCOUNT_FREEZED)
        {
          std::cout << "This Accound is Freezed , please Contact Support\n";
        }
        catch(Saving::INVALID_AMOUNT)
        {
          std::cout << "This Amount is invalid , please enter valid amount\n";
        }
        std::cout << "\n\n\t\tPress 2 to go Back\n";
        char c;
        std::cin >> c;
        break;
      }
      case 4:
      {
        std::cout << "Enter Account Number : ";
        long acc;
        std::cin >> acc;
        //TODO: Add function to check if account exist before initiating tansfer
        std::cout << "Enter Amount : ";
        long amount;
        std::cin >> amount;
        try
        {
          this->transfer(acc , amount);
          std::cout << "\n--Transfer Processing--\n";
        }
        catch(Saving::ACCOUNT_FREEZED)
        {
          std::cout << "This Accound is Freezed , please Contact Support\n";
        }
        catch(Saving::INVALID_AMOUNT)
        {
          std::cout << "This Amount is invalid , please enter valid amount\n";
        }
        std::cout << "\n\n\t\tPress 2 to go Back\n";
        char c;
        std::cin >> c;
        break;
      } 
      case 5:
      {
        long amount;
        std::cout << "Enter Loan Amount\n";
        std::cin >>  amount;
        try
        {
          requestLoan(amount);
          std::cout << "Your request will be processed. An employee will contact you\n";
        } 
        catch(Saving::ACCOUNT_FREEZED)
        {
          std::cout << "This Accound is Freezed , please Contact Support\n";
        }
        catch(Saving::INVALID_AMOUNT)
        {
          std::cout << "This Amount is invalid , please enter valid amount\n";
        }
        std::cout << "\n\n\t\tPress 2 to go Back\n";
        char c;
        std::cin >> c;
        break;
      }
      case 6:
      {
        viewHistory();
        std::cout << "\n\n\t\tPress 2 to go Back\n";
        char c;
        std::cin >> c;
        break;

        break;
      }
      case 7:
      {
        //first read message file
        std::string filename = "db/customer/messages/";
        filename += this->getName();
        filename += ".txt";

        std::ifstream infile(filename);
        std::vector<Message*>msgs;
        while(infile.good())
        {
          std::string from;
          time_t date;
          std::string subject;
          std::string message;

          infile >> from >> date;
          infile.seekg(1 , std::ios::cur);
          getline(infile , subject);
          getline(infile , message);
          msgs.push_back(new Message(from , this->getName() , subject , message , date));
        }

        for(int i=msgs.size()-2; i>=0; i--)
        {
          msgs[i]->show();
          std::cout<<std::endl;
        }
      }
      case 8:
      {
        return;
      }      
    }
  }
}

void Customer::save()
{
  std::string filename = "db/bank/customer_accounts.txt";
  std::ofstream outfile(filename , std::ios::app);

  outfile << this->getAccountType() << " "<< this->getName() << " " << this->getAccountNumber() << " " <<this->getDateOfBirth() << " " << this->getPhoneNumber() << " " << this->getBalance() << " " << this->getFreezeStatus() << " " << this->getReportedTransactions() << " " << this->getPass() <<"\n";
  outfile.close();
}

Saving::Saving() : Customer()
{

}
Saving::Saving(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass) : Customer(acc_type , n , acc , dob , phone , pass)
{
 
}
Saving::Saving(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass , long balance , bool isFreezed , int n_report) : Customer(acc_type , n , acc , dob , phone , pass , balance , isFreezed , n_report) , annual_interest_rate(1.2) , transfer_fee(100) 
{

}
void Saving::deposit(long amount)
{
  if(this->getFreezeStatus() == true) throw ACCOUNT_FREEZED();
  if(amount < this->getMinimumDeposit()) throw INVALID_AMOUNT();

  this->setBalance(this->getBalance() +amount);
  Transaction transac(this->getName() , 1 , amount , this->getAccountNumber() , time(NULL));

  transac.save(); //write transaction to File
}

void Saving::withdrawal(long amount)
{
  if(this->getFreezeStatus() == true) throw ACCOUNT_FREEZED();
  if(amount < this->getMinimumWithdrawal() || amount > this->getBalance()) throw INVALID_AMOUNT();

  this->setBalance(this->getBalance() - amount);

  Transaction transac(this->getName() , 2 , amount , this->getAccountNumber() , time(NULL));

  transac.save(); //write transaction to File
}

void Saving::transfer(long acc , long amount)
{
  withdrawal(amount + transfer_fee);
  Transaction transac(this->getName() , 3, amount , this->getAccountNumber() , time(NULL));

  transac.save(); //write transaction to File
  //write transfer to file so Bank class can process it
  std::string filename;
  filename = "db/customer/transfers.txt"; 
    
  std::ofstream outfile(filename , std::ios::app);
  outfile << acc << " " << amount <<"\n";
  outfile.close();

  //Bank class will handle the deposit into appropriate account
}

Current::Current()
{

}
Current::Current(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass) : Customer(acc_type , n , acc , dob , phone , pass)
{
 
}
Current::Current(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass , long balance , bool isFreezed , int n_report) : Customer(acc_type , n , acc , dob , phone , pass , balance , isFreezed , n_report){}

void Current::deposit(long amount)
{
  if(this->getFreezeStatus() == true) throw ACCOUNT_FREEZED();
  if(amount < this->getMinimumDeposit()) throw INVALID_AMOUNT();

  this->setBalance(this->getBalance() +amount);

  Transaction transac(this->getName() , 1 , amount , this->getAccountNumber() , time(NULL));

  transac.save(); //write transaction to File

}

void Current::withdrawal(long amount)
{
  if(this->getFreezeStatus() == true) throw ACCOUNT_FREEZED();
  if(amount < this->getMinimumWithdrawal() || amount > this->getBalance()) throw INVALID_AMOUNT();

  this->setBalance(this->getBalance() - amount);

  Transaction transac(this->getName() , 2 , amount , this->getAccountNumber() , time(NULL));

  transac.save(); //write transaction to File
}

void Current::transfer(long acc , long amount)
{
  withdrawal(amount);
  Transaction transac(this->getName() , 3 , amount , this->getAccountNumber() , time(NULL));

  transac.save(); //write transaction to File

  //write transfer to file so Bank class can process it
  std::string filename;
  filename = "db/customer/transfers.txt"; 
    
  std::ofstream outfile(filename , std::ios::app);
  outfile << acc << " " << amount <<"\n";
  outfile.close();

  //Bank class will handle the deposit into appropriate account
}