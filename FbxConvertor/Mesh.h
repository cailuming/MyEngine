#pragma once
#include"Main.h"
struct Vec3 {
	float x;
	float y;
	float z;
};

struct Vertex {
	Vec3 pos;
	Vec3 norm;
	Vec3 tex;
};

// Mesh file format
struct MeshFile {
	int vertexCount;
	int indexCount;
	int polyCount;
	Vec3 trans;
	Vec3 scale;
	Vertex *vertex;
	int *indices;
};


class Mesh
{
public:
	Mesh() {};
	~Mesh() {};
public:
	static Mesh *instance;
	static Mesh *Create();
	static void Destroy();
public:
	MeshFile mesh;
public:
	void setVertexData(int index,float x,float y,float z);
	void setNormalData(int index, float x, float y, float z);
	void setUVData(int index, float x, float y);
	void setTransData(FbxDouble3 trans, FbxDouble3 scale);
};

