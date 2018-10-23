#include "sphere.hpp"

namespace phys
{
    Sphere::Sphere(double radius,double mass,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_frontal_area{pi*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::Sphere(double radius,double mass,Vec3 position,Vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_frontal_area{pi*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::Sphere(double radius,double mass,double c_r,Vec3 position):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_coef_restitution{c_r},
        m_frontal_area{pi*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::Sphere(double radius,double mass,double c_r,Vec3 position,Vec3 velocity):
        m_radius{radius},
        m_mass{mass},
        m_position{position},
        m_velocity{velocity},
        m_coef_restitution{c_r},
        m_frontal_area{pi*radius*radius}
    {
        m_drag_coef = m_drag_coef*m_frontal_area;
    }

    Sphere::~Sphere()
    {
        m_radius = 0;
        m_mass = 0;
//        m_position{0,0,0};
//        m_velocity{0,0,0};
        m_coef_restitution = 0;
        m_frontal_area = 0;
        m_drag_coef = 0;
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

    void Sphere::handleSphereCollision(Sphere *other_sphere)
    {
        // Get rid of overlap first
        Vec3 pos_diff{other_sphere->m_position-m_position};
        double pos_diff_norm{Vec3::norm(pos_diff)};
        double overlap{m_radius+other_sphere->m_radius-pos_diff_norm};
        Vec3 shift_dir{pos_diff/pos_diff_norm};
        if (Vec3::norm(other_sphere->m_velocity) > Vec3::norm(m_velocity))
        {
            other_sphere->m_position += shift_dir*overlap;
            Vec3 abs_pos{Vec3::abs(other_sphere->m_position)};
            if (abs_pos.getX() > 5 || abs_pos.getY() > 5 || abs_pos.getZ() > 5)
            {
                double x = (abs_pos.getX() > 5) ? 5*other_sphere->m_position.signX() : other_sphere->m_position.getX();
                double y = (abs_pos.getY() > 5) ? 5*other_sphere->m_position.signY() : other_sphere->m_position.getY();
                double z = (abs_pos.getZ() > 5) ? 5*other_sphere->m_position.signZ() : other_sphere->m_position.getZ();
                other_sphere->m_position = Vec3{x,y,z};
            }
        }
        else
        {
            m_position -= shift_dir*overlap;
            Vec3 abs_pos{Vec3::abs(m_position)};
            if (abs_pos.getX() > 5 || abs_pos.getY() > 5 || abs_pos.getZ() > 5)
            {
                double x = (abs_pos.getX() > 5) ? 5*m_position.signX() : m_position.getX();
                double y = (abs_pos.getY() > 5) ? 5*m_position.signY() : m_position.getY();
                double z = (abs_pos.getZ() > 5) ? 5*m_position.signZ() : m_position.getZ();
                m_position = Vec3{x,y,z};
            }
        }

        // Update velocities
        pos_diff = other_sphere->m_position-m_position;
        Vec3 vel_diff{other_sphere->m_velocity-m_velocity};
        double mass_sum{m_mass+other_sphere->m_mass};
        double m1_frac{2*m_mass/mass_sum};
        double m2_frac{2*other_sphere->m_mass/mass_sum};
        Vec3 projection{Vec3::dot(vel_diff,pos_diff)/Vec3::norm2(pos_diff)*pos_diff};
        other_sphere->m_velocity = other_sphere->m_coef_restitution*(other_sphere->m_velocity-m1_frac*projection);
        m_velocity = m_coef_restitution*(m_velocity+m2_frac*projection);

//        Vec3 pos_diff{m_position-other_sphere->m_position};
//        Vec3 vel_diff{m_velocity-other_sphere->m_velocity};
//        double mass_sum{m_mass+other_sphere->m_mass};
//        double m2_frac{2*other_sphere->m_mass/mass_sum};
//        double m1_frac{2*m_mass/mass_sum};
//        Vec3 projection{Vec3::dot(vel_diff,pos_diff)/Vec3::norm2(pos_diff)*pos_diff};
//        m_velocity = m_coef_restitution*(m_velocity-m2_frac*projection);
//        other_sphere->m_velocity = other_sphere->m_coef_restitution*(other_sphere->m_velocity+m1_frac*projection);

//        Vec3 shift_dir{pos_diff/Vec3::norm(pos_diff)};
//        double overlap{m_radius+other_sphere->m_radius-Vec3::norm(pos_diff)};
//        double radius_sum{this->m_radius+other_sphere->m_radius};
//        m_position += shift_dir*overlap*other_sphere->m_radius/radius_sum;
//        other_sphere->m_position += shift_dir*overlap*m_radius/radius_sum;

//        other_sphere->m_position += other_sphere->m_velocity/Vec3::norm(other_sphere->m_velocity)*overlap;
//        m_position += m_velocity/Vec3::norm(m_velocity)*overlap;
    }

    double Sphere::getMass() const
    {
        return m_mass;
    }
}
