#include <iostream>
#include "server.h"

Server::Server() :
        pollTable_(new ABSPOLLTABLE[maxClient])

{
    this->serverSocket_ = new ABSSOCKET(port);
    this->serverSocket_->bindSocket();
    this->serverSocket_->listenSocket();
}


Server::~Server()
{
    delete [] this->pollTable_;
}



void		Server::buildPoll()
{
    this->iPoll_ = 0;

    int events = 0;
    events = events | POLLIN;
    this->pollTable_[this->iPoll_].fd = this->serverSocket_->getSocket();
    this->pollTable_[this->iPoll_].events = events;
    ++this->iPoll_;

    std::map<int, Client *>::iterator it = this->clientMap_.begin();
    while (it != this->clientMap_.end() && this->iPoll_ < maxClient)
    {
        if (!it->second->getDecoOrder())
        {
            int events = 0;
            events = events | POLLIN;
            if (it->second->getWriteOrder())
                events = events | POLLOUT;
            this->pollTable_[this->iPoll_].fd = it->first;
            this->pollTable_[this->iPoll_].events = events;
            ++this->iPoll_;
            it++;
        }
        else
        {
            delete it->second;
            this->clientMap_.erase(it++);
        }
    }

}

void		Server::unbuildPoll()
{
    for (int i = 0; i < this->iPoll_; i++)
    {

        if (this->pollTable_[i].revents & (POLLERR | POLLNVAL | POLLHUP))
        {
            std::map<int, Client *>::iterator itFind = this->clientMap_.find(this->pollTable_[i].fd);
            if (itFind != this->clientMap_.end())
            {
                delete itFind->second;
                this->clientMap_.erase(itFind);
            }
        }
        else
        {
            if (this->pollTable_[i].revents & (POLLIN))
            {
                std::map<int, Client *>::iterator itFind = this->clientMap_.find(this->pollTable_[i].fd);
                if (itFind != this->clientMap_.end())
                {
                    itFind->second->read();
                }
                else
                {
                    Socket * clientSocket = this->serverSocket_->acceptSocket();
                    Client *newClient = new Client(*this, clientSocket);
                    this->clientMap_[clientSocket->getSocket()] = newClient;
                }
            }
            if (this->pollTable_[i].revents & (POLLOUT))
            {
                std::map<int, Client *>::iterator itFind = this->clientMap_.find(this->pollTable_[i].fd);
                if (itFind != this->clientMap_.end())
                    itFind->second->write();
            }

        }
    }

}

void		Server::watchPoll()
{
	std::cout << "bip" << std::endl;
    if (ABSPOLL(this->pollTable_, this->iPoll_, -1) < 0)
        std::cerr << "poll err" << std::endl;
}

void		Server::run()
{
    while (true)
    {
        this->buildPoll();
        this->watchPoll();
        this->unbuildPoll();
    }
}

UserList	&Server::getUserList()
{
  return this->userlist_;
}


