#include "transaction.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

Transaction::Transaction(){}
Transaction::Transaction(std::string c_name , int t , long amt , long acc_num , time_t d) :customer_name(c_name) , type(t) , amount(amt) , account_number(acc_num) , date(d){}

int Transaction::getType()
{
  return type;
}

long Transaction::getAmount()
{
  return amount;
}

std::string Transaction::getCustomerName()
{
  return customer_name;
}
long Transaction::getAccountNumber()
{
  return account_number;
}

time_t Transaction::getDate()
{
  return date;
}

int Transaction::getNTransactions()
{
  return n_transactions;
}

void Transaction::save()
{
   //write deposit to file
    
    //First set appropriate directory
    std::string filename;
    
    filename = "db/customer/transactions/"; 
    filename += this->getCustomerName();
    filename += ".txt";

    //Then write to File and close it
    std::ofstream outfile(filename , std::ios::app);
    outfile << this->getType() << " "<< this->getAccountNumber()<< " "<<amount << " " << time(NULL)<<"\n";
    outfile.close();
}

void Transaction::report()
{
  //write transaction to file so Bank class can process it
  std::string filename;
  filename = "db/customer/reportedTransaction.txt"; 

  //Then write to File and close it
  std::ofstream outfile(filename , std::ios::app);
  outfile << this->getAccountNumber()<< "\n";
  outfile.close();
}

void Transaction::show()
{
  std::cout 
  << std::setw(30)  << account_number
  << std::left << std::setw(30) << (type == 1 ? "Deposit" : "Withdrawal")
  << std::setw(30) << amount
  << std::setw(30) << asctime(localtime(&date));
}
