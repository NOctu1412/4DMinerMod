#pragma once

#include <string>
#include <glm/glm.hpp>

class FontRenderer {
public:
	std::string text;
	glm::vec2 charSize;
	int32_t fontSize;
	glm::vec2 pos;
	glm::f32vec4 color;
	glm::fmat4x4 model;
	bool centered;
	char uk1; //unknown
	char uk2;
	char uk3;
	int64_t shader;
	int64_t VAO;
	int64_t charVAO;
};