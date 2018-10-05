#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(vec3 position,vec3 velocity):
        m_position{position},
        m_velocity{velocity}
    {
    }

    Sphere::~Sphere()
    {
    }

    void Sphere::update()
    {
        m_velocity = m_velocity + m_acceleration*m_dt;
    }

    float Sphere::getDt() const
    {
        return m_dt;
    }

    void Sphere::setDt(float dt)
    {
        m_dt = dt;
    }
}
