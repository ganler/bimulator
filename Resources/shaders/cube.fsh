varying vec2 Tx;
varying vec3 Norm;
varying vec4 frag_pos;


uniform vec3 light_pos;
uniform vec3 view_pos;

void main()
{
    normalize(vec2(1.0,5.0));
    if(frag_pos.x>799.9)
	    gl_FragColor = texture2D(CC_Texture3,vec2(-frag_pos.y/1600.0-0.5,-frag_pos.z/1600.0-0.5));
    else if(frag_pos.x<-799.9)
	    gl_FragColor = texture2D(CC_Texture3,vec2(frag_pos.y/1600.0+0.5,-frag_pos.z/1600.0-0.5));
    else if(frag_pos.y>799.9)
	    gl_FragColor = texture2D(CC_Texture3,vec2(frag_pos.x/1600.0+0.5,-frag_pos.z/1600.0-0.5));
    else if(frag_pos.y<-799.9)
	    gl_FragColor = texture2D(CC_Texture3,vec2(-frag_pos.x/1600.0-0.5,-frag_pos.z/1600.0-0.5));
    else if(frag_pos.z>799.9)
	    gl_FragColor = texture2D(CC_Texture3,vec2(-frag_pos.x/1600.0-0.5,-frag_pos.y/1600.0-0.5));
    else if(frag_pos.z<-799.9)
	    gl_FragColor = texture2D(CC_Texture3,vec2(frag_pos.x/1600.0+0.5,frag_pos.y/1600.0+0.5));
    
    else
    {
    vec3 light_color = vec3(1.0, 1.0, 0.8);
    float ambient_fac = 0.0;
    vec3 ambient = ambient_fac * light_color;

    // Diffuse
    vec3 nNorm = normalize(Norm);
    vec3 light_dir = normalize(light_pos - vec3(frag_pos));
    float diff = 0.5* max(dot(nNorm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    // Specular
    float specular_fac = 0.8;
    if(frag_pos.z < -2.99)
        specular_fac = 0.05;
    vec3 view_dir = normalize(view_pos - vec3(frag_pos));
    vec3 reflect_dir = reflect(-light_dir, nNorm);
    float spec ;
    if(frag_pos.z<-2.9)
        spec=pow(max(dot(view_dir, reflect_dir), 0.0), 8.0);
    else
        spec=pow(max(dot(view_dir, reflect_dir), 0.0), 32.0); // 反射光别太强了
    vec3 specular = specular_fac * spec * light_color;
    vec3 result = (ambient + diffuse + specular)*texture2D(CC_Texture0,Tx).xyz;

    float  shadowDepth = texture2D(CC_Texture2,vec2(gl_FragCoord.x/800.0,-gl_FragCoord.y/600.0)).x;
    gl_FragColor = shadowDepth*vec4(result,1.0)+texture2D(CC_Texture1,vec2(gl_FragCoord.x/800.0,-gl_FragCoord.y/600.0));
    if(frag_pos.z<-2.99)//画球洞
    {
        if((frag_pos.x-125)*(frag_pos.x-125)+(frag_pos.y-65)*(frag_pos.y-65)<64.0)//画球洞
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else if((frag_pos.x-125)*(frag_pos.x-125)+(frag_pos.y+65)*(frag_pos.y+65)<64.0)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else if((frag_pos.x+125)*(frag_pos.x+125)+(frag_pos.y-65)*(frag_pos.y-65)<64.0)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else if((frag_pos.x+125)*(frag_pos.x+125)+(frag_pos.y+65)*(frag_pos.y+65)<64.0)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else if(frag_pos.x*frag_pos.x+(frag_pos.y-65)*(frag_pos.y-65)<64.0)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else if(frag_pos.x*frag_pos.x+(frag_pos.y+65)*(frag_pos.y+65)<64.0)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);   
    } 
}
    

    if(gl_FragCoord.x>=375.0&&gl_FragCoord.x<=425.0&&gl_FragCoord.y<=301.0&&gl_FragCoord.y>=299.0)
	gl_FragColor=vec4(1.0,1.0,0.0,1.0);
    if(gl_FragCoord.x>=399.0&&gl_FragCoord.x<=401.0&&gl_FragCoord.y<=325.0&&gl_FragCoord.y>=275.0)
               gl_FragColor=vec4(1.0,1.0,0.0,1.0);	
    //绘制准星

} 