#ifndef __ARRAY_TYPE_DESCRIPTOR__
#define __ARRAY_TYPE_DESCRIPTOR__

#include <cstddef>

template <typename T>
class class_descriptor;

template <typename T>
class array_type_descriptor;

template <typename T, int N>
class array_inserter
{
	T* m_curr;
	T* m_end;
public:
	array_inserter(T (&t)[N])
	{
		m_curr = t;
		m_end = t + N;
	}
	bool ok()
	{
		return m_curr != m_end;
	}

	T& insert() 
	{
		*(m_curr++);
	}
};

template <typename T, int N>
class array_type_descriptor<T[N]>
{
public:
	array_inserter<T, N> begin_insert(T (&t)[N]) const
	{
		return array_inserter<T, N>(t);
	}

	size_t get_size(const T (&t)[N]) const
	{
		return N;
	}
};

template <typename T, int N>
class class_descriptor<T[N]>
{
public:
	typedef array_type_descriptor<T[N]> descriptor_t;
};

template <typename TWriter, typename T>
void dispatch_write_object(const array_type_descriptor<T>& desc,
							TWriter &writer, const T& t)
{
	writer.begin_array();
	auto size = desc.get_size(t);
	for (int n = 0; n < size; n++)
	{
		writer.begin_item();
		write_json(writer, t[n]);
		writer.end_item();
	}
	writer.end_array();
}

template <typename TReader, typename T>
void dispatch_read_object(const array_type_descriptor<T>& desc,
							TReader &reader, T& t)
{
	reader.enter_array();
	auto it = desc.begin_insert(t);
	if (it.ok() && !reader.is_end_array())
	{
		do {
			read_object(reader, it.insert());
			if (reader.is_end_array())
				break;
			reader.next_item();
		}while (it.ok());
	}
	reader.leave_array();
}
#endif /* __ARRAY_TYPE_DESCRIPTOR__ */
