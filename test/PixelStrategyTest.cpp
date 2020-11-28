#include "gtest/gtest.h"
#include <PixelStrategy/EncryptPixel.hpp>
#include <string>
#include <string_view>
#include <algorithm>

using NsPixelStrategy::EncryptPixel;

TEST(EncryptPixelTest, shouldEncryptStringMessageBitsInLSB) {

    //given
    const size_t N = 8;
    const char aLetter = 'A';
    std::string msg {&aLetter};
    char data[N]{};
    EncryptPixel strategy{msg};

    //when
    for(size_t i = 0; i < N; ++i) {
        data[i] = strategy.pixelOperation(data[i]);
    }

    //then
    char result {0};
    for(size_t i = 0; i < N; ++i) {
        result = strategy.setBit(result, strategy.checkFirstBit(data[i]), i);
    }
    EXPECT_EQ(aLetter, result);
}

TEST(EncryptPixelTest, shouldEncryptStringViewMessageBitsInLSB) {

    //given
    const size_t N = 8;
    const char aLetter = 'A';
    std::string msg {&aLetter};
    std::string_view sv {msg};
    char data[N]{};
    EncryptPixel strategy{sv};

    //when
    for(size_t i = 0; i < N; ++i) {
        data[i] = strategy.pixelOperation(data[i]);
    }

    //then
    char result {0};
    for(size_t i = 0; i < N; ++i) {
        result = strategy.setBit(result, strategy.checkFirstBit(data[i]), i);
    }
    EXPECT_EQ(aLetter, result);
}