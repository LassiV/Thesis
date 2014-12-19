uniform sampler2D texture;
const float Threshold = 0.55;
const float Factor = 2.0;
void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	float luminance = pixel.r * 0.2126 + pixel.g * 0.7152 + pixel.b * 0.0722;
	//float luminance = (pixel.r + pixel.g + pixel.b)/(3.0); 
	pixel *= clamp(luminance - Threshold, 0.0, 1.0) * Factor;
	gl_FragColor = pixel;
}

