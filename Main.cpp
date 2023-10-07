#include "Main.hpp"

const DWORD g_procId = GetCurrentProcessId();

int main() {
	std::cout << "Start!" << std::endl;
	std::map<HWND, RECT> windowsToRectsMap;

	EnumWindows([](const _In_ HWND p_window, const _In_ LPARAM p_lParam) -> BOOL {
		std::map<HWND, RECT> &windowsToRects = *(reinterpret_cast<std::map<HWND, RECT>*>(p_lParam));
		DWORD procId = 0;
		GetWindowThreadProcessId(p_window, &procId);

		EnumChildWindows(p_window, [](const _In_ HWND p_window, const _In_ LPARAM p_lParam) -> BOOL {
			std::map<HWND, RECT> &windowsToRects = *(reinterpret_cast<std::map<HWND, RECT>*>(p_lParam));
			DWORD procId = 0;
			GetWindowThreadProcessId(p_window, &procId);

			if (procId != g_procId) {
				windowsToRects[p_window] = {};
				GetWindowRect(p_window, &windowsToRects[p_window]);
			}
			return TRUE;
		}, reinterpret_cast<LPARAM>(&windowsToRects));

		if (procId != g_procId) {
			windowsToRects[p_window] = {};
			GetWindowRect(p_window, &windowsToRects[p_window]);
		}
		return TRUE;
	}, reinterpret_cast<LPARAM>(&windowsToRectsMap));


	std::cout << "We have `" << windowsToRectsMap.size() << "` windows." << std::endl;
	std::cout << "Press enter to make them spin." << std::endl;

#pragma warning(suppress:6031)
	std::getchar();

	std::cout << "Spinning began!" << std::endl;

	ULONGLONG timeVar = GetTickCount64();
	const ULONGLONG endTime = timeVar + 5000;

	while (timeVar < endTime) {
		timeVar = GetTickCount64();

		for (auto &element : windowsToRectsMap) {
			const HWND window = element.first;
			RECT rect = element.second;

			GetWindowRect(window, &rect);

			const LONG animTime = timeVar / ULLONG_MAX * SPINWIN_TIME_SCALE;

			MoveWindow(window,
				rect.left + (LONG) (sin(animTime) * SPINWIN_AMP),
				rect.top + (LONG) (cos(animTime) * SPINWIN_AMP),
				rect.right - rect.left,
				rect.bottom - rect.top, true);
		}
	}

}
