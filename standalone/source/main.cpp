#include <pyrange/greeter.h>  // for LanguageCode, LanguageCode::DE, Language...
#include <pyrange/version.h>  // for PYRANGE_VERSION

#include <cxxopts.hpp>    // for value, OptionAdder, Options, OptionValue
#include <iostream>       // for operator<<, endl, basic_ostream, ostream
#include <memory>         // for shared_ptr, __shared_ptr_access
#include <string>         // for string, hash, operator<<, operator==
#include <unordered_map>  // for operator==, unordered_map, _Node_const_i...

auto main(int argc, char** argv) -> int {
    const std::unordered_map<std::string, pyrange::LanguageCode> languages{
        {"en", pyrange::LanguageCode::EN},
        {"de", pyrange::LanguageCode::DE},
        {"es", pyrange::LanguageCode::ES},
        {"fr", pyrange::LanguageCode::FR},
    };

    cxxopts::Options options(*argv, "A program to welcome the world!");

    std::string language;
    std::string name;

    // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result["version"].as<bool>()) {
        std::cout << "PyRange, version " << PYRANGE_VERSION << std::endl;
        return 0;
    }

    auto langIt = languages.find(language);
    if (langIt == languages.end()) {
        std::cerr << "unknown language code: " << language << std::endl;
        return 1;
    }

    // pyrange::PyRange pyrange(name);
    // std::cout << pyrange.greet(langIt->second) << std::endl;

    return 0;
}
