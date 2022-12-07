#pragma once

typedef int length;

class Point6d
{
public:
    typedef float length;
public:
    void mumble(length val) { _val = val; }
    length mumble() { return _val; }

private:
    
    length _val;
};

