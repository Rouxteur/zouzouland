#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

class Response
{
 private:
  std::string	code_;
  std::string	text_;
  
 public:
  Response();
  const char	*getText() const;
  const char	*getCode() const;
  void		resetResponse();
  void		setText(const std::string &);
  void		setCode(const std::string &);

};

#endif // RESPONSE_H
