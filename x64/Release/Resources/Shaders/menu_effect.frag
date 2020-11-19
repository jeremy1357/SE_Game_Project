#version 330 core
in vec2 fragment_position;
//in vec2 fragment_uv;
out vec4 output_color;

uniform float time;
//uniform vec2 mouse;
uniform vec2 resolution;


void main()
{
	vec2 p = ( fragment_position.xy / resolution.xy ) * 2.0 - 1.0;
	
	vec3 c = vec3( 0.0 );
	
	float amplitude = 0.10; 
	float glowT = sin(time) * 0.5 + 0.5;
	float glowFactor = mix( 0.15, 0.35, glowT );
	c += vec3(0.02, 0.03, 0.13) * ( glowFactor * abs( 0.5 / sin(p.x + sin( p.y + time ) * amplitude ) ));
	c += vec3(0.02, 0.10, 0.03) * ( glowFactor * abs( 0.23 / sin(p.x + sin( p.y + time+1.00 ) * amplitude+0.1 ) ));

	output_color = vec4(c, 1.0);
}