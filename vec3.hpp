#ifndef VEC3_H
#define VEC3_H

namespace phys
{
    class Vec3
    {
    public:
        Vec3();
        Vec3(float x,float y,float z);

        Vec3 operator +(Vec3 rhs);
        Vec3 operator -(Vec3 rhs);
        Vec3 operator *(Vec3 rhs);
        void operator +=(Vec3 rhs);
        void operator -=(Vec3 rhs);
        void operator *=(Vec3 rhs);
        Vec3 operator -();
        Vec3 operator +(float value);
        Vec3 operator -(float value);
        Vec3 operator *(float value);
        Vec3 operator /(float value);
        void operator +=(float value);
        void operator -=(float value);
        void operator *=(float value);
        void operator /=(float value);
        bool operator ==(const Vec3 rhs) const;

        float getX() const;
        float getY() const;
        float getZ() const;
        int signX();
        int signY();
        int signZ();
        static Vec3 abs(Vec3 vector);

    private:
        float m_x{0};
        float m_y{0};
        float m_z{0};
    };

    Vec3 operator +(float lhs, Vec3 rhs);
    Vec3 operator -(float lhs, Vec3 rhs);
    Vec3 operator *(float lhs, Vec3 rhs);
}
#endif // VEC3_H
