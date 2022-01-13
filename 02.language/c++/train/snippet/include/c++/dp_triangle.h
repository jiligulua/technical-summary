#pragma once
#include "base.h"

namespace mars
{
    constexpr int MAX_ROW = 100;
    class DpTriangle
    {
    public:
        DpTriangle();
        ~DpTriangle();

        void run();

    private:
        void initialize_data();
        unsigned calculate_max_sum(unsigned i, unsigned j);

    private:
        // shared_ptr<int [][MAX_ROW]> raw_data_;
        // shared_ptr<int [][MAX_ROW]> max_data_;

        unsigned data_[MAX_ROW][MAX_ROW];
        unsigned max_sum_[MAX_ROW][MAx_ROW];
        unsigned row_;
    };
}