#pragma once
#include<string>
#include<unordered_map>
#include"cell.h"
using namespace std;

namespace Scanalyse
{
	class Fun
	{
	public:
		Fun() {

		}
		~Fun() {

		}
		vector<string> files;//����ļ����������ļ�·��
		int rowCount[100];//ÿ���ļ�������
		int columnCount[100];//ÿ���ļ�������
		vector<Cells> cellList;//���ÿ���ļ���cellsʵ��
		unordered_map<int, string> allNumToGene;
		unordered_map<string, int> allGeneToNum;
		unordered_map<string, string> geneSymbolToEnsemblId;

		void read();
		int CaculateRow(string path);
		int CaculateColumn(string path);
		void GetAllFiles(string path, vector<string>& files);
		void GetAllFormatFiles(string path, vector<string>& files, string format);
		void CreatAllGeneMap();
		void replaceEnsemblId();
	};
	
		
}

