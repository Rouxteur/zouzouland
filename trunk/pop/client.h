#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include "parser.h"
#include "user.h"
#include "response.h"
#include "request.h"
#include "Socket/Socket.h"
#include "dirent.h"
#include <sstream>
class Server;



const int readSize = 4096;

class Client
{
    typedef void (Client::*pmethod)(const std::string &);

public:
    Client(Server & , Socket *);
    ~Client();
    void	read();
    void	write();
    bool	getWriteOrder() const;
    void	setWriteOrder(bool);
    void	execRequest();
    void	commandApop(const std::string &);
    void	commandRetr(const std::string &);
    void	commandStat(const std::string &);
    void	commandList(const std::string &);
	void	commandDele(const std::string &);
    void	commandQuit(const std::string &);
    void	commandError();
    bool	getDecoOrder() const;
    std::string MailsInfo(const std::string &);
private:
    Server	&server_;
    Socket	*socket_;
    Parser	parser_;
    User	*user_;
    Response	response_;
    Request	&request_;
    bool	writeOrder_;
    bool	decoOrder_;
    std::map<std::string, pmethod> parsingCommandMap_;

};

#endif // CLIENT_H
