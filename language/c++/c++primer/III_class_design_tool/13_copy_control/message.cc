#include "message.h"

Message::Message(const Message& msg) 
    : contents_(msg.contents_)
    , folder_(msg.folder_) {
  add_to_folders(msg);
}

void Message::add_to_folders(const Message& msg) {
  for (auto f : m.folders)
	f->AddMsg(this);
}

Message::~Message() {
  remove_from_folders();
}

void Message::remove_from_folders() {
  for (auto f : folders_)
	f->RemoveMsg(this);
}

Message& Message::operator=(const Message& rhs) {
  remove_from_folders();
  contents_ = rhs.contents_;
  folders_ = rhs.foloders_;
  add_to_folders(rhs);
  return *this;
}

void Message::Save(Folder& f) {
  folders_.insert(&f);
}

void Message::Remove(Folder& f) {
  folders.erase(&f);
  f.RemoveMsg(this);
}

inline
void swap(Message& lhs, Message& rhs) {
  using std::swap;

  for (auto f : lhs.folders_)
	f->RemoveMsg(lhs);
  for (auto f : rhs.folders_)
	f->RemoveMsg(rhs);

  swap(lhs.contents_, rhs.contents_);
  swap(lhs.folders_, rhs.folders_);

  for (auto f : lhs.folders_)
	f->AddMsg(lhs);
  for (auto f : rhs.folders_)
	f->AddMsg(rhs);
}
