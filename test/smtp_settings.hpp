#include <string>
/*
 * These are the settings used by smtp_client_test.
*/

using namespace std;

class smtp_settings{

    public:
        string smtp_server = "smtp.example.com";

        int smtp_port = 25;

        string smtp_username = "user";

        string smtp_password = "password";


        string mail_from_address = "from@example.com";

        string mail_to_address = "to@example.com";

        string mail_subject = "Test Subject";

        string mail_msg = "This is a test.";
};
