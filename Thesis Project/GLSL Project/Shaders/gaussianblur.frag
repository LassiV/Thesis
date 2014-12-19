uniform sampler2D texture;
uniform vec2 offsetFactor;
void main()
{
	vec2 texCoord = gl_TexCoord[0].xy;
	vec4 color = vec4(0.0);
	color += texture2D(texture, texCoord - 4.0 * offsetFactor) * 0.0162162162;
	color += texture2D(texture, texCoord - 3.0 * offsetFactor) * 0.0540540541;
	color += texture2D(texture, texCoord - 2.0 * offsetFactor) * 0.1216216216;
	color += texture2D(texture, texCoord - offsetFactor) * 0.1945945946;
	color += texture2D(texture, texCoord) * 0.2270270270;
	color += texture2D(texture, texCoord + offsetFactor) * 0.1945945946;
	color += texture2D(texture, texCoord + 2.0 * offsetFactor) * 0.1216216216;
	color += texture2D(texture, texCoord + 3.0 * offsetFactor) * 0.0540540541;
	color += texture2D(texture, texCoord + 4.0 * offsetFactor) * 0.0162162162;
	gl_FragColor = color;
}