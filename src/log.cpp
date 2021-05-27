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

#include "log.h"
#include <cstdio>
#include <string>

namespace mcl::utils::log
{
int init(const std::string& filePath, Mode m)
{
	mode = m;
	stat = true;
	if (mode == Mode::FILE)
	{
		f = std::fopen(filePath.c_str(), "a");
		if (!f)
		{
			stat = false;
			return 0;
		}
	}
	return 1;
}

/* -------------------------------------------------------------------------- */

void close()
{
	if (mode == Mode::FILE)
		std::fclose(f);
}
} // namespace mcl::utils::log
