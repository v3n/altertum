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

/*Entry point for altertum unit tests*/
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*Testing structure for Vector2 type*/
struct Vector2Test :testing ::Test {
	Vector2 vec2_1, vec2_2;

	/*Function to test operator==*/
	const bool V2Equals(const Vector2 a, const Vector2 b)
	{
		return (a == b);
	}
};

/*Testing structure for Vector3 type*/
struct Vector3Test :testing::Test {
	Vector3 vec3_1, vec3_2;

	/*Function to test operator==*/
	const bool V3Equals(const Vector3 a, const Vector3 b)
	{
		return (a == b);
	}
};

/*Testing structure for the Vector4 type*/
struct Vector4Test :testing::Test {
	Vector4 vec4_1, vec4_2;

	/*Function to test operator==*/
	const bool V4Equals(const Vector4 a, const Vector4 b)
	{
		return (a == b);
	}
};

/*Testing structure for the Matrix3 type*/
struct Matrix3Test :testing::Test {
	Matrix3 mat3_1, mat3_2;
};

/*Testing structure for the Matrix4 type*/
struct Matrix4Test :testing::Test {
	Matrix4 mat4_1, mat4_2;

	/*Function to test operator==*/
	bool Mat4Equals(const Matrix4 a, const Matrix4 b)
	{
		return(a == b);
	}
};

/*Testing structure for the AABB type*/
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

/*Vector2 Test Fixture: operators*/
TEST_F(Vector2Test, operators) {
	vec2_1 = altertum::vector2::vector2(0.1, 0.00001);
	vec2_2 = altertum::vector2::vector2(-10, 0.00001);
	EXPECT_EQ(V2Equals(vec2_1, vec2_2), false);

	vec2_1 = altertum::vector2::vector2(.123400000000000, .43210000000000000);
	vec2_2 = altertum::vector2::vector2(.1234f, .4321f);
	EXPECT_EQ(V2Equals(vec2_1, vec2_2), true);
	
	vec2_1 = altertum::vector2::vector2(-0, +0);
	vec2_2 = altertum::vector2::vector2(+0.0, -0.0f);
	EXPECT_EQ(V2Equals(vec2_1, vec2_2), true);
}

/*Vector3 Test Fixture: operators where only 2 Vector3 objects are used*/
TEST_F(Vector3Test, operatorsNoFloat) {
	// == //

	// += //

	// + //

	// -= //

	// - //
}

/*Vector3 Test Fixture: operators where a Vector3 object and float are used*/
TEST_F(Vector3Test, operatorsFloat) {
	// += //

	// + //

	// -= //

	// - //

	// * //
	
	// *= //

	// / //

	// /= //
}

/*Vector3 Test Fixture: any property of a Vector3 which requires computation*/
TEST_F(Vector3Test, computedProperties) {
	//cross
	
	//dot

	//distance

	//normalize

	//xy
}

/*Vector4 Test Fixture: operators*/
TEST_F(Vector4Test, operators) {
	// == //
}

/*Matrix3 Test Fixture: testing rotation*/
TEST_F(Matrix3Test, rotationTest) {

}

/*Matrix4 Test Fixture: operators*/
TEST_F(Matrix4Test, operators) {
	// == //

	// * //
	
	// *= //
}

/*Matrix4 Test Fixture: testing the 5 separate ways of constructing a Matrix4*/
TEST_F(Matrix4Test, constructionTest) {
	//From Vector4[]

	//From float[]

	//From Matrix3

	//From Quaternion

	//From Vector3, Quaternion, Vector3 (scale, rotation, translation)

}

/*AABB Test Fixture: tests for the size-relative properties*/
TEST_F(A2B2Test, sizePropertiesTest) {
	//xsize
	
	//ysize

	//zsize

	//volume
}

/*AABB Test Fixture: tests for properties not related to size*/
TEST_F(A2B2Test, otherPropertiesTest) {
	//intersect

	//center

	//contains
}