#pragma once
#include "base.h"

namespace mars
{
    void test_dynamic_memory();
    void test_reset();
    void test_temp_object();
    void test_temp_string();
    void test_1212();

    void test_1216();

    void test_array();

    void test_merge_char();
    void test_merge_string();

    void process(shared_ptr<string> p);
    void process(shared_ptr<int> p);

    void input_dynamic_array();
    void test_allocator();
    void test_allocator_str();
    void test_allocator_algo();

    void runQueries();
}