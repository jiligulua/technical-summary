标准库提供100多个算法，它们有一致的结构，理解它们的最基本方法是了解它们是否读取元素、改变元素或是重排元素顺序。

unique:只消除相邻重复的元素，所以，若是要消除不相邻的元素，就需要先sort排序，构成相邻的元素在一起，之后用unque才可以删除相邻的元素，即达到删除不重复的元素。此时，不再是原有的字符序列.

sort:针对字符默认按照字典元素排列   unique：在sort基础上，删除相邻重复元素而定制函数，可以实现自己需要的一致性顺序。

stable_sort:维持原有元素的顺序    stable_partition:维持原有元素的顺序

transfer:接受3个迭代器和一个可调用对象，前两个迭代器表示输入序列，第三哪个迭代器表示目的位置，算法对输入序列中每个元素调用可调用对象，并将结果写到目的位置。目的位置迭代器与表示输入序列开始位置的迭代器可以是相同的。当输入迭代器和目的迭代器相同时，transform将输入序列中每个元素替换为可调用对象操作该元素得到的结果。

count_if，类似find_if此函数接受一对迭代器，表示一个输入范围，还接受一个谓词，会对输入范围中每一个元素执行。count_if返回一个计算值，表示谓词有多少次位真。

再探迭代器，标准库<iterator>提供4中迭代器：
1.插入迭代器，被绑定到一个容器上，是迭代器适配器，可用来向容器插入元素。有3个：back_inserter,front_inserter,inserter(c, it),分别对应容器的push_back,push_front和insert(it,c)

2.流迭代器，通过它操作流，它将对应的流当作一个特定类型的元素序列来处理，使用流迭代器，可以用泛型算法从流对象读取数据以及向其写入数据。有2个：istream_iterator, ostream_iterator。默认初始化流迭代器，就是创将了一个可以当作尾后值使用的迭代器。
eg：ifstream in("afile"); istream_iterator<string> str_in(in); string表明流迭代器的元素，使用某一个流来初始化流迭代器。若没有流初始化，只是默认值，那就是尾后迭代器。
输入流迭代器的专业用法：用输入流（cin、ifstream）初始化后，直接使用该流迭代器和尾后迭代器，构造容器，如：istream_iterator<int> in_iter(cin), eof;
std::vector<int> ivec(in_iter, eof);
流迭代器至少支持某些迭代器操作，那么至少可以用某些算法来操作流迭代器。需要知道哪些算法可以用于流迭代器。
标准库保证在第一次解引用迭代器之前，从流中读取数据的操作已经完成了。这就允许使用懒惰求值。

ostream_iterator操作
可对任何具有输出运算符（<<）的类型定义ostream_iterator。可提供（可选的）第二参数，它是一个C风格字符串，在输出每个元素后都会打印此字符串，作分割符挺好的。
 
ostream_iterator<int> out_iter(cout, " ");
for (auto e : vec)
  *out_iter++ = e;// out_iter = e;
cout << endl;
copy(vec.cbegin(), vec.cend(), out_iter);
运算符*和++实际上对ostream_iterator对象不做任何作用。
一般输入流迭代器在赋值运算符右边，输出流迭代器在赋值运算符左边。赋值给输出流迭代器之后，直接就输出了。
可以使用流迭代器处理类类型只要该类定义了输入运算符>>就可以使用ostream_iterator和输出运算符<<就可以使用ostream_iterator

3.反向迭代器
就是在容器中从尾元素向首元素反向移动的迭代器。对于反向迭代器，递增（以及）递减操作的含义会颠倒过来。处理forward_list，其它容器都支持反向迭代器。我们可以调用rbegin,rend,crbegin, crend成员函数来获得反向迭代器。eg:反向迭代器的目的是表示元素范围，普通迭代器与反向迭代器的关系反映了左闭合区间。
通过调用reverse_iterator的base成员函数来完成这一转换，此成员函数会返回其对应的普通迭代器。
cbegin    comma          rcomma.base()
|        |               |      | cend()
F I R S T, M I D D L E , L A S T 
                       |       | 
					   rcomma  crbegin()

std::vector<int>::reverse_iterator re(ivec.cbegin()+2);
std::vector<int>::reverse_iterator rb(ivec.cbegin()+7);

10.5 泛型算法结构
任何算法的最基本特征是它要求其迭代器提供哪些操作，这样的迭代器共有5种，分别是
输入迭代器、输出迭代器：单遍扫描，只能递增，前者只读（不写），后者只写（不读）
前向迭代器:                       只能递增 
双向迭代器:   可读写，多遍扫描，  可递增递减
随机访问迭代器：                  支持全部迭代器运算
