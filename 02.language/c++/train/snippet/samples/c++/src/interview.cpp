#include "../base.h"
#include "interview.h"
#include <iomanip>
#include <cmath>

namespace mars
{
    void interview()
    {
        // printSpiral();

        // int push[] = {1,2,3,4,5};
        // int pop[] = {4,5,3,2,1};
        // int ret = isPopOrder_31_ex(push, pop, 5);

        // int pop2[] = {4,3,5,1,2};
        // ret = isPopOrder_31_ex(push, pop2, 5);

        // printBinaryTree_32();

        // int p[] =  {5, 7, 6, 9, 11, 10, 8};
        // bool ret = isSequenceOfBST(p, sizeof(p)/sizeof(int));

        // int p2[] =  {7, 4, 6, 5};
        // bool ret2 = isSequenceOfBST(p2, sizeof(p2)/sizeof(int));

        // char p[] = {'1','2','3','4','5','6','7','8','9'};
        // printPermutation(p, sizeof(p)/sizeof(int));

        // int data[] = {5, 6, 7, 2, 3, 4, 8, 9, 2, 5, 6};
        // int len = sizeof(data) / sizeof(int);
        // quickSort(data, len, 0, len - 1);

        // testHeap();
        // vector<int> vi = {0, 1, 10, 12, 211, 213, 3210, 3215};
        // // vector<int> vi = {211, 213};
        // for (auto num : vi)
        // {
        //     findNthDigit_44(num);
        // }


        // test45
        vector<int> vi = {321,32,3,9,987,967, 99,8};
        // vector<int> vi = {321,32,3};
        printMinNumber_45(vi);
    }

    void GetMedian::Insert(int num)
    {
        int size = maxheap.size() + minheap.size();
        if (size & 1)
        { //第偶数个的情况
            int tmp = num;
            if ((!maxheap.empty()) && (num < maxheap[0]))
            {
                tmp = maxheap[0];
                maxheap[0] = num;
                make_heap(maxheap.begin(), maxheap.end());
            }

            minheap.push_back(tmp);
            push_heap(minheap.begin(), minheap.end(), greater<int>());
        }
        else
        {
            int tmp = num;
            if ((!minheap.empty()) && (num > minheap[0]))
            {
                tmp = minheap[0];
                minheap[0] = num;
                make_heap(minheap.begin(), minheap.end(), greater<int>());
            }

            maxheap.push_back(tmp);
            push_heap(maxheap.begin(), maxheap.end());
        }
    }

    double GetMedian::getMedian()
    {
        int size = maxheap.size() + minheap.size();
        double result;
        if (size & 1)
        {
            result = maxheap[0];
        }
        else
        {
            result = (maxheap[0] + minheap[0]) / 2.;
        }

        return result;
    }

    Spiral::Spiral(int row, int col)
        : mat(nullptr), row_(row), col_(col)
    {
        // 第一种方法：col必须是常量
        // int (*p)[5] = new int[row][5];

        // 第二种方法：row和col就可以不是常量了
        mat = new int *[row];
        for (int i = 0; i < row; ++i)
            mat[i] = new int[col];
    }

    Spiral::~Spiral()
    {
        if (mat != nullptr)
        {
            for (int i = 0; i < row_; ++i)
                delete[] mat[i];
            delete[] mat;
        }
    }

    void Spiral::genSprial()
    {
        int i, j = 0;
        int left, top, right, bottom;
        left = top = 0;
        right = col_ - 1;
        bottom = row_ - 1;

        int total = row_ * col_;
        int index = 1;
        while (true)
        {
            for (i = top, j = left; j <= right; ++j)
            {
                mat[i][j] = index++;
                if (--total == 0)
                    return;
            }
            ++top;

            for (i = top, j = right; i <= bottom; ++i)
            {
                mat[i][j] = index++;
                if (--total == 0)
                    return;
            }
            --right;

            for (i = bottom, j = right; j >= left; --j)
            {
                mat[i][j] = index++;
                if (--total == 0)
                    return;
            }
            --bottom;

            for (i = bottom, j = left; i >= top; --i)
            {
                mat[i][j] = index++;
                if (--total == 0)
                    return;
            }
            ++left;
        }
    }

    void Spiral::print()
    {
        for (int i = 0; i < row_; i++)
        {
            for (int j = 0; j < col_; ++j)
                cout << setw(5) << mat[i][j];
            cout << endl;
        }
    }

    void printSpiral()
    {
        cout << "::Print Spiral" << endl;
        int n;
        while (true)
        {
            do
            {
                cout << "input matrix n: ";
                cin >> n;
            } while (n < 1);

            Spiral sprial(n, n);
            sprial.genSprial();
            sprial.print();
        }
    }

    bool isPopOrder_31(const int *pPush, const int *pPop, int len)
    {
        if (len == 0 || pPush == nullptr || pPop == nullptr)
            return false;

        int indexPush = 0;
        int indexPop = 0;
        stack<int> s;

        s.push(*(pPush + indexPush++));

        while (!s.empty() || indexPush < len)
        {
            if (!s.empty())
            {
                if (s.top() == *(pPop + indexPop))
                {
                    s.pop();
                    ++indexPop;
                }
                else
                {
                    if (indexPush == len)
                        return false;
                    s.push(*(pPush + indexPush++));
                }
            }
            else
            {
                if (indexPush == len)
                    return false;
                s.push(*(pPush + indexPush++));
            }
        }

        return true;
    }

