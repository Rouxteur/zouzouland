#include "user.h"

User::User() : name_("")
{
}

User::User(const std::string &name) : name_(name)
{
}

User::~User()
{
}

const std::string	&User::getName() const
{
  return name_;
}

void			User::setName(const std::string &name)
{
  name_ = name;
}

const std::string	&User::getPassword() const
{
  return password_;
}

void			User::setPassword(const std::string &password)
{
  this->password_ = password;
}
