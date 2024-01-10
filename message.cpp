#include "message.hpp"
#include <bits/types/time_t.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ctime>

Message::Message() {}
Message::Message(const std::string &from, const std::string &to , const std::string &subject, const std::string &message , const time_t& date): from(from) , to(to), subject(subject), message(message) , date(date){} 

std::string Message::getFrom() const
{
  return from;
}

std::string Message::getTo() const
{
  return to;
}
std::string Message::getSubject() const
{
   return subject;
}

std::string Message::getMessage() const
{
  return message;
}
time_t Message::getDate() const
{
  return date;
}
 void Message::send()
{
  std::string filename = "db/customer/messages/";
  filename += this->getTo();
  filename += ".txt";

  std::ofstream outfile(filename , std::ios::app);
  outfile << this->getFrom() << " " << this->date <<"\n";
  outfile << this->getSubject() << "\n";
  outfile << this->getMessage()<<"\n";
  outfile.close();
}

void Message::show()
{
  time_t dt = this->getDate();
  std::cout << "From: " << this->getFrom() << "\nDate: " << asctime(localtime(&dt)) << "\n";
  std::cout << "Subject: " << this->getSubject() << "\n";
  std::cout << "Message: " << this->getMessage() << "\n\n";
}