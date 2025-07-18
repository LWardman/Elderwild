#pragma once

#include "CoreMinimal.h"

#define REQUIRES(...) if (AnyNull(TEXT(__FILE__), __LINE__, #__VA_ARGS__, __VA_ARGS__)) return;

template<typename T>
FORCEINLINE bool AnyNull(const TCHAR* File, int32 Line, const char* ArgNames, T* ptr)
{
	if (ptr == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s:%d] Null pointer: %s"), File, Line, *FString(ANSI_TO_TCHAR(ArgNames)));
		return true;
	}
	return false;
}

template <typename T, typename... Rest>
FORCEINLINE bool AnyNull(const TCHAR* File, int32 Line, const char* ArgNames, T* ptr, Rest*... rest)
{
	bool isNull = false;

	if (ptr == nullptr)
	{
		char Buffer[1024];
		strcpy_s(Buffer, sizeof(Buffer), ArgNames);

		char* context = nullptr;
		char* token = strtok_s(Buffer, ",", &context);

		if (token)
		{
			while (*token == ' ') ++token;
			UE_LOG(LogTemp, Warning, TEXT("[%s:%d] Null pointer: %s"), File, Line, *FString(ANSI_TO_TCHAR(token)));
		}

		isNull = true;
	}

	const char* nextArgs = strchr(ArgNames, ',');
	if (nextArgs) ++nextArgs; 

	return isNull || AnyNull(File, Line, nextArgs ? nextArgs : "", rest...);
}
