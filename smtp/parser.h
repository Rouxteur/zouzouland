#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "request.h"

class Parser
{
  bool		complete_;
  Request	request_;

public:
  Parser();
  std::string	req_;

  bool		isComplete() const;
  Request	&getRequest();
  void		parseCmd(const std::string &);
};

#endif // PARSER_H
