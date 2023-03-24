// Copyright 2022 CQUnreal. All Rights Reserved.

#include "UnLuaEx.h"
#include "LuaCore.h"
#include "LuaDynamicBinding.h"

static int32 FPaths_Combine(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	FString FinalPath;
	for (int32 index = 1; index <= NumParams; ++index)
	{
		FString arg = luaL_tolstring(L, index, nullptr);
		if (FinalPath.IsEmpty())
		{
			if (!arg.IsEmpty())
			{
				FinalPath = arg;
				continue;
			}

		}
		if (!arg.IsEmpty())
			FinalPath = FPaths::Combine(FinalPath, arg);
	}
	lua_pushstring(L, TCHAR_TO_ANSI(*FinalPath));
	return 1;
}

static int32 FPaths_ProjectScriptDir(lua_State *L)
{
	int32 NumParams = lua_gettop(L);
	FString Result = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Script"));

	FTCHARToUTF8 UTF8CHAR_Ins(*Result);
	lua_pushlstring(L, (ANSICHAR*)(UTF8CHAR_Ins.Get()), UTF8CHAR_Ins.Length());
	return 1;
}


static const luaL_Reg FPathsLib[] =
{
	{ "Combine", FPaths_Combine },
	{ "ProjectScriptDir",FPaths_ProjectScriptDir},
	{ nullptr, nullptr }
};

// Export Actor Component
BEGIN_EXPORT_CLASS(FPaths)
	ADD_STATIC_FUNCTION_EX("EngineDir", FString, EngineDir)
	ADD_STATIC_FUNCTION_EX("EngineUserDir", FString, EngineUserDir)
	ADD_STATIC_FUNCTION_EX("EngineContentDir", FString, EngineContentDir)
	ADD_STATIC_FUNCTION_EX("EngineConfigDir", FString, EngineConfigDir)
	ADD_STATIC_FUNCTION_EX("EngineSavedDir", FString, EngineSavedDir)
	ADD_STATIC_FUNCTION_EX("EnginePluginsDir", FString, EnginePluginsDir)
	// ADD_STATIC_FUNCTION_EX("PlatformExtensionsDir", FString, PlatformExtensionsDir)
	ADD_STATIC_FUNCTION_EX("RootDir", FString, RootDir)
	ADD_STATIC_FUNCTION_EX("ProjectDir", FString, ProjectDir)
	ADD_STATIC_FUNCTION_EX("ProjectUserDir", FString, ProjectUserDir)
	ADD_STATIC_FUNCTION_EX("ProjectContentDir", FString, ProjectContentDir)
	ADD_STATIC_FUNCTION_EX("ProjectConfigDir", FString, ProjectConfigDir)
#if ENGINE_MAJOR_VERSION > 4 || ENGINE_MINOR_VERSION > 24
	ADD_STATIC_FUNCTION_EX("ProjectSavedDir", const FString&, ProjectSavedDir)
#else
	ADD_STATIC_FUNCTION_EX("ProjectSavedDir", FString, ProjectSavedDir)
#endif
	ADD_STATIC_FUNCTION_EX("ProjectIntermediateDir", FString, ProjectIntermediateDir)
	ADD_STATIC_FUNCTION_EX("ProjectPluginsDir", FString, ProjectPluginsDir)
	ADD_STATIC_FUNCTION_EX("ProjectLogDir", FString, ProjectLogDir)
	ADD_STATIC_FUNCTION_EX("GetExtension", FString, GetExtension, const FString&, bool)
	ADD_STATIC_FUNCTION_EX("Split", void, Split,const FString&, FString&, FString&, FString&)
	ADD_STATIC_FUNCTION_EX("FileExists",bool, FileExists,const FString&)
	ADD_STATIC_FUNCTION_EX("DirectoryExists", bool, DirectoryExists, const FString&)
	ADD_STATIC_FUNCTION_EX("ConvertRelativePathToFull", FString, ConvertRelativePathToFull, const FString&)
	ADD_LIB(FPathsLib)
END_EXPORT_CLASS()
IMPLEMENT_EXPORTED_CLASS(FPaths)

