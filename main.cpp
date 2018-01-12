#include "json/json.h"
#include "foo.h"


int main (int argc, char *argv[]) 
{
    foo b1(1, 2, "sha	nks");
    std::cout << to_json(b1) << std::endl;
    return 0;
}