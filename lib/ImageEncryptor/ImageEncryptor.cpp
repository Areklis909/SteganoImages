#ifndef IMAGE_ENCRYPTOR_CPP
#define IMAGE_ENCRYPTOR_CPP

#include <ImageEncryptor/ImageEncryptor.hpp>
#include <tuple>
#include <utility>

namespace NsImageEncryptor {

using namespace NsConstData;

ImageEncryptor::ImageEncryptor(const std::string &imagePath,
                               const std::string &pathToWrite)
    : imageHandler(imagePath, pathToWrite), messageLengthThreshold(150),
      noThreads(3) {}

ImageEncryptor::~ImageEncryptor() {}

std::vector<NsRange::Range>
ImageEncryptor::divideIntoRanges(const std::string &message, const int start) {

  using NsRange::Range;
  std::vector<Range> ret;
  const size_t sz = message.size();
  const size_t taskSize = sz / noThreads;
  const size_t rest = sz % noThreads;
  int startPoint = start;
  for (size_t i = 0; i < noThreads; ++i) {
    const int currentTaskSize =
        (i == (noThreads - 1)) ? taskSize + rest : taskSize;
    ret.push_back(Range(startPoint, startPoint + currentTaskSize));
    startPoint = startPoint + currentTaskSize;
  }
  return ret;
}

std::vector<std::string_view> ImageEncryptor::divideIntoSubmessages(
    const std::string &message, const std::vector<NsRange::Range> &ranges) {

  std::vector<std::string_view> submessages;
  submessages.reserve(ranges.size());
  std::transform(ranges.begin(), ranges.end(), std::back_inserter(submessages),
                 [&](auto &range) {
                   const int length = range.end() - range.start();
                   return std::string_view(message.c_str() + range.start(),
                                           length);
                 });
  return submessages;
}

std::vector<NsTaskDetail::TaskDetail>
ImageEncryptor::getTaskDetails(const std::string &message, const int start) {

  using NsRange::Range;
  using NsTaskDetail::TaskDetail;
  using namespace NsConstData;

  std::vector<TaskDetail> ret;
  auto ranges = divideIntoRanges(message, 0);
  auto submessages = divideIntoSubmessages(message, ranges);
  for (const auto complet : zip(submessages, ranges)) {
    ret.push_back(
        TaskDetail(complet.first, (complet.second * bitsInByte + start)));
  }
  return ret;
}

void ImageEncryptor::encryptMulti(const NsTaskDetail::TaskDetail taskDetail) {
  using namespace NsConstData;
  const auto range = taskDetail.getRange();
  const auto message = taskDetail.getMessage();
  int index = 0;
  auto putMessageBitIntoPixel = [&](unsigned char &byte) {
    // get message byte value, current bit number and bit value
    const unsigned char tmp = message.at(index / bitsInByte);
    const int bitNum = index % bitsInByte;
    const bool val = checkBit(tmp, bitNum);
    byte = setFirstBit(byte, val);
    ++index;
  };
  imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel,
                                           range.start(), range.end());
}

NsRange::Range ImageEncryptor::getMessageRange(const std::string &message,
                                               const int start) {
  using NsRange::Range;

  const int msgSizeInBits = message.size() * bitsInByte;
  const int allPixels = imageHandler.getNumOfPixels();
  if (msgSizeInBits > allPixels) {
    throw std::runtime_error("Message is too big!");
  }
  return Range(start, start + msgSizeInBits);
}

void ImageEncryptor::encryptSingle(const std::string &message,
                                   const int startPoint) {

  using namespace NsConstData;
  const auto range = getMessageRange(message, startPoint);
  int index = 0;
  auto putMessageBitIntoPixel = [&](unsigned char &byte) {
    // get message byte value, current bit number and bit value
    const unsigned char tmp = message.at(index / bitsInByte);
    const int bitNum = index % bitsInByte;
    const bool val = checkBit(tmp, bitNum);
    byte = setFirstBit(byte, val);
    ++index;
  };
  imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel,
                                           range.start(), range.end());
}

void ImageEncryptor::encryptData(const std::string &message) {

  using namespace NsConstData;
  using namespace NsParallelEncoder;
  const size_t sz = message.size() * bitsInByte;
  imageHandler.verifyMessageSize(sz);
  encodeMessageSize(sz, msgSizeStartPoint);
  if (message.length() < messageLengthThreshold) {
    encryptSingle(message, msgBodyStartPoint);
  } else {
    auto details = getTaskDetails(message, msgBodyStartPoint);
    NsTaskDetail::TaskDetail det(details.at(0));
    ParallelTask task(&ImageEncryptor::encryptMulti, this, det);
    std::vector<decltype(task)> tasks;
    for (size_t i = 0; i < noThreads; ++i) {
      tasks.push_back(
          ParallelTask(&ImageEncryptor::encryptMulti, this, details.at(i)));
    }
    ParallelEncoder parallelEncoder(tasks);
  }
}

void ImageEncryptor::encodeMessageSize(const size_t message,
                                       const int startPoint) {
  using namespace NsConstData;
  const auto range = getMessageRange(message, startPoint);
  int index = 0;
  const std::byte *bytes = toBytes(message);
  auto putMessageBitIntoPixel = [&](unsigned char &messageByte) {
    // get message byte value, current bit number and bit value
    const int i = index / bitsInByte;
    const std::byte tmp = bytes[i];
    const int bitNum = index % bitsInByte;
    const bool val = checkBit(tmp, bitNum);
    messageByte = setFirstBit(messageByte, val);
    ++index;
  };
  imageHandler.applyToEveryPixelInRangeRaw(putMessageBitIntoPixel,
                                           range.start(), range.end());
}

} // namespace NsImageEncryptor

#endif