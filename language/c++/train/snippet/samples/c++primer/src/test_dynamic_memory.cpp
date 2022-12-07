#include "base.h"
#include <unistd.h>
#include "test_dynamic_memory.h"

namespace mars
{
    void test_dynamic_memory()
    {
        // test_reset();
        // test_temp_string();
        // test_temp_object();
        // test_1212();
        // test_1216();
        // test_array();
        // test_merge_char();
        // test_merge_string();
        // input_dynamic_array();
        // test_allocator();
        // test_allocator_str();
        // test_allocator_algo();
        runQueries();
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
        process(spName);                     // 使用shared_ptr，引用计数加1

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
        // IntP p5(p22.get()); // 产生未定义行为，重复删除内存
    }

    void test_array()
    {
        shared_ptr<int> up(new int[10], [](int *p)
                           { delete[] p; });
    }

    void test_merge_char()
    {
        cout << "test merge char" << endl;
        char pstr1[]{"Hello World!"};
        char pstr2[]{"I love you!"};

        int len1 = sizeof(pstr1) / sizeof(char);
        int len2 = sizeof(pstr2) / sizeof(char);
        unique_ptr<char[]> up(new char[len1 + len2 - 1]());
        for (int i = 0; i < len1 - 1; ++i)
        {
            up[i] = *(pstr1 + i);
        }

        for (int i = 0; i < len1; ++i)
        {
            up[i + len1 - 1] = *(pstr2 + i);
        }

        for (int i = 0; i < len1 + len2 - 1; ++i)
            cout << up[i];
        cout << endl;
    }

    void test_merge_string()
    {
        cout << "test_merge_string\n";
        string str1 = "Hello World! ";
        string str2 = "I love you! ";

        unique_ptr<char[]> up(new char[str1.size() + str2.size()]());
        for (int i = 0; i < str1.size(); ++i)
            up[i] = str1[i];

        for (int i = 0; i < str2.size(); ++i)
            up[i + str1.size()] = str2[i];

        for (int i = 0; i < str1.size() + str2.size(); ++i)
            cout << up[i];
        cout << endl;
    }

    void input_dynamic_array()
    {

        cout << "wait for input string:\n omit\n";
        return;
        char *pcz1 = new char[1];
        char *pcz2 = new char[100];
        cin >> pcz1;
        cout << pcz1;
        cin >> pcz2;
        cout << pcz2;
    }

    void test_allocator()
    {
        int n = 100;

        allocator<string> alloc;
        auto const p = alloc.allocate(n);
        auto q = p; // q指向最后构造的元素之后的位置。

        alloc.construct(q++);
        alloc.construct(q++, 10, 'c');
        alloc.construct(q++, "hi");

        while (q != p)
            alloc.destroy(--q);

        alloc.deallocate(p, n);
    }

    void test_array_str()
    {
        int n = 100;
        string *const p = new string[n];
        string s;
        string *q = p;
        while (cin >> s && q != p + n)
            *q++ = s;

        const size_t size = q - p;
        delete[] p;
    }

    void test_allocator_str()
    {
        // {
        //     cout << "input line, waiting ...\n";
        //     string line;
        //     while (getline(cin, line))
        //         cout << line << endl;
        // }

        cout << "input string for allocator, waiting ...\n";

        int n = 100;
        allocator<string> alloc;
        auto const p = alloc.allocate(n);
        auto q = p;
        string s;

        // 当从键盘上输入一串字符并按回车之后，这些字符首先被送到输入缓存区中。
        // 每当按下回车键之后，cin.get()就会检查输入缓存区中是否有字符串可读。
        // cin.get()并检查是否有流输入结束标识符Ctrl+Z（win）或Ctrl+D（Linux）

        // 检查方式有两种：阻塞(Windows)和非阻塞(Linux)

        // 阻塞式检查：只有在回车按下时，才检查缓存区字符串

        // 特点：
        // 0.Ctrl+Z:为流结束信号
        // 1.只有按下回车之后才有可能检测在此之前是否有Ctrl+Z按下；
        // 2.如果输入缓冲区中有可读的数据则不会检测Ctrl+Z
        //（因为有要读的数据，^z不会产生字符，以及^z之后的数据，都不会被存储到输入缓冲区中）。

        // 非阻塞式样指的是按下 Ctrl+D 之后立即响应的方式。
        // 如果在按 Ctrl+D 之前已经从键盘输入了字符，则 Ctrl+D的作用就相当于回车，
        // 即把这些字符送到输入缓冲区供读取使用，此时Ctrl+D不再起流结束符的作用。
        // 如果按 Ctrl+D 之前没有任何键盘输入，则 Ctrl+D 就是流结束的信号。

        // Windows一般使用阻塞式检查Ctrl+Z，Linux一般使用非阻塞式检查Ctrl+D。
        while (cin >> s && q != p + n)
            alloc.construct(q++, s);

        for_each(p, q, [](string str)
                 { cout << str << " "; });

        while (q != p)
            alloc.destroy(--q);

        alloc.deallocate(p, n);
    }

    void test_allocator_algo()
    {
        cout << "test allocator algoritm: \n";
        vector<int> vi {1,2,3,4,5,6,7,8};

        allocator<int> alloc;
        auto const p = alloc.allocate(vi.size() * 2);

        auto q = uninitialized_copy(vi.begin(), vi.end(), p);
        q = uninitialized_fill_n(q, vi.size(), 42);

        for_each(p, q, [](int i){
            cout << i << " ";
        });

        while(q != p)
            alloc.destroy(--q);

        alloc.deallocate(p, vi.size() * 2);

        cout << endl;
    }

    // The pub is for public. 
    // std::streambuf::pubseekoff is the public face of the protected virtual function seekoff.
    void runQueries()
    {
        char *buf = getcwd(nullptr, 0);
        ostringstream oo;
        oo << buf << "\\snippet\\res\\text.txt";
        string path = oo.str();
        
        
        bool suc = false;
        ifstream ifs(path);
        if (ifs.is_open())
            suc = true;

    }
}