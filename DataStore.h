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
	//构造函数
	DataStore();
	DataStore(Matrix<double, 1, Dynamic> data);
	DataStore(Matrix<std::string, 1, Dynamic> data);

	//数据储存
	void store(Matrix<double, 1, Dynamic> data);
	void store(Matrix<std::string, 1, Dynamic> data);

	//返回数据类型
	std::string GetType();

	//添加一个数据
	void AddData(float data);
	void AddData(double data);
	void AddData(std::string data);

	//返回数据
	void GetData(Matrix<double, 1, Dynamic> &load);
	void GetData(Matrix<std::string, 1, Dynamic> &load);
	
	//resize
	void resize(int num);

	//索引
	void GetByIndex(Index index, double &load);
	
	void GetByIndex(Index index, std::string &load);

	


};