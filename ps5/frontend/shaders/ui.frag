#version 450
// PS5 port frontend: signed-distance-field glyphs (params.w = 0: x = edge, y = softness in field
// units) and rounded rectangles (params.w = 1: uv = pixels from the centre, x/y = half size,
// z = corner radius, softness one pixel).
// Copyright (C) 2026 Spyros
// SPDX-License-Identifier: GPL-3.0-or-later

layout(set = 1, binding = 0) uniform sampler2D u_atlas;

layout(location = 0) in vec2 v_uv;
layout(location = 1) in vec4 v_color;
layout(location = 2) in vec4 v_params;
layout(location = 0) out vec4 o_color;

void main()
{
	// Sampled outside the branch on purpose: the PS5 shader compiler (psbc) moves the coordinate of
	// a sample inside divergent control flow to the top and builds it from the input's first
	// component twice, so the atlas was read at (u, u) and every glyph came out as bars (vk-285-41).
	vec4 sampled = texture(u_atlas, v_uv);
    // (AI-assisted) Nine unconditional samples avoid divergent-coordinate compiler issues.
    vec2 pixel=v_uv*vec2(160.0,144.0);vec2 base=(floor(pixel)+0.5)/vec2(160.0,144.0);vec2 step=1.0/vec2(160.0,144.0);
    vec3 A=texture(u_atlas,base+step*vec2(-1,-1)).rgb;
    vec3 B=texture(u_atlas,base+step*vec2(0,-1)).rgb;
    vec3 C=texture(u_atlas,base+step*vec2(1,-1)).rgb;
    vec3 D=texture(u_atlas,base+step*vec2(-1,0)).rgb;
    vec3 E=texture(u_atlas,base).rgb;
    vec3 F=texture(u_atlas,base+step*vec2(1,0)).rgb;
    vec3 G=texture(u_atlas,base+step*vec2(-1,1)).rgb;
    vec3 H=texture(u_atlas,base+step*vec2(0,1)).rgb;
    vec3 I=texture(u_atlas,base+step*vec2(1,1)).rgb;
    if(v_params.w>5.5){o_color=sampled*v_color;return;}
    if(v_params.w>1.5){
      vec3 color=E;vec2 f=fract(pixel);
      bool split=distance(B,H)>0.08&&distance(D,F)>0.08;
      if(v_params.w>2.5&&split){
        float tl=distance(D,B)<0.04&&distance(E,A)>0.04?1.0-smoothstep(0.45,0.65,f.x+f.y):0.0;
        float tr=distance(B,F)<0.04&&distance(E,C)>0.04?1.0-smoothstep(0.45,0.65,1.0-f.x+f.y):0.0;
        float bl=distance(D,H)<0.04&&distance(E,G)>0.04?1.0-smoothstep(0.45,0.65,f.x+1.0-f.y):0.0;
        float br=distance(H,F)<0.04&&distance(E,I)>0.04?1.0-smoothstep(0.45,0.65,2.0-f.x-f.y):0.0;
        color=mix(color,(D+B)*0.5,tl);color=mix(color,(B+F)*0.5,tr);color=mix(color,(D+H)*0.5,bl);color=mix(color,(H+F)*0.5,br);
      }
      if(v_params.w>3.5){
        vec3 average=(B+D+F+H)*0.25;
        float edge=clamp(length(E-average)*4.0,0.0,1.0);
        color+=clamp(E-average,vec3(-0.10),vec3(0.10))*v_params.x*0.35*(1.0-edge);
        float luma=dot(color,vec3(0.2126,0.7152,0.0722));color=mix(vec3(luma),color,1.0+v_params.y);
        color=(color-0.5)*v_params.z+0.5;
        if(v_params.w>4.5)color=mix(color,pow(max(color,vec3(0)),vec3(0.92))*vec3(1.0,0.98,0.96),0.25);
      }
      o_color=vec4(clamp(color,0.0,1.0),1.0)*v_color;return;
    }
	float field = sampled.r;
	float a;
	if (v_params.w < 0.5)
	{
		a = smoothstep(v_params.x - v_params.y, v_params.x + v_params.y, field);
	}
	else
	{
		vec2 q = abs(v_uv) - v_params.xy + vec2(v_params.z);
		float d = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0) - v_params.z;
		a = 1.0 - smoothstep(-0.75, 0.75, d);
	}
	o_color = vec4(v_color.rgb, v_color.a * a);
}
