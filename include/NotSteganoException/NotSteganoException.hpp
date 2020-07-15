#include <exception>

namespace NsNotSteganoException {

class NotSteganoException : public std::exception {
public:
  NotSteganoException();
  virtual const char *what() const noexcept override;
  
};

} // namespace NsNotSteganoException