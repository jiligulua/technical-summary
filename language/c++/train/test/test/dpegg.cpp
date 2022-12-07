#include <iostream>
#include <algorithm>

using namespace std;



class Solution {
public:
    int superEggDrop(int k, int n) {
        int **f = new int*[k+1];
        for(int i = 0; i < k+1; ++i)
            f[i] = new int[n+1];

        for(int i = 0; i < k+1; ++i)
            for(int j = 0; j < n+1; ++j)
                f[i][j] = j;

        for(int i = 1; i <= k; ++i)
            for(int j = 1; j <= n; ++j)
                for(int x = 1; x <= j; ++x)
                    f[i][j] = min(f[i][j], 1+max(f[i-1][j-1], f[i][j-x]));


        return f[k][n];
    }
};

int main()
{
	Solution s;
	
	cout << s.superEggDrop(2, 2) << endl;

	return 1;
}
