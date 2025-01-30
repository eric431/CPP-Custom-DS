#pragma once

template<typename K, typename V>
class MyOpenAddressedHashMap
{
    struct Node
    {
        K key;
        V value;

        Node(K ky, V vl) : key(ky), value(vl){};
    };

    size_t hash(K key)
    {
        return static_cast<size_t>(key) % m_capacity;
    }

    public:
        MyOpenAddressedHashMap() : m_size(0), m_capacity(0) 
        {
            m_capacity = 10;
            m_hash_table = new Node<K, V>* [m_capacity];
        }

        // Copy constructors
        MyOpenAddressedHashMap(const MyOpenAddressedHashMap& map)
        {
            m_capacity = map.m_capacity;
            m_size = map.m_size;

            m_hash_map = map.m_hash_map;
        }

        // Copy Assignment
        MyOpenAddressedHashMap& operator=(const MyOpenAddressedHashMap& map)
        {
            m_capacity = map.m_capacity;
            m_size = map.m_size;

            m_hash_map = map.m_hash_map;
            return *this;
        }

        // Move constructors
        MyOpenAddressedHashMap(const MyOpenAddressedHashMap&& map)
        {
            m_capacity = map.m_capacity;
            m_size = map.m_size;

            m_hash_map = map.m_hash_map;            
        }

        // Move Assignment
        MyOpenAddressedHashMap& operator=(const MyOpenAddressedHashMap&& map)
        {
            if(this != &map)
            {
                delete m_hash_table;

                m_hash_table = map.hash_table;
                m_size = map.size;
                m_capacity = map.capacity;

                map.m_hash_table = nullptr;
            }
            return *this;
        }

        ~MyOpenAddressedHashMap()
        {
            delete m_hash_table;
        }

        void insert(const K& key, const V& value)
        {
            size_t hash_index {};
            if(++m_size > m_capacity)
            {
                m_capacity *= 2;
                Node<K, V>* tmp[m_capacity] {};

                for(size_t i{0}; i < m_hash_table.size(); ++i)
                {
                    int key = m_hash_table[i]->key;
                    hash_index = hash(key);

                    tmp[hash_index] = m_hash_table[i];
                }

                delete[] m_hash_table;
                m_hash_table = tmp;
                delete tmp;

            }

            hash_index = hash(key);
            while(m_hash_table[hash_index] != NULL 
                  && m_hash_table[hash_index]->key != key
                  && m_hash_table[hash_index]->key != -1)
            {
                hash_index++;
                hash_index %= m_capacity;
            }

            Node<K, V>* entry = new Node(key, value);

            m_hash_table[hash_index] = entry;
        }

        void delete_key(const K& key)
        {
            size_t hash_index = hash(key);

            while(m_hash_map[hash_index] != NULL)
            {
                if(m_hash_table[hash_index]->key == key)
                {
                    m_hash_table[hash_index] = m_dummy;

                    --size;
                }
                ++hash_index;
                hash_index %= m_capacity;
            }
        }

        V operator[](const K& key)
        {
            size_t hashIndex = hash(key);
            return m_hash_table[hashIndex];
        }

        size_t size()
        {
            return m_size;
        }

        size_t capacity()
        {
            return m_capacity;
        }

    private:
        size_t m_size {};
        size_t m_capacity {};
        Node<K, V>* m_hash_table[] {};
        Node<K, V> m_dummy {};
};