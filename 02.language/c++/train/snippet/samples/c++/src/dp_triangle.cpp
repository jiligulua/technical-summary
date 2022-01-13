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
        for(int i = 0; i < MAX_ROW; ++i)
            for(int j = 0; j < MAX_ROW; ++j)
            {
                max_sum_[i][j] = -1;
                data_[i][j] = -1;
            }
    }

    void DpTriangle::run()
    {
        initialize_data();
        unsigned sum = calculate_max_sum(0, 0);
        cout << "sum is: " << sum;
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
            }
            cout << endl;
        }
    }

    unsigned DpTriangle::calculate_max_sum(unsigned i, unsigned j)
    {
        if (i == row_-1)
            return data_[i][j];

        unsigned x = calculate_max_sum(i+1, j);
        unsigned y = calculate_max_sum(i+1, j+1);
        return max(x, y) + data_[i][j];
    }

}