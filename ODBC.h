#ifndef ODBC_H_
#define ODBC_H_

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



class ODBC
{
private:
	RETCODE retcode;
	UCHAR szDSN[255]; //数据源名称  	
	UCHAR userID[255];//数据库用户ID  
	UCHAR passWORD[255];//用户密码

	//环境变量
	#define MAXBUFLEN 255  
	SQLHENV henv = SQL_NULL_HENV;
	SQLHDBC hdbc1 = SQL_NULL_HDBC;
	SQLHSTMT hstmt1 = SQL_NULL_HSTMT;

public:
	//构造函数
	ODBC();  //不连接数据库，需要手动调用connect方法
	ODBC(UCHAR source_name[], UCHAR id[], UCHAR pswd[]);  //自动连接数据库，无需调用

	//拷贝构造函数
	ODBC(const ODBC& sql);

	//析构函数,在析构函数中关闭与数据库的连接
	~ODBC();

	//命名函数
	void SetSource(UCHAR source_name[]);
	void SetId(UCHAR id[]);
	void SetPswd(UCHAR pswd[]);

	//连接数据库
	void connect();

	//select查询,输入为sql server语法的select语句
	void SelectQuery(char handle[],char temp_handle[], DataVector &vector);

	void FetchForOne(DataVector &vector);


};

#endif