#type vertex
#version 460 core
layout(location = 0) in vec2 aWorldPosition; // the position variable has attribute position 0
layout(location = 1) in vec2 aLocalPosition; //the color of the vector
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTilingFactor;
layout(location = 4) in int aTexID;
layout(location = 5) in vec4 aColor;
layout(location = 6) in float aThickness;
layout(location = 7) in float aFade;
layout(location = 8) in int aProjectionMode;
layout(location = 9) in int aCoreID;

// camera variables
uniform mat4 uPerspective;
uniform mat4 uOrthographic;
uniform mat4 uView;

struct VertexOutput
{
    vec2 LocalPosition;
    vec2 TexCoord;
    float TilingFactor;
    vec4 Color;
    float Thickness;
    float Fade;
};
 
layout(location = 0) out VertexOutput Output;
layout(location = 6) out flat int TexID;
layout(location = 7) out flat int CoreID;

void main()
{
    Output.LocalPosition = aLocalPosition;
    Output.TexCoord = aTexCoord;
    Output.TilingFactor = aTilingFactor;
    Output.Color = aColor;
    Output.Thickness = aThickness;
    Output.Fade = aFade;
    TexID = aTexID;
    CoreID = aCoreID;

    vec4 position;
    switch (aProjectionMode) {
        case 0:
            position = uPerspective * uView * vec4(aWorldPosition, 0.0f, 1.0f);
            break;
        case 1:
            position = uOrthographic * uView * vec4(aWorldPosition, 0.0f, 1.0f);
            break;
        case 2:
            position = vec4(aWorldPosition, 0.0f, 1.0f);
        default:
            break;
    }
    gl_Position = position;
}


#type fragment
#version 460 core

// attachment 0 and 1
layout(location = 0) out vec4 display;
layout(location = 1) out int objectID;

struct VertexOutput
{
    vec2 LocalPosition;
    vec2 TexCoord;
    float TilingFactor;
    vec4 Color;
    float Thickness;
    float Fade;
};

layout(location = 0) in VertexOutput Input;
layout(location = 6) in flat int TexID;
layout(location = 7) in flat int CoreID;

layout(binding = 0) uniform sampler2D uTexture[32];

void main()
{
    // Calculate distance and fill circle with white
    float distance = 1.0 - length(Input.LocalPosition);
    float circle = smoothstep(0.0, Input.Fade, distance);
    circle *= smoothstep(Input.Thickness + Input.Fade, Input.Thickness, distance);
    
    if (circle == 0.0)
        discard;
    
    //Set output color
    display = Input.Color;

    if (TexID >= 0) {
        display *= texture(uTexture[TexID], Input.TexCoord * Input.TilingFactor);
    }

    display.a *= circle;
    
    objectID = CoreID;
}