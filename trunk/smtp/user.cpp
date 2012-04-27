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
