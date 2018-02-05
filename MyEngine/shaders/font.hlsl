 
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
	
	float3 col=mTex.Sample(TextureSampler,float2(uv.x,1-uv.y)).z;
 	// float3 col=mTex.Sample(TextureSampler,float2(uv.x,1-uv.y)).z;
	// float3 col=mTex.Sample(TextureSampler,float2(uv.x,1-uv.y)).z;
	// float3 col=mTex.Sample(TextureSampler,float2(uv.x,1-uv.y)).z;
	
	col*=4; 
	 
	float alp=col.z; 
	
	return float4(float3(1,1,1),col.z);
}