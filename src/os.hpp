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

#ifndef MONOCASUAL_UTILS_OS_H
#define MONOCASUAL_UTILS_OS_H

#if defined(_WIN32)
#define MCL_OS_WINDOWS 1
#else
#define MCL_OS_WINDOWS 0
#endif

#if defined(__APPLE__)
#define MCL_OS_MAC 1
#else
#define MCL_OS_MAC 0
#endif

#if defined(__linux__)
#define MCL_OS_LINUX 1
#else
#define MCL_OS_LINUX 0
#endif

#if defined(__FreeBSD__)
#define MCL_OS_FREEBSD 1
#else
#define MCL_OS_FREEBSD 0
#endif

#ifndef NDEBUG
#define MCL_DEBUG_MODE 1
#else
#define MCL_DEBUG_MODE 0
#endif

namespace mcl::utils::os
{
}

#endif
