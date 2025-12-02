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

#include <filesystem>
#if defined(_WIN32) // getcwd (unix) or __getcwd (win)
#include <direct.h>
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <climits>
#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <string>
#include <sys/stat.h> // stat (fs::dirExists)
#ifdef __APPLE__
#include <libgen.h> // basename unix
#include <pwd.h>    // getpwuid
#endif
#include "fs.hpp"
#include "string.hpp"

namespace stdfs = std::filesystem;

namespace mcl::utils::fs
{
bool fileExists(const std::string& s)
{
	return stdfs::exists(s);
}

/* -------------------------------------------------------------------------- */

bool isDir(const std::string& s)
{
	return stdfs::is_directory(s);
}

/* -------------------------------------------------------------------------- */

bool dirExists(const std::string& s)
{
	return stdfs::exists(s);
}

/* -------------------------------------------------------------------------- */

bool mkdir(const std::string& s)
{
	return dirExists(s) ? true : stdfs::create_directory(s);
}

/* -------------------------------------------------------------------------- */

std::string getRealPath(const std::string& s)
{
	return s.empty() || !stdfs::exists(s) ? "" : stdfs::canonical(s).string();
}

/* -------------------------------------------------------------------------- */

std::string basename(const std::string& s)
{
	return stdfs::path(s).filename().string();
}

/* -------------------------------------------------------------------------- */

std::string dirname(const std::string& s)
{
	return stdfs::path(s).parent_path().string();
}

/* -------------------------------------------------------------------------- */

std::string getCurrentPath()
{
	return stdfs::current_path().string();
}

/* -------------------------------------------------------------------------- */

std::string getExt(const std::string& s)
{
	return stdfs::path(s).extension().string();
}

/* -------------------------------------------------------------------------- */

std::string stripExt(const std::string& s)
{
	return stdfs::path(s).replace_extension("").string();
}

/* -------------------------------------------------------------------------- */

bool isProject(const std::string& s)
{
	/** TODO - checks too weak. */
	return getExt(s) == ".gprj";
}

/* -------------------------------------------------------------------------- */

std::string getHomePath()
{
#if defined(__linux__) || defined(__FreeBSD__)

	char buf[PATH_MAX];
	snprintf(buf, PATH_MAX, "%s", getenv("HOME"));

#elif defined(_WIN32)

	char buf[MAX_PATH];
	snprintf(buf, MAX_PATH, ".");

#elif defined(__APPLE__)

	char           buf[PATH_MAX];
	struct passwd* pwd = getpwuid(getuid());
	if (pwd == nullptr)
	{
		return "";
	}
	const char* home = pwd->pw_dir;
	snprintf(buf, PATH_MAX, "%s/Library/Application Support", home);

#endif

	return stdfs::path(buf).string();
}

/* -------------------------------------------------------------------------- */

bool isRootDir(const std::string& s)
{
	return stdfs::current_path().root_directory() == s;
}

/* -------------------------------------------------------------------------- */

std::string getUpDir(const std::string& s)
{
#ifdef _WIN32

	// If root, let the user browse the drives list by returning "".
	if (isRootDir(s))
		return "";

#endif

	return stdfs::path(s).parent_path().string();
}

/* -------------------------------------------------------------------------- */

std::string uriToPath(const std::string& uri)
{
	std::string out = uri;
	out             = string::replace(out, "file://", "");
	out             = string::replace(out, "%20", " ");
	return out;
}

/* -------------------------------------------------------------------------- */

std::string join(const std::string& a, const std::string& b)
{
	auto out = stdfs::path(a) / stdfs::path(b);
	return out.string();
}

/* -------------------------------------------------------------------------- */

bool isValidFileName(const std::string& f)
{
#if _WIN32
	const std::vector<char> forbidden = {'<', '>', ':', '"', '/', '\\', '|', '?', '*'};
#else
	const std::vector<char> forbidden = {'/', ':'}; // ':' not supported in macOS
#endif
	for (const char c : forbidden)
		if (utils::string::contains(f, c))
			return false;
	return true;
}
} // namespace mcl::utils::fs
