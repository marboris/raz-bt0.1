#include <filesystem>
#include <fstream>
#include <iostream>
#include <system_error>
#include <array>
#include <cstdint>

namespace fs = std::filesystem;

static constexpr std::string_view EXT_CPP = ".cpp";
static constexpr std::string_view EXT_CC  = ".cc";
static constexpr std::string_view EXT_RO  = ".ro";

static constexpr std::size_t BUF_SIZE = 64 * 1024;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: missing required argument: source .ro file.\nUsage: ./main <source.ro> [<dest|dest/file.cpp>]\n";
        return 1;
    }
    if (argc > 3) {
        std::cerr << "Error: too many arguments; expected at most 2 positional arguments.\n";
        return 2;
    }

    fs::path srcArg = argv[1];
    fs::path outArg = (argc == 3) ? fs::path(argv[2]) : fs::path(".");

    if (srcArg.extension() != fs::path(EXT_RO)) {
        std::cerr << "Invalid input: source file must have the '.ro' extension.\n";
        return 3;
    }

    std::error_code ec;
    if (!fs::exists(srcArg, ec) || ec) {
        std::cerr << "File error: source not found or inaccessible: " << srcArg << "\n";
        return 4;
    }
    if (!fs::is_regular_file(srcArg, ec) || ec) {
        std::cerr << "Type error: source is not a regular file: " << srcArg << "\n";
        return 5;
    }

    std::ifstream in(srcArg, std::ios::binary);
    if (!in) {
        std::cerr << "I/O error: failed to open source for reading (permission denied or I/O failure): " << srcArg << "\n";
        return 6;
    }

    bool outIsFile = false;
    fs::path destPath;
    auto ext = outArg.extension();
    if (!ext.empty()) {
        if (ext == fs::path(EXT_CPP) || ext == fs::path(EXT_CC)) {
            outIsFile = true;
            destPath = outArg;
        } else {
            std::cerr << "Invalid destination: when specifying a filename, extension must be '.cpp' or '.cc'.\n";
            return 7;
        }
    } else {
        outIsFile = false;
    }

    if (!outIsFile) {
        fs::path outDir = outArg;
        if (outDir.empty()) outDir = ".";
        std::error_code ec2;
        fs::create_directories(outDir, ec2);
        if (ec2) {
            std::cerr << "Filesystem error: failed to create or access destination directory '" << outDir << "': " << ec2.message() << "\n";
            return 8;
        }
        destPath = outDir / (srcArg.stem().string() + std::string(EXT_CPP));
    } else {
        fs::path parent = destPath.parent_path();
        if (!parent.empty()) {
            std::error_code ec3;
            fs::create_directories(parent, ec3);
            if (ec3) {
                std::cerr << "Filesystem error: failed to create or access parent directory '" << parent << "': " << ec3.message() << "\n";
                return 9;
            }
        }
    }

    std::error_code ec4;
    fs::path absSrc = fs::absolute(srcArg, ec4);
    fs::path absDest = fs::absolute(destPath, ec4);
    std::cout << "Source: " << absSrc << "\n";
    std::cout << "Destination: " << absDest << "\n";

    std::ofstream out(destPath, std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "I/O error: failed to open destination for writing: " << destPath << "\n";
        return 10;
    }

    std::array<char, BUF_SIZE> buffer;
    while (in) {
        in.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        std::streamsize got = in.gcount();
        if (got > 0) {
            out.write(buffer.data(), got);
            if (!out) {
                std::cerr << "I/O error: write operation failed on destination file.\n";
                return 11;
            }
        }
    }

    in.close();
    out.close();

    std::error_code ec5;
    auto sz = fs::file_size(destPath, ec5);
    if (!ec5) {
        std::cout << "Copy succeeded. Destination size: " << sz << " bytes\n";
    } else {
        std::cout << "Copy succeeded.\n";
    }

    return 0;
}
