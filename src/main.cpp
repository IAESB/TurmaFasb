#include <iostream>
#include <boost/program_options.hpp>
#include <thread>
#include "optionsargs.h"
#include "basesync.h"
#include "servermanager.h"

using namespace std;

enum ExitReturn{
    SUCCESS=0,
    SUCCESS_IN_COMMAND_LINE=1,
    ERROR_IN_COMMAND_LINE=2,
    ERROR_IN_FILE_LOCK=3,
    ERROR_UNHANDLED_EXCEPTION=4,
};

OptionsArgs process_command_line(int argc, char** argv);

int main(int argc, char** argv)
{
    try{
        OptionsArgs options = process_command_line(argc, argv);

        std::cout << "Using port: " << options.port << endl;
        std::cout << "Using webDir: " << options.webDir << endl;

        ServerManager server(options);
        server.start();

        while(true){
            std::this_thread::sleep_for(chrono::seconds(1));
        }

        server.stop();

    }catch(exception& ex){
        std::cerr << "Unhandled Exception reached the top of main: "
                  << ex.what() << ", application will now exit" << std::endl;
        return ExitReturn::ERROR_UNHANDLED_EXCEPTION;
    }

    return ExitReturn::SUCCESS;
}

OptionsArgs process_command_line(int argc, char** argv)
{
    namespace po = boost::program_options;
    OptionsArgs opc;
    po::options_description desc("Options");

    desc.add_options()
            ("help,h", "Print help messages")
            ("port,p", po::value<int>()->default_value(4567), "<PORT> set port to open socket.")
            ("webdir,w", po::value<string>()->default_value("../www"), "<PATH_DIR> set dir to web content.")
            ("conction-database,c", po::value<string>()->required(), "<URL> REQUERID conection of data base. Ex.: \"mysql://host=localhost db=mydatabase user=root password=root\"")
            ("conction-mentor,m", po::value<string>(), "<URL> conection of data base of Mentor.")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc),
        vm); // can throw

    if (vm.count("help") || argc==1)
    {
        std::cout << "Basic Command Line Parameter App" << std::endl
                  << desc << std::endl;
//        std::exit(ExitReturn::SUCCESS);
    }
    if (vm.count("port"))
    {
        opc.port = vm["port"].as<int>();
    }
    if (vm.count("webdir"))
    {
        opc.webDir = vm["webdir"].as<string>();
    }
    if (vm.count("conction-database"))
    {
        opc.database = vm["conction-database"].as<string>();
    }
    if (vm.count("conction-mentor"))
    {
        opc.mentor = vm["conction-mentor"].as<string>();
    }
    
    
    po::notify(vm); // throws on error, so do after help in case there are any problems

    return opc;
}


