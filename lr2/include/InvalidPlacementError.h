#ifndef LR2_INVALIDPLACEMENTERROR_H
#define LR2_INVALIDPLACEMENTERROR_H

#include <iostream>

class InvalidPlacementError : public std::runtime_error{
public:
    InvalidPlacementError(const std::string &msg) : std::runtime_error(msg){}
};

#endif //LR2_INVALIDPLACEMENTERROR_H
