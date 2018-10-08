#ifndef VEC3_H
#define VEC3_H

namespace phys
{
    class vec3
    {
    public:
        vec3();
        vec3(float getX,float y,float z);

        vec3 operator +(vec3 rhs);
        vec3 operator -(vec3 rhs);
        vec3 operator -();
        vec3 operator +(float value);
        vec3 operator -(float value);
        vec3 operator *(float value);
        vec3 operator /(float value);
        bool operator ==(const vec3 rhs) const;

        float getX() const;
        float getY() const;
        float getZ() const;
        static vec3 abs(vec3 vector);

    private:
        float m_x{0};
        float m_y{0};
        float m_z{0};
    };

    vec3 operator +(float lhs, vec3 rhs);
    vec3 operator -(float lhs, vec3 rhs);
}
#endif // VEC3_H
