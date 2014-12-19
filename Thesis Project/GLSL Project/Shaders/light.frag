uniform sampler2D texture;
uniform vec2 lightPos;
uniform float lightRadius;
uniform vec4 lightColor;
 
void main() {	
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);	
	float dist = length(lightPos - gl_FragCoord.xy);			
	float lightIntensity = (1.0 - (dist / lightRadius));
	if(dist >= lightRadius)	lightIntensity = 0.0;		
    gl_FragColor = pixel * lightIntensity * lightColor;
}

