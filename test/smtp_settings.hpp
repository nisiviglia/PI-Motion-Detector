#include <string>
/*
 * These are the settings used by smtp_client_test.
*/

using namespace std;

class smtp_settings{

    public:
        string smtp_server = "mail.optonline.net";

        int smtp_port = 587;

        string smtp_username = "TGlGZTAxMA==";

        string smtp_password = "MTAxQzUwMTk=";


        string mail_from_address = "pi@google.com";

        string mail_to_address = "nisiviglia@gmail.com";

        string mail_subject = "Test mail from pi";

        string mail_msg = "This is a test.";
};
