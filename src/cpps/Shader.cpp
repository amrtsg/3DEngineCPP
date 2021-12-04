#include <Shader.h>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    // 1. Retrieve the vertex/fragment source code from filePath
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);
    try
    {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure e) {
        cout << "SHADER PROGRAM ERROR " << endl;
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "VERTEX ERROR " << infoLog << endl;
    }


    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "FRAGMENT ERROR " << infoLog << endl;
    }
    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        cout << "SHADER LINKING ERROR " << infoLog << endl;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

// Uses the current shader
void Shader::use() {
    glUseProgram(this->Program);
}

//pass uniform values to variables in shader
void Shader::setUniforms(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    GLint modelLoc = glGetUniformLocation(this->Program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    GLint viewLoc = glGetUniformLocation(this->Program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLint projLoc = glGetUniformLocation(this->Program, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

//pass uniform values to variables in shader
void Shader::setUniforms(glm::mat4 view, glm::mat4 projection) {
    GLint viewLoc = glGetUniformLocation(this->Program, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    GLint projLoc = glGetUniformLocation(this->Program, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

//pass clip plane value to shader
void Shader::loadClipPlane(glm::vec4 clipPlane) {
    GLint objClipPlaneLoc = glGetUniformLocation(this->Program, "clipPlane");
    glUniform4f(objClipPlaneLoc, clipPlane.x, clipPlane.y, clipPlane.z, clipPlane.w);
}

//pass water texture values to shader
void Shader::loadWaterTextures() {
    GLint reflectLoc = glGetUniformLocation(this->Program, "reflectionTexture");
    glUniform1i(reflectLoc, 0);
    GLint refractLoc = glGetUniformLocation(this->Program, "refractionTexture");
    glUniform1i(refractLoc, 1);
    GLint dudvLoc = glGetUniformLocation(this->Program, "dudv");
    glUniform1i(dudvLoc, 2);
    GLint depthLoc = glGetUniformLocation(this->Program, "depthMap");
    glUniform1i(depthLoc, 3);
    GLint normLoc = glGetUniformLocation(this->Program, "normalMap");
    glUniform1i(normLoc, 4);
}

//pass terrain textures to shader
void Shader::loadTerrainTextures() {
    GLint backLoc = glGetUniformLocation(this->Program, "backgroundTexture");
    glUniform1i(backLoc, 0);
    GLint rLoc = glGetUniformLocation(this->Program, "rTexture");
    glUniform1i(rLoc, 1);
    GLint gLoc = glGetUniformLocation(this->Program, "gTexture");
    glUniform1i(gLoc, 2);
    GLint bLoc = glGetUniformLocation(this->Program, "bTexture");
    glUniform1i(bLoc, 3);
    GLint blendLoc = glGetUniformLocation(this->Program, "blendMap");
    glUniform1i(blendLoc, 4);
}

//pass fog variables to shader
void Shader::loadFogVariables(glm::vec3 skyColour, float density, float gradient) {
    GLint skyLoc = glGetUniformLocation(this->Program, "fogColour");
    glUniform3f(skyLoc, skyColour.x, skyColour.y, skyColour.z);
    GLint densityLoc = glGetUniformLocation(this->Program, "density");
    glUniform1f(densityLoc, density);
    GLint gradientLoc = glGetUniformLocation(this->Program, "gradient");
    glUniform1f(gradientLoc, gradient);
}


//pass fog variables to shader
void Shader::loadSkyboxVariables(glm::vec3 skyColour, float upperLimit, float lowerLimit) {
    GLint skyLoc = glGetUniformLocation(this->Program, "fogColour");
    glUniform3f(skyLoc, skyColour.x, skyColour.y, skyColour.z);
    GLint upperLoc = glGetUniformLocation(this->Program, "upperLimit");
    glUniform1f(upperLoc, upperLimit);
    GLint lowerLoc = glGetUniformLocation(this->Program, "lowerLimit");
    glUniform1f(lowerLoc, lowerLimit);
}

void Shader::loadLightVariables(glm::vec3 lightPos, glm::vec3 lightCol) {
    GLint posLoc = glGetUniformLocation(this->Program, "lightPosition");
    glUniform3f(posLoc, lightPos.x, lightPos.y, lightPos.z);
    GLint colourLoc = glGetUniformLocation(this->Program, "lightColour");
    glUniform3f(colourLoc, lightCol.x, lightCol.y, lightCol.z);
}