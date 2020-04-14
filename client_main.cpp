#include <iostream>
#include "client.hpp"

int main(int argc, char** argv) {
  Client client("127.0.0.1", strtol(argv[1], NULL, 10));
  while (true) {
    client.Send();
  }
}