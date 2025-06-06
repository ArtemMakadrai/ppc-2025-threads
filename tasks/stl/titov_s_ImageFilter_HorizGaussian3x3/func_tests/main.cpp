#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

#include "core/task/include/task.hpp"
#include "stl/titov_s_ImageFilter_HorizGaussian3x3/include/ops_stl.hpp"

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_10_1) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 1.0);
  std::vector<double> output_image(kWidth * kHeight, 1.0);
  std::vector<double> expected_output(kWidth * kHeight, 1.0);
  std::vector<int> kernel = {1, 2, 1};

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      if (j == 0 || j == kWidth - 1) {
        expected_output[((i * kWidth)) + j] = 0.75;
      } else {
        expected_output[((i * kWidth)) + j] = 1.0;
      }
    }
  }

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[((i * kWidth)) + j], expected_output[((i * kWidth)) + j], 1e-5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_10_vertical_lines) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 0.0);
  std::vector<double> output_image(kWidth * kHeight, 0.0);
  std::vector<double> expected_output(kWidth * kHeight, 0.0);
  std::vector<int> kernel = {1, 2, 1};

  for (size_t i = 0; i < kHeight; ++i) {
    input_image[((i * kWidth)) + 2] = 1.0;
    input_image[((i * kWidth)) + 7] = 1.0;
  }

  for (size_t i = 0; i < kHeight; ++i) {
    expected_output[((i * kWidth)) + 1] = 0.25;
    expected_output[((i * kWidth)) + 2] = 0.5;
    expected_output[((i * kWidth)) + 3] = 0.25;
    expected_output[((i * kWidth)) + 6] = 0.25;
    expected_output[((i * kWidth)) + 7] = 0.5;
    expected_output[((i * kWidth)) + 8] = 0.25;
  }

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[((i * kWidth)) + j], expected_output[((i * kWidth)) + j], 1e-5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_horizontal_lines) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 0.0);
  std::vector<double> output_image(kWidth * kHeight, 0.0);
  std::vector<double> expected_output(kWidth * kHeight, 0.0);
  std::vector<int> kernel = {1, 2, 1};

  for (size_t j = 0; j < kWidth; ++j) {
    input_image[(2 * kWidth) + j] = 1.0;
    input_image[(7 * kWidth) + j] = 1.0;
  }

  expected_output[2 * kWidth] = expected_output[(3 * kWidth) - 1] = expected_output[7 * kWidth] =
      expected_output[(8 * kWidth) - 1] = 0.75;
  for (size_t i = 1; i < kWidth - 1; ++i) {
    expected_output[(2 * kWidth) + i] = 1.0;
    expected_output[(7 * kWidth) + i] = 1.0;
  }

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[((i * kWidth)) + j], expected_output[((i * kWidth)) + j], 1e-5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_empty_image) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 0.0);
  std::vector<double> output_image(kWidth * kHeight, 0.0);
  std::vector<double> expected_output(kWidth * kHeight, 0.0);
  std::vector<int> kernel = {1, 2, 1};

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[(i * kWidth) + j], expected_output[(i * kWidth) + j], 1e-5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_sharp_transitions) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 0.0);
  std::vector<double> output_image(kWidth * kHeight, 0.0);
  std::vector<double> expected_output(kWidth * kHeight, 0.0);
  std::vector<int> kernel = {1, 2, 1};

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth / 2; ++j) {
      input_image[(i * kWidth) + j] = 0.0;
    }
    for (size_t j = kWidth / 2; j < kWidth; ++j) {
      input_image[(i * kWidth) + j] = 1.0;
    }
  }

  for (size_t i = 0; i < kHeight; ++i) {
    expected_output[(i * kWidth) + 4] = 0.25;
    expected_output[(i * kWidth) + 5] = 0.75;
    expected_output[(i * kWidth) + 6] = 1.0;
    expected_output[(i * kWidth) + 7] = 1.0;
    expected_output[(i * kWidth) + 8] = 1.0;
    expected_output[(i * kWidth) + 9] = 0.75;
  }

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[(i * kWidth) + j], expected_output[(i * kWidth) + j], 1e-5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_smooth_gradients) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 0.0);
  std::vector<double> output_image(kWidth * kHeight, 0.0);
  std::vector<double> expected_output(kWidth * kHeight, 0.0);
  std::vector<int> kernel = {1, 2, 1};

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      input_image[(i * kWidth) + j] = expected_output[(i * kWidth) + j] = static_cast<double>(j) / (kWidth - 1);
    }
  }

  for (size_t i = 0; i < kHeight; ++i) {
    expected_output[(i * kWidth)] = 0.03;
    expected_output[((i + 1) * kWidth) - 1] = 0.72;
  }

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[(i * kWidth) + j], expected_output[(i * kWidth) + j], 0.5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_all_max) {
  constexpr size_t kWidth = 10;
  constexpr size_t kHeight = 10;
  std::vector<double> input_image(kWidth * kHeight, 255.0);
  std::vector<double> output_image(kWidth * kHeight, 0.0);
  std::vector<double> expected_output(kWidth * kHeight, 255.0);
  std::vector<int> kernel = {1, 2, 1};

  for (size_t i = 0; i < kHeight; ++i) {
    expected_output[(i * kWidth)] = 191.25;
    expected_output[((i + 1) * kWidth) - 1] = 191.25;
  }

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  for (size_t i = 0; i < kHeight; ++i) {
    for (size_t j = 0; j < kWidth; ++j) {
      ASSERT_NEAR(output_image[(i * kWidth) + j], expected_output[(i * kWidth) + j], 1e-5);
    }
  }
}

TEST(titov_s_image_filter_horiz_gaussian3x3_stl, test_random_invariant_mean) {
  constexpr size_t kWidth = 100;
  constexpr size_t kHeight = 100;

  std::vector<double> input_image(kWidth * kHeight);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 255.0);

  for (size_t i = 0; i < kWidth * kHeight; ++i) {
    input_image[i] = dis(gen);
  }

  std::vector<int> kernel = {1, 2, 1};

  std::vector<double> output_image(kWidth * kHeight, 0.0);

  auto task_data_stl = std::make_shared<ppc::core::TaskData>();
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(input_image.data()));
  task_data_stl->inputs.emplace_back(reinterpret_cast<uint8_t*>(kernel.data()));
  task_data_stl->inputs_count.emplace_back(input_image.size());
  task_data_stl->outputs.emplace_back(reinterpret_cast<uint8_t*>(output_image.data()));
  task_data_stl->outputs_count.emplace_back(output_image.size());

  titov_s_image_filter_horiz_gaussian3x3_stl::GaussianFilterSTL gaussian_filter_stl(task_data_stl);

  ASSERT_EQ(gaussian_filter_stl.Validation(), true);

  gaussian_filter_stl.PreProcessing();
  gaussian_filter_stl.Run();
  gaussian_filter_stl.PostProcessing();

  double avg_input =
      std::accumulate(input_image.begin(), input_image.end(), 0.0) / static_cast<double>(input_image.size());
  double avg_output =
      std::accumulate(output_image.begin(), output_image.end(), 0.0) / static_cast<double>(output_image.size());

  ASSERT_NEAR(avg_input, avg_output, 1);
}
