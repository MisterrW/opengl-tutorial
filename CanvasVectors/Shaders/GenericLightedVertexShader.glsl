#version 430 core
layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 vertex_normal_modelspace;
 
uniform mat4 projection_matrix, view_matrix, model_matrix;
// uniform vec3 rotation;
// uniform vec3 LightPosition_worldspace;

out vec3 normal_cameraspace;
out vec3 lightDirection_cameraspace;
 
void main()
{
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position_modelspace, 1);

    vec3 LightPosition_worldspace = vec3(400, 500, 800);

    // Position of the vertex, in worldspace : M * position
    vec3 Position_worldspace = (model_matrix * vec4(vertex_position_modelspace,1)).xyz;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).

    vec3 vertexPosition_cameraspace = ( view_matrix * model_matrix * vec4(vertex_position_modelspace,1)).xyz;

    vec3 EyeDirection_cameraspace = vec3(0,0,0) + vertexPosition_cameraspace;

    // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
    vec3 LightPosition_cameraspace = ( view_matrix * vec4(LightPosition_worldspace,1)).xyz;
    // vec3 LightPosition_cameraspace = vec3(0, 0, 0);
    lightDirection_cameraspace = LightPosition_cameraspace - EyeDirection_cameraspace;

    // Normal of the the vertex, in camera space
    normal_cameraspace = ( view_matrix * model_matrix * vec4(vertex_normal_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
}