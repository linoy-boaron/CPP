//
// Created by Linoy on 12/01/2020.
//

#ifndef UNTITLED19_HASHMAP_HPP
#define UNTITLED19_HASHMAP_HPP

using namespace std;

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <bitset>
#include <list>

/**
 * key not found exception
 */
class KeyNotFound : public std::runtime_error
{
public:
    /**
     * exception constructor
     */
    KeyNotFound() : std::runtime_error("Key not found in map")
    {}
};

/**
 * vectors size are not the same exception
 */
class VectorsSizeNotMatch : public std::runtime_error
{
public:
    /**
     * exception constructor
     */
    VectorsSizeNotMatch() : std::runtime_error(
            "Values size vector and Keys size vectors are not the same")
    {}
};

template<typename keyT, typename valueT>
#define HIGHER_LIMITATION 0.75
#define LOWER_LIMITATION 0.25
#define INITIAL_CAPACITY 16
#define RESIZE_FACTOR 2

/**
 * hash map implementation
 * @tparam keyT
 * @tparam valueT
 */
class HashMap
{

private:
    int _capacityLimitation = INITIAL_CAPACITY;
    list <pair<keyT, valueT>> *_hashNodes;

    /**
     * insert all elements from input to hash map
     * @param keys
     * @param values
     */
    void _insertNodes(const vector<keyT> &keys, const vector<valueT> &values)
    {
        while ((double) set<keyT>(keys.begin(), keys.end()).size() / _capacityLimitation >
               HIGHER_LIMITATION)
        {
            _capacityLimitation = _capacityLimitation * RESIZE_FACTOR;
        }

        while ((double) set<keyT>(keys.begin(), keys.end()).size() / _capacityLimitation <
               LOWER_LIMITATION && _capacityLimitation > RESIZE_FACTOR)
        {
            _capacityLimitation = _capacityLimitation / RESIZE_FACTOR;
        }

        _hashNodes = new list<pair<keyT, valueT>>[_capacityLimitation];

        for (int i = 0; i < _capacityLimitation; i++)
        {
            _hashNodes[i] = list<pair<keyT, valueT >>();
        }

        auto key = keys.begin();
        auto value = values.begin();

        while (key != keys.end() and value != values.end())
        {
            _insertNode(*key, *value);
            key++;
            value++;
        }
    };

    /**
     * rehash hash map with new capacity
     * @param oldCapacity
     */
    void _reHash(const int &oldCapacity)
    {
        list <pair<keyT, valueT>> *newMap = new list<pair<keyT, valueT>>[_capacityLimitation];

        for (int i = 0; i < oldCapacity; i++)
        {
            for (auto const &node: _hashNodes[i])
            {
                newMap[_hashKey(node.first)].push_back({node.first, node.second});
            }
        }
        delete[] _hashNodes;
        _hashNodes = newMap;
    }

    /**
     * insert node to hash map. If key already exist - update element.
     */
    void _insertNode(const keyT &key, const valueT &value)
    {
        if (this->containsKey(key))
        {
            this->erase(key);
        }
        _hashNodes[_hashKey(key)].push_back({key, value});
    }

    /**
     *
     * @param key
     * @return calculate index to hash map
     */
    int _hashKey(const keyT &key) const
    {
        int newIndex = std::hash<keyT>()(key);
        return newIndex & (capacity() - 1);
    }

    /**
     * update the lists to be the first/end iterators at every index in hash map
     * @param firstIters
     * @param endIters
     */
    void _updateFirstAndEndIters(list<typename list<pair<keyT, valueT>>::iterator> &firstIters,
                                 list<typename list<pair<keyT, valueT>>::iterator> &endIters) const
    {
        int endIndex = 0;
        for (int i = 0; i < _capacityLimitation; i++)
        {
            if (_hashNodes[i].size() > 0)
            {
                firstIters.push_back(_hashNodes[i].begin());
                endIters.push_back(--_hashNodes[i].end());
                endIndex = i;
            }
        }
        if (endIndex != 0)
        {
            endIters.push_back(_hashNodes[endIndex].end());
        }
        else
        {
            endIters.push_back(_hashNodes[_capacityLimitation - 1].end());
        }
    }

public:
    /**
     * iterator implementation to hash map
     */
    class const_iterator
    {
    public:
        typedef int difference_type;
        typedef pair<keyT, valueT> value_type;
        typedef const_iterator self_type;
        typedef pair<keyT, valueT> &reference;
        typedef typename list<pair<keyT, valueT>>::iterator pointer;
        typedef std::forward_iterator_tag iterator_category;

