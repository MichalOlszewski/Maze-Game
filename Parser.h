#pragma once
/*S�u�y do parsowania plik�w .obj �ci�gnietych z internetu
   Dostajemy wsp�rzedne wierzcho�k�w, wsp�rz�dne wekt. normalnych i wsp�rz�dne teksturowania*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>


using namespace std;

class Parser
{

public:

	//vector<glm::vec4> ftmp;
	inline vector<string> split(string line, const char* sep);
	inline void readfile(const char* filename, vector<float>& vertices, vector<float> &normals, vector<float>& textures);
	//inline vector<glm::vec4> getVtmp();
	//inline vector<glm::vec4> getVnmp();
	//inline vector<glm::vec2> getVttmp();
	//inline vector<glm::vec4> getFtmp();

};



