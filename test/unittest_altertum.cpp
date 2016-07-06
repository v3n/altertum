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
struct VectorTest :testing ::Test {
	Vector4 * vec4_1, * vec4_2;
	Vector3 * vec3_1, * vec3_2;
	Vector2 * vec2_1, * vec2_2;

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

	/*Return true if Vector4 a == Vector2 b*/
	const bool CheckV4Equality(const Vector4 &a, const Vector4 &b)
	{
		return (a.w == b.w && a.x == b.x && a.y == b.y && a.z && b.z);
	}
	/*Return true if Vector3 a == Vector3 b*/
	const bool CheckV3Equality(const Vector3 &a, const Vector3 &b)
	{
		return (a.x == b.x && a.y && b.y && a.z == b.z);
	}
	/*Return true if Vector2 a == Vector4 b*/
	const bool CheckV2Equality(const Vector2 &a, const Vector2 &b)
	{
		return (a.x == b.x && a.y == b.y);
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
	//~VectorTest() {}
};
struct MatrixTest :testing::Test {
	Matrix4 * mat4_1, * mat4_2;
	Matrix3 * mat3_1, * mat3_2;
	Vector4 * a, * b, * c, * d;
	Vector3* a2, * b2, * c2;
	void SetUp()
	{
		mat4_1 = new Matrix4;
		mat4_2 = new Matrix4;
		mat3_1 = new Matrix3;
		mat3_2 = new Matrix3;
	}
	void TearDown()
	{
		delete mat4_1, mat4_2, mat3_1, mat3_2, a, b, c, d, a2, b2, c2;
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
	//~MatrixTest() {}
};
struct BBoxTest :testing::Test {
	AABB * a2b2_1, * a2b2_2;
	OBB * o1b2_1, * o1b2_2;
	Vector4 * a, * b, * c, * d;
	Vector3 * a2, * b2, * c2;
	Matrix4 * m4;
	Vector3 * origin, * radius, * max, * min;
	void SetUp()
	{
		a2b2_1 = new AABB;
		a2b2_2 = new AABB;
		o1b2_1 = new OBB;
		o1b2_2 = new OBB;
	}
	void TearDown()
	{
		delete a2b2_1, a2b2_2, o1b2_1, o1b2_2, a, b, c, d, a2, b2, c2, m4, origin, radius, max, min;
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
	AABB* CreateAABB(Vector3 &origin, Vector3 &radius, Vector3 &max, Vector3 &min)
	{
		AABB* a2b2 = new AABB;
		a2b2->origin = origin;
		a2b2->radius = radius;
		a2b2->max = max;
		a2b2->min = min;
		return a2b2;
	}
	void AssignOBB(OBB &o1b2, AABB &a2b2, Matrix4 &transform)
	{
		o1b2.aabb = a2b2;
		o1b2.transform = transform;
	}
	void AssignAABB(AABB &a2b2, Vector3 &origin, Vector3 &radius, Vector3 &max, Vector3 &min)
	{
		a2b2.origin = origin;
		a2b2.radius = radius;
		a2b2.max = max;
		a2b2.min = min;
	}
	//~BBoxTest() {}
};
struct QuatTest :testing::Test {
	Quaternion * quat1, * quat2;

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
	//~QuatTest() {}
};

/*Test fixtures
	TODO: Possibly split multiple types into multiple groups of tests
	(VectorTest -> Vector2Test, Vector3Test, Vector4Test, etc)
*/
//Vector Arithmetic
TEST_F(VectorTest, vecArithmetic)
{
	//Vector4
	AssignV4(*vec4_1, 234.5f, -44444444.3f, -.09385f, .1111222f);
	AssignV4(*vec4_2, 234.567f, -333444555.9f, .1234567875f, 11.2344432f);
	EXPECT_NE(vec4_1, vec4_2);
	EXPECT_FALSE(CheckV4Equality(*vec4_1, *vec4_2));
	vec4_1->w += .067f;
	EXPECT_EQ(vec4_1->w, vec4_2->w);
	vec4_1 = vec4_2;
	for (int i = 0; i < 20; i++)
	{
		AssignV4(*vec4_1, vec4_1->w + i, vec4_1->x + i, vec4_1->y + i, vec4_1->z);
		AssignV4(*vec4_2, vec4_2->w + i, vec4_2->x + i, vec4_2->y + i, vec4_2->z);
	}
	EXPECT_TRUE(CheckV4Equality(*vec4_1, *vec4_2));
	for (int i = 1; i < 1000; i++)
	{
		EXPECT_EQ(vec4_1->w/(12+i), vec4_2->w/(12+i));
		EXPECT_EQ(vec4_1->x/(-1-i), vec4_2->x/(-1-i));
		EXPECT_EQ(vec4_1->y/(-1234*i), vec4_2->y/(-1234*i));
		EXPECT_EQ(vec4_1->z/(905/i), vec4_2->z/(905/i));
	}
	//Vector3
	AssignV3(*vec3_1, 1.2f, 3.4f, 4.5f);
	AssignV3(*vec3_2, vec3_1->x, vec3_1->y, 18.5f);
	EXPECT_NE(vec3_1, vec3_2);
	EXPECT_TRUE(vec3_1 == vec3_1);
	EXPECT_FALSE(vec3_1 == vec3_2);
	EXPECT_FALSE(CheckV3Equality(*vec3_1, *vec3_2));
	vec3_2 = vec3_1;
	for (int i = 0; i < 20; i++)
	{
		AssignV3(*vec3_1, vec3_1->x + i, vec3_1->y + i, vec3_1->z + i);
		AssignV3(*vec3_2, vec3_2->x + i, vec3_2->y + i, vec3_2->z + i);
	}
	EXPECT_TRUE(CheckV3Equality(*vec3_1, *vec3_2));
	for (int i = 0; i < 50; i++)
	{
		EXPECT_EQ(vec3_1->x / (4 + i), vec3_2->x / (4 + i));
		EXPECT_EQ(vec3_1->y / (60 - i), vec3_2->y / (60 - i));
		EXPECT_EQ(vec3_1->z / (17 / 6*(i+1)), vec3_2->z / (17 / 6*(i+1)));
	}
	
	//Vector2
	AssignV2(*vec2_1, 6.7f, .989989989f);
	AssignV2(*vec2_2, 453.4443325251f, -9000882.453f);
	EXPECT_NE(vec2_1, vec2_2);
	EXPECT_FALSE(CheckV2Equality(*vec2_1, *vec2_2));
	for (int i = 0; i < 20; i++)
	{
		AssignV2(*vec2_1, vec2_1->x + i, vec2_1->y + i);
		AssignV2(*vec2_2, vec2_2->x + i, vec2_2->y + i);
	}
	EXPECT_FALSE(CheckV2Equality(*vec2_1, *vec2_2));
	EXPECT_TRUE(vec2_1->x * 100 > vec2_2->x);
	for (int i = 1; i < 200; i++)
	{
		EXPECT_NE(vec2_1->x/i, vec2_2->x/i);
		EXPECT_NE(vec2_1->y / (i*i*i), vec2_2->y / (i*i*i));
	}
}
//Vector Functions
TEST_F(VectorTest, vecFunctions)
{
	//Vector3
	const Vector3 forwardVec = Vector3::forward();
	const Vector3 rightVec = Vector3::right();
	const Vector3 upVec = Vector3::up();
	EXPECT_EQ(forwardVec.z, 1.0f);
	EXPECT_EQ(forwardVec.x, 0.0f);
	EXPECT_EQ(forwardVec.y, 0.0f);
	EXPECT_EQ(rightVec.x, -1.0f);
	EXPECT_EQ(rightVec.y, 0.0f);
	EXPECT_EQ(rightVec.z, 0.0f);
	EXPECT_EQ(upVec.y, 1.0f);
	EXPECT_EQ(upVec.x, 0.0f);
	EXPECT_EQ(upVec.z, 0.0f);
}

//Matrix Arithmetic
TEST_F(MatrixTest, matArithmetic)
{
	//Matrix4
	a = CreateV4(1.0f, 2.0f, 3.0f, 4.0f);
	b = CreateV4(5.0f, 6.0f, 7.0f, 8.0f);
	c = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	d = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	AssignMat4(*mat4_1, *a, *b, *c, *d);
	AssignMat4(*mat4_2, *d, *c, *b, *a);
	EXPECT_FALSE(CheckMat4Equality(*mat4_1, *mat4_2));
	EXPECT_TRUE(mat4_1->a.w == mat4_2->d.w);
	EXPECT_TRUE(mat4_1->a.x == mat4_2->d.x);
	EXPECT_TRUE(mat4_1->a.y == mat4_2->d.y);
	EXPECT_TRUE(mat4_1->a.z == mat4_2->d.z);
	
	//Matrix3
	a2 = CreateV3(1.0f, 2.0f, 3.0f);
	b2 = CreateV3(4.0f, 5.0f, 6.0f);
	c2 = CreateV3(7.0f, 8.0f, 9.0f);
	AssignMat3(*mat3_1, *a2, *b2, *c2);
	AssignMat3(*mat3_1, *c2, *b2, *a2);
	EXPECT_FALSE(CheckMat3Equality(*mat3_1, *mat3_2));
}

//Matrix Functions
TEST_F(MatrixTest, matFunctions)
{
	//Matrix4
	a = CreateV4(1.0f, 0.0f, 0.0f, 0.0f);
	b = CreateV4(0.0f, 1.0f, 0.0f, 0.0f);
	c = CreateV4(0.0f, 0.0f, 1.0f, 0.0f);
	d = CreateV4(0.0f, 0.0f, 0.0f, 1.0f);
	AssignMat4(*mat4_1, *a, *b, *c, *d);
	
	//identity
	const Matrix4 identityMat = Matrix4::identity();
	EXPECT_TRUE(CheckMat4Equality(*mat4_1, identityMat));

	a = CreateV4(0.5f, 0.0f, 0.0f, 0.5f);
	b = CreateV4(0.0f, 0.5f, 0.0f, 0.5f);
	c = CreateV4(0.0f, 0.0f, 0.5f, 0.5f);
	d = CreateV4(0.0f, 0.0f, 0.0f, 1.0f);
	AssignMat4(*mat4_2, *d, *c, *b, *a);
	
	//bias
	const Matrix4 biasMat = Matrix4::bias();
	EXPECT_TRUE(CheckMat4Equality(*mat4_2, biasMat));

	//Matrix3
	a2 = CreateV3(1.0f, 0.0f, 0.0f);
	b2 = CreateV3(0.0f, 1.0f, 0.0f);
	c2 = CreateV3(0.0f, 0.0f, 1.0f);
	AssignMat3(*mat3_1, *a2, *b2, *c2);

	//identity
	const Matrix3 identityMat3 = Matrix3::identity();
	EXPECT_TRUE(CheckMat3Equality(*mat3_1, identityMat3));
}

//Bounding box arithmetic
TEST_F(BBoxTest, bboxArithmetic)
{
	a = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	b = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	c = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	d = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	m4 = CreateMat4(*a, *b, *c, *d);
	origin = CreateV3(0.0f, 0.0f, 0.0f);
	radius = CreateV3(0.0f, 0.0f, 0.0f);
	max = CreateV3(0.0f, 0.0f, 0.0f);
	min = CreateV3(0.0f, 0.0f, 0.0f);
	AssignAABB(*a2b2_1, *origin, *radius, *max, *min);
	a2b2_2 = a2b2_1;
	AssignOBB(*o1b2_1, *a2b2_1, *m4);
	o1b2_2 = o1b2_1;
}

//Bounding box functions
TEST_F(BBoxTest, bboxFunctions)
{
	a = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	b = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	c = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	d = CreateV4(0.0f, 0.0f, 0.0f, 0.0f);
	m4 = CreateMat4(*a, *b, *c, *d);
	origin = CreateV3(0.0f, 0.0f, 0.0f);
	radius = CreateV3(0.0f, 0.0f, 0.0f);
	max = CreateV3(0.0f, 0.0f, 0.0f);
	min = CreateV3(0.0f, 0.0f, 0.0f);
	AssignAABB(*a2b2_1, *origin, *radius, *max, *min);
	a2b2_2 = a2b2_1;
	AssignOBB(*o1b2_1, *a2b2_1, *m4);
	o1b2_2 = o1b2_1;
}

//Quaternion arithmetic
TEST_F(QuatTest, quatArithmetic)
{
	AssignQuat(*quat1, 0.0f, 0.0f, 0.0f, 0.0f);
	AssignQuat(*quat2, 0.0f, 0.0f, 0.0f, 0.0f);
}

//Quaternion functions
TEST_F(QuatTest, quatFunctions)
{
	AssignQuat(*quat1, 0.0f, 0.0f, 0.0f, 0.0f);
	AssignQuat(*quat2, 0.0f, 0.0f, 0.0f, 0.0f);
}