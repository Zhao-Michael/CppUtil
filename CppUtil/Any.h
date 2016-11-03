#pragma once
#include <stdio.h>
#include <typeinfo>
#include <assert.h>

class PlaceHolder
{
public:

	virtual ~PlaceHolder() {};

	virtual const std::type_info & type() const = 0;

	virtual PlaceHolder* clone() const = 0;

};


template<typename ValueType>
class Holder :public PlaceHolder
{
public:

	Holder(const ValueType & value) :held(value) { };

	Holder(ValueType&& value) : held(static_cast<ValueType>(value)) { }

	virtual const std::type_info & type() const
	{
		return typeid(held);
	}

	virtual Holder* clone() const
	{
		return new Holder(held);
	}

public:

	ValueType held;

private: // intentionally left unimplemented

	Holder & operator=(const Holder &) = delete;

};



class Any
{
	PlaceHolder* content;

public:

	Any() noexcept : content(0) { }  //默认构造函数

	template<typename T>  //构造函数
	Any(const T & other) : content(new Holder<T>(other)) {};

	Any(const Any & other) : content(other.content ? other.content->clone() : 0) {} //拷贝构造函数


	template<typename T>  //拷贝赋值函数
	Any & operator=(T const & rhs)
	{
		delete content;
		content = new Holder<T>(rhs);
		return *this;
	}

	Any & swap(Any & rhs) noexcept
	{
		Any(rhs).swap(*this);
		return *this;
	}

	Any & operator=(const Any & rhs)
	{
		Any(rhs).swap(*this);
		return *this;
	}

	Any & operator=(Any && rhs) noexcept
	{
		rhs.swap(*this);
		Any().swap(rhs);
		return *this;
	}




public:   //普通成员函数

	const std::type_info & type() const {
		return content ? content->type() : typeid(void);
	}

	~Any() noexcept
	{
		delete content;
	}


	bool empty() { return !content; };


	void clear() noexcept
	{
		Any().swap(*this);
	}


	template<typename ValueType>
	bool is_type()
	{
		return typeid(ValueType).name() == content->type().name();
	}


	template<typename ValueType>
	ValueType cast_type()
	{
		if (!is_type<ValueType>()) throw bad_cast();

		return static_cast<Holder<ValueType>*> (content)->held;
	}


};