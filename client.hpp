#ifndef INC_1C_ADMISSION_CLIENT_HPP
#define INC_1C_ADMISSION_CLIENT_HPP

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
#include <iostream>

#include "maybe.hpp"
#include "error.hpp"

class Client {
public:
  Client(const std::string& ip, short port);
  Maybe<void> Send();
  Maybe<void> Get();
private:
  int client_fd;
};

#endif //INC_1C_ADMISSION_CLIENT_HPP
