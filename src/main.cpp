#include <ImageEncryptor/ImageEncryptor.hpp>

int main() {
    NsImageEncryptor::ImageEncryptor encryptor("/home/alis/SteganoImages/src/obraz.PNG", "/home/alis/SteganoImages/src/obraz2.PNG");
    encryptor.encrypt2("Arek");
    return 0;
}