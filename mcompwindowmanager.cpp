// mcompwindowmanager.cpp

#include "mcompwindowmanager.h"
#include "mcompwallpaper.h"
#include <miral/application_info.h>

mcomp::WindowManager::WindowManager(miral::WindowManagerTools const& tools, mcomp::Wallpaper const& wallpaper) :
	MinimalWindowManager{tools},
	wallpaper{&wallpaper}
{
}

auto mcomp::WindowManager::PlaceNewWindow(
		miral::ApplicationInfo const& appInfo,
		miral::WindowSpecification const& requestedSpecification) -> miral::WindowSpecification
{
	auto result = MinimalWindowManager::PlaceNewWindow(appInfo, requestedSpecification);

	if (appInfo.application() == wallpaper->session())
	{
		// Set the resulting type ourselves
		result.type() = mir_window_type_decoration;
	}

	return result
}
