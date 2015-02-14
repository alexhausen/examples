#pragma once

#include <lua.hpp>
#include <vector>

class BoolArray {
public:
	BoolArray(unsigned int size);
	~BoolArray();
	static int New(lua_State* L);
	static int Set(lua_State* L);
	static int Get(lua_State* L);
	static int Size(lua_State* L);

private:
	static BoolArray* lua_checkarray(lua_State* L);
	std::vector<bool> array_;
};

