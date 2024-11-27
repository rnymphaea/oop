#ifndef LR2_INVALIDATTACKERROR_H
#define LR2_INVALIDATTACKERROR_H

#include <iostream>

class InvalidAttackError : public std::runtime_error{
public:
    InvalidAttackError(const std::string &msg) : std::runtime_error(msg){}
};


#endif //LR2_INVALIDATTACKERROR_H
