#include <string>
#include <map>
#include "json/json.h"
#include "foo.h"

void read_write_json_string() 
{
    std::string s_json_parse = 
        "{\"a_val\":1,"
        "\"another_val\":2,"
        "\"third_val\":\"string\","
        "\"fourth\":\"grear\"}";
    foo result;
    from_json(result, s_json_parse);
    std::cout << "here's result " << std::endl;
    result.print();
    std::string s_json_write = to_json(result);

    std::cout << s_json_write << std::endl;

    if (s_json_parse == s_json_write)
        std::cout << "test pass" << std::endl;
    else
        std::cout << "test fail" << std::endl;

}
int main (int argc, char *argv[]) 
{
    // foo b1(1, 2, "a string", "gear");
    // std::cout << to_json(b1) << std::endl;

    read_write_json_string();

    // std::map<std::string, std::string> test;
    // test["12"] = "ABCD";
    // test["10"] = "ABCDE";

    // std::string mapString = to_json(test);
    // std::cout << mapString << std::endl;
    return 0;
}