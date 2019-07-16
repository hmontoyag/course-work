
const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
//
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
//
#include "IRCServer.h"

int QueueLength = 5;

//test

int
IRCServer::open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
  
	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
			     (char *) &optval, sizeof( int ) );
	
	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			  (struct sockaddr *)&serverIPAddress,
			  sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}
	
	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

void
IRCServer::runServer(int port)
{
	int masterSocket = open_server_socket(port);

	initialize();
	
	while ( 1 ) {
		
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
					  (struct sockaddr *)&clientIPAddress,
					  (socklen_t*)&alen);
		
		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}
		
		// Process request.
		processRequest( slaveSocket );		
	}
}
std::map<std::string, std::vector<std::string> >  roomlist;
std::map<std::string, std::vector<std::string> > roomlog;
std::map<std::string, std::vector<std::string> > userlog;

int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}
	
	// Get the port from the arguments
	int port = atoi( argv[1] );

	IRCServer ircServer;

	// It will never return
	ircServer.runServer(port);
	
}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//

void
IRCServer::processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;
	
	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;
	
	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
		read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}
		
		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}
	
	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
        commandLine[ commandLineLength ] = 0;

//	printf("RECEIVED: %s\n", commandLine);

//	printf("The commandLine has the following format:\n");
//	printf("COMMAND <user> <password> <arguments>. See below.\n");
//	printf("You need to separate the commandLine into those components\n");
//	printf("For now, command, user, and password are hardwired.\n");
        
        
        char * pch;
	pch=strtok(commandLine, " ");
        
	const char * command =pch;
	pch = strtok(NULL," ");
        if(command==NULL){
	  command =" ";
	}
	const char * user =pch;
	pch = strtok(NULL," ");
        if(user==NULL){
	  const char * msg = "ERROR (Command missing)\r\n";
	  write(fd,msg,strlen(msg));
	return;
	}
	const char * password = pch;
	pch = strtok(NULL, "");
        if(password==NULL){
	  password=" ";
	}
	const char * args = pch;
	if(args==NULL){
	  args=" ";
	}
	printf("RECEIVED: %s\n", commandLine);
	printf("command=%s\n", command);
	printf("user=%s\n", user);
	printf( "password=%s\n", password );
	printf("args=%s\n", args);

	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password, args);
	}
	else if (!strcmp(command, "ENTER-ROOM")) {
		enterRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LEAVE-ROOM")) {
		leaveRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "SEND-MESSAGE")) {
		sendMessage(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-MESSAGES")) {
		getMessages(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
		getUsersInRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-ALL-USERS")) {
		getAllUsers(fd, user, password, args);
	}
	else if (!strcmp(command, "CREATE-ROOM")){
	          createRoom(fd,user,password,args);
	}
	else {
		const char * msg =  "UNKNOWN COMMAND\r\n";
		write(fd, msg, strlen(msg));
	}

	// Send OK answer
	//const char * msg =  "OK\n";
	//write(fd, msg, strlen(msg));

	close(fd);	
}
std::map<std::string,std::string>sesmap;

void
IRCServer::initialize()
{

 /*El mapa se cambia cada sesion,
					  y se mantiene, annades a el y a
					  el txt cada usuario que se agregue.
					  Key: Usuario.  Al final, mientras
					  todo se haya guardado en el txt
					  se puede borrar el map sin problema*/
   
   //Open password file
   std::ifstream userlist("password.txt");
   std::string pass_r;
   std::string user_r;
   std::string waste;

int num = 0;
	// Initialize users in room
          while(!(userlist.eof())){
	    getline(userlist, user_r);
	    if(user_r=="\r"||user_r=="\n"||user_r==" "||user_r==""){ break;}
	    getline(userlist, pass_r);
	    getline(userlist,waste);
       
	    sesmap[user_r] = pass_r;
//	    num++;
//	    printf("%d\n",num);
//	    printf("%s\n",user_r.c_str());
//	   printf("%s\n",pass_r.c_str());
	  }
	// Initalize message list
return;
}

bool
IRCServer::checkPassword(int fd, const char * user, const char * password) {
	std::string userc(user);
	std::string passc(password);
	if((sesmap.find(userc)==sesmap.end())){
	  dprintf(fd,"ERROR (Wrong password)\r\n");
	  return false;
	}
	if(sesmap[userc]==passc){
	 // dprintf(fd,"ERROR (Wrong password)\r\n");
	  return true;
	} else {
	  dprintf(fd,"ERROR (Wrong password)\r\n");
	  return false;
   }	
}

void
IRCServer::addUser(int fd, const char * user, const char * password, const char * args)
{
 	// Here add a new user. For now always return OK.
//print into file
//
  FILE * file = fopen("password.txt", "a");
        std::string user_au(user);
	std::string pass_au(password);
	
        if(!(sesmap.find(user_au)==sesmap.end())){
	  const char * msg = "ERROR (User Exists)\r\n";
	  write(fd, msg, strlen(msg));
	  return;
	}
        sesmap[user_au]=pass_au;

	const char * msg =  "OK\r\n";
	fprintf(file,"%s\r%s\n\r",user,password);
	
	write(fd, msg, strlen(msg));
     fclose(file);
	return;		
}
//
//


void
IRCServer::createRoom(int fd,const char * user, const char * password, const char * args)
{
  std::string room(args);
  if(!checkPassword(fd,user,password)){return;}
//  const char * msg = "response:\r\n";
//  write(fd,msg,strlen(msg));
       
    roomlist[room];
    roomlog[room];
    userlog[room];
const char *  msg = "OK\r\n";
  write(fd,msg,strlen(msg));
  return;
}
void
IRCServer::enterRoom(int fd, const char * user, const char * password, const char * args)
{
   std::string room(args);
   if(!checkPassword(fd,user,password)){ return; }
   if(roomlist.find(room)==roomlist.end()){
     const char * msg = "ERROR (No room)\r\n";
     write(fd,msg,strlen(msg));
     return;
   }
 //  if(!(checkPassword(fd,user,password))){
 //    dprintf(fd, "ERROR (Wrong password)\r\n");
 //   }
//   if(!checkPassword(fd,user,password)){
// return;
//   }
   int found = 0;
   int i;
   std::string usere(user);
   for(i=0;i<roomlist[room].size();i++){
     if(roomlist[room][i]==usere){
       found = 1;
     }
   }
   if(found == 1){
   }
   if(found == 0){
   roomlist[room].push_back(usere);
   }
   const char * msg = "OK\r\n";
   write(fd,msg,strlen(msg));


}

void
IRCServer::leaveRoom(int fd, const char * user, const char * password, const char * args)
{
std::string userl(user);
std::string pass(password);
std::string room(args);
if(!checkPassword(fd,user,password)){
  return;
}
int i;
int found = 0;
int at;
for(i=0;i<roomlist[room].size();i++){
  if(roomlist[room][i]==userl){
    found = 1;
    at = i;
   }
}
  if(found == 0){
    const char * msg = "ERROR (No user in room)\r\n";
    write(fd,msg,strlen(msg));
    return;
  }

  if(found == 1){
    roomlist[room].erase(roomlist[room].begin() + at);
    const char * msg = "OK\r\n";
    write(fd,msg,strlen(msg));
  }
}



void
IRCServer::sendMessage(int fd, const char * user, const char * password, const char * args)
{
std::string userr(user);
std::string pass(password);
if(!checkPassword(fd,user,password)){
  return;
}
//parse args into room and message
char * par;
char *arg = strdup(args);
par = strtok(arg," ");
std::string room(par);
//const char * one = room.c_str();
//write(fd,one,strlen(one));
par = strtok(NULL,"\n");
std::string message;
if (par!=NULL){ 
std::string mm(par);
message =mm;
}
if(par==NULL){
std::string mm = "";
message = mm;
}


//const char * two = message.c_str();
//write(fd,two,strlen(two));
//LOOK for user in room
int found = 0;
int i;
for(i=0;i<roomlist[room].size();i++){
  if(roomlist[room][i]==userr){
    found = 1;
   }
}
  if(found==0){
    dprintf(fd,"ERROR (user not in room)\r\n");
    return; 
   }
  if(found == 1){
    roomlog[room].push_back(message);
    userlog[room].push_back(userr);
  



const char * msg = "OK\r\n";
write(fd,msg,strlen(msg));
return;}
}

void
IRCServer::getMessages(int fd, const char * user, const char * password, const char * args)
{
std::string userr(user);
std::string pass(password);
if(!checkPassword(fd,user,password)){
  return;
}
//parse
char * par;
char * arg = strdup(args);
par = strtok(arg," ");
std::string num(par);
//const char * n = num.c_str();
//write(fd,n,strlen(n));
int numb = atoi(num.c_str());
par = strtok(NULL, "\r\n");
std::string room(par);
//const char * r = room.c_str();
//write(fd,r,strlen(r));
//CHECK for room
int found = 0, i;
for(i=0;i<roomlist[room].size();i++){
  if(roomlist[room][i]==userr){
     found = 1;
  }
}
  if(found == 0){
    dprintf(fd,"ERROR (User not in room)\r\n");
    return;
  }
  if(found==1){
  std::list<std::string> auxl;
  std::list<std::string> useraux;
  int logsize = roomlog[room].size();
  int count = numb;
    for(i=numb+1; i<logsize;i++){
      std::string mes = roomlog[room].back();
      roomlog[room].pop_back();
      auxl.push_back(mes);
      
      //dprintf(fd,"%d ", j);
      std::string us = userlog[room].back();
      userlog[room].pop_back();
      useraux.push_back(us);
      //const char * u = us.c_str();
      //write(fd,u,strlen(u));
      //dprintf(fd," ");
      //const char * m = mes.c_str();
      //write(fd,m,strlen(m));
      //dprintf(fd,"\r\n");
      
    
    }
    if(auxl.empty()){
      dprintf(fd,"NO-NEW-MESSAGES\r\n");
      return;
    }
    for(i=numb+1;i<logsize;i++){
      std::string mes = auxl.back();
      auxl.pop_back();
    
      roomlog[room].push_back(mes);

      std::string us = useraux.back();
      useraux.pop_back();

      userlog[room].push_back(us);
      const char * u = us.c_str();
      dprintf(fd,"%d ", count+1);
      count++;
      write(fd,u,strlen(u));
      dprintf(fd," ");
      const char * m = mes.c_str();
      write(fd,m,strlen(m));
      dprintf(fd,"\r\n");

    }
  }
  dprintf(fd,"\r\n");
  return;
}

void
IRCServer::getUsersInRoom(int fd, const char * user, const char * password, const char * args)
{
std::string userg(user);
std::string passg(password);
std::string room(args);
if(!checkPassword(fd,user,password)){
  return;
}
std::string us;
std::list<std::string> auxlist;
std::vector<std::string> aux;
int i;
int r = roomlist[room].size();
  for(i =0;i<r;i++){
    us = roomlist[room].back(); 
    roomlist[room].pop_back();
    auxlist.push_back(us);
    aux.push_back(us);
  }
  std::string who;
  auxlist.sort();
  for(i=0;i<r;i++){
    us = aux.back();
    aux.pop_back();
    roomlist[room].push_back(us);
    who = auxlist.front();
    auxlist.pop_front();
    const char * msg = who.c_str();
    write(fd,msg,strlen(msg));
    const char * uu = "\r\n";
    write(fd,uu,strlen(uu));
  }
  const char * l = "\r\n";
  write(fd,l,strlen(l));
  
}
void
IRCServer::getAllUsers(int fd, const char * user, const char * password,const  char * args)
{
    std::string userg(user);
    std::string passg(password);

    if(!checkPassword(fd,user,password)){
      
      return;
    }

     int size = sesmap.size();
     std::list<std::string> lou;
     for(std::map<std::string,std::string>::iterator it = sesmap.begin();it!=sesmap.end();++it){
       lou.push_back(it->first);
     }
     lou.sort();
     std::list<std::string>::iterator pp;
     const char * res = "response:\r\n";
     for(pp=lou.begin();pp!=lou.end();++pp){
       std::string p = *pp;
       const char * msg = p.c_str();
       write(fd,msg,strlen(msg));
       const char * n = "\r\n";
       write(fd,n,strlen(n));
      
      }
    res = "\r\n";
    write(fd,res,strlen(res));

}

