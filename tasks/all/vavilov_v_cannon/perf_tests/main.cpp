#include <gtest/gtest.h>

#include <boost/mpi/communicator.hpp>
#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

#include "all/vavilov_v_cannon/include/ops_all.hpp"
#include "core/perf/include/perf.hpp"
#include "core/task/include/task.hpp"

TEST(vavilov_v_cannon_all, test_pipeline_run) {
  boost::mpi::communicator world;
  constexpr int kN = 900;
  std::vector<double> a(kN * kN, 1.0);
  std::vector<double> b(kN * kN, 1.0);
  std::vector<double> c(kN * kN, 0.0);
  std::vector<double> expected_output(kN * kN, kN);

  auto task_data_all = std::make_shared<ppc::core::TaskData>();
  if (world.rank() == 0) {
    task_data_all->inputs.emplace_back(reinterpret_cast<uint8_t *>(a.data()));
    task_data_all->inputs.emplace_back(reinterpret_cast<uint8_t *>(b.data()));
    task_data_all->inputs_count.emplace_back(a.size());
    task_data_all->inputs_count.emplace_back(b.size());
    task_data_all->outputs.emplace_back(reinterpret_cast<uint8_t *>(c.data()));
    task_data_all->outputs_count.emplace_back(c.size());
  }

  auto task_all = std::make_shared<vavilov_v_cannon_all::CannonALL>(task_data_all);

  auto perf_attr = std::make_shared<ppc::core::PerfAttr>();
  perf_attr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perf_attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perf_results = std::make_shared<ppc::core::PerfResults>();

  auto perf_analyzer = std::make_shared<ppc::core::Perf>(task_all);
  perf_analyzer->PipelineRun(perf_attr, perf_results);
  if (world.rank() == 0) {
    ppc::core::Perf::PrintPerfStatistic(perf_results);
    for (int i = 0; i < kN * kN; i++) {
      ASSERT_EQ(expected_output[i], c[i]);
    }
  }
}

TEST(vavilov_v_cannon_all, test_task_run) {
  boost::mpi::communicator world;
  constexpr int kN = 900;
  std::vector<double> a(kN * kN, 1.0);
  std::vector<double> b(kN * kN, 1.0);
  std::vector<double> c(kN * kN, 0.0);
  std::vector<double> expected_output(kN * kN, kN);

  auto task_data_all = std::make_shared<ppc::core::TaskData>();
  if (world.rank() == 0) {
    task_data_all->inputs.emplace_back(reinterpret_cast<uint8_t *>(a.data()));
    task_data_all->inputs.emplace_back(reinterpret_cast<uint8_t *>(b.data()));
    task_data_all->inputs_count.emplace_back(a.size());
    task_data_all->inputs_count.emplace_back(b.size());
    task_data_all->outputs.emplace_back(reinterpret_cast<uint8_t *>(c.data()));
    task_data_all->outputs_count.emplace_back(c.size());
  }

  auto task_all = std::make_shared<vavilov_v_cannon_all::CannonALL>(task_data_all);

  auto perf_attr = std::make_shared<ppc::core::PerfAttr>();
  perf_attr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perf_attr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  auto perf_results = std::make_shared<ppc::core::PerfResults>();

  auto perf_analyzer = std::make_shared<ppc::core::Perf>(task_all);
  perf_analyzer->TaskRun(perf_attr, perf_results);
  if (world.rank() == 0) {
    ppc::core::Perf::PrintPerfStatistic(perf_results);
    for (int i = 0; i < kN * kN; i++) {
      ASSERT_EQ(expected_output[i], c[i]);
    }
  }
}
