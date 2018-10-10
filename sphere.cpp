#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(float radius,float mass,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_drag_coef{0.8f*3.14159f*radius*radius}
    {
    }

    Sphere::Sphere(float radius,float mass,Vec3 position,Vec3 velocity):
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

    void Sphere::handleBoundaryCollision(Boundary* box)
    {
        if (m_position.getX() > box->max_x-m_radius || m_position.getX() < box->min_x+m_radius)
        {
            float dist_out;
            dist_out = (m_position.getX()>0) ? dist_out=m_position.getX()+m_radius-box->max_x : dist_out=m_position.getX()-m_radius-box->min_x;
            m_position -= Vec3{dist_out,0.f,0.f};
            m_velocity *= Vec3{-1.f,1.f,1.f}*m_coef_restitution;
        }
        if (m_position.getY() > box->max_y-m_radius || m_position.getY() < box->min_y+m_radius)
        {
            float dist_out;
            dist_out = (m_position.getY()>0) ? dist_out=m_position.getY()+m_radius-box->max_y : dist_out=m_position.getY()-m_radius-box->min_y;
            m_position -= Vec3{0.f,dist_out,0.f};
            m_velocity *= Vec3{1.f,-1.f,1.f}*m_coef_restitution;
        }
        if (m_position.getZ() > box->max_z-m_radius || m_position.getZ() < box->min_z+m_radius)
        {
            float dist_out;
            dist_out = (m_position.getZ()>0) ? dist_out=m_position.getZ()+m_radius-box->max_z : dist_out=m_position.getZ()-m_radius-box->min_z;
            m_position -= Vec3{0.f,0.f,dist_out};
            m_velocity *= Vec3{1.f,1.f,-1.f}*m_coef_restitution;
        }
    }

    void Sphere::update(float dt,Vec3 acceleration,Boundary* box)
    {
        m_acceleration = acceleration;
        m_velocity = m_velocity + m_acceleration*dt;
        m_position = m_position + m_velocity*dt;

        if (box != nullptr)
            handleBoundaryCollision(box);
    }

    Vec3 Sphere::getPosition() const
    {
        return m_position;
    }

    Vec3 Sphere::getVelocity() const
    {
        return m_velocity;
    }

    Vec3 Sphere::getAcceleration() const
    {
        return m_acceleration;
    }

    float Sphere::getDragCoef() const
    {
        return m_drag_coef;
    }

    float Sphere::getMass() const
    {
        return m_mass;
    }
}
