#ifndef LIB_SOCKET_H
#define LIB_SOCKET_H

#include <string>
#include <jansson.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////
//socket_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class socket_t
{
public:
  socket_t() : m_socket(-1)
  {
  };
  socket_t(int socket) : m_socket(socket)
  {
  };
  ~socket_t()
  {
  };

  void close();
  void write(const void *buf, int size_buf);
  int read_some(void *buf, int size_buf);
  int read_all(const char *file_name, bool verbose);
  std::string read_all(size_t size_read);
  int hostname_to_ip(const char *host_name, char *ip);

  //JSON functions
  size_t write(json_t *json);
  json_t * read();

protected:
  int m_socket; // socket descriptor 
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//tcp_server_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class tcp_server_t : public socket_t
{
public:
  tcp_server_t(const unsigned short server_port);
  socket_t accept_client();
  ~tcp_server_t();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//tcp_client_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class tcp_client_t : public socket_t
{
public:
  tcp_client_t(const char *host_name, const unsigned short server_port);
  ~tcp_client_t();
  void open();

protected:
  std::string m_server_ip;
  unsigned short m_server_port;
};

#endif