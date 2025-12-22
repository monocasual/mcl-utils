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

#ifndef MONOCASUAL_UTILS_VECTOR_H
#define MONOCASUAL_UTILS_VECTOR_H

#include "os.hpp"
#include <algorithm>
#include <ranges>
#include <vector>

namespace mcl::utils::container
{
/* indexOf
Returns the index of element p in container/view 'v'. Returns v.size() if
element is not found. */

template <typename T, typename P>
std::size_t indexOf(const T& v, const P& p)
{
	return static_cast<std::size_t>(std::distance(std::cbegin(v), std::find(std::cbegin(v), std::cend(v), p)));
}

/* -------------------------------------------------------------------------- */

template <typename T, typename F>
auto findIf(T& v, F&& func)
{
	return std::find_if(std::begin(v), std::end(v), func);
}

/* -------------------------------------------------------------------------- */

template <typename T, typename F>
bool hasIf(const T& v, F&& func)
{
	return findIf(v, func) != std::cend(v);
}

template <typename T, typename Target>
bool has(const T& v, const Target& target)
{
	return std::find(std::cbegin(v), std::cend(v), target) != std::cend(v);
}

/* -------------------------------------------------------------------------- */

template <typename T, typename F>
void removeIf(T& v, F&& func)
{
	v.erase(std::remove_if(v.begin(), v.end(), func), v.end());
}

template <typename T, typename V>
void remove(T& v, const V& o)
{
	v.erase(std::remove(v.begin(), v.end(), o), v.end());
}

template <typename T>
void removeAt(T& v, std::size_t index)
{
	v.erase(v.begin() + index);
}

/* -------------------------------------------------------------------------- */

template <typename T, typename I>
std::vector<T> cast(const I& i)
{
	return {i.begin(), i.end()};
}

/* -------------------------------------------------------------------------- */

template <typename Vector, typename Default>
auto atOr(const Vector& v, std::size_t index, Default d)
{
	return index < v.size() ? v[index] : d;
}

/* -------------------------------------------------------------------------- */

template <typename T>
    requires std::integral<T>
constexpr auto range(T n) noexcept
{
	return std::views::iota(T{0}, n);
}

/* -------------------------------------------------------------------------- */

/* enumerate
Simple shim to make 'enumerate' work on Apple Clang, where std::views::enumerate
is not supported yet (end of 2025). */

template <std::ranges::range R>
auto enumerate(R&& r) noexcept
{
#if MCL_OS_MAC
	return std::views::zip(std::views::iota(std::size_t{0}), std::forward<R>(r));
#else
	return std::views::enumerate(std::forward<R>(r));
#endif
}
} // namespace mcl::utils::container

#endif
