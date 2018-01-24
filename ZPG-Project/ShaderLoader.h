#pragma once

#include <glad/glad.h> 
#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class ShaderLoader
{
	GLuint	programID, vertexID, fragmentID;
	string loadFile(const char *fname);
public:
	GLuint loadShader(const char *vertexFile, const char *fragmentFile);
	void deleteShader();
};

