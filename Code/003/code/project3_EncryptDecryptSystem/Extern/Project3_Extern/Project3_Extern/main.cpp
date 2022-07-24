#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

vector<unsigned char> clearTextVec;

static size_t getFileSize(const char* filePath);
static string readFileIntoString(char const* filename);

void EncryptFile(char const *clearTextPath, char const *codeBookPath, char const *cipherTextPath);
void DecryptFile(char const *cipherTextPath, char const *codeBookPath, char const *decryptFilepath);
std::vector<unsigned char> read_File(const char* filePath);

int main()
{
	int operateType = 0;
	char const *codeBookPath = "..\\Project3_Extern\\codebook.txt";
	char const *clearTextPath = "..\\Project3_Extern\\cleartext.txt";
	char const *cipherTextPath = "..\\Project3_Extern\\ciphertext.txt";
	char const *newDecryptFilepath = "..\\Project3_Extern\\decrypttext.txt";
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

void EncryptFile(char const *clearTextPath, char const *codeBookPath, char const *cipherTextPath)
{
	int pos;
	int index;
	int temp;
	char m[] = " ";
	int begin, end;
	FILE *pfr, *pfw, *pcode;

	clearTextVec = readBinaryFile(clearTextPath);
	fopen_s(&pcode, codeBookPath, "rb");


	/*
	for (int i = 0; i < codeFilelength; i++)
	{
		pos = codeStr.find(' ', i);
		if (codeFileBuffer[i] == ' ')
		{
			codeSubStr = codeStr.substr(i, pos - i);
			CodeBookVec.push_back(codeSubStr);
			i = pos;
		}
			
	}
	

	for (int j = 0; j < length; j++)
	{
		index = (int)p[j];
		cout << "index" << index << endl;
		cout << "CodeBookVec" << CodeBookVec[index] << endl;
		temp = stoi(CodeBookVec[index]);
		p[j] = temp + '0';
		cout << "stoi(CodeBookVec[index]" << temp << endl;
		cout << "p[j]" << p[j] << endl;
	}
	*/

}

void DecryptFile(char const *cipherTextPath, char const *codeBookPath, char const *decryptFilepath)
{
	int pos;
	FILE *pfr, *pfw, *pcode;
	ifstream codeFile(codeBookPath);
	int index;
	string codeStr;
	string codeSubStr;
	int temp;

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
		/*
		int length = getFileSize(cipherTextPath);
		char *p = (char *)malloc(length * sizeof(char));

		fread(p, sizeof(char), length, pfr);
		getline(codeFile, codeStr);
		
		codeStr = codeStr + ' ';
		for (int i = 0; i < codeStr.size(); i++)
		{
			pos = codeStr.find(' ', i);
			if (pos < codeStr.size())
			{
				codeSubStr = codeStr.substr(i, pos - i);
				CodeBookVec.push_back(codeSubStr);
				i = pos;
			}
		}

		for (int j = 0; j < length; j++)
		{
			temp = p[j] - '0';
			cout << "p[j]" << p[j] << endl;
			cout << "p[j]" << temp << endl;
			for (int k = 0; k < CodeBookVec.size(); k++)
			{
				if (stoi(CodeBookVec[k]) == temp)
				{
					index = k;
					cout << "index" << index << endl;
					//cout << "p[j]" << p[j] << endl;
					//temp = stoi(CodeBookVec[index]);
					p[j] = index + '0';
					break;
				}
			}
			
		}

		fwrite(p, sizeof(char), length, pfw);

		fclose(pfr);
		fclose(pfw);
		fclose(pcode);
		*/
	}
}


static size_t getFileSize(FILE* file)
{
	fseek(file, 0, SEEK_END);
	size_t read_len = ftell(file);
	fseek(file, 0, SEEK_SET);
	return read_len;
}

static size_t getFileSize(const char* filePath)
{
	FILE* file;
	fopen_s(&file,filePath, "rb");
	if (file == nullptr) 
	{
		return 0;
	}
	size_t size = getFileSize(file);
	fclose(file);
	return size;
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


std::vector<unsigned char> readBinaryFile(const char* filePath)
{
	std::vector<unsigned char> fileData;
	std::ifstream inputFile(filePath, std::ios::binary);
	inputFile.seekg(0, std::ios::end);
	fileData.resize(inputFile.tellg());
	inputFile.seekg(0);
	inputFile.read(reinterpret_cast<char*>(fileData.data()), fileData.size());
	return fileData;
}
