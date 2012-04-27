#include "response.h"

Response::Response() : code_("+OK"), text_("POP3 server ready<1896.697170952@richar-r.mendoza.epitech.eu>")
{
}

const char * Response::getText() const
{
    return this->text_.c_str();
}


const char * Response::getCode() const
{
    return this->code_.c_str();
}

void	Response::setText(const std::string &text)
{
  text_ = text;
}

void	Response::setCode(const std::string &code)
{
  code_ = code;
}

void	Response::resetResponse()
{
    this->code_ = "";
    this->text_ = "";
}
