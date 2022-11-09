#pragma once

#include <cstddef>

class QuadRenderer {
public:
	int64_t shader;
	int32_t VAO;
	int32_t buffers[4];
	int32_t mode;
	int32_t elementCount;
	char uk1, uk2, uk3, uk4;
};