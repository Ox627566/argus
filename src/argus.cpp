#include "argus.hpp"

#include "utils/cli/parser.hpp"
namespace argus {
    namespace {
        [[nodiscard]] auto check_script(std::string_view script) -> std::expected<void, std::string> {
            namespace fs = std::filesystem;
            fs::path p(script);
            if (!fs::exists(p)) {
                return std::unexpected(std::format("script file not found: ", script));
            }
            if (p.extension() != ".lua") {
                return std::unexpected("file must have a .lua extension");
            }
            if (fs::is_empty(p)) {
                return std::unexpected("you cannot pass an empty script");
            }
            return {};
        }
    }  // namespace
    struct argus::Impl {
        utils::cli::parser parser_;
    };

    argus::argus() : impl_(std::make_unique<Impl>()) {}
    [[nodiscard]] auto argus::initialize(int argc, char** argv) -> std::expected<void, std::string> {
        auto res = impl_->parser_.parse(argc, argv);
        if (!res) {
            return {};
        }
        auto res1 = check_script(res->script_file);

        if (!res1) {
            std::println("{}", res1.error());
        }
        return {};
    }
    argus::~argus() = default;
}  // namespace argus
