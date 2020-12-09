#ifndef TASK_DETAIL_HPP
#define TASK_DETAIL_HPP

#include <Range/Range.hpp>
#include <string>
#include <vector>

namespace NsTaskDetail {

/*
  TaskDetail
*/

class TaskDetail {

  const std::string submessage;
  const NsRange::Range range;

public:
  TaskDetail(const std::string &submessage, const NsRange::Range &range);
  std::string getMessage() const;
  NsRange::Range getRange() const;
};

/*
  TaskDetailManager
*/

class TaskDetailManager {
public:
  TaskDetailManager(const size_t maxThreads);
  ~TaskDetailManager() = default;

  std::vector<NsTaskDetail::TaskDetail>
  getTaskDetails(const std::string &message, const int start);

private:
  const size_t noThreads;
  
  std::vector<std::string>
  divideIntoSubmessages(const std::string &message,
                        const std::vector<NsRange::Range> &ranges);

  std::vector<NsRange::Range> divideIntoRanges(const std::string &message,
                                               const int start);
};

} // namespace NsTaskDetail

#endif