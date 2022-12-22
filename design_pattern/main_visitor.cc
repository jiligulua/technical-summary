#include "visitor.h"

int main() {
  PrintVisitor vis;
  
  StA a;
  a.val = 8.97;
  StB b;
  b.val = 8;

  Element* element = &a;
  element->Accept(vis);

  element = &b;
  element->Accept(vis);
}


/*

C++11改进后的访问者模式不会因被访问者的继承层次经常变化而需要经常修改，接口层稳定。和以前的访问者模式的实现相比，改进后的访问者模式把Visitor接口层的变化转移到被访问者基类对象中，虽然Visitor接口层会保持稳定，但如果需要增加新的访问者，基类的Visitor类型也要对应扩展，但是这种变化相对于原来Visitor接口层的变化来说是很小了（只需要在类型定义中扩展一个类型即可），也是容易维护的。
 
 */