        /**
         * constructor
         * @param ptr
         * @param endPtrs
         * @param firstPtrs
         */
        const_iterator(pointer ptr, const list <pointer> &endPtrs,
                       const list <pointer> &firstPtrs) : _ptr(ptr)
        {
            this->_endPtrs = endPtrs;
            this->_firstPtrs = firstPtrs;
        }

        /**
         * move operator to the next position
         * @return
         */
        self_type &operator++()
        {
            bool isInEnd = false;
            self_type &i = *this;

            if (_ptr == (*(--(--_endPtrs.end()))))
            {
                _ptr = *(--_endPtrs.end());
                return i;
            }

            auto iterEnd = _endPtrs.begin();
            auto iterBegin = _firstPtrs.begin();
            while (iterEnd != _endPtrs.end() && iterBegin != _firstPtrs.end())
            {
                if (*iterEnd == _ptr)
                {
                    iterBegin++;
                    _ptr = *iterBegin;
                    isInEnd = true;
                    break;
                }
                ++iterBegin;
                ++iterEnd;
            }

            if (!isInEnd)
            {
                _ptr++;
            }
            return i;
        }

        /**
         * move operator to the next position
         * @return
         */
        const self_type operator++(int)
        {
            self_type temp = *this;
            this->operator++();
            return temp;
        }

        /**
         * get reference to pointer
         * @return
         */
        reference operator*()
        { return *_ptr; }

        /**
         * get reference to pointer - const
         */
        reference operator*() const
        { return *_ptr; }

        /**
         * get the current pointer
         * @return
         */
        pointer operator->()
        { return _ptr; }

        /**
         * get the current const pointer
         * @return
         */
        pointer operator->() const
        { return _ptr; }

        /**
         *
         * @param rhs
         * @return true if pointers are the same
         */
        bool operator==(const self_type &rhs) const
        { return _ptr == rhs._ptr; }

        /**
         *
         * @param rhs
         * @return true if pointers are not the same
         */
        bool operator!=(const self_type &rhs) const
        { return _ptr != rhs._ptr; }

    private:
        pointer _ptr;
        list <pointer> _endPtrs;
        list <pointer> _firstPtrs;
    };


    /**
     * defualt constructor
     */
    HashMap() : _hashNodes(new list<pair<keyT, valueT>>[_capacityLimitation])
    {
        for (int i = 0; i < _capacityLimitation; i++)
        {
            _hashNodes[i] = list<pair<keyT, valueT >>();
        }
    };

    /**
     * constructor with vector of elements as input
     * @param keys
     * @param values
     */
    HashMap(const vector<keyT> &keys, const vector<valueT> &values)
    {
        if (keys.size() != values.size())
        {
            throw VectorsSizeNotMatch();
        }

        _insertNodes(keys, values);

    }

    /**
     * copy constructor
     * @param toCopy
     */
    HashMap(const HashMap &toCopy) : _capacityLimitation(toCopy._capacityLimitation)
    {
        this->_hashNodes = new list<pair<keyT, valueT>>[toCopy._capacityLimitation];
        for (int i = 0; i < _capacityLimitation; i++)
        {
            _hashNodes[i] = toCopy._hashNodes[i];
        }
    };

    /**
     * destructor
     */
    ~HashMap()
    {
        clear();
        delete[] _hashNodes;
    };

    /**
     *
     * @return the number of elements in hash map
     */
    int size() const
    {
        int size = 0;
        for (int i = 0; i < _capacityLimitation; i++)
        {
            size += _hashNodes[i].size();
        }
        return size;
    };

    /**
     *
     * @return the current capacity of the hash map
     */
    int capacity() const
    {
        return _capacityLimitation;
    }

    /**
     *
     * @return true if hash map is empty, elsewhere false
     */
    bool empty() const
    {
        return this->size() == 0;
    }

    /**
     * insert element to hash map
     * @param key
     * @param value
     * @return true if inserted, elsewhere false
     */
    bool insert(const keyT &key, const valueT &value)
    {
        if (containsKey(key))
        {
            return false;
        }

        if (this->getLoadFactor() >= HIGHER_LIMITATION)
        {
            _capacityLimitation *= RESIZE_FACTOR;
            _reHash(_capacityLimitation / RESIZE_FACTOR);
        }
        _hashNodes[_hashKey(key)].push_back({key, value});

        return true;
    }

    /**
     * insert function for const
     * @param key
     * @param value
     * @return
     */
    bool insert(const keyT &key, const valueT &value) const
    {
        return true;
    }

    /**
     *
     * @param key
     * @return true if key exist in hash map, elsewhere false
     */
    bool containsKey(const keyT &key) const
    {
        for (auto const &node: _hashNodes[_hashKey(key)])
        {
            if (node.first == key)
            {
                return true;
            }
        }
        return false;
    }

