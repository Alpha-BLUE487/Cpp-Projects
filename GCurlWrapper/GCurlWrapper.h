#pragma once
#include <Windows.h>
#include <string>
#include <fstream>
namespace Mail
{
	struct MailInfo
	{
		int portnumber;
		std::string hostname;
		std::string senders_address;
		std::string recievers_address;
		std::string senders_password;
		std::string mail_body;

	};

	class Mailer
	{

		MailInfo m_mailinformation;

	public:

		/*This routine takes a mailinformation object as argument and uses this information to
		send mail to the reciever		
		*/
		void sendMail(MailInfo mailinformation);
		

		void recievemail(); // Working On It


	private:
		// Helper functions

        /*This routine takes the location of the file and the string text as its argument from the 
		calling routine and saves the contents of text  in the given file. It returns SUCCESS if
		if was able to open file and FALIURE if the operation was not successful*/
		bool saveToFile(const std::string filepath, std::string& texttosave);
		

		/*This routine sanitizes or removes the occcurences of a given character from the string*/
		void sanitizeString(std::string& input_string, char character_to_remove);
		
		/*This routine outputs the curl command for sending mail by using the m_mailinformation
		of the class. */
		std::string buildCurlCommandString();
		

	};
}
