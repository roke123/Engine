#ifndef __REFOBJECT_H__
#define __REFOBJECT_H__

class RefObject
{
public:
	RefObject() : refCount_( new int )
	{
		*refCount_ = 1;
	}

	virtual ~RefObject()
	{
		delete refCount_;
	}

	void AddRef() const
	{
		++ *refCount_;
	}

	void Release() const
	{
		if( -- *refCount_ == 0 )
			//调用完this的析构函数后在refObject的析构函数中delete refCount_
			delete this;
	}

	void operator = ( const RefObject& refObject )
	{
		refObject.AddRef();

		refCount_ = refObject.refCount_;
	}

	RefObject( const RefObject& refObject )
	{
		refObject.AddRef();

		refCount_ = refObject.refCount_;
	}

private:
	int * refCount_;
};

#endif	//end of RefObject.h