#version 330 core

out vec4 FragColor;
in vec4 vertexColor;
uniform vec4 blinkingColor;
uniform bool blinking;

void main()
{
   if (blinking) {
      FragColor = blinkingColor;
   } else {
      FragColor = vertexColor;
   }
}
