#ifndef INC_1C_ADMISSION_MAYBE_HPP
#define INC_1C_ADMISSION_MAYBE_HPP


// Inspired by https://youtu.be/PH4WBuE1BHI (basic idea)
// and https://gitlab.com/Lipovsky/tiny-support (Failure trick)

#include <system_error>

template <class T>
class Maybe {
public:
  static_assert(!std::is_reference<T>::value, "Do not use reference types");

  Maybe() : ok(true) {} // By default we think that our value is not an error
  explicit Maybe(const T& rhs) : ok(true), expected_(rhs) {}
  explicit Maybe(T&& rhs) : ok(true), expected_(std::move(rhs)) {}

  template <class... Args>
  explicit Maybe(Args&&... args) : ok(true), expected_(std::forward<Args>(args)...) {}

  explicit Maybe(std::error_code ec) : ok(false), ec_(ec) {}

  Maybe(Maybe&& m) noexcept(std::is_nothrow_move_constructible<T>::value);
  Maybe& operator=(Maybe&& m) noexcept(std::is_nothrow_move_constructible<T>::value);
  Maybe(const Maybe& m);
  Maybe& operator=(const Maybe& m);

  T& value() & { return expected_; }
  T&& value() && { return std::move(expected_); }
  const T& value() const& { return expected_; }
  const T&& value() const&& { return std::move(expected_); }

  [[nodiscard]] std::error_code error() const { return ec_; }


  [[nodiscard]] bool HasError() const { return !ok; }

  [[nodiscard]] bool HasValue() const { return ok; }

  ~Maybe() = default;

private:
  bool ok;
  union {
    T expected_;
    std::error_code ec_;
  };
};

template <>
class Maybe<void> {
public:
  Maybe() = default;
  explicit Maybe(std::error_code ec) : ec_(ec) {}
  bool HasError();
  [[nodiscard]] std::error_code error() const;

private:
  std::error_code ec_;
};

class Failure {
public:
  explicit Failure(std::error_code& ec) : ec_(ec) {}

  Failure(const Failure&) = delete;
  Failure& operator=(const Failure&) = delete;
  Failure(Failure&&) = delete;
  Failure&operator=(Failure&&) = delete;

  template<class T>
  operator Maybe<T>() {
    return Maybe<T>(ec_);
  }

private:
  std::error_code ec_;
};

namespace make_result {

    template <typename T>
    Maybe<T> Ok(T&& value) {
      return Maybe<T>(std::move(value));
    }

    template <typename T>
    Maybe<T> Ok(T& value) {
      return Maybe<T>(value);
    }

    template <typename T>
    Maybe<T> Ok(const T& value) {
      return Maybe<T>(value);
    }


    Maybe<void> Ok();

    Failure Fail(std::error_code ec);

}


#endif //INC_1C_ADMISSION_MAYBE_HPP
