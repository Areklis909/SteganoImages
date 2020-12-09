#ifndef READ_STRATEGY_HPP
#define READ_STRATEGY_HPP

#include <PixelStrategy/PixelStrategy.hpp>

namespace NsPixelStrategy {

class ReadStrategy : public PixelStrategy {

public:
  virtual char pixelOperation(char byte);
};

} // namespace NsPixelStrategy

#endif