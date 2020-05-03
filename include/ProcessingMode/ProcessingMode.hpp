#ifndef PROCESSING_MODE_HPP
#define PROCESSING_MODE_HPP

#include <string>
#include "ProcessingModeType.hpp"

namespace NsProcessingMode {

class ProcessingMode {

public:
    ProcessingMode(const ProcessingModeType mode);
    ~ProcessingMode();

    std::string toString();
    static ProcessingMode fromString(const std::string & strMode);
private:
    const ProcessingModeType mode;
    static const std::string encodingStr;
    static const std::string decodingStr;
};

}

#endif