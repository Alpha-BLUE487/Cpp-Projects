// GCurlWrapTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
namespace Mail
{
	struct MailInfo
	{
		std::string hostname;
		int portnumber;
		std::string senders_address;
		std::string recievers_address;
		std::string senders_password;
		std::string mail_body;

	};
	class Mailer
	{

		MailInfo m_mailinformation;

	public:

		void sendMail(MailInfo mailinformation)
		{
			m_mailinformation = mailinformation;
			//std::string command_string = "curl --url \"smtps://smtp.gmail.com:465\" --ssl-reqd --mail-from \"cosmogopi487@gmail.com\" --mail-rcpt \"krishnagopi487@gmail.com\" --upload-file master.txt --user \"cosmogopi487@gmail.com:gopi@487\"";
			std::string command_string = buildCurlCommandString();
			//Debug
			std::cout << command_string;

			WinExec(command_string.c_str(), SW_HIDE);
		}
		void recievemail() {} // TODO


	private:
		bool saveToFile(const std::string filepath, std::string& texttosave)
		{

			// Try to create a file in the given path
			std::ofstream file(filepath);
			// if file is opened then copy the entire data to the file
			if (file.is_open())
			{
				file << texttosave;
			// close the file
				file.close();
			// return SUCCESS to the calling routine
				return true;
			}
			// if file is not opened then return FALIURE to the calling routine
			return false;

		}
		std::string buildCurlCommandString()
		{
			const std::string QUOT = "\"";
			 std::string curl_command_string;
			
			 // Append curl command to string 
			curl_command_string.append("curl ");
					   			 		  
			 // Append --url command to string
			curl_command_string.append("--url ");
			 // Append "smtps://" to string
			curl_command_string.append(QUOT+"smtps://");
			 // Append host name along with the port number seperated by a colon
			curl_command_string.append(m_mailinformation.hostname+":"+std::to_string(m_mailinformation.portnumber)+QUOT);
			 //  Append --ssl-reqd command for performing TLS Handshake Compulsory
			curl_command_string.append(" --ssl-reqd ");
			 // Append --mail-from with senders address 
			curl_command_string.append("--mail-from "+QUOT+m_mailinformation.senders_address+QUOT);
			 // Append --mail-rcptv with recievers address 
			curl_command_string.append(" --mail-rcpt "+QUOT+m_mailinformation.recievers_address+QUOT);
			 // Append the body of the Mail Messaage by first storing the file then adding its path as a command to curl
			saveToFile("master.txt",m_mailinformation.mail_body);
			curl_command_string.append(" --upload-file master.txt");
			 // Append --user along with senders mail address with password seperated by a colon
			curl_command_string.append(" --user "+QUOT+m_mailinformation.senders_address+":"+m_mailinformation.senders_password+QUOT);
			
			return curl_command_string;
			
			  
		}

	};
}
int main()
{
	Mail::MailInfo mail_information;
 	mail_information.portnumber =465;
	mail_information.hostname = "smtp.gmail.com";
	mail_information.senders_address = "X";
	mail_information.recievers_address = "Y";
	mail_information.mail_body = "Hello World!";
	mail_information.senders_password = "ENTER PASSWORD";


	Mail::Mailer mail;
	mail.sendMail(mail_information);

	//std::string command = "curl --url \"smtps://smtp.gmail.com:465\" --ssl-reqd --mail-from \"cosmogopi487@gmail.com\" --mail-rcpt \"krishnagopi487@gmail.com\" --upload-file master.txt --user \"cosmogopi487@gmail.com:gopi@487\"";
	//std::cout << command;
	//WinExec(command.c_str(), SW_HIDE);

	std::cin.get();
    
}

