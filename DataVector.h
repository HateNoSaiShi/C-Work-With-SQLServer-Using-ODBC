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
	std::vector<DataStore> data; //һ��Ԫ�ش���һ������
	Matrix<std::string, 1, Dynamic> data_name;
	Matrix<std::string, 1, Dynamic> type;

public:
	Matrix<int, 1, Dynamic> data_type;
	int row_num;
	
	void WriteInType(int num, std::string _type);


	//���캯��
	DataVector();
	DataVector(const DataVector &vector, Matrix<std::string,1,Dynamic> name_list);

	//resize
	void resize(int num);

	//�������һ��Ԫ��
	template<class T>
	void AddDataByCol(int ColNum, T _data)
	{
		data[ColNum].AddData(_data);
	}

	//��������д��data_name
	void StoreDataName(int num, std::string name);

	//��ȡ��������
	Matrix<std::string, 1, Dynamic> GetDataName();

	//��ȡ��������
	Matrix<std::string, 1, Dynamic> GetType();

	//��ȡ�����±�
	Index GetItemIndex(std::string code, std::string date);

	//��������ȡ����.ǰ����������code,���ڣ�˳�򱣳������ݿ�һ�¡����ݿ����ĸ��ǵ�һ�У�����Ϊ��һ��������
	double GetData(std::string str1, std::string str2, std::string col_name);
	Matrix<double, 1, Dynamic> GetData(std::string str1, std::string str2, Matrix<std::string, 1, Dynamic> col_list);
	Matrix<double, 1, Dynamic> GetData(std::string windcode, std::string col_name);	
	void GetData(int col_index, Matrix<double, 1, Dynamic> &load);
	void GetData(int col_index, Matrix<std::string, 1, Dynamic> &load);


	Matrix<std::string, 1, Dynamic> GetDate(std::string windcode);

};