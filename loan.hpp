#ifndef LOAN_HPP
#define LOAN_HPP
#include <string>
class Loan
{
  std::string customer_name;
  long customer_account_number;
  long amount;

  public:
    Loan();
    Loan(const std::string& name, long accountNumber, long loanAmount): customer_name(name), customer_account_number(accountNumber), amount(loanAmount) {}
    std::string getCustomerName() const;
    long getCustomerAccountNumber() const;
    long getAmount() const;

    void setCustomerName(const std::string& name);
    void setCustomerAccountNumber(long accountNumber);
    void setAmount(long loanAmount);
    void request();
    void show() const;

    void operator = (Loan);
};
#endif