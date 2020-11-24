#include <cstddef>
#include <Utils/Utils.hpp>


namespace NsUtils {

size_t digits(size_t number) {

    int res = 0;
    while(number > 0) {
        ++res;
        number = number / 10;
    }
    return res;
}


}