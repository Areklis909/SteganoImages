#include <ConstData/ConstData.hpp>

namespace NsConstData {

ConstData &ConstData::instance() {
  static ConstData s;
  return s;
}

int ConstData::bitsInByte() const { return 8; }

int ConstData::msgMarkerStartPoint() const { return 0; }

int ConstData::msgSizeSize() const { return 8; }

int ConstData::msgSizeMarkerSizeInBits() const { return msgSizeSize() * bitsInByte(); }

std::string ConstData::steganoMarker() const { return "SteganoImages"; }

int ConstData::getSteganoMarkerSizeInBits() const { return bitsInByte() * steganoMarker().size(); }

} // namespace NsConstData