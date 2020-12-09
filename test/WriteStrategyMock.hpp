#ifndef WRITE_STRATEGY_MOCK_HPP
#define WRITE_STRATEGY_MOCK_HPP

#include "gmock/gmock.h"
#include <PixelStrategy/WriteStrategy.hpp>

namespace NsTest {

class WriteStrategyMock : public NsPixelStrategy::WriteStrategy {
public:
  WriteStrategyMock() = default;
  MOCK_METHOD(char, pixelOperation, (char), (override));
};

}

#endif