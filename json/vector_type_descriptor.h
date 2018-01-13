#ifndef __VECTOR_TYPE_DESCRIPTOR__
#define __VECTOR_TYPE_DESCRIPTOR__

#include <vector>
#include "array_type_descriptor.h"
template <typename T>
class vector_inserter
{
	std::vector<T>& m_vec;
public:
	vector_inserter(std::vector<T>& vec) : m_vec(vec)
	{
		vec.clear();
	}

	bool ok()
	{
		return true;
	}

	T& insert() 
	{
		m_vec.emplace_back();
		return m_vec.back();
	}
};

template<typename T>
class array_type_descriptor<std::vector <T>>
{
public:
	vector_inserter<T> begin_insert(std::vector<T>& vec) const 
	{
		return vector_inserter<T>(vec);
	}
	
	size_t get_size(const std::vector<T>& vec) const 
	{
		return vec.size();	
	}
};

template <typename T>
class class_descriptor <std::vector<T>>
{
public:
	typedef array_type_descriptor<std::vector<T>> descriptor_t;
};

#endif /* __VECTOR_TYPE_DESCRIPTOR__ */