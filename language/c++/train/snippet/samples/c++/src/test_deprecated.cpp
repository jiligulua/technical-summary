#include "base.h"
#include "test_deprecated.h"

using namespace std;

namespace cpp11
{
    void test_deprecated()
    {
        test_bind();
        test_adaptor();
    }

    int sub(int x, int y)
    {
        return x - y;
    }

    void test_bind()
    {
        cout << "\ntest_bind" << endl;
        vector<int> nums = {1, 3, 14, 53, 4, 56, 20};
        auto it = find_if(cbegin(nums), cend(nums), bind1st(greater<int>(), 5));
        if (it != cend(nums))
            cout << *it << endl;


       auto it1 = find_if(cbegin(nums), cend(nums), bind2nd(greater<int>(), 5));
        if (it1 != cend(nums))
            cout << *it1 << endl;


        function<int(int)> f = bind(sub, 100, placeholders::_1);
        cout << "sub(x, y) -> sub(6): " << f(6) << endl;

        // function<bool(int)> f_greater = bind(greater<int>(), 5, placeholders::_1);
        auto f_greater = bind(greater<int>(), 5, placeholders::_1);
        cout << "greate<int>, 5 > ? result is: " << f_greater(15) << endl;

        bool is_bind_expr = is_bind_expression<decltype(f_greater)>::value;
    }

    int compare(const char *p, const char *q) {
        while(p) {
            auto *temp = q;
            while(*temp != '\0') {
                if (*p++ != *temp++)
                    break;
            }
            if(*temp == '\0')
                return 1;
        }
        return 0;
    }

    bool compare_str(const string &p, const string &q) {
        return -1 != p.find(q);
    }

    void test_adaptor()
    {
        int ret = compare("aloveb", "love");

        vector<string> vstr = {"abcedf", "abcefaabce", "123abc", "1245abc3456"};
        auto bind_compare = bind(compare_str, placeholders::_1, "abc");
        replace_if(begin(vstr), end(vstr), bind_compare, "love");
        //replace_if(begin(vstr), end(vstr), [](string a)->bool{ return -1 != a.find("abc"); }, "love");
        for(auto item : vstr)
            cout << item << " ";
        cout << endl;
    }
}