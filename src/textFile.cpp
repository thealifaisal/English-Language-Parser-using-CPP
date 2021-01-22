// extract first ocurring words from each line.
// example of line:
// 		word	<meaning> | <examples>

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream inFile;
	ofstream outFile;
	
	inFile.open("Verbs.txt", ios::in);
	outFile.open("Verbs1.txt", ios::out);
	
	string line, ch = "";
	
	int i=0;
	
	while(!inFile.eof())
	{
		getline(inFile, line);
		
//		cout<<line<<"\n";
		
		while(line[i] != '\t')
		{
			ch = ch + line[i];
			
			i++;
		}
		
		cout<<ch<<"\n";
		outFile<<ch<<"\n";
		
		ch = "";
		i=0;
	}
	
	outFile.close();
	inFile.close();
	
	return 0;
}
