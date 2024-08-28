#include <cstdlib>
#include <fmt/ostream.h>
#include <iostream>
#include <filesystem>
#include <sstream>

namespace Extraction
{
void
extractDebPackageRaw(std::filesystem::path& inputFile, std::filesystem::path& outputFolder)
{
    std::string extractPackageCommand {};
    {
        std::stringstream sStream {};
        sStream << "ar x --output " << outputFolder << " " << inputFile;

        extractPackageCommand = sStream.str();
    }

    fmt::println("Debug: {}", extractPackageCommand);
    int errorStatus {std::system(extractPackageCommand.c_str())};
    if (EXIT_SUCCESS != errorStatus)
    {
        exit(errorStatus);
    }
}

void
unpackFileWithNameStartingWith(std::filesystem::path& outputFolder, std::string_view fileNameStart)
{
    std::filesystem::directory_iterator outputFolderIter {outputFolder};

    const auto isFileNameControl {
    [fileNameStart](const auto& candidate)
    {
        return candidate.path().filename().string().starts_with(fileNameStart);
    }};
    const auto controlFileIter {std::ranges::find_if(outputFolderIter, isFileNameControl)};
    if (end(outputFolderIter) == controlFileIter)
    {
        exit(EXIT_FAILURE);
    }

    if (!controlFileIter->path().has_extension())
    {
        fmt::println("Debug: Control is not archived.");
        return;
    }

    const auto controlArchive {controlFileIter->path()};

    std::string unpackCommand {};
    {
        std::stringstream sStream {};

        sStream << "tar -xf " << controlArchive << " --directory " << outputFolder << " && "
                << "rm " << controlArchive;
        unpackCommand = sStream.str();
    }

    fmt::println("Debug: {}", unpackCommand);

    int errorStatus {std::system(unpackCommand.c_str())};
    if (EXIT_SUCCESS != errorStatus)
    {
        exit(errorStatus);
    }
}
}  // namespace Extraction

int
main(int numberOfArguments, char* arguments[])
{
    if (numberOfArguments != 3)
    {
        fmt::println(std::cerr,
                     "Error: invalid usage. Two arguments expected.\n"
                     "Valid usage: DebArchiveExtractor <path to input DEB package> <directory "
                     "where extracted data is placed>");
        return EXIT_FAILURE;
    }

    std::filesystem::path inputFile {canonical(std::filesystem::absolute(arguments[1]))};
    std::filesystem::path outputFolder {arguments[2]};

    if (!is_regular_file(inputFile))
    {
        fmt::println(std::cerr, "Error: First argument must be a file.");
        return EXIT_FAILURE;
    }

    if (!exists(outputFolder) || !is_directory(outputFolder))
    {
        fmt::println(std::cerr, "Error: Second argument must be an existing directory.");
        return EXIT_FAILURE;
    }

    Extraction::extractDebPackageRaw(inputFile, outputFolder);
    Extraction::unpackFileWithNameStartingWith(outputFolder, "control");
    Extraction::unpackFileWithNameStartingWith(outputFolder, "data");

    return EXIT_SUCCESS;
}