#include <iostream>
#include "maybe.hpp"
#include "error.hpp"

#include "server.hpp"

int main(int argc, char** argv) {

  size_t portno;
  std::cin >> portno;

  Server server;
  server.initialize(portno);
  server.run();


  return 0;
}