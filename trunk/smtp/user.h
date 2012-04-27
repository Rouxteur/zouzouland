#ifndef USER_H
#define USER_H

#include <string>
class User
{
 public:
  User();
  User(const std::string &);
  ~User();
  const std::string	&getName() const;
  void			setName(const std::string &);

 private:
  std::string		name_;
};
#endif
