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

	// For each character in the title, load the glyph, render it, and update the width and height of the title based on that glyph
	for (auto const& ch: title)
	{
		FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
		auto const glyph = face->glyph;
		FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);

		titleWidth += glyph->advance.x >> 6;								// Right shift the bits on the glyph->advance amount by 6
		titleHeight += std::max(titleHeight, glyph->bitmap.rows);			// Pick the largest value between titleHeight and glyph->bitmap.rows
	}

	int base_x = (width - titleWidth)/2;
	int base_y = titleHeight + (height - titleHeight)/2;

	for (auto const& ch : title)
	{
		FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
		auto const glyph = face->glyph;
		FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);

		auto const& bitmap = glyph->bitmap;
		auto const x = base_x + glyph->bitmap_left;

		if (static_cast<int>(x + bitmap.width) <= width)
		{
			unsigned char* src = bitmap.buffer;

			auto const y = base_y - glyph->bitmap_top;
			auto* dest = region_address + y*stride + 4*x;

			for (auto row = 0u; row != bitmap.rows; ++row)
			{
				for (auto col = 0u; col != 4*bitmap.width; ++col)
				{
					dest[col] |= src[col/4];
				}

				src += bitmap.pitch;
				dest += stride;
			}
		
		}

		base_x += glyph->advance.x >> 6;
		base_y += glyph->advance.y >> 6;

	}
}

void egmde::Printer::footer(int32_t width, int32_t height, unsigned char* regionAddress, std::initializer_list<char const*> const& lines)
{
	auto const stride = 4*width;

	int helpWidth = 0;
	unsigned int helpHeight = 0;
	unsigned int lineHeight = 0;

	for (auto const* rawLine : lines)
	{
		int lineWidth = 0;

		auto const line = converter.from_bytes(rawLine);

		auto const fwidth = width / 60;

		FT_Set_Pizel_Sizes(face, fwidth, 0);

		for (auto const& ch : line)
		{
			FT_Load_Glyph(facce, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
			auto const glyph = face->glyph;
			FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);

			lineWidth += glyph->advance.x >> 6;
			lineHeight = std::max(lineHeight, glyph->bitmap.rows + glyph->bitmap.rows/2);
		}

		if (helpWidth < lineWidth)
			helpWidth = lineWidth;

		helpHeight += lineHeight;
	}

	int base_y = (height - helpHeight);

	for (auto const* rawLine : lines)
	{
		int base_x = (width - helpWidth) / 2;

		auto const line = converter.from_bytes(rawLine);

		for (auto const& ch : line)
		{
			FT_Load_Glyph(facce, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT);
			auto const glyph = face->glyph;
			FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
			
			auto const& bitmap = glyph->bitmap;
			auto const x = base_x + glyph->bitmap_left;

			if (static_cast<int>(x + bitmap.width) <= width)
			{
				unsigned char* src = bitmap.buffer;

				auto const y = base_y - glyph->bitmap_top;
				auto* dest = regionAddress + y * stride + 4 * x;

				for (auto row = 0u; row != bitmap.rows; ++row)
				{
					for (auto col = 0u; col != 4 * bitmap.width; ++col)
					{
						unsigned char pixel = (0xaf * src[col / 4]) / 0xff;
						dest[col] = (0xff * pixel + (dest[col] * (0xff - pixel))) / 0xff;
					}

					src += bitmap.pitch;
					dest += stride;

					if (dest > regionAddress + height * stride)
						break;
				}

			}

			base_x += glyph->advance.x >> 6;
		}
		base_y += lineHeight;
	}

}
