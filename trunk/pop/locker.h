#ifndef LOCKER_H_
#define LOCKER_H_

#include <string>

class Locker
{
 public:
  Locker(const std::string& folder, const std::string& lockfile);
  void lock();
  void unlock();
 private:
  bool isLocked();
  void createLock();
  std::string folder_;
  std::string lock_;
};

#endif
