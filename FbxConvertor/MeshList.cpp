#include "MeshList.h"

 
MeshList *MeshList::instance=0;

MeshList *MeshList::getInstance() {
	if (!instance) {
		instance = new MeshList();
	}
	return instance;
};

void MeshList::release() {
	if (instance) {
		delete instance;
		instance = 0;
	}
};

void MeshList::AddMesh(Mesh *p) {
	if (!root) {
		root = new Mesh*[64];
	}
	if (meshNum>63) {
		printf("array size is exceeded!\n");
		return;
	}
	root[meshNum++] = p;
};

void MeshList::PrintInfo() {
	for (int i = 0; i < meshNum; i++) {

	}
};

void MeshList::writeAsJson(const char *filename) {
	FILE *file = 0;
	char buff[64];
	sprintf_s(buff, "%s.json", filename);
	fopen_s(&file, buff, "w+");

	if (file) {
		fseek(file, 0, 0);

		fprintf_s(file, "{\n");
		fprintf_s(file, "   \"meshNum\":%d,\n",meshNum);
		 
		fprintf_s(file, "   \"meshData\":[\n");
	    for (int i = 0; i < meshNum;i++) {
			fprintf_s(file, "   {\n");
			 
			fprintf_s(file, "      \"polyCount\":%d,\n", root[i]->mesh.polyCount);
			fprintf_s(file, "      \"trans\":[%f,%f,%f],\n", root[i]->mesh.trans.x, root[i]->mesh.trans.y, root[i]->mesh.trans.z);
			fprintf_s(file, "      \"scale\":[%f,%f,%f],\n", root[i]->mesh.scale.x, root[i]->mesh.scale.y,root[i]->mesh.scale.z);

			fprintf_s(file, "      \"vertexData\":[\n   ");

			for (int j = 0; j < root[i]->mesh.polyCount*3; j++) {
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].pos.x);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].pos.y);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].pos.z);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].norm.x);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].norm.y);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].norm.z);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].tex.x);
				fprintf_s(file, "%f,", root[i]->mesh.vertex[j].tex.y);
				if (j == root[i]->mesh.polyCount * 3 - 1) {
					fprintf_s(file, "%d", (int)root[i]->mesh.vertex[j].tex.z);
				}
				else {
					fprintf_s(file, "%d,", (int)root[i]->mesh.vertex[j].tex.z);
				}
			}
		 
			fprintf_s(file, "\n       ]\n");
		 
			if (i==meshNum-1) {
				fprintf_s(file, "   }\n");
			}
			else {
				fprintf_s(file, "},\n");
			}

		}

		fprintf_s(file, "]\n");

		fprintf_s(file, "}\n");

		fflush(file);
		fclose(file);
		printf("Convert fbx to Json successfully!\n");
	}
	else {
		printf("Failed to create the file!\n");
	}
};

void MeshList::writeAsBinary(const char *filename) {
	FILE *file = 0;
	char buff[64];
	sprintf_s(buff, "%s.clm3D", filename);

	fopen_s(&file, buff, "wb+");

	if (file) {
		fseek(file, 0, 0);
		fwrite(&meshNum, sizeof(int), 1, file);

	    for (int i = 0; i < meshNum; i++) {
			
			fwrite(&root[i]->mesh.polyCount, sizeof(int), 1, file);
			fwrite(&root[i]->mesh.trans, sizeof(Vec3), 1, file);
			fwrite(&root[i]->mesh.scale, sizeof(Vec3), 1, file);
			fwrite(root[i]->mesh.vertex, sizeof(Vertex), root[i]->mesh.polyCount*3, file);
 
		}
		fflush(file);
		fclose(file);
		printf("Convert fbx to clm3D successfully!\n");
	}
	else {
		printf("Failed to create the file!\n");
	}
};
