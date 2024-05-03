#include "stdafx.h"
#include "Anti Leak.h"
//#include <openssl/md5.h>
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <vector>
#pragma comment(lib, "static-release-x86/libcurl_a.lib")
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
	std::vector<std::string> splittedString;
	int startIndex = 0;
	int  endIndex = 0;
	while ((endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size())
	{

		std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();

	}
	if (startIndex < stringToBeSplitted.size())
	{
		std::string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;
}
//==============================================================
bool cAL::Authenticated()
{
	DWORD nSize;
	DWORD nSize2;
	int nSize3;
	DWORD lVolSerialNbr = 0;

	GetVolumeInformation("C:\\", 0, 0, &lVolSerialNbr, 0, 0, 0, 0);


	DWORD HardWareID = lVolSerialNbr;

	int asdf = HardWareID;
#define AddHWIDPerson(HWID)\
	if(asdf == HWID)\
	{\
		return true;\
	}

	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://wakingbots.atwebpages.com/Clientes.txt");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		std::size_t found = readBuffer.find(std::to_string(asdf));
		if (found != std::string::npos)
			return true;
	}
	//AddHWIDPerson(-2035593796); //Victor
	//AddHWIDPerson(-31918725); //Billy


	return false;
}