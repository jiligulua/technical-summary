#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main() {
  string c;
  vector<string> vi;
  while(cin >> c) 
    vi.push_back(c);
   

  cout << endl;
  for (auto item : vi)
    cout << item << " ";
  cout << endl;

  return 1;
}
