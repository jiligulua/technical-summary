#include "Operator.h"
#include <exception>
#include <stdexcept>

Operator::Operator(const std::string & str) : str_(str) {
  if (str_.empty())
    throw std::runtime_error("input str invalid");
}

int Operator::GetResult() {
  ParseNextNum();
  ParseNextSign();
  while (!signs_.empty() || !str_.empty()) {
	if (MeetMulDiv()) {
	  if (NextIsLeftBacket()) {
	    ParseNextNum();
		ParseNextSign();
	  } else {
	    ProcessMulDiv();
	  }
	} else if (MeetRightBacket()) {
	  ProcessUntilLeftBacket();
	} else {
	  ParseNextNum();
	  ParseNextSign();
	}
  }   
}
