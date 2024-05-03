#pragma once
#include <Windows.h>

#define baseAddr (DWORD)GetModuleHandle(NULL)


/*local smallBufferSize = 0xE0
	local lengthAddress = address + smallBufferSize
	local length = readInteger(lengthAddress)
	local res = nil
	if (length < smallBufferSize) then
		res = readString(address, length)
	else
		res = readString(readInteger(address), length)
	end
	return res*/
template <class T> T ReadMemory(DWORD dwAddrToRead)
{
	return *(T*)dwAddrToRead;
}

template <class T> bool WriteMemory(DWORD Address, T Valuee)
{
	*(T*)Address = Valuee;
	return true;
}

inline char* GetStr(DWORD offset) {
	auto smallBufferSize = 0xE0;
	auto lengthAddress = offset + smallBufferSize;
	auto length = *(int*)(offset + smallBufferSize);

	if (length < smallBufferSize)
		return (char*)offset;
	else
		return (char*)(*(DWORD*)offset);
}
#define BLOCK_SIZE 32

UINT getBlockIndex(const Position& pos) { return ((pos.y / BLOCK_SIZE) * (65536 / BLOCK_SIZE)) + (pos.x / BLOCK_SIZE); }

UINT getTileIndex(const Position& pos) { return ((pos.y % BLOCK_SIZE) * BLOCK_SIZE) + (pos.x % BLOCK_SIZE); }

static bool isPartOf(const char* w1, const char* w2)
{
	int i = 0;
	int j = 0;


	while (w1[i] != '\0') {
		if (w1[i] == w2[j])
		{
			int init = i;
			while (w1[i] == w2[j] && w2[j] != '\0')
			{
				j++;
				i++;
			}
			if (w2[j] == '\0') {
				return true;
			}
			j = 0;
		}
		i++;
	}
	return false;
}