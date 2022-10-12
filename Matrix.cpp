#include "Matrix.h"

//íPà çsóÒÇÇ¬Ç≠ÇÈ
void MATRIX2::identity() {
    _11 = 1; _12 = 0; _13 = 0;
    _21 = 0; _22 = 1; _23 = 0;
    _31 = 0; _32 = 0; _33 = 1;
}
//ägëÂèkè¨çsóÒÇÇ¬Ç≠ÇÈ
void MATRIX2::scaling(float x, float y) {
    _11 = x; _12 = 0; _13 = 0;
    _21 = 0; _22 = y; _23 = 0;
    _31 = 0; _32 = 0; _33 = 1;
}
//âÒì]çsóÒÇÇ¬Ç≠ÇÈ
void MATRIX2::rotate(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    _11 = c; _12 = -s; _13 = 0;
    _21 = s; _22 = c; _23 = 0;
    _31 = 0; _32 = 0; _33 = 1;
}
//ïΩçsà⁄ìÆçsóÒÇÇ¬Ç≠ÇÈ
void MATRIX2::translate(float x, float y) {
    _11 = 1; _12 = 0; _13 = x;
    _21 = 0; _22 = 1; _23 = y;
    _31 = 0; _32 = 0; _33 = 1;
}
//ÅuÇRçsÇRóÒçsóÒÅvÇ∆ÅuÇQçsÇPóÒçsóÒÅiÇQéüå≥ÉxÉNÉgÉãÅjÅ{ÇPçsÅvÇÃä|ÇØéZ
Vec2 MATRIX2::operator*(const Vec2& v) {
    return Vec2(
        _11 * v.x + _12 * v.y + _13 * 1,
        _21 * v.x + _22 * v.y + _23 * 1
    );
}
//ÇRçsÇRóÒçsóÒÇ«Ç§ÇµÇÃä|ÇØéZ
MATRIX2 MATRIX2::operator*(const MATRIX2& m) {

    MATRIX2 tmp;

    tmp._11 = _11 * m._11 + _12 * m._21 + _13 * m._31;
    tmp._11 = _11 * m._12 + _12 * m._22 + _13 * m._32;
    tmp._11 = _11 * m._13 + _12 * m._23 + _13 * m._33;
    tmp._21 = _21 * m._11 + _22 * m._21 + _23 * m._31;
    tmp._21 = _21 * m._12 + _22 * m._22 + _23 * m._32;
    tmp._21 = _21 * m._13 + _22 * m._23 + _23 * m._33;
    tmp._31 = _31 + m._11 + _32 * m._21 + _33 * m._31;
    tmp._31 = _31 + m._12 + _32 * m._22 + _33 * m._32;
    tmp._31 = _31 + m._13 + _32 * m._23 + _33 * m._33;

    return tmp;
}
//--------------------------------------------------------
//ç≈ìKâªÇ≥ÇÍÇΩMAT33ìØémÇÃä|ÇØéZ
//--------------------------------------------------------
void MATRIX2::mulTranslate(float x, float y) {
    // |_11 _12 _13|    |1  0  x| Å@ |_11  _12  _11x+_12y+_13| 
    // |_21 _22 _23| Å~ |0  1  y| ÅÅ |_21  _22  _21x+_22y+_23|
    // |  0   0   1|    |0  0  1|    |  0    0              1|
    _13 += _11 * x + _12 * y;
    _23 += _21 * x + _22 * y;
}
void MATRIX2::mulScaling(float x, float y) {
    // |_11 _12 _13|    |x  0  0| Å@ |_11x _12y _13|
    // |_21 _22 _23| Å~ |0  y  0| ÅÅ |_21x _22y _23|
    // |  0   0   1|    |0  0  1|    |  0    0    1|
    _11 *= x;    _12 *= y;
    _21 *= x;    _22 *= y;
}
void MATRIX2::mulRotate(float angle) {
    // |_11 _12 _13|    |c -s  0| Å@ |_11c+_12s   _11(-s)+_12c   _13|
    // |_21 _22 _23| Å~ |s  c  0| ÅÅ |_21c+_22s   _21(-s)+_22c   _23|
    // |  0   0   1|    |0  0  1|    |        0             0      1|
    float c = cos(angle);
    float s = sin(angle);
    float tmp;
    //1çsñ⁄
    tmp = _11 * c + _12 * s;
    _12 = _11 * -s + _12 * c;
    _11 = tmp;
    //2çsñ⁄
    tmp = _21 * c + _22 * s;
    _22 = _21 * -s + _22 * c;
    _21 = tmp;
}



