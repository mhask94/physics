#include "vec3.hpp"

namespace phys
{
    Vec3::Vec3(){}

    Vec3::Vec3(float x,float y,float z):
        m_x{x}, m_y{y}, m_z{z}
    {
    }

    float Vec3::getX() const
    {
        return m_x;
    }

    float Vec3::getY() const
    {
        return m_y;
    }

    float Vec3::getZ() const
    {
        return m_z;
    }

    int Vec3::signX()
    {
        int x{0};
        return x = (this->getX() < 0) ? x=-1 : x=1;
    }

    int Vec3::signY()
    {
        int y{0};
        return y = (this->getY() < 0) ? y=-1 : y=1;
    }

    int Vec3::signZ()
    {
        int z{0};
        return z = (this->getZ() < 0) ? z=-1 : z=1;
    }

    Vec3 Vec3::sign(Vec3 vector)
    {
        vector.m_x = vector.signX();
        vector.m_y = vector.signY();
        vector.m_z = vector.signZ();
        return vector;
    }

    Vec3 Vec3::abs(Vec3 vector)
    {
        Vec3 new_vector{0,0,0};
        new_vector.m_x = vector.m_x < 0 ? vector.m_x*=-1 : vector.m_x*=1;
        new_vector.m_y = vector.m_y < 0 ? vector.m_y*=-1 : vector.m_y*=1;
        new_vector.m_z = vector.m_z < 0 ? vector.m_z*=-1 : vector.m_z*=1;

        return new_vector;
    }

    Vec3 Vec3::operator +(Vec3 rhs)
    {
        return Vec3{this->m_x+rhs.m_x,this->m_y+rhs.m_y,this->m_z+rhs.m_z};
    }

    Vec3 Vec3::operator +(float value)
    {
        return Vec3{this->m_x+value,this->m_y+value,this->m_z+value};
    }

    Vec3 Vec3::operator -(Vec3 rhs)
    {
        return Vec3{this->m_x-rhs.m_x,this->m_y-rhs.m_y,this->m_z-rhs.m_z};
    }

    Vec3 Vec3::operator *(Vec3 rhs)
    {
        return Vec3{this->m_x*rhs.m_x,this->m_y*rhs.m_y,this->m_z*rhs.m_z};
    }

    void Vec3::operator +=(Vec3 rhs)
    {
        *this = (*this) + rhs;
    }

    void Vec3::operator -=(Vec3 rhs)
    {
        *this = (*this) - rhs;
    }

    void Vec3::operator *=(Vec3 rhs)
    {
        *this = (*this) * rhs;
    }

    Vec3 Vec3::operator -()
    {
        return Vec3{-this->m_x,-this->m_y,-this->m_z};
    }

    Vec3 Vec3::operator -(float value)
    {
        return Vec3{this->m_x-value,this->m_y-value,this->m_z-value};
    }

    Vec3 Vec3::operator *(float value)
    {
        return Vec3{this->m_x*value,this->m_y*value,this->m_z*value};
    }

    Vec3 Vec3::operator /(float value)
    {
        return Vec3{this->m_x/value,this->m_y/value,this->m_z/value};
    }

    void Vec3::operator +=(float value)
    {
        *this = (*this) + value;
    }

    void Vec3::operator -=(float value)
    {
        *this = (*this) - value;
    }

    void Vec3::operator *=(float value)
    {
        *this = (*this) * value;
    }

    void Vec3::operator /=(float value)
    {
        *this = (*this) / value;
    }

    bool Vec3::operator ==(const Vec3 rhs) const
    {
        return (this->m_x==rhs.m_x && this->m_y==rhs.m_y && this->m_z==rhs.m_z);
    }

    bool Vec3::operator !=(const Vec3 rhs) const
    {
        return (this->m_x!=rhs.m_x && this->m_y!=rhs.m_y && this->m_z!=rhs.m_z);
    }

    Vec3 operator+(float lhs, Vec3 rhs)
    {
        return rhs + lhs;
    }

    Vec3 operator-(float lhs, Vec3 rhs)
    {
        return -rhs + lhs;
    }

    Vec3 operator *(float lhs, Vec3 rhs)
    {
        return rhs * lhs;
    }

}
