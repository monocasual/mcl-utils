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

#ifndef MONOCASUAL_UTILS_ID_H
#define MONOCASUAL_UTILS_ID_H

#include <cassert>
#include <cstddef>
#include <ostream>

namespace mcl::utils
{
class Id
{
public:
	/* Constructor (1, default)
	Creates an invalid ID. */

	constexpr Id() noexcept = default;

	/* Constructor (2)
	Creates a regular ID. Must be greater than 0. */

	explicit constexpr Id(std::size_t v) noexcept
	: m_value(v)
	{
		assert(v > 0);
	}

	/* Constructor (3)
	Takes an enum class as parameter. Useful when you want to make an ID out of
	an existing enum class element. */

	template <typename EnumClass>
	    requires std::is_enum_v<EnumClass>
	explicit Id(EnumClass e) noexcept
	: Id(static_cast<std::size_t>(e))
	{
	}

	static constexpr Id makeInvalid() noexcept { return Id(); }

	constexpr bool        isValid() const noexcept { return m_value > 0; }
	constexpr std::size_t getValue() const noexcept { return m_value; }

	/* Operator ==([enum class])
	Special overload of operator == to allow comparing an Id with an enum class
	element. */

	template <typename EnumClass>
	    requires std::is_enum_v<EnumClass>
	constexpr bool operator==(EnumClass e) const
	{
		return m_value == static_cast<std::size_t>(e);
	}

	constexpr bool operator==(const Id&) const noexcept  = default;
	constexpr auto operator<=>(const Id&) const noexcept = default;

	constexpr Id operator+(const Id& o) const noexcept
	{
		return Id(m_value + o.m_value);
	}

	constexpr Id operator+(std::size_t n) const noexcept
	{
		return Id(m_value + n);
	}

	constexpr Id& operator++() noexcept // ++id
	{
		++m_value;
		return *this;
	}

	constexpr Id operator++(int) noexcept // id++
	{
		Id tmp{*this};
		++(*this);
		return tmp;
	}

	friend std::ostream& operator<<(std::ostream& out, const Id& id)
	{
		out << id.m_value;
		return out;
	}

private:
	std::size_t m_value{0};
};
} // namespace mcl::utils

/* std::hash<mcl::utils::Id>
Provide std::hash specialization for Id, so you can use Id as a key for e.g.
std::unordered_map. */

namespace std
{
template <>
struct hash<mcl::utils::Id>
{
	std::size_t operator()(const mcl::utils::Id& id) const noexcept
	{
		return std::hash<std::size_t>{}(id.getValue());
	}
};
} // namespace std

#endif
