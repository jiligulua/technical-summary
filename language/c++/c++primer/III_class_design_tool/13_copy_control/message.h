#ifndef MARS_COPY_CONTROL_MESSAGE_H_
#define MARS_COPY_CONTROL_MESSAGE_H_

#include <string>
#include <set>

using std::string;
using std::set;

class Folder;

class Message {
  friend class Folder;
  friend void swap(Message& lhs, Message& rhs);

 public:
  explicit Message(const string& str = "") : contents_(str) {}

  Message(const Message& msg);
  Message& operator=(const Message&);
  ~Message();

  void Save(Folder&);
  void Remove(Folder&);

 private:
  // 拷贝构造函数、拷贝赋值运算符和析构函数所使用的工具函数
  // 将本Message添加到指向参数的Folder中
  void add_to_folders(const Message&);

  // 从folders中的每个Folder中删除本Message
  void remove_from_folder();

  string contents_;
  set<Folder*> folders_;

};

#endif // MARS_COPY_CONTROL_MESSAGE_H_
