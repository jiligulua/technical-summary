// Neptune.cpp: 定义应用程序的入口点。
//

#include "Neptune.h"

using namespace std;

#include "Neptune.h"
#include "non_mutate.h"
#include "test_non_mutate.h"
#include "test_array.h"



int main()
{


	test_np_search_n();
	test_np_serach_n_predicat();

	test_multi_array();
	test_multi_array_using();

	system("pause");

	//bool is_bind_expr = is_bind_expression<decltype(f_greater)>::value;

	return 0;
}