    bool isPopOrder_31_ex(const int *pPush, const int *pPop, int len)
    {
        if (len == 0 || pPush == nullptr || pPop == nullptr)
            return false;

        stack<int> s;
        const int *pTempPush = pPush;
        const int *pTempPop = pPop;

        s.push(*pTempPush++);

        while (!s.empty() || (pTempPush - pPush) < len)
        {
            if (!s.empty())
            {
                if (s.top() == *pTempPop)
                {
                    s.pop();
                    ++pTempPop;
                }
                else
                {
                    if (pTempPush - pPush == len)
                        return false;
                    s.push(*pTempPush++);
                }
            }
            else
            {
                if (pTempPush - pPush == len)
                    return false;
                s.push(*pTempPush++);
            }
        }

        return true;
    }

    void printBinaryTree_32()
    {
        // 使用栈或者队列，来解决问题。一个不够，就用2个，或交替使用
    }

    bool isSequenceOfBST(const int *p, int start, int end)
    {
        if (start == end)
            return true;

        int i = start;
        int pivot = *(p + end);
        while (*(p + i) < pivot)
            ++i;

        int j = i;
        while (*(p + j) > pivot)
            ++j;

        if (j != end)
            return false;

        bool left = true;
        if (i - start > 1)
            left = isSequenceOfBST(p, start, i - 1);

        bool right = true;
        if (end - i > 1)
            right = isSequenceOfBST(p, i, end - 1);

        return left && right;
    }

    bool isSequenceOfBST(const int *p, int len)
    {
        if (p == nullptr)
            return false;
        if (len == 1)
            return true;

        return isSequenceOfBST(p, 0, len - 1);
    }

    void permutation(char *pStr, char *pBeg)
    {
        if (*pBeg == '\0')
        {
            printf("%s\n", pStr);
            return;
        }
        else
        {
            for (char *pCh = pBeg + 1; *pCh != '\0'; ++pCh)
            {
                char temp = *pCh;
                *pCh = *pBeg;
                *pBeg = temp;

                permutation(pStr, pBeg + 1);

                temp = *pCh;
                *pCh = *pBeg;
                *pBeg = temp;
            }
        }
    }

    void printPermutation(char *pStr, int len)
    {
        if (pStr == nullptr)
            return;

        permutation(pStr, pStr); // 初始化第一个
    }

    void swap(int *p, int *q)
    {
        int temp = *p;
        *p = *q;
        *q = temp;
    }

    int randomInRange(int start, int end)
    {
        return 1;
    }

    int partition(int data[], int length, int start, int end)
    {
        if (data == nullptr || length <= 0 || start < 0 || end >= length)
            throw new invalid_argument("Invalid Parameters!");

        // int index = randomInRange(start, end);
        // 将pivot放到数组的最后
        // swap(&data[index], &data[end]);

        int low = start;
        int high = end;
        int pivot = data[end];
        while (low < high)
        {
            while (low < high && data[low] <= pivot)
                ++low;
            swap(&data[low], &data[high]);

            while (low < high && pivot < data[high])
                --high;
            swap(&data[low], &data[high]);
        }

        return low;
    }

    void quickSort(int data[], int length, int low, int high)
    {
        if (low < high)
        {
            int index = partition(data, length, low, high);
            quickSort(data, length, low, index - 1);
            quickSort(data, length, index + 1, high);
        }
    }

    void testHeap()
    {
        int myints[] = {10, 20, 30, 5, 15};
        std::vector<int> v(myints, myints + 5);

        std::make_heap(v.begin(), v.end());
        std::cout << "initial max heap   : " << v.front() << '\n';

        std::pop_heap(v.begin(), v.end());

        std::cout << "max heap after pop : " << v.front() << '\n';
        v.pop_back();
        std::cout << "max heap after pop : " << v.front() << '\n';

        v.push_back(99);
        std::push_heap(v.begin(), v.end());
        std::cout << "max heap after push: " << v.front() << '\n';

        std::sort_heap(v.begin(), v.end());

        std::cout << "final sorted range :";
        for (unsigned i = 0; i < v.size(); i++)
            std::cout << ' ' << v[i];

        std::cout << '\n';
    }

    void testMiddle()
    {
        GetMedian test;
        test.Insert(1);
        test.Insert(9);
        test.Insert(3);
        test.Insert(6);
        test.Insert(20);
        test.Insert(82);

        cout << test.getMedian() << endl;
    }

    void findNthDigit_44(int n)
    {
        // 时间复制度：O(n) = log10n
        int digit = 1;
        int count = 10;
        int start = 0;
        int tempn = n + 1;
        while (tempn > count)
        {
            tempn -= count;
            start = pow(10, digit);
            ++digit;
            count = pow(10, digit) * digit;
        }

        long num = start + (tempn - 1) / digit;
        long reminder = (tempn - 1) % digit;
        cout << "第" << n << "位的数字是" << num << ", 是在数字中的第" << reminder << "位" << endl;
    }

    // from simple to complex, 两两比较扩展到整个数列的比较，就可以用使用sort中的cmp函数。
    void printMinNumber_45(vector<int>  numbers)
    {
        sort(numbers.begin(), numbers.end(), [](int a, int b) -> bool {
            string ab = std::to_string(a) + std::to_string(b);
            string ba = std::to_string(b) + std::to_string(a);

            return ab < ba; // if return true, the first parameter is before the second one.
        });

        for(auto item : numbers)
        {
            cout << item;
        }
        cout << endl;
    }

}