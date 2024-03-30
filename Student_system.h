#pragma once
#include"computer_reservation_system.h"
#include<iostream>
#define STUDENT_FILE "student.txt"
using namespace std;

class Student:public userID{
public:
	Student();

	string m_Name;

	//学生已经登录
	bool student_log_in;

	//初始化
	void student_start_process();

	//登录界面
	void student_login_screen();

	//调用账号系统数据
	userID UID;

	//学生菜单
	void Student_Menu();

	//申请预约
	void Apply_reservation();

	//调用机房数据
	computer_reservation_system crs;

	//查看我的预约
	void View_my_reservation();

	//查看所有预约
	void Sut_View_all_reservation();

	//取消预约
	void Cancel_reservation();

	//学生登录流程
	void student_system_process();

	//记录临时申请电脑数
	int temp_computer_num[3] = {0,0,0};

	//析构函数
	~Student();
};
