#include "ODBC.h"
#include <stdio.h>      
#include <string.h>      
#include <windows.h>      
#include <sql.h>     
#include <sqlext.h>      
#include <sqltypes.h>      
#include <odbcss.h>  
#include <string>
#include <iostream>
#include "DataVector.h"
#include <vector>



ODBC::ODBC()
{
}

ODBC::ODBC(UCHAR source_name[], UCHAR id[], UCHAR pswd[])
{
	SetSource(source_name);
	SetId(id);
	SetPswd(pswd);

	//连接到数据库
	connect();
	
}

ODBC::ODBC(const ODBC& sql)
{
	memcpy(szDSN, sql.szDSN, 30);
	memcpy(userID, sql.userID, 30);
	memcpy(passWORD, sql.passWORD, 30);
}

ODBC::~ODBC()
{
	SQLDisconnect(hdbc1);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	printf("数据库连接已断开!\n");
}

void ODBC::SetSource(UCHAR source_name[])
{
	memcpy(szDSN, source_name, 30);
}

void ODBC::SetId(UCHAR id[])
{
	memcpy(userID, id, 30);
}

void ODBC::SetPswd(UCHAR pswd[])
{
	memcpy(passWORD, pswd, 30);
}

void ODBC::connect()
{ 
	//1.环境句柄     
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	//2.连接句柄      
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
	retcode = SQLConnect(hdbc1, szDSN, SQL_NTS, userID, SQL_NTS, passWORD, SQL_NTS);
	
	//判断连接是否成功     

	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO))
	{
		printf("数据库连接失败!\n");
	}
	else
	{
		printf("数据库连接成功!\n");
	}
	
}

void ODBC::SelectQuery(char handle[], char temp_handle[], DataVector &vector)
{
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
	retcode = SQLExecDirect(hstmt1, (SQLCHAR *)temp_handle, strlen(temp_handle));
	if (!SQL_SUCCEEDED(retcode))
	{
		std::cout << "查询时发生错误" << std::endl;
	}
	else
	{
		SQLTCHAR row_num[50];
		retcode = SQLFetch(hstmt1);
		SQLGetData(hstmt1, 1, SQL_C_TCHAR, (SQLPOINTER)row_num,
			sizeof(row_num), NULL);
		std::string input;
		input = (char*)row_num;
		int num;
		num = std::atoi(input.c_str());
		vector.row_num = num;

		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
		retcode = SQLExecDirect(hstmt1, (SQLCHAR *)handle, strlen(handle));
		if (!SQL_SUCCEEDED(retcode))
		{
			std::cout << "查询时发生错误" << std::endl;
		}
		else
		{
			std::cout << "查询成功" << std::endl;
		}
		
	}


	
}

void ODBC::FetchForOne(DataVector &vector)
{
	//准备工作
	SQLSMALLINT ColNums;
	SQLNumResultCols(hstmt1, &ColNums);
	SQLTCHAR name[100];
	SQLSMALLINT sColNameBytes;
	SQLSMALLINT sDataType;
	SQLULEN uiColumnSize;
	SQLSMALLINT sDecimalDigits;
	SQLSMALLINT sNullable;
	SQLUSMALLINT i;

	//存储数据名称
	vector.resize(ColNums);
	//Matrix<int, 1, Dynamic> data_type;
	vector.data_type.resize(1, ColNums);
	for (i = 0; i < ColNums; i++)
	{
		retcode = SQLDescribeCol(hstmt1, i + 1, name, sizeof(name), &sColNameBytes,&sDataType, &uiColumnSize,
			&sDecimalDigits, &sNullable);
		vector.StoreDataName(i, (char*)name);
		vector.data_type[i] = sDataType;
	}

	//存储数据
	std::vector<SQLTCHAR[50]> load(ColNums);
	while (true) 
	{
		retcode = SQLFetch(hstmt1);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) 
		{
			for (i = 0; i < ColNums; i++)
			{
				SQLGetData(hstmt1, i + 1, SQL_C_TCHAR, (SQLPOINTER)load[i],
					sizeof(load[i]), NULL);

				if (vector.data_type[i] == 93 || vector.data_type[i] == -9)
				{
					//string
					std::string input;
					input = (char*)load[i];
					vector.AddDataByCol(i, input);
					//vector.WriteInType(i, "string");
				}
				else
				{
					//number
					std::string input;
					input = (char*)load[i];
					vector.AddDataByCol(i, std::atof(input.c_str()));
					//vector.WriteInType(i, "number");
				}
			}
		}
		else
		{
			break;
		}
	}


}