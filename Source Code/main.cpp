#include "Driver/Driver.h"

#include <string>
#include <iostream>

int main()
{
    try
    {

        RunCompiler("testInput.swi");
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    return 0;
}