#version 400 core

layout(location = 0) in vec3 vertexPosition_modelspace;

layout(location = 1) in vec2 vertexUV;

layout(location = 2) in vec3 normals;

out vec3 vertex;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

out vec3 normal;

out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
//out vec3 LightDirection_cameraspace;


uniform mat4 mvp;

uniform mat4 model;

uniform mat4 view;

uniform vec3 location;

uniform vec3 light_pos;

void main()
{
    gl_Position = (mvp * vec4(vertexPosition_modelspace,1))  ;

    // Position of the vertex, in worldspace : M * position
    Position_worldspace = (model * vec4(vertexPosition_modelspace,1)).xyz;

    // Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( view * model * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

   
	
	// Normal of the the vertex, in camera space
	Normal_cameraspace = ( view * model * vec4(normals,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

    UV = vertexUV;

    normal = normals;

    vertex = vertexPosition_modelspace;
}