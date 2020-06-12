#ifndef PARALLEL_ENCODER_HPP
#define PARALLEL_ENCODER_HPP

#include "ParallelTask.hpp"
#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include <future>

namespace NsParallelEncoder {

template <typename Task> class ParallelEncoder {

  std::vector<decltype(std::async(std::launch::async, std::declval<Task>()))>
      futures;

public:
  ParallelEncoder(const std::vector<Task> &tasks) {
    for (const auto task : tasks) {
      futures.push_back(std::async(std::launch::async, task));
    }
  };

  ~ParallelEncoder() {
    for (auto &&fut : futures) {
      fut.get();
    }
  };
};

} // namespace NsParallelEncoder

#endif