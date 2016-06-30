/*
	* Author: Nathanael Thompson
	* License: https://github.com/v3n/altertum/blob/master/LICENSE
*/

#include <math_types.h>
#include "gtest\gtest.h"
using altertum::Vector2; //there might be a better way of doing this...
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

struct VectorTest :testing ::Test {
	Vector4* vec4_1;
	Vector4* vec4_2;
	Vector3* vec3_1;
	Vector3* vec3_2;
	Vector2* vec2_1;
	Vector2* vec2_2;

	void SetUp()
	{
		vec4_1 = new Vector4;
		vec4_2 = new Vector4;
		vec3_1 = new Vector3;
		vec3_2 = new Vector3;
		vec2_1 = new Vector2;
		vec2_2 = new Vector2;
	}
	void TearDown()
	{
		delete vec4_1, vec4_2, vec3_1, vec3_2, vec2_1, vec2_2;
	}

	/*For the following functions, return true if Vector(2,3, or 4) a==b*/
	const bool CheckV4Equality(const Vector4* a, const Vector4* b)
	{
		return (a->w == b->w && a->x == b->x && a->y == b->y && a->z && b->z);
	}
	const bool CheckV3Equality(const Vector3* a, const Vector3* b)
	{
		return (a->x == b->x && a->y && b->y && a->z == b->z);
	}
	const bool CheckV2Equality(const Vector2* a, const Vector2* b)
	{
		return (a->x == b->x && a->y == b->y);
	}

	//TODO: Create assignment functions
	~VectorTest() {}
};
struct MatrixTest :testing::Test {
	Matrix4* mat4_1;
	Matrix4* mat4_2;
	Matrix3* mat3_1;
	Matrix3* mat3_2;

	void SetUp()
	{
		mat4_1 = new Matrix4;
		mat4_2 = new Matrix4;
		mat3_1 = new Matrix3;
		mat3_2 = new Matrix3;
	}
	void TearDown()
	{
		delete mat4_1, mat4_2, mat3_1, mat3_2;
	}
	//TODO: Create equality functions
	//TODO: Create assignment functions
	~MatrixTest() {}
};
struct BBoxTest :testing::Test {
	AABB* a2b2_1;
	AABB* a2b2_2;
	OBB* o1b2_1;
	OBB* o1b2_2;

	void SetUp()
	{
		a2b2_1 = new AABB;
		a2b2_2 = new AABB;
		o1b2_1 = new OBB;
		o1b2_2 = new OBB;
	}
	void TearDown()
	{
		delete a2b2_1, a2b2_2, o1b2_1, o1b2_2;
	}
	/*Return true if @param:a properties' origin and radius == @param:b*/
	const bool CheckA2B2Equality(const AABB* a, const AABB* b)
	{
		return (a->origin.x == b->origin.x
			&& a->origin.y == b->origin.y
			&& a->origin.z == b->origin.z
			&& a->radius.x == b->radius.x
			&& a->radius.y == b->radius.y
			&& a->radius.z == b->radius.z);
	}
	/*Same as above, with a different signature. Used in function CheckOBBTransformEquality*/
	const bool CheckA2B2Equality(const AABB a, const AABB b)
	{
		return (a.origin.x == b.origin.x
			&& a.origin.y == b.origin.y
			&& a.origin.z == a.origin.z
			&& a.radius.x == a.radius.x
			&& a.radius.y == a.radius.y
			&& a.radius.z == a.radius.z);
	}
	const bool CheckOBBTransformEquality(const Vector4 a, const Vector4 b)
	{
		return(a.w == b.w && a.x == b.x && a.y == b.y && a.z == b.z);
	}
	/*Return true if origin, radius, and transform of params a and b are equal*/
	const bool CheckOBBEquality(const OBB* a, const OBB* b)
	{
		return (CheckA2B2Equality(a->aabb, b->aabb)
			&& CheckOBBTransformEquality(a->transform.a, b->transform.a)
			&& CheckOBBTransformEquality(a->transform.b, b->transform.b)
			&& CheckOBBTransformEquality(a->transform.c, b->transform.c)
			&& CheckOBBTransformEquality(a->transform.d, b->transform.d));
	}
	//TODO: Create assignment functions
	~BBoxTest() {}
};
struct QuatTest :testing::Test {
	Quaternion* quat1;
	Quaternion* quat2;

	void SetUp()
	{
		quat1 = new Quaternion;
		quat2 = new Quaternion;
	}
	void TearDown()
	{
		delete quat1, quat2;
	}
	
	const bool CheckEquality(const Quaternion* a, const Quaternion* b)
	{
		return (a->w == b->w 
			&& a->x == b->x
			&& a->y == b->y
			&& a->z == b->z);
	}
	//TODO: Create assignment functions
	~QuatTest() {}
};

/*Test fixtures
	TODO: Possibly split multiple types into multiple groups of tests
	(VectorTest -> Vector2Test, Vector3Test, Vector4Test, etc)
*/
//Vector Arithmetic
TEST_F(VectorTest, vecArithmetic)
{
	vec4_1->w = 1;
	vec4_1->x = 2;
	vec4_1->y = 4;
	vec4_1->z = 8;

	vec4_2->w = 16;
	vec4_2->x = 32;
	vec4_2->y = 64;
	vec4_2->z = 128;
}
//Vector Functions
TEST_F(VectorTest, vecFunctions)
{

}

//Matrix Arithmetic
TEST_F(MatrixTest, matArithmetic)
{

}

//Matrix Functions
TEST_F(MatrixTest, matFunctions)
{

}

//Bounding box arithmetic
TEST_F(BBoxTest, bboxArithmetic)
{

}

//Bounding box functions
TEST_F(BBoxTest, bboxFunctions)
{

}

//Quaternion arithmetic
TEST_F(QuatTest, quatArithmetic)
{

}

//Quaternion functions
TEST_F(QuatTest, quatFunctions)
{

}


