#include <boost/filesystem.hpp>
#include <iostream>

int main() {
    try {
        boost::filesystem::path source("source.txt");
        boost::filesystem::path destination("destination.txt");

        boost::filesystem::copy_file(source, destination);
        std::cout << "File copied successfully!" << std::endl;
    } catch (const boost::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }

    return 0;
}

