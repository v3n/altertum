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

	/*Return true if Vector2 a== Vector2 b*/
	const bool CheckV4Equality(const Vector4 &a, const Vector4 &b)
	{
		return (a.w == b.w && a.x == b.x && a.y == b.y && a.z && b.z);
	}
	/*Return true if Vector3 a== Vector3 b*/
	const bool CheckV3Equality(const Vector3 &a, const Vector3 &b)
	{
		return (a.x == b.x && a.y && b.y && a.z == b.z);
	}
	/*Return true if Vector4 a== Vector4 b*/
	const bool CheckV2Equality(const Vector2 &a, const Vector2 &b)
	{
		return (a.x == b.x && a.y == b.y);
	}
	/*Create new Vector2 from parameters*/
	Vector2* CreateV2(float x, float y)
	{
		Vector2* vec2 = new Vector2;
		vec2->x = x;
		vec2->y = y;
		return vec2;
	}
	/*Create new Vector3 from parameters*/
	Vector3* CreateV3(float x, float y, float z)
	{
		Vector3* vec3 = new Vector3;
		vec3->x = x;
		vec3->y = y;
		vec3->z = z;
		return vec3;
	}
	/*Create new Vector4 from parameters*/
	Vector4* CreateV4(float w, float x, float y, float z)
	{
		Vector4* vec4 = new Vector4;
		vec4->w = w;
		vec4->x = x;
		vec4->y = y;
		vec4->z = z;
		return vec4;
	}
	/*Change the values of Vector2 to parameter values*/
	void AssignV2(Vector2 &vec2, float x, float y)
	{
		vec2.x = x;
		vec2.y = y;
	}
	/*Change the values of Vector3 to parameter values*/
	void AssignV3(Vector3 &vec3, float x, float y, float z)
	{
		vec3.x = x;
		vec3.y = y;
		vec3.z = z;
	}
	/*Change the values of Vector4 to parameter values*/
	void AssignV4(Vector4 &vec4, float w, float x, float y, float z)
	{
		vec4.w = w;
		vec4.x = x;
		vec4.y = y;
		vec4.z = z;
	}
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
	/*Create matrix3 from parameters*/
	Matrix3* CreateMat3(Vector3 &a, Vector3 &b, Vector3 &c)
	{
		Matrix3* mat3 = new Matrix3;
		mat3->a = a;
		mat3->b = b;
		mat3->c = c;
		return mat3;
	}
	/*Create matrix4 from parameters*/
	Matrix4* CreateMat4(Vector4 &a, Vector4 &b, Vector4 &c, Vector4 &d)
	{
		Matrix4* mat4 = new Matrix4;
		mat4->a = a;
		mat4->b = b;
		mat4->c = c;
		mat4->d = d;
		return mat4;
	}
	/*Assign matrix3 values from parameters*/
	void AssignMat3(Matrix3 &mat3, Vector3 &a, Vector3 &b, Vector3 &c)
	{
		mat3.a = a;
		mat3.b = b;
		mat3.c = c;
	}
	/*Assign matrix4 values from parameters*/
	void AssignMat4(Matrix4 &mat4, Vector4 &a, Vector4 &b, Vector4 &c, Vector4 &d)
	{
		mat4.a = a;
		mat4.b = b;
		mat4.c = c;
		mat4.d = d;
	}
	/*Return true if values of matrices a and b are equal*/
	bool CheckMat3Equality(const Matrix3 &a, const Matrix3 &b)
	{
		return(a.a.x == b.a.x && a.a.y == b.a.y && a.a.z == b.a.z
			&& a.b.x == b.b.x && a.b.y == b.b.y && a.b.z == b.b.z
			&& a.c.x == b.c.x && a.c.y == b.c.y && a.c.z == b.c.z);
	}
	/*Return true if values of matrices a and b are equal*/
	bool CheckMat4Equality(const Matrix4 &a, const Matrix4 &b)
	{
		return(a.a.x == b.a.x && a.a.y == b.a.y && a.a.z == b.a.z && a.a.w == b.a.w
			&& a.b.x == b.b.x && a.b.y == b.b.y && a.b.z == b.b.z && a.b.w == b.b.w
			&& a.c.x == b.c.x && a.c.y == b.c.y && a.c.z == b.c.z && a.c.w == b.c.w
			&& a.d.x == b.d.x && a.d.y == b.d.y && a.d.z == b.d.z && a.d.w == b.d.w);
	}
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
	/*Return true if a's properties == b's properties. Used in function CheckOBBTransformEquality*/
	const bool CheckA2B2Equality(const AABB &a, const AABB &b)
	{
		return (a.origin.x == b.origin.x
			&& a.origin.y == b.origin.y
			&& a.origin.z == a.origin.z
			&& a.radius.x == a.radius.x
			&& a.radius.y == a.radius.y
			&& a.radius.z == a.radius.z);
	}
	const bool CheckOBBTransformEquality(const Vector4 &a, const Vector4 &b)
	{
		return(a.w == b.w && a.x == b.x && a.y == b.y && a.z == b.z);
	}
	/*Return true if origin, radius, and transform of params a and b are equal*/
	const bool CheckOBBEquality(const OBB &a, const OBB &b)
	{
		return (CheckA2B2Equality(a.aabb, b.aabb)
			&& CheckOBBTransformEquality(a.transform.a, b.transform.a)
			&& CheckOBBTransformEquality(a.transform.b, b.transform.b)
			&& CheckOBBTransformEquality(a.transform.c, b.transform.c)
			&& CheckOBBTransformEquality(a.transform.d, b.transform.d));
	}
	OBB* CreateOBB(AABB &a2b2, Matrix4 &transform)
	{
		OBB* o1b2 = new OBB;
		o1b2->aabb = a2b2;
		o1b2->transform = transform;
		return o1b2;
	}
	AABB* CreateAABB(Vector3 &origin, Vector3 &radius)
	{
		AABB* a2b2 = new AABB;
		a2b2->origin = origin;
		a2b2->radius = radius;
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
	/*Returns true if a==b*/
	const bool CheckQuatEquality(const Quaternion &a, const Quaternion &b)
	{
		return (a.w == b.w 
			&& a.x == b.x
			&& a.y == b.y
			&& a.z == b.z);
	}
	/*Create quaternion from parameters*/
	Quaternion* CreateQuat(float w, float x, float y, float z)
	{
		Quaternion* quat = new Quaternion;
		quat->w = w;
		quat->x = x;
		quat->y = y;
		quat->z = z;
		return quat;
	}
	/*Assign values to a quaternion*/
	void AssignQuat(Quaternion &quat, float w, float x, float y, float z)
	{
		quat.w = w;
		quat.x = x;
		quat.y = y;
		quat.z = z;
	}
	~QuatTest() {}
};

/*Test fixtures
	TODO: Possibly split multiple types into multiple groups of tests
	(VectorTest -> Vector2Test, Vector3Test, Vector4Test, etc)
*/
//Vector Arithmetic
TEST_F(VectorTest, vecArithmetic)
{
	
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


