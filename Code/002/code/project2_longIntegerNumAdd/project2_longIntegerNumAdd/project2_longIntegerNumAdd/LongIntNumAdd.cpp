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

/* 以下为进制转换功能函数 */
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
		cout << "文件打开失败" << endl;
		ret = 1u;
	}
	else
	{
		cout << "文件打开成功" << endl;

		while (getline(file, buf1))
		{
			FileData.push_back(buf1);
		}
		file.close();

		vector<string>::iterator it = FileData.begin();

		cout << "文件内容为：" << endl;
		while (it != FileData.end())
		{
			cout << *it << endl;
			it++;
		}

		/* 获取输入输出的进制 */
		cout << "请输入待处理数据的进制：" << endl;
		cin >> rawInputObjSystem;
		cout << "请输入输出结果值的进制：" << endl;
		cin >> rawOutputObjSystem;

		InputObjSystem = Char2Num(rawInputObjSystem);
		OutputObjSystem = Char2Num(rawOutputObjSystem);

		//cout << InputObjSystem << endl;
		//cout << OutputObjSystem << endl;

		if ((InputObjSystem < 2) || (InputObjSystem > 36) || (OutputObjSystem < 2) || (OutputObjSystem > 36))
		{
			cout << "输入进制参数错误，程序退出！" << endl;
			ret = 1u;
		}
		else
		{

			if (1 == JudgeInputParaRange(FileData[0], rawInputObjSystem))
			{
				//cout <<"1111，1111！" << FileData[0] << endl;
				ret = 1u;
			}
			else if (1 == JudgeInputParaRange(FileData[1], rawInputObjSystem))
			{

				//cout << "2222！"<< FileData[1] << endl;
				ret = 1u;
			}
			else
			{

			}
		}
	}

	return ret;
}

/* 判断待计算的值和当前选定的进制是否相符 */
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
				cout << "输入进制参数与待计算值不符1，程序退出！" << endl;
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
					cout << "输入进制参数与待计算值不符2，程序退出！" << endl;
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
				cout << "输入进制参数与待计算值不符3，程序退出！" << endl;
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
					cout << "输入进制参数与待计算值不符4，程序退出！" << endl;
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
					cout << "输入进制参数与待计算值不符5，程序退出！" << endl;
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
			cout << "待计算值错误，程序退出！" << endl;
			errRet = 1;
			return errRet;
		}
	}
	return errRet;
}

static void DataProcessing(void)
{
	string rawRetVal;

	/*判断输入数字符号*/
	if ((FileData[0][0] == '-') && (FileData[1][0] == '-'))
	{
		/* 删除首序列的符号 */
		FileData[0].erase(0, 1);
		FileData[1].erase(0, 1);

		/* 删除首数字的0值 */
		while (FileData[0][0] == '0')
		{
			FileData[0].erase(0, 1);
		}
		while (FileData[1][0] == '0')
		{
			FileData[1].erase(0, 1);
		}

		cout << "相加的两组数为：" << endl;
		cout << "-" << FileData[0] << endl;
		cout << "-" << FileData[1] << endl;

		rawRetVal = AddOperate(FileData[0], FileData[1]);
		//cout << "相加结果为：-" << rawRetVal << endl;
		TheMoronicCowmpouterOutPrint(rawRetVal,0xAA);

	}
	else if ((FileData[0][0] == '-') && (FileData[1][0] != '-'))
	{
		FileData[0].erase(0, 1);
		if (FileData[1][0] == '+')
		{
			FileData[1].erase(0, 1);
		}
		/* 删除首数字的0值 */
		while (FileData[0][0] == '0')
		{
			FileData[0].erase(0, 1);
		}
		while (FileData[1][0] == '0')
		{
			FileData[1].erase(0, 1);
		}

		cout << "相加的两组数为：" << endl;
		cout << "-" << FileData[0] << endl;
		cout << FileData[1] << endl;

		if (FileData[1].size() > FileData[0].size())
		{
			rawRetVal = MinusOperate(FileData[1], FileData[0]);

			while (rawRetVal[0] == '0')
			{
				rawRetVal.erase(0, 1);
			}
			//cout << "相加结果为:" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
		}
		else if (FileData[0].size() > FileData[1].size())
		{
			rawRetVal = MinusOperate(FileData[0], FileData[1]);
			//cout << "相加结果为：-" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0xAA);
		}
		else
		{
			if (FileData[0] <= FileData[1])
			{
				rawRetVal = MinusOperate(FileData[1], FileData[0]);
				//cout << "相加结果为：" << rawRetVal << endl;
				TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
			}
			else
			{
				rawRetVal = MinusOperate(FileData[0], FileData[1]);
				//cout << "相加结果为：-" << rawRetVal << endl;
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

		cout << "相加的两组数为：" << endl;
		cout << FileData[0] << endl;
		cout << "-" << FileData[1] << endl;

		if (FileData[1].size() > FileData[0].size())
		{
			rawRetVal = MinusOperate(FileData[1], FileData[0]);
			while (rawRetVal[0] == '0')
			{
				rawRetVal.erase(0, 1);
			}
			//cout << "相加结果为:-" << rawRetVal << endl;
			TheMoronicCowmpouterOutPrint(rawRetVal, 0xAA);
		}
		else if (FileData[0].size() > FileData[1].size())
		{
			rawRetVal = MinusOperate(FileData[0], FileData[1]);
			//cout << "相加结果为:" << rawRetVal << endl;
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
				//cout << "相加结果为:" << rawRetVal << endl;
				TheMoronicCowmpouterOutPrint(rawRetVal, 0x55);
			}
			else
			{
				rawRetVal = MinusOperate(FileData[1], FileData[0]);
				while (rawRetVal[0] == '0')
				{
					rawRetVal.erase(0, 1);
				}
				//cout << "相加结果为:-" << rawRetVal << endl;
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

		cout << "相加的两组数为：" << endl;
		cout << FileData[0] << endl;
		cout << FileData[1] << endl;

		rawRetVal = AddOperate(FileData[0], FileData[1]);


		//cout << "相加结果为：" << rawRetVal << endl;
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


/* 当超过十进制后，需对字符进行转数字操作 */
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

/* 当超过十进制后，需对数字进行转字符操作 */
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

	cout << "相加输出结果为" << OutputObjSystem << "进制；数值为:" << endl;
	if (a == 0xAA)
	{	
		cout << "-";
	}
	else
	{

	}

	/* 此处需要倒序取出 */
	for (auto it2 = OutputObjsystemNum.rbegin(); it2 != OutputObjsystemNum.rend(); it2++)
	{
		cout << *it2;
	}
	cout << endl;
}