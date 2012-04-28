#include "userlist.h"
#include <iostream>

UserList::UserList()
{
  User *user1 = new User("bob", "9f9d51bc70ef21ca5c14f307980a29d8"); // bob : bob
  User *user2 = new User("joe", "8ff32489f92f33416694be8fdc2d4c22"); // joe : joe
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
      std::cout << name << " to " << myuser->getName() << std::endl;
      std::cout << password << " to " << myuser->getPassword() << std::endl;
      if (name.compare(myuser->getName()) == 0 && password.compare(myuser->getPassword()) == 0)
		return true;
    }
  return false;
}
