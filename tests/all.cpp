#include "src/fs.hpp"
#include "src/id.hpp"
#include "src/math.hpp"
#include "src/string.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("fs")
{
	using namespace mcl::utils::fs;

	REQUIRE(fileExists("nonexistent_file") == false);
	REQUIRE(dirExists("ghost_dir/") == false);
	REQUIRE(isDir("nonexistent_dir") == false);
	// REQUIRE(basename("tests/utils.cpp") == "utils.cpp"); // ????
	REQUIRE(dirname("tests/utils.cpp") == "tests");
	REQUIRE(getExt("tests/utils.cpp") == ".cpp");
	REQUIRE(stripExt("tests/utils.cpp") == "tests/utils");
#if defined(_WIN32)
	REQUIRE(isRootDir("C:\\path\\to\\something") == false);
	REQUIRE(getUpDir("C:\\path\\to\\something") == "C:\\path\\to");
	REQUIRE(getUpDir("C:\\path") == "C:\\");
#else
	REQUIRE(isRootDir("/") == true);
	REQUIRE(isRootDir("/path/to/something") == false);
	REQUIRE(getUpDir("/path/to/something") == "/path/to");
	REQUIRE(getUpDir("/path") == "/");
	REQUIRE(getUpDir("/") == "/");
#endif
}

TEST_CASE("string")
{
	using namespace mcl::utils::string;

	REQUIRE(replace("This is cool", "cool", "hot") == "This is hot");
	REQUIRE(trim("   This is cool       ") == "This is cool");

	std::vector<std::string> v = split("This is cool", " ");
	REQUIRE(v.size() == 3);
	REQUIRE(v.at(0) == "This");
	REQUIRE(v.at(1) == "is");
	REQUIRE(v.at(2) == "cool");
}

TEST_CASE("math")
{
	using namespace mcl::utils::math;

	REQUIRE(map(0.0f, 0.0f, 30.0f, 0.0f, 1.0f) == 0.0f);
	REQUIRE(map(30.0f, 0.0f, 30.0f, 0.0f, 1.0f) == 1.0f);
	REQUIRE_THAT(map(15.0f, 0.0f, 30.0f, 0.0f, 1.0f), Catch::Matchers::WithinAbs(0.5f, 0.001f));

	REQUIRE(map(0.0f, 30.0f, 1.0f) == 0.0f);
	REQUIRE(map(30.0f, 30.0f, 1.0f) == 1.0f);
	REQUIRE_THAT(map(15.0f, 30.0f, 1.0f), Catch::Matchers::WithinAbs(0.5f, 0.001f));
}

TEST_CASE("id")
{
	using namespace mcl::utils;

	Id invalid;
	Id valid{1};

	REQUIRE(invalid.isValid() == false);
	REQUIRE(valid.isValid() == true);
	REQUIRE(valid.getValue() == 1);
	REQUIRE(valid != invalid);
	REQUIRE(valid > invalid);
	REQUIRE(++valid == Id{2});
	REQUIRE(valid++ == Id{2});
	REQUIRE(valid == Id{3});
}