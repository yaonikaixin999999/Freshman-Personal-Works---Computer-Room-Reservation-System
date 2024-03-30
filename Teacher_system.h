#pragma once
#include"computer_reservation_system.h"
#include<iostream>
#define TEACHER_FILE "teacher.txt"
using namespace std;

class Teacher:public userID {
public:
	Teacher();

	string m_Name;

	//教师已经登录
	bool teacher_log_in;

	//初始化
	void teacher_start_process();

	//登录界面
	void teacher_login_screen();

	//教师菜单
	void Teacher_Menu();

	//调用账号系统数据
	userID UID;

	//调用机房数据
	computer_reservation_system CRS;

	//查看所有预约
	void Tea_View_all_reservation();

	//审核预约
	void Audit_reservation();

	//教师登录流程
	void teacher_system_process();

	~Teacher();
};
