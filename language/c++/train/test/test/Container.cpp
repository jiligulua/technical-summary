#include "Container.h"
#include <vector>
using namespace std;

void Container::testVector()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);

    for(auto it = v.begin(); it != v.end(); ++it) 
    {
        v.erase(it);
        --it;
    }

    // v.clear();
}