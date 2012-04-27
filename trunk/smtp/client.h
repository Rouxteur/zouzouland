#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include "parser.h"
#include "mail.h"
#include "response.h"
#include "request.h"
#include "Socket/Socket.h"

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
    void	commandHelo(const std::string &);
    void	commandMail(const std::string &);
    void	commandRcpt(const std::string &);
    void	commandData(const std::string &);
    void	commandQuit(const std::string &);
    void	commandError();
    bool	getDecoOrder() const;
private:
    Server	&server_;
    Socket	*socket_;
    Parser	parser_;
    Mail	mail_;
    Response	response_;
    Request	&request_;
    bool	writeOrder_;
    bool	decoOrder_;
    std::map<std::string, pmethod> parsingCommandMap_;

};

#endif // CLIENT_H
