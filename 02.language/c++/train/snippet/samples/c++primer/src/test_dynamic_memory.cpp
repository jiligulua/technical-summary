#include "base.h"
#include "test_dynamic_memory.h"

namespace mars
{
    void test_dynamic_memory()
    {
        test_reset();
        test_temp_string();
        test_temp_object();
        test_1212();
        test_1216();
    }

    void test_temp_object()
    {
        cout << "test_temp_object";
        shared_ptr<int> p(new int(42));
        cout << p.use_count() << '\n';
        {
            cout << p.use_count() << '\n';
            shared_ptr<int>(p);
            cout << p.use_count() << '\n';
        }
        cout << p.use_count() << '\n';
    }

    void test_temp_string()
    {
        cout << "test_temp_string\n";
        shared_ptr<string> p(new string("hello"));
        // shared_ptr<string> q(p);
        cout << "#0:" << p.use_count() << '\n';
        {
            cout << "#1:" << p.use_count() << '\n';
            (shared_ptr<string>(p));
            // cout << *p << endl;
            cout << "#2:" << p.use_count() << '\n';
        }
        cout << "#3:" << p.use_count() << '\n';
    }
    
    
    void process(shared_ptr<string> p)
    {
        cout << *p << endl;
    }

    void process(shared_ptr<int> p)
    {
        cout << *p << endl;
    }

    // reset一般会和unique一起使用，来控制多个shared_ptr共享的对象
    void test_reset()
    {
        shared_ptr<int> p(new int(1024)); //
        // p.reset(new int(0));//p指向一个新的对象
        shared_ptr<int> p2(p);

        if (!p.unique()) // 说明还有其它人在使用该对象
        {
            p.reset(new int(*p)); //我们不是唯一用户，分配新的拷贝
        }
        *p += 12; //现在我们知道我们是唯一的用户，可以改变对象的值

        shared_ptr<string> spName = make_shared<string>("Chris");
        // process(shared_ptr<string>(spName.get())); // 使用原始指针，那么将创建一个新的shared指针和新的引用计数
        process(shared_ptr<string>(spName)); // 类型转换？引用计数没有变化
        process(spName); // 使用shared_ptr，引用计数加1


        shared_ptr<int> test1(new int(42));
        // process(shared_ptr<int>(test1));
        // process(test1);
        
        // process(shared_ptr<int>(test1.get())); // 使用原始指针的话，就创建一个新的引用计数，否则的话，是累积引用计数
                                               // 这个临时的对象，在将实参赋值给形参之后，就立刻消亡。
        // cout << "test1: " << *test1 << endl;
    }

    void test_1212()
    {
        auto p = new int();
        auto sp = make_shared<int>();
        process(sp);
        process(shared_ptr<int>(p)); // 由于没有对p进行delete，所以调用process没有问题。
    }

    void test_1216()
    {
        cout << "test_1216\n";
        unique_ptr<int> p1(new int(42));

        cout << "#1:" << *p1 << endl;

        unique_ptr<int> p2;

        p2.reset(p1.release());


        int ix = 1024, *pi = &ix, *pi2 = new int(2048);
        typedef unique_ptr<int> IntP;

        // IntP p0(ix); 没有该构造函数，需要使用指针类型。
        // IntP p11(pi); 不是动态内存，在unique_ptr析构时，发生类型不匹配，不能删除
        IntP p22(pi2);
        // IntP p3(&ix); 不是动态内存，在unique_ptr析构时，发生类型不匹配，不能删除
        // IntP p4(new int (2048));
        IntP p5(p22.get()); // 产生未定义行为，重复删除内存
    }
}