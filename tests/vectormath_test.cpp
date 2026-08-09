#include "vectormath.h"

#include <gtest/gtest.h>

#include <sstream>

#include "common.h"

// pass Float to gtest macro template, to test both double and float easily
#define EXPECT_FLOATINGPOINT_EQ(val1, val2)                                 \
  EXPECT_PRED_FORMAT2(::testing::internal::CmpHelperFloatingPointEQ<Float>, \
                      val1, val2)

// ---------------------------------------------------------
// TupleData & Core Tuple Tests
// ---------------------------------------------------------

TEST(TupleTest, ConstructorAndDimensions) {
  Vec2 v2(1, 2);
  EXPECT_EQ(v2.dimension(), 2);
  EXPECT_EQ(Vec2::Dim, 2);

  Vec3 v3(1, 2, 3);
  EXPECT_EQ(v3.dimension(), 3);
  EXPECT_EQ(Vec3::Dim, 3);

  Vec4 v4(1, 2, 3, 4);
  EXPECT_EQ(v4.dimension(), 4);
  EXPECT_EQ(Vec4::Dim, 4);
}

// ---------------------------------------------------------
// CRTP Skills Tests
// ---------------------------------------------------------

TEST(TupleMathTest, Addable) {
  Vec4 v1(1.0, 2.0, 3.0, 4.0);
  Vec4 v2(5.0, 6.0, 7.0, 8.0);

  Vec4 v3 = v1 + v2;
  EXPECT_FLOATINGPOINT_EQ(v3.x, 6.0);
  EXPECT_FLOATINGPOINT_EQ(v3.y, 8.0);
  EXPECT_FLOATINGPOINT_EQ(v3.z, 10.0);
  EXPECT_FLOATINGPOINT_EQ(v3.w, 12.0);

  v1 += v2;
  EXPECT_FLOATINGPOINT_EQ(v1.x, 6.0);
  EXPECT_FLOATINGPOINT_EQ(v1.y, 8.0);
  EXPECT_FLOATINGPOINT_EQ(v1.z, 10.0);
  EXPECT_FLOATINGPOINT_EQ(v1.w, 12.0);
}

TEST(TupleMathTest, Subtractable) {
  Vec4 v1(10.0, 20.0, 30.0, 40.0);
  Vec4 v2(1.0, 2.0, 3.0, 4.0);

  Vec4 v3 = v1 - v2;
  EXPECT_FLOATINGPOINT_EQ(v3.x, 9.0);
  EXPECT_FLOATINGPOINT_EQ(v3.y, 18.0);
  EXPECT_FLOATINGPOINT_EQ(v3.z, 27.0);
  EXPECT_FLOATINGPOINT_EQ(v3.w, 36.0);

  v1 -= v2;
  EXPECT_FLOATINGPOINT_EQ(v1.x, 9.0);
  EXPECT_FLOATINGPOINT_EQ(v1.y, 18.0);
  EXPECT_FLOATINGPOINT_EQ(v1.z, 27.0);
  EXPECT_FLOATINGPOINT_EQ(v1.w, 36.0);
}

TEST(TupleMathTest, Multipliable) {
  Vec4 v(2.0, 3.0, 4.0, 5.0);

  Vec4 v_mul1 = v * 2.0;
  EXPECT_FLOATINGPOINT_EQ(v_mul1.x, 4.0);
  EXPECT_FLOATINGPOINT_EQ(v_mul1.y, 6.0);
  EXPECT_FLOATINGPOINT_EQ(v_mul1.z, 8.0);
  EXPECT_FLOATINGPOINT_EQ(v_mul1.w, 10.0);

  Vec4 v_mul2 = 3.0 * v;
  EXPECT_FLOATINGPOINT_EQ(v_mul2.x, 6.0);
  EXPECT_FLOATINGPOINT_EQ(v_mul2.y, 9.0);
  EXPECT_FLOATINGPOINT_EQ(v_mul2.z, 12.0);
  EXPECT_FLOATINGPOINT_EQ(v_mul2.w, 15.0);

  v *= 4.0;
  EXPECT_FLOATINGPOINT_EQ(v.x, 8.0);
  EXPECT_FLOATINGPOINT_EQ(v.y, 12.0);
  EXPECT_FLOATINGPOINT_EQ(v.z, 16.0);
  EXPECT_FLOATINGPOINT_EQ(v.w, 20.0);
}

