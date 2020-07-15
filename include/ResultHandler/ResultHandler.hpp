#ifndef RESULT_HANDLER_HPP
#define RESULT_HANDLER_HPP

#include <MessageSaver/MessageSaver.hpp>
#include <OutputMode/OutputMode.hpp>
#include <optional>

namespace NsResultHandler {

class ResultHandler {

public:
  ResultHandler(const std::string &result, const NsOutputMode::OutputMode mode,
                std::optional<std::string> filePath);
};

} // namespace NsResultHandler

#endif