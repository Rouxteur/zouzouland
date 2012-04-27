#include "userlist.h"
#include <iostream>

UserList::UserList()
{
  User *user1 = new User("bob");
  User *user2 = new User("joe");
  users_.push_front(user1);
  users_.push_front(user2);
}

UserList::~UserList()
{
}

bool	UserList::findUser(const std::string &name)
{
  std::list<User *>::iterator it;

  for ( it=users_.begin() ; it != users_.end(); it++ )
    {
      User *myuser = *it;
      if (name.compare(myuser->getName()) == 0)
	return true;
    }
  return false;
}
