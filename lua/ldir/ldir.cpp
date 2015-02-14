#include <lua.hpp>
#include <dirent.h>
#include <errno.h>
#include <cstring>

static int l_dir (lua_State *L) {
	DIR *dir;
	struct dirent *entry;
	int i;
	const char *path = luaL_checkstring(L, 1);

	/* open directory */
	dir = opendir(path);
	if (dir == NULL) {  /* error opening the directory? */
		lua_pushnil(L);  /* return nil and ... */
		lua_pushstring(L, strerror(errno));  /* error message */
		return 2;  /* number of results */
	}

	/* create result table */
	lua_newtable(L);
	i = 1;
	while ((entry = readdir(dir)) != NULL) {
		lua_pushnumber(L, i++);  /* push key */
		lua_pushstring(L, entry->d_name);  /* push value */
		lua_settable(L, -3);
	}

	closedir(dir);
	return 1;  /* table is already on top */
}

//int main() {
//	return 0;
//}

static const struct luaL_reg mylib [] = {
	{"dir", l_dir},
	{NULL, NULL}  /* sentinel */
};

extern "C" int luaopen_mylib (lua_State *L) {
	luaL_openlib(L, "mydirlib", mylib, 0);
	return 1;
}
