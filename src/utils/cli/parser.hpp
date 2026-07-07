#pragma once

#include <CLI/CLI.hpp>
namespace argus::utils::cli {
    namespace {
        auto thread_nmber() -> int{
            return std::thread::hardware_concurrency();
        }
    }  // namespace
    class argus_formatter : public CLI::Formatter {
        std::string make_usage(const CLI::App*, std::string name) const override { return "Usage: " + name + " <script.lua> [options]\n"; }
    };
    class parser {
     public:
        parser() : app("") {
            app.formatter(std::make_shared<argus_formatter>());
            app.get_formatter()->label("REQUIRED", "mandatory");
            app.get_formatter()->label("POSITIONALS", "ARGUMENTS");
            app.get_formatter()->label("OPTIONS", "FLAGS");
            app.add_option("script", opt.script_file, "Lua script")->required();
            app.add_option("-t, --threads", opt.threads_number, "threads")
                ->option_text(std::format("[1-{}]",thread_nmber()))
                ->check(CLI::Range(1,thread_nmber()))
                ->default_val(thread_nmber());
        }
        struct options {
            std::string script_file;
            std::size_t threads_number{0};
        };
        [[nodiscard]] auto parse(int argc, char** argv) -> std::expected<options, std::string> {
            try {
                app.parse(argc, argv);
                return opt;
            } catch (const CLI::ParseError& err) {
                std::println("{}", app.help());
                return std::unexpected(err.what());
            }
        }
        ~parser() = default;

     private:
        options opt;
        CLI::App app;
    };
}  // namespace argus::utils::cli
