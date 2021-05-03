#version 400 core

//this should be changable from c++ code
//and because engine loads then as text files -> it should be as simple as finding and replacing a string
//but for now -> it's changed manually
#define MAX_LIGHTS 6

struct PointLight
{
    vec3 Location;

    vec3 Color;

    float Intensity;

    float Reflectivity;

    bool Exists;
};

uniform PointLight pointLights[MAX_LIGHTS];

// Interpolated values from the vertex shaders
in vec2 UV;

in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
//in vec3 LightDirection_cameraspace;

in vec3 normal;

in vec3 vertex;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D textureSampler;

uniform vec3 ambient_light_color;

uniform mat4 view;

uniform float diffuse_intensity;

uniform float diffuse_reflectivity;

uniform vec3 light_pos;

vec3 calculatePointLight(PointLight light,vec3 mat_color, vec3 normal, vec3 eye)
{
     // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( view * vec4(light.Location,1)).xyz;
	vec3 LightDirection_cameraspace =( view * vec4(light.Location,1)).xyz + EyeDirection_cameraspace;

    // Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );

    //this means that this is a filler light
    /*if(!light.Exists)
    {
        return vec3(0,0,0);
    }*/

    // Distance to the light
    float distance = length( light.Location - Position_worldspace);
    // Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
    float cosTheta = clamp( dot(normal,l), 0,1 );

    // Direction in which the triangle reflects the light
    vec3 R = reflect(-l,normal);

    // Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
    float cosAlpha = clamp( dot( eye,R ), 0,1 );
    return mat_color * light.Reflectivity*light.Intensity*light.Color*cosTheta / (distance*distance);
}

void main()
{
   // Distance to the light
	float distance = length( light_pos - Position_worldspace);

    // Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	//vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	//float cosTheta = clamp( dot( n,l ), 0,1 );

    // Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	//vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	//float cosAlpha = clamp( dot( E,R ), 0,1 );
    

    //ambient_light_intensity*ambient_light_reflectivity
    // Output color = color of the texture at the specified UV
    //color = ambient_light_intensity * ambient_light_reflectivity *   texture( textureSampler, UV ).rgb +   texture( textureSampler, UV ).rgb * diffuse_intensity*diffuse_reflectivity*cosTheta / (distance*distance);
    vec3 mat_color =  texture( textureSampler, UV ).rgb;
    vec3 temp = ambient_light_color+mat_color+mat_color;//ambient_light_intensity * ambient_light_reflectivity *   mat_color;
    for(int i = 0 ;i < MAX_LIGHTS;i++)
    {
       temp +=  calculatePointLight(pointLights[i],mat_color,n,E);
    }
    //temp+=pointLights[0].Color*pointLights[0].Intensity;
    color = temp;
}