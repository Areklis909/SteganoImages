#ifndef CONVERTER_INTERFACE
#define CONVERTER_INTERFACE

#include <vector>
#include <iostream>

namespace NsConverterInterface {

template<typename T>
struct CrtpHelper {
    T & underlying() {
        return static_cast<T &>(*this);
    };

    T const & underlying() const {
        return static_cast<T const &>(*this);
    }
};

template<typename T>
class ConverterInterface : public CrtpHelper<T> {

public:
    template<typename Input, typename Output>
    Output convert(Input input) {
        return this->underlying().template convert<Input, Output>(input);
    }

    ConverterInterface() {};
    ~ConverterInterface() {};
};

}

#endif