#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(float radius,float mass,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_drag_coef{0.15f*3.14159f*radius*radius}
    {
    }

    Sphere::Sphere(float radius,float mass,Vec3 position,Vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_drag_coef{0.15f*3.14159f*radius*radius}
    {
    }

    Sphere::Sphere(float radius,float mass,float c_r,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_coef_restitution{c_r},
        m_drag_coef{0.15f*3.14159f*radius*radius}
    {
    }

    Sphere::Sphere(float radius,float mass,float c_r,Vec3 position,Vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_coef_restitution{c_r},
        m_drag_coef{0.15f*3.14159f*radius*radius}
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

    void Sphere::fixTinyBouncesAtWall()
    {
        m_velocity = (Vec3::abs(m_velocity).getY() < .00000000001f) ? m_velocity * Vec3{1,0,1} : m_velocity;
        m_velocity = (Vec3::abs(m_velocity).getZ() < .00000000001f) ? m_velocity * Vec3{1,1,0} : m_velocity;
        m_velocity = (Vec3::abs(m_velocity).getX() < .00000000001f) ? m_velocity * Vec3{0,1,1} : m_velocity;

        if (m_velocity.getX()==m_velocity.getY()==0 || m_velocity.getX()==m_velocity.getZ()==0 || m_velocity.getY()==m_velocity.getZ()==0)
            m_velocity *= Vec3{0,0,0};
    }

    void Sphere::update(float dt,Vec3 acceleration,Boundary* box)
    {
        Vec3 zero{0,0,0};
        m_velocity = m_velocity + acceleration*dt;
        if (Vec3::anyElementIsNear(m_velocity,zero,.00000000001f) && this->isNearWall(box) && m_velocity!=zero)
            fixTinyBouncesAtWall();
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

    float Sphere::getDragCoef() const
    {
        return m_drag_coef;
    }

    float Sphere::getRadius() const
    {
        return m_radius;
    }

    bool Sphere::isNearWall(Boundary* box)
    {
        if (box == nullptr)
            return false;
        if (m_position.getX() >= box->max_x-m_radius-0.1f || m_position.getX() <= box->min_x+m_radius+0.1f)
            return true;
        else if (m_position.getY() >= box->max_y-m_radius-0.1f || m_position.getY() <= box->min_y+m_radius+0.1f)
            return true;
        else if (m_position.getZ() >= box->max_z-m_radius-0.1f || m_position.getZ() <= box->min_z+m_radius+0.1f)
            return true;
        else
            return false;
    }

    float Sphere::getMass() const
    {
        return m_mass;
    }
}
