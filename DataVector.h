#pragma once
#include <vector>
#include "DataStore.h"
#include <Eigen/Dense>
#include <string>
#include <iostream>
using namespace Eigen;

class DataVector
{
private:
	std::vector<DataStore> data; //一个元素代表一列数据
	Matrix<std::string, 1, Dynamic> data_name;
	Matrix<std::string, 1, Dynamic> type;

public:
	Matrix<int, 1, Dynamic> data_type;
	int row_num;
	
	void WriteInType(int num, std::string _type);


	//构造函数
	DataVector();
	DataVector(const DataVector &vector, Matrix<std::string,1,Dynamic> name_list);

	//resize
	void resize(int num);

	//按列添加一个元素
	template<class T>
	void AddDataByCol(int ColNum, T _data)
	{
		data[ColNum].AddData(_data);
	}

	//将数据名写入data_name
	void StoreDataName(int num, std::string name);

	//获取数据名称
	Matrix<std::string, 1, Dynamic> GetDataName();

	//获取数据类型
	Matrix<std::string, 1, Dynamic> GetType();

	//获取数据下标
	Index GetItemIndex(std::string code, std::string date);

	//按索引获取数据.前两个参数（code,日期）顺序保持与数据库一致。数据库中哪个是第一列，就作为第一个参数。
	double GetData(std::string str1, std::string str2, std::string col_name);
	Matrix<double, 1, Dynamic> GetData(std::string str1, std::string str2, Matrix<std::string, 1, Dynamic> col_list);
	Matrix<double, 1, Dynamic> GetData(std::string windcode, std::string col_name);	
	void GetData(int col_index, Matrix<double, 1, Dynamic> &load);
	void GetData(int col_index, Matrix<std::string, 1, Dynamic> &load);


	Matrix<std::string, 1, Dynamic> GetDate(std::string windcode);

};