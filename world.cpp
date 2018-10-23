#include "world.hpp"
#include <vector>
#include "sphere.hpp"

namespace phys
{
    World::World()
    {
    }

    World::World(Boundary* box):
        m_boundary{box}
    {
    }

    World::World(Vec3 gravity):
        m_gravity{gravity}
    {
    }

    World::World(Vec3 gravity,Boundary* box):
        m_gravity{gravity},
        m_boundary{box}
    {
    }

    World::World(Vec3 gravity, double density):
        m_gravity{gravity},
        m_density{density}
    {
    }

    World::World(Vec3 gravity, double density,Boundary* box):
        m_gravity{gravity},
        m_density{density},
        m_boundary{box}
    {
    }

    World::~World()
    {
        if (m_boundary != nullptr)
            delete m_boundary;
        m_boundary = nullptr;
    }

    Vec3 World::getGravity() const
    {
        return m_gravity;
    }

    void World::setGravity(const Vec3 &gravity)
    {
        m_gravity = gravity;
    }

    double World::getDensity() const
    {
        return m_density;
    }

    void World::setDensity(double density)
    {
        m_density = density;
    }

    void World::addSphere(Sphere *sphere)
    {
        m_num_spheres++;
        m_spheres.push_back(sphere);
    }

    unsigned int World::getNumSpheres() const
    {
        return m_num_spheres;
    }

    void World::update()
    {
        if (m_num_spheres > 0)
        {
            for (int i{0}; i < m_num_spheres; i++)
            {
                this->updateDynamics(m_spheres[i]);
//                if (i>0)
//                    for (int j{i-1}; j >= 0; j--)
//                        this->checkForSphereCollision(m_spheres[i],m_spheres[j]);
                for (int j{0}; j < m_num_spheres; j++)
                {
                    if (i!=j)
                        this->checkForSphereCollision(m_spheres[i],m_spheres[j]);
                }
            }
//            for (int i{0}; i < m_num_spheres; i++)
//            {
//                for (int j{0}; j < m_num_spheres; j++)
//                {
//                    if (i!=j)
//                        this->checkForSphereCollision(m_spheres[i],m_spheres[j]);
//                }
//            }
        }
    }

    double World::getDt()
    {
        return m_dt;
    }

    void World::setDt(double dt)
    {
        m_dt = dt;
    }

    void World::updateDynamics(Sphere* sphere)
    {
        Vec3 drag_force{0,0,0};
        drag_force = 0.5*m_density*sphere->getVelocity()*sphere->getVelocity()*sphere->getDragCoef();
        Vec3 acc{0,0,0};
        acc = m_gravity - drag_force*phys::Vec3::sign(sphere->getVelocity())/sphere->getMass();
        sphere->update(m_dt,acc,m_boundary);
    }

    void World::checkForSphereCollision(Sphere *sphere1, Sphere *sphere2)
    {
        double dist_apart{0};
        dist_apart = Vec3::norm(sphere1->getPosition()-sphere2->getPosition());
        if (dist_apart < sphere1->getRadius()+sphere2->getRadius())
        {
            sphere1->handleSphereCollision(sphere2,m_boundary);
        }
    }

    void World::setBoundary(Boundary *boundary)
    {
        m_boundary = boundary;
    }

    Boundary* World::getBoundary() const
    {
        return m_boundary;
    }

    void World::clearWorld()
    {
        for (int i{m_num_spheres-1}; i >= 0; i--)
        {
            delete m_spheres[i];
            m_spheres[i] = nullptr;
            m_spheres.pop_back();
        }
        m_num_spheres = 0;
    }
}
