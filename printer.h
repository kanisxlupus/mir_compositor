//printer.h

#ifndef MCOMP_PRINTER_H
#define MCOMP_PRINTER_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <codecvt>
#include <locale>

namespace mcomp
{
	struct Printer
	{
		Printer();
		~Printer();
		Printer(Printer const&) = delete;
		Printer& operator=(Printer const&) = delete;

		void printer(int32_t width, int32_t height, unsigned char* regionAddress, std::string const& title);
		void footer(int32_t width, int32_t height, unsigned char* regionAddress, std::initializer_list<char const*> const& lines);
	
	private:
		struct Codecvt : std::codecvt_byname<wchar_t, char, std::mbstate_t>
		{
			Codecvt() : std::codecovt_byname<wchar_t, char, std::mbstate_t>("C"){}
			~Codecvt() = default;
		};

		std::wstring_convert<Codecvt> converter;

		FT_Library lib;
		FT_Face face;
	};
}

#endif
