#include "../base.h"
#include "interview.h"
#include <iomanip>

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

        int p[] =  {5, 7, 6, 9, 11, 10, 8};
        bool ret = isSequenceOfBST(p, sizeof(p)/sizeof(int));

        int p2[] =  {7, 4, 6, 5};
        bool ret2 = isSequenceOfBST(p2, sizeof(p2)/sizeof(int));
     }

     Spiral::Spiral(int row, int col)
     : mat(nullptr)
     , row_(row)
     , col_(col) {
        // 第一种方法：col必须是常量
        // int (*p)[5] = new int[row][5];

        // 第二种方法：row和col就可以不是常量了
        mat = new int*[row];
        for(int i = 0; i < row; ++i)
            mat[i] = new int[col];
    }

     Spiral::~Spiral() {
        if (mat != nullptr) 
        {
            for(int i = 0; i < row_; ++i)
                delete [] mat[i];
            delete [] mat;
        }
     }

    void Spiral::genSprial()
    {
        int i,j = 0;
        int left,top,right,bottom;
        left = top = 0;
        right = col_ - 1;
        bottom = row_ - 1;

        int total = row_ * col_;
        int index = 1;
        while(true) 
        {
            for(i = top, j = left; j <= right; ++j) {
                mat[i][j] = index++;
                if  (--total == 0) return;
            }
            ++top;

            for(i = top, j = right; i <= bottom; ++i) {
                mat[i][j] = index++;
                if (--total == 0) return;
            }
            --right;
            
            for(i = bottom, j = right; j >= left; --j) {
                mat[i][j] = index++;
                if (--total == 0) return;
            }
            --bottom;

            for(i = bottom, j = left; i >= top; --i) {
                mat[i][j] = index++;
                if (--total == 0) return;
            }
            ++left;
        }
    }

    void Spiral::print() 
    {
        for (int i = 0; i < row_; i++) 
        {
            for(int j = 0; j < col_; ++j) 
                cout << setw(5) << mat[i][j];
            cout << endl;
        }        
    }

    void printSpiral()
    {
        cout << "::Print Spiral" << endl;
        int n;
        while(true) {
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
        
        while(!s.empty() || indexPush < len) 
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
                    if (indexPush == len) return false;
                    s.push(*(pPush + indexPush++));
                }
            }
            else
            {
                if (indexPush == len) return false;
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
        
        while(!s.empty() || (pTempPush - pPush) < len) 
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
                    if (pTempPush - pPush == len) return false;
                    s.push(*pTempPush++);
                }
            }
            else
            {
                if (pTempPush - pPush == len) return false;
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
        if (start == end) return true;

        int i = start;
        int pivot = *(p+end);
        while(*(p+i) < pivot)
            ++i;

        int j = i;
        while(*(p+j) > pivot)
            ++j;
        
        if (j != end)
            return false;
        
        bool left = true;
        if (i - start > 1)
            left = isSequenceOfBST(p, start, i-1);

        bool right = true;
        if (end - i > 1 )
            right = isSequenceOfBST(p, i, end-1);

        return left && right;
    }

    bool isSequenceOfBST(const int *p, int len)
    {
        if (p == nullptr) return false;
        if (len == 1) return true;

        return isSequenceOfBST(p, 0, len-1);
    }
}