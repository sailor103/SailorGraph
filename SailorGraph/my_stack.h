// my_stack.h : ջ��
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
	Node<T> *top;  //ָ��ջ����ָ��
};

//=======�����Ǻ�����ʵ��=======
template <class T>
my_Stack<T>::~my_Stack()//��������
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
T my_Stack<T>::Top()//����ջ��Ԫ��
{
    if(IsEmpty())
	{
	   //cout<<"ջ��Ԫ��Ϊ��,�����쳣"<<endl;
		AfxMessageBox(_T("����������������"));
	   exit(0);
	  // return T;
	}
	return top->data;
}

template <class T>
my_Stack<T>& my_Stack<T>::Add(T &x)//���Ԫ��
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
    	AfxMessageBox(_T("�ڴ���䲻��"));
    }
	return *this;
}

template <class T>
my_Stack<T>& my_Stack<T>::Delete()//ɾ��ջ��Ԫ��,���ҷ���ɾ����ֵ
{
     if(IsEmpty())
	 {
	   //cout<<"ջ��Ԫ��Ϊ��,�����쳣"<<endl;
       AfxMessageBox(_T("����������������"));
	   exit(0);
	   return *this;
	 }

	 Node<T>*p=top;
	 top=top->link;
	 delete p;
	 return *this;
}

#endif



