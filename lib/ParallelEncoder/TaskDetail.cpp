#ifndef TASK_DETAIL_CPP
#define TASK_DETAIL_CPP

#include <ParallelEncoder/TaskDetail.hpp>
#include <ConstData/ConstData.hpp>

namespace NsTaskDetail {

/*
    TaskDetail
*/

TaskDetail::TaskDetail(const std::string &submessage,
                       const NsRange::Range &range)
    : submessage(submessage), range(range) {}

std::string TaskDetail::getMessage() const { return submessage; }
NsRange::Range TaskDetail::getRange() const { return range; }

/*
    TaskDetailManager
*/

TaskDetailManager::TaskDetailManager(const size_t maxThreads)
    : noThreads(maxThreads) {}

std::vector<std::string> TaskDetailManager::divideIntoSubmessages(
    const std::string &message, const std::vector<NsRange::Range> &ranges) {
  std::vector<std::string> submessages;
  submessages.reserve(ranges.size());
  std::transform(ranges.begin(), ranges.end(), std::back_inserter(submessages),
                 [&](auto &range) {
                   const int length = range.end() - range.start();
                   return std::string(message.c_str() + range.start(),
                                           length);
                 });
  return submessages;
}

std::vector<NsRange::Range>
TaskDetailManager::divideIntoRanges(const std::string &message,
                                    const int start) {
  using NsRange::Range;
  std::vector<Range> ret;
  const size_t sz = message.size();
  const size_t taskSize = sz / noThreads;
  const size_t rest = sz % noThreads;
  int startPoint = start;
  for (size_t i = 0; i < noThreads; ++i) {
    const int currentTaskSize =
        (i == (noThreads - 1)) ? taskSize + rest : taskSize;
    ret.emplace_back(startPoint, startPoint + currentTaskSize);
    startPoint = startPoint + currentTaskSize;
  }
  return ret;
}

std::vector<NsTaskDetail::TaskDetail>
TaskDetailManager::getTaskDetails(const std::string &message, const int start) {
  using NsRange::Range;
  using namespace NsConstData;

  const int startingPoint = 0;

  std::vector<TaskDetail> ret;
  auto ranges = divideIntoRanges(message, startingPoint);
  auto submessages = divideIntoSubmessages(message, ranges);
  for (const auto complet : zip(submessages, ranges)) {
    ret.emplace_back(complet.first, ((complet.second * ConstData::instance().bitsInByte()) + start));
  }
  return ret;
}

} // namespace NsTaskDetail

#endif