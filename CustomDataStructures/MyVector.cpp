#pragma once
#include<iostream>

template<typename T>
class MyVector
{
    T *m_data[];
    size_t m_size;
    size_t m_capacity;

    public:
        MyVector()
        : m_data(nullptr), m_size(0), m_capacity(0);

        // copy constructor
        MyVector(const MyVector& vec)
        {
            m_data = vec.m_data;
            m_size = vec.m_size;
            m_capacity = vec.m_capacity;
        }

        // copy assignment 
        MyVector& operator=(const MyVector& vec)
        {
            m_data = vec.m_data;
            m_size = vec.m_size;
            m_capacity = vec.m_capacity; 

            return *this;          
        }

        // move constructor
        MyVector(const MyVector&& vec)
        : m_data(vec.m_data),
        m_size(vec.m_size),
        m_capacity(vec.m_capacity)
        {}

        // move assignment
        MyVector& operator=(const MyVector&& vec)
        {
            if(this != &vec)
            {
                delete m_data;

                m_data = vec.data;
                m_size = vec.size;
                m_capacity = vec.capacity;

                vec.data = nullptr;
            }
            return *this;
        }

        ~MyVector()
        {
            delete[] m_data;
        }

        // push_back
        void push_back(T el)
        {
            if(m_capacity == m_size)
            {
                // double the capacity of the vector
                m_capacity *= 2;
                T *new_data = new T[m_capacity];

                for(size_t i{0}; i < m_size; ++i) new_data[i] = data[i];

                delete[] data;
                data = new_data;
            }

            m_data[m_size++] = el;
        }

        // pop_back
        void pop_back()
        {
            --size;
        }

        // back
        T back()
        {
            return m_data[m_size];
        }

        // front
        T front()
        {
            return m_data[0];
        }

        // clear
        void erase(size_t idx)
        {
            for(auto i{idx}; i < m_size - 1; ++i)
            {
                m_data[i] = m_idx[i + 1];
            }
            --m_size;
        }

        // capacity
        size_t capacity()
        {
            return m_capacity;
        }

        // size
        size_t size()
        {
            return m_size;
        }

        // erase
        void clear()
        {
            delete[] m_data;
        }

        // []
        T& operator[](size_t i)
        {
            return m_data[i];
        }

        // at
        T at(size_t i)
        {
            if(i < m_size)
            {
                return m_data[i];
            }

            std::cerr << "Index is not within range";
        }
};