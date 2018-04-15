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
	UCHAR szDSN[255]; //����Դ����  	
	UCHAR userID[255];//���ݿ��û�ID  
	UCHAR passWORD[255];//�û�����

	//��������
	#define MAXBUFLEN 255  
	SQLHENV henv = SQL_NULL_HENV;
	SQLHDBC hdbc1 = SQL_NULL_HDBC;
	SQLHSTMT hstmt1 = SQL_NULL_HSTMT;

public:
	//���캯��
	ODBC();  //���������ݿ⣬��Ҫ�ֶ�����connect����
	ODBC(UCHAR source_name[], UCHAR id[], UCHAR pswd[]);  //�Զ��������ݿ⣬�������

	//�������캯��
	ODBC(const ODBC& sql);

	//��������,�����������йر������ݿ������
	~ODBC();

	//��������
	void SetSource(UCHAR source_name[]);
	void SetId(UCHAR id[]);
	void SetPswd(UCHAR pswd[]);

	//�������ݿ�
	void connect();

	//select��ѯ,����Ϊsql server�﷨��select���
	void SelectQuery(char handle[],char temp_handle[], DataVector &vector);

	void FetchForOne(DataVector &vector);


};

#endif