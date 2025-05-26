#include "seq/makadrai_a_sort_by_Shell/include/ops_seq.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

void makadrai_a_sort_by_Shell::TestTaskSequential::shellSort(std::vector<int>& arr) {
  int n = arr.size();
  int gap = 1;

  while (gap < n / 3) {
    gap = 3 * gap + 1;
  }

  while (gap > 0) {
    for (int i = gap; i < n; i++) {
      int temp = arr[i];
      int j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
        arr[j] = arr[j - gap];
      }
      arr[j] = temp;
    }
    gap /= 3;
  }
}
void makadrai_a_sort_by_Shell::TestTaskSequential::merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);
  for (int i = 0; i < n1; i++) L[i] = arr[left + i];
  for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}
void makadrai_a_sort_by_Shell::TestTaskSequential::mergeSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}
void makadrai_a_sort_by_Shell::TestTaskSequential::hybridShellMergeSort(std::vector<int>& arr) {
  shellSort(arr);
  mergeSort(arr, 0, rc_size_ - 1);
}

bool makadrai_a_sort_by_Shell::TestTaskSequential::PreProcessingImpl() {
  unsigned int input_size = task_data->inputs_count[0];
  auto* in_ptr = reinterpret_cast<int*>(task_data->inputs[0]);
  input_ = std::vector<int>(in_ptr, in_ptr + input_size);

  unsigned int output_size = task_data->outputs_count[0];
  output_ = std::vector<int>(output_size, 0);

  rc_size_ = static_cast<int>(std::sqrt(input_size));
  size_ = input_size;
  std::cerr << size_;
  return true;
}

bool makadrai_a_sort_by_Shell::TestTaskSequential::ValidationImpl() {
  return true;
  if (input_.empty()) {
    return false;
  }

  return task_data->inputs_count[0] == task_data->outputs_count[0];
}

bool makadrai_a_sort_by_Shell::TestTaskSequential::RunImpl() {
  // Multiply matrices
  /*for (int i = 0; i < rc_size_; ++i) {
    for (int j = 0; j < rc_size_; ++j) {
      for (int k = 0; k < rc_size_; ++k) {
        output_[(i * rc_size_) + j] += input_[(i * rc_size_) + k] * input_[(k * rc_size_) + j];
      }
    }
  }*/

  hybridShellMergeSort(input_);

  return true;
}

bool makadrai_a_sort_by_Shell::TestTaskSequential::PostProcessingImpl() {
  /*for (size_t i = 0; i < size_; i++) {
    reinterpret_cast<int *>(task_data->outputs[0])[i] = input_[i];
  }*/

  auto* output_raw = reinterpret_cast<int*>(task_data->outputs[0]);
  std::ranges::copy(input_.begin(), input_.end(), output_raw);

  return true;
}
