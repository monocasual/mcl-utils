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

#include "os.hpp"
#include <climits>
#include <cstdlib>
#include <filesystem>
#include <string>
#if MCL_OS_MAC
#include <libgen.h> // basename unix
#include <pwd.h>    // getpwuid
#include <unistd.h> // getuid
#endif
#if MCL_OS_WINDOWS
#include <shlobj.h> // SHGetKnownFolderPath
#endif
#include "fs.hpp"
#include "log.hpp"
#include "string.hpp"

namespace stdfs = std::filesystem;

namespace mcl::utils::fs
{
namespace
{
#if MCL_OS_LINUX || MCL_OS_FREEBSD

std::string getEnvVariable_(const char* s)
{
	const char* tmp = getenv(s);
	if (tmp == nullptr)
		return "";
	return {tmp};
}

#endif
} // namespace

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

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

std::string getConfigDirPath()
{
#if MCL_OS_LINUX || MCL_OS_FREEBSD

	/* See https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html
	from issue https://github.com/monocasual/giada/issues/338 */

	const std::string xdgConfigHome = getEnvVariable_("XDG_CONFIG_HOME");
	if (xdgConfigHome != "")
		return xdgConfigHome;

	const std::string home = getEnvVariable_("HOME");
	if (home == "")
	{
		ML_DEBUG("Can't fetch $HOME environment variable\n");
		return "";
	}

	return stdfs::path(home) / ".config";

#elif MCL_OS_WINDOWS

	wchar_t* appdataPathPtr = nullptr;
	auto     result         = SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &appdataPathPtr);
	if (result != S_OK)
	{
		ML_DEBUG("Unable to fetch AppData path\n");
		return "";
	}

	auto appDataPath = std::wstring(appdataPathPtr);

	// It's up to the SHGetKnownFolderPath caller to free appdataPathPtr.
	CoTaskMemFree(static_cast<void*>(appdataPathPtr));

	return appDataPath.string();

#elif MCL_OS_MAC

	char           buf[PATH_MAX];
	struct passwd* pwd = getpwuid(getuid());
	if (pwd == nullptr)
	{
		ML_DEBUG("Unable to fetch user infos\n");
		return "";
	}
	const char* home = pwd->pw_dir;
	snprintf(buf, PATH_MAX, "%s/Library/Application Support", home);

	return stdfs::path(buf).string();

#endif
}

/* -------------------------------------------------------------------------- */

bool isRootDir(const std::string& s)
{
	return stdfs::current_path().root_directory() == s;
}

/* -------------------------------------------------------------------------- */

std::string getUpDir(const std::string& s)
{
#if MCL_OS_WINDOWS

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
#if MCL_OS_WINDOWS
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
