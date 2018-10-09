#include "world.hpp"
#include <vector>
#include "sphere.hpp"

namespace phys
{
    World::World()
    {
    }

    World::World(vec3 gravity, float density):
        m_gravity{gravity},
        m_density{density}
    {
    }

    World::~World()
    {
    }

    vec3 World::getGravity() const
    {
        return m_gravity;
    }

    void World::setGravity(const vec3 &gravity)
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
            m_spheres[i]->update(m_dt,m_gravity);
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
        vec3 drag_force{0,0,0};
        drag_force = 0.5f*m_density*sphere->getVelocity()*sphere->getVelocity()*sphere->getDragCoef();
        vec3 acc{0,0,0};
        acc = m_gravity + drag_force;
        sphere->update(m_dt,acc);
    }
}
