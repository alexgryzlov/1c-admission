#ifndef INC_1C_ADMISSION_SERVER_HPP
#define INC_1C_ADMISSION_SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <cstdlib>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cinttypes>
#include <csignal>
#include <cerrno>
#include <climits>
#include <fcntl.h>
#include <cstring>
#include <thread>

#include "maybe.hpp"
#include "error.hpp"
#include "storage.hpp"

class Server {
public:
  Server();
  ~Server();
  Maybe<void> initialize(size_t portno);
  Maybe<void> run();
  Maybe<int> acceptClient();
  // We will have two types of messages.
  // Client can do only 2 actions:
  //    - Add message
  //    - Request one's message history
  // If client wants to add a message than it should begin with '+'
  // If client wants to request history than is should begin with '?#', where # stands for client number,
  // or empty space if he wants his own history.
  Maybe<void> clientSession(int client);


private:
  int current_id;
  int server_fd;
  Storage storage;
};

#endif //INC_1C_ADMISSION_SERVER_HPP
