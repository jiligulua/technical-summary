#include "base.h"
#include "dp_samples.h"

namespace mars
{
    void test_dp_samples()
    {
        dp_eggs();
    }

    void dp_eggs()
    {
         int a[105][10005];
         for(int i = 1; i <= 100; ++i)
            for(int j = 1; j <= 10000; ++j)
                a[i][j] = 1;

        cout << "input k, n: ";
        int k,n;
        cin >> k >> n;

        
    }
}