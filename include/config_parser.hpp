#ifndef CONFIG_PARSER
#define CONFIG_PARSER

#include <string>
#include <boost/property_tree/ptree.hpp>

//! A config file parser.
/*! 
  Example usage to get the SMTP server name from the config file: <br>

       config_parser config("full_path_to_config_file"); 
       
       std::string server_name = config.get_str("SMTP.server"); 

       if(server_name == ""){std::cout << "server name not in config file\n"; 

*/
class config_parser{

    public:
        config_parser(std::string filename);

        std::string get_str(std::string path);

        int get_int(std::string path);

        float get_float(std::string path);

    private:
        bool generate_config_file();

        boost::property_tree::ptree tree;

        std::string filename = "";
};

#endif
