#include"fun.h"
#include"cell.h"
#include <io.h>
#include<iostream>
#include <fstream>  
#include <string>  
#include <vector>  

using namespace std;
using namespace Scanalyse;


int main()

{
	Fun fun;
	fun = Fun();
	/*
	string path1 = "E:\\cell mapping\\GSE66507.csv";
	string path2 = "E:\\cell mapping\\GSE66507mapping.csv";
	fun.replaceEnsemblId(path1,path2);

	*/
	string filePath = "E:\\cell";
	string outpath = "E:\\testcell\\merge.csv";
	fun.read(filePath);
	fun.CreatAllGeneMap();
	fun.initMergeMatrix();
	fun.mergeMatrixs();
	fun.outToCsvFile(outpath);

	cin.get();
	cin.get();
	return 0;
}
