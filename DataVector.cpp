#include <vector>
#include "DataStore.h"
#include <Eigen/Dense>
#include <string>
#include "DataVector.h"

using namespace Eigen;

void DataVector::WriteInType(int num, std::string _type)
{
	type[num] = _type;
}

DataVector::DataVector()
{

}

DataVector::DataVector(const DataVector &vector, Matrix<std::string, 1, Dynamic> name_list)
{
	data_name = name_list;
	data = vector.data;
}

void DataVector::resize(int num)
{
	data.resize(num);
	data_name.resize(num);
	type.resize(num);
	for (Index i = 0; i < type.size(); i++)
	{
		data[i].resize(row_num);
	}
}

void DataVector::StoreDataName(int ColNum, std::string name)
{
	data_name[ColNum] = name;
}

Matrix<std::string, 1, Dynamic> DataVector::GetDataName()
{
	return data_name;
}

Matrix<std::string, 1, Dynamic> DataVector::GetType()
{
	return type;
}

Index DataVector::GetItemIndex(std::string str1, std::string str2)
{
	Index i,res;
	res = -1;
	Matrix<std::string, 1, Dynamic> temp1;
	Matrix<std::string, 1, Dynamic> temp2;
	data[0].GetData(temp1);
	data[1].GetData(temp2);
	for (i = 0; i < row_num; i++)
	{
		if (temp1[i] == str1 && temp2[i] == str2)
		{
			res = i;
			break;
		}
	}
	if (res == -1)
	{
		std::cout << "日期或标的代码不存在" << std::endl;
	}
	return res;
}

double DataVector::GetData(std::string str1, std::string str2, std::string col_name)
{
	Index col_index = -1;
	for (Index i = 0; i < data_name.size(); i++)
	{
		if (data_name[i] == col_name)
		{
			col_index = i;
			break;
		}
	}
	Index row_index = GetItemIndex(str1, str2);
	double res;	
	if (col_index == -1)
	{
		std::cout << "数据名" + col_name + "不存在" << std::endl;
	}
	data[col_index].GetByIndex(row_index, res);
	return res;
	
}

Matrix<double, 1, Dynamic> DataVector::GetData(std::string str1, std::string str2, Matrix<
	std::string, 1, Dynamic> col_list)
{
	Index row_index = GetItemIndex(str1, str2);
	Index length = col_list.size();

	Matrix<double, 1, Dynamic> res;
	res.resize(1, length);
	Index flag;
	for (Index i = 0; i < length; i++)
	{
		flag = -1;
		for (Index j = 0; j < data_name.size(); j++)
		{
			if (data_name[j] == col_list[i])
			{
				flag = 0;
				data[j].GetByIndex(row_index, res[i]);
				break;
			}
		}
		if (flag == -1)
		{
			std::cout << "数据名" + col_list[i] + "不存在" << std::endl;
		}
	}

	return res;

}


Matrix<double, 1, Dynamic> DataVector::GetData(std::string windcode, std::string col_name)
{
	Index col_index = -1;
	Matrix<double, 1, Dynamic> res;
	for (Index i = 0; i < data_name.size(); i++)
	{
		if (data_name[i] == col_name)
		{
			col_index = i;
			break;
		}
	}
	if (col_index == -1)
	{
		std::cout << "数据名" + col_name + "不存在" << std::endl;
		return res;
	}
	else
	{
		Index index_start = -1;
		Index index_end = -1;
		Matrix<std::string, 1, Dynamic> temp;
		data[0].GetData(temp);

		for (Index i = 0; i < temp.size(); i++)
		{
			if (index_start == -1)
			{
				if (temp[i] == windcode)
				{
					index_start = i;
				}
			}
			else
			{
				if (temp[i] != windcode)
				{
					index_end = i - 1;
					break;
				}
				if (i == temp.size() - 1)
				{
					index_end = i;
				}
			}
			
		}
		Matrix<double, 1, Dynamic> temp2;
		data[col_index].GetData(temp2);
		res = temp2.segment(index_start, index_end - index_start + 1);
		return res;


	}

	
}



void DataVector::GetData(int col_index, Matrix<double, 1, Dynamic> &load)
{
	data[col_index].GetData(load);
}


void DataVector::GetData(int col_index, Matrix<std::string, 1, Dynamic> &load)
{
	data[col_index].GetData(load);
}


Matrix<std::string, 1, Dynamic> DataVector::GetDate(std::string windcode)
{
	Index col_index = -1;
	Matrix<std::string, 1, Dynamic> res;
	for (Index i = 0; i < data_name.size(); i++)
	{
		if (data_name[i] == "date")
		{
			col_index = i;
			break;
		}
	}
	if (col_index == -1)
	{
		std::cout << "数据名date不存在" << std::endl;
		return res;
	}
	else
	{
		Index index_start = -1;
		Index index_end = -1;
		Matrix<std::string, 1, Dynamic> temp;
		data[0].GetData(temp);
		
		for (Index i = 0; i < temp.size(); i++)
		{
			if (index_start == -1)
			{
				if (temp[i] == windcode)
				{
					index_start = i;
				}
			}
			else
			{
				if (temp[i] != windcode)
				{
					index_end = i - 1;
					break;
				}
				if (i == temp.size() - 1)
				{
					index_end = i;
				}
			}

		}
		Matrix<std::string, 1, Dynamic> temp2;
		data[col_index].GetData(temp2);
		res = temp2.segment(index_start, index_end - index_start + 1);
		return res;


	}
}