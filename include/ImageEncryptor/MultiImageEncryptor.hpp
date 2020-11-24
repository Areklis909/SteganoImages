#ifndef MULTI_IMAGE_ENCRYPTOR
#define MULTI_IMAGE_ENCRYPTOR

#include <future>
#include <string>
#include <memory>
#include <ImageEncryptor/ImageEncryptorInterface.hpp>
#include <ImageHandler/ImageHandlerInterface.hpp>
#include <ParallelEncoder/TaskDetail.hpp>

namespace NsImageEncryptor {

class MultiImageEncryptor : public ImageEncryptorInterface {
  std::vector<std::future<void>> taskHandles;
  const size_t noThreads = 3;

  void encryptionWorker(const NsTaskDetail::TaskDetail &detail);
public:
  MultiImageEncryptor(std::unique_ptr<NsImageHandler::ImageHandlerInterface> h);
  ~MultiImageEncryptor();

  void encryptData(const std::string &message) override;
};

} // namespace NsImageEncryptor

#endif