
#ifdef _WIN32
# include <WinSock2.h>
# include <Windows.h>
#endif

#include "Socket.h"

void	Socket::setFdReadCallback(FdCallback callback)
{
	this->read_cb = callback;
}

void	Socket::setFdWriteCallback(FdCallback callback)
{
	this->write_cb = callback;
}
