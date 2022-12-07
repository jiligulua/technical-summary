#include "BaseFeature.h"
#include <algorithm>
#include <stdio.h>
#include <string>

namespace {
    static const char kTag[] = "Chris: ";
}
void A::testForeach()
{
    auto i = 1;
    auto l = 42LL;

    std::vector<int> iv = {1, 2, 3, 4, 5, 6};

    for (auto i : iv)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

void A::testUniquePtr()
{
    std::unique_ptr<int> p1(new int(42));
    std::unique_ptr<int> p2 = std::move(p1);

    if (p1)
    {
        foo(p1.get());
    }

    if (p2)
    {
        foo(p2.get());
    }
}

void A::testSharePtr()
{
    // std::shared_ptr<int> p1(new int(42));
    auto p11 = std::make_shared<int>(42);
    std::shared_ptr<int> p2(p11);

    // p2.reset();  // reset()表示将nullptr交给p2智能指针对象管理，而对原来内存块计数减1

    if (!p2.unique())
    {
    }

    bar(p11);
    foo(p2.get());
}

void A::testWeakPtr()
{
    auto p = std::make_shared<int>(42);

    std::weak_ptr<int> wp = p;

    {
        auto sp = wp.lock(); // 只能使用lock获得共享对象
        std::cout << "test weak_ptr: " << *sp.get() << std::endl;
    }

    
    std::shared_ptr<int> p2 = p;
    p.reset(); // 对原有对象进行引数减1操作

    if (wp.expired())
    {
        std::cout << "weak_ptr is expired" << std::endl;
    }
    else
    {
        std::cout << "weak_ptr is not expired" << std::endl;
    }
    
}

void A::foo(int *p)
{
    std::cout << "ptr content is: " << *p << std::endl;
}

void A::bar(std::shared_ptr<int> p)
{
    ++(*p);
}

Options A::getOptions(int num)
{
    if (num > 45)
    {
        return Options::All;
    }
    else if (num > 20)
    {
        return Options::One;
    }
    else
    {
        return Options::None;
    }
}

void A::testLoopReference()
{
    std::shared_ptr<AStruct> spA(new AStruct);
    std::shared_ptr<BStruct> spB(new BStruct);

    spA->bPtr = spB;
    spB->aPtr = spA;
}

void A::testLambda()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    v.push_back(6);

    std::cout << "lambda: ";
    int x;
    std::for_each(v.begin(), v.end(), [&x](int n){
        x = n;
        std::cout << x << " ";
    });

    auto is_odd = [](int n) { return n % 2 == 1; };
    auto pos = std::find_if(std::begin(v), std::end(v), is_odd);
    if (pos != std::end(v)) 
    {
        std::cout << "" << *pos << std::endl;
    }
}

void A::testBeginEnd()
{
    
}

void A::testC99()
{
    std::cout << "test C99 in C++11: ";
    std::cout << "function name: " << __func__ << " file: " << __FILE__ << " line: "<< __LINE__ << std::endl;
}

void A::testPrintf()
{
    std::cout << "test Printf: ";

    printf("%s\n", "Hello world");
    // fprintf(stdout, "%s\n", "Hello World");
    fprintf(stderr, "%s\n", "This is a error o移动utput");

    // 1>log.txt 2>err.txt  pipe stream, 1> get the stdout output, 2> get the stderr output
}

#define XNAME(n) x##n
#define PXN(n) printf("x" #n " = %d\n", x##n)

#define TEST1(param1, param2, var)   param1##param2 var
#define TEST2(param1, param2)  param1##param2
#define PASTE_STR(param1, param2)  param1 param2
// #define _TEST1(param1, param2)  TEST1(param1, param2)
#define HELLO F
#define WORLD f

void A::testMacro(...)
{
    int XNAME(1) = 12; // define variable x1, and assign 12 to it

    PXN(1);

    int a = TEST2(12, 43);
    printf("%d\n", a);

    
    // TEST(HELLO, WORLD);
    TEST1(in, t, x) = 1;
    // printf("%s\n", str);

    char cszHello[] = "hello";
    // char *q = TEST2("Hello", "World!"); // if so, the result of q is "Hello""World!". it's wrong! 

    char cszWelcomeWorld[] = PASTE_STR("Hello", "World");
    printf("welcome world is %s\n", cszWelcomeWorld);
    printf("file name is: %s\n", __FILE__);

    LOG("%s %s", kTag, "use the __VA_ARGS__");
}

#include <cuchar>

void A::testUnicodeLib()
{
    setlocale(LC_ALL, "en_US.utf8");
    char16_t utf16[] = u"\u4F60\u597D\u554A";
    std::size_t in_sz = sizeof(utf16) / sizeof(*utf16);

    char mbr[sizeof(utf16)*2] = {0};
    char *p = mbr;
    mbstate_t s;
    for(std::size_t n = 0; n < in_sz; ++n)
    {
        int len = c16rtomb(p, utf16[n], &s);
        if (len == -1)
        {
            break;
        } 
        else 
        {
            p += len;
        }
    }
    
    std::cout << "uft-16 -> utf-8: " << mbr << std::endl;
}

void A::testUnicodeLib2(void)
{
    setlocale(LC_ALL, "en_US.utf8");
    char16_t in[] = u"zß水?"; // or "z\u00df\u6c34\U0001F34C"
    size_t in_sz = sizeof in / sizeof *in;
 
    printf("Processing %zu UTF-16 code units: [ ", in_sz);
    for(size_t n = 0; n < in_sz; ++n) printf("%#x ", in[n]);
    puts("]");
 
    mbstate_t state;
    char out[MB_CUR_MAX * in_sz] = {0};
    char *p = out;
    for(size_t n = 0; n < in_sz; ++n) {
        int rc = c16rtomb(p, in[n], &state); 
        if(rc == -1) break;
        p += rc;
    }
 
    size_t out_sz = p - out;
    printf("into %zu UTF-8 code units: [ ", out_sz);
    for(size_t x = 0; x < out_sz; ++x) printf("%#x ", +(unsigned char)out[x]);
    puts("]");
}