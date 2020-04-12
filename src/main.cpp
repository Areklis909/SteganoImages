// #include <ImageHandler/ImageHandler.hpp>
#include <TextToBitsConverter/TextToBitsConverter.hpp>
#include <BitsToSignConverter/BitsToSignConverter.hpp>

template<typename T, typename In, typename Out>
Out doStuff(NsConverterInterface::ConverterInterface<T> converter, In input) {
    return converter.template convert<In, Out>(input);
}

int main() {
    using NsTextToBitsConverter::TextToBitsConverter;
    using NsBitsToSignConverter::BitsToSignConverter;
    TextToBitsConverter conv;
    std::string s = "abc";
    auto encrypted =  doStuff<TextToBitsConverter, std::string, std::vector<NsCharBit::CharBit> >(conv, s);

    BitsToSignConverter invConv;
    auto decrypted = doStuff<BitsToSignConverter, std::vector<NsCharBit::CharBit>, std::string>(invConv, encrypted);

    for(const auto character : decrypted) {
        std::cout << static_cast<int>(character) << " ";
    }
    return 0;
}