#include "ShaderProgram.h"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Log.h"


ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
	:vertex(vertexPath, GL_VERTEX_SHADER)
	, fragment(fragmentPath, GL_FRAGMENT_SHADER)
{
	// create the shader program and store the program id
	shaderProgram_id = glCreateProgram();
	attach(*this, vertex);
	attach(*this, fragment);
	glLinkProgram(shaderProgram_id);

	// delete the vertex and fragment shaders now that they have been used
	vertex.DeleteShader();
	fragment.DeleteShader();

	if (!checkAndLogLinkSuccess()) {
		glDeleteProgram(shaderProgram_id);
		throw std::runtime_error("Shaders did not link.");
	}
}

bool ShaderProgram::recompile() {

	try {
		// Try to create a new program
		ShaderProgram newProgram(vertex.getPath(), fragment.getPath());
		*this = std::move(newProgram);
		return true;
	}
	catch (std::runtime_error &e) {
		Log::warn("SHADER_PROGRAM falling back to previous version of shaders");
		return false;
	}
}


void attach(ShaderProgram& sp, Shader& s) {
	glAttachShader(sp.shaderProgram_id, s.shader_id);
}


bool ShaderProgram::checkAndLogLinkSuccess() const {

	GLint success;

	glGetProgramiv(shaderProgram_id, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logLength;
		glGetProgramiv(shaderProgram_id, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> log(logLength);
		glGetProgramInfoLog(shaderProgram_id, logLength, NULL, log.data());

		Log::error("SHADER_PROGRAM linking {} + {}:\n{}", vertex.getPath(), fragment.getPath(), log.data());
		return false;
	}
	else {
		Log::info("SHADER_PROGRAM successfully compiled and linked {} + {}", vertex.getPath(), fragment.getPath());
		return true;
	}
}
