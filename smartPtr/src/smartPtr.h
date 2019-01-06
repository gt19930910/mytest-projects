#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>
using namespace std;


class CPoint 
{
public:
	CPoint(int xVal = 0, int yVal = 0) :x(xVal), y(yVal) {}
	//常量成员函数，意指不修改任何成员变量，外部定义的常量对象只能调用常量成员函数
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int xVal) { x = xVal; }
	void setY(int yVal) { y = yVal; }

private:
	int x, y;
};
/*
class CPtr
{
private:
	friend class CSmartPtr;
	CPtr(CPoint *ptr) :p(ptr), count(1) {}
	~CPtr() { delete p; }

	int count;
	CPoint *p;
};

class CSmartPtr
{
public:
	CSmartPtr(CPoint *ptr) :rp(new CPtr(ptr)) {}
	CSmartPtr(const CSmartPtr &sp) :rp(sp.rp) { ++rp->count; }
	CSmartPtr& operator=(const CSmartPtr &rhs) 
	{
		++rhs.rp->count;
		if (--rp->count == 0)
			delete rp;
		rp = rhs.rp;
		return *this;
	}
	~CSmartPtr() 
	{
		if (--rp->count == 0)
			delete rp;
		else
			cout << "还有" << rp->count << "个指针指向基础对象" << endl;
	}

	CPoint& operator *() { return *(rp->p); }

	CPoint* operator ->() { return rp->p; }

private:
	CPtr *rp;
};
*/

//模板类作为友元时要先声明
template <typename T>
class CSmartPtr;

//辅助类
template <typename T>
class CPtr
{
private:
	//该类成员访问权限全部为private,因为不想让用户直接使用该类
	//定义只能指针类为友元,因为智能指针类需要直接操作辅助类
	friend class CSmartPtr<T>;

	//基础类对象指针作为参数
	CPtr(T *ptr):p(ptr), count(1) {}
	~CPtr() { delete p; }

	//引用计数
	int count;
	//基础对象指针
	T *p; 
};

template <typename T>
class CSmartPtr
{
public:
	CSmartPtr(T *ptr):rp(new CPtr<T>(ptr)) {}
	CSmartPtr(const CSmartPtr<T> &sp):rp(sp.rp) { ++rp->count; }
	CSmartPtr& operator=(const CSmartPtr<T> &rhs)
	{
		++rhs.rp->count;
		if (--rp->count == 0)
			delete rp;
		rp = rhs.rp;
		return *this;
	}

	T& operator*() { return *(rp->p); }

	T* operator->() { return rp->p; }

	~CSmartPtr()
	{
		if (--rp->count == 0)
			delete rp;
		else
			cout << "还有" << rp->count << "个指针指向基础对象" << endl;
	}

private:
	CPtr<T> *rp; //辅助类对象指针
};

#endif