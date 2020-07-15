#ifndef MESSAGE_TOO_BIG_EXC
#define MESSAGE_TOO_BIG_EXC

#include <MessageTooBigException/MessageTooBigException.hpp>

namespace NsMessageTooBigException {

MessageTooBigException::MessageTooBigException() {}

// MessageTooBigException::~MessageTooBigException() {}

const char *MessageTooBigException::what() const noexcept {
  const char *msg = "Supplied message size is too big! \n";
  return msg;
}

} // namespace NsMessageTooBigException

#endif