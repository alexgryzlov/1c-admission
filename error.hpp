#ifndef INC_1C_ADMISSION_ERROR_HPP
#define INC_1C_ADMISSION_ERROR_HPP

#include <system_error>


enum ErrorCode : int {
  BIND_ERROR = 1,
  LISTEN_ERROR,
  SOCKET_ERROR,
  ACCEPT_ERROR,
  WRITE_ERROR
};
template <>
struct std::is_error_code_enum<ErrorCode > : true_type {};

std::error_code make_error_code(ErrorCode);

#endif //INC_1C_ADMISSION_ERROR_HPP
