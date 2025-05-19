#version 460 core
layout (location = 0) in vec4 color;
layout (location = 1) in vec3 normal;

out vec4 FragColor;

vec3 lightPos = vec3(4.0, 5.0, -3.0);
vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main() {
  float lightAngle = max(dot(normalize(normal), normalize(lightPos)), 0.0);
  FragColor = color * vec4((0.3 + 0.7 * lightAngle) * lightColor, 1.0);
}
