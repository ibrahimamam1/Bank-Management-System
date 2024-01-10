#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
class Employee
{
  int type;
  std::string name;
  int id;
  std::string date_of_birth;
  std::string date_of_join;
  std::string pass;
  long salary;
  long phone_number;
  static int n_employees;

  public:
  Employee();
  Employee(int type , std::string n , std::string dob , std::string doj , long salary , long phone_number , std::string pass);

  std::string getName() const;
  int getId() const;
  std::string getDob() const;
  std::string getDoj() const;
  std::string getPass() const;
  long getSalary() const;
  long getPhone() const;

  void setName(std::string n);
  void setId(int _id);
  void setDob(std::string );
  void setDoj(std::string );
  void setPass(std::string );
  void setSalary(long);
  void setPhone(long);

  void show();
  virtual void employeeMenu() = 0;

};

class Worker : public Employee
{
  public:
  Worker(int type , std::string n , std::string dob , std::string doj , long salary , long phone_number , std::string pass);
  void show();
  void validateLoanRequest();
  void viewTransactionHistory(std::string c_name);
  void sendMessageToCustomer();
  void employeeMenu();
};

class Manager : public Employee
{
  public:
  Manager(int type , std::string n , std::string dob , std::string doj , long salary , long phone_number , std::string pass);
  void printCustomerList();
  void printEmployeeList();
  void viewRecords(std::string c_name);
  void employeeMenu();
};



#endif