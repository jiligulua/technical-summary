#ifndef MARS_SINGLETON_H
#define MARS_SINGLETON_H
#include <utility>
#include <stdexcept>
// 用可变参数模板实现构造函数形参个数和类型都不同的泛型单例

template <typename T>
class Singleton {
 public:
  template <typename... Args> 
  static T* Instance(Args... args) { // 可变参数模板实现构造函数形参个数和类型地泛化
    if (nullptr == instance_)
	  instance_ = new T(std::forward<Args>(args)...); // 完美转发，避免不必要地内存复制提高性能
	
	return instance_;
  }

  static T* GetInstance(void) {
    if (nullptr == instance_) 
	  throw std::logic_error("The instance isn't initialized, please initialize the instance first.");
	
	return instance_;
  }

  static void DestroyInstance(void) {
    delete instance_;
	instance_ = nullptr;
  }

 private:
  Singleton(void);
  ~Singleton(void);
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  static T* instance_;
};

template <typename T>
T* Singleton<T>::instance_ = nullptr;

#endif //  MARS_SINGLETON_H
