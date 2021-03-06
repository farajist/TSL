#ifndef __JSON_H__
#define __JSON_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "json_writer.h"
#include "json_reader.h"
#include "class_descriptor.h"
#include "map_type_descriptor.h"
#include "array_type_descriptor.h"
#include "vector_type_descriptor.h"
/**
 * forward declaration for the write_object function
 * defined in class_descriptor.h
 * */
template <typename TWriter, typename T>
void write_object(TWriter& writer, const T& t);

/**
 * forward declaration for the read_object function
 * defined in class_descriptor.h
 * */
template <typename TReader, typename T>
void read_object(TReader& reader, T& t);

/**
 * json writing helper, dumps json-serialized object
 * to the stream being wrapped in the writer  
 * ......
 * */
template <typename TStream, typename T>
void write_json(json_writer<TStream> &writer, const T& t)
{
    write_object(writer, t);
}

/**
 * json writing helper, dumps json-serialized object
 * to the stream passed as a parameter 
 * ......
 * */

template <typename TStream, typename T>
void write_json(TStream &stream, const T& t)
{
    auto writer = get_json_writer(stream);
    write_object(writer, t);
}

/**
 * client interface function, simply serializes a visitable 
 * object (one that has a class_descriptor) and returns 
 * the result as a string object
 * */

template <typename T>
std::string to_json(const T& t)
{
    std::stringstream sout;
    write_json(sout, t);
    return sout.str();
}

template <typename TStream, typename T>
void read_json(json_reader<TStream>& reader, T& t)
{
    read_object(reader, t);
}

template <typename TStream, typename T>
void read_json(TStream& stream, T& t)
{
    auto reader = get_json_reader(stream); 
    read_object(reader, t);
}

/**
 * client interface function, simply deserializes a visitable 
 * object (one that has a class_descriptor) and returns 
 * the result as a reference to the instance object 
 * */

template <typename T>
void from_json(T& t, const std::string& json)
{
    std::stringstream sin(json);
    read_json(sin, t);
}

#endif /* __JSON_H__ */