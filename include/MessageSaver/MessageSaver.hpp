#ifndef MESSAGE_SAVER_HPP
#define MESSAGE_SAVER_HPP

#include <string>
#include <fstream>

namespace NsMessageSaver {

class MessageSaver {

    std::fstream fileWhereTheMsgWillBeSaved;
public:
    MessageSaver(const std::string & filePathWhereTheMsgWillBeSaved);
    ~MessageSaver();
    void saveMessage(const std::string & msg);
};

}


#endif