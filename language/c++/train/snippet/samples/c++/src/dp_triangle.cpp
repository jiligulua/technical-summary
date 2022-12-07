#include "dp_triangle.h"
#include <ctime>
#include <random>

using namespace std;

namespace mars
{
    DpTriangle::DpTriangle()
    {
    }

    DpTriangle::~DpTriangle()
    {
        // 直接在输入时，进行初始化max_sum_效率更高
        // for(int i = 0; i < MAX_ROW; ++i)
        //     for(int j = 0; j < MAX_ROW; ++j)
        //     {
        //         max_sum_[i][j] = -1;
        //         data_[i][j] = -1;
        //     }
    }

    void DpTriangle::run()
    {
        initialize_data();
        // unsigned sum = max_sum(0, 0);
        // cout << "sum is: " << sum << endl;

        // unsigned sum1 = max_sum_save(0, 0);
        // cout << "sum is: " << sum1 << endl;

        unsigned sum2 = max_sum_nonrecur();
        cout << "sum is: " << sum2 << endl;

        unsigned sum3 = max_sum_nonrecur_space_optimize();
        cout << "sum is: " << sum3 << endl;
    }

    void DpTriangle::initialize_data()
    {
        cout << "input row line (0 ~ 100): ";
        cin >> row_;
        while (row_ > MAX_ROW)
        {
            cout << row_ << " is greate than " << MAX_ROW << ", try again: ";
            cin >> row_;
        }

        cout << "automatically generate data...\n";
        default_random_engine e(time(0));
        uniform_int_distribution<unsigned int> u(0, MAX_ROW);
        for (unsigned i = 0; i < row_; ++i)
        {
            for (unsigned j = 0; j <= i; ++j)
            {
                data_[i][j] = u(e);
                cout << data_[i][j] << " ";
                max_sum_[i][j] = -1;
            }
            cout << endl;
        }
    }

    unsigned DpTriangle::max_sum(unsigned i, unsigned j)
    {
        if (i == row_ - 1)
            return data_[i][j];

        unsigned x = max_sum(i + 1, j);
        unsigned y = max_sum(i + 1, j + 1);

        return max(x, y) + data_[i][j];
    }

    unsigned DpTriangle::max_sum_save(unsigned i, unsigned j)
    {
        if (max_sum_[i][j] != -1)
            return max_sum_[i][j];

        if (i == row_ - 1)
            max_sum_[i][j] = data_[i][j];
        else
        {
            unsigned x = max_sum_save(i + 1, j);
            unsigned y = max_sum_save(i + 1, j + 1);
            max_sum_[i][j] = max(x, y) + data_[i][j];
        }

        return max_sum_[i][j];
    }

    // 从递归到递推的根本转变：就是从已知推出未知！
    unsigned DpTriangle::max_sum_nonrecur()
    {
        for(int i = 0; i < row_; ++i)
            max_sum_[row_-1][i] = data_[row_-1][i];

        for(int i = row_-2; i >= 0; --i)
            for(int j = 0; j < i+1; ++j)
                max_sum_[i][j] = max(max_sum_[i+1][j], max_sum_[i+1][j+1]) + data_[i][j];

        return max_sum_[0][0];
    }

    unsigned DpTriangle::max_sum_nonrecur_space_optimize()
    {
        p_max_sum_ = data_[row_-1];
        for(int i = row_-2; i >= 0; --i)
            for(int j = 0; j < i+1; ++j)
                p_max_sum_[j] = max(p_max_sum_[j], p_max_sum_[j+1]) + data_[i][j];
        
        return p_max_sum_[0];
    }

}