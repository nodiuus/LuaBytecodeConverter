#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

extern "C" {
    #include "Lua/lua.h"
    #include "Lua/lauxlib.h"
    #include "Lua/lualib.h"
}

int HexWriter(lua_State* L, const void* Pointer, size_t Size, void* UserData) {
    (void)L;   
    FILE* File = (FILE*)UserData;
    const unsigned char* Bytes = (const unsigned char*)Pointer;
    
    for (size_t i = 0; i < Size; i++) {
        fprintf(File, "%02X", Bytes[i]);
    }
    return 0;
}

int Writer(lua_State* L, const void* Pointer, size_t Size, void* UserData) {
    (void)L;  
    FILE* File = (FILE*)UserData;
    fwrite(Pointer, Size, 1, File);
    return 0;
}

int main() {
    lua_State* L = luaL_newstate();

    std::string Input = "local hi = 'h2i'; print(hi)";
    //std::cin >> Input;

    luaL_loadstring(L, Input.c_str());

    FILE* File = fopen("bytecode", "wb");
    lua_dump(L, HexWriter, File);
    fclose(File);
    
    lua_close(L);
    return 0;
}