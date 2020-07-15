#ifndef OUTPUT_MODE_TYPE_HPP
#define OUTPUT_MODE_TYPE_HPP

#include <OutputMode/OutputModeType.hpp>
#include <string>

namespace NsOutputMode {

class OutputMode {

  OutputModeType mode;

public:
  OutputMode(const OutputModeType type);  
  static const std::string fileStr;
  static const std::string stdoutStr;

  bool operator==(const OutputMode &other);
  std::string toString();
  static OutputMode fromString(const std::string &strMode);
};

} // namespace NsOutputMode

#endif