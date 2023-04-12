#type vertex
#version 450 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in int aProjectionMode;
layout(location = 4) in int aCoreID;
layout(location = 5) in int aUIID;

// camera variables
uniform mat4 uPerspective;
uniform mat4 uOrthographic;
uniform mat4 uView;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
};

layout (location = 0) out VertexOutput Output;
layout (location = 2) out flat int coreID;

void main()
{
	Output.Color = aColor;
	Output.TexCoord = aTexCoord;
	coreID = aCoreID;

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
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int oCoreID;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
};

layout (location = 0) in VertexOutput Input;
layout (location = 2) in flat int coreID;

layout (binding = 0) uniform sampler2D u_FontAtlas;

float screenPxRange() {
	const float pxRange = 2.0; // set to distance field's pixel range
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(Input.TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

//uniform sampler2D uIDAttachment;

void main()
{
	vec4 texColor = Input.Color * texture(u_FontAtlas, Input.TexCoord);

	vec3 msd = texture(u_FontAtlas, Input.TexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
	if (opacity == 0.0)
		discard;

	vec4 bgColor = vec4(0.0);
    o_Color = mix(bgColor, Input.Color, opacity);
	if (o_Color.a == 0.0)
		discard;

	oCoreID = coreID;
}