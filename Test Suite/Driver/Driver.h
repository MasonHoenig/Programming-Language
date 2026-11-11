#ifndef DRIVER_H
#define DRIVER_H

#include <string>

class Driver {
public:
    Driver();


    int run(const std::string& sourceFile);

private:
    std::string readFile(const std::string& filename);
};


#endif