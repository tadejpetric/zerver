#include <optional>
#include <stdexcept>
#include <string>

struct prog_settings {
    int in_family;
    std::string address;
    uint16_t port;
};

namespace {
struct prog_settings_opt {
    std::optional<int> in_family;
    std::optional<std::string> address;
    std::optional<uint16_t> port;
};

// trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

template <typename T>
void assign_setting_once(const std::string setting_name, std::optional<T>& setting_ref, T setting_value) {
    if (setting_ref.has_value()) {
        throw std::runtime_error("Setting " + setting_name + " provided multiple times.");
    }

    setting_ref = setting_value;
}

prog_settings all_settings_populated(const prog_settings_opt& settings) {
    return prog_settings{
        .in_family = settings.in_family.value(),
        .address = settings.address.value(),
        .port = settings.port.value(),
    };
}

void populate_setting(prog_settings_opt& opt_settings, const std::string key, const std::string val) {
    if (key == "in_family") {
        int in_family;
        if (val == "AF_INET") {
            in_family = AF_INET;
        } else if (val == "AF_INET6") {
            in_family = AF_INET6;
        } else {
            in_family = std::stoi(val);
        }
        assign_setting_once("in_family", opt_settings.in_family, in_family);
    } else if (key == "address") {
        assign_setting_once("address", opt_settings.address, val);
    } else if (key == "port") {
        uint16_t port = static_cast<uint16_t>(std::stoi(val));
        assign_setting_once("port", opt_settings.port, port);
    }
}

}  // namespace

prog_settings get_settings(const int argc, const char* argv[]) {
    if (argc != 2) {
        throw std::runtime_error("Settings file not provided with arguments.");
    }

    std::ifstream cfg(argv[1]);
    if (!cfg) {
        throw std::system_error(errno,                   // error number reported by ifstream
                                std::system_category(),  // POSIX/windows error code conversion
                                "Failed to open config");
    }

    prog_settings_opt opt_settings{};

    std::string line;
    while (std::getline(cfg, line)) {
        trim(line);
        if (line.empty()) continue;
        auto pos = line.find(':');
        if (pos == std::string::npos) continue;
        std::string key = line.substr(0, pos);
        std::string val = line.substr(pos + 1);
        trim(key);
        trim(val);

        populate_setting(opt_settings, key, val);
    }
    cfg.close();

    return all_settings_populated(opt_settings);
}