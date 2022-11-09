#pragma once

#include <cstdint>

class MeshRenderer {
public:
	int32_t VAO;
	int64_t VBOs;
	int32_t indexVBO, vertexCount, bufferCount, mode;
};