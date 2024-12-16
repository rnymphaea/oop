#ifndef LR2_NOABILITIESERROR_H
#define LR2_NOABILITIESERROR_H

#include <iostream>

class NoAbilitiesError : public std::runtime_error{
public:
    NoAbilitiesError(const std::string &msg) : std::runtime_error(msg){}
};

#endif //LR2_NOABILITIESERROR_H
