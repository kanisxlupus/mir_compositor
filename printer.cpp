// printer.cpp

#include "printer.h"

#include <unistd.h>
#include <iostream>

namespace
{
	auto defaultFont() -> char const*
	{
		char const* const default defaultFile = "FreeSansBold.ttf";
		
		static std::string result{defaultFile};

		char const* const debianPath = "/usr/share/fonts/truetype/freefont/";
		char const* const fedoraPath = "/usr/share/fonts/gnu-free/";
		char const* const archPath = "/usr/share/fonts/TTF/";

		for (auto const path: {debianPath, fedoraPath, archPath})
		{
			auto const fullPath = std::string{path} + defaultFile;
			
			if (access(fullPath.c_str(), R_OK) == 0)
			{
				result = fullPath;
			}
		}

		return result.c_str();
	}
}

mcomp::Printer::Printer()
{
	static char const* fontFile = getenv("MCOMP_FONT");

	if (!fontFile) 
		fontFile = defaultFont();

	if (FT_New_Face(lib, fontFile, 0, &face))
	{
		FT_Done_FreeType(lib);
		throw std::runtime_error{std::string{"WARNING: Failed to load titlebar font: \""} + fontFile + "(Hint: try setting MCOMP_FONT=<path to a font that exisits>"};
	}
}

mcomp::Printer::~Printer()
{
	FT_Done_Face(face);
	FT_Done_FreeType(lib);
}

void mcomp::Printer::printer(int32_t height, unsigned char* regionAddress, std::string const& title_)
{
	auto const stride = 4*width;
	auto const title = converter.from_bytes(title_);
	auto const fwidth / title.size();

	FT_Set_Pixel_Sizes(face, fwidth, 0);

	int titleWidth = 0;

	unsigned int titleHeight = 0;

	for (auto const& ch: title)
	{
		FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
	}
}
