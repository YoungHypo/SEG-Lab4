#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>
#define caseNum 10
using namespace std;

string path = "input/50A/";

struct DataType {//单个标准输入对应的数据类型
	string type;
	int begin = 0;
	int end = 0;
};
void Disassembly_Txt_file(vector<string>& strvec)//读取标准输入
{
	string pathstr = path + "stdin_format.txt";
	fstream fin(pathstr.c_str(), ios::in);
	if (!fin) exit(-1);
	while (!fin.eof())
	{
		string s;
		fin >> s;
		strvec.push_back(s);
	}
}
void Stringsplit(const string& str, DataType& dt)//字符串分割
{
	if (str == "")		return;
	string strs = str;
	size_t pos = strs.find('(');
	// 若找不到内容则字符串搜索函数返回 npos
	if (pos != strs.npos)
	{
		dt.type = strs.substr(0, pos);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(',');
		dt.begin = stoi(strs.substr(0, pos), 0, 10);

		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(')');
		dt.end = stoi(strs.substr(0, pos), 0, 10);
	}
	else dt.type = strs;
}
int getRandomint(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}
char getRandomchar() {
	int flag = getRandomint(0, 1);
	int num = getRandomint(0, 25);
	return (flag) ? 'a' + num : 'A' + num;
}
void getRandomString(int len, string& str) {

	str = "";
	for (int i = 0; i < len; i++) {
		char s = getRandomchar();
		str.push_back(s);
	}
}
int main()
{
	cout << "file path:" << path << endl;

	srand(time(NULL));
	vector<string> strvec;
	Disassembly_Txt_file(strvec);
	vector<DataType> dtvec;
	//读取标准输入stdin_format.txt
	for (int i = 0; i < strvec.size(); i++)
	{
		DataType dt;
		Stringsplit(strvec[i], dt);
		dtvec.push_back(dt);
	}

	//生成随机数并且将其输入到txt文件中
	for (int j = 0; j < caseNum; j++)
	{
		//打开文件名
		string path_file = path + "in/" + to_string(j) + "_input.txt";
		fstream fin(path_file.c_str(), ios::out);

		//依次生成各个标准输入的随机数
		for (int i = 0; i < dtvec.size(); i++)
		{
			if (i != 0) fin << " ";
			if (dtvec[i].type == "int") {
				int num = getRandomint(dtvec[i].begin, dtvec[i].end);
				fin << num;
			}
			else if (dtvec[i].type == "char") {
				char s = getRandomchar();
				fin << s;
			}
			else if (dtvec[i].type == "string") {
				int len = getRandomint(dtvec[i].begin, dtvec[i].end);
				string str;
				getRandomString(len, str);
				fin << str;
			}
		}
		fin.close();
	}
	cout << "Complete the sample creation" << endl;
	return 0;
}