// ShaderLoader.cpp
#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

GLuint LoadShader(const std::string& filePath, GLenum shaderType) {
    // Get the path to the directory of the ShaderLoader.cpp file
    std::string shaderLoaderPath(__FILE__);
    std::string shaderLoaderDirectory = shaderLoaderPath.substr(0, shaderLoaderPath.find_last_of("\\/"));

    // Construct the full path to the shader file
    std::string fullFilePath = shaderLoaderDirectory + "\\..\\Shaders\\" + filePath;

    std::cout << "Loading shader from file: " << fullFilePath << std::endl;  // Debug output

    // Read shader source code from file
    std::ifstream shaderFile(fullFilePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << fullFilePath << std::endl;
        return 0;
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string shaderCode = shaderStream.str();
    shaderFile.close();

    // Compile shader
    const char* shaderCodeCStr = shaderCode.c_str();
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderCodeCStr, NULL);
    glCompileShader(shaderID);

    // Check for shader compilation errors
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cerr << "Shader compilation error in " << fullFilePath << ": " << infoLog << std::endl;
        return 0;
    }

    return shaderID;
}