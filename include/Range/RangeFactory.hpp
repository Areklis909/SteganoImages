#ifndef RANGE_FACTORY_HPP
#define RANGE_FACTORY_HPP

#include <string>
#include <ConstData/ConstData.hpp>
#include <MessageSizeFinder/MessageSizeFinder.hpp>
#include "Range.hpp"

namespace NsRange {

class RangeFactory {

  const int maxPixels;
public:
  RangeFactory(const int maxPixels) : maxPixels(maxPixels) {};

  template<typename T>
  Range getRange(const T &message, const int start) {

    using namespace NsConstData;
    MessageSizeFinder<decltype(message)> sizeFinder;
    const int msgSizeInBits = sizeFinder.getSize(message) * ConstData::instance().bitsInByte();
    if (msgSizeInBits > maxPixels) {
      throw std::runtime_error("Message is too big!");
    }
    return Range(start, start + msgSizeInBits);
  }
};

} // namespace NsRange

#endif