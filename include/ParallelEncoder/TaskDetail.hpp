#ifndef TASK_DETAIL_HPP
#define TASK_DETAIL_HPP

#include <Range/Range.hpp>
#include <string_view>

namespace NsTaskDetail {

class TaskDetail {

  const std::string_view submessage;
  const NsRange::Range range;

public:
  TaskDetail(const std::string_view &submessage, const NsRange::Range &range);
  ~TaskDetail();
  std::string_view getMessage() const;
  NsRange::Range getRange() const;
};

} // namespace NsTaskDetail

#endif