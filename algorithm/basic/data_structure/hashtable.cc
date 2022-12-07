#include <new>
#include <cstdlib>

template <typename T>
class HashTable {
 private:
  int max_size_;
  int count_;
  T* elements_;

 public:
  HashTable(int size) {
    max_size_ = size;
	count_ = 0;
	elements_ = new (std::nothrow) T[size];
	if (elements_ == nullptr)
	  exit(1);
	for (int i = 0; i < size; ++i)
	  elements_[i] = nullptr;
  }

  ~HashTable() {
    delete[] elements_; 
  }

  int Hash(T value);
  int SearchHash(T value);
 
 private:
  int GetPrime();
};

template <typename T>
int HashTable<T>::GetPrime() {
  return max_size_;
}

template <typename T>
int HashTable<T>::Hash(T value) {
  return value % GetPrime();
}

template <typename T>
int HashTable<T>::SearchHash(T value) {
  int index = Hash(value);
  if (elements_[index] == value) {
    return index;
  } 
  
  int re_index = (index+1) % max_size_;
  while (re_index != index) {
	if (elements_[re_index] == nullptr) 
	  break;

    if (elements_[re_index] == value) 
	  return re_index;

	re_index = (re_index+1) % max_size_;
  }

  if (re_index == index) {
	return -1;
  } else {
    elements_[re_index] = value;
	return re_index;
  }
}
