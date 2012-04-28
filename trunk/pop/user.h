#ifndef USER_H
#define USER_H

#include <string>
class User
{
 public:
  User();
  User(const std::string &);
  User(const std::string &, const std::string &);

  ~User();
  const std::string	&getName() const;
  void			setName(const std::string &);
  const std::string	&getPassword() const;
  void			setPassword(const std::string &);

 private:
  std::string		name_;
  std::string		password_;
};
#endif
