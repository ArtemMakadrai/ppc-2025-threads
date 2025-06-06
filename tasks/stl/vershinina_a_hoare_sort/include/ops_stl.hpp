#pragma once

#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace vershinina_a_hoare_sort_stl {

class TestTaskSTL : public ppc::core::Task {
 public:
  explicit TestTaskSTL(ppc::core::TaskDataPtr task_data) : Task(std::move(task_data)) {}
  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

 private:
  std::vector<double> input_;
  std::vector<double> res_;
};

}  // namespace vershinina_a_hoare_sort_stl
