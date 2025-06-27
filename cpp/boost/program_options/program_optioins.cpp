#include <iostream>
#include <boost/program_options.hpp>
#include <vector>

using namespace std;
namespace po = boost::program_options;

void print_vm(po::options_description &opts, po::variables_map &vm)
{
    if (vm.empty())
    {
        cout << opts << endl;
        return ;
    }

    if (vm.count("help"))
    {
        cout << opts << endl;
        return ;
    }

    if (vm.count("dir"))
    {
        cout << "dir opt: ";
        for (auto &str : vm["dir"].as<std::vector<string>>())
            cout << str << ", ";
        cout << endl;
    }

    if (vm.count("depth"))
    {
        cout << "depth opt: " << vm["depth"].as<int>() << endl;
    }
}

int main(int argc, char *argv[])
{
    po::options_description opts("demo options");

    string filename;
    opts.add_options()
        ("help,h", "help message\n    a bit of long text")
        ("filename,f", po::value<std::string>(&filename)->default_value("test"), "to find a file")
        ("dir,D", po::value<std::vector<string>>()->multitoken(), "search dir")
        ("depth,d", po::value<int>()->implicit_value(5), "search depth")
        ;
    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, opts), vm);
        po::notify(vm);
    }
    catch(exception &e)
    {
        cout << "exception : " << e.what() << endl;
    }

    print_vm(opts, vm);
}










