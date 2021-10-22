#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/**
��Ϣ����ϵͳ��
1���û������û�����ϵͳ�жϵ�ǰ�����ļ�����û�и��û���
  ��1������и��û����������Ӧ�����룬������ȷ����ʾ�û���Ϣ
  ��2�����û�и��û�������ʾ�Ƿ񴴽����û�����������ʾ����д��ȷ����Ϣ
**/

using namespace std;

bool ifStop();
bool ifFind(string user_name);
void addUser(string user_name);

int main() {
	string user_name; //�û���

	while (true)
	{
		cout << "������������֣�";
		cin >> user_name;

		if (!ifFind(user_name)) addUser(user_name);
		if (ifStop()) break;
	}

	return 0;
}

//�жϳ����Ƿ����
bool ifStop() {
	char ch;
	cout << "\n�Ƿ������y/n��: ";
	cin >> ch;

	return ch == 'n'; //ֻ��������n��ʱ��Ż��˳������������ַ�����ʱ�򣬵�һ���ַ����ᱣ��
}

//�ж���û���ҵ�Ŀ���û�
bool ifFind(string user_name) {
	ifstream infile("userData.txt"); //�Զ�ȡģʽ��

	if (!infile) {
		cerr << "�޷�������ļ�";
	}

	bool flag = false; //�ж���û���ҵ�
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
			cout << "��ã� " << user_name << endl;
			cout << "�������ѯ���룺";
			cin >> tryPwd;
			if (tryPwd == words[1]) cout << "������ȷ���ֻ����ǣ�" << words[2] << endl;
			else cout << "�������������";

			flag = true; //�ҵ���
			break;
		}
	}
}

//����û���Ϣ
void addUser(string user_name) {
	ofstream outfile("userData.txt", ios_base::app); //��׷��ģʽ��
	if (!outfile) cerr << "�޷�������ļ�";
	else {
		string pwd;
		string check;
		string phoneNumber;

		cout << "��ǰ�û������ڣ������������Դ����û���";
		cin >> pwd;
		cout << "���ٴ��������룺";
		cin >> check;
		if (pwd == check) {
			cout << "�������ֻ��ţ�";
			cin >> phoneNumber;

			outfile << user_name << ' '
				<< pwd << ' '
				<< phoneNumber
				<< endl;

			cout << "ԭ�����ļ���û�У����������Ѿ��洢��" << endl;
		}
		else {
			cout << "�����������벻�ԣ������²���" << endl;
		}
	}
}