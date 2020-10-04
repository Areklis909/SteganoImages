#ifndef PARALLEL_ENCODER_HPP
#define PARALLEL_ENCODER_HPP

#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include <future>

namespace NsParallelEncoder {

template <typename Task> class ParallelEncoder {

  Task taskPattern;
public:
  ParallelEncoder(Task pattern) : taskPattern(pattern) {};

  template<typename Collection>
  auto runTaskOverCollection(Collection && c) {

    std::vector<std::future<void>> taskHandles;
    for (const auto detail : c) {
      taskHandles.push_back(
        std::async(std::launch::async, [&, detail](){
          taskPattern(detail);
        })
      );
    }
    return taskHandles;
  }
};

} // namespace NsParallelEncoder

#endif