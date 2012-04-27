#include "response.h"

Response::Response() : code_("220"), text_("richar_r.mendoza.epitech.eu. ESMTP Mendoza")
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
