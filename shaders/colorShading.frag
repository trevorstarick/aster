#version 330

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

//uniform float time;
uniform sampler2D samplerTexture;

void main() {

    vec4 textureColor = texture(samplerTexture, fragmentUV);
    color = textureColor;


}
