#include "Main.hpp"

int main() {
	std::cout << "Start!" << std::endl;

	std::vector<HWND> windowsArray;

	EnumWindows([](const _In_ HWND p_window, const _In_ LPARAM p_windowsArray) -> BOOL {
		std::vector<HWND> &windows = *(reinterpret_cast<std::vector<HWND>*>(p_windowsArray));
		windows.push_back(p_window);
		return TRUE;
	}, reinterpret_cast<LPARAM>(&windowsArray));

	std::cout << "We have `" << windowsArray.size() << "` windows.";
	std::cout << "Press enter to make them spin!";

	const DWORD procId = GetCurrentProcessId();




}
