#include "NumArray.h"

BoolArray::BoolArray(unsigned int size)
	:array_(size) {
}

BoolArray::~BoolArray() {
}

BoolArray* BoolArray::lua_checkarray(lua_State* L) {
	BoolArray* array = (BoolArray*) lua_touserdata(L, 1);
	luaL_argcheck(L, array != NULL, 1, "'array' expected");
	return array;
}


int BoolArray::New(lua_State* L) {
	int n = luaL_checkint(L, 1);
	luaL_argcheck(L, n > 0, 1, "invalid array size");
	//BoolArray* array = 
	new (lua_newuserdata(L, sizeof(BoolArray))) BoolArray(n);
	luaL_getmetatable(L, "Lua.Canvas");
	lua_setmetatable(L, -2);
	return 1;
}

int BoolArray::Set(lua_State* L) {
	BoolArray* a = lua_checkarray(L);
	int index = luaL_checkint(L, 2) - 1;
	luaL_checkany(L, 3);
	luaL_argcheck(L, 0 <= index && index < (int)a->array_.size(), 2, "index out of bounds");
	bool b = lua_toboolean(L, 3);
	a->array_[index] = b;
	return 0;
}

int BoolArray::Get(lua_State* L) {
	BoolArray* a = lua_checkarray(L);
	int index = luaL_checkint(L, 2) - 1;
	luaL_argcheck(L, 0 <= index  && index < (int)a->array_.size(), 2, "index out of bounds");
	lua_pushboolean(L, a->array_[index]);
	return 1;
}

int BoolArray::Size(lua_State* L) {
	BoolArray* a = lua_checkarray(L);
	lua_pushinteger(L, a->array_.size());
	return 1;
}

static const struct luaL_Reg arraylib_f[] = {
	{ "new", BoolArray::New },
	{ NULL, NULL }
};

static const struct luaL_Reg arraylib_m[] = {
	{ "set", BoolArray::Set },
	{ "get", BoolArray::Get },
	{ "size", BoolArray::Size },
	{ NULL, NULL }
};

extern "C" int luaopen_BoolArray(lua_State* L) {
	luaL_newmetatable(L, "LuaBook.array");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_register(L, NULL, arraylib_m);
	luaL_register(L, "array", arraylib_f);
	return 1;
}

