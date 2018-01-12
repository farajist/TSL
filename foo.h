#ifndef __FOO__
#define __FOO__
#include <string>
#include "json/class_descriptor.h"

class foo {
public:
    foo(int a, int b, std::string s) : a_val(a), another_val(b), third_val(s) {} 

private:
    int a_val;
    int another_val;
    std::string third_val;
};

BEGIN_CLASS_DESCRIPTOR (foo)
    CLASS_DESCRIPTOR_ENTRY(a_val)
    CLASS_DESCRIPTOR_ENTRY(another_val)
    CLASS_DESCRIPTOR_ENTRY(third_val)
END_CLASS_DESCRIPTOR()

#endif /* __FOO__ */