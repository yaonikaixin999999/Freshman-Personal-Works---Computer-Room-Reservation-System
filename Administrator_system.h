#pragma once
#include"computer_reservation_system.h"
#include<iostream>
#define ADMINISTRATOR_FILE "adimistrator.txt"
#define STUDENT_FILE "student.txt"
#define TEACHER_FILE "teacher.txt"

using namespace std;

class Administrator:public userID {
public:
	Administrator();

	//管理员已经登录
	bool Administrator_log_in;

	//初始化
	void administrator_start_process();

	//管理员菜单
	void Administrator_menu();

	//管理员登录界面
	void administrator_login_screen();

	//添加账号
	void Add_username();

	//查看账号
	void View_username();

	//调用机房数据
	computer_reservation_system CRS;

	//调用账号系统数据
	userID UID;

	//查看机房
	void View_computer_room();

	//清空预约
	void clear_reservation();

	//管理员登录流程
	void Administrator_system_process();

	~Administrator(){}
};
