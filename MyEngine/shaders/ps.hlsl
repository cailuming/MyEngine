 
// cbuffer gBuffer : register(b0)
// {
// 	matrix mat;
// 	float iTime;
// 	float iTime1;
// 	float2 iResolution;
// };


// struct PixelShaderInput
// {
// 	float4 pos : SV_POSITION;
// 	float3 norm : NORMAL;
// 	float2 tex : TEXCOORD;
// };


#define PI 3.1415926
#define FAR 64

struct Ray {
	float3 o;
	float3 d;
};

float2 obj(float3 p,float3 c) {
	p -= c;
	
	return float2(length(p)-1,0);
}

float2 plane(float3 p, float3 c) {
	p -= c;
	return float2(p.y+1+0.2*sin(0.5*p.z*p.x), 1);
}

void cmp(float2 a,inout float2 r) {
	r=r.x > a.x ? a : r;
}

float2 map(float3 p) {
	float2 ref = float2(1,0);
	cmp(obj(p,float3(0,0,0)),ref);
	cmp(plane(p, float3(0, 0, 0)), ref);
	return ref;
}

float2 rayHit(Ray r) {
	float2 h = float2(0,0);
	float t = 0;

	for (int i = 0; i < FAR;i++) {
		h = map(r.o+t*r.d);
		if (h.x<=0.0005|| t>=60) {
			break;
		}
		t += h.x;
	}
	return float2(t,h.y);
}

float shadow(float3 lp,float3 ld,float mint,float maxt,float k){
    float h=0;
	float t=0;
	float res=1;
	for(int i=0;i<64;i++){
        h=map(lp+t*ld).x;
		t+=h;
        res=min(res,k*h/t);
		if(h<0.0001||t<mint||t>maxt){
			return 0;
		}
	}
    return res;
}
float3 norm(float3 p,float t) {
	float m = map(p).x;
	float2 dir = float2(0,1)*t*0.01;
	return -normalize(float3(m - map(p + dir.yxx).x,m - map(p + dir.xyx).x,m - map(p + dir.xxy).x));
}

void doLight(inout float3 col,float3 p,float3 lp,float t) {
	float3 n = norm(p,t);
	float3 ld = normalize(lp-p);
	float nl = clamp(dot(n,ld),0,1);
	float sl=  shadow(lp,ld,0.0001,length(lp-p)*0.95,128);
	nl*=sl;
	col = float3(nl,nl,nl);
}

void setCamera(inout Ray r,float3 pos,float3 tar,float2 uv) {
	float3 look = normalize(tar);
	float3 right = normalize(cross(float3(0,1,0),look));
	float3 up = normalize(cross(look,right));
	r.o = pos;
	r.d = normalize(uv.x*right + uv.y*up + 0.4*look);
}

void textureMap(inout float3 col,float3 p,int id) {
	float v = 0;
	switch (id) {
	case 0:
		 
		break;
	case 1:
		float arc = atan2(p.z,p.x);
		v = cos(5.*arc+length(p));
		col *= float3(v,v,0);
		
		break;
	}
}

void fog(inout float3 col,float3 ro,float3 rd,float t,float3 lp) {
	float a = 0.2;
	float b = 0.2;

	float3 fogc = float3(0.5, 0.6, 0.7);
	float3 sunc = float3(0.8, 0.6, 0.5);

	float fogv = a * exp(-ro.y*b) * (1.0 - exp(-t*rd.y*b)) / rd.y;
	float sunv = clamp(dot(rd,normalize(lp)),0,1);
	fogc = lerp(fogc,sunc,sunv);
	col= lerp(col, fogc, fogv);
}

float4 main(PixelShaderInput input) : SV_TARGET
{
	float2 uv = input.tex-float2(0.5,0.5);
	float as = iResolution.x / iResolution.y;
	uv.x *= as;
	Ray ray;
	float3 eye = float3(0,0,-20);
	float3 tar = float3(0, 0, 10);
	float3 col = float3(0,0,0);
	float3 light = float3(10,10,-10);
	setCamera(ray,eye,tar,uv);
	float2 res = rayHit(ray);
	float3 hitP = ray.o + res.x*ray.d;

	doLight(col, hitP, light,res.x);
	textureMap(col,hitP,res.y);
	fog(col, ray.o, ray.d, res.x, light);

    return float4(col.xyz,1);
}
