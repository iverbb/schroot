include(CheckCXXSourceRuns)

function(regex_test outvar)
  check_cxx_source_runs(
"#include <regex>
#include <iostream>

int main() {
  std::regex foo(\"^foo[bar]\$\");
  std::regex bar(\"^foo[bar]\$\", std::regex::extended);
  std::regex chk(\"^[^:/,.][^:/,]*\$\", std::regex::extended);

  std::string test(\"foob\");
  std::string fail(\"fail:\");

  if (!std::regex_search(test, foo)) return 1;
  if (!std::regex_search(test, bar)) return 2;
  if (!std::regex_search(test, chk)) return 3;
  if (std::regex_search(fail, foo)) return 4;
  if (std::regex_search(fail, bar)) return 5;
  if (std::regex_search(fail, chk)) return 6;

  if (!std::regex_match(test, foo)) return 7;
  if (!std::regex_match(test, bar)) return 8;
  if (!std::regex_match(test, chk)) return 9;
  if (std::regex_match(fail, foo)) return 10;
  if (std::regex_match(fail, bar)) return 11;
  if (std::regex_match(fail, chk)) return 12;

  // Checks for broken support in GCC 4.9 and 5.1
  std::regex range1(\"^[a-z0-9][a-z0-9-]*\$\", std::regex::extended);
  std::regex range2(\"^[a-z0-9][-a-z0-9]*\$\", std::regex::extended);
  if (!std::regex_match(test, range1)) return 13;
  if (!std::regex_match(test, range2)) return 14;
  if (!std::regex_match(\"a-\", range1)) return 15;
  if (!std::regex_match(\"a-\", range2)) return 16;
  if (std::regex_match(\"-a\", range1)) return 17;
  if (std::regex_match(\"-a\", range2)) return 18;

  return 0;
}"
${outvar})

  set(${outvar} ${${outvar}} PARENT_SCOPE)
endfunction(regex_test)

regex_test(HAVE_REGEX_REGEX)
if(NOT HAVE_REGEX_REGEX)
      message(FATAL_ERROR "No working regular expression implementation found")
endif()
