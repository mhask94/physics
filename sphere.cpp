#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(float mass,vec3 position):
        m_mass{mass},
        m_position{position}
    {
    }

    Sphere::Sphere(float mass,vec3 position,vec3 velocity):
        m_mass{mass},
        m_position{position},
        m_velocity{velocity}
    {
    }

    Sphere::~Sphere()
    {
    }

    void Sphere::update(float dt,vec3 gravity,float density)
    {
        m_acceleration = gravity + 0.0;
        m_velocity = m_velocity + m_acceleration*dt;
        m_position = m_position + m_velocity*dt;
    }

    vec3 Sphere::getPosition() const
    {
        return m_position;
    }

    vec3 Sphere::getVelocity() const
    {
        return m_velocity;
    }

    vec3 Sphere::getAcceleration() const
    {
        return m_acceleration;
    }

//    void Sphere::setAcceleration(const vec3 &acceleration)
//    {
//        m_acceleration = acceleration;
//    }

    float Sphere::getMass() const
    {
        return m_mass;
    }
}
