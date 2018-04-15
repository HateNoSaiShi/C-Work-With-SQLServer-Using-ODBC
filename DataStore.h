#pragma once
#include <Eigen\Dense>
#include <string>

using namespace Eigen;

class DataStore
{
private:
	Matrix<double, 1, Dynamic> float_data;
	Matrix<std::string, 1, Dynamic> string_data;
	std::string data_type;
	int type;
	Index len = 0;

public:
	//���캯��
	DataStore();
	DataStore(Matrix<double, 1, Dynamic> data);
	DataStore(Matrix<std::string, 1, Dynamic> data);

	//���ݴ���
	void store(Matrix<double, 1, Dynamic> data);
	void store(Matrix<std::string, 1, Dynamic> data);

	//������������
	std::string GetType();

	//���һ������
	void AddData(float data);
	void AddData(double data);
	void AddData(std::string data);

	//��������
	void GetData(Matrix<double, 1, Dynamic> &load);
	void GetData(Matrix<std::string, 1, Dynamic> &load);
	
	//resize
	void resize(int num);

	//����
	void GetByIndex(Index index, double &load);
	
	void GetByIndex(Index index, std::string &load);

	


};