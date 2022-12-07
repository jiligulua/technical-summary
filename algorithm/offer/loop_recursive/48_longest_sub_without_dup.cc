#include <iostream>
#include <string>

// 写代码和定位问题，必须对业务逻辑有很明确的信息，要理清思路和写出文字
// 一定要明确题干是什么
int LongestSubstringWithoutDuplication(const std::string& str) {
  int cur_len = 0;
  int max_len = 0;

  int *position = new int[26];
  for (int i = 0; i < 26; ++i) {
    position[i] = -1; // 表示先前没有出现过该字符
  }

  for (int i = 0; i < str.length(); ++i) {
    int pre_index = position[0];
	
	if (pre_index == -1 || i - pre_index > cur_len) {
	  ++cur_len;
	} else {
	  if (cur_len > max_len)
	    max_len = cur_len;

	  cur_len = i - pre_index;
	}
	
	position[str[i]-'a'] = i;
  }
  
  if (cur_len > max_len)
    max_len = cur_len;

  delete[] position;
  return max_len;
}

int main() {
  std::string str = "arabcacfr"; 
  std::cout << "Max length is " << LongestSubstringWithoutDuplication(str) << std::endl; 
}
