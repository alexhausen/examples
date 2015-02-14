--local libinit = assert(package.loadlib("/home/xande/projetos/PoC/lua/ldir/libluadir.so.1.0.1", "luaopen_mylib"))
--set LUA_CPATH=.
local libinit = assert(package.loadlib("./libluadir.so", "luaopen_mylib"))
local fs = libinit()
local files = fs.dir(".")
for key, file in pairs(files) do
	print(key, file)
end
