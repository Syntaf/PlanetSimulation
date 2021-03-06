#version 330
// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 squareVertices;
layout(location = 1) in vec4 xyzs; // Position of the center of the particule and size of the square
layout(location = 2) in vec4 color; // Position of the center of the particule and size of the square

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 planetcolor;

// Values that stay constant for the whole mesh.
uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;
uniform mat4 VP; // Model-View-Projection matrix, but without the Model (the position is in BillboardPos; the orientation depends on the camera)

void main()
{
    float planetSize = xyzs.w; // because we encoded it this way.
    vec3 planetCenter_wordspace = xyzs.xyz;
    
    vec3 vertexPosition_worldspace = 
        planetCenter_wordspace
        + CameraRight_worldspace * squareVertices.x * planetSize
        + CameraUp_worldspace * squareVertices.y * planetSize;

    // Output position of the vertex
    gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);

    // UV of the vertex. No special space for this one.
    UV = squareVertices.xy + vec2(0.5, 0.5);
    planetcolor = color;
}
