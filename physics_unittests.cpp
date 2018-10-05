#include "gtest/gtest.h"
#include "sphere.hpp"
#include "vec3.hpp"

TEST(SphereWithInitialVelocity,AskedToUpdate_CorrectPosition)
{
    phys::vec3 position{0,0,0};
    phys::vec3 velocity{0,0,0};

    phys::Sphere sphere{position,velocity};
    sphere.update();

    EXPECT_EQ(vec3{0,0,0},sphere.getPosition());
}
