#include "client.h"
#include <iostream>

void Client::commandError()
{
  this->response_.setCode("500");
  this->response_.setText("Syntax Error");
  this->request_.resetRequest();
}

void Client::commandHelo(const std::string &arg)
{
  this->response_.setCode("250");
  this->response_.setText("richar_r.mendoza.epitech.eu");
  this->request_.resetRequest();
}

void Client::commandMail(const std::string &arg)
{
  std::string myarg(arg.c_str());
  if (myarg.size() > 10)
    myarg = myarg.substr(6, myarg.size() - 9);
  
  this->mail_.setFrom(myarg);
  this->response_.setCode("250");
  this->response_.setText("2.1.0 Ok");
  this->request_.resetRequest();
}

void Client::commandRcpt(const std::string &arg)
{
  std::string myarg(arg.c_str());
  //if (myarg.size() > 10)
  //myarg = myarg.substr(7, myarg.size() - 7);
  unsigned int sep = myarg.find("@richar-r.mendoza.epitech.eu");
  std::cout << myarg << std::endl;
  if (sep != std::string::npos && sep > 4)
    {
      myarg = myarg.substr(4, myarg.size() - (myarg.size() - sep) - 4);
      std::cout << myarg << std::endl;
      if (this->server_.getUserList().findUser(myarg))
	{
	  this->mail_.setTo(myarg);
	  this->response_.setCode("250");
	  this->response_.setText("2.1.5 Ok");
	  this->request_.resetRequest();
	}
      else
	{
	  this->response_.setCode("515");
	  this->response_.setText("Destination mailbox address invalid.");
	  this->request_.resetRequest();
	}
    }
  else
    {
      this->response_.setCode("512");
      this->response_.setText("Host Unknown");
      this->request_.resetRequest();
    }
}

void Client::commandData(const std::string &arg)
{ 
  if (arg.compare("\n") == 0)
    {
      this->response_.setCode("354");
      this->response_.setText("Enter mail, end with . on a line by itself");
    }
  else
    {
      this->mail_.setContent(arg);
      this->response_.setCode("250");
      this->response_.setText("2.0.0 Ok");
      if (mail_.save())
	this->request_.resetRequest();
    }
}

void Client::commandQuit(const std::string &arg)
{
  this->mail_.save();
  this->response_.setCode("221");
  this->response_.setText("2.0.0 Bye");
  this->request_.resetRequest();
}
