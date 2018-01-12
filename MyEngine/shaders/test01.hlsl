 
#define PI 3.1415926
#define FAR 64

struct Ray {
	float3 o;
	float3 d;
};

float2 hash(float2 p)
{
	float2 x =float2(127.1,311.7);
	float2 y =float2(269.5,183.3);
	
	p = float2(dot(p,x),dot(p,y));
	return -1.0 + 2.0*frac(sin(p)*4302458.545);
}

float Noise(in float2 x){
    float2 p =floor(x);
    float2 w =frac(x);
    //quintic interpolant
    float2 u = w*w*w*w*w*6-15*w*w*w*w+10*w*w*w;
    float2 du = 30*w*w*w*w-60*w*w*w+30*w*w;
    //gradients
    float2 g1 = hash(p+float2(0,0));
    float2 g2 = hash(p+float2(1,0));
    float2 g3 = hash(p+float2(0,1));
    float2 g4 = hash(p+float2(1,1));
    // projections
    float v1 = dot(g1,w-float2(0,0));
    float v2 = dot(g2,w-float2(1,0));
    float v3 = dot(g3,w-float2(0,1));
    float v4 = dot(g4,w-float2(1,1));
    // interpolation
    float k1=v2-v1;
    float k2=v3-v1;
    float k3=v4-v3-v2+v1;
    float v = v1+k1*u.x+k2*u.y+k3*u.x*u.y;
 
	return v;	
}

float fbm(in float2 p){
    float res =0;
    float ft =0.5;
    float total=0;
    float arc =iTime*0.001;
    float2x2 m = float2x2(0.8,1.6 , -0.6,0.8);
    
    for(int i=0;i<4;i++){
        res+=2*Noise(p);
        total+=ft;
        ft*=0.5;
        p=mul(p,m);
        m=mul(m,m);
    }
    
    return res/total;
}

float2 obj(float3 p,float3 c) {
	p -= c;
	float f =Noise(float2(p.x,p.z));
	return float2(lerp(length(p)-1,5*f,0.5),0);
}

float2 plane(float3 p, float3 c) {
	p -= c;
    float f =Noise(float2(p.x,p.z));
	return float2(p.y+1+0.5*f, 1);
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
	float t=1;
	float res=1;
	for(int i=0;i<128;i++){
        h=map(lp+t*ld).x;
		
        res=min(res,h*k/t);
		t+=clamp(h,mint,1);
		if(h<0.0001||t<mint||t>maxt){
			break;
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
	float3 ld = normalize(p-lp);
	float nl = clamp(dot(n,-ld),0,1);
	 float sl=  shadow(lp,ld,0.0001,length(lp-p)*0.98,128);
	 nl*=sl;
	col = float3(nl,nl,nl);
}

void setCamera(inout Ray r,float3 pos,float3 tar,float2 uv) {
	float3 look = normalize(tar);
	float3 right = normalize(cross(float3(0,1,0),look));
	float3 up = normalize(cross(look,right));
	r.o = pos;
	r.d = normalize(uv.x*right + uv.y*up +  look);
}
 
void textureMap(inout float3 col,float3 p,int id) {
	float v = 0;
	switch (id) {
	case 0:
		 
		break;
	case 1:
		float arc = atan2(p.z,p.x);
		 
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
	float3 eye = float3(0,0,-10+2*sin(iTime*0.0001));
	float3 tar = float3(0, 0, 1);
	float3 col = float3(0,0,0);
	float3 light = float3(sin(iTime*0.001)*10,20,cos(iTime*0.001)*10);
	setCamera(ray,eye,tar,uv);
	float2 res = rayHit(ray);
	float3 hitP = ray.o + res.x*ray.d;

	doLight(col, hitP, light,res.x);
	textureMap(col,hitP,res.y);
	fog(col, ray.o, ray.d, res.x, light);
   
    return float4(col.xyz,1);
}
