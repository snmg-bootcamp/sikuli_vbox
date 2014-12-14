// Sikuli Vbox Client

// Some codes is got from https://gist.github.com/vivithemage/9517678
// Created by Alec Su
// Created in 2014/10/31
// Last Motify: 2014/11/27
#include <iostream>
#include <cstdlib>
#include <string>
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[])
{
    path sikuli("/Applications/Sikuli-IDE.app/Contents/Resources/Java/sikuli-ide.jar");
    if(!exists(sikuli))
    {
        cout << "Cannot find sikuli.\n" << "Please download sikuli at http://www.sikuli.org/download.html\n";
        return 0;
    }
    char url[500], curl_command[550];
    bool down_suc = 0;
    if (argc == 2)
    {
        strcpy(url, argv[1]);
    }
    else if (argc == 1)
    {
        string url_str;
        cout << "Input sikuli script url: ";
        getline(cin, url_str, '\n');
        strcpy(url, url_str.c_str());
    }
    else
    {
        cout << "Command error!\n";
        return 0;
    }
    sprintf(curl_command, "mkdir tmp; cd tmp; curl -s -O \"%s\"", url); // Create a command to use in curl
    system(curl_command);// Run curl to download sikuli scripts
    // list all files in current directory.
    //You could put any file path in here, e.g. "/home/me/mwah" to list that directory
    path p("./tmp");
    
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
        system("cd tmp; java -Xms64M -Xmx512M -Dfile.encoding=UTF-8 -Dsikuli.FromCommandLine -jar /Applications/Sikuli-IDE.app/Contents/Resources/Java/sikuli-ide.jar -r *.skl"); // Run sikuli script
        system("rm -r -f tmp"); //Delete sikuli stript and tmp directory
    }
    else // If download failed
    {
        cout << "Download failed. Please check the url.\n\n";
    }
    return 0;
}
