
texture2D mTex; //纹理变量
SamplerState TextureSampler //纹理采样器 
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

float2x2 rot2D(float arc){
   float c =cos(arc);
   float s =sin(arc);
   
   return float2x2(c,s,-s,c);
}

float3 hash( float3 p )
{
	p = float3( dot(p,float3(127.1,311.7,321.3)),dot(p,float3(269.5,183.3,301.332)),dot(p,float3(169.5,183.3,411.3)) );
	return -1.0 + 2.0*frac(sin(p)*4302458.545);
}
 
float4 Noise(in float3 x){
    // grid
    float3 p =floor(x);
    float3 w =frac(x);
    
    //quintic interpolant

    float3 u = w*w*w*w*w*6-15*w*w*w*w+10*w*w*w;
    float3 du = 30*w*w*w*w-60*w*w*w+30*w*w;
    
    //gradients
    float3 g1 = hash(p+float3(0,0,0));
    float3 g2 = hash(p+float3(1,0,0));
    float3 g3 = hash(p+float3(0,1,0));
    float3 g4 = hash(p+float3(1,1,0));
    float3 g5 = hash(p+float3(0,0,1));
    float3 g6 = hash(p+float3(1,0,1));
    float3 g7 = hash(p+float3(0,1,1));
    float3 g8 = hash(p+float3(1,1,1));
    
    // projections

    float v1 = dot(g1,w-float3(0,0,0));
    float v2 = dot(g2,w-float3(1,0,0));
    float v3 = dot(g3,w-float3(0,1,0));
    float v4 = dot(g4,w-float3(1,1,0));
    float v5 = dot(g5,w-float3(0,0,1));
    float v6 = dot(g6,w-float3(1,0,1));
    float v7 = dot(g7,w-float3(0,1,1));
    float v8 = dot(g8,w-float3(1,1,1));

    // interpolation
    float k1=v2-v1;
    float k2=v3-v1;
    float k3=v5-v1;
     
    float k4=v1-v2-v5+v6;
    float k5=v1-v2-v3+v4;
    float k6=v1-v3-v5+v7;
    float k7=v8-v7-v6+v5-v4+v3+v2-v1;
    
    float v = v1+ 
              k1*u.x+
              k2*u.y+
              k3*u.z+
              k4*u.x*u.z+
              k5*u.x*u.y+
              k6*u.y*u.z+
              k7*u.x*u.y*u.z;
   
     float3 n = normalize(float3(
         k1+k4*u.z+k5*u.y+k7*u.y*u.z,
         k2+k5*u.x+k6*u.z+k7*u.x*u.z,
         k3+k4*u.x+k6*u.y+k7*u.x*u.y
         )*du);
                          
   return float4(v,n);
}

float fbm(in float2 uv){
    float res =0;
    float ft =0.5;
    float total=0;
   
    float2x2 m = float2x2(0.8,1.6, -0.6, 0.8);
    float2x2 m1 = float2x2(0.8,0.6, -0.6, 0.8);
    for(int i=0;i<4;i++){
        res+=2*Noise(float3(uv+iTime*0.002,uv.x+iTime*0.002)).x;
        total+=ft;
        ft*=0.5;
       
        uv=mul(uv,m);
        m=mul(m,m1);
    }
    
    return res/total;
}

float4 main(PixelShaderInput input) : SV_TARGET
{
	float2 uv = input.tex-float2(0.5,0.5);
	float as = iResolution.x / iResolution.y;
	uv.x *= as;
    uv*=6;
	float time=iTime*0.0001; 
    float f=clamp(fbm(float2(uv.x,uv.y+time)),0.3,1);
   
    float v=0.5/length(uv);
    v*=f;
    
	float3 col= float3(v,v,v);
    return float4(col,1);
}