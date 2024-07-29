#ifndef BOX_H_
#define BOX_H_

#include <memory>
#include <type_traits>

// https://gist.github.com/tomoyanonymous/5f1b18d893d67f56ea0e2ab72ed142f3
template <typename T> struct Box {
  // construct from an existing object
  Box() = delete;
  Box(T rt) : t(std::make_shared<T>(std::move(rt))) {}
  template <class U>
  using enabler = std::enable_if_t<std::is_same_v<std::decay_t<U>, T>>;
  template <typename U, enabler<U>>
  Box(U &&rt) : t(std::make_shared<U>(std::forward<U>(rt))) {}
  // cast back to wrapped type
  operator T &() { return *t; }
  operator const T &() const { return *t; }

  T &getraw() const { return *t; }
  // store the value
  std::shared_ptr<T> t;
};

#endif // !BOX_H_
