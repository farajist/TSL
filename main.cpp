#include <string>
#include <map>
#include "json/json.h"
#include "foo.h"


int main (int argc, char *argv[]) 
{
    // foo b1(1, 2, "a string");
    // std::cout << to_json(b1) << std::endl;



std::map<std::string, std::string> test;
test["12"] = "ABCD";
test["10"] = "ABCDE";

std::string mapString = to_json(test);
std::cout << mapString << std::endl;
    return 0;
}