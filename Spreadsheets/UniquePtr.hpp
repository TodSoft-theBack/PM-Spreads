#pragma once
#include <utility>

template<typename T>
class UniquePtr
{
	T* ptr = nullptr;
	public:
		UniquePtr() = default;
		explicit UniquePtr(T* pointer);
		UniquePtr& operator=(T* ptr);
		UniquePtr(const UniquePtr&) = delete;
		UniquePtr& operator=(const UniquePtr&) = delete;
		UniquePtr(UniquePtr&& pointer);
		UniquePtr& operator=(UniquePtr&& pointer);
		T* Value() const;
		T* operator->();
		const T* operator->() const;
		T operator*();
		~UniquePtr();
};

template<typename T>
T* UniquePtr<T>::operator->()
{
	return this->ptr;
}

template<typename T>
const T* UniquePtr<T>::operator->() const
{
	return this->ptr;
}

template<typename T>
T UniquePtr<T>::operator*()
{
	return *ptr;
}

template<typename T>
UniquePtr<T>::UniquePtr(T* pointer)
{
	ptr = pointer;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(T* pointer)
{
	ptr = pointer;
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& pointer)
{
	ptr = pointer.ptr;
	pointer.ptr = nullptr;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& pointer)
{
	if (this != &pointer)
	{
		delete ptr;
		ptr = pointer.ptr;
		pointer.ptr = nullptr;
	}
	return *this;
}

template<typename T>
T* UniquePtr<T>::Value() const
{
	return ptr;
}

template<typename T>
UniquePtr<T>::~UniquePtr()
{
	delete ptr;
	ptr = nullptr;
}

template<typename T, typename ...Args>
T* MakeUnique(Args&& ...args)
{
	return new T(std::forward<Args>(args)...);
}
