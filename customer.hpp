#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
class Customer
{
  int account_type;
  std::string name;
  long account_number;
  std::string date_of_birth;
  long phone_number;
  std::string pass;
  long balance;
  long minimum_deposit;
  long minimum_withdrawal;
  bool isFreezed;
  int reported_transactions;
  

  public:
  class INVALID_AMOUNT{}; //Exception class
  class ACCOUNT_FREEZED{}; //Exception class
  Customer();
  Customer(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass); 
  Customer(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass , long balance , bool isFreezed , int n_report);
  
  int getAccountType() const;
  std::string getName() const;
  long getAccountNumber() const;
  std::string getDateOfBirth() const;
  long getPhoneNumber() const;
  std::string getPass() const;
  long getBalance() const;
  long getMinimumDeposit() const;
  long getMinimumWithdrawal() const;
  bool getFreezeStatus() const;
  int getReportedTransactions() const;

  void setAccountType(int);
  void setName(std::string);
  void setAccountNumber(long) ;
  void setDateOfBirth(std::string );
  void setPhoneNumber(long );
  void setBalance(long);
  void setPass(std::string);
  void setFreezeStatus(bool);
  void incrementReport();

  virtual void deposit(long amount) = 0;
  virtual void withdrawal(long amount) = 0;
  virtual void transfer(long account_number , long amount) = 0;
  void checkBalance();
  void viewHistory();
  void requestLoan(long amount);
  void customerMenu();

  void save();

};

class Saving : public Customer
{
  double annual_interest_rate;
  double transfer_fee;

  public:
  Saving();
  Saving(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass); 
  Saving(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass , long balance , bool isFreezed , int n_report);
  
  double getTransferFee() const;
  double getAnnualInterstRate() const;

  void deposit(long amount);
  void withdrawal(long amount);
  void transfer(long account_number , long amount); //Todo
};

class Current : public Customer
{
  public:
  Current();
  Current(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass); 
  Current(int acc_type , std::string n , long acc , std::string dob , long phone , std::string pass , long balance , bool isFreezed , int n_report);
  void deposit(long amount);
  void withdrawal(long amount);
  void transfer(long account_number , long amount); //Todo
};
#endif