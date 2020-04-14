#include "maybe.hpp"


template<class T>
Maybe<T>::Maybe(Maybe &&m) noexcept(std::is_nothrow_move_constructible<T>::value) : ok(m.ok) {
  if (m.HasValue()) {
    new (&expected_) T(std::move(m.expected_));
  } else {
    new (&ec_)  std::system_error(std::move(m.ec_));
  }
}

template<class T>
Maybe<T>& Maybe<T>::operator=(Maybe &&m) noexcept(std::is_nothrow_move_constructible<T>::value) {
  if (this == &m) {
    return *this;
  }

  if (m.HasValue()) {
    new (&expected_) T(std::move(m.expected_));
  } else {
    new (&ec_)  std::system_error(std::move(m.ec_));
  }
  ok = m.ok;

  return *this;
}

template<class T>
Maybe<T>::Maybe(const Maybe &m) : ok(m.ok) {
  if (m.HasValue()) {
    new (&expected_) T(m.expected_);
  } else {
    new (&ec_) std::system_error(m.ec_);
  }
}

template<class T>
Maybe<T>& Maybe<T>::operator=(const Maybe<T>& m) {
  if (this == &m) {
    return *this;
  }

  if (m.HasValue()) {
    new (&expected_) T(m.expected_);
  } else {
    new (&ec_) std::system_error(m.ec_);
  }
  ok = m.ok;

  return *this;
}


bool Maybe<void>::HasError() {
  return (bool)ec_;
}


[[nodiscard]] std::error_code Maybe<void>::error() const {
  return ec_;
}

namespace make_result {
    Failure Fail(std::error_code ec) {
      return Failure{ec};
    }

    Maybe<void> Ok() {
      return Maybe<void>{};
    }
}
