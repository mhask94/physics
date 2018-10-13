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

    World::World(Vec3 gravity, float density):
        m_gravity{gravity},
        m_density{density}
    {
    }

    World::World(Vec3 gravity, float density,Boundary* box):
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

    float World::getDensity() const
    {
        return m_density;
    }

    void World::setDensity(float density)
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
        for (unsigned int i{0}; i < m_num_spheres; i++)
        {
            this->updateDynamics(m_spheres[i]);
        }
    }

    float World::getDt()
    {
        return m_dt;
    }

    void World::setDt(float dt)
    {
        m_dt = dt;
    }

    void World::updateDynamics(Sphere* sphere)
    {
        Vec3 drag_force{0,0,0};
        drag_force = 0.5f*m_density*sphere->getVelocity()*sphere->getVelocity()*sphere->getDragCoef();
        Vec3 acc{0,0,0};
        acc = m_gravity - drag_force*phys::Vec3::sign(sphere->getVelocity())/sphere->getMass();
        sphere->update(m_dt,acc,m_boundary);
    }

    void World::setBoundary(Boundary *boundary)
    {
        m_boundary = boundary;
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
