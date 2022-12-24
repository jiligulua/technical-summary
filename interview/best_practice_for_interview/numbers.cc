#include <set>
#include <iostream>
#include <vector>

bool find_number(int pre, int index, const std::size_t size, std::set<int>& remain);
void find_number(void) {
  std::set<int> s;
  for (int i = 1; i < 10; ++i)
	s.insert(i);

  const std::size_t size = 9;
  for (int i = 1; i < 10; ++i) {
	s.erase(i);
    if (find_number(i, 2, size, s))
	  break;
	else
	  s.insert(i);
  }
}

bool find_number(int pre, int index, const std::size_t size, std::set<int>& remain) {
  if (index == size) {
    auto number = pre * 10 + *remain.begin();
	if (0 == number % index) {
	  std::cout << "Find number is " << number << std::endl;
	  return true;
	} else {
	  return false;
	}
  } else {
    for (auto i : remain) {
	  auto number = pre*10 + i;
	  if (0 == number % index) {
	    remain.erase(i);
		if (find_number(number, index+1, size, remain)) {
		  return true;
		} else {
		  remain.insert(i);
		  continue;
		}
	  }
	}
	return false;
  }
}

//
// 优化：
// 1. 用bool[]数组替代vector，提升性能，直接使用bool数组来标识是否使用该数；
// 2. 使用vector<int>来保存数字序列；
// 3. 上述办法只是获取了一个数据，并没有获得所有的数据，还可以改进；
// 4. 可有可无，可以从0或1开始，但是使用0开始，更加程序化；
// 
// 优化之后的代码，代码行更少，更加精简，更加纯粹，意味着出错更少
// 一般来讲，递归调用有两个函数，一个初始化数据，一个处理数据；
// 
void find_number(int, int, std::vector<int>&, bool*); 
std::vector<int> find_number_ex(void) {
  std::vector<int> ivec;
  bool used[10];
  int index = 1;
  find_number(0, 0, ivec, used);
  return ivec;
}

void find_number(int number, int index, std::vector<int>& ivec, bool* used) {
  if (number != 0 && 
	  number % index != 0) {
    return;
  }

  if (9 == index) {
    ivec.push_back(number);
	return;
  }
 
  // 这种写法，减少了if-else的嵌套
  for (int i = 1; i < 10; ++i) {
    if (!used[i]) {
	  used[i] = true;
	  find_number(number*10+i, index+1, ivec, used);
	  used[i] = false;
	}
  }
}

int main(int argc, char* argv[]) {
  find_number();
  auto numbers = find_number_ex();
  for (auto num : numbers)
	std::cout << num << std::endl;
}
