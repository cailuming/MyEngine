#include "Mesh.h"

Mesh *Mesh::instance=0;

Mesh *Mesh::Create() {
	if (nullptr==instance) {
		instance = new Mesh();
	}
	return instance;
};

void Mesh::Destroy() {
	if (instance) {
		delete instance;
		instance = 0;
	}
};

void Mesh::setVertexData(int index, float x, float y, float z) {
	mesh.vertex[index].pos.x = x;
	mesh.vertex[index].pos.y = y;
	mesh.vertex[index].pos.z = z;
};

void Mesh::setNormalData(int index, float x, float y, float z) {
	mesh.vertex[index].norm.x = x;
	mesh.vertex[index].norm.y = y;
	mesh.vertex[index].norm.z = z;
};
void Mesh::setUVData(int index, float x, float y) {
	mesh.vertex[index].tex.x = x;
	mesh.vertex[index].tex.y = y;
	mesh.vertex[index].tex.z = 0;
};

void Mesh::setTransData(FbxDouble3 trans, FbxDouble3 scale) {
	mesh.trans.x=trans.mData[0];
	mesh.trans.y = trans.mData[1];
	mesh.trans.z = trans.mData[2];

	mesh.scale.x = scale.mData[0];
	mesh.scale.y = scale.mData[1];
	mesh.scale.z = scale.mData[2];
};
