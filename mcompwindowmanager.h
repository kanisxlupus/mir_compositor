// mcompwindowmanager.h

#ifndef MCOMP_WINDOWMANAGER_H
#define MCOMP_WINDOWMANAGER_H

#include <miral/minimal_window_manager.h>

namespace mcomp
{
	class Wallpaper;

	class WindowManager : public miral::MinimalWindowManager
	{
		public:
			WindowManager(miral::WindowManagerTools const& tools, mcomp::Wallpaper const& wallpaper);

			auto PlaceNewWindow(miral::ApplicationInfo const& appInfo, miral::WindowSpecification const& requestedSpecification)
			-> miral::WindowSpecification override;

		private:
			Wallpaper const* const wallpaper;

	};
}

#endif 
