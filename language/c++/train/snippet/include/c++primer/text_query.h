#pragma once
#include "base.h"

class TextQuery
{
public:
    explicit TextQuery(const string &path);
    ~TextQuery();

    bool query(const string &key_word);

    void print();
    void print(int number);

private:
    std::map<int, string> lines_;
    std::set<int> numbers_;
};