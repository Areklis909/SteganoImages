#ifndef TASK_DETAIL_CPP
#define TASK_DETAIL_CPP

#include <ParallelEncoder/TaskDetail.hpp>

namespace NsTaskDetail {

TaskDetail::TaskDetail(const std::string_view &submessage,
                       const NsRange::Range &range)
    : submessage(submessage), range(range) {}

TaskDetail::~TaskDetail() {}

std::string_view TaskDetail::getMessage() const { return submessage; }
NsRange::Range TaskDetail::getRange() const { return range; }

} // namespace NsTaskDetail

#endif