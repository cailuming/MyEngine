
float2x2 rot2D(float arc){
   float c =cos(arc);
   float s =sin(arc);
   
   return float2x2(c,s,-s,c);
}
float2 complex2(float2 a, float2 b){

    return float2(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
} 

void Julia(inout float3 col,float2 uv){
   float2 z =uv;
  
   float2 c =float2(-0.12+0.8*cos(iTime*0.0001),0.1+0.5*sin(iTime*0.0001));
   float v=0;
    
   z.xy=mul(z.xy,rot2D(iTime*0.001));
   for(int i=0;i<40;i++){
      z=complex2(z,z)+c;
   }

   v = sqrt(z.x*z.x+z.y*z.y);
   float arc=  atan2(uv.y,uv.x);
   if(abs(v)<1){	  
      z*=(3-clamp(iTime*0.0000005,0,2.9));
   
      col=float3(cos(z.y),sin(z.x),uv.x);
   }else{
	  col=float3(0.2,0.3,length(uv-z+arc));
   }
}

float4 main(PixelShaderInput input) : SV_TARGET
{
	float2 uv = input.tex-float2(0.5,0.5);
	float as = iResolution.x / iResolution.y;
	uv.x *= as;
	float time=iTime*0.001; 
	float3 col=0;
    Julia(col,uv);
    return float4(col,1);
}