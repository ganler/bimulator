void main()
{
	gl_FragColor = texture2D(CC_Texture0,vec2(gl_FragCoord.x/800.0,gl_FragCoord.y/600.0));
    	if(gl_FragCoord.x>=375&&gl_FragCoord.x<=425&&gl_FragCoord.y<=301&&gl_FragCoord.y>=299)
		gl_FragColor=vec4(1.0,1.0,0.0,1.0);
    	if(gl_FragCoord.x>=399&&gl_FragCoord.x<=401&&gl_FragCoord.y<=325&&gl_FragCoord.y>=275)
               	gl_FragColor=vec4(1.0,1.0,0.0,1.0);	

	gl_FragColor=vec4(1.0,1.0,0.0,1.0);	
}