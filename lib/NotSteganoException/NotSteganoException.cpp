#ifndef NOT_STEGANO_EXC
#define NOT_STEGANO_EXC

#include <NotSteganoException/NotSteganoException.hpp>

namespace NsNotSteganoException {

NotSteganoException::NotSteganoException() {}

// NotSteganoException::~NotSteganoException() {}

const char *NotSteganoException::what() const noexcept {
  const char *msg = "This image was not stegano-processed before! \n";
  return msg;
}

} // namespace NsNotSteganoException

#endif