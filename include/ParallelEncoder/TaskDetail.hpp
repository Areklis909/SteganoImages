#ifndef TASK_DETAIL_HPP
#define TASK_DETAIL_HPP

#include <string_view>
#include <Range/Range.hpp>

namespace NsTaskDetail {

class TaskDetail {

    const std::string_view submessage;
    const NsRange::Range range;
public:
    TaskDetail(const std::string_view & submessage, const NsRange::Range & range);
    ~TaskDetail();
    std::string_view getMessage() const;
    NsRange::Range getRange() const;
};


}

#endif