#ifndef PLANET_H_
#define PLANET_H_

#include <glm/glm.hpp>

const float G = (float)6.6700E-11;

struct Planet {
    // Add a specific force to our total force vector.
    //	 This simply encapsulates .push_back(val) and
    //	 makes the calling look more clear and centered
    //	 around the math(and not what is going on)
    void addForce(glm::vec3 const& m_force)
    {
        force.push_back(m_force);
    }

    // Return the total force summed up in the vector.
    //	 The use of getting the total force would be to
    //	 find the direction and end force of each planet
    glm::vec3 getTotalForce() const
    {
        glm::vec3 total(0.0, 0.0, 0.0);
        for(auto i = 0; i < force.size(); i++)
            total += force[i];
        return total;
    }

    // Clear all elements inside the force vector, essentially
    //	 stopping any planet currently in motion
    void clearForce()
    {
        force.clear();
    }

    glm::vec3 pos, speed;               // position and speed of the planet
    std::vector<glm::vec3> force;       // forces acting on planet
    unsigned char r,g,b,a;              // color of our planet
    float size;                         // size of our planet
    float mass;                         // how heavy our planet is (proportional to size)
    float cameradistance;               // distance planet is from camera
};


#endif
