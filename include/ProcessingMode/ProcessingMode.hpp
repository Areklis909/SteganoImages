#ifndef PROCESSING_MODE_HPP
#define PROCESSING_MODE_HPP

#include "ProcessingModeType.hpp"
#include <string>

namespace NsProcessingMode {

class ProcessingMode {

public:
  ProcessingMode(const ProcessingModeType mode);

  bool operator==(const ProcessingMode &other) const;
  bool operator==(ProcessingMode && other) const;

  std::string toString();
  static ProcessingMode fromString(const std::string &strMode);

private:
  const ProcessingModeType mode;
  static const std::string encodingStr;
  static const std::string decodingStr;
};

} // namespace NsProcessingMode

#endif