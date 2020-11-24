#ifndef MESSAGE_SIZE_FINDER
#define MESSAGE_SIZE_FINDER

#include <string>
#include <type_traits>

template<typename MessageType>
class MessageSizeFinder {
public:
    MessageSizeFinder() = default;

    size_t getSize(const MessageType msg) {
        if constexpr(std::is_same<std::string, typename std::decay<MessageType>::type>()) {
            return msg.size();
        } else {
            return sizeof(msg);
        }
    }
};

#endif