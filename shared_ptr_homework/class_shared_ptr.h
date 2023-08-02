#pragma once

template<class T>
class My_shared_ptr
{
    T* _ptr;
    int* count;

public:

    // Constructors

    My_shared_ptr() : _ptr(nullptr), count(new int(0)) {}
    My_shared_ptr(T* ptr) : _ptr(ptr), count(new int(1)) {}

    // Release method

    T* release()
    {
        T* releasedPtr = this->_ptr;
        if (this->_ptr != nullptr && --(*count) == 0)
        {
            delete this->count;
        }
        this->_ptr = nullptr;
        this->count = new int(0);
        return releasedPtr;
    }

    // Copy Constructor

    My_shared_ptr(const My_shared_ptr& other) : _ptr(other._ptr), count(other.count)
    {
        (*this->count)++;
    }
    
    // Reset method

    void reset()
    {
        if (this->_ptr != nullptr && --(*count) == 0)
        {
            delete this->_ptr;
            delete this->count;
        }
        this->_ptr = nullptr;
        this->count = new int(0);
    }

    // Get Method

    inline T* get() const { return this->_ptr; }

    // Destructor

    ~My_shared_ptr()
    {
        if (this->_ptr != nullptr && --(*count) == 0)
        {
            delete this->_ptr;
            delete this->count;
        }
    }

    // Bool overloading

    explicit operator bool() const
    {
        return this->_ptr != nullptr;
    }

    // Dereference

    T& operator*()
    {
        return *_ptr;
    }

    // Cout

    template<class T >
    friend ostream& operator<<(ostream& os, const My_shared_ptr<T>& ptr);
};

// Cout

template<class T >
ostream& operator<<(ostream& os, const My_shared_ptr<T>& ptr)
{
    os << *ptr.get();

    return os;
}