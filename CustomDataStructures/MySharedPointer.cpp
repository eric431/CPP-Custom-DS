#pragma once

template<typename T>
class SharedPointer
{
    public:
        SharedPointer() : m_ptr(nullptr), m_count(new uint(0))
        {
        }

        SharedPointer(T* ptr) : m_ptr(ptr), m_count(new uint(1))
        {
        }

        // copy constructor 
        SharedPointer(const SharedPointer<T>& ptr)
        {
            m_ptr = ptr.m_ptr;
            m_count = ptr.m_count;
            ++(*m_count);
        }

        // copy assignment
        SharedPointer& operator=(const SharedPointer<T>& ptr)
        {
            m_ptr = ptr.m_ptr;
            m_count = ptr.m_count;
            ++(*m_count);
        }

        // move constructor
        SharedPointer(const SharedPointer<T>&& ptr)
        {
            m_ptr = ptr;
            m_count = ptr.m_count;

            ptr.m_ptr = ptr.m_count = nullptr;
        }

        // improve cleanup later
        SharedPointer& operator=(const SharedPointer<T>&& ptr)
        {
            m_ptr = ptr.m_ptr;
            m_count = ptr.m_count;

            ptr.m_ptr = ptr.m_count = nullptr;
        }

        T* get();

        T& operator*()
        {
            return *m_ptr;
        }

        T* operator->()
        {
            return m_ptr;
        }

        uint get_count() const
        {
            return *(m_count);
        }

        ~SharedPointer()
        {
            --(*m_count);

            if((*m_count) == 0)
            {
                delete m_count;

                if(m_ptr)
                    delete m_ptr;
            }
        }

    private:
        uint* m_count{nullptr};
        T* m_ptr{nullptr};
};