#ifndef __MAP_TYPE_DESCRIPTOR__
#define __MAP_TYPE_DESCRIPTOR__

#include <map>
// #include <string>
template <typename T>
class class_descriptor;

template <typename T>
class map_type_descriptor
{
};

template <typename T>
class class_descriptor<std::map<std::string, T>>
{
	public:
		typedef map_type_descriptor<std::map<std::string, T>> descriptor_t;
};

template <typename TReader, typename T>
void dispatch_read_object(const
				map_type_descriptor<std::map<std::string, T>>& desc, 
				TReader& reader, std::map<std::string, T>& t)
{
	reader.enter_object();
	if (!reader.is_end_object())
	{
		std::string s_prop;
		reader.first_prop(s_prop);
		for (;;)
		{
			read_json(reader, t[s_prop]);
			if (reader.is_end_object())
				break;
			reader.next_prop(s_prop);
		}
	}
	reader.leave_object();
}

template <typename TWriter, typename T>
void dispatch_write_object(const
				map_type_descriptor<std::map<std::string, T>>& desc, 
				TWriter& writer, const std::map<std::string, T>& t)
{
	writer.begin_object("map");
	for (auto it = t.begin(); it != t.end(); it++)
	{
		writer.begin_prop(it->first.c_str());
		write_json(writer, it->second);
		writer.end_prop();
	}
	writer.end_object();	
}

#endif /* __MAP_TYPE_DESCRIPTOR__ */