#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

vector<string> FileData;


static int OperateFile(void);
static void DataProcessing(void);
static string AddOperate(string &s3, string &s4);
static string MinusOperate(string &s3, string &s4);

/* ����Ϊ����ת�����ܺ��� */
vector<char> OutputObjsystemNum;
int InputObjSystem = 10u;
int OutputObjSystem = 10u;

static int JudgeInputParaRange(string &s, char data);
static int Char2Num(char ch);
static char Num2Char(int num);
static string ObjSystem2decimal(string &s, int obj);
static void Decimal2ObjSystem(string s, int obj);
static void TheMoronicCowmpouterOutPrint(string s, int a);


/* feature main function */
void LongIntNumAdd_MainFunc(void)
{
	if (1u == OperateFile())
	{
		return;
	}

	DataProcessing();
}

static int OperateFile(void)
{
	char rawInputObjSystem = 0u;
	char rawOutputObjSystem = 0u;
	int ret = 0u;
	string buf1;
	ifstream file("..\\project2_longIntegerNumAdd\\data.txt");

	if (!file.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		ret = 1u;
	}
	else
	{
		cout << "�ļ��򿪳ɹ�" << endl;

		while (getline(file, buf1))
		{
			FileData.push_back(buf1);
		}
		file.close();

		vector<string>::iterator it = FileData.begin();

		cout << "�ļ�����Ϊ��" << endl;
		while (it != FileData.end())
		{
			cout << *it << endl;
			it++;
		}

		/* ��ȡ��������Ľ��� */
		cout << "��������������ݵĽ��ƣ�" << endl;
		cin >> rawInputObjSystem;
		cout << "������������ֵ�Ľ��ƣ�" << endl;
		cin >> rawOutputObjSystem;

		InputObjSystem = Char2Num(rawInputObjSystem);
		OutputObjSystem = Char2Num(rawOutputObjSystem);

		//cout << InputObjSystem << endl;
		//cout << OutputObjSystem << endl;

		if ((InputObjSystem < 2) || (InputObjSystem > 36) || (OutputObjSystem < 2) || (OutputObjSystem > 36))
		{
			cout << "������Ʋ������󣬳����˳���" << endl;
			ret = 1u;
		}
		else
		{

			if (1 == JudgeInputParaRange(FileData[0], rawInputObjSystem))
			{
				//cout <<"1111��1111��" << FileData[0] << endl;
				ret = 1u;
			}
			else if (1 == JudgeInputParaRange(FileData[1], rawInputObjSystem))
			{

				//cout << "2222��"<< FileData[1] << endl;
				ret = 1u;
			}
			else
			{

			}
		}
	}

	return ret;
}

/* �жϴ������ֵ�͵�ǰѡ���Ľ����Ƿ���� */
static int JudgeInputParaRange(string &s,char data)
{
	int errRet = 0u;
	char *st1 = const_cast<char *>(s.c_str());
 
	for (int i = 0u; i < s.length(); i++)
	{
		cout << st1[i] << endl;

		if (st1[i] >= '0' && st1[i] <= '9')
		{
			if (data <= st1[i])
			{
				cout << "������Ʋ����������ֵ����1�������˳���" << endl;
				errRet = 1;
				return errRet;
			}
			else
			{
				errRet = 0;
			}
		}
		else if (st1[i] >= 'A' && st1[i] <= 'Z')
		{
			if (data <= 'Z')
			{
				if (data <= st1[i])
				{
					cout << "������Ʋ����������ֵ����2�������˳���" << endl;
					errRet = 1;
					return errRet;
				}
				else
				{
					errRet = 0;
				}
			}
			else if ((data - 32) <= st1[i])
			{
				cout << "������Ʋ����������ֵ����3�������˳���" << endl;
				errRet = 1;
				return errRet;
			}
			else
			{
				errRet = 0;
			}
		}
		else if (st1[i] >= 'a' && st1[i] <= 'z')
		{
			if (data <= 'Z')
			{
				if (data <= (st1[i] - 32))
				{
					cout << "������Ʋ����������ֵ����4�������˳���" << endl;
					errRet = 1;
					return errRet;
				}
				else
				{
					errRet = 0;
				}
			}
			else
			{
				if (data <= st1[i])
				{
					cout << "������Ʋ����������ֵ����5�������˳���" << endl;
					errRet = 1;
					return errRet;
				}
				else
				{
					errRet = 0;
				}
			}
		}
		else
		{
			cout << "������ֵ���󣬳����˳���" << endl;
			errRet = 1;
			return errRet;
		}
	}
	return errRet;
}

