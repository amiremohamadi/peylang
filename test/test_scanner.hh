#ifndef TEST_SCANNER_HH_
#define TEST_SCANNER_HH_

#include <array>
#include <catch.hpp>
#include <fstream>
#include <parser/scanner.hh>
#include <parser/tokens.hh>

TEST_CASE("scanner basic test", "[scanner]") {
  std::ifstream in("sample_file.pey");
  // check if the file is opened correctly
  SECTION("the file is opened correctly") { REQUIRE(in.is_open() == true); }
  // pass ifstream as istream* to the scanner
  pey::Scanner sc(&in);

  // read tokens from the scanner to _tk
  // then compare each token with _expected one
  pey::token _tk;
  std::array<pey::token, 4> _expected = {
      pey::token::T_INT,
      pey::token::T_INT,
      pey::token::T_INT,
      pey::token::T_FLOAT,
  };

  for (auto _tk_expected : _expected) {
    _tk = static_cast<pey::token>(sc.yylex());
    REQUIRE(_tk_expected == _tk);
  }
}

#endif // END TEST_SCANNER_HH_
