#pragma once
#include <iostream>
#include <sstream>

template<typename T>
class Vector
{
    static const size_t DEFAULT_CAPACITY = 8;
    T* collection = nullptr;
    size_t count = 0;
    size_t capacity = DEFAULT_CAPACITY;

    private:
        void CopyMemberData(const Vector<T>& vector);
        void MoveMemberData(Vector<T>&& vector);
        void FreeMemberData();
        void Resize(size_t size);

    public: 
        Vector();
        Vector(size_t capacity);
        Vector(size_t count, const T& defaultValue);
        Vector(const T* collection, size_t count);
        Vector(const Vector<T>& vector);
        Vector(Vector<T>&& vector);

        size_t Count() const;
        bool Contains(const T& element) const;
        const T* Collection() const;
        std::stringstream ToString() const;

        const Vector<T>& operator=(const Vector<T>& vector);
        const Vector<T>& operator=(Vector<T>&& vector);
        const T& operator[] (unsigned index) const;
        T& operator[] (unsigned index);

        void PushBack(const T& item);
        void PushBack(T&& item);
        int IndexOf(const T& item, unsigned startIndex) const;
        int IndexOf(const T& item) const;
        int LastIndexOf(const T& item, unsigned startIndex) const;
        int LastIndexOf(const T& item) const;
        void InsertAt(unsigned index, const T& item);
        void InsertAt(unsigned index, T&& item);
        void RemoveAt(unsigned index);
        void RemoveBack();
        void Clear();

        template<typename V>
        friend std::ostream& operator <<(std::ostream& stream, const Vector<V>& vector);
        ~Vector();
};

template<typename T>
void Vector<T>::CopyMemberData(const Vector<T>& vector)
{
    capacity = vector.capacity;
    count = vector.count;
    collection = new T[capacity];
    for (size_t i = 0; i < count; i++)
        collection[i] = vector.collection[i];      
}

template<typename T>
void Vector<T>::MoveMemberData(Vector<T>&& vector)
{
    this->capacity = vector.capacity;
    this->count = vector.count;
    this->collection = vector.collection;
    vector.collection = nullptr;
}

template<typename T>
void Vector<T>::FreeMemberData()
{
    delete[] collection;
    collection = nullptr;
}

template<typename T>
void Vector<T>::Resize(size_t size)
{
    if (size == 0)
    {
        collection = nullptr;
        count = 0;
        capacity = DEFAULT_CAPACITY;
        return;
    }
    capacity = size;
    T* newCollection = new T[capacity];
    for (size_t i = 0; i < count; i++)
        newCollection[i] = collection[i];                
    FreeMemberData();
    collection = newCollection;
}

template<typename T>
Vector<T>::Vector()
{
    collection = new T[capacity];
}

template<typename T>
Vector<T>::Vector(size_t capacity)
{
    this->capacity = capacity;
    count = 0;
    collection = new T[capacity];
}

template<typename T>
Vector<T>::Vector(size_t capacity, const T& defaultValue)
{  
    this->capacity = capacity;
    this->count = 0;
    collection = new T[capacity];
    for (size_t i = 0; i < count; i++)
        collection[i] = defaultValue;          
}

template<typename T>
Vector<T>::Vector(const T* collection, size_t count)
{
    capacity = count * 2;
    this->count = count;
    this->collection = new T[capacity];
    for (size_t i = 0; i < count; i++)
        this->collection[i] = collection[i];      
}

template<typename T>
Vector<T>::Vector(const Vector<T>& vector)
{
    CopyMemberData(vector);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& vector)
{
    MoveMemberData(std::move(vector));
}


template<typename T>
size_t Vector<T>::Count() const
{
    return count;
}

template<typename T>
bool Vector<T>::Contains(const T& element) const
{
    for(size_t i = 0; i < count; i++)
        if(collection[i] == element)
            return true;
    return false;
}

template<typename T>
const T* Vector<T>::Collection() const
{
    return collection;
}

