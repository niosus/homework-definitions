#include "tui_pixelator/stb_image.hpp"

#include <gtest/gtest.h>

#include <ftxui/screen/color.hpp>

namespace {
using pixelator::StbImage;
const auto kImagePath{"../../tui_pixelator/test_data/test.png"};
const auto kBlack{ftxui::Color::RGB(0, 0, 0)};
const auto kWhite{ftxui::Color::RGB(255, 255, 255)};
}  // namespace

TEST(StbImageValidationTest, Initialization) {
  const StbImage image{kImagePath};
  ASSERT_FALSE(image.empty())
      << "Make sure the image is available at " << kImagePath
      << " with respect to the root of the project.";
  ASSERT_EQ(image.rows(), 6);
  ASSERT_EQ(image.cols(), 4);

  ASSERT_EQ(image.at(0, 0), kBlack);
  ASSERT_EQ(image.at(1, 1), kBlack);
  ASSERT_EQ(image.at(2, 2), kBlack);

  ASSERT_EQ(image.at(3, 0), kWhite);
  ASSERT_EQ(image.at(4, 1), kWhite);
  ASSERT_EQ(image.at(5, 2), kWhite);
}

TEST(StbImageValidationTest, MoveConstructor) {
  StbImage image{kImagePath};
  ASSERT_FALSE(image.empty())
      << "Make sure the image is available at " << kImagePath
      << " with respect to the root of the project.";
  const StbImage image_other{std::move(image)};
  ASSERT_TRUE(image.empty());
  ASSERT_FALSE(image_other.empty());
  ASSERT_EQ(image_other.rows(), 6);
  ASSERT_EQ(image_other.cols(), 4);

  ASSERT_EQ(image_other.at(0, 0), kBlack);
  ASSERT_EQ(image_other.at(1, 1), kBlack);
  ASSERT_EQ(image_other.at(2, 2), kBlack);

  ASSERT_EQ(image_other.at(3, 0), kWhite);
  ASSERT_EQ(image_other.at(4, 1), kWhite);
  ASSERT_EQ(image_other.at(5, 2), kWhite);
}

TEST(StbImageValidationTest, MoveAssignmentOperator) {
  StbImage image_to_move_to{};
  ASSERT_TRUE(image_to_move_to.empty());
  StbImage image{kImagePath};
  image_to_move_to = std::move(image);
  ASSERT_TRUE(image.empty());
  ASSERT_FALSE(image_to_move_to.empty());

  ASSERT_EQ(image_to_move_to.rows(), 6);
  ASSERT_EQ(image_to_move_to.cols(), 4);

  ASSERT_EQ(image_to_move_to.at(0, 0), kBlack);
  ASSERT_EQ(image_to_move_to.at(1, 1), kBlack);
  ASSERT_EQ(image_to_move_to.at(2, 2), kBlack);

  ASSERT_EQ(image_to_move_to.at(3, 0), kWhite);
  ASSERT_EQ(image_to_move_to.at(4, 1), kWhite);
  ASSERT_EQ(image_to_move_to.at(5, 2), kWhite);
}