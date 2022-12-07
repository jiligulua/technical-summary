#ifndef BLOB_H_
#define BLOB_H_

#include <vector>
#include <string>
#include <memory>
#include <initializer_list>

using std::vector;
using std::string;

// 前置声明，在Blob中声明友元所需要的
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);


template <typename T>
class Blob {
 public:
  // 用每个实例化Blob的实参类型同样实例化BlobPtr，需要前置声明
  friend class BlobPtr<T>;
  // 所有实例是Blob的友元，该情况不用前置声明
  template <typename X> friend class BlobPtr2;

  // BlobPtr3是非模板类，它是所有Blob实例的友元，不用前置声明
  friend class BlobPtr3;
  // 应该可以将Blob<T>中的<T>去掉，因为在Blob的类作用域内
  //friend bool operator==<T>(const Blob&, const Blob&); 
  friend bool operator==<T>(const Blob<T>&, const Blob<T>&);

  // 还可将访问权限授予模板自己的类型参数，就是将自己的类型参数成为友元
  // 这样就可以用内置类型T来实例化Blob啦
  friend T;

  typedef T value_type;
  typedef typename vector<T>::size_type size_type;

  Blob() {}
  template <typename It>
  Blob(It b, It e);
  Blob(std::initializer_list<T> il) {}

  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }

  void push_back(const T &t) { data->push_back(t); }
  void push_back(T &&t) { data->push_back(std::move(t)); }
  void pop_back();

  T& back();
  const T& back() const;
  
  T& operator[](size_type i);
  const T& operator[](size_type i) const;

 private:
  std::shared_ptr<vector<T>> data;
  void check(size_type i, const string &msg) const;  
}; 

template <typename T>
template <typename It>
Blob<T>::Blob(It b, It e)
  : data(std::make_shared<vector<string>>(b, e)) {}

template <typename T>
void Blob<T>::check(size_type i, const string &msg) const
{
  if (i >= data->size())
    throw std::out_of_range(msg);
}

template <typename T>
void Blob<T>::pop_back()
{
  check(0, "pop_back on empty Blob");
  data->pop_back();
}

template <typename T>
T& Blob<T>::back()
{
  check(0, "back on empty Blob");
  return data->back();
}

template <typename T>
const T& Blob<T>::back() const 
{
  check(0, "back on empty Blob");
  return data->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i)
{
  check(0, "subscribe out of range");
  return (*data)[i];
}

template <typename T>
const T& Blob<T>::operator[](size_type i) const
{
  check(0, "subscribe out of range");
  return (*data)[i];
}

#endif // BLOB_H_
