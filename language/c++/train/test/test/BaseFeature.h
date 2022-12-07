#pragma once
_Pragma("once")

#include <iostream>
#include <vector>
#include <memory>

#define LOG(...) {\
    fprintf(stderr, "%s line:%d ", __FILE__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
    }

#define PR(...) printf(__VA_ARGS__)



enum class Options {
    None,
    One,
    All
};

class A
{
    public:
    void testForeach();

    Options getOptions(int num);

    void testUniquePtr();
    void testSharePtr();
    void testWeakPtr();
    void testLoopReference();

    void testLambda();
    void testC99();

    void testPrintf();
    void testMacro(...);
    void testUnicodeLib();
    void testUnicodeLib2(void);



    private:
    void foo(int *p);
    void bar(std::shared_ptr<int> p);

    void testBeginEnd();
};

class B
{
    public:
    virtual void f(int) { std::cout << "B::f" << std::endl;}
};

class D : public B
{
    public:
    virtual void f(int) override final { std::cout << "D::f" << std::endl; }
};

class F : public D
{
    public:
    void f(short)  { std::cout << "F:f" << std::endl; }    

    // virtual void f(int) override { std::cout << "F::f" << std::endl; }
};

struct AStruct;
struct BStruct;

struct AStruct
{
    // std::shared_ptr<BStruct> bPtr;
    std::weak_ptr<BStruct> bPtr;
    ~AStruct() { std::cout << "AStruct is deleted!" << std::endl; }
};

struct BStruct
{
    // std::shared_ptr<AStruct> aPtr;
    std::weak_ptr<AStruct> aPtr;
    ~BStruct() { std::cout << "BStruct is deleted!" << std::endl; }
};

