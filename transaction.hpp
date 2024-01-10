#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include<ctime>
#include<iostream>

class Transaction
{
  std::string customer_name;
  int type;
  long amount;
  long account_number;
  time_t date;
  static int n_transactions;

  public:
  Transaction();
  Transaction(std::string c_name , int t , long amt , long acct_num , time_t d);
  int getType();
  long getAmount();
  std::string getCustomerName();
  long getAccountNumber();
  time_t getDate();
  static int getNTransactions();

  void save();
  void report();
  void show();
};

#endif