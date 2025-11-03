/* -----------------------------------------------------------------------------
 *
 * Monocasual Utils
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2021 Giovanni A. Zuliani | Monocasual
 *
 * This file is part of Monocasual Utils.
 *
 * Monocasual Utils is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Monocasual Utils is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Giada - Monocasual Utils. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------- */

#include "string.hpp"
#include <climits>
#include <cstdarg>
#include <iomanip>
#include <vector>

namespace mcl::utils::string
{
std::string trim(const std::string& s)
{
	std::size_t first = s.find_first_not_of(" \n\t");
	std::size_t last  = s.find_last_not_of(" \n\t");
	return s.substr(first, last - first + 1);
}

/* -------------------------------------------------------------------------- */

std::string replace(std::string in, const std::string& search, const std::string& replace)
{
	std::size_t pos = 0;
	while ((pos = in.find(search, pos)) != std::string::npos)
	{
		in.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return in;
}

/* -------------------------------------------------------------------------- */

bool contains(const std::string& s, char c)
{
	return s.find(c) != std::string::npos;
}

/* -------------------------------------------------------------------------- */

std::vector<std::string> split(const std::string& in, const std::string& sep)
{
	std::vector<std::string> out;
	std::string              full  = in;
	std::string              token = "";
	std::size_t              curr  = 0;
	std::size_t              next  = -1;
	do
	{
		curr  = next + 1;
		next  = full.find_first_of(sep, curr);
		token = full.substr(curr, next - curr);
		if (token != "")
			out.push_back(token);
	} while (next != std::string::npos);
	return out;
}

/* -------------------------------------------------------------------------- */

float toFloat(const std::string& s)
{
	try
	{
		return std::stof(s);
	}
	catch (const std::exception&)
	{
		return 0.0f;
	}
}

/* -------------------------------------------------------------------------- */

int toInt(const std::string& s)
{
	try
	{
		return std::stoi(s);
	}
	catch (const std::exception&)
	{
		return 0;
	}
}
} // namespace mcl::utils::string
