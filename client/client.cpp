// Sikuli Vbox Client

// Some codes is got from https://gist.github.com/vivithemage/9517678
// Created by Alec Su
// Created in 2014/10/31
// Last Motify: 2014/11/27
#include <iostream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[])
{
	char url[500], curl_command[550];
	bool down_suc = 0;
	string url_str;
	cout << "Input sikuli script url: ";
	getline(cin, url_str, '\n');
	strcpy_s(url, url_str.c_str());
	cout << "Downloading script...\n";
	sprintf_s(curl_command, "data\\curl\\curl.exe -s -O \"%s\"", url); // Create a command to use in curl
	system(curl_command);// Run curl to download sikuli scripts
	// list all files in current directory.
	//You could put any file path in here, e.g. "/home/me/mwah" to list that directory
	path p(".");

	directory_iterator end_itr;

	// cycle through the directory
	for (directory_iterator itr(p); itr != end_itr; ++itr)
	{
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if (is_regular_file(itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			string current_file_extension = itr->path().extension().string();
			if (current_file_extension == ".skl") // If find any files which extension is .skl 
			{
				cout << "Download finished.\n";
				down_suc = 1;
				break;
			}
		}
	}
	if (down_suc == 1) // If download successful
	{
		cout << "Running Sikuli script...\n";
		system("data\\jre1.8.0_25\\bin\\java.exe -Xms64M -Xmx512M -Dfile.encoding=UTF-8 -Dsikuli.FromCommandLine -jar data\\sikuli\\sikulix.jar -r *.skl"); // Run sikuli script
		system("del *.skl"); //Delete sikuli stript
	}
	else // If download failed
	{
		cout << "Download failed. Please check the url.\n\n";
		cout << "Press any key to exit...";
		_getch();
	}
	return 0;
}