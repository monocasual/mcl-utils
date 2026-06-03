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

#ifndef MONOCASUAL_UTILS_MATH_H
#define MONOCASUAL_UTILS_MATH_H

#include <cmath>
#include <concepts>
#include <type_traits>

namespace mcl::utils::math
{
float linearToDB(float f);
float dBtoLinear(float f);

/* -------------------------------------------------------------------------- */

/* quantize
Quantizes 'value' to the nearest multiple of 'step'. Two overloads are provided
because integral and floating-point types need different implementations:
- Integral types use pure integer arithmetic by adding half a step before
  division. This avoids floating-point conversion and rounds to the nearest
  multiple efficiently.
- Floating-point types use the classic floor(x / step + 0.5) formulation,
  which preserves the fractional part during division and performs proper
  rounding in floating-point space. */

template <typename T>
    requires std::integral<T>
constexpr T quantize(T value, T step) noexcept
{
	return ((value + step / T{2}) / step) * step;
}

template <typename T>
    requires std::floating_point<T>
T quantize(T value, T step) noexcept
{
	return step * std::floor((value / step) + T{0.5});
}

/* -------------------------------------------------------------------------- */

/* map (1)
Maps 'x' in range [a, b] to a new range [w, z]. Source:
    https://en.wikipedia.org/wiki/Linear_equation#Two-point_form*/

template <typename TI, typename TO>
constexpr TO map(TI x, TI a, TI b, TO w, TO z)
{
	static_assert(std::is_arithmetic_v<TI>);
	static_assert(std::is_arithmetic_v<TO>);

	if (a == b) // Prevents division by zero (undefined behavior)
		return x;
	return (((x - a) / (double)(b - a)) * (z - w)) + w;
}

/* map (2)
Maps 'x' in range [0, b) to a new range [0, z]. */

template <typename TI, typename TO>
constexpr TO map(TI x, TI b, TO z)
{
	return map(x, static_cast<TI>(0), b, static_cast<TO>(0), z);
}
} // namespace mcl::utils::math

#endif
