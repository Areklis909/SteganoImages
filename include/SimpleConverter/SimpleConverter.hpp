#ifndef SIMPLE_CONVERTER_HPP
#define SIMPLE_CONVERTER_HPP

#include <sstream>
#include <type_traits>

namespace NsSimpleConverter {

class SimpleConverter {

public:
    SimpleConverter() = default;
    ~SimpleConverter() = default;

    template<typename T>
    typename std::enable_if<std::is_integral_v<T>, std::string>::type
     toString(const T & value) {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
};

}

#endif