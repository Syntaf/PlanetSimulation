#ifndef PLANET_H_
#define PLANET_H_

#include <glm/glm.hpp>

const float G = (float)6.6700E-11;

struct Planet {
	glm::vec3 pos, speed;
	std::vector<glm::vec3> force;
	unsigned char r,g,b,a;
	float size;
	float mass;
	float cameradistance;

	void addForce(glm::vec3 const& m_force)
	{
		force.push_back(m_force);
	}

	glm::vec3 getTotalForce() const
	{
		glm::vec3 total(0.0, 0.0, 0.0);
		for(auto i = 0; i < force.size(); i++)
			total += force[i];
		return total;
	}

	void clearForce()
	{
		force.clear();
	}

	/*
    float gravitationalForce(Planet otherObject)
	{
		//F = G m1*m2 / r^2
		// G = gravitational constant | G = 6.67300 x 10^-11
		//m1 = mass 1(kg)
		//m2 = mass 2(kg)
		//r = distance between the centers of the masses

		//find the distance between the x y and z pairs
		float x_dist = x - otherObject.x;
		float y_dist = y - otherObject.y;

		//calculate distance between the two objects r^2 = x^2 + y^2
		float r_Squared = ((x_dist * x_dist) + (y_dist * y_dist));

		return G * (((mass) * otherObject.mass) / r_Squared); //returns force in newtons
	}
	*/
};


#endif
