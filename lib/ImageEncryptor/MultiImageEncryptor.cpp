#include <ImageEncryptor/MultiImageEncryptor.hpp>
#include <ParallelEncoder/ParallelEncoder.hpp>
#include <PixelStrategy/EncryptPixel.hpp>
#include <string_view>

namespace NsImageEncryptor {

MultiImageEncryptor::MultiImageEncryptor(
    std::unique_ptr<NsImageHandler::ImageHandlerInterface> h)
    : ImageEncryptorInterface(std::move(h)) {}

MultiImageEncryptor::~MultiImageEncryptor() {
  std::for_each(taskHandles.begin(), taskHandles.end(), [](auto && f){ f.get(); });
}

void MultiImageEncryptor::encryptionWorker(const NsTaskDetail::TaskDetail &detail) {
  auto range = detail.getRange();
  handler->applyToEveryPixelInRangeRaw(strategy, range.start(), range.end());
}

void MultiImageEncryptor::encryptData(const std::string &message) {
  using namespace NsConstData;
  using namespace NsParallelEncoder;
  using namespace NsTaskDetail;

  TaskDetailManager taskMgr(noThreads);

  auto details = taskMgr.getTaskDetails(message, ConstData::instance().msgSizeMarkerSizeInBits() + ConstData::instance().getSteganoMarkerSizeInBits());
  auto taskPattern = [&](const TaskDetail &detail) { encryptionWorker(detail); };
  ParallelEncoder encoder(taskPattern);
  taskHandles = encoder.runTaskOverCollection(details);
}

} // namespace NsImageEncryptor