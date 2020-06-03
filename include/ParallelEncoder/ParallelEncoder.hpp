#ifndef PARALLEL_ENCODER_HPP
#define PARALLEL_ENCODER_HPP

#include <future>
#include <ConstData/ConstData.hpp>
#include <ImageHandler/ImageHandler.hpp>
#include "ParallelTask.hpp"

namespace NsParallelEncoder {

template<typename Task>
class ParallelEncoder {

    std::vector<decltype(std::async(std::launch::async, std::declval<Task>())) > futures;
public:
    ParallelEncoder(const std::vector<Task> & tasks) {
        for(const auto task : tasks) {
            futures.push_back(std::async(std::launch::async, task));
        }
    };

    ~ParallelEncoder() {
        for(auto && fut : futures) {
            fut.get();
        }
    };

};


}



#endif