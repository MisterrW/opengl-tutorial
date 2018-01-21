#version 430 core

layout(location = 0) out vec4 out_color;
 
// in vec4 color;
in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;


void main()
{
  float distance = length(lightDirection_cameraspace);
  vec3 n = normalize( normal_cameraspace );
  vec3 l = normalize( lightDirection_cameraspace );
  float cosTheta = clamp(dot( n, l), 0, 1);
  vec4 LightColor = vec4(0.2, 0.4, 0.7, 1);
  vec4 MaterialDiffuseColor = vec4(1, 1, 1, 1);
  float LightPower = 60000000;

  // out_color = MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance);
  // out_color = LightColor * LightPower * cosTheta / (distance*distance);
  vec4 color = LightColor * LightPower * cosTheta / (distance * distance);
  if (color.x > 1.0) {
      color.x = 1.0;
  }
  if (color.y > 1.0) {
      color.y = 1.0;
  }
  if (color.z > 1.0) {
      color.z = 1.0;
  }
  if (color.w > 1.0) {
      color.w = 1.0;
  }
  out_color = color;
  // out_color = LightColor * LightPower * cosTheta;
  // out_color = vec4(1, 0, 1, 1);
}