#pragma once

#include <cstdint>

class TexRenderer {
public:
	int64_t texture;
	int64_t shader;
	int32_t VAO;
	int32_t buffers[5];
};