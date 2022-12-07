#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template<typename T, typename S>
class GenericAlgo
{
public:
	auto getCount(const T& t, const S& s) -> decltype(count(t.cbegin(), t.cend(), s))
	{
		return count(t.cbegin(), t.cend(), s);
		
	}
};
