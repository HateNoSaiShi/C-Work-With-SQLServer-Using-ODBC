#include "DataStore.h"
#include <Eigen/Dense>
using namespace Eigen;

DataStore::DataStore()
{
	float_data.resize(1, 1);
	string_data.resize(1, 1);
}

DataStore::DataStore(Matrix<double, 1, Dynamic> data)
{
	store(data);
}

DataStore::DataStore(Matrix<std::string, 1, Dynamic> data)
{
	store(data);
}

void DataStore::store(Matrix<double, 1, Dynamic> data)
{
	data_type = "number";
	float_data = data;
	type = 1;
}

void DataStore::store(Matrix<std::string, 1, Dynamic> data)
{
	data_type = "string";
	string_data = data;
	type = 2;
}

std::string DataStore::GetType()
{
	return data_type;
}


void DataStore::AddData(float data)
{
	//float_data.conservativeResize(len + 1);
	len++;
	float_data[len - 1] = data;
}


void DataStore::AddData(double data)
{
	//float_data.conservativeResize(len + 1);
	len++;
	float_data[len - 1] = data;
}


void DataStore::AddData(std::string data)
{
	//string_data.conservativeResize(len + 1);
	len++;
	string_data[len - 1] = data;
}

void DataStore::GetData(Matrix<double, 1, Dynamic> &load)
{
	load = float_data;
}

void DataStore::GetData(Matrix<std::string, 1, Dynamic> &load)
{
	load = string_data;
}

void DataStore::resize(int num)
{
	float_data.resize(1, num);
	string_data.resize(1, num);
}


void DataStore::GetByIndex(Index index, double &load)
{
	load = float_data(index);
}


void DataStore::GetByIndex(Index index, std::string &load)
{
	load = string_data(index);
}