void MATRIX3::Identity() {
    _11 = 1;     _12 = 0;     _13 = 0;     _14 = 0;
    _21 = 0;     _22 = 1;     _23 = 0;     _24 = 0;
    _31 = 0;     _32 = 0;     _33 = 1;     _34 = 0;
    _41 = 0;     _42 = 0;     _43 = 0;     _44 = 1;
}
void MATRIX3::Translate(float x, float y, float z){
    _11 = 1;     _12 = 0;     _13 = 0;     _14 = x;
    _21 = 0;     _22 = 1;     _23 = 0;     _24 = y;
    _31 = 0;     _32 = 0;     _33 = 1;     _34 = z;
    _41 = 0;     _42 = 0;     _43 = 0;     _44 = 1;
}
void MATRIX3::Translate(class Vec3& t){
    _11 = 1;     _12 = 0;     _13 = 0;     _14 = t.x;
    _21 = 0;     _22 = 1;     _23 = 0;     _24 = t.y;
    _31 = 0;     _32 = 0;     _33 = 1;     _34 = t.z;
    _41 = 0;     _42 = 0;     _43 = 0;     _44 = 1;
}
void MATRIX3::Scaling(float x, float y, float z){
    _11 = x;     _12 = 0;     _13 = 0;     _14 = 0;
    _21 = 0;     _22 = y;     _23 = 0;     _24 = 0;
    _31 = 0;     _32 = 0;     _33 = z;     _34 = 0;
    _41 = 0;     _42 = 0;     _43 = 0;     _44 = 1;
}
void MATRIX3::RotateZ(float angle){
    float c = cosf(angle);
    float s = sinf(angle);
    _11 = c;     _12 = -s;     _13 = 0;     _14 = 0;
    _21 = s;     _22 = c;     _23 = 0;     _24 = 0;
    _31 = 0;     _32 = 0;     _33 = 1;     _34 = 0;
    _41 = 0;     _42 = 0;     _43 = 0;     _44 = 1;
}
void MATRIX3::camera(const Vec3& campos, const Vec3& lookatpos, const Vec3& upvec){
    //ÉJÉÅÉâÇÃÉçÅ[ÉJÉãé≤ç¿ïWÇãÅÇﬂÇÈ(ê≥ãKíºåÉxÉNÉgÉãÅj
    Vec3 z = normalize(campos - lookatpos);
    Vec3 x = normalize(cross(upvec, z));
    Vec3 y = cross(z, x);
    _11 = x.x;    _12 = x.y;    _13 = x.z;    _14 = x.x * -campos.x + x.y * -campos.y + x.z * -campos.z;
    _21 = y.x;    _22 = y.y;    _23 = y.z;    _24 = y.x * -campos.x + y.y * -campos.y + y.z * -campos.z;
    _31 = z.x;    _32 = z.y;    _33 = z.z;    _34 = z.x * -campos.x + z.y * -campos.y + z.z * -campos.z;
    _41 = 0;      _42 = 0;      _43 = 0;      _44 = 1;
}
void MATRIX3::pers(float angle, float aspect, float n, float f){
    float s = 1.0f / tanf(angle * 0.5f);
    float a = f / (-f + n);
    float b = a * n;
    _11 = s / aspect;   _12 = 0;        _13 = 0;            _14 = 0;
    _21 = 0;            _22 = s;        _23 = 0;            _24 = 0;
    _31 = 0;            _32 = 0;        _33 = a;            _34 = b;
    _41 = 0;            _42 = 0;        _43 = -1;           _44 = 0;
}
void MATRIX3::MulTranslate(float x, float y, float z){
    _14 += _11 * x + _12 * y + _13 * z;
    _24 += _21 * x + _22 * y + _23 * z;
    _34 += _31 * x + _32 * y + _33 * z;
}
void MATRIX3::MulTranslate(const Vec3& t){
    _14 += _11 * t.x + _12 * t.y + _13 * t.z;
    _24 += _21 * t.x + _22 * t.y + _23 * t.z;
    _34 += _31 * t.x + _32 * t.y + _33 * t.z;
}
void MATRIX3::MulScaling(float x, float y, float z){
    _11 *= x;    _12 *= y;    _13 *= z;
    _21 *= x;    _22 *= y;    _23 *= z;
    _31 *= x;    _32 *= y;    _33 *= z;
}
void MATRIX3::MulScaling(const Vec3& s){
    _11 *= s.x;    _12 *= s.y;    _13 *= s.z;
    _21 *= s.x;    _22 *= s.y;    _23 *= s.z;
    _31 *= s.x;    _32 *= s.y;    _33 *= s.z;
}
void MATRIX3::MulRotateZ(float angle){
    float c = cosf(angle);
    float s = sinf(angle);
    float tmp;
    //1çsñ⁄
    tmp = _11 * c + _12 * s;
    _12 = _11 * -s + _12 * c;
    _11 = tmp;
    //2çsñ⁄
    tmp = _21 * c + _22 * s;
    _22 = _21 * -s + _22 * c;
    _21 = tmp;
    //3çsñ⁄
    tmp = _31 * c + _32 * s;
    _32 = _31 * -s + _32 * c;
    _31 = tmp;
}
MATRIX3 MATRIX3::operator*(const MATRIX3& m)const {
    MATRIX3 tmp;

    tmp._11 = _11 * m._11 + _12 * m._21 + _13 * m._31 + _14 * m._41;
    tmp._21 = _21 * m._11 + _22 * m._21 + _23 * m._31 + _24 * m._41;
    tmp._31 = _31 * m._11 + _32 * m._21 + _33 * m._31 + _34 * m._41;
    tmp._41 = _41 * m._11 + _42 * m._21 + _43 * m._31 + _44 * m._41;

    tmp._12 = _11 * m._12 + _12 * m._22 + _13 * m._32 + _14 * m._42;
    tmp._22 = _21 * m._12 + _22 * m._22 + _23 * m._32 + _24 * m._42;
    tmp._32 = _31 * m._12 + _32 * m._22 + _33 * m._32 + _34 * m._42;
    tmp._42 = _41 * m._12 + _42 * m._22 + _43 * m._32 + _44 * m._42;

    tmp._13 = _11 * m._13 + _12 * m._23 + _13 * m._33 + _14 * m._43;
    tmp._23 = _21 * m._13 + _22 * m._23 + _23 * m._33 + _24 * m._43;
    tmp._33 = _31 * m._13 + _32 * m._23 + _33 * m._33 + _34 * m._43;
    tmp._43 = _41 * m._13 + _42 * m._23 + _43 * m._33 + _44 * m._43;

    tmp._14 = _11 * m._14 + _12 * m._24 + _13 * m._34 + _14 * m._44;
    tmp._24 = _21 * m._14 + _22 * m._24 + _23 * m._34 + _24 * m._44;
    tmp._34 = _31 * m._14 + _32 * m._24 + _33 * m._34 + _34 * m._44;
    tmp._44 = _41 * m._14 + _42 * m._24 + _43 * m._34 + _44 * m._44;

    return tmp;
}
Vec3 MATRIX3::operator*(const Vec3& v)const {
    Vec3 tmp;
    tmp.x = _11 * v.x + _12 * v.y + _13 * v.z + _14;
    tmp.y = _21 * v.x + _22 * v.y + _23 * v.z + _24;
    tmp.z = _31 * v.x + _32 * v.y + _33 * v.z + _34;
    //projÇ∆ÇÃä|ÇØéZ
    if (_43 < 0) {//âûópÇ™Ç´Ç©Ç»Ç¢Ç™ÅAÇ±ÇÍÇ≈proj matÇ∆îªíf
        if (v.z != 0) {
            return tmp / (v.z < 0 ? -v.z : v.z);
        }
    }
    //projà»äOÇÃä|ÇØéZ
    return tmp;
}