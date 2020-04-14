#include "storage.hpp"
#include <iostream>


Storage::Storage() {}

Storage::~Storage() {
  fclose(storage_ptr);
}

Maybe<void> Storage::LookUp(size_t id, const std::function<void(char*, size_t)>& op) {
  storage_ptr = fopen("messages.txt", "r");
  size_t buffer_size = 4096;
  std::cout << "IM HRE\n";
  char* buffer = static_cast<char *>(malloc(buffer_size));
  while (getline(&buffer, &buffer_size, storage_ptr) != -1) {
    size_t line_size = strlen(buffer);
    if (buffer[0] - '0' == id) {
      op(buffer, line_size);
    }
  }
  free(buffer);
  fclose(storage_ptr);
  return make_result::Ok();
}

Maybe<void> Storage::AddLine(size_t client_id, char *buffer, size_t buffer_size) {
  std::lock_guard<std::mutex> guard(add_mutex);
  storage_ptr = fopen("messages.txt", "a+");
  fprintf(storage_ptr, "%zu ", client_id);
  auto write_res = fwrite(buffer, 1, buffer_size, storage_ptr);
  fprintf(storage_ptr, "\n");
  if (write_res == -1) {
    return make_result::Fail(WRITE_ERROR);
  }
  fclose(storage_ptr);
  return make_result::Ok();
}