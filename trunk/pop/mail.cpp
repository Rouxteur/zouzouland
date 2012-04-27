#include "mail.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

Mail::Mail() : to_(""), from_(""), content_(""), saved_(false)
{
}

Mail::~Mail()
{
}

const std::string	&Mail::getTo() const
{
  return this->to_;
}

void			Mail::setTo(const std::string &to)
{
  this->to_ = to;
}

const std::string	&Mail::getFrom() const
{
  return this->from_;
}

void			Mail::setFrom(const std::string &from)
{
  this->from_ = from;
}

const std::string	&Mail::getContent() const
{
  return this->content_;
}

void			Mail::setContent(const std::string &content)
{
  this->content_ = content;
}

bool			Mail::save()
{
	if (!this->saved_ && !this->to_.empty() && !this->content_.empty())
    {
      std::string folder(path);
      int i = 1;

      folder.append("/");
      folder.append(this->to_);
      folder.append("/");

      std::string file1(folder + "1");
      FILE * fp = fopen(file1.c_str(), "rb");
  
      while (fp != NULL)
	{
	  fclose(fp);
	  std::ostringstream oss;
	  oss << i;
	  std::string file(folder + oss.str());
	  fp = fopen(file.c_str(), "rb");
	  i++;
	}
	if (i > 1)
      i--;
      std::ostringstream oss;
      oss << i;
      std::string finalfile(folder + oss.str());
      std::ofstream wfile(finalfile.c_str());  
      wfile << this->content_;
      wfile.close();
      this->saved_ = true;
	  std::cout << "new mail saved to " << finalfile << std::endl;
    }
  return true;
}
