#include "gtest/gtest.h"
#include "../include/smtp_client.hpp"
#include "./smtp_settings.hpp"

// Tests that the smtp_client can successfully send an email.
TEST(smtpClient_test, send_email){
    smtp_settings s;

    smtp_client *client = new smtp_client(
            s.smtp_server, 
            s.smtp_port, 
            s.smtp_username, 
            s.smtp_password);
    client->set_connection_timeout_in_seconds(5);

    bool rc = client->send(
            s.mail_from_address, 
            s.mail_to_address, 
            s.mail_subject, 
            s.mail_msg);
    
    if(rc){client->print_connection_output();}
    delete(client);

    EXPECT_FALSE(rc);
}

// Makes sure that smtp_client fails gracefully when supplied an
// invalid server.
TEST(smtpClient_test, fail_to_send_with_invalid_smtp_server){
    smtp_settings s;

    smtp_client *client = new smtp_client(
            "invaild.example.com", 
            s.smtp_port, 
            s.smtp_username, 
            s.smtp_password);
    client->set_connection_timeout_in_seconds(1);

    bool rc = client->send(
            s.mail_from_address, 
            s.mail_to_address, 
            s.mail_subject, 
            s.mail_msg);
    
    delete(client);

    EXPECT_TRUE(rc);
}

// Makes sure that smtp_client fails gracefully when supplied 
// invalid authentication credentials.
TEST(smtpClient_test, fail_to_send_with_invalid_auth){
    smtp_settings s;

    smtp_client *client = new smtp_client(
            s.smtp_server, 
            s.smtp_port, 
            "invalid_username", 
            s.smtp_password);
    client->set_connection_timeout_in_seconds(1);

    bool rc = client->send(
            s.mail_from_address, 
            s.mail_to_address, 
            s.mail_subject, 
            s.mail_msg);
    
    delete(client);

    EXPECT_TRUE(rc);
}

// Test base 64 encoding
TEST(smtpClient_test, base64_encode){
    smtp_client s("test", 0, "test", "test");
    
    std::string test1 = "testtest";
    std::string encoded_test1 = s.base64_encode(test1);
    EXPECT_TRUE(encoded_test1 == "dGVzdHRlc3Q=");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

