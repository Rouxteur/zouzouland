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
	std::list<User *>::iterator it;

  for ( it=users_.begin() ; it != users_.end(); it++ )
    {
		delete *it;
  }
}

bool	UserList::findUser(const std::string &name, const std::string &password)
{
  std::list<User *>::iterator it = users_.begin();

  for ( ; 
	  it != users_.end(); it++ )
    {
      User *myuser = *it;
      if (name.compare(myuser->getName()) == 0 && password.compare(myuser->getPassword()) == 0)
		return true;
    }
  return false;
}
