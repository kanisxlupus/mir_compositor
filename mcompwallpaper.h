// mcompwallpaper.h

#ifndef MCOMP_WALLPAPER_H
#define MCOMP_WALLPAPER_H

#include <miral/application.h>
#include <miral/window.h>

#include <memory>
#include <mutex>
#include <string>

// Struct for connecting to a Wayland compositor
struct wl_display;

namespace mcomp
{
	class Wallpaper
	{
		public:
			void operator()(wl_display* display);
			void operator()(std::weak_ptr<mir::scene::Session> const& session);

			auto session() const -> std::shared_ptr<mir::scene::Session>;

			void stop();

			// Backgroun color initialization
			void bottom(std::string const& option);
			void top(std::string const& option);

		private:
			std::mutex mutable mutex;
			std::weak_ptr<mir::scene:Session> weak_session;

			uint8_t bottom_color[4] = {0x0a, 0x24, 0x77, 0xFF};
			uint8_t top_color[4] = {0x00, 0x00, 0x00, 0xFF};

			struct Self;
			std::weak_ptr<Self> self;
	};
}

#endif