static void DataProcessing(void)
{
	string rawRetVal;

	/*�ж��������ַ���*/
	if ((FileData[0][0] == '-') && (FileData[1][0] == '-'))
	{
		/* ɾ�������еķ��� */
		FileData[0].erase(0, 1);
		FileData[1].erase(0, 1);

		/* ɾ�������ֵ�0ֵ */
		while (FileData[0][0] == '0')
		{
			FileData[0].erase(0, 1);
		}
		while (FileData[1][0] == '0')
		{
			FileData[1].erase(0, 1);
		}

		cout << "��ӵ�������Ϊ��" << endl;
		cout << "-" << FileData[0] << endl;
		cout << "-" << FileData[1] << endl;

		rawRetVal = AddOperate(FileData[0], FileData[1]);
		//cout << "��ӽ��Ϊ��-" << rawRetVal << endl;
		TheMoronicCowmpouterOutPrint(rawRetVal,0xAA);

	}
	else if ((FileData[0][0] == '-') && (FileData[1][0] != '-'))
	{
		FileData[0].erase(0, 1);
		if (FileData[1][0] == '+')
		{
			FileData[1].erase(0, 1);
		}
		/* ɾ�������ֵ�0ֵ */
		while (FileData[0][0] == '0')
		{
			FileData[0].erase(0, 1);
		}
		while (FileData[1][0] == '0')
		{
			FileData[1].erase(0, 1);
		}

		cout << "��ӵ�������Ϊ��" << endl;
		cout << "-" << FileData[0] << endl;
		cout << FileData[1] << endl;

		if (FileData[1].size() > FileData[0].size())
		{
			rawRetVal = MinusOperate(FileData[1], FileData[0]);

			while (rawRetVal[0] == '0')
			{
				rawRetVal.erase(0, 1);
			}
			//cout << "��ӽ��Ϊ:" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
		}
		else if (FileData[0].size() > FileData[1].size())
		{
			rawRetVal = MinusOperate(FileData[0], FileData[1]);
			//cout << "��ӽ��Ϊ��-" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0xAA);
		}
		else
		{
			if (FileData[0] <= FileData[1])
			{
				rawRetVal = MinusOperate(FileData[1], FileData[0]);
				//cout << "��ӽ��Ϊ��" << rawRetVal << endl;
				TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
			}
			else
			{
				rawRetVal = MinusOperate(FileData[0], FileData[1]);
				//cout << "��ӽ��Ϊ��-" << rawRetVal << endl;
				TheMoronicCowmpouterOutPrint(rawRetVal, 0xAA);
			}
		}
	}
	else if ((FileData[0][0] != '-') && (FileData[1][0] == '-'))
	{
		if (FileData[0][0] == '+')
		{
			FileData[0].erase(0, 1);
		}
		FileData[1].erase(0, 1);
		while (FileData[1][0] == '0')
		{
			FileData[1].erase(0, 1);
		}
		while (FileData[0][0] == '0')
		{
			FileData[0].erase(0, 1);
		}

		cout << "��ӵ�������Ϊ��" << endl;
		cout << FileData[0] << endl;
		cout << "-" << FileData[1] << endl;

		if (FileData[1].size() > FileData[0].size())
		{
			rawRetVal = MinusOperate(FileData[1], FileData[0]);
			while (rawRetVal[0] == '0')
			{
				rawRetVal.erase(0, 1);
			}
			//cout << "��ӽ��Ϊ:-" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0xAA);
		}
		else if (FileData[0].size() > FileData[1].size())
		{
			rawRetVal = MinusOperate(FileData[0], FileData[1]);
			//cout << "��ӽ��Ϊ:" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
		}
		else
		{
			if (FileData[0] >= FileData[1])
			{
				rawRetVal = MinusOperate(FileData[0], FileData[1]);
				while (rawRetVal[0] == '0')
				{
					rawRetVal.erase(0, 1);
				}
				//cout << "��ӽ��Ϊ:" << rawRetVal << endl;
				TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
			}
			else
			{
				rawRetVal = MinusOperate(FileData[1], FileData[0]);
				while (rawRetVal[0] == '0')
				{
					rawRetVal.erase(0, 1);
				}
				//cout << "��ӽ��Ϊ:-" << rawRetVal << endl;
				TheMoronicCowmpouterOutPrint(rawRetVal, 0xAA);
			}
		}
	}
	else
	{
		if (FileData[0][0] == '+')
		{
			FileData[0].erase(0, 1);
		}
		if (FileData[1][0] == '+')
		{
			FileData[1].erase(0, 1);
		}
		while (FileData[0][0] == '0')
		{
			FileData[0].erase(0, 1);
		}
		while (FileData[1][0] == '0')
		{
			FileData[1].erase(0, 1);
		}

		cout << "��ӵ�������Ϊ��" << endl;
		cout << FileData[0] << endl;
		cout << FileData[1] << endl;

		rawRetVal = AddOperate(FileData[0], FileData[1]);


		//cout << "��ӽ��Ϊ��" << rawRetVal << endl;
		TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
	}

}

