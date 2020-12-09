#ifndef WRITE_STRATEGY_HPP
#define WRITE_STRATEGY_HPP

#include <PixelStrategy/PixelStrategy.hpp>
#include <string>

namespace NsPixelStrategy {

class WriteStrategy : public PixelStrategy {

public:
  char pixelOperation(char byte) override { return 0; };
  void setMessage(const std::string & msg) {
    message = msg;
    index = 0;
  }
protected:
  int index = 0;
  std::string message;
};

} // namespace NsPixelStrategy

#endif