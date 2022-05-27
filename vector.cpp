#include <iostream>

template<typename T>
class Vector
{
private:
    size_t cap;
    size_t size;
    T* buf;

public:
    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector(size_t,T);
    Vector(size_t);
    Vector(std::initializer_list<T> value_list);
    Vector& operator= (const Vector&);
    Vector& operator= (Vector&&);
    T& operator[] (size_t);
    const T& operator[] (size_t)const;
    bool empty()const;
    size_t size_of();
    size_t capacity();
    void push_back(T);
    void pop_back();
    void resize(size_t);
    void clear();
    void shrink_to_fit();
    ~Vector();    
};

int main()
{
    return 0;
}

template <typename T>
Vector<T>::Vector(): cap{1},size{},buf{}
{}

template <typename T>
Vector<T>::Vector(const Vector<T>& object): cap{object.cap}, size{object.size}
{
    buf = new T[cap];
    for (int i = 0; i < cap; i++)
    {
        buf[i] = object.buf[i];
    }  
}

template <typename T>
Vector<T>::Vector(Vector&& tmp): cap{tmp.cap}, size{tmp.size},buf{tmp.buf}
{
    tmp.cap = 0;
    tmp.size = 0;
    tmp.buf = nullptr;
}

template <typename T>
Vector<T>::Vector(size_t count,T element):cap{count},size{cap},buf{new T[cap]}
{
    if(count > 0)
    {
        for (int i = 0; i < size; i++)
        {
            buf[i] = element;
        } 
    }
    else
    {
        std::cout << "Count must be natural number\n" << std::endl;
    }
}

template <typename T>
Vector<T>::Vector(size_t count):cap{count},size{cap}
{
    if(count > 0)
    {
        buf = new T[size];
    }
    else
    {
        std::cout << "Count must be natural number\n" << std::endl;
    }    
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> value_list): cap{1}, size{}
{
    if (value_list.size())
    {
        cap = value_list.size();
        size = cap;
        buf = new T(cap);
        int count = 0;
        for (auto it = value_list.begin(); it != value_list.end(); ++it,++count)
        {
            buf[count] = *it;
        }   
    } 
}

template <typename T>
Vector<T>::~Vector()
{
    if (buf)
    {
        delete [] buf;
    }    
}

template <typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& object)
{
    if(this != &object)
    {
        if(object.buf)
        {
            this->cap = object.cap;
            this->size = object.size;
            this->buf = new T[size];
            for (int i = 0; i < size; i++)
            {
                this->buf[i] = object.buf[i];
            }
        }         
    } 
    return *this;    
}

template <typename T>
T& Vector<T>::operator[] (size_t index)
{
    return buf[index];
}

template <typename T>
const T& Vector<T>::operator[] (size_t index)const
{
    return buf[index];
}

template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& object)
{
    if(!object.empty())
    {
        this->cap = object.cap;
        this->size = object.size;
        T* tmp = this->buf;
        this->buf = object.buf;
        object.buf = tmp;
        tmp = nullptr;
    }
    return *this;
}

template <typename T>
bool Vector<T>::empty()const
{
    bool test = false;
    if (!buf)
    {
        test = true;
        return test;
    }
    return test;   
}

template <typename T>
size_t Vector<T>::size_of()
{
    return this->size;
}

template <typename T>
size_t Vector<T>::capacity()
{
    return this->cap;
}

template <typename T>
void Vector<T>::push_back(T element)
{
    if(this->empty())
    {
        buf = new T[1];
    }
    ++size;
    if(size > cap)
    {
        cap *= 2;
        T* tmp = new T[cap];
        for (int i = 0; i < size; i++)
        {
            tmp[i] = buf[i];
        }
        delete [] buf;
        buf = tmp;
        tmp = nullptr;
    }
    buf[size] = element;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (size)
    {
        --size;
    }   
}

template <typename T>
void Vector<T>::resize(size_t new_cap)
{
    if (new_cap >= size)
    {
        cap = new_cap;
        if(this->empty())
        {
            buf = new T[cap];
        }
        else
        {
            T* tmp = new T[cap];
            for (int i = 0; i < size; i++)
            {
                tmp[i] = buf[i];
            }
            delete [] buf;
            buf = tmp;
            tmp = nullptr;           
        }    
    }    
}

template <typename T>
void Vector<T>::clear()
{
    if(!buf)
    {
        size = 0;
        cap = 1;
        delete [] buf;
    }
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if(this->empty())
    {
        if (cap != size)
        {
            cap = size;
            T* tmp = new T[cap];
            for (int i = 0; i < size; i++)
            {
                tmp[i] = buf[i];
            }
            delete [] buf;
            buf = tmp;
            tmp = nullptr;   
        }   
    }
}
