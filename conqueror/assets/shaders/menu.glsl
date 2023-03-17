#type vertex
#version 330 core

layout (location = 0) in vec2 aPos; // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; //the color of the vector
layout (location = 2) in vec2 aTexCoord; //the coords of the texture
layout (location = 3) in float aTexID; //The slot of the texture
layout (location = 4) in float aCoreID;

// declare vertex variables that are being piped to fragment
out vec4 fColor;
out vec2 fTexCoord;
flat out float fTexID;
flat out float fCoreID;

void main()
{
    // the least 1 needs an explanation
    gl_Position = vec4(aPos, 0, 1); // adjust the gl_Position with the help of 'u' Factors
    fColor = aColor; // set the output variable to a dark-red color
    fTexCoord = aTexCoord; // set texCoord from the array within the code
    fTexID = aTexID; // pipe texID to fragment
    fCoreID = aCoreID;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 display;
layout(location = 1) out int objectID;


in vec4 fColor; // get color from vertex
in vec2 fTexCoord; // get texCoord from vertex
flat in float fTexID; // get texID from vertex
flat in float fCoreID;


uniform sampler2D uTexture[8];

void main()
{
    if (int(fTexID) >= 0) {
        display = texture(uTexture[int(fTexID)], fTexCoord);
    }
    else {
        // if there is no texture, display the colors
        display = fColor;
    }
    objectID = int(fCoreID);
}