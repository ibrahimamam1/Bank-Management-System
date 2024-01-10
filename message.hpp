#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <bits/types/time_t.h>
#include<string>
class Message
{
  std::string from;
  std::string to;
  std::string subject;
  std::string message;
  time_t date;

  public:
    Message();
    Message(const std::string &from,const std::string &to , const std::string &subject, const std::string &message , const time_t& date); // 3-argument constructor

    std::string getFrom()const;
    std::string getTo() const;
    std::string getSubject()const;
    std::string getMessage()const;
    time_t getDate() const;

    void send();
    void show();
};
#endif