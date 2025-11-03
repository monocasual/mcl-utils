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

#ifndef MONOCASUAL_UTILS_LOG_H
#define MONOCASUAL_UTILS_LOG_H

#include <cstdio>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

namespace mcl::utils::log
{
enum class Mode
{
	DISABLED,
	TO_FILE,
	TO_STDOUT
};
/* -------------------------------------------------------------------------- */

inline FILE* f;
inline bool  stat;
inline Mode  mode;

/* -------------------------------------------------------------------------- */

/* init
Initializes logger. Mode defines where to write the output: LOG_MODE_STDOUT,
LOG_MODE_FILE and LOG_MODE_MUTE. */

int init(const std::string& filePath, Mode mode);

void close();

/* -------------------------------------------------------------------------- */

/* string_to_c_str
Internal utility function for string transformation. Uses forwarding references
(&&) to avoid useless string copy. */

static constexpr auto string_to_c_str = [](auto&& s)
{
	/* Remove any reference and const-ness, since the function can handle
	l-value and r-value, const or not. TODO - Use std::remove_cvref instead,
	when switching to C++20. */
	if constexpr (std::is_same_v<std::remove_const_t<std::remove_reference_t<
	                                 decltype(s)>>,
	                  std::string>)
		// If the argument is a std::string return an old-style C-string
		return s.c_str();
	else
		// Return the argument unchanged otherwise
		return s;
};

/* -------------------------------------------------------------------------- */

/* print
A variadic printf-like logging function. Any `std::string` argument will be
automatically transformed into a C-string. */

template <typename... Args>
static void print(const char* format, Args&&... args)
{
	if (mode == Mode::DISABLED)
		return;

	if (mode == Mode::TO_FILE && stat == true)
	{
		// Replace any std::string in the arguments by its C-string
		std::fprintf(f, format, string_to_c_str(std::forward<Args>(args))...);
#ifdef _WIN32
		fflush(f);
#endif
	}
	else
		std::printf(format, string_to_c_str(std::forward<Args>(args))...);
}

/* -------------------------------------------------------------------------- */

#ifndef NDEBUG
#define ML_DEBUG(x) std::cerr << __FILE__ << "::" << __func__ << "() - " << x << std::endl
#else
#define ML_DEBUG(x) \
	do              \
	{               \
	} while (0)
#endif
} // namespace mcl::utils::log

#endif
