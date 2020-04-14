#include "server.hpp"
#include <iostream>
#include <string>

Maybe<void> Server::initialize(size_t portno) {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    return make_result::Fail(SOCKET_ERROR);
  }

  uint32_t ip_addr;
  inet_pton(AF_INET, "127.0.0.1", &ip_addr);
  auto port = htons(portno);
  const struct sockaddr_in addr = {AF_INET, port, ip_addr};

  auto bind_res = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
  if (bind_res == -1) {
    return make_result::Fail(BIND_ERROR);
  }

  auto listen_res = listen(fd, SOMAXCONN);
  if (listen_res == -1) {
    return make_result::Fail(LISTEN_ERROR);
  }
  server_fd = fd;
  return make_result::Ok();
}

Maybe<void> Server::run() {
  while(true) {
    auto client_fd = acceptClient();
    if (client_fd.HasValue()) {
      std::thread(&Server::clientSession, this, client_fd.value()).detach();
    }
  }
}

Maybe<int> Server::acceptClient() {
  int client_fd = accept(server_fd, NULL, NULL);
  if (client_fd == -1) {
    return make_result::Fail(ACCEPT_ERROR);
  }
  return make_result::Ok(client_fd);
}


Server::~Server() {
  close(server_fd);
}



Maybe<void> Server::clientSession(int client) {
  int client_id = current_id++;
  while (true) {
    char buffer[4096] = {0};
    auto res = read(client, buffer, sizeof(buffer));
    std::cout << std::string(buffer) << std::endl;
    if (res <=  0) {
      shutdown(client, SHUT_RDWR);
    }

    size_t buffer_size = strlen(buffer);

    auto get_history = [&client](char* buffer, size_t line_size){
      write(client, buffer, line_size);
    };

    if (buffer[0] == '+') {
      storage.AddLine(client_id, buffer, buffer_size);
    }
    else {
      if (buffer_size > 1) {
        storage.LookUp((buffer[1] - '0'), get_history);
        write(client, "&", 1);
      } else {
        storage.LookUp(client_id, get_history);
      }
    }
  }
}

Server::Server() : current_id(1) {}