template<typename T>
std::stringstream Vector<T>::ToString() const
{
    std::stringstream stream;
    stream << *this;
    return stream;
}

template<typename T>
const Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
{
    if (this != &vector)
    {
        FreeMemberData();
        CopyMemberData(vector);
    }
    return *this;
}

template<typename T>
const Vector<T>& Vector<T>::operator=(Vector<T>&& vector)
{
    if (this != &vector)
    {
        FreeMemberData();
        MoveMemberData(std::move(vector));
    }
    return *this;
}

template<typename T>
const T& Vector<T>::operator[] (unsigned index) const
{
    if (index >= capacity)
        throw std::runtime_error("Index was outside of the bounds of the vector!");
    
    return collection[index];
}

template<typename T>
T& Vector<T>::operator[] (unsigned index)
{
    if (index >= capacity)
        throw std::runtime_error("Index was outside of the bounds of the vector!");
    
    return collection[index];
}

template<typename T>
void Vector<T>::PushBack(const T& item)
{
    if (count == capacity)
        Resize(capacity * 2);
    
    collection[count++] = item;
}

template<typename T>
void Vector<T>::PushBack(T&& item)
{
    if (count == capacity)
        Resize(capacity * 2);
    
    collection[count++] = std::move(item);
}

template<typename T>
inline int Vector<T>::IndexOf(const T& item, unsigned startIndex) const
{
    int index = -1;
    if (startIndex >= count)
        throw std::runtime_error("Invalid index");
    for (int i = startIndex; i < count; i++)
        if (operator[](i) == item)
            return i;
    return index;
}

template<typename T>
inline int Vector<T>::IndexOf(const T& item) const
{
    int index = -1;
    for (int i = 0; i < count; i++)
        if (operator[](i) == item)
            return i;
    return index;
}

template<typename T>
inline int Vector<T>::LastIndexOf(const T& item, unsigned startIndex) const
{
    int index = -1;
    if (startIndex >= count)
        throw std::runtime_error("Invalid index");
    for (int i = startIndex; i >= 0; i--)
        if (operator[](i) == item)
            return i;
    return index;
}

template<typename T>
inline int Vector<T>::LastIndexOf(const T& item) const
{
    int index = -1;
    for (int i = count - 1; i >= 0; i--)
        if (operator[](i) == item)
            return i;
    return index;
}

template<typename T>
void Vector<T>::InsertAt(unsigned index, const T& item)
{
    if (index >= count)
        throw std::runtime_error("Index was outside of the bounds of the vector!");
    if (count == capacity)
        Resize(capacity * 2);
    
    for (int i = count; i > index; i--)
        collection[i] = collection[i - 1];
    count++;
    collection[index] = item;
}

template<typename T>
void Vector<T>::InsertAt(unsigned index, T&& item)
{
    if (index >= count)
        throw std::runtime_error("Index was outside of the bounds of the vector!");
    
    if (count == capacity)
        Resize(capacity * 2);     
    for (int i = count; i > index; i--)
        collection[i] = collection[i - 1];
    
    count++;
    collection[index] = std::move(item);
}

template<typename T>
void Vector<T>::RemoveAt(unsigned index)
{
    if (index >= count)
        throw 0;
    if (count <= capacity / 4)
        Resize(capacity / 2);
    for (unsigned i = index; i < count - 1; i++)
        collection[i] = collection[i+1];
    count--;
}

template<typename T>
void Vector<T>::RemoveBack()
{
    if (count <= capacity / 4)
        Resize(capacity / 2);  
    count--;
}

template<typename T>
void Vector<T>::Clear()
{
    count = 0;
}

template<typename V>
std::ostream& operator<<(std::ostream& stream, const Vector<V>& vector)
{
    stream <<"{ ";
    for (unsigned i = 0; i < vector.count; i++)
        stream << vector[i] << (i != vector.count - 1 ? ", ":"");
    stream <<" }";
    return stream;
}

template<typename T>
Vector<T>::~Vector()
{
    FreeMemberData();
}