    /**
     *
     * @param key
     * @return reference to value at key position in hash map
     *
     */
    valueT &at(const keyT &key) const
    {
        for (auto &node: _hashNodes[_hashKey(key)])
        {
            if (node.first == key)
            {
                return node.second;
            }
        }
        throw KeyNotFound();
    }

    /**
     * remove element in hash map
     * @param key
     * @return
     */
    bool erase(const keyT &key)
    {
        if (!containsKey(key))
        {
            return false;
        }

        list <pair<keyT, valueT>> &list = _hashNodes[_hashKey(key)];
        list.remove(pair<keyT, valueT>(key, at(key)));

        if (this->getLoadFactor() < LOWER_LIMITATION)
        {
            _capacityLimitation /= RESIZE_FACTOR;
            _reHash(_capacityLimitation * RESIZE_FACTOR);
        }
        return true;
    }

    /**
     *
     * @return the load factor of the hash map
     */
    double getLoadFactor() const
    {
        return (double) size() / capacity();
    }

    /**
     *
     * @param key
     * @return the bucket size for hash(key) index
     */
    int bucketSize(const keyT &key) const
    {
        if (!containsKey(key))
        {
            throw KeyNotFound();
        }
        return _hashNodes[_hashKey(key)].size();
    }

    /**
     *
     * @param key
     * @return the bucket index
     */

    int bucketIndex(const keyT &key) const
    {
        if (!containsKey(key))
        {
            throw KeyNotFound();
        }
        return _hashKey(key);
    }

    /**
     * clear all elements in map
     */
    void clear()
    {
        for (int i = 0; i < _capacityLimitation; i++)
        {
            _hashNodes[i].clear();
        }
    }

    /**
     * the = operator
     * @param other
     * @return other hash map copied to this
     */
    HashMap &operator=(const HashMap &other)
    {
        if (this != &other)
        {
            delete[] this->_hashNodes;

            this->_capacityLimitation = other._capacityLimitation;
            this->_hashNodes = new list<pair<keyT, valueT>>[other._capacityLimitation];
            for (int i = 0; i < _capacityLimitation; i++)
            {
                _hashNodes[i] = other._hashNodes[i];
            }
        }
        return *this;
    }

    /**
     *
     * @param key
     * @return the value at key position. If not exists add the key to the hash map
     */
    valueT &operator[](const keyT &key)
    {
        if (!containsKey(key))
        {
            insert(key, valueT());
        }
        return at(key);
    }

    /**
     *
     * @param key
     * @return the value at key position. If not exists add the key to the hash map
     */
    const valueT &operator[](const keyT &key) const
    {
        if (!containsKey(key))
        {
            insert(key, valueT());
        }
        return at(key);
    }

    /**
     * if hash maps are different return true, elsewhere false
     */
    bool operator!=(const HashMap &other) const
    {
        return !(this->operator==(other));
    }

    /**
     * the equality operator
     * @param other
     * @return if hash maps are the same
     */
    bool operator==(const HashMap &other) const
    {
        for (int i = 0; i < _capacityLimitation; i++)
        {
            for (auto const &node : _hashNodes[i])
            {
                if (!other.containsKey(node.first))
                {
                    return false;
                }
                if (other.containsKey(node.first) && other.at(node.first) != node.second)
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * begin iterator to hashmap
     * @return
     */
    const_iterator begin() const
    {
        list<typename list<pair<keyT, valueT>>::iterator> firstIters = {}, endIters = {};
        _updateFirstAndEndIters(firstIters, endIters);

        for (int i = 0; i < _capacityLimitation; i++)
        {
            if (_hashNodes[i].size() > 0)
            {
                return const_iterator(_hashNodes[i].begin(),
                                      endIters, firstIters);
            }
        }
        return const_iterator(_hashNodes[_capacityLimitation - 1].end(),
                              endIters, firstIters);
    }

    /**
     * end iterator to hash map
     * @return
     */
    const_iterator end() const
    {
        list<typename list<pair<keyT, valueT>>::iterator> firstIters, endIters;
        _updateFirstAndEndIters(firstIters, endIters);
        for (int i = _capacityLimitation - 1; i != 0; i--)
        {
            if (_hashNodes[i].size() > 0)
            {
                return const_iterator(_hashNodes[i].end(), endIters, firstIters);
            }
        }
        return const_iterator(_hashNodes[_capacityLimitation - 1].end(), endIters, firstIters);
    }

    /**
     * begin iterator to hash map
     * @return
     */
    const const_iterator cbegin() const
    {
        return begin();
    }

    /**
     * end iterator to hash map
     * @return
     */
    const const_iterator cend() const
    {
        return end();
    }
};

#endif //UNTITLED19_HASHMAP_HPP
