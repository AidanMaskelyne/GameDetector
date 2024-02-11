#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm> 
#include <cctype>
#include <locale>

inline void left_trim_string(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

inline void right_trim_string(std::string& s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

#ifdef _WIN32
#include <Windows.h>
std::wstring RegGetString(HKEY hKey, const std::wstring& subKey, const std::wstring& value)
{
	DWORD dataSize{};
	LONG retCode = RegGetValue(
		hKey,
		subKey.c_str(),
		value.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		nullptr,
		&dataSize
	);

	if (retCode != ERROR_SUCCESS)
	{
		throw std::runtime_error("Failed to get size of key value");
	}

	std::wstring data;
	data.resize(dataSize / sizeof(wchar_t));

	retCode = RegGetValue(
		hKey,
		subKey.c_str(),
		value.c_str(),
		RRF_RT_REG_SZ,
		nullptr,
		&data[0],
		&dataSize
	);

	if (retCode != ERROR_SUCCESS)
	{
		throw std::runtime_error("Failed to get data of key value");
	}

	DWORD stringLengthInWChars = dataSize / sizeof(wchar_t);
	stringLengthInWChars--;		/* Remove additional NUL written by Win32 API */
	data.resize(stringLengthInWChars);

	return data;
}
#endif