#include "MyReader.h"

MyReader * MyReader::instance=0;

MyReader * MyReader::getInstance() {
	if (nullptr==instance) {
		instance = new MyReader();
	}
	return instance;
};

void MyReader::release() {
	if (instance) {
		delete instance;
		instance = 0;
	}
};

void MyReader::showVersion(FbxImporter* lImporter){
	int lFileMajor, lFileMinor, lFileRevision;
	lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);
	printf("version is %d.%d.%d\n", lFileMajor, lFileMinor, lFileRevision);
}


void MyReader::importScene(const char *fileName) {
	mManager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(mManager, IOSROOT);
	mManager->SetIOSettings(ios);
	int index=StringUtils::getInstance()->getLastCharLocAt(fileName,'\\');
	outName = new char[strlen(fileName)-index+1];
	
	StringUtils::getInstance()->sliceString(fileName, index+1, strlen(fileName), outName);
 
	// we just create an FbxImpoter
	FbxImporter* lImporter = FbxImporter::Create(mManager, "");

	// Init the fbx importer
	if (!lImporter->Initialize(fileName, -1, mManager->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		system("pause");
		exit(-1);
	}
	showVersion(lImporter);
	
	printf("Please wait a moment!\n");
	
	lScene = FbxScene::Create(mManager, "myScene");

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	// The file is imported, so get rid of the importer.
	lImporter->Destroy();
}

void MyReader::readScene() {
	FbxNode* lRootNode = lScene->GetRootNode();

	meshList = MeshList::getInstance();

	if (lRootNode) {
		printf("......................MeshNum %d:\n", lRootNode->GetChildCount());
		
		for (int i = 0; i < lRootNode->GetChildCount(); i++) {
			HandleNode(lRootNode->GetChild(i));
		}
		
	}
	 
	mManager->Destroy();
 
}

void MyReader::HandleNodeByType(FbxNodeAttribute::EType type,FbxNode* pNode) {
	switch (type) {
	 
	case FbxNodeAttribute::eSkeleton: 
		break;
	case FbxNodeAttribute::eMesh:
		Mesh *mesh = new Mesh();
		meshList->AddMesh(mesh);
		
		HandleMeshWithoutIndex(pNode,mesh);
		break;
	}
}

// just print the Node attributes info
void MyReader::PrintAttributeName(FbxNodeAttribute* pAttribute) {

	switch (pAttribute->GetAttributeType())
	{
	default:
		break;
	case FbxNodeAttribute::eMarker:
		printf("type is emarker,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::eSkeleton:
		printf("type is eSkeleton,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::eMesh:
		printf("type is eMesh,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::eNurbs:
		printf("type is eNurbs,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::ePatch:
		printf("type is emarker,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::eCamera:
		printf("type is eCamera,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::eLight:
		printf("type is eLight,name is %s\n", pAttribute->GetName());
		break;

	case FbxNodeAttribute::eLODGroup:
		printf("type is eLODGroup,name is %s\n", pAttribute->GetName());
		break;
	}
};

void MyReader::PrintTransform(FbxNode *pNode){
	
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();
	
	printf("\n");
	// Print the contents of the node.
	printf(" translation=(%f, %f, %f)\n rotation=(%f, %f, %f)\n scaling=(%f, %f, %f)\n\n",
		translation[0], translation[1], translation[2],
		rotation[0], rotation[1], rotation[2],
		scaling[0], scaling[1], scaling[2]
	);
}

void MyReader::HandleNode(FbxNode* pNode) {
	// How many attributes does the node have
	FbxNodeAttribute *pAttribute;
	
	const char* nodeName = pNode->GetName();
	printf("node name:%s\n",nodeName);
	PrintTransform(pNode);

	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++) {
		pAttribute = pNode->GetNodeAttributeByIndex(i);
		PrintAttributeName(pAttribute);
		HandleNodeByType(pAttribute->GetAttributeType(), pNode);
	}
    
	for (int i = 0; i < pNode->GetChildCount();i++) {
		HandleNode(pNode->GetChild(i));
	}
}
 
void MyReader::HandleUV(int i,int j,FbxMesh *pMesh,Mesh *mesh) {
	int controlID = i * 3 + j;
	FbxGeometryElementUV* leUV = pMesh->GetElementUV(0);
	if (!leUV) {
		printf("there is no UV!\n");
		return;
	}
	FbxVector2 uv;
	switch (leUV->GetMappingMode())
	{
	default:
		break;
	case FbxGeometryElement::eByControlPoint:
		switch (leUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
			uv = leUV->GetDirectArray().GetAt(controlID);

			mesh->setUVData(controlID,uv.mData[0],uv.mData[1]);
		  
			break;
		case FbxGeometryElement::eIndexToDirect:
		{

			int id = leUV->GetIndexArray().GetAt(controlID);
			
			uv = leUV->GetDirectArray().GetAt(id);

			mesh->setUVData(controlID, uv.mData[0], uv.mData[1]);

		}
		break;
		default:
			break; // other reference modes not shown here!
		}
		break;

	case FbxGeometryElement::eByPolygonVertex:
	{

		int id = pMesh->GetTextureUVIndex(i, j);

		switch (leUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		case FbxGeometryElement::eIndexToDirect:
		{
		 
			uv = leUV->GetDirectArray().GetAt(id);
			mesh->setUVData(controlID, uv.mData[0], uv.mData[1]);
 
		}
		break;
		default:
			break; // other reference modes not shown here!
		}
	}
	break;
	}
}

void MyReader::HandleNormal(int i, int j, FbxMesh *pMesh, Mesh *mesh) {
	FbxGeometryElementNormal* leNorm = pMesh->GetElementNormal(0);
	 
	FbxVector4 norm;
 
	int vertexID = i * 3 + j;
	switch (leNorm->GetReferenceMode())
	{
	case FbxGeometryElement::eDirect:
		norm = leNorm->GetDirectArray().GetAt(vertexID);
		mesh->setVertexData(vertexID, norm.mData[0], norm.mData[1], norm.mData[2]);

		break;
	case FbxGeometryElement::eIndexToDirect:
	{
		int id = leNorm->GetIndexArray().GetAt(vertexID);
		
		norm = leNorm->GetDirectArray().GetAt(id);
		mesh->setVertexData(vertexID, norm.mData[0], norm.mData[1], norm.mData[2]);
	}
	break;
	default:
		break; // other reference modes not shown here!
	}
}
 
 
void MyReader::HandleMeshWithoutIndex(FbxNode* pNode, Mesh *mesh) {
	FbxMesh *pMesh = pNode->GetMesh();
	if (!pMesh) return;
	mesh->mesh.polyCount = pMesh->GetPolygonCount();
	mesh->mesh.vertex = new Vertex[mesh->mesh.polyCount*3];

	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	mesh->setTransData(translation, scaling);
 
	for (int i = 0; i < mesh->mesh.polyCount; i++) {
		int polySize = pMesh->GetPolygonSize(i);
		if (polySize>3) {
			printf("poly index size is bigger than 3!");
			break;
		}

		for (int j = 0; j < polySize; j++) {
			int cID = pMesh->GetPolygonVertex(i, j);

			mesh->mesh.vertex[i * 3 + j].pos.x = pMesh->GetControlPointAt(cID).mData[0];
			mesh->mesh.vertex[i * 3 + j].pos.y = pMesh->GetControlPointAt(cID).mData[1];
			mesh->mesh.vertex[i * 3 + j].pos.z = pMesh->GetControlPointAt(cID).mData[2];

			HandleUV(i, j, pMesh, mesh);
			HandleNormal(i, j, pMesh, mesh);
		}
	}
};


void MyReader::WriteFile() {
#ifdef BINARY
	meshList->writeAsBinary(outName);
#endif

#ifdef JSON
	meshList->writeAsJson(outName);
#endif
}
 
 