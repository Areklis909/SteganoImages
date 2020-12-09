#ifndef CONST_DATA_HPP
#define CONST_DATA_HPP

#include <cstddef>
#include <cstdint>
#include <string>

namespace NsConstData {

class ConstData {
  ConstData() = default;
  ConstData(const ConstData &) = default;
public:
  static ConstData &instance();
  int bitsInByte() const;
  int msgMarkerStartPoint() const;
  int msgSizeSize() const;
  int msgSizeMarkerSizeInBits() const;
  std::string steganoMarker() const;
  int getSteganoMarkerSizeInBits() const;
};

} // namespace NsConstData

#endif