#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4 & matrix);
	//void glUniform1f GLEW_GET_FUN(__glewUniform1f)				// done
	//void glUniform1fv GLEW_GET_FUN(__glewUniform1fv)
	//void glUniform1i GLEW_GET_FUN(__glewUniform1i)				// done
	//void glUniform1iv GLEW_GET_FUN(__glewUniform1iv)
	//void glUniform2f GLEW_GET_FUN(__glewUniform2f)
	//void glUniform2fv GLEW_GET_FUN(__glewUniform2fv)
	//void glUniform2i GLEW_GET_FUN(__glewUniform2i)
	//void glUniform2iv GLEW_GET_FUN(__glewUniform2iv)
	//void glUniform3f GLEW_GET_FUN(__glewUniform3f)
	//void glUniform3fv GLEW_GET_FUN(__glewUniform3fv)
	//void glUniform3i GLEW_GET_FUN(__glewUniform3i)
	//void glUniform3iv GLEW_GET_FUN(__glewUniform3iv)
	//void glUniform4f GLEW_GET_FUN(__glewUniform4f) 				// done
	//void glUniform4fv GLEW_GET_FUN(__glewUniform4fv)
	//void glUniform4i GLEW_GET_FUN(__glewUniform4i)
	//void glUniform4iv GLEW_GET_FUN(__glewUniform4iv)
	//void glUniformMatrix2fv GLEW_GET_FUN(__glewUniformMatrix2fv)
	//void glUniformMatrix3fv GLEW_GET_FUN(__glewUniformMatrix3fv)
	//void glUniformMatrix4fv GLEW_GET_FUN(__glewUniformMatrix4fv)	// done

private:
	unsigned int m_rendererID;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_unoform_location_cache;

	int GetUniformLocation(const std::string& name);

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

