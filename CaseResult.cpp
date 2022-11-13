#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>
#define caseNum 10
using namespace std;

string path = "input/50A/";

//测试OJ并且保存结果
void getFileCppname(vector<string>& filevec)
{
	string pathstr = path + "listname.txt";
	fstream fin(pathstr.c_str(), ios::in);
	if (!fin) exit(-1);
	while (!fin.eof())
	{
		string s;
		fin >> s;
		s = s.substr(0, s.size() - 4);
		filevec.push_back(s);
	}
	filevec.pop_back();
}
int main()
{
	cout << "file path:" << path << endl;

	vector<string> filenvec, filecppcmd;
	getFileCppname(filenvec);

	for (int i = 0; i < filenvec.size(); i++) {
		string s = "g++ " + path + filenvec[i] + ".cpp -o " + filenvec[i] + ".o";
		filecppcmd.push_back(s);
	}

	for (int i = 0; i < filecppcmd.size(); i++)
	{
		cout << filecppcmd[i] << endl;
		system(filecppcmd[i].c_str());
	}
	cout << "Test result redirection" << endl;
	for (int j = 0; j < caseNum; j++)
	{
		string path_file = to_string(j) + "_input.txt";
		for (int i = 0; i < filenvec.size(); i++)
		{
			string get_output_cmd = "./" + filenvec[i] + ".o <" + path + "in/" + path_file + " >" + path + "out/" + to_string(j) + "_" + filenvec[i] + ".txt 2>&1";
			//cout << get_output_cmd << endl;
			system(get_output_cmd.c_str());
		}
	}
	cout << "Complete the result output" << endl;
	return 0;
}