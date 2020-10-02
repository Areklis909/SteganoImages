#ifndef PARALLEL_TASK_HPP
#define PARALLEL_TASK_HPP

#include <functional>

namespace NsParallelEncoder {

/*
    This class is an abstraction of a task to be
    executed in a thread. It accepts a function together with the arguments
   (func, arg1, arg2, ..., argN), and executes it in operator().
*/

// template <typename... Args> 
template<typename TaskType>
class ParallelTask {

  /*
      Ugh, fancy way to say 'return type of a std::bind call with the argumens
     args'. Credits to Tomek K.
  */
  // decltype(std::bind(std::declval<Args>()...)) task;
  TaskType task;

public:
  // ParallelTask(Args... args) : task(std::bind(std::forward<Args>(args)...)){};
  ParallelTask(TaskType && t) : task(std::forward<TaskType>(t)) {};

  void operator()() { task(); }
};

} // namespace NsParallelEncoder

#endif