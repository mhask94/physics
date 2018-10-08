#include "vec3.hpp"

namespace phys
{

    vec3::vec3(){}

    vec3::vec3(float x,float y,float z):
        m_x{x}, m_y{y}, m_z{z}
    {
    }

    float vec3::getX() const
    {
        return m_x;
    }

    float vec3::getY() const
    {
        return m_y;
    }

    float vec3::getZ() const
    {
        return m_z;
    }

    vec3 vec3::operator +(vec3 rhs)
    {
        return vec3{this->m_x+rhs.m_x,this->m_y+rhs.m_y,this->m_z+rhs.m_z};
    }

    vec3 vec3::operator +(float value)
    {
        return vec3{this->m_x+value,this->m_y+value,this->m_z+value};
    }

    vec3 vec3::operator -(vec3 rhs)
    {
        return vec3{this->m_x-rhs.m_x,this->m_y-rhs.m_y,this->m_z-rhs.m_z};
    }

    vec3 vec3::operator -()
    {
        return vec3{-this->m_x,-this->m_y,-this->m_z};
    }

    vec3 vec3::operator -(float value)
    {
        return vec3{this->m_x+value,this->m_y+value,this->m_z+value};
    }

    vec3 vec3::operator *(float value)
    {
        return vec3{this->m_x*value,this->m_y*value,this->m_z*value};
    }

    vec3 vec3::operator /(float value)
    {
        return vec3{this->m_x/value,this->m_y/value,this->m_z/value};
    }

    bool vec3::operator ==(const vec3 rhs) const
    {
        return (this->m_x==rhs.m_x && this->m_y==rhs.m_y && this->m_z==rhs.m_z);
    }

    vec3 operator+(float lhs, vec3 rhs)
    {
        return rhs + lhs;
    }

    vec3 operator-(float lhs, vec3 rhs)
    {
        return -rhs + lhs;
    }
}
