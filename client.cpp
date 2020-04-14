#include "client.hpp"

Client::Client(const std::string &ip, short port) {
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  uint32_t ip_addr;
  inet_pton(AF_INET, ip.c_str(), &ip_addr);
  const struct sockaddr_in serv_addr = {AF_INET, htons(port), ip_addr};
  connect(client_fd, (sockaddr*)&serv_addr, sizeof(serv_addr));
}

Maybe<void> Client::Send() {
  std::string data;
  std::cin >> data;
  int write_res = write(client_fd, data.c_str(), data.size());
  if (data[0] == '+') {
    if (write_res == -1) {
      return make_result::Fail(WRITE_ERROR);
    }
  }
  if (data[0] == '?') {
    Get();
  }
  return make_result::Ok();
}

Maybe<void> Client::Get() {
  char buffer[4096];
  while (read(client_fd, buffer, sizeof(buffer)) > 0) {
    if (buffer[0] == '&') {
      break;
    }
    std::cout << std::string(buffer) << std::endl;
  }
}

