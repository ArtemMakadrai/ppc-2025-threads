#include <gtest/gtest.h>

#include <chrono>
#include <cstdint>
#include <memory>
#include <random>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "core/task/include/task.hpp"
#include "stl/sotskov_a_shell_sorting_with_simple_merging/include/ops_stl.hpp"

namespace sotskov_a_shell_sorting_with_simple_merging_stl {
namespace {
struct RandomVectorParams {
  int size;
  int min_value;
  int max_value;
};
struct SortingTestParams {
  std::vector<int> expected;
  std::vector<int> input;
};

std::vector<int> GenerateRandomVector(const RandomVectorParams &params) {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<int> distribution(params.min_value, params.max_value);

  std::vector<int> random_vector(params.size);
  for (int &element : random_vector) {
    element = distribution(generator);
  }

  return random_vector;
}
}  // namespace
}  // namespace sotskov_a_shell_sorting_with_simple_merging_stl

TEST(sotskov_a_shell_sorting_with_simple_merging_stl, test_pipeline_run) {
  sotskov_a_shell_sorting_with_simple_merging_stl::RandomVectorParams params = {
      .size = 2000000, .min_value = 0, .max_value = 500};
  std::vector<int> in = sotskov_a_shell_sorting_with_simple_merging_stl::GenerateRandomVector(params);
  std::vector<int> out(in.size(), 0);
  std::vector<int> expected = in;

  sotskov_a_shell_sorting_with_simple_merging_stl::ShellSortWithSimpleMerging(expected);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  auto test_task_stl = std::make_shared<sotskov_a_shell_sorting_with_simple_merging_stl::TestTaskSTL>(task_data_stl);

  // Create Perf attributes
  auto perf_attr = std::make_shared<ppc::core::PerfAttr>();
  perf_attr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perf_attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perf_results = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perf_analyzer = std::make_shared<ppc::core::Perf>(test_task_stl);
  perf_analyzer->PipelineRun(perf_attr, perf_results);
  ppc::core::Perf::PrintPerfStatistic(perf_results);

  ASSERT_EQ(out, expected);
}

TEST(sotskov_a_shell_sorting_with_simple_merging_stl, test_task_run) {
  sotskov_a_shell_sorting_with_simple_merging_stl::RandomVectorParams params = {
      .size = 2000000, .min_value = 0, .max_value = 500};
  std::vector<int> in = sotskov_a_shell_sorting_with_simple_merging_stl::GenerateRandomVector(params);
  std::vector<int> out(in.size(), 0);
  std::vector<int> expected = in;

  sotskov_a_shell_sorting_with_simple_merging_stl::ShellSortWithSimpleMerging(expected);

  // Create task_data
  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_stl->inputs_count.emplace_back(in.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_stl->outputs_count.emplace_back(out.size());

  // Create Task
  auto test_task_stl = std::make_shared<sotskov_a_shell_sorting_with_simple_merging_stl::TestTaskSTL>(task_data_stl);

  // Create Perf attributes
  auto perf_attr = std::make_shared<ppc::core::PerfAttr>();
  perf_attr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perf_attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Create and init perf results
  auto perf_results = std::make_shared<ppc::core::PerfResults>();

  // Create Perf analyzer
  auto perf_analyzer = std::make_shared<ppc::core::Perf>(test_task_stl);
  perf_analyzer->TaskRun(perf_attr, perf_results);
  ppc::core::Perf::PrintPerfStatistic(perf_results);

  ASSERT_EQ(out, expected);
}