#include <Windows.h>

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/timer.hpp>

#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include "structs.h"

const nana::string keys[] = { STR("Page Down"), STR("Test") };

//TODO: get the updated addy and/or implement an AOB scanner
const uint32_t CWndManPtr = 0x1337;

void SendKey(const uint32_t keycode) {
	auto const ptr = *reinterpret_cast<CWndMan**>(CWndManPtr);
	if (ptr)
	{
		__try
		{
			ptr->OnKey(keycode, (MapVirtualKey(keycode, 0) << 16) + 1);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { }
	}
}

struct autoskill
{
	autoskill(nana::form& form, const nana::string& name)
		: cb(form, name),
		cmb(form),
		lbl(form, STR("delay in seconds")) {
		for (auto&& s : keys) cmb.push_back(s);
	}

	nana::checkbox cb;
	nana::combox cmb;
	nana::label lbl;
};

DWORD WINAPI StartHsBot(LPVOID /*lpThreadParameter*/) {
	nana::timer timer;
	timer.elapse([]
	{
		//TODO: Display msg
		nana::timer tm;
		tm.interval(5000);
		tm.start();
		tm.elapse([&]
		{
			//TODO: send the key(s)
			tm.stop();
		});
	});
	nana::form fm;
	nana::place plc(fm);
	plc.div("<items margin=5 gap=5 grid=[3,3]>");

	nana::checkbox cb_talk(fm, STR("Talk"));
	cb_talk.events().click([&]
	{
		if (cb_talk.checked()) timer.start();
		else timer.stop();
	});

	nana::textbox tb_message(fm, STR("Message"));
	nana::spinbox sb_to(fm);
	sb_to.range(0, 10000, 5);
	sb_to.events().text_changed([&](const nana::arg_spinbox& args)
	{
		timer.interval(args.widget.to_int() * 1000);
	});

	plc.field("items") << cb_talk << tb_message << sb_to;

	std::vector<std::unique_ptr<autoskill>> autoskills;
	for (size_t i = 0; i < 2; i++)
	{
		autoskills.emplace_back(std::make_unique<autoskill>(fm, STR("Skill ") + std::to_wstring(i + 1)));
		auto& as = autoskills.back();
		plc.field("items") << as->cb.handle() << as->cmb.handle() << as->lbl.handle();
	}

	plc.collocate();

	fm.show();
	nana::exec();

	return EXIT_SUCCESS;
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID /*lpvReserved*/) {
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(nullptr, 0, StartHsBot, hinstDLL, 0, nullptr);
	}

	return TRUE;
}


int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int /*nCmdShow*/) {
	return StartHsBot(hInstance);
}
