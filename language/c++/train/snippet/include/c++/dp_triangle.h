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
        unsigned max_sum(unsigned i, unsigned j);
        unsigned max_sum_save(unsigned i, unsigned j);
        unsigned max_sum_nonrecur();
        unsigned max_sum_nonrecur_space_optimize();

    private:
        // shared_ptr<int [][MAX_ROW]> raw_data_;
        // shared_ptr<int [][MAX_ROW]> max_data_;

        unsigned data_[MAX_ROW][MAX_ROW];
        unsigned max_sum_[MAX_ROW][MAX_ROW];
        unsigned row_;
        unsigned * p_max_sum_;
    };
}