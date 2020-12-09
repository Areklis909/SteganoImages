#ifndef IMAGE_ENCRYPTOR_HPP
#define IMAGE_ENCRYPTOR_HPP

#include <BitwiseOperations/BitwiseOperations.hpp>
#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include <ParallelEncoder/ParallelEncoder.hpp>
#include <ParallelEncoder/TaskDetail.hpp>
#include <type_traits>
#include <cstddef>
#include <memory>

namespace NsImageEncryptor {

class ImageEncryptor : public NsBitwiseOperations::BitwiseOperations {

  // NsImageHandler::ImageHandler imageHandler;
  std::unique_ptr<NsImageHandler::ImageHandlerInterface> imageHandler;

  const size_t messageLengthThreshold = 150;
  const size_t noThreads = 3;
  std::vector<std::future<void>> taskHandles;

  NsRange::Range getMessageRange(const std::string &message, const int start);
  void encryptMulti(const NsTaskDetail::TaskDetail taskDetail);
  void encryptSingle(const std::string &message, const int startPoint);
  std::vector<NsRange::Range> divideIntoRanges(const std::string &message,
                                               const int start);
  std::vector<std::string_view>
  divideIntoSubmessages(const std::string &message,
                        const std::vector<NsRange::Range> &ranges);
  std::vector<NsTaskDetail::TaskDetail>
  getTaskDetails(const std::string &message, const int start);

  template <typename T>
  NsRange::Range getMessageRange(T message, const int start) {
    using NsRange::Range;
    using namespace NsConstData;

    const int msgSizeInBits = sizeof(message) * ConstData::instance().bitsInByte();
    const int allPixels = imageHandler->getNumOfPixels();
    if (msgSizeInBits > allPixels) {
      throw std::runtime_error("Message is too big!");
    }
    return Range(start, start + msgSizeInBits);
  }

  template <typename T> const std::byte *toBytes(T &data) {
    T *ptr = reinterpret_cast<T *>(&data);
    const void *dataBuf = static_cast<const void *>(ptr);
    return static_cast<const std::byte *>(dataBuf);
  }

  void encodeMessageSize(const size_t message, const int startPoint);
  void encodeSteganoMarker();

public:
  // ImageEncryptor(const std::string &imagePath, const std::string &pathToWrite);
  ImageEncryptor(std::unique_ptr<NsImageHandler::ImageHandlerInterface> handler);
  ~ImageEncryptor();

  void encryptData(const std::string &message);
};

} // namespace NsImageEncryptor

#endif