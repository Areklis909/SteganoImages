#include <exception>

namespace NsMessageTooBigException {

class MessageTooBigException : public std::exception {
public:
  MessageTooBigException();
  virtual const char *what() const noexcept override;
  
};

} // namespace NsMessageTooBigException