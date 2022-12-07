#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <exception>

using std::stack;
using std::string;
using std::cout;
using std::endl;

const string flags("+-*/()");

int Operator(const char op, stack<int> &s);

void Operator(stack<char>& signs, stack<int>& num) {
  int result = Operator(signs.top(), num);
  signs.pop();
  num.push(result);
}

int Operator(const char op, stack<int> &s) {
  int left = s.top();
  s.pop();

  int right = s.top();
  s.pop();

  int result = 0;

  switch(op) {
	case '+':
	  result = left + right;
	  break;
	case '-':
	  result = left - right;
	  break;
	case '*':
	  result = left * right;
	  break;
	case '/':
	  result = left / right;
	  break;
   default:
	  // 好像这里应该写些东西，忘了，下次补上;
	  result = 0;
  }
  return result;
}

void PushNextOperationIdentify(const string& str, stack<char>& s, size_t& next_pos) {
  string::size_type pos = 0;
  pos = str.find_first_of(flags, next_pos);
  while (pos == next_pos) {
    s.push(str.at(pos));
    ++next_pos;
    pos = str.find_first_of(flags, next_pos);
  }
}

void CalculateBacketContent(stack<int> &s_num, stack<char>& s_op) {
   if (s_op.top() == ')')
	 s_op.pop();

   stack<char> s_tmp_op;
   stack<int> s_tmp_num;
   while (!s_num.empty()) {
     s_tmp_num.push(s_num.top());
	 s_num.pop();
   }

   while (!s_op.empty() && s_op.top() != '(') {
     s_tmp_op.push(s_op.top());
	 s_op.pop();
   }
   if (!s_op.empty() && s_op.top() == '(') {
     s_op.pop();
   }

   int result = 0;
   while(!s_tmp_op.empty()) 
     Operator(s_tmp_op, s_tmp_num);

   s_num.push(s_tmp_num.top());
}

int GetResult(string str) {
  if (str.empty())
    return 0;

  std::size_t next_pos = 0;
  stack<int> st_nums;
  stack<char> st_signs;
  do {
    try {
	  str = str.substr(next_pos);
	  next_pos = 0;
	  int num = stoi(str, &next_pos);
	  st_nums.push(num);

	  if (!st_signs.empty() && (st_signs.top() == '*' || st_signs.top() == '/'))
	    Operator(st_signs, st_nums); 

      str = str.substr(next_pos);
	  next_pos = 0;

	  if (str.empty()) {
	    CalculateBacketContent(st_nums, st_signs);
	  } else {
	    PushNextOperationIdentify(str, st_signs, next_pos);
	    if (st_signs.top() != ')' && !str.empty()) {
	      continue;
	    } else {
	      CalculateBacketContent(st_nums, st_signs);	
	    }
	  }
	} catch (const std::invalid_argument& ex) {
	  PushNextOperationIdentify(str, st_signs, next_pos);
	} catch (const std::out_of_range& ex) {
	  cout << "std::out_of_range" << ex.what() << endl;
	  throw std::runtime_error("invalid string expression");
	}
  } while(!st_signs.empty());


  return st_nums.top();
}

int main() {
  try {
    //string str("13-(41+12*118-1)*2+4");
    //string str("10-2*5+4");
    string str;
	while (std::cin >> str) 
      cout << str << "=" << GetResult(str) << endl;;
  } catch (const std::exception& ex) {
	cout << "Exception: " << ex.what() << endl;
  }
}
