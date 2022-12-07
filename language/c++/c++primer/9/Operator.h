#ifndef MARS_OPERATOR_H_
#define MARS_OPERATOR_H_

#include <string>
#include <stack>

class Operator {
  private:
	const std::string oper_flag_ {"+-*%()"};
	std::string str_;
	std::stack<int> nums_;
	std::stack<char> signs_;

  public:
	Operator(const std::string& str);
	int GetResult();

  private:
    int GetOperateResult(char c, int left, int right);
	void ParseNextNum();
	void ParseNextSign();
	bool MeetRightBacket();
	bool MeetMulDiv();
	void ProecessMulDiv();
	void ProcessUntilLeftBacket();
};

#endif // MARS_OPERATOR_H_
