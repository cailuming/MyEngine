#pragma once
#include"Mesh.h"
class MeshList
{
private:
	MeshList() {};
	~MeshList() {};
public:
	static MeshList *instance;
	static MeshList *getInstance();
	static void release();
public:
	int meshNum;
	bool useIndex;
public:
	Mesh **root;
public:
	void AddMesh(Mesh *p);
 
	void PrintInfo();
	void writeAsJson(const char *filename);
	void writeAsBinary(const char *filename);
};

