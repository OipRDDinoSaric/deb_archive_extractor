#include <fstream>
#include <filesystem>
#include <iostream>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

#include <boost/iostreams/device/file.hpp>

int main() {
    std::filesystem::path inputFilePath{
            "./text.txt.gz"};
    std::filesystem::path outputFilePath{
            "./text2.txt"};

    std::ifstream inputFileStream(inputFilePath,
                                  std::ios_base::binary);
    boost::iostreams::filtering_istream decompressingStream;

    decompressingStream.push(boost::iostreams::gzip_decompressor());
    decompressingStream.push(inputFileStream);

    std::ofstream outputFileStream{outputFilePath,
                                   std::ios_base::binary};

    outputFileStream << decompressingStream.rdbuf();

    return 0;
}