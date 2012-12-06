// my_stack.h : 栈类
//

#ifndef MY_STACK_H_H
#define MY_STACK_H_H

//#include <iostream>
//using namespace std;

template <class T> class my_Stack;

template <class T> class Node
{
    friend my_Stack<T>;
public:
	Node(){data=0;link=NULL;}
private:
	T data;
	Node<T> *link;
};

template <class T>
class my_Stack
{
public:
	my_Stack(){top=NULL;}
	~my_Stack();
	bool IsEmpty(){return top==0;}
	T Top();
	my_Stack<T>& Add(T& x);
	my_Stack<T>& Delete();

private:
	Node<T> *top;  //指向栈顶的指针
};

//=======下面是函数的实现=======
template <class T>
my_Stack<T>::~my_Stack()//析构函数
{
    Node<T>*next;
	while(top)
	{
		next=top->link;
		delete top;
		top=next;

	}
}

template <class T>
T my_Stack<T>::Top()//返回栈顶元素
{
    if(IsEmpty())
	{
	   //cout<<"栈顶元素为空,程序异常"<<endl;
		AfxMessageBox(_T("数据输入有误，请检查"));
	   exit(0);
	  // return T;
	}
	return top->data;
}

template <class T>
my_Stack<T>& my_Stack<T>::Add(T &x)//添加元素
{
    try
    {
		Node<T>*p=new Node<T>;
		p->data=x;
		p->link=top;
		top=p;
    }
    catch (...)
    {
    	AfxMessageBox(_T("内存分配不足"));
    }
	return *this;
}

template <class T>
my_Stack<T>& my_Stack<T>::Delete()//删除栈顶元素,并且返回删除的值
{
     if(IsEmpty())
	 {
	   //cout<<"栈顶元素为空,程序异常"<<endl;
       AfxMessageBox(_T("数据输入有误，请检查"));
	   exit(0);
	   return *this;
	 }

	 Node<T>*p=top;
	 top=top->link;
	 delete p;
	 return *this;
}

#endif



