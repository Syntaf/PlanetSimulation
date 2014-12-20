#ifndef PLANETMANAGER_H_
#define PLANETMANAGER_H_

#include "planet.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class PlanetManager{
    public:
        // Simple assignment and bind operations are done inside constructor
        //	 The position and color data arrays are allocated for the buffers
        //	 and our vertex array is generated and binded.
        PlanetManager(int maxplanets=20);
        ~PlanetManager();

        // Initializes and sets all values of each planet before the first render
        //	 is procd. The planets will currently arrange in a square shape, but
        //	 should be random shortly.
        void initPlanets();

        // Use external common function to load a DDS texture file and bind 
        //	 the texture variable accordingly
        bool loadTexture(const std::string& filename);

        // Generate all OpenGL buffers before the first render is called, this
        //	 function should only be called once and from then on, the
        //	 updateGLBuffers() function is used to place new data inside the
        //	 buffers.
        //	 TODO: remove billboard buffer, we will not be moving around anyways
        void genGLBuffers();

        // Fill the dynamically allocated arrays with the new position, size and
        //	 color calculated in the updatePlanets function. uses and index and 
        //	 current planet count to properly place data in the correct index
        void fillPlanetGLBuffers(const int& index, const int& planet_count);

        // Function used while the program is active, similar to the genGLBuffers
        //	 but instead of generating the buffers, it updates the data inside the
        //	 buffer.
        void updateGLBuffers();

        // Activate OpenGL texture for drawing to screen
        void activateTexture();

        // The physics and computation heavy portion of the program, calculates
        //	 the new position and other factors that allow each planet to be
        //	 realistically simulated. accepts the current matrices for context
        //	 and updates each planet individually.
        void updatePlanets(const float& delta, glm::mat4& projection_matrix,
                glm::mat4& view_matrix);

        // OpenGL side of the manager, draws the planets with OpenGL and awaits
        //	 SFML's call to display() in the app's run loop.
        void drawPlanets();

    private:
        std::vector<Planet> d_planet_container;         // holds all active, and inactive,
                                                        // planets.

        GLuint d_vertex_array_id;                       // our one vertex array ID for drawing
        GLuint d_texture_id;                            // holds our texture(s)
        GLuint d_billboard_vertex_buffer;               // TODO remove?
        GLuint d_planet_position_buffer;                // the position buffer used by OpenGL
        GLuint d_planet_color_buffer;                   // the color buffer used by OpenGL
        
        GLuint d_texture;                               // location of our texture(not id)

        GLfloat* g_planet_position_size_data;           // holds all position data for buffers
        GLubyte* g_planet_color_data;                   // holds all color data for buffers

        static const GLfloat g_vertex_buffer_data[];    // simple vertex buffer data

        //custom 'constants'
        int d_MAXPLANETS;                               // program 'constants' e.g. they are
                                                        // constant in respect to the universe
                                                        // but can be changed by the user.
};

#endif