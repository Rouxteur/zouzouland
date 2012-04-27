CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= main.cpp server.cpp client.cpp client_cmd.cpp parser.cpp request.cpp response.cpp Socket/SocketUnix.cpp mail.cpp user.cpp userlist.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mendoza

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f *~
	rm -f \#*\#

fclean:	clean
	rm -f $(EXECUTABLE)

re:	fclean all