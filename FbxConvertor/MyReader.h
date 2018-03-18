#pragma once
#include "Main.h"
#include "MeshList.h"
#include "StringUtils.h"

class MyReader  
{
private:
	MyReader() { };
	~MyReader() {};
public:
	static MyReader *instance;
	static MyReader *getInstance();
	static void release();
public:
	void showVersion(FbxImporter* lImporter);
	void importScene(const char *fileName);
	void readScene();
 
public:
	
	void WriteFile();
	void HandleNode(FbxNode* pNode);
	void HandleMesh(FbxNode* pNode,Mesh *mesh);
	void HandleMeshWithoutIndex(FbxNode* pNode, Mesh *mesh);
	void HandleUV(int i, int j, FbxMesh *pMesh, Mesh *mesh);
	void HandleNormal(int i, int j, FbxMesh *pMesh, Mesh *mesh);
	void HandleNodeByType(FbxNodeAttribute::EType type,FbxNode* pNode);
public:
	void PrintAttributeName(FbxNodeAttribute* pAttribute);
	void PrintTransform(FbxNode *pNode);
private:
	FILE*		mFilePointer;
	FbxManager*	mManager;
	FbxScene* lScene;
	MeshList *meshList;
	char *outName;
 
};

