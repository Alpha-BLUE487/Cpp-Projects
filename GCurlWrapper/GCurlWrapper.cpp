// GCurlWrapper.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "GCurlWrapper.h"

void Mail::Mailer::sendMail(MailInfo mailinformation)
{
	
		m_mailinformation = mailinformation;
		//std::string command_string = "curl --url \"smtps://smtp.gmail.com:465\" --ssl-reqd --mail-from \"cosmogopi487@gmail.com\" --mail-rcpt \"krishnagopi487@gmail.com\" --upload-file master.txt --user \"cosmogopi487@gmail.com:gopi@487\"";
		std::string command_string = buildCurlCommandString();

		// Execute the command string with window hidden
		WinExec(command_string.c_str(), SW_HIDE);
	

}

void Mail::Mailer::recievemail()
{

}

bool Mail::Mailer::saveToFile(const std::string filepath, std::string& texttosave)
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

void Mail::Mailer::sanitizeString(std::string& input_string, char character_to_remove)
{
	
		// Get the first position of this character in the given string
		auto character_position = input_string.find(character_to_remove);

		// Till the string reaches the end or all the occurences of given character are removed
		while (character_position != std::string::npos)
		{
			// Remove the character at the given position
			input_string.erase(character_position);
			// Move to next occurence if available
			character_position = input_string.find(character_to_remove, character_position + 1);
		}
	

}

std::string Mail::Mailer::buildCurlCommandString()
{
	
		const std::string QUOT = "\"";
		std::string curl_command_string;

		// Append curl command to string 
		curl_command_string.append("curl ");

		// Append --url command to string
		curl_command_string.append("--url ");
		// Append "smtps://" to string
		curl_command_string.append(QUOT + "smtps://");
		// Append host name along with the port number seperated by a colon
		curl_command_string.append(m_mailinformation.hostname + ":" + std::to_string(m_mailinformation.portnumber) + QUOT);
		//  Append --ssl-reqd command for performing TLS Handshake Compulsory
		curl_command_string.append(" --ssl-reqd ");
		// Append --mail-from with senders address 
		curl_command_string.append("--mail-from " + QUOT + m_mailinformation.senders_address + QUOT);
		// Append --mail-rcptv with recievers address 
		curl_command_string.append(" --mail-rcpt " + QUOT + m_mailinformation.recievers_address + QUOT);
		// Append the body of the Mail Messaage by first storing the file then adding its path as a command to curl
		std::string attachment_filename = m_mailinformation.senders_address;
		sanitizeString(attachment_filename, '@');
		saveToFile(attachment_filename, m_mailinformation.mail_body);
		curl_command_string.append(" --upload-file " + attachment_filename);
		// Append --user along with senders mail address with password seperated by a colon
		curl_command_string.append(" --user " + QUOT + m_mailinformation.senders_address + ":" + m_mailinformation.senders_password + QUOT);

		return curl_command_string;
	
}
