#ifndef PROJECT_EVENTS_H_
#define PROJECT_EVENTS_H_

#include <map>
#include <utility>

class NonCopyable {
 protected:
  NonCopyable(void) = default;
  ~NonCopyable(void) = default;
  NonCopyable(const NonCopyable&) = delete;
  NonCopyable& operator=(const NonCopyable&) = delete;
};


template <typename Func>
class Events : NonCopyable {
 public:
  Events(void) {}
  ~Events(void) {}

  // 注册观察者，支持右值引用
  int Connect(Func&& f) {
    return Assign(f);
  }

  // 注册观察者
  int Connect(const Func& f) {
    return Assign(f);
  }

  // 移除观察者
  void Disconnect(int key) {
    connections_.erase(key);
  }

  template <typename... Args>
  void Notify(Args&&... args) {
    for (auto& it : connections_) {
	  it.second(std::forward<Args>(args)...);
	}
  }

 private:
  // 保存观察者并分配观察者的编号
  template <typename F> 
  int Assign(F&& f) {
    int k = observer_id_++;
    connections_.emplace(k, std::forward<F>(f));
	return k;	
  }

  int observer_id_ = 0;
  std::map<int, Func> connections_;
};

#endif // PROJECT_EVENTS_H_
