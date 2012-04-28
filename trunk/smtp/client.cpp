#include "client.h"

#include <iostream>
#include <string.h>

Client::Client(Server& server, Socket* socket) :
        server_(server),
        socket_(socket),
	request_(parser_.getRequest()),
	writeOrder_(true),
        decoOrder_(false)
{

    this->parsingCommandMap_["HELO"] = &Client::commandHelo;
    this->parsingCommandMap_["MAIL"] = &Client::commandMail;
    this->parsingCommandMap_["RCPT"] = &Client::commandRcpt;
    this->parsingCommandMap_["DATA"] = &Client::commandData;
    this->parsingCommandMap_["QUIT"] = &Client::commandQuit;
}


void Client::read()
{
    char readBuff[readSize + 1];
    int len = this->socket_->recvSocket(readBuff, readSize);
    if (len > 0)
    {
        readBuff[len] = 0;
	std::string line(readBuff);
	std::cout << line << std::endl;
	this->parser_.parseCmd(line);
	if (this->parser_.isComplete() == true)
	  {
	    //this->request_ = &this->parser_.getRequest();
	    this->execRequest();
	  }
	// si parsing renvoi objet requete complet, execCmd
        this->writeOrder_ = true;
    }
    else
    {
      this->decoOrder_ = true;
      std::cerr << "Client Disconnection" << std::endl;
    }
}

void Client::write()
{
    const char * code = this->response_.getCode();
    const char * text = this->response_.getText();

	if (strcmp(code, "") != 0)
	{
		unsigned int codeLength = strlen(code);
		unsigned int textLength = strlen(text);
		unsigned int totalLength = textLength + codeLength + 3;
		char space = ' ';
		const char *endl = "\r\n";
		char *message = new char[totalLength + 4];

		memcpy(message, code, codeLength);
		memcpy(message + codeLength, &space, 1);
		memcpy(message + codeLength + 1 , text, textLength);
		memcpy(message + codeLength + 1 + textLength , endl, 2);
		this->socket_->sendSocket(message, totalLength);
		this->writeOrder_ = false;
		delete message;
		if (strcmp(code, "221") == 0)
			this->socket_->close();
	}
    this->response_.resetResponse();
}

bool Client::getWriteOrder() const
{
    return this->writeOrder_;
}

void Client::setWriteOrder(bool b)
{
    this->writeOrder_ = b;
}

void Client::execRequest()
{
    if (this->parsingCommandMap_.find(this->request_.getCmd()) != this->parsingCommandMap_.end())
        (this->*(this->parsingCommandMap_[this->request_.getCmd()]))(this->request_.getArgs());
    else
      this->commandError();
}

bool Client::getDecoOrder() const
{
return this->decoOrder_;
}

Client::~Client()
{
    delete this->socket_;
}
