#ifndef SEDNA_SHARED_PTR_H_
#define SEDNA_SHARED_PTR_H_

#include <functional>
#include "debug_delete.h"

using std::function;

namespace yh {

template <typename T> class SharedPtr;

class SharedPtrControlBlock {
  template <typename T> friend class SharedPtr;
  SharedPtrControlBlock() : count_(1) {}
  int count_;
};


template <typename T>
class SharedPtr {
 public:
  explicit SharedPtr(T *ptr = nullptr, function<void(T*)> deleter = DebugDelete()) 
      : ptr_(ptr)
      , deleter_(deleter)
	  ,	control_block_(ptr_ != nullptr ? new SharedPtrControlBlock : nullptr) {}

  SharedPtr(const SharedPtr &rhs) {
    if (nullptr != rhs.control_block_) {
	  addRef();
	  ptr_ = rhs.ptr_;
	  deleter_ = rhs.deleter_;
	  control_block_ = rhs.control_block_;
	}		  
  }
    
  ~SharedPtr() {
      
  }

  SharedPtr& operator=(const SharedPtr &rhs) {
    if (ptr_ != rhs.ptr_) {
	  SharedPtr temp(rhs);
	  swap(temp);
	}  
	return *this;
  }

  void addRef() {
    ++control_block_->count_;
  }

  void release() {
	if (--control_block_->count_ == 0)
	  ~SharedPtr();
  }

  T* operator->() const {
    return ptr_;
  }

  T& operator*() const {
    return *ptr_;
  }

 private:
  T* ptr_;
  SharedPtrControlBlock *control_block_;
  function<void(T*)> deleter_ { DebugDelete() };
  unsigned ref_count;
}; 

} // namespace yh

#endif // SENDA_SHARED_PTR_H_
