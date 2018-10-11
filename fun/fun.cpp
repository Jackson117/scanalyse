#include"fun.h"
#include"cell.h"
#include <io.h>
#include<iostream>
#include <fstream>  
#include <string>  
#include <vector>  
#include<queue>
#include<sstream>
using namespace std;
using namespace Scanalyse;


vector<string> files;//����ļ����������ļ�·��
int rowCount[100] ;//ÿ���ļ�������
int columnCount[100] ;//ÿ���ļ�������
vector<Cells> cellList;//���ÿ���ļ���cellsʵ��
unordered_map<int, string> allNumToGene;
unordered_map<string, int> allGeneToNum;

void Fun::read()
{
	string filePath = "E:\cell";
	string distAll = "AllFiles.txt";
	//��ȡ���е��ļ����������ļ����ļ� 
	//GetAllFiles(filePath, files);  

	//��ȡ���и�ʽΪcsv���ļ�  
	string format = ".csv";
	Fun fun;
	fun = Fun();
	fun.GetAllFormatFiles(filePath, files, format);
	ofstream ofn(distAll);

	int size = files.size();
	ofn << size << endl;
	for (int i = 0; i<size; i++)
	{
		ofn << files[i] << endl;
		cout << files[i] << endl;
		rowCount[i] = CaculateRow(files[i]);
		columnCount[i] = CaculateColumn(files[i]);
	}
	
	for (int i = 0; i < size; i++)
	{
		Cells paraCells(rowCount[i],columnCount[i]);
		paraCells.readFile(files[i]);
		cellList.push_back(paraCells);
	}

	Cells testcell = cellList[1];
	unsigned short **para = testcell.getCell;
	unsigned short *p;
	for (int i = 0; i < 47193;i++) {
		p = *para;
		for (int j = 0; j < 373;j++) {
			cout<<*p+j<<' '; 
		}       
		cout<<endl;
	}
	ofn.close();
}

int Fun::CaculateRow(string path)
{
	ifstream inFile(path, ios::in);
	string lineStr;
	string geneName;
	string str;
	int row = 0;

	while (getline(inFile, lineStr)) 
	{
		row++;
	}
	return row;
}

int Fun::CaculateColumn(string path)
{
	ifstream inFile(path, ios::in);
	string lineStr;
	string geneName;
	string str;
	int column = 0;

	if (getline(inFile, lineStr)) {
		stringstream ss(lineStr);
		while (getline(ss, str, ',')) 
		{
			column++;
		}
	}
	return column;
}


void Fun::GetAllFiles(string path, vector<string>& files)
{
	long   hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

}



//��ȡ�ض���ʽ���ļ���  
void Fun::GetAllFormatFiles(string path, vector<string>& files, string format)

{
	//�ļ����    
	long   hFile = 0;
	//�ļ���Ϣ    
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  

					GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files, format);
				}

			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));

			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);

	}
}

void Fun::CreatAllGeneMap()
{
	unordered_map<string, int> parageneToNum;
	unordered_map<int, string> paranumToGene;
	int i = 0,iter;
	Cells paraCell;
	string paraGene;
	for (iter = 0; iter <cellList.size; ++iter) {
		paraCell = cellList[iter];
		parageneToNum = paraCell.getGeneToNum();
		paranumToGene = paraCell.getNumToGene();
		for (int j = 0; j < parageneToNum.size; j++)
		{
			paraGene=paranumToGene[j];
			allNumToGene[i] = paraGene;
			allGeneToNum[paraGene] = i;
			i++;
		}
	}
}

