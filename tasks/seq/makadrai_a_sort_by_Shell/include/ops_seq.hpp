#pragma once

#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace makadrai_a_sort_by_Shell {

class TestTaskSequential : public ppc::core::Task {
 public:
  explicit TestTaskSequential(ppc::core::TaskDataPtr task_data) : Task(std::move(task_data)) {}
  bool PreProcessingImpl() override;
  bool ValidationImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;

  void merge(std::vector<int>& arr, int left, int mid, int right);
  void shellSort(std::vector<int>& arr);
  void mergeSort(std::vector<int>& arr, int left, int right);
  void hybridShellMergeSort(std::vector<int>& arr);
 private:
  std::vector<int> input_, output_;
  int size_;
  int rc_size_{};
};

}  // namespace makadrai_a_sort_by_Shell