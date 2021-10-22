#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/**
信息管理系统：
1、用户输入用户名，系统判断当前数据文件中有没有该用户：
  （1）如果有该用户，则输入对应的密码，输入正确后显示用户信息
  （2）如果没有该用户，则提示是否创建该用户，并根据提示，填写正确的信息
**/

using namespace std;

bool ifStop();
bool ifFind(string user_name);
void addUser(string user_name);

int main() {
	string user_name; //用户名

	while (true)
	{
		cout << "请输入你的名字：";
		cin >> user_name;

		if (!ifFind(user_name)) addUser(user_name);
		if (ifStop()) break;
	}

	return 0;
}

//判断程序是否结束
bool ifStop() {
	char ch;
	cout << "\n是否继续；y/n？: ";
	cin >> ch;

	return ch == 'n'; //只有在输入n的时候才会退出，输入其他字符串的时候，第一个字符不会保存
}

//判断有没有找到目标用户
bool ifFind(string user_name) {
	ifstream infile("userData.txt"); //以读取模式打开

	if (!infile) {
		cerr << "无法打开这个文件";
	}

	bool flag = false; //判断有没有找到
	string line;

	while (getline(infile, line)) {
		//cout << line << endl;

		istringstream ss(line);
		vector<string> words;
		string word;
		while (ss >> word) {
			words.push_back(word);
		}

		if (user_name == words[0]) {
			string tryPwd;
			cout << "你好， " << user_name << endl;
			cout << "请输入查询密码：";
			cin >> tryPwd;
			if (tryPwd == words[1]) cout << "密码正确，手机号是：" << words[2] << endl;
			else cout << "密码错误，请重试";

			flag = true; //找到了
			break;
		}
	}
}

//添加用户信息
void addUser(string user_name) {
	ofstream outfile("userData.txt", ios_base::app); //以追加模式打开
	if (!outfile) cerr << "无法打开这个文件";
	else {
		string pwd;
		string check;
		string phoneNumber;

		cout << "当前用户不存在，请输入密码以创建用户：";
		cin >> pwd;
		cout << "请再次输入密码：";
		cin >> check;
		if (pwd == check) {
			cout << "请输入手机号：";
			cin >> phoneNumber;

			outfile << user_name << ' '
				<< pwd << ' '
				<< phoneNumber
				<< endl;

			cout << "原来的文件里没有，不过我们已经存储了" << endl;
		}
		else {
			cout << "两次密码输入不对，请重新操作" << endl;
		}
	}
}