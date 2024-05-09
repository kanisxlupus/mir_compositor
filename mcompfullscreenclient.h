#ifndef MCOMP_MCOMPFULLSCREENCLIENT_H
#define MCOMP_MCOMPFULLSCREENCLIENT_H

#include <mir/fd.h>
#include <mir/geometry/rectangles.h>

#include <wayland-client.h>

#include <functional>
#include <map>
#include <memory>
#include <mutex>

struct xkb_context;
struct xkb_keymap;
struct xkb_state;

namespace mcomp
{
	class FullscreenClient
	{
		public:
			explicit FullscreenClient(wl_display* display);

			virtual ~FullscreenCllient();

			void run(wl_display* display);

			void stop();

			auto makeShmPool(size_t size, void** data) const
				-> std::unique_ptr<wl_shm_pool, void (*)(wl_shm_pool*)>;

			wl_display* display = nullptr;
			wl_compositor* compositor = nullptr;
			wl_shell* shell = nullptr;

			class Output
			{	
				public:
					Output(wl_output* output, std::function<void(Output const&)> onConstructed, std::function<void(Output const&)> onChange);
					~Output();

					Output(Output const&) = delete;

					Output(Output&&) = delete;



			}

	}

}
