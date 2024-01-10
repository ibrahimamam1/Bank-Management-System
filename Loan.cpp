#include "loan.hpp"
#include<iostream>
#include <fstream>
#include<iomanip>

std::string Loan::getCustomerName() const
{
    return customer_name;
}
long Loan::getCustomerAccountNumber() const
{
  return customer_account_number;
}
long Loan::getAmount() const
{
  return amount;
}

void Loan::setCustomerName(const std::string& name)
{
  customer_name = name;
}
void Loan::setCustomerAccountNumber(long accountNumber)
{
  customer_account_number = accountNumber;
}
void Loan::setAmount(long loanAmount)
{
  amount = loanAmount;
}
void Loan::request()
{
  std::string filename;
  filename = "db/customer/loanRequest.txt"; 
  std::ofstream outfile(filename , std::ios::app);
  outfile << this->getCustomerName() << " " << this->getCustomerAccountNumber() << " " << this->getAmount()<<"\n";
  outfile.close();
}
void Loan::show() const
{
  const int columnWidth = 20;
  std::cout 
  << std::setw(columnWidth) << customer_name
  << std::setw(columnWidth) << customer_account_number
  << std::setw(columnWidth) << amount << std::endl;
}

void Loan::operator = (Loan x)
{
  customer_name = x.getCustomerName();
  customer_account_number = x.getCustomerAccountNumber();
  amount = x.getAmount();
}