#include <new>

class NoCopy {
public:
  NoCopy() = default;
  NoCopy(const NoCopy &) = delete;
  NoCopy& operator=(const NoCopy &) = delete;
  ~NoCopy() = default; 
};

class RawHandlerHolder : public NoCopy {
 public:
  explicit RawHandlerHolder(std::new_handler nh) : handler_(nh) {}
  ~RawHandlerHolder() { std::set_new_handler(handler_); }

 private:
  std::new_handler handler_;
};

template <typename T>
class NewHandlerSupport {
 public:
  static std::new_handler set_new_handler(std::new_handler p) noexcept;
  static void * operator new(std::size_t size); 
 
 private:
  static std::new_handler current_handler_;
};

template <typename T>
std::new_handler NewHandlerSupport<T>::set_new_handler(std::new_handler p) noexcept {
  std::new_handler old_handler = current_handler_;
  current_handler_ = p;
  return old_handler;
}

template <typename T> 
void* NewHandlerSupport<T>::operator new(std::size_t size) {
  RawHandlerHolder h(std::set_new_handler(current_handler_));
  return ::operator new (size);
}

template <typename T>
std::new_handler NewHandlerSupport<T>::current_handler_ = nullptr;
