#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "socket.hh"

///////////////////////////////////////////////////////////////////////////////////////
//main
//example of a TCP client that writes and reads a message with end of message format "\r\n"
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  char buf[10];
  int recv_size;
  sprintf(buf, "12345\r\n");

  tcp_client_t client("127.0.0.1", 2000);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //create socket and open connection
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  client.open();

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //write
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  client.write(buf, strlen(buf));
  std::cout << "client sent " << strlen(buf) << " bytes: " << buf;

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //read
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  recv_size = client.read_some(buf, sizeof(buf));

  //strip extra charactes received (size is not known, detect end of message)
  std::string str(buf);
  size_t pos = str.find("\r\n");
  std::string str_message(str.substr(0, pos + 2));
  std::cout << "client received " << recv_size << " bytes: " << str_message;

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //close connection
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  client.close();

  return 0;
}