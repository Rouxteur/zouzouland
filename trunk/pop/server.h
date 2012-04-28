#ifndef SERVER_H
#define SERVER_H

#include <map>

# ifdef _WIN32
#  include <winsock2.h>
#  include <windows.h>
#  define ABSPOLL WSAPoll
#  define ABSPOLLTABLE WSAPOLLFD
# else
#  include <poll.h>
#  define ABSPOLL poll
#  define ABSPOLLTABLE struct pollfd
# endif // _WIN32

const int maxClient = 1024;
const int port = 10112;

#include "client.h"
#include "userlist.h"
#include "Socket/Socket.h"

class Client;

class Server
{
public:
    Server();
    ~Server();
    void			buildPoll();
    void			unbuildPoll();
    void			watchPoll();
    void			run();
    UserList			&getUserList();

private:
   Socket *serverSocket_;
    std::map<int, Client *>	clientMap_;
    UserList			userlist_;
    ABSPOLLTABLE		*pollTable_;
    int				iPoll_;
};

#endif // SERVER_H
