#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include <Windows.h>

const nana::string c[] = {STR("Page Down"), STR("Test")};

DWORD WINAPI StartHsBot(LPVOID lpThreadParameter)
{
	auto instance = reinterpret_cast<HINSTANCE>(lpThreadParameter);

	nana::form fm;
	nana::place plc(fm);
	plc.div("<items margin=5 gap=5 grid=[3,3]>");

	nana::checkbox cb_talk(fm, STR("Talk"));
	nana::textbox tb_message(fm, STR("Message"));
	nana::spinbox sb_to(fm);
	sb_to.range(0, 10000, 5);

	nana::checkbox cb_skill1(fm, STR("Skill 1"));
	nana::combox cmb_skill1(fm);
	for (auto&& s : c) cmb_skill1.push_back(s);
	nana::label l_skill1(fm, STR("delay in seconds"));

	nana::checkbox cb_skill2(fm, STR("Skill 2"));
	nana::combox cmb_skill2(fm);
	for (auto&& s : c) cmb_skill2.push_back(s);
	nana::label l_skill2(fm, STR("delay in seconds"));

	plc.field("items") << cb_talk << tb_message << sb_to << cb_skill1 << cmb_skill1 << l_skill1 << cb_skill2 << cmb_skill2 << l_skill2;
	plc.collocate();

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
