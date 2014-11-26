#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	char url[500],curl_command[550];
	cout << "Input sikuli script url: ";
	cin >> url;
	cout << "Downloading script...\n";
	sprintf(curl_command,"data\\curl\\curl.exe -s -O \"%s\"",url);
	system(curl_command);
	cout << "Download finished.\n";
	cout << "Running Sikuli script...\n";
	system("data\\jre1.8.0_25\\bin\\java.exe -Xms64M -Xmx512M -Dfile.encoding=UTF-8 -Dsikuli.FromCommandLine -jar data\\sikuli\\sikulix.jar -r *.skl");
	system("pause");
	system("del *.skl");
}
