#include <iostream>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "locker.h"

Locker::Locker(const std::string& folder, const std::string& lock) 
  : folder_(folder),
    lock_(lock)
{
  
}

void Locker::lock()
{
  while (this->isLocked())
    usleep(500);
  this->createLock();
}

void Locker::createLock()
{
  int ret = open(std::string(this->folder_ + '/' + this->lock_).c_str(), O_CREAT);
}

void Locker::unlock()
{
  unlink(std::string(this->folder_ + '/' + this->lock_).c_str());
}

bool Locker::isLocked()
{
  DIR *pdir;
  struct dirent *pent;
  bool ret = false;

  errno=0;
  pdir=opendir(this->folder_.c_str());
  if (!pdir){
    std::cerr << "opendir() failure in file locker [ERRNO:"<< errno << "]" << std::endl;
    return false;
  }
  else
    while ((pent=readdir(pdir)))
      {
	if (errno)
	  {
	    std::cerr << "readdir() failure in file locker [ERRNO:"<< errno << "]" << std::endl;
	      closedir(pdir);
	      return false;
	  }
	if (this->lock_ == std::string((pent->d_name)))
	  ret = true;
      }
  closedir(pdir);
  return ret;
}
