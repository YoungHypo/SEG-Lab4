#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>
#define caseNum 10
using namespace std;

string path = "input/50A/";

class Cluster {
	vector<string> blocks;
	string representBlock;
public:
	Cluster(string n) :representBlock(n) { blocks.push_back(n); }
	void insert(string str) { blocks.push_back(str); }
	string getRepresentBlock() { return representBlock; }
	int blockNum() { return blocks.size(); }
	void printCluster(fstream& fin) {
		if (blocks.size() == 1)	return;
		for (int i = 0; i < blocks.size(); i++)
		{
			for (int j = i + 1; j < blocks.size(); j++)
			{
				string stri = path + blocks[i] + ".cpp";
				string strj = path + blocks[j] + ".cpp";
				fin << stri << "," << strj << endl;
				//cout << stri << "/" << strj << endl;
			}
		}
	}
	void printNonEquiv(Cluster& clu, fstream& fin) {
		for (int i = 0; i < blocks.size(); i++)
		{
			for (int j = 0; j < clu.blocks.size(); j++)
			{
				string stri = path + blocks[i] + ".cpp";
				string strj = path + clu.blocks[j] + ".cpp";
				fin << stri << "," << strj << endl;
				//cout << stri << "/" << strj << endl;
			}
		}
	}
};

class CaseTest {
	vector<vector<string> > _output;
	string name;
public:
	CaseTest(string n) :name(n) {}
	void insert(vector<string>& temp) { _output.push_back(temp); }
	string getName() { return name; }
	int getTestNum() { return _output.size(); }
	bool operator==(CaseTest& ct) {
		for (int j = 0; j < _output.size(); j++)
		{
			//单个测试的输出行数都不一样吗，没必要继续了
			if (_output[j].size() != ct._output[j].size()) return false;
			//两个对象对应的测试挨个比较
			for (int i = 0; i < _output[j].size(); i++)
			{
				if (_output[j][i] != ct._output[j][i])return false;
			}
		}
		return true;
	}
	bool operator!=(CaseTest& ct) { return !((*this) == ct); }
};
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
	filevec.pop_back();//会多读一个空行
}
int getIndex_of_CaseTest(vector<CaseTest>& ct, string& n)
{
	int index = -1;
	for (int i = 0; i < ct.size(); i++)
	{
		if (n == ct[i].getName())
		{
			index = i;
			break;
		}
	}
	return index;

}

int main()
{
	cout << "file path:" << path << endl;

	vector<string> filenvec;
	vector<CaseTest> ct;
	vector<Cluster> cluster;

	getFileCppname(filenvec);
	//获取文件名到filenvec
	for (int i = 0; i < filenvec.size(); i++)
	{
		CaseTest temp(filenvec[i]);
		ct.push_back(temp);
	}
	//获取各个OJ程序的输出结果
	for (int j = 0; j < caseNum; j++)
	{
		for (int i = 0; i < ct.size(); i++)
		{
			string path_file = path + "out/" + to_string(j) + "_" + ct[i].getName() + ".txt";
			fstream fin(path_file.c_str(), ios::in);
			if (!fin) exit(-1);
			vector<string> outstr;
			while (!fin.eof())
			{
				string s;
				fin >> s;
				outstr.push_back(s);
			}
			ct[i].insert(outstr);
		}
	}
	Cluster ctmp(ct[0].getName());
	cluster.push_back(ctmp);
	bool cflag = 0;
	//不断更新等价关系，生成等价簇数组ct
	for (int i = 1; i < ct.size(); i++)
	{
		for (int j = 0; j < cluster.size(); j++)
		{
			string repreName = cluster[j].getRepresentBlock();
			int index = getIndex_of_CaseTest(ct, repreName);
			if (ct[i] == ct[index])
			{
				cflag = 1;
				cluster[j].insert(ct[i].getName());
				break;
			}
		}
		if (cflag) {
			cflag = 0;
			continue;
		}
		else {
			Cluster ctmp(ct[i].getName());
			cluster.push_back(ctmp);
		}
	}
	//等价关系
	fstream fin("equal.csv", ios::out | ios::app);
	if (!fin) exit(-1);
	for (int i = 0; i < cluster.size(); i++)
	{
		cluster[i].printCluster(fin);
	}
	fin.close();

	//不等价关系
	fin.open("inequal.csv", ios::out | ios::app);
	if (!fin) exit(-1);
	for (int i = 0; i < cluster.size(); i++)
	{
		for (int j = i + 1; j < cluster.size(); j++)
		{
			cluster[i].printNonEquiv(cluster[j], fin);
		}
	}
	fin.close();

	cout << "Complete equivalence judgments" << endl;
	return 0;
}

/*
	cout << cluster.size() << endl;
	for (int i = 0; i < cluster.size(); i++)
		cout << cluster[i].blockNum() << " ";
	cout << endl;

*/