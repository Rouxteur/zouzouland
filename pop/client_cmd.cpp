#include "client.h"
#include <iostream>

void Client::commandError()
{
  this->response_.setCode("500");
  this->response_.setText("Syntax Error");
  this->request_.resetRequest();
}

void Client::commandStat(const std::string &arg)
{
  this->response_.setCode("+Ok");
  this->response_.setText("x 1024");
  this->request_.resetRequest();
}

void Client::commandRetr(const std::string &arg)
{
  this->response_.setCode("+Ok");
  this->response_.setText("mail");
  this->request_.resetRequest();
}

void Client::commandApop(const std::string &arg)
{
  std::string myarg(arg.c_str());
  unsigned int sep = myarg.find(" ");
  if (sep != std::string::npos && sep > 1)
    {
		std::string uname(myarg.substr(0, sep));
		std::string upass(myarg.substr(sep, myarg.size() - sep));
      if (this->server_.getUserList().findUser(uname, upass))
		{
			user_.setName(uname);
			user_.setPassword(upass);
			this->response_.setCode("+Ok");
			this->response_.setText(uname + "'s mailbox has x messages ( 1024 )");
			this->request_.resetRequest();
		}
      else
		{
		  this->response_.setCode("-Err");
		  this->response_.setText("Permission denied");
		  this->request_.resetRequest();
		}
    }
  else
    {
      this->response_.setCode("-Err");
		  this->response_.setText("Bad Request");
      this->request_.resetRequest();
    }
}

void Client::commandList(const std::string &arg)
{ 
      this->response_.setCode("+Ok");
      this->response_.setText("Enter mail, end with . on a line by itself");
	  this->request_.resetRequest();
}

void Client::commandDele(const std::string &arg)
{ 
      this->response_.setCode("+Ok");
      this->response_.setText("message " + arg + " deleted");
	  this->request_.resetRequest();
}

void Client::commandQuit(const std::string &arg)
{
  this->response_.setCode("+Ok");
  this->response_.setText("QUIT");
  this->decoOrder_ = true;
  this->request_.resetRequest();
}
