
texture2D mTex; //纹理变量
SamplerState TextureSampler //纹理采样器 
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

#define MAXIT 100
 
 
float2x2 rot2D(float arc){
   float c =cos(arc);
   float s =sin(arc);
   
   return float2x2(c,s,-s,c);
}

float2 IPower2(float2 a,float2 b){
    
  return float2(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
 
   
void Julia(float2 uv,inout float3 col){
    float2 z =uv;
    float t1 =iTime*0.05;
    
    float2 c =float2(-0.044*abs(cos(t1)),0.69*abs(sin(t1)));
    float v =0.;
    
    for(int i=0;i<MAXIT;i++){
        z = IPower2(z,z)+c; 
        if(dot(z,z)>2.0){
            v=abs(sin(iTime*4.+20.*dot(z,uv)));
            
            break;
        }
        
    }
    
    float r =v*0.8;
    float g =cos(length(z)-v*0.5)*clamp(dot(z,z),0.5,2.);
    float b =0.1;
   
    float arc = atan2(z.y,z.x+1e-15);
   
    float v1 = 0.4/(length(uv-z));
    
    v1=pow(v1,2.5);
    
    col+=float3(r,g,b)*v1;
}

float4 main(PixelShaderInput input) : SV_TARGET
{
	float2 uv = input.tex-float2(0.5,0.5);
	float as = iResolution.x / iResolution.y;
	uv.x *= as;
	
	uv=mul(uv.xy,rot2D(iTime*0.05));
	float c =1.9*abs(cos(iTime*0.05));
	uv*=c;
    uv.x-=0.4*sin(c);
	
	float time=iTime*0.001; 
	float3 col=0;
    Julia(uv,col);
	col = sqrt(col);
    return float4(col,1);
}
 
