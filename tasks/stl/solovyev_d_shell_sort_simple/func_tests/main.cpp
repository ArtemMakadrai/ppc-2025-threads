#include <gtest/gtest.h>

#include <climits>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#include "core/task/include/task.hpp"
#include "stl/solovyev_d_shell_sort_simple/include/ops_stl.hpp"

namespace {
std::vector<int> GetRandomVector(int sz) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) {
    vec[i] = (int)((gen() % (200)) - 100);
  }
  return vec;
}
bool IsSorted(std::vector<int> data) {
  int last = INT_MIN;
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i] < last) {
      return false;
    }
    last = data[i];
  }
  return true;
}
}  // namespace

TEST(solovyev_d_shell_sort_simple_stl, sort_empty) {
  // Create data
  std::vector<int> in = {};
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_10_negative) {
  // Create data
  std::vector<int> in = {1, 5, -7, 3, 7, -3, 8, 4, -1, 6};
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_10) {
  // Create data
  std::vector<int> in = {1, 5, 7, 3, 7, 3, 8, 4, 1, 6};
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_20) {
  // Create data
  std::vector<int> in = {1, 5, 7, 3, 7, 3, 8, 4, 1, 6, 4, 6, 7, 3, 12, 21, 65, 43, 1, 54, 34, 76};
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_30_negative) {
  // Create data
  std::vector<int> in = {1,   5,   7, 3,  7,  3,  -8,   4,  1,   6,   4,  6, 7,   3, -12, 21,
                         -65, -43, 1, 54, 34, 76, -345, 21, 765, 346, 34, 1, 434, 8, 343, -88};
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_30) {
  // Create data
  std::vector<int> in = {1,  5,  7, 3,  7,  3,  8,   4,  1,   6,   4,  6, 7,   3, 12,  21,
                         65, 43, 1, 54, 34, 76, 345, 21, 765, 346, 34, 1, 434, 8, 343, 88};
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_rand_10) {
  // Create data
  std::vector<int> in = GetRandomVector(10);
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}

TEST(solovyev_d_shell_sort_simple_stl, sort_rand_50) {
  // Create data
  std::vector<int> in = GetRandomVector(50);
  std::vector<int> out(in.size(), 0);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  solovyev_d_shell_sort_simple_stl::TaskSTL task_stl(task_data_stl);
  ASSERT_EQ(task_stl.Validation(), true);
  task_stl.PreProcessing();
  task_stl.Run();
  task_stl.PostProcessing();
  ASSERT_TRUE(IsSorted(out));
}