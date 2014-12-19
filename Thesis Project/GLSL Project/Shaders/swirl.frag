// Scene buffer
uniform sampler2D texture; 

// Currently not used in this demo!
uniform float time = 0.0; 

// GeeXLab built-in uniform, width of
// the current render target
uniform float rt_width; 
// GeeXLab built-in uniform, height of
// the current render target
uniform float rt_height; 

// Swirl effect parameters
uniform float radius = 200.0;
uniform float angle = 0.8;
uniform vec2 center = vec2(400.0, 300.0);

vec4 PostFX(sampler2D tex, vec2 uv, float time)
{
  vec2 texSize = vec2(rt_width, rt_height);
  vec2 tc = uv * texSize;
  tc -= center;
  float dist = length(tc);
  if (dist < radius) 
  {
    float percent = (radius - dist) / radius;
    float theta = percent * percent * angle * 8.0;
    float s = sin(theta);
    float c = cos(theta);
    tc = vec2(dot(tc, vec2(c, -s)), dot(tc, vec2(s, c)));
  }
  tc += center;
  vec3 color = texture2D(texture, tc / texSize).rgb;
  return vec4(color, 1.0);
}

void main (void)
{
  vec2 uv = gl_TexCoord[0].st;
  gl_FragColor = PostFX(texture, uv, time);
}