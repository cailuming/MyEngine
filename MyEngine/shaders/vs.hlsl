// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved
//----------------------------------------------------------------------
cbuffer gBuffer : register(b0)
{
	matrix mat;
	float iTime;
	float iTime1;
	float2 iResolution;
};
struct VertexShaderInput
{
    float3 pos : POSITION;
	float3 norm : NORMAL;
	float2 tex : TEXCOORD;

};

struct VertexShaderOut
{
	float4 pos : SV_POSITION;
	float3 norm : NORMAL;
	float2 tex : TEXCOORD;

};

VertexShaderOut main(VertexShaderInput input)
{ 
	VertexShaderOut outp;
    float4 pos = float4(input.pos, 1.0f);
	//pos = mul(model,pos);
	outp.pos = pos;
	outp.norm = input.norm;
	outp.tex = input.tex;
    return outp;
}
