#ifndef INC_1C_ADMISSION_STORAGE_HPP
#define INC_1C_ADMISSION_STORAGE_HPP

#include "maybe.hpp"
#include "error.hpp"

#include <cstring>
#include <mutex>
#include <functional>

class Storage {
public:
  Storage();
  ~Storage();
  Maybe<void> AddLine(size_t client_id, char* buffer, size_t buffer_size);
  Maybe<void> LookUp(size_t id, const std::function<void(char*, size_t)>& op);

private:
  std::mutex add_mutex;
  FILE* storage_ptr;
};


#endif //INC_1C_ADMISSION_STORAGE_HPP
