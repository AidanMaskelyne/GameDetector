#pragma once

#include "Utilities.h"

#if defined(_WIN32)
namespace gd::Steam
{
	std::wstring getSteamInstallPath(void)
	{
		std::wstring steamInstallPath = RegGetString(HKEY_CURRENT_USER, L"Software\\Valve\\Steam", L"SteamPath");

		std::replace(steamInstallPath.begin(), steamInstallPath.end(), L'/', L'\\');	/* Replace the forward slashes with back slashes */

		return steamInstallPath;
	}

	std::filesystem::path getLibraryFoldersVBFFile(const std::wstring* steamPath)
	{
		std::filesystem::path path(*steamPath);
		path.append("steamapps");
		path.append("libraryfolders.vdf");

		return path;
	}

	std::vector<std::filesystem::path> getSteamLibraryFolders(const std::wstring* steamInstallFolder)
	{
		std::vector<std::filesystem::path> libraryFolders = {};

		std::filesystem::path vbfFileLocation = getLibraryFoldersVBFFile(steamInstallFolder);

		std::ifstream vbfFile;
		std::string line;

		vbfFile.open(vbfFileLocation.c_str(), std::ios::binary);
		if (vbfFile.is_open())
		{
			while (std::getline(vbfFile, line))
			{
				if (line.find("path") != std::string::npos)
				{
					std::wstring libraryPath = L"";

					left_trim_string(line);
					right_trim_string(line);
					line.erase(0, 6);	/* Remove the "path" from the start of the string */
					left_trim_string(line);

					/* Remove the start and end quotes */
					line.erase(0, 1);
					line.erase(line.size() - 1, 1);

					/* Change the `\\` to a `\` in the path */
					for (std::string::size_type i = 0; i < line.size(); ++i)
					{
						libraryPath += line[i];

						/* Skip over the next backslash */
						if (line[i] == '\\')
						{
							++i;
						}
					}

					// libraryFolders.push_back(libraryPath);
					std::filesystem::path steamLibraryFolder(libraryPath);
					steamLibraryFolder.append("steamapps");
					steamLibraryFolder.append("common");
					libraryFolders.push_back(steamLibraryFolder);
				}
			}
		}
		else
		{
			std::wcout << L"[ERROR] Failed to open file: " << vbfFileLocation.native() << std::endl;
		}

		return libraryFolders;
	}
}
#else
#error Tried to include Steam_Win32.h on a non-windows platform
#endif