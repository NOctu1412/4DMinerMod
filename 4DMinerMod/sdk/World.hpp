#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <unordered_map>
#include <map>
#include <mutex>
#include <atomic>
#include <vector>

class Chunk {
public:

};

class CloudChunk {
public:

};

class World {
public:
	std::wstring worldPath, chunksPath;
	int32_t seed;
	glm::f32vec3 terrainOffsets, biomeOffsets, caveOffsets;
	bool flatWorld;
	char uk1, uk2, uk3, uk4, uk5, uk6, uk7;
	std::unordered_map<glm::i64vec3, Chunk*, std::hash<glm::i64vec3>, std::equal_to<glm::i64vec3>, std::allocator<std::pair<glm::i64vec3 const, Chunk*>>> world;
	std::mutex worldMutex;
	std::atomic<bool> chunksReady;
	char uk8, uk9, ukA;
	std::atomic<int> loadedChunks;
	std::vector<Chunk*> newChunks;
	char pad[0x60]; //originally it is Frustum
	std::atomic<bool> shouldSpawnEntities, shouldSaveUnmodifiedChunks;
	char ukB;
	std::atomic<int> difficulty;
	std::atomic<bool> smoothLightning;
	char pad1[7];
};

class CloudManager {
public:
	glm::f32vec3 offset, velocity, lastPlayerPos, lastOffset;
	int32_t seed;
	int uk1;
	std::map<std::tuple<int64_t, int64_t, int64_t>, CloudChunk*, std::less<std::tuple<int64_t, int64_t, int64_t>>, std::allocator<std::pair<std::tuple<int64_t, int64_t, int64_t> const, CloudChunk*>>> clouds;
	std::mutex cloudsMutex;
	std::atomic<bool> chunksReady;
	char pad[3];
	std::atomic<int> loadedChunks;
	std::vector<CloudChunk*> newChunks;
	std::vector<std::tuple<int64_t, int64_t, int64_t>> newChunkPositions;
};