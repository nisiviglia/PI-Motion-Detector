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
#include <iostream>

/// @brief A constructor that takes in all necessary information to open a connection.
///
/// @param server The FQDN (smtp.example.com) of the SMTP server.
/// @param port Port used by the SMTP server.
/// @param username Username used to authenticate. 
/// @param password Password used to authenticate.
smtp_client::smtp_client(
        std::string server, int port, std::string username, std::string password) 
        : server(server), port(port), username(username), password(password){
        
    //Configure socket connection
    stream.expires_from_now(boost::posix_time::seconds(this->connection_timeout));
}

/// @brief Sends an email to the SMTP server after authentication.
///
/// @param fromAddress Email address of the sender.
/// @param toAddress Email address of the recipient.
/// @param subject Subject of the email.
/// @param message Message body of the email.
///
/// @return  False for success.
bool smtp_client::send(std::string fromAddress, std::string toAddress, 
        std::string subject, std::string message){

    //Connect to SMTP server
    stream.connect(this->server, std::to_string(this->port));
    if (!stream)
    {
        this->connection_output =  stream.error().message();
        return true;
    }

    //Send email
    stream << "HELO relay.example.com\r\n";
    stream << "AUTH LOGIN\r\n";
    stream << username + "\r\n";
    stream << password + "\r\n";
    stream << "MAIL FROM:<" + fromAddress + ">\r\n";
    stream << "RCPT TO:<" + toAddress + ">\r\n";
    stream << "DATA\r\n";
    stream << "From: \"pi-door-alarm\" <door@location>\r\n";
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
    
    //Confirm email was successfully sent
    if(this->connection_output
            .find(this->connection_success_msg) == std::string::npos){

        return true;
    }

    return false;
}

/// @brief Change the default connection timeout metric.
///
/// @param seconds 
void smtp_client::set_connection_timeout_in_seconds(int seconds){
    stream.expires_from_now(boost::posix_time::seconds(seconds));
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

