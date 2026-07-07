#include "argus.hpp"
auto main(int argc, char** argv) -> int {
    argus::argus argus;
    if (auto result = argus.initialize(argc, argv); !result) {
        std::println("{}", result.error());
    }
    return 0;
}
