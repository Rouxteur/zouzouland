#include "parser.h"
#include <iostream>
Parser::Parser() : complete_(false), req_("")
{ 
}

bool		Parser::isComplete() const
{
  return complete_;
}

Request	&Parser::getRequest()
{
  return request_;
}

void		Parser::parseCmd(const std::string &line)
{
  this->req_.append(line);
  this->complete_ = false;

  while (this->req_.at(0) == ' ')
    this->req_ = this->req_.substr(1, this->req_.size() - 1);

  if (this->req_.find("\n") && this->request_.getCmd().empty())
    {  
      if (this->req_.size() >= 4)
	this->request_.setCmd(this->req_.substr(0, 4));
      if (this->req_.size() >= 6)
	this->request_.setArgs(this->req_.substr(5, this->req_.size() -5));
      if (this->req_.size() >= 9)
	this->req_ = this->request_.getArgs();
      else 
	this->req_ = "    ";
      this->complete_ = true;
    }
  if (this->request_.getCmd().compare("DATA") == 0)
    if (this->req_.substr(this->req_.size() - 4, 4).compare("\n.\r\n") == 0)
      {
	this->request_.setArgs(this->req_);
	this->complete_ = true;
      }

  if (this->complete_ == true)
      this->req_ = "";
}
