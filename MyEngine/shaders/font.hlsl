 
texture2D mTex; //纹理变量
SamplerState TextureSampler //纹理采样器 
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	 
	float2 uv =input.tex;
	  
	float4 col=0;
	
    float atlasX = 0.0012;
    float atlasY = 0.1;	
    col= mTex.Sample(TextureSampler,float2(uv.x,1-uv.y)).w;
	 
	col.xyz=1;
	 
	return float4(col.xyz,col.w);
}