static string AddOperate(string &s3, string &s4)
{
	
	string s1 = ObjSystem2decimal(s3, InputObjSystem);
	string s2 = ObjSystem2decimal(s4, InputObjSystem);

	int end1 = s1.size() - 1;
	int end2 = s2.size() - 1;
	int carray = 0;
	string ret;

	while (end1 >= 0 || end2 >= 0)
	{
		int a1 = 0;
		int a2 = 0;
		int sum = 0;
		if (end1 >= 0)
		{
			a1 = s1[end1] - '0';
			end1--;
		}
		if (end2 >= 0)
		{
			a2 = s2[end2] - '0';
			end2--;
		}

		sum = a1 + a2 + carray;
		if (sum > 9)
		{
			carray = sum / 10;
			sum = sum % 10;
		}
		else
		{
			carray = 0;
		}
		ret += (sum + '0');
	}
	if (carray > 0)
	{
		char ch = '1';
		ret += ch;
	}
	
	reverse(ret.begin(), ret.end());
	return ret;
}


static string MinusOperate(string &s3, string &s4)
{
	string s1 = ObjSystem2decimal(s3, InputObjSystem);
	string s2 = ObjSystem2decimal(s4, InputObjSystem);

	int end1 = s1.size() - 1;
	int end2 = s2.size() - 1;
	int carray = 0;
	string ret;

	while (end1 >= 0 || end2 >= 0)
	{
		int a1 = 0;
		int a2 = 0;
		int sum = 0;
		if (end1 >= 0)
		{
			a1 = s1[end1] - '0';
			end1--;
		}
		if (end2 >= 0)
		{
			a2 = s2[end2] - '0';
			end2--;
		}

		sum = a1 - a2 - carray;
		if (sum < 0)
		{
			carray = 1;
			sum = sum + 10;
		}
		else
		{
			carray = 0;
		}
		ret += (sum + '0');
	}
	reverse(ret.begin(), ret.end());

	return ret;
}


static string ObjSystem2decimal(string &s, int obj)
{
	string ret;
	stringstream ss;
	long long decimalNum = 0;

	for (int i = 0; i <= s.length() - 1; i++)
	{
		decimalNum = (decimalNum*obj) + Char2Num(s[i]);
	}
	ss << decimalNum;
	ss >> ret;

	return ret;
}

static void Decimal2ObjSystem(string s, int obj)
{
	stringstream ss;
	long long decimalNum;

	ss << s;
	ss >> decimalNum;
	
	while (decimalNum) {
		OutputObjsystemNum.push_back(Num2Char(decimalNum % obj));
		decimalNum = decimalNum / obj;
	}
}


/* ������ʮ���ƺ�����ַ�����ת���ֲ��� */
static int Char2Num(char ch)
{
	if (ch >= '0'&&ch <= '9')
	{
		return ch - '0';
	}
	else if (ch >= 'A' && ch <= 'Z')
	{
		return ch - 'A' + 10;
	}
	else
	{
		return ch - 'a' + 10;
	}
}

/* ������ʮ���ƺ�������ֽ���ת�ַ����� */
static char Num2Char(int num)
{
	if (num >= 0 && num <= 9)
	{
		return (char)('0' + num - 0);
	}
	else if (num >= 'A' && num <= 'Z')
	{
		return (char)('A' + num - 10);
	}
	else
	{
		return (char)('a' + num - 10);
	}
}

static void TheMoronicCowmpouterOutPrint(string s,int a)
{
	Decimal2ObjSystem(s, OutputObjSystem);

	cout << "���������Ϊ" << OutputObjSystem << "���ƣ���ֵΪ:" << endl;
	if (a == 0xAA)
	{	
		cout << "-";
	}
	else
	{

	}

	/* �˴���Ҫ����ȡ�� */
	for (auto it2 = OutputObjsystemNum.rbegin(); it2 != OutputObjsystemNum.rend(); it2++)
	{
		cout << *it2;
	}
	cout << endl;
}