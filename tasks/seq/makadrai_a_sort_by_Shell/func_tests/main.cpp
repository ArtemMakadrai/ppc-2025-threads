#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "core/task/include/task.hpp"
#include "core/util/include/util.hpp"
#include "seq/makadrai_a_sort_by_Shell/include/ops_seq.hpp"

TEST(makadrai_a_sort_by_Shell, makadrai_a_sort_by_Shell_size_50) {
  constexpr size_t kCount = 50;
  // Create data
  std::vector<int> in(kCount, 0);
  std::vector<int> out(kCount, 0);
  std::srand(std::time(0));
  for (size_t i = 0; i < kCount; i++) {
    in[i] = std::rand() % 100;
  }

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  makadrai_a_sort_by_Shell::TestTaskSequential test_task_sequential(task_data_seq);
  ASSERT_EQ(test_task_sequential.ValidationImpl(), true);
  test_task_sequential.PreProcessingImpl();
  test_task_sequential.RunImpl();
  test_task_sequential.PostProcessingImpl();

  bool f = true;
  for (size_t i = 1; i < kCount; i++) {
    if (out[i] < out[i - 1]) {
      f = false;
    }
  }
  int sum = 0;
  for (size_t i = 0; i < kCount; i++) {
    sum += out[i];
  }
  if (sum == 0) {
    f = false;
  }

  EXPECT_TRUE(f);
}

TEST(makadrai_a_sort_by_Shell, makadrai_a_sort_by_Shell_size_from_file) {
  std::string line;
  std::ifstream test_file(ppc::util::GetAbsolutePath("seq/makadrai_a_sort_by_Shell/data/test.txt"));
  if (test_file.is_open()) {
    getline(test_file, line);
  }
  test_file.close();

  size_t count = std::stoi(line);
  count = 10;
  // Create data
  std::vector<int> in(count, 0);
  std::vector<int> out(count, 0);
  std::srand(std::time(0));
  for (size_t i = 0; i < count; i++) {
    in[i] = std::rand() % 100;
  }

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  makadrai_a_sort_by_Shell::TestTaskSequential test_task_sequential(task_data_seq);
  ASSERT_EQ(test_task_sequential.ValidationImpl(), true);
  test_task_sequential.PreProcessingImpl();
  test_task_sequential.RunImpl();
  test_task_sequential.PostProcessingImpl();

  bool f = true;

  for (size_t i = 1; i < count; i++) {
    if (out[i] < out[i - 1]) {
      f = false;
    }
  }
  bool f1 = true;
  int sum = 0;
  for (size_t i = 0; i < count; i++) {
    sum += out[i];
  }
  if (sum == 0) {
    f1 = false;
  }

  for (size_t i = 0; i < 10; i++) std::cout << in[i] << " ";
  std::cout << std::endl;
  for (size_t i = 0; i < 10; i++) std::cout << out[i] << " ";
  EXPECT_TRUE((f && f1));
}

TEST(makadrai_a_sort_by_Shell, makadrai_a_sort_by_Shell_vector_from_file) {
  std::string line;
  std::ifstream test_file(ppc::util::GetAbsolutePath("seq/makadrai_a_sort_by_Shell/data/test_1.txt"));

  std::vector<int> numbers;
  if (test_file.is_open()) {
    int num;
    while (test_file >> num) {
      numbers.push_back(num);
    }
    test_file.close();
  }
  const size_t count = numbers.size();

  // Create data
  std::vector<int> in(count, 0);
  std::vector<int> out(count, 0);

  for (size_t i = 0; i < count; i++) {
    in[i] = numbers[i];
  }

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  makadrai_a_sort_by_Shell::TestTaskSequential test_task_sequential(task_data_seq);
  ASSERT_EQ(test_task_sequential.ValidationImpl(), true);
  test_task_sequential.PreProcessingImpl();
  test_task_sequential.RunImpl();
  test_task_sequential.PostProcessingImpl();

  bool f = true;

  for (size_t i = 1; i < count; i++) {
    if (out[i] < out[i - 1]) {
      f = false;
    }
  }
  int sum = 0;
  for (size_t i = 0; i < count; i++) {
    sum += out[i];
  }
  if (sum == 0) {
    f = false;
  }

  EXPECT_TRUE(f);
}

TEST(makadrai_a_sort_by_Shell, makadrai_a_sort_by_Shell_size_null) {
  size_t kCount = 0;
  // Create data
  std::vector<int> in(kCount, 0);
  std::vector<int> out(kCount, 0);
  std::srand(std::time(0));
  for (size_t i = 0; i < kCount; i++) {
    in[i] = std::rand() % 100;
  }

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  makadrai_a_sort_by_Shell::TestTaskSequential test_task_sequential(task_data_seq);
  ASSERT_EQ(test_task_sequential.ValidationImpl(), true);
  test_task_sequential.PreProcessingImpl();
  test_task_sequential.RunImpl();
  test_task_sequential.PostProcessingImpl();

  bool f = true;

  for (size_t i = 1; i < kCount; i++) {
    if (out[i] < out[i - 1]) {
      f = false;
    }
  }
  int sum = 0;
  for (size_t i = 0; i < kCount; i++) {
    sum += out[i];
  }
  if (sum == 0) {
    f = false;
  }
}

TEST(makadrai_a_sort_by_Shell, makadrai_a_sort_by_Shell_size_1000) {
  size_t kCount = 1000;
  // Create data
  std::vector<int> in(kCount, 0);
  std::vector<int> out(kCount, 0);
  std::srand(std::time(0));
  for (size_t i = 0; i < kCount; i++) {
    in[i] = std::rand() % 100;
  }

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  makadrai_a_sort_by_Shell::TestTaskSequential test_task_sequential(task_data_seq);
  ASSERT_EQ(test_task_sequential.ValidationImpl(), true);
  test_task_sequential.PreProcessingImpl();
  test_task_sequential.RunImpl();
  test_task_sequential.PostProcessingImpl();

  bool f = true;

  for (size_t i = 1; i < kCount; i++) {
    if (out[i] < out[i - 1]) {
      f = false;
    }
  }
  int sum = 0;
  for (size_t i = 0; i < kCount; i++) {
    sum += out[i];
  }
  if (sum == 0) {
    f = false;
  }
  EXPECT_TRUE(f);
}

TEST(makadrai_a_sort_by_Shell, makadrai_a_sort_by_Shell_size_1) {
  size_t kCount = 1;
  // Create data
  std::vector<int> in(kCount, 0);
  std::vector<int> out(kCount, 0);
  std::srand(std::time(0));
  for (size_t i = 0; i < kCount; i++) {
    in[i] = std::rand() % 100;
  }

  // Create task_data
  auto task_data_seq = std::make_shared<ppc::core::TaskData>();
  task_data_seq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  task_data_seq->inputs_count.emplace_back(in.size());
  task_data_seq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  task_data_seq->outputs_count.emplace_back(out.size());

  // Create Task
  makadrai_a_sort_by_Shell::TestTaskSequential test_task_sequential(task_data_seq);
  ASSERT_EQ(test_task_sequential.ValidationImpl(), true);
  test_task_sequential.PreProcessingImpl();
  test_task_sequential.RunImpl();
  test_task_sequential.PostProcessingImpl();

  bool f = true;

  for (size_t i = 1; i < kCount; i++) {
    if (out[i] < out[i - 1]) {
      f = false;
    }
  }
  int sum = 0;
  for (size_t i = 0; i < kCount; i++) {
    sum += out[i];
  }
  if (sum == 0) {
    f = false;
  }

  EXPECT_TRUE(f);
}