#include"Main.h"
#include "MyReader.h"

MyReader *reader = MyReader::getInstance();

void main(int argn,char **argv) {
	//argv[1]
	//reader->importScene(argv[1]);
	reader->importScene("test.fbx");
	reader->readScene();
    
	reader->WriteFile();

	system("pause");
}