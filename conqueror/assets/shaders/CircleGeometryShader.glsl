#type vertex
#version 460 core
layout(location = 0) in vec2 aWorldPosition; // the position variable has attribute position 0
layout(location = 1) in vec2 aLocalPosition; //the color of the vector
layout(location = 2) in vec4 aColor;
layout(location = 3) in float aThickness;
layout(location = 4) in float aFade;
layout(location = 5) in int aCoreID;

// camera variables
uniform mat4 uProjection;
uniform mat4 uView;

struct VertexOutput
{
    vec2 LocalPosition;
    vec4 Color;
    float Thickness;
    float Fade;
};
 
layout(location = 0) out VertexOutput Output;
layout(location = 3) out flat int CoreID;

void main()
{
    Output.LocalPosition = aLocalPosition;
    Output.Color = aColor;
    Output.Thickness = aThickness;
    Output.Fade = aFade;

    CoreID = aCoreID;
    gl_Position = uProjection * uView * vec4(aWorldPosition, 0.0f, 1.0f); // adjust gl_Position with the help of 'u' Factors
}


#type fragment
#version 460 core

// attachment 0 and 1
layout(location = 0) out vec4 display;
layout(location = 1) out int objectID;

struct VertexOutput
{
    vec2 LocalPosition;
    vec4 Color;
    float Thickness;
    float Fade;
};

layout(location = 0) in VertexOutput Input;
layout(location = 4) in flat int CoreID;


void main()
{
    float distance = 1.0 - length(Input.LocalPosition);
    vec3 color = vec3(smoothstep(0.0, Input.Fade, distance));
    color *= vec3(smoothstep(Input.Thickness + Input.Fade, Input.Thickness, distance));

    display = Input.Color;
    display.rgb *= color;
    
    objectID = CoreID;
}