/* -----------------------------------------------------------------------------
 *
 * Monocasual Utils
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright (C) 2021-2025 Giovanni A. Zuliani | Monocasual
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

#ifndef MONOCASUAL_UTILS_STRING_H
#define MONOCASUAL_UTILS_STRING_H

#include <string>
#include <vector>

namespace mcl::utils::string
{
std::string replace(std::string in, const std::string& search,
    const std::string& replace);

std::string trim(const std::string& s);

std::vector<std::string> split(const std::string& in, const std::string& sep);

/* contains
Returns true if the string in input contains the specified character. */

bool contains(const std::string&, char);

/* toFloat, toInt
Convert a string to numbers. Like std::stof, std::stoi, just safer. */

float toFloat(const std::string&);
int   toInt(const std::string&);
} // namespace mcl::utils::string

#endif
