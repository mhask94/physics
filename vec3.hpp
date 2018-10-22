#ifndef VEC3_H
#define VEC3_H

namespace phys
{
    class Vec3
    {
    public:
        Vec3();
        Vec3(double x,double y,double z);

        Vec3 operator +(Vec3 rhs);
        Vec3 operator -(Vec3 rhs);
        Vec3 operator *(Vec3 rhs);
        void operator +=(Vec3 rhs);
        void operator -=(Vec3 rhs);
        void operator *=(Vec3 rhs);
        Vec3 operator -();
        Vec3 operator +(double value);
        Vec3 operator -(double value);
        Vec3 operator *(double value);
        Vec3 operator /(double value);
        void operator +=(double value);
        void operator -=(double value);
        void operator *=(double value);
        void operator /=(double value);
        bool operator ==(const Vec3 rhs) const;
        bool operator !=(const Vec3 rhs) const;

        double getX() const;
        double getY() const;
        double getZ() const;
        int signX();
        int signY();
        int signZ();
        static Vec3 sign(Vec3 vector);
        static Vec3 abs(Vec3 vector);
        static bool isNear(Vec3 vec1,Vec3 vec2,double delta);
        static bool anyElementIsNear(Vec3 vec1,Vec3 vec2,double delta);
        static double dot(Vec3 vec1,Vec3 vec2);
        static double norm(Vec3 vector);
        static double norm2(Vec3 vector);

    private:
        double m_x{0};
        double m_y{0};
        double m_z{0};
    };

    Vec3 operator +(double lhs, Vec3 rhs);
    Vec3 operator -(double lhs, Vec3 rhs);
    Vec3 operator *(double lhs, Vec3 rhs);
}
#endif // VEC3_H
