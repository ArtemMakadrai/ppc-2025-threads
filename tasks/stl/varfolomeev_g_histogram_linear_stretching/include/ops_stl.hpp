#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace varfolomeev_g_histogram_linear_stretching_stl {

class TestTaskSTL : public ppc::core::Task {
 public:
  explicit TestTaskSTL(ppc::core::TaskDataPtr task_data) : Task(std::move(task_data)) {}
  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

 private:
  std::vector<uint8_t> img_, res_;
};

}  // namespace varfolomeev_g_histogram_linear_stretching_stl