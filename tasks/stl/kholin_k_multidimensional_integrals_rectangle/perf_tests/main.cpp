#include <gtest/gtest.h>

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "core/task/include/task.hpp"
#include "stl/kholin_k_multidimensional_integrals_rectangle/include/ops_stl.hpp"

TEST(kholin_k_multidimensional_integrals_rectangle_stl, test_pipeline_run) {
  // Create data
  size_t dim = 3;
  std::vector<double> values{0.0, 0.0, 0.0};
  auto f = [](const std::vector<double> &f_values) {
    return std::cos((f_values[0] * f_values[0]) + (f_values[1] * f_values[1]) + (f_values[2] * f_values[2])) *
           (1 + (f_values[0] * f_values[0]) + (f_values[1] * f_values[1]) + (f_values[2] * f_values[2]));
  };
  std::vector<double> in_lower_limits{-1, 2, -3};
  std::vector<double> in_upper_limits{8, 8, 2};
  double n = 150.0;
  std::vector<double> out_i(1, 0.0);

  auto f_object = std::make_unique<std::function<double(const std::vector<double> &)>>(f);

  // Create task_data
  std::shared_ptr<ppc::core::TaskData> task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(&dim));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(values.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(f_object.get()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_lower_limits.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_upper_limits.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(&n));
  task_data_stl->inputs_count.emplace_back(values.size());
  task_data_stl->inputs_count.emplace_back(in_lower_limits.size());
  task_data_stl->inputs_count.emplace_back(in_upper_limits.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out_i.data()));
  task_data_stl->outputs_count.emplace_back(out_i.size());

  // Create Task
  auto test_task_stl = std::make_shared<kholin_k_multidimensional_integrals_rectangle_stl::TestTaskSTL>(task_data_stl);

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
  double ref_i = 12;
  double locality = fabs(ref_i - out_i[0]);
  ASSERT_NEAR(locality, 0, 1);
}

TEST(kholin_k_multidimensional_integrals_rectangle_stl, test_task_run) {
  // Create data
  size_t dim = 3;
  std::vector<double> values{0.0, 0.0, 0.0};
  auto f = [](const std::vector<double> &f_values) {
    return std::cos((f_values[0] * f_values[0]) + (f_values[1] * f_values[1]) + (f_values[2] * f_values[2])) *
           (1 + (f_values[0] * f_values[0]) + (f_values[1] * f_values[1]) + (f_values[2] * f_values[2]));
  };
  std::vector<double> in_lower_limits{-1, 2, -3};
  std::vector<double> in_upper_limits{8, 8, 2};
  double n = 150.0;
  std::vector<double> out_i(1, 0.0);

  auto f_object = std::make_unique<std::function<double(const std::vector<double> &)>>(f);

  // Create task_data
  std::shared_ptr<ppc::core::TaskData> task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(&dim));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(values.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(f_object.get()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_lower_limits.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in_upper_limits.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t *>(&n));
  task_data_stl->inputs_count.emplace_back(values.size());
  task_data_stl->inputs_count.emplace_back(in_lower_limits.size());
  task_data_stl->inputs_count.emplace_back(in_upper_limits.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out_i.data()));
  task_data_stl->outputs_count.emplace_back(out_i.size());

  // Create Task
  auto test_task_stl = std::make_shared<kholin_k_multidimensional_integrals_rectangle_stl::TestTaskSTL>(task_data_stl);

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
  double ref_i = 12;
  double locality = fabs(ref_i - out_i[0]);
  ASSERT_NEAR(locality, 0, 1);
}