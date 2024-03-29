#include <Wordset.hpp>
#include <catch2/catch_amalgamated.hpp>
#include <convert.hpp>
#include <string>

namespace {
namespace proj3 = shindler::ics46::project3;

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.

TEST_CASE("Hash:dbc:Expect5553", "[Required][Hash]") {
    const static unsigned int BASE = 37;
    const static unsigned int MOD = 100000;
    auto hashValue = proj3::polynomialHashFunction("dbc", BASE, MOD);
    size_t shouldBe = 4 * BASE * BASE + 2 * BASE + 3;
    REQUIRE(hashValue == shouldBe);
}

TEST_CASE("Table:SingleInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("dbc");
    REQUIRE(wordSet.contains("dbc"));
    REQUIRE(wordSet.capacity() == 11);
}

TEST_CASE("Table:MultiInsert:ExpectInTableAndUnchangedCapacity",
          "[Required][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    REQUIRE(wordSet.capacity() == 11);
    REQUIRE(wordSet.size()==8);
}

// this test case is not required, in the sense
// that it is not a prerequisite to grading part 1.
// However, I am providing it in hopes that it helps
// you to test your code.
// The functionality is still needed for full credit!
TEST_CASE("Table:MultiInsertWithResize:ExpectInTableAndResizedTable",
          "[Sample][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    wordSet.insert("wednesday");
    wordSet.insert("thursday");
    wordSet.insert("friday");
    wordSet.insert("saturday");
    wordSet.insert("sunday");
    REQUIRE(wordSet.contains("monday"));
    REQUIRE(wordSet.contains("sunday"));
    REQUIRE(wordSet.capacity() == 23);
    REQUIRE(wordSet.size()==19);
    wordSet.erase("happy");
    REQUIRE_FALSE(wordSet.contains("happy"));
    REQUIRE(wordSet.size()==18);
}

TEST_CASE("ResolvesAtFourEvictions",
          "[Additional][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("a");
    wordSet.insert("hc");
    wordSet.insert("b");
    wordSet.insert("hd");
    wordSet.insert("c");
    wordSet.erase("c");
    REQUIRE(wordSet.size() == 4);
    REQUIRE(wordSet.capacity() == 11);
    wordSet.insert("hb");
    REQUIRE(wordSet.size() == 5);
    REQUIRE(wordSet.capacity() == 11);
}

TEST_CASE("Table:DupliateInsert", "[Extra][Table][Insert]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("dbc");
    REQUIRE(wordSet.contains("dbc"));
    REQUIRE(wordSet.capacity() == 11);
    REQUIRE(wordSet.size() == 1);

    wordSet.insert("dbc");
    REQUIRE(wordSet.capacity() == 11);
    REQUIRE(wordSet.size() == 1);
}

TEST_CASE("Table:MultiInsertWithRemove:ExpectSmallerSizeAfterErase",
          "[Complex][Table][Remove]") {
    const static size_t INITIAL_CAPACITY = 11;
    proj3::WordSet wordSet(INITIAL_CAPACITY);
    wordSet.insert("sleepy");
    wordSet.insert("happy");
    wordSet.insert("dopey");
    wordSet.insert("sneezy");
    wordSet.insert("datalink");
    wordSet.insert("australia");
    wordSet.insert("guacamole");
    wordSet.insert("phylum");
    REQUIRE(wordSet.contains("happy"));
    REQUIRE(wordSet.contains("dopey"));
    wordSet.insert("salsa");
    wordSet.insert("sloth");
    wordSet.insert("colossus");
    wordSet.insert("synergize");
    wordSet.insert("monday");
    wordSet.insert("tuesday");
    wordSet.insert("wednesday");
    wordSet.insert("thursday");
    wordSet.insert("friday");
    wordSet.insert("saturday");
    wordSet.insert("sunday");
    REQUIRE(wordSet.contains("monday"));
    REQUIRE(wordSet.contains("sneezy"));
    REQUIRE(wordSet.contains("colossus"));
    REQUIRE(wordSet.capacity() == 23);
    REQUIRE(wordSet.size() == 19);
    wordSet.erase("happy"); 
    wordSet.erase("colossus"); 
    wordSet.erase("monday"); 
    wordSet.erase("Someone"); 
    REQUIRE(wordSet.size() == 16);
    REQUIRE_FALSE(wordSet.contains("happy"));
    REQUIRE_FALSE(wordSet.contains("colossus"));
    REQUIRE_FALSE(wordSet.contains("monday"));
}

}  // namespace
