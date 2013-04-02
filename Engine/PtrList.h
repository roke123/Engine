#ifndef __PTRLIST_H__
#define __PTRLIST_H__

#include <list>
using namespace std;

//使用时需解引用
template<class T>
class PtrList
{
public:
	PtrList() {}
	//自动释放链表中指针
	~PtrList();

	list<T *>& operator * ()
	{
		return list_;
	}

	typedef typename std::list<T *>::iterator iterator;
	typedef typename std::list<T *>::const_iterator const_iterator;

private:
	PtrList<T>& operator = ( const PtrList<T>& ) {}
	PtrList( const PtrList<T>& ) {}

private:
	list<T *> list_;
};

template<class T>
PtrList<T>::~PtrList()
{
	iterator ite = list_.begin();
	for( ; ite != list_.end(); ++ite )
	{
		(*ite)->Release();
	}
	list_.clear();
}

#endif	// end of PtrList.h