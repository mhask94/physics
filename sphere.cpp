#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(float radius,float mass,vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_drag_coef{0.8f*3.14159f*radius*radius}
    {
    }

    Sphere::Sphere(float radius,float mass,vec3 position,vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_drag_coef{0.8f*3.14159f*radius*radius}
    {
    }

    Sphere::~Sphere()
    {
    }

    void Sphere::update(float dt,vec3 acceleration)
    {
        m_acceleration = acceleration;
        m_velocity = m_velocity + m_acceleration*dt;
        m_position = m_position + m_velocity*dt;

        if (m_position.getX() > 5.f-m_radius || m_position.getX() < -5.f+m_radius)
            m_velocity *= vec3{-1,1,1}*m_coef_restitution;
        if (m_position.getY() > 5-m_radius || m_position.getY() < -5+m_radius)
            m_velocity *= vec3{1,-1,1}*m_coef_restitution;
        if (m_position.getZ() > 5-m_radius || m_position.getZ() < -5+m_radius)
            m_velocity *= vec3{1,1,-1}*m_coef_restitution;

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

    float Sphere::getDragCoef() const
    {
        return m_drag_coef;
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
