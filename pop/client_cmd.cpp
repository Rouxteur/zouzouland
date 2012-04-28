#include "client.h"
#include <iostream>

std::string Client::MailsInfo(const std::string &name)
{
      DIR *pdir;
      struct dirent *pent;
      int nb_files = 0;
      int total_size = 0;
      std::string folder("../mails/");
      folder.append(name);
      folder.append("/");
      pdir = opendir(folder.c_str());
      if (!pdir)
	std::cerr << "failed to open mails" << std::endl;
      else
	while ((pent=readdir(pdir)))
	  {
	    if (pent->d_type != DT_DIR)
	      {
		nb_files++;
		total_size += pent->d_reclen;
	      }
	  }
      closedir(pdir);
      
      std::ostringstream oss, oss2;      
      oss << nb_files;
      std::string txt(oss.str());
      txt.append(" ");
      oss2 << total_size;
      txt.append(oss2.str());      
      return txt;
}

void Client::commandError()
{
  this->response_.setCode("500");
  this->response_.setText("Syntax Error");
  this->request_.resetRequest();
}


void Client::commandStat(const std::string &arg)
{
  if (this->user_ != NULL)
    {
      std::string txt(this->MailsInfo(this->user_->getName()));
      this->response_.setCode("+Ok");
      this->response_.setText(txt);
      this->request_.resetRequest();
    }
  else
    {
      this->response_.setCode("-Err");
      this->response_.setText("Permission denied");
      this->request_.resetRequest();
    }
}

void Client::commandRetr(const std::string &arg)
{
  this->response_.setCode("+Ok");
  this->response_.setText("mail");
  this->request_.resetRequest();
}

void Client::commandApop(const std::string &arg)
{
  std::string myarg(arg.c_str());
  unsigned int sep = myarg.find(" ");
  if (sep != std::string::npos && sep > 1)
    {
      std::string uname(myarg.substr(0, sep));
      std::string upass(myarg.substr(sep + 1, 32));
      if ((this->user_ = this->server_.getUserList().findUser(uname, upass)) != NULL)
	{
	  std::string vals(this->MailsInfo(uname));
	  std::istringstream ss(vals);
	  std::string s;
	  std::string txt;

	  txt.append("'s mailbox has ");
	  ss >> s;
	  txt.append(s);
	  txt.append(" messages (");
	  ss >> s;
	  txt.append(s);
	  txt.append(" octets )");

	  this->response_.setText(txt);
	  this->request_.resetRequest();
      	}
	else
	{
	  this->response_.setCode("-Err");
	  this->response_.setText("Permission denied");
	  this->request_.resetRequest();
	}
    }
  else
    {
      this->response_.setCode("-Err");
		  this->response_.setText("Bad Request");
      this->request_.resetRequest();
    }
}

void Client::commandList(const std::string &arg)
{ 
  if (user_ != NULL)
    {
      DIR *pdir;
      struct dirent *pent;
      int nb_files = 0;
      int total_size = 0;
      std::string folder("../mails/");
      folder.append(user_->getName());
      folder.append("/");
      pdir = opendir(folder.c_str());
      if (!pdir)
	std::cerr << "failed to open mails" << std::endl;
      else
	while ((pent=readdir(pdir)))
	  {
	    if (pent->d_type != DT_DIR)
	      {
		nb_files++;
		total_size += pent->d_reclen;
	      }
	  }
      closedir(pdir);
      
      this->response_.setCode("+Ok");
      std::ostringstream oss, oss2;      
      oss << nb_files;
      std::string txt(oss.str());
      txt.append(" ");
      oss2 << total_size;
      txt.append(oss2.str());      
      this->response_.setText(txt);
      this->request_.resetRequest();
    }
  else
    {
      this->response_.setCode("-Err");
      this->response_.setText("Permission denied");
      this->request_.resetRequest();
    }  
}

void Client::commandDele(const std::string &arg)
{ 
      this->response_.setCode("+Ok");
      this->response_.setText("message " + arg + " deleted");
	  this->request_.resetRequest();
	  }

void Client::commandQuit(const std::string &arg)
{
  this->response_.setCode("+Ok");
  this->response_.setText("QUIT");
  this->decoOrder_ = true;
  this->request_.resetRequest();
}
