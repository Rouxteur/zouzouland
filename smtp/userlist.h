#ifndef USERLIST_H
#define USERLIST_H

#include <list>
#include "user.h"

class UserList
{
 public:
  UserList();
  ~UserList();
  bool findUser(const std::string &);

 private:
  std::list<User *>	users_;
};
#endif
