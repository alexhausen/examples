extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <cstdio>

static int func(lua_State* L);

static const struct luaL_reg mylib[] = {
	{ "func", func },
	{ NULL, NULL }
};

extern "C" int luaopen_libmylib(lua_State* L) {
	luaL_openlib(L, "mylib", mylib, 0);
	return 1;
}

static int func(lua_State* L) {
	puts("C function called");
	lua_pushnumber(L, 42);
	return 1;
}

