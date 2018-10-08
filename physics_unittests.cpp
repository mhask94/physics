#include "gtest/gtest.h"
#include "sphere.hpp"
#include "vec3.hpp"

TEST(SphereWith0VelocityAnd0Acceleration,AskedToUpdate_InitialPosition)
{
    float mass{1};
    phys::vec3 init_pos{0,0,0};
    phys::vec3 init_vel{0,0,0};
    phys::Sphere sphere{mass,init_pos,init_vel};
    sphere.update();

    phys::vec3 expected_pos{0,0,0};

    EXPECT_EQ(expected_pos,sphere.getPosition());
}

TEST(SphereWithVelocityAnd0Acceleration,AskedToUpdate_CorrectPosition)
{
    float mass{1};
    phys::vec3 init_pos{0,0,0};
    phys::vec3 init_vel{1,0,0};
    phys::Sphere sphere{mass,init_pos,init_vel};
    sphere.update();

    phys::vec3 expected_pos{0,0,0};
    float dt{sphere.getDt()};
    expected_pos = init_pos + init_vel*dt;

    EXPECT_EQ(expected_pos,sphere.getPosition());

    phys::vec3 init_pos2{-1,0,1};
    phys::vec3 init_vel2{1,-1,0};
    phys::Sphere sphere2{mass,init_pos2,init_vel2};
    sphere2.update();

    phys::vec3 expected_pos2{0,0,0};
    float dt2{sphere2.getDt()};
    expected_pos2 = init_pos2 + init_vel2*dt2;

    EXPECT_EQ(expected_pos2,sphere2.getPosition());
}

TEST(SphereWithGravityAndNoVelocity,AskedToUpdate_UpdatesCorrectly)
{
    float mass{1};
    phys::vec3 init_pos{0,10,0};
    phys::vec3 gravity{0,-9.81,0};
    phys::Sphere sphere{mass,init_pos};
    sphere.setAcceleration(gravity);
    sphere.update();

    phys::vec3 expected_pos{0,0,0};
    phys::vec3 expected_vel{0,0,0};
    float dt{sphere.getDt()};
    expected_vel = gravity*dt;
    expected_pos = init_pos + expected_vel*dt;

    EXPECT_EQ(expected_pos,sphere.getPosition());
}
