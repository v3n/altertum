/*
	* Author: Nathanael Thompson
	* License: https://github.com/v3n/altertum/blob/master/LICENSE
*/

#include <math_types.h>
#include "gtest\gtest.h"
#include "aabb.h" 
#include "vector4.h" 
#include "vector3.h" 
#include "vector2.h" 
#include "matrix3.h" 
#include "matrix4.h" 

using altertum::Vector2;
using altertum::Vector3;
using altertum::Vector4;
using altertum::AABB;
using altertum::OBB;
using altertum::Matrix3;
using altertum::Matrix4;
using altertum::Quaternion;

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

struct Vector2Test :testing ::Test {
	Vector2 vec2_1, vec2_2;

	/*Function to test operator==*/
	const bool V2Equals(const Vector2 a, const Vector2 b)
	{
		return (a == b);
	}
};
struct Vector3Test :testing::Test {
	Vector3 vec3_1, vec3_2;

	/*Function to test operator==*/
	const bool V3Equals(const Vector3 a, const Vector3 b)
	{
		return (a == b);
	}
};
struct Vector4Test :testing::Test {
	Vector4 vec4_1, vec4_2;

	/*Function to test operator==*/
	const bool V4Eqauls(const Vector4 a, const Vector4 b)
	{
		return (a == b);
	}
};
struct Matrix3Test :testing::Test {
	Matrix3 mat3_1, mat3_2;
};
struct Matrix4Test :testing::Test {
	Matrix4 mat4_1, mat4_2;

	/*Function to test operator==*/
	bool Mat4Equals(const Matrix4 a, const Matrix4 b)
	{
		return(a == b);
	}
};
struct A2B2Test : testing::Test {
	AABB a2b2_1, a2b2_2;
	Vector3 min, max;
};

/*Test fixtures
	TODO: 
	//aabb: 2 constructors, intersect, center, xsize, ysize, zsize, volume, contains
	//vector4: 2 constructors
	//vector3: 2 constructors, arithmetic operators, cross, dot, distance, normalize, xy
	//matrix3: 1 constructor, rotation
	//matrix4: 3 constructors, arithmetic operators, rotation, compose
*/

/*Test fixture for vector2: contructor and operators*/
TEST_F(Vector2Test, vector2Operators)
{
	vec2_1 = altertum::vector2::vector2(0.1, 0.00001);
	vec2_2 = altertum::vector2::vector2(-10, 0.00001);
	EXPECT_EQ(V2Equals(vec2_1, vec2_2), false);

	vec2_1 = altertum::vector2::vector2(.1234, .4321);
	vec2_2 = altertum::vector2::vector2(.1234f, .4321f);
	EXPECT_EQ(V2Equals(vec2_1, vec2_2), true);
	
	vec2_1 = altertum::vector2::vector2(0, 0);
	vec2_2 = altertum::vector2::vector2(0.0, 0.0f);
	EXPECT_EQ(V2Equals(vec2_1, vec2_2), true);
}
