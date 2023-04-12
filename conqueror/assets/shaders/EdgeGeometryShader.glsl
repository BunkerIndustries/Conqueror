#type vertex
#version 460 core
layout(location = 0) in vec2 aPos; // the position variable has attribute position 0
layout(location = 1) in vec4 aColor; //the color of the vector
layout(location = 2) in vec2 aTexCoord; //the coords of the texture
layout(location = 3) in float aTilingFactor;
layout(location = 4) in int aTexID; //The slot of the texture
layout(location = 5) in int aProjectionMode;
layout(location = 6) in int aCoreID;
layout(location = 7) in int aUIID;

// camera variables
uniform mat4 uPerspective;
uniform mat4 uOrthographic;
uniform mat4 uView;

struct VertexOutput
{
    vec4 Color;
    vec2 TexCoord;
    float TilingFactor;
};
 
layout(location = 0) out VertexOutput Output;
layout(location = 3) out flat int TexID;
layout(location = 4) out flat int CoreID;

void main()
{
    Output.Color = aColor;
    Output.TexCoord = aTexCoord;
    Output.TilingFactor = aTilingFactor;
    TexID = aTexID;
    CoreID = aCoreID;

    vec4 position;
    switch(aProjectionMode) {
        case 0: 
            position = uPerspective * uView * vec4(aPos, 0.0f, 1.0f);
            break;
        case 1:
            position = uOrthographic * uView * vec4(aPos, 0.0f, 1.0f);
            break;
        case 2:
            position = vec4(aPos, 0.0f, 1.0f);
        default:
            break;   
    }
    gl_Position = position;

}


#type fragment
#version 460 core

layout(location = 0) out vec4 display;
layout(location = 1) out int objectID;



struct VertexOutput
{
    vec4 Color;
    vec2 TexCoord;
    float TilingFactor;
};

layout(location = 0) in VertexOutput Input;
layout(location = 3) in flat int TexID;
layout(location = 4) in flat int CoreID;

uniform sampler2D uTexture[31];
//uniform usampler2D uIDAttachment;
//uniform vec2 screenSize;

void main()
{
    vec4 color = Input.Color;
    if (TexID >= 0)
        color *= texture(uTexture[TexID], Input.TexCoord * Input.TilingFactor);
    
    if (color.a == 0.0)
        discard;
    
    display = color;
    objectID = CoreID;
}