// Copyright (C) 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
/// @file smtp_client.cpp
/// @brief A simple SMTP client.
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2017-12-30

#include "../include/smtp_client.hpp"
#include <sstream>
#include <iostream>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>

/// @brief A constructor that takes in all necessary information to open a connection.
///
/// @param server The FQDN (smtp.example.com) of the SMTP server.
/// @param port Port used by the SMTP server.
/// @param username Username used to authenticate. 
/// @param password Password used to authenticate.
smtp_client::smtp_client(
        std::string server, int port, std::string username, std::string password) 
        : server(server), port(port), username(username), password(password){}

/// @brief Sends an email to the SMTP server after authentication.
///
/// @param fromAddress Email address of the sender.
/// @param toAddress Email address of the recipient.
/// @param subject Subject of the email.
/// @param message Message body of the email.
///
/// @return  True for success.
bool smtp_client::send(std::string fromAddress, std::string toAddress, 
        std::string subject, std::string message){
    
    //Init stream
    boost::asio::ip::tcp::iostream stream;
    
    //Configure socket connection
    stream.expires_from_now(boost::posix_time::seconds(this->connection_timeout));

    //Connect to SMTP server
    stream.connect(this->server, std::to_string(this->port));
    if (!stream)
    {
        this->connection_output =  "connection failed: " + stream.error().message();
        return false;
    }
    
    //Send email
    stream << "HELO relay.example.com\r\n";
    stream << "AUTH LOGIN\r\n";
    stream << this->base64_encode(username) + "\r\n";
    stream << this->base64_encode(password) + "\r\n";
    stream << "MAIL FROM:<" + fromAddress + ">\r\n";
    stream << "RCPT TO:<" + toAddress + ">\r\n";
    stream << "DATA\r\n";
    stream << "From: \"alarm\" <alarm@pi.staten>\r\n";
    stream << "To: Person <" + toAddress + ">\r\n";
    stream << "Subject: " + subject + "\r\n";
    stream << "\r\n";
    stream << message + "\r\n";
    stream << ".\r\n";
    stream << "QUIT\r\n";
    stream.flush();

    //Save output from connection 
    this->connection_output = std::string(
            std::istreambuf_iterator<char>(stream.rdbuf()),
            std::istreambuf_iterator<char>());
    
    //Close connection
    stream.close();

    //Confirm email was successfully sent
    if(this->connection_output
            .find(this->connection_success_msg) == std::string::npos){

        return false;
    }

    return true;
}

/// @brief Change the default connection timeout metric.
///
/// @param seconds 
void smtp_client::set_connection_timeout_in_seconds(int seconds){
    this->connection_timeout = seconds;
}

/// @brief Change the text string used to validate that the email was sent.<br>
/// This text string will be searched for in the connection output. <br> 
/// If it is found then the connection is considered a success. <br> 
///
/// Example server success response: <br> 
///     `250 2.0.0 OK AF/B0-03722-16D188B5`
///
/// Example success_msg: <br> 
///     `250 2.0.0 OK`
///
/// @param msg SMTP server response for mail being sent successfully. 
void smtp_client::set_connection_success_msg(std::string msg){
    this->connection_success_msg = msg;
}

/// @brief Print the connection output to the terminal.
void smtp_client::print_connection_output(){
    std::cout << this->connection_output;
}

/// @brief Get the output from the last server connection. 
///
/// @return  A string containing all the server responses from the last connection.
std::string smtp_client::get_connection_output(){
    return this->connection_output;
}

/// @brief converts a string to a base64 string.
///
/// @param input input string to be encoded.
///
/// @return base64 encoded string.
// 
// Credit: itc 
// https://stackoverflow.com/a/28471421
std::string smtp_client::base64_encode(const std::string &val){

	using namespace boost::archive::iterators;
    using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
    return tmp.append((3 - val.size() % 3) % 3, '=');
}

