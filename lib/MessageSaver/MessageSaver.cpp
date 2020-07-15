#ifndef MESSAGE_SAVER_CPP
#define MESSAGE_SAVER_CPP

#include <MessageSaver/MessageSaver.hpp>

namespace NsMessageSaver {

MessageSaver::MessageSaver(const std::string &filePathWhereTheMsgWillBeSaved)
    : fileWhereTheMsgWillBeSaved(filePathWhereTheMsgWillBeSaved,
                                 std::ios_base::out) {
  if (fileWhereTheMsgWillBeSaved.good() == false) {
    std::string s{"Failed to open the file for writing: "};
    throw std::runtime_error((s + filePathWhereTheMsgWillBeSaved).c_str());
  }
}

MessageSaver::~MessageSaver() {
  if (fileWhereTheMsgWillBeSaved.is_open() == true) {
    fileWhereTheMsgWillBeSaved.close();
  }
}

void MessageSaver::saveMessage(const std::string & msg) {
    fileWhereTheMsgWillBeSaved << msg;
}

} // namespace NsMessageSaver

#endif