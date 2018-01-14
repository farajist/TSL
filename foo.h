#ifndef __FOO__
#define __FOO__
#include <string>
#include <iostream>
#include "json/class_descriptor.h"

class foo {
public:
    foo(int a, int b, std::string s, std::string f) : a_val(a), another_val(b), third_val(s), fourth(f) {}
    foo() : a_val(0), another_val(0), third_val("") {} 

    void print() 
    {
        std::cout << "a_val     " << a_val << std::endl;
        std::cout << "another_val   " << another_val << std::endl;
        std::cout << "third_val     " << third_val << std::endl;
        std::cout << "fourth     " << fourth << std::endl;
    }

private:
    int a_val;
    int another_val;
    std::string third_val;
    std::string fourth;
};

SERIALIZABLE(foo, a_val, another_val, third_val, fourth)

//to hell with it 
// BEGIN_CLASS_DESCRIPTOR (foo)
//     CLASS_DESCRIPTOR_ENTRY(a_val)
//     CLASS_DESCRIPTOR_ENTRY(another_val)
//     CLASS_DESCRIPTOR_ENTRY(third_val)
// END_CLASS_DESCRIPTOR()

#endif /* __FOO__ */