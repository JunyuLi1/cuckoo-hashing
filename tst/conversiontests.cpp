#include <Wordset.hpp>
#include <catch2/catch_amalgamated.hpp>
#include <convert.hpp>
#include <fstream>
#include <string>

namespace {
namespace proj3 = shindler::ics46::project3;

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// You MAY use isValidChange and validConversion in unit tests
// 	(i.e., this file and any other unit tests in this folder you add),
// but you MAY NOT use it in your code otherwise.

bool isValidChange(const std::string &start, const std::string &end) {
    if (start.length() != end.length()) {
        return false;
    }
    int count = 0;
    for (size_t i = 0; i < start.length(); i++) {
        if (start[i] != end[i]) {
            count++;
        }
    }
    return count == 1;
}

bool validConversion(const std::vector<std::string> &conversionPath,
                     const std::string &start, const std::string &end,
                     std::istream &istream) {
    // read word list into std::set<std::string>

    std::set<std::string> words;
    std::string line;
    std::string word;
    std::stringstream strs;

    if (conversionPath.empty()) {
        return false;
    }
    if (start == end and conversionPath.size() == 1 and
        conversionPath[0] == start) {
        return true;
    }
    if (conversionPath[0] != start or
        conversionPath[conversionPath.size() - 1] != end) {
        return false;
    }

    while (istream >> word) {
        words.insert(word);
    }

    for (unsigned i = 0; i < conversionPath.size() - 1; i++) {
        if (!words.contains(conversionPath[i]) ||
            !isValidChange(conversionPath[i], conversionPath[i + 1])) {
            return false;
        }
    }

    return words.contains(conversionPath[conversionPath.size() - 1]);
}

TEST_CASE("Conversion:Ant->Art:ExpectSolution",
          "[Required][Conversion][HasSolution]") {
    const static size_t BASE_CAPACITY = 11;
    proj3::WordSet words(BASE_CAPACITY);
    std::ifstream istream("words.txt");
    proj3::loadWordsIntoTable(istream, words);

    auto conversionPath = proj3::convert("ant", "art", words);

    // this was a success if r was a valid conversion of length 2.
    std::ifstream istream2("words.txt");
    REQUIRE(conversionPath.size() == 2);
    REQUIRE(validConversion(conversionPath, "ant", "art", istream2));
}

TEST_CASE("Conversion:Ant->Eat:ExpectSolution",
          "[Required][Conversion][HasSolution]") {
    const static size_t BASE_CAPACITY = 11;
    proj3::WordSet words{BASE_CAPACITY};
    std::ifstream istream{"words.txt"};
    proj3::loadWordsIntoTable(istream, words);

    auto conversionPath = proj3::convert("ant", "eat", words);

    std::ifstream istream2{"words.txt"};

    REQUIRE(conversionPath.size() == 5);
    REQUIRE(validConversion(conversionPath, "ant", "eat", istream2));
}

TEST_CASE("Conversion:apple->ddddd:ExpectNoSolution",
          "[Required][Conversion][NoSolution]") {
    const static size_t BASE_CAPACITY = 11;
    proj3::WordSet words{BASE_CAPACITY};
    std::ifstream istream{"words.txt"};
    proj3::loadWordsIntoTable(istream, words);

    auto conversionPath = proj3::convert("apple", "ddddd", words);

    std::ifstream istream2{"words.txt"};

    REQUIRE(conversionPath.empty());
    REQUIRE_FALSE(validConversion(conversionPath, "apple", "ddddd", istream2));
}

TEST_CASE("Conversion:reflection->deflection:ExpectSolution",
          "[Required][Conversion][Solution]") {
    const static size_t BASE_CAPACITY = 11;
    proj3::WordSet words{BASE_CAPACITY};
    std::ifstream istream{"words.txt"};
    proj3::loadWordsIntoTable(istream, words);

    auto conversionPath = proj3::convert("reflect", "deflect", words);

    std::ifstream istream2{"words.txt"};

    REQUIRE(conversionPath.size() == 2);
    REQUIRE(validConversion(conversionPath, "reflect", "deflect", istream2));
}

TEST_CASE("Conversion:lead->gold:ExpectSolution",
          "[Required][Conversion][Solution]") {
    const static size_t BASE_CAPACITY = 11;
    proj3::WordSet words{BASE_CAPACITY};
    std::ifstream istream{"words.txt"};
    proj3::loadWordsIntoTable(istream, words);

    auto conversionPath = proj3::convert("lead", "gold", words);

    std::ifstream istream2{"words.txt"};

    REQUIRE(conversionPath.size() == 4);
    REQUIRE(validConversion(conversionPath, "lead", "gold", istream2));
}

TEST_CASE("Part2:loadWords:wordSetWorks",
          "[Part2][LoadWords]") {
    const static size_t BASE_CAPACITY = 11;
    proj3::WordSet words(BASE_CAPACITY);
    std::ifstream istream("words.txt");
    proj3::loadWordsIntoTable(istream, words);
    std::ifstream teststream("words.txt");
    std::string word;
    while (teststream >> word) {
        REQUIRE(words.contains(word));
    }
  REQUIRE(words.capacity() == 411527);
}

}  // namespace
