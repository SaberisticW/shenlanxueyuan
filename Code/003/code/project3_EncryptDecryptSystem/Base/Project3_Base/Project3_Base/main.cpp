#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

string LowercaseAB = "abcdefghijklmnopqrstuvwxyz";
string MajusculeAB = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int getFileSize(char const *path);
static string readFileIntoString(char const* filename);

void EncryptFile(char const *clearTextPath, char const *codeBookPath, char const *cipherTextPath);
void DecryptFile(char const *cipherTextPath, char const *codeBookPath, char const *decryptFilepath);

int main()
{
	int operateType = 0;
	char const *codeBookPath = "..\\Project3_Base\\codebook.txt";
	char const *clearTextPath = "..\\Project3_Base\\cleartext.txt";
	char const *cipherTextPath = "..\\Project3_Base\\ciphertext.txt";
	char const *newDecryptFilepath = "..\\Project3_Base\\decrypttext.txt";
	string outStr;

	cout << "运行加密文件程序，请输入1。运行解密文件程序，请输入2 ：" << endl;
	cin >> operateType;

	if (1 == operateType)
	{
		EncryptFile(clearTextPath, codeBookPath, cipherTextPath);
		outStr = readFileIntoString(cipherTextPath);
		cout << "加密后的 ciphertext 内容为:" << endl;
		cout << outStr << endl;
	}
	else if (2 == operateType)
	{
		DecryptFile(cipherTextPath, codeBookPath, newDecryptFilepath);
		outStr = readFileIntoString(newDecryptFilepath);
		cout << "解密后的 decrypttext 内容为:" << endl;
		cout << outStr << endl;
	}
	else
	{
		cout << "输入错误，程序退出！" << endl;
	}
	
	system("pause");

	return 1;
}

void EncryptFile(char const *clearTextPath, char const *codeBookPath,char const *cipherTextPath)
{
	int i = 0;
	FILE *pfr, *pfw,*pcode;

	fopen_s(&pfr, clearTextPath, "rb");
	fopen_s(&pfw, cipherTextPath, "wb");
	fopen_s(&pcode, codeBookPath, "rb");
	
	if (pfr == NULL || pfw == NULL)
	{

		fclose(pfr);
		fclose(pfw);
		fclose(pcode);

	}
	else
	{
		int length = getFileSize(clearTextPath);
		char *p = (char *)malloc(length * sizeof(char));
		string codeStr;
		int index;

		fread(p, sizeof(char), length, pfr);
		
		codeStr = readFileIntoString(codeBookPath);

		for (i = 0; i < length; i++)
		{
			if (p[i] >= 'a' && p[i] <= 'z')
			{
				index = LowercaseAB.find_first_of(p[i]);
				p[i] = codeStr[index];

			}
			else if (p[i] >= 'A' && p[i] <= 'Z')
			{
				index = MajusculeAB.find_first_of(p[i]);
				p[i] = codeStr[index] - 32;
			}
			else
			{

			}
		}	
		fwrite(p, sizeof(char), length, pfw);

		fclose(pfr);
		fclose(pfw);
		fclose(pcode);
	}

}

void DecryptFile(char const *cipherTextPath, char const *codeBookPath, char const *decryptFilepath)
{
	int i = 0;
	int j = 0;
	FILE *pfr, *pfw, *pcode;
	
	fopen_s(&pfr, cipherTextPath, "rb");
	fopen_s(&pfw, decryptFilepath, "wb");
	fopen_s(&pcode, codeBookPath, "rb");

	if (pfr == NULL || pfw == NULL)
	{
		fclose(pfr);
		fclose(pfw);
		fclose(pcode);
		return;
	}
	else
	{
		int length = getFileSize(cipherTextPath);
		char *p = (char *)malloc(length * sizeof(char));
		string codeStr;
		string codeMajusculeStr;
		int index;

		fread(p, sizeof(char), length, pfr);
		codeStr = readFileIntoString(codeBookPath);

		transform(codeStr.begin(),codeStr.end(),back_inserter(codeMajusculeStr),::toupper);
	
		for (i = 0; i < length; i++)
		{
			if (p[i] >= 'a' && p[i] <= 'z')
			{
				index = codeStr.find_first_of(p[i]);
				p[i] = LowercaseAB[index];
			}
			else if (p[i] >= 'A' && p[i] <= 'Z')
			{
				index = codeMajusculeStr.find_first_of(p[i]);
				p[i] = MajusculeAB[index];
			}
			else
			{

			}
		}

		fwrite(p, sizeof(char), length, pfw);

		fclose(pfr);
		fclose(pfw);
		fclose(pcode);
	}
}

static int getFileSize(char const *path)
{
	FILE *pf;
	fopen_s(&pf, path, "r");

	if (pf == NULL)
	{
		return -1;
	}
	else
	{
		fseek(pf, 0, SEEK_END);
		int length = ftell(pf);

		return length;
	}
}

static string readFileIntoString(char const* filename)
{
	ifstream ifile(filename);
	
	ostringstream buf;
	char ch;

	while (buf&&ifile.get(ch))
		buf.put(ch);
	
	return buf.str();
}
