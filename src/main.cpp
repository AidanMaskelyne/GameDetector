#include <GameDetector/GameDetector.h>

int main(int argc, char* argv[])
{
	std::wstring steamInstallPath = gd::Steam::getSteamInstallPath();

	std::wcout << L"[INFO] Got Steam install path: " << steamInstallPath << std::endl;

	std::vector<std::filesystem::path> steamLibraryFolders = gd::Steam::getSteamLibraryFolders(&steamInstallPath);

	for (uint32_t i = 0; i < steamLibraryFolders.size(); i++)
	{
		std::wcout << L"[INFO] Found Steam library folder: " << steamLibraryFolders[i].native() << std::endl;
	}

	std::cout << std::endl << "Hit [ENTER] to exit the program...";
	std::cin.get();

	return 0;
}