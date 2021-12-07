#include "base.h"
#include "test_sentence.h"

namespace mars
{
    void test_sentence()
    {
        // test_repeat_word();
        test_exception();
    }

    void test_repeat_word()
    {
        cout << "test_repeat_word, end with '#'" << endl;
        string word;
        string preword("");
        size_t cur_repeat_cnt = 0;

        string max_repeat_str;
        size_t max_repeat_cnt = 0;

        while (cin >> word && word != "#")
        {
            if (preword == word)
            {
                ++cur_repeat_cnt;
                if (cur_repeat_cnt > max_repeat_cnt)
                {
                    max_repeat_str = word;
                    max_repeat_cnt = cur_repeat_cnt;
                }
            }
            else
            {
                cur_repeat_cnt = 0;
            }
            preword = word;
        }

        cout << "max continuous repeat count is: " << max_repeat_cnt
             << " its string is: " << max_repeat_str << endl;
    }

    void test_exception()
    {
        cout << "test_exception, please input two integral number, end with #." << endl;
        int a;
        int b;
        while (cin >> a >> b && (a != '#' || b != '#'))
        {
            try
            {
                if (b == 0) {
                    throw runtime_error("b can not be zero.\n");
                }
                auto result = a / b;
                cout << "result a / b = " << result << endl;;
            }
            catch (runtime_error e)
            {
                cout << e.what() << endl;
                cout << "Try Again? Yes or No? " << endl;
                string word;
                cin >> word;
                if (!word.empty() && std::tolower(word[0]) == 'n') 
                    break;
            }
        }
    }
}