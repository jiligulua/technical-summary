list,forward_list,deque还支持push_front，循环添加元素可构成逆序。习题
4个提供随机访问的容器：vector, string, array, deque。所谓的随机访问就是：front，back，下标和at，返回的都是引用，若是用auto则需要添加引用符号&。
较list相比，执行相同的操作forward_list效率更高 

resize 只改变容器中的元素，而不改变容器的容量。它是生成新的容器元素。若原先有比较多的元素，而resize的数量比原来少，就会对原有的元素进行截断处理。若比原来的多，并且仅是指定数量，则原来的元素不变。新增的元素才会被指定的元素替换。
resize(n), resize(n, t)只有这两个函数，该函数只改变容器中的元素。

reserve 不会减少容器占用的内存空间，只有当需要的内存空间超过当前容量时，reserve调用才会改变vector的容量。它是分配新的空间

vector如何增长？
只有在执行insert时size和capicity相等，或调用resize或reserve时给定的大小超过当前capacity，vector才可重新分配空间。会分配多少超过给定容量的额外空间取决于具体实现。
vector的实现采用的策略似乎是每次需要分配新内存空间时将当前容量翻倍


capacity：不扩张内存空间的情况下可以容纳多少个元素
reserve：允许我们通知容器应该准备保存多少个元素

latin-1:单字节编码，向下兼容ASCII，编码范围是0x00-0xFF，0x00-0x7F是ASCII完全一样，0x80-0x9F是控制字符，0xA0-0xFF是文字符号

默认情况下，stack和queue是基于deque实现的，priority_queue是在vector之上实现的。在创建一个适配器时，将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型。

stack：除array和forward_list之外，其它4种顺序容器都可以构造stack
queue：构造于list or deque之上
priority_queue: 要求随机访问能力，可构造于vector or deque之上，不能基于list构造
