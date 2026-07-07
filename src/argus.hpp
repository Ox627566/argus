#pragma once

namespace argus {
    class argus {
     public:
        argus();
        [[nodiscard]] auto initialize(int argc, char** argv) -> std::expected<void, std::string>;
        ~argus();

     private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}  // namespace argus
