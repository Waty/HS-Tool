#include <nana/gui.hpp>
#include <Windows.h>

DWORD WINAPI StartHsBot(LPVOID lpThreadParameter)
{
	HINSTANCE instance = reinterpret_cast<HINSTANCE>(lpThreadParameter);
	nana::form fm;

	fm.show();
	nana::exec();

	return EXIT_SUCCESS;
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID /*lpvReserved*/)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(nullptr, 0, StartHsBot, hinstDLL, 0, nullptr);
	}

	return TRUE;
}


int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/)
{
	return StartHsBot(hInstance);
}
