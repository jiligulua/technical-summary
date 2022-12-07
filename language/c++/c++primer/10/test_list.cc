#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include "common.h"

using namespace std;

int main() {
  list<string> slist = {"I", "love", "it", "I", "love", "computer", "science"};
  Print(slist);
  slist.sort();
  slist.unique();
  Print(slist);
}


