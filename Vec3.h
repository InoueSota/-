#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
class Vec3 {
public:
    float x, y, z;
    Vec3(float x = 0, float y = 0, float z = 0);
    void set(float x, float y, float z = 0);
    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(float f) const;
    Vec3 operator/(float f) const;
    Vec3 operator-() const;
    void operator+=(const Vec3& v);
    void operator-=(const Vec3& v);
    void operator*=(float f);
    void operator/=(float f);
    float sqMag() const;
    float magSq() const;//‹@”\‚ÍsqMag‚Æ“¯‚¶
    float mag() const;
    Vec3 setMag(float mag);
    Vec3 limmit(float maxMag);
    Vec3 normalize();
    float dot(const Vec3& v)const;
    Vec3 cross(const Vec3& v)const;
    float crossZ(const Vec3& v)const;//ŠOÏZ¬•ª‚Ì‚İŒvZ(‚Q‚c—p)
    float crossY(const Vec3& v)const;//ŠOÏY¬•ª‚Ì‚İŒvZ(‚Q‚c—p)
};

Vec3 operator* (float f, const Vec3& v);// Vec3 = float * Vec3
Vec3 normalize(const Vec3& a);
float dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
float crossZ(const Vec3& a, const Vec3& b);
float crossY(const Vec3& a, const Vec3& b);
