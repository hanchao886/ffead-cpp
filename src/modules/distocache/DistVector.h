/*
	Copyright 2009-2013, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (const the& "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
 * DistVector.h
 *
 *  Created on: 04-Apr-2013
 *      Author: sumeetc
 */

#ifndef DISTVECTOR_H_
#define DISTVECTOR_H_
#include "PooledDistoCacheConnectionFactory.h"
#include "BinarySerialize.h"

template <class T> class DistVector {
	std::string cacheKey;
	DistoCacheClientUtils* cl;
public:
	DistVector(const std::string& cacheKey)
	{
		this->cacheKey = cacheKey;
		cl = PooledDistoCacheConnectionFactory::getConnection();
		try {
			cl->allocate(cacheKey, "vector");
		} catch(const std::string& err) {
			if(err!="Entry already exists") {
				throw err;
			}
		}
	}
	void push_back(const T& t)
	{
		std::string serValue = BinarySerialize::serialize<T>(t);
		cl->addCollectionEntry(cacheKey, serValue);
	}
	void insert(const T& t, const int& position)
	{
		std::string serValue = BinarySerialize::serialize<T>(t);
		cl->insert(cacheKey, serValue, position);
	}
	void insert(const T& t, const int& position, const int& repetition)
	{
		std::string serValue = BinarySerialize::serialize<T>(t);
		cl->insert(cacheKey, serValue, position, repetition);
	}
	T at(const int& position)
	{
		std::string serValue = cl->getCollectionEntryAt(cacheKey, position);
		return BinarySerialize::unserialize<T>(serValue);
	}
	T front()
	{
		std::string serValue = cl->getFrontValue(cacheKey);
		return BinarySerialize::unserialize<T>(serValue);
	}
	T back()
	{
		std::string serValue = cl->getBackValue(cacheKey);
		return BinarySerialize::unserialize<T>(serValue);
	}
	void erase(const int& position)
	{
		cl->removeCollectionEntryAt(cacheKey, position);
	}
	size_t size()
	{
		return cl->size(cacheKey);
	}
	bool isEmpty()
	{
		return cl->isEmpty(cacheKey);
	}
	void clear()
	{
		cl->clear(cacheKey);
	}
	void free()
	{
		cl->deallocate(cacheKey);
	}
	virtual ~DistVector()
	{
		PooledDistoCacheConnectionFactory::releaseConnection(cl);
	}

	class iterator {
			friend class DistVector;
			int position;
			std::string cacheKey;
			DistoCacheClientUtils* cl;
			iterator(std::string cacheKey, DistoCacheClientUtils* cl)
			{
				this->cacheKey = cacheKey;
				this->cl = cl;
			}
		public:
			iterator()
			{
				position = -1;
			}
			T get()
			{
				if(position>=0)
				{
					std::string serValue = cl->getCollectionEntryAt(cacheKey, position);
					return BinarySerialize::unserialize<T>(serValue);
				}
				else
				{
					throw "Position value is less than 0";
				}
			}
			void set(T v)
			{
				if(position>=0)
				{
					std::string serValue = BinarySerialize::serialize<T>(v);
					cl->setCollectionEntryAt(cacheKey, position, serValue);
				}
				else
				{
					throw "Position value is less than 0";
				}
			}
			iterator& operator++()
			{
				position++;
				return *this;
			}
			iterator& operator+=(int incValue)
			{
				position += incValue;
				return *this;
			}
			iterator operator++(int)
			{
				iterator temp;
				temp.position = position;
				++position;
				return temp;
			}
			iterator& operator--()
			{
				position--;
				return *this;
			}
			iterator& operator-=(int incValue)
			{
				position -= incValue;
				return *this;
			}
			iterator operator--(int)
			{
				iterator temp;
				temp.position = position;
				--position;
				return temp;
			}
			bool operator!=(const iterator& b)
			{
				return position!=b.position;
			}
		};

	iterator begin()
	{
		iterator it(const cacheKey&, const cl&);
		it.position = 0;
		return it;
	}
	iterator end()
	{
		iterator it(cacheKey, cl);
		it.position = size();
		return it;
	}
};

#endif /* DISTVECTOR_H_ */
