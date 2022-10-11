#include "Vec3.h"

Vec3::Vec3(float x, float y, float z) {
    this->x = x;    this->y = y;    this->z = z;
}
void Vec3::set(float x, float y, float z) {
    this->x = x;    this->y = y;    this->z = z;
}
Vec3 Vec3::operator-(const Vec3& v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}
Vec3 Vec3::operator+(const Vec3& v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}
Vec3 Vec3::operator*(float f) const {
    return Vec3(x * f, y * f, z * f);
}
Vec3 Vec3::operator/(float f) const {
    return Vec3(x / f, y / f, z / f);
}
Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}
void Vec3::operator+=(const Vec3& v) {
    x += v.x;   y += v.y;   z += v.z;
}
void Vec3::operator-=(const Vec3& v) {
    x -= v.x;    y -= v.y;    z -= v.z;
}
void Vec3::operator*=(float f) {
    x *= f;    y *= f;    z *= f;
}
void Vec3::operator/=(float f) {
    x /= f;    y /= f;    z /= f;
}
float Vec3::sqMag() const {
    return x * x + y * y + z * z;
}
float Vec3::magSq() const {
    return x * x + y * y + z * z;
}
float Vec3::mag() const {
    return sqrtf(x * x + y * y + z * z);
}
Vec3 Vec3::setMag(float mag) {
    float len = sqrtf(x * x + y * y + z * z);
    if (len > 0) {
        mag /= len;
        x *= mag;
        y *= mag;
        z *= mag;
    }
    return Vec3(x, y, z);
}
Vec3 Vec3::limmit(float maxMag) {
    float len = sqrtf(x * x + y * y + z * z);
    if (len > maxMag) {
        maxMag /= len;
        x *= maxMag;
        y *= maxMag;
        z *= maxMag;
    }
    return Vec3(x, y, z);
}
Vec3 Vec3::normalize() {
    float len = sqrtf(x * x + y * y + z * z);
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
    return Vec3(x, y, z);
}
float Vec3::dot(const Vec3& v) const {
    return x * v.x + y * v.y + z * v.z;
}
Vec3 Vec3::cross(const Vec3& v) const {
    return Vec3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}
float Vec3::crossZ(const Vec3& v) const {
    return x * v.y - y * v.x;
}
float Vec3::crossY(const Vec3& v) const {
    return x * v.z - z * v.x;
}

//‚RŽŸŒ³ƒxƒNƒgƒ‹‚Ìˆê”ÊŠÖ”-------------------------------------------------------
Vec3 operator*(float f, const Vec3& v) {
    return Vec3(f * v.x, f * v.y, f * v.z);
}
//”ñ”j‰ónoramalize
Vec3 normalize(const Vec3& a) {
    float l = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
    if (l > 0) {
        return Vec3(a.x / l, a.y / l, a.z / l);
    }
    return a;
}
float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}
float crossZ(const Vec3& a, const Vec3& b) {
    return a.x * b.y - a.y * b.x;
}
float crossY(const Vec3& a, const Vec3& b) {
    return a.x * b.z - a.z * b.x;
}

