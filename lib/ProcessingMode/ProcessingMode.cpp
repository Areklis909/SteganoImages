#ifndef PROCESSING_MODE_CPP
#define PROCESSING_MODE_CPP

#include <ProcessingMode/ProcessingMode.hpp>
#include <stdexcept>

namespace NsProcessingMode {

ProcessingMode::ProcessingMode(const ProcessingModeType mode) : mode(mode) {}

ProcessingMode ProcessingMode::fromString(const std::string &strMode) {
  if (encodingStr.compare(strMode) == 0) {
    return ProcessingMode(ProcessingModeType::ENCODING);
  } else if (decodingStr.compare(strMode) == 0) {
    return ProcessingMode(ProcessingModeType::DECODING);
  } else {
    throw std::runtime_error(
        "Failed to translate from std::string to ProcessingMode!");
  }
}

std::string ProcessingMode::toString() {
  std::string ret;
  switch (mode) {
  case ProcessingModeType::ENCODING: {
    ret = encodingStr;
    break;
  }
  case ProcessingModeType::DECODING: {
    ret = decodingStr;
    break;
  }
  default: {
    throw std::runtime_error(
        "Wrong processing mode type detected during translation!");
  }
  }
  return ret;
}

bool ProcessingMode::operator==(const ProcessingMode &other) const {
  return other.mode == mode;
}

bool ProcessingMode::operator==(ProcessingMode && other) const {
  return other.mode == mode;
}

const std::string ProcessingMode::encodingStr = "encoding";
const std::string ProcessingMode::decodingStr = "decoding";

} // namespace NsProcessingMode

#endif