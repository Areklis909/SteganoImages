#include <ImageDecoder/ImageDecoderInterface.hpp>
#include <NotSteganoException/NotSteganoException.hpp>

namespace NsImageDecoder {

std::string ImageDecoderInterface::readMessage() {
    using NsNotSteganoException::NotSteganoException;

    if(findSteganoMarker() == false) {
        throw NotSteganoException();
    }
    return getMessage(getMessageSize());
}


} // namespace NsImageDecoder