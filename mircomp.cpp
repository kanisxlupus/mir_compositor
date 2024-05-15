// main.cpp

#include <miral/runner.h>
#include <miral/append_event_filter.h>
#include <miral/external_client.h>
#include <miral/keymap.h>
#include <miral/minimal_window_manager.h>
#include <miral/set_window_management_policy.h>
#include <miral/toolkit_event.h>
#include <miral/window_manager_tools.h>
#include <miral/window.h>

#include <linux/input.h>
#include <iostream>
#include <sys/types.h>
#include <signal.h>

using namespace miral;
using namespace miral::toolkit;

int main(int argc, char const* argv[])
{
	MirRunner runner{argc, argv};
	
	ExternalClientLauncher extClientLauncher;
	
	bool startupLaunched = false;

	auto const startupActions = [&](MirEvent const* event)
	{
		if (!startupLaunched)
		{
			extClientLauncher.launch("open quickStartGuide.pdf"); 
			startupLaunched = true;
			return true;
		}
		
		return false;
	};

	
	auto const keyboardShortcuts = [&](MirEvent const* event)
	{
		// Check to see if there was an input event
		if (mir_event_get_type(event) != mir_event_type_input)
		{
			return false;
		}

		// Check to see if the input event was a keyboard event
		MirInputEvent const* inputEvent = mir_event_get_input_event(event);
		if (mir_input_event_get_type(inputEvent) != mir_input_event_type_key)
		{
			return false;
		}

		// Check to see if the keyboard event was the button being pressed down
		MirKeyboardEvent const* keyEvent = mir_input_event_get_keyboard_event(inputEvent); 
		if (mir_keyboard_event_action(keyEvent) != mir_keyboard_action_down)
		{
			return false;
		}

		// Check to see if the keyboard event was modified by 'ctrl+alt'
		MirInputEventModifiers mods = mir_keyboard_event_modifiers(keyEvent);
		if(!(mods & mir_input_event_modifier_alt) || !(mods & mir_input_event_modifier_ctrl))
		{
			return false;
		}

		// Perform keyboard shortcut action
		switch(mir_keyboard_event_scan_code(keyEvent))
		{
			case KEY_BACKSPACE:
				runner.stop();
				return true;

			case KEY_T:
				extClientLauncher.launch("weston-terminal");
				return true;
			
			// Open the README again
			case KEY_H:
				extClientLauncher.launch("open quickStartGuide.pdf");
				return true;
		
			case KEY_C:
				extClientLauncher.launch("gnome-chess");

			default:
				return false;
		}
	};

	return runner.run_with(
			{
				set_window_management_policy<MinimalWindowManager>(),
				extClientLauncher,
				AppendEventFilter{startupActions},
				AppendEventFilter{keyboardShortcuts},
				Keymap{},	
			});
}