TEST(TupleMathTest, Divideable) {
  Vec4 v(4.0, 8.0, 12.0, 16.0);

  Vec4 v_div = v / 2.0;
  EXPECT_FLOATINGPOINT_EQ(v_div.x, 2.0);
  EXPECT_FLOATINGPOINT_EQ(v_div.y, 4.0);
  EXPECT_FLOATINGPOINT_EQ(v_div.z, 6.0);
  EXPECT_FLOATINGPOINT_EQ(v_div.w, 8.0);

  v /= 4.0;
  EXPECT_FLOATINGPOINT_EQ(v.x, 1.0);
  EXPECT_FLOATINGPOINT_EQ(v.y, 2.0);
  EXPECT_FLOATINGPOINT_EQ(v.z, 3.0);
  EXPECT_FLOATINGPOINT_EQ(v.w, 4.0);
}

TEST(TupleMathTest, Negateable) {
  Point2 p(1.0, -2.0);
  Point2 p_neg = -p;

  // Test that the return value is correctly negated
  EXPECT_FLOATINGPOINT_EQ(p_neg.x, -1.0);
  EXPECT_FLOATINGPOINT_EQ(p_neg.y, 2.0);

  // Test that the original value is UNMODIFIED
  EXPECT_FLOATINGPOINT_EQ(p.x, 1.0);
  EXPECT_FLOATINGPOINT_EQ(p.y, -2.0);
}

TEST(TupleMathTest, HasL2Distance) {
  Vec2 v2(3.0, 4.0);
  EXPECT_FLOATINGPOINT_EQ(length_squared(v2), 25.0);
  EXPECT_FLOATINGPOINT_EQ(length(v2), 5.0);

  Vec3 v3(2.0, 3.0, 6.0);
  EXPECT_FLOATINGPOINT_EQ(length_squared(v3), 49.0);  // 4 + 9 + 36 = 49
  EXPECT_FLOATINGPOINT_EQ(length(v3), 7.0);

  Vec4 v4(1.0, 2.0, 3.0, 4.0);
  EXPECT_FLOATINGPOINT_EQ(length_squared(v4), 30.0);  // 1 + 4 + 9 + 16 = 30
}

TEST(TupleMathTest, DotProductable) {
  Vec3 v1(1.0, 2.0, 3.0);
  Vec3 v2(4.0, 5.0, 6.0);

  Float dot_product_3d = dot(v1, v2);
  // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
  EXPECT_FLOATINGPOINT_EQ(dot_product_3d, 32.0);

  Vec4 v3(1.0, 2.0, 3.0, 4.0);
  Vec4 v4(2.0, 3.0, 4.0, 5.0);

  Float dot_product_4d = dot(v3, v4);
  // 1*2 + 2*3 + 3*4 + 4*5 = 2 + 6 + 12 + 20 = 40
  EXPECT_FLOATINGPOINT_EQ(dot_product_4d, 40.0);
}

TEST(TupleMathTest, CrossProductable) {
  Vec3 i(1.0, 0.0, 0.0);
  Vec3 j(0.0, 1.0, 0.0);

  Vec3 k = cross(i, j);
  EXPECT_FLOATINGPOINT_EQ(k.x, 0.0);
  EXPECT_FLOATINGPOINT_EQ(k.y, 0.0);
  EXPECT_FLOATINGPOINT_EQ(k.z, 1.0);

  Vec3 neg_k = cross(j, i);
  EXPECT_FLOATINGPOINT_EQ(neg_k.x, 0.0);
  EXPECT_FLOATINGPOINT_EQ(neg_k.y, 0.0);
  EXPECT_FLOATINGPOINT_EQ(neg_k.z, -1.0);
}

