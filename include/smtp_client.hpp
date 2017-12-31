#ifndef SMTP_CLIENT
#define SMTP_CLIENT

#include <string>
#include <boost/asio.hpp>

//! A simple SMTP client.
/*! 
  Example usage: <br>

       smtp_client *client = new smtp_client(
                               "smtp.example.com",
                               25,
                              "user",
                               "password");
 
       bool rc = client->send(
               "sender@email.com",
               "receiver@email.com,
               "subject",
               "the message.");
 
       if(rc){ std::cout << "error" << std::endl; }
 
       client->print_connection_output();
 
       delete(client);
*/

class smtp_client{

    public:
        smtp_client(
                std::string server, 
                int port, 
                std::string username, 
                std::string password); 

        bool send(
                std::string fromAddress, 
                std::string toAddress, 
                std::string subject, 
                std::string message);

        void set_connection_timeout_in_seconds(int seconds);

        void set_connection_success_msg(std::string msg);

        void print_connection_output();

        std::string get_connection_output();

    private:
            // The iostream used to open the connection to the SMTP server
            boost::asio::ip::tcp::iostream stream;

            // The metric used to timeout a stuck connection
            int connection_timeout = 30;

            // The string of text used to verify that the email was sent successfully.
            // This is done by searching for this string of text in the text output
            // from the connection.
            std::string connection_success_msg = "250 2.0.0 OK ";

            // Holds the text output from the last connection
            std::string connection_output = "";


            // The DQDN of the SMTP server
            std::string server = ""; 

            // Port of the SMTP server
            int port = 0; 

            // Username used to authenticate with the server
            std::string username = ""; 

            // Password used to authenticate with the server
            std::string password = ""; 
};
#endif
