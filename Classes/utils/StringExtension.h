#pragma once
#include <strstream>
#include <string>

class StringExtension{
public:
        template <class T>
        static std::string toString(const T& t){
                std::stringstream sstr;
                sstr << t;
                return sstr.str();
        }
};