#include <set>
#include <map>
#include <iostream>
#include <string>
#include <unordered_set>


int main() {
  using namespace std;
   
  unordered_set<int> single;
  int num;

  cout << "Input: ";
  while (cin >> num) {
    single.insert(num); 
  }
  cout << endl;

  

  cout << "Output: ";
  for (auto item : single)
	cout << item << " ";

  return 1;
}
