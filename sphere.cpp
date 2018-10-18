#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(double radius,double mass,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_frontal_area{3.14159*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::Sphere(double radius,double mass,Vec3 position,Vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_frontal_area{3.14159*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::Sphere(double radius,double mass,double c_r,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_coef_restitution{c_r},
        m_frontal_area{3.14159*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::Sphere(double radius,double mass,double c_r,Vec3 position,Vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_coef_restitution{c_r},
        m_frontal_area{3.14159*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::~Sphere()
    {
    }

    void Sphere::handleBoundaryCollision(Boundary* box)
    {
        double dist_out{0};
        if (m_position.getX() > box->max_x-m_radius || m_position.getX() < box->min_x+m_radius)
        {
            dist_out = (m_position.getX()>0) ? m_position.getX()+m_radius-box->max_x : m_position.getX()-m_radius-box->min_x;
            m_position -= Vec3{dist_out,0,0};
            m_velocity *= Vec3{-1,1,1}*m_coef_restitution;
        }
        if (m_position.getY() > box->max_y-m_radius || m_position.getY() < box->min_y+m_radius)
        {
            dist_out = (m_position.getY()>0) ? m_position.getY()+m_radius-box->max_y : m_position.getY()-m_radius-box->min_y;
            m_position -= Vec3{0,dist_out,0};
            m_velocity *= Vec3{1,-1,1}*m_coef_restitution;
        }
        if (m_position.getZ() > box->max_z-m_radius || m_position.getZ() < box->min_z+m_radius)
        {
            dist_out = (m_position.getZ()>0) ? m_position.getZ()+m_radius-box->max_z : m_position.getZ()-m_radius-box->min_z;
            m_position -= Vec3{0,0,dist_out};
            m_velocity *= Vec3{1,1,-1}*m_coef_restitution;
        }
    }

    void Sphere::update(double dt,Vec3 acceleration,Boundary* box)
    {
        m_velocity = m_velocity + acceleration*dt;
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

    double Sphere::getDragCoef() const
    {
        return m_drag_coef;
    }

    double Sphere::getRadius() const
    {
        return m_radius;
    }

    bool Sphere::isNearWall(Boundary* box)
    {
        double buffer{0.1};
        if (box == nullptr)
            return false;
        if (m_position.getX() >= box->max_x-m_radius-buffer || m_position.getX() <= box->min_x+m_radius+buffer)
            return true;
        else if (m_position.getY() >= box->max_y-m_radius-buffer || m_position.getY() <= box->min_y+m_radius+buffer)
            return true;
        else if (m_position.getZ() >= box->max_z-m_radius-buffer || m_position.getZ() <= box->min_z+m_radius+buffer)
            return true;
        else
            return false;
    }

    double Sphere::getMass() const
    {
        return m_mass;
    }
}
