#include "request.h"

Request::Request() : cmd_(""), args_("")
{
  
}
void			Request::setCmd(std::string cmd)
{
  this->cmd_ = cmd;
}

const std::string	&Request::getCmd() const
{
  return cmd_;
}

void			Request::setArgs(const std::string &args)
{
  this->args_ = args;
}

const std::string	&Request::getArgs() const
{
  return args_;
}

void			Request::resetRequest()
{
  this->setCmd("");
  this->setArgs("");
}
