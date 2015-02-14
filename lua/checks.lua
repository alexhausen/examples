


std::map<std::string, std::string> check_table_string_string(lua_State* L, int table_pos) {
	map<std::string, std::string> table;
	//make sure there is free space on stack for key and value	
	lua_checkstack(L, 2);
	//first key
	lua_pushnil(L);
	while (lua_next(L, table_pos)) {
		// get key from index -2 and value from index -1
		std::string k = luaL_checkstring(L, -2);
		std::string v = luaL_checkstring(L, -1);
		table.insert(std::make_pair(k, v));
		//remove value, keep key for next iteration
		lua_pop(L, 1);
	}
	return table;
}

std::vector<std::string> check_array_string(lua_State* L, int array_pos) {
	std::vector<std::string> array;
	lua_checkstack(L, 2);
	lua_pushnil(L);
	while (lua_next(L, array_pos)) {
		std::string s = luaL_checkstring(L, -1);
		array.push_back(s);
		lua_pop(L, 1);
	}
	return array;
}


check<std::string>
luaL_checkstring(L, n);


check<int>
luaL_checkinteger(L, n);


check<double>
luaL_checknumber(L, n);


