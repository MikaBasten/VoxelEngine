// ShaderLoader.h
#pragma once

#include <glew.h>
#include <string>

GLuint LoadShader(const std::string& filePath, GLenum shaderType);