TEST(TupleMathTest, Normalize) {
  // 2D Normalization
  Vec2 v2(3.0, 4.0);
  Vec2 v2_norm = normalize(v2);

  EXPECT_FLOATINGPOINT_EQ(v2_norm.x, 0.6);
  EXPECT_FLOATINGPOINT_EQ(v2_norm.y, 0.8);
  EXPECT_FLOATINGPOINT_EQ(length(v2_norm), 1.0);

  // 3D Normalization
  // A 3-4-5 triangle mapped to the Y and Z axes
  Vec3 v3(0.0, 3.0, 4.0);
  Vec3 v3_norm = normalize(v3);

  EXPECT_FLOATINGPOINT_EQ(v3_norm.x, 0.0);
  EXPECT_FLOATINGPOINT_EQ(v3_norm.y, 0.6);
  EXPECT_FLOATINGPOINT_EQ(v3_norm.z, 0.8);
  EXPECT_FLOATINGPOINT_EQ(length(v3_norm), 1.0);

  // 4D Normalization
  // Length of (1, 1, 1, 1) is sqrt(1^2 + 1^2 + 1^2 + 1^2) = 2.0
  Vec4 v4(1.0, 1.0, 1.0, 1.0);
  Vec4 v4_norm = normalize(v4);

  EXPECT_FLOATINGPOINT_EQ(v4_norm.x, 0.5);
  EXPECT_FLOATINGPOINT_EQ(v4_norm.y, 0.5);
  EXPECT_FLOATINGPOINT_EQ(v4_norm.z, 0.5);
  EXPECT_FLOATINGPOINT_EQ(v4_norm.w, 0.5);
  EXPECT_FLOATINGPOINT_EQ(length(v4_norm), 1.0);
}

TEST(TupleMathTest, Reflect) {
  Vec2 v2(1, -2);
  Vec2 n2(0, 1);
  Vec2 reflection2 = reflect(v2, n2);

  EXPECT_FLOATINGPOINT_EQ(reflection2.x, 1);
  EXPECT_FLOATINGPOINT_EQ(reflection2.y, 2);

  // both in xy plane
  Vec3 v3(1.0, -2.0, 0.0);
  Vec3 n3(0.0, 1.0, 0.0);
  Vec3 reflection3 = reflect(v3, n3);
  EXPECT_FLOATINGPOINT_EQ(reflection3.x, 1.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.y, 2.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.z, 0.0);

  // bounce along z axis
  v3 = Vec3(0.0, 0.0, -1.0);
  n3 = Vec3(0.0, 0.0, 1.0);
  reflection3 = reflect(v3, n3);
  EXPECT_FLOATINGPOINT_EQ(reflection3.x, 0.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.y, 0.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.z, 1.0);

  // symmetric off xy plane
  v3 = Vec3(1.0, 1.0, -1.0);
  n3 = Vec3(0.0, 0.0, 1.0);
  reflection3 = reflect(v3, n3);
  EXPECT_FLOATINGPOINT_EQ(reflection3.x, 1.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.y, 1.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.z, 1.0);

  // incidence parallel to surface
  v3 = Vec3(2.0, -1.0, 0.0);
  n3 = Vec3(0.0, 0.0, 1.0);
  reflection3 = reflect(v3, n3);
  EXPECT_FLOATINGPOINT_EQ(reflection3.x, 2.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.y, -1.0);
  EXPECT_FLOATINGPOINT_EQ(reflection3.z, 0.0);

  // Tilted 3d normal
  v3 = Vec3(0.0, 0.0, -3.0);
  n3 = Vec3(Float(1) / Float(3), Float(2) / Float(3), Float(2) / Float(3));
  reflection3 = reflect(v3, n3);
  EXPECT_FLOATINGPOINT_EQ(reflection3.x, Float(4) / Float(3));
  EXPECT_FLOATINGPOINT_EQ(reflection3.y, Float(8) / Float(3));
  EXPECT_FLOATINGPOINT_EQ(reflection3.z, Float(-1) / Float(3));

  // General 3d
  v3 = Vec3(6.0, -2.0, -3.0);
  n3 = Vec3(Float(2) / Float(7), Float(3) / Float(7), Float(6) / Float(7));
  reflection3 = reflect(v3, n3);
  EXPECT_NEAR(reflection3.x, Float(342) / Float(49), 1e-6);
  EXPECT_NEAR(reflection3.y, Float(-26) / Float(49), 1e-6);
  EXPECT_NEAR(reflection3.z, Float(-3) / Float(49), 1e-6);
}
// ---------------------------------------------------------
// Utilities Tests
// ---------------------------------------------------------

TEST(TupleUtilTest, Printable) {
  Color c3(0.1, 0.5, 0.9);
  std::stringstream ss3;
  ss3 << c3;
  EXPECT_EQ(ss3.str(), "0.1 0.5 0.9");

  Color4 c4(1.0, 0.0, 0.5, 0.25);
  std::stringstream ss4;
  ss4 << c4;
  EXPECT_EQ(ss4.str(), "1 0 0.5 0.25");
}