#ifndef REQUEST_H
#define REQUEST_H
#include <string>
#include <algorithm>

class Request
{
public:
  Request();
  void          	setCmd(std::string cmd);
  const std::string&	getCmd() const;
  void          	setArgs(const std::string& args);
  const std::string&	getArgs() const;
  void                  resetRequest();
 private:
    std::string         cmd_;
    std::string         args_;
};

#endif // REQUEST_H
