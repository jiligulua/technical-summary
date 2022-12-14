#ifndef MARS_COPY_CONTROL_HAS_PTR_H_
#define MARS_COPY_CONTROL_HAS_PTR_H_

#include <string>
using std::string;


class HasPtr {
  public:
	//HasPtr(const string & s = string())
	//  : ps(new string(s))
	//  , i(0)
	//  , use(new std::size_t(1)) {}

	HasPtr(const string & s = string())
	  : ps(new string(s))
	  , i(0) {}
	  

	~HasPtr();
	
	//HasPtr(const HasPtr & p)
	//  : ps(p.ps)
	//  , i(p.i)
	//  , use(p.use) {
	//    ++*use;
	//  }

	HasPtr(const HasPtr & p)
	  : ps(new string(*p.ps))
	  , i(p.i) {}

	//HasPtr& operator=(const HasPtr&);
	HasPtr& operator=(HasPtr);
	HasPtr& operator=(const string&);
	string& operator*();
    bool operator<(const HasPtr&) const;

  private:
    friend void swap(HasPtr&, HasPtr&);

  private:
    string* ps;
	int i;
	//std::size_t* use;
};

#endif 
