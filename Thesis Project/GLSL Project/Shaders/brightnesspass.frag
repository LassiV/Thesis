uniform sampler2D texture; //Source texture for the brightness pass
const float threshold = 0.7; //Threshold to limit the 
const float factor = 2.0;
void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
	//RGB color values added together and divided by 765 to produce approximate total brightness value
	//765 = 255*3 -> total value of colors divided by this to get a value between 0 and 1.
	float luminance = (pixel.r + pixel.g + pixel.b)/(765.0); 
	pixel *= clamp(luminance - threshold, 0.0, threshold) * factor;
	gl_FragColor = pixel;
}