#ifndef OUTPUT_MODE_CPP
#define OUTPUT_MODE_CPP

#include <OutputMode/OutputMode.hpp>
#include <stdexcept>

namespace NsOutputMode {

OutputMode::OutputMode(const OutputModeType type)
    : mode(type) {}

// OutputMode::~OutputMode() {}

bool OutputMode::operator==(const OutputMode &other) const {
  return other.mode == mode;
}

std::string OutputMode::toString() {
  switch (mode) {
  case OutputModeType::STDOUT: {
    return stdoutStr;
  }
  case OutputModeType::FILE: {
    return fileStr;
  }
  default: {
    throw std::runtime_error("Incorrect mode!");
  }
  }
}

OutputMode OutputMode::fromString(const std::string & strMode) {
  if(stdoutStr.compare(strMode) == 0) {
    return OutputMode(OutputModeType::STDOUT);
  } else if(fileStr.compare(strMode) == 0) {
    return OutputMode(OutputModeType::FILE);
  } else {
    throw std::runtime_error("Incorrect output mode string");
  }
}

const std::string OutputMode::fileStr = "file";
const std::string OutputMode::stdoutStr = "stdout";

} // namespace NsOutputMode

#endif