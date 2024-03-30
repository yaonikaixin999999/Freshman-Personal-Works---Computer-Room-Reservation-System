#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<istream>
#include<algorithm>
#include<map>
#define RESERVATION_FILE "reservation.txt"
#define COMPUTER_ROOM_FILE "computer_room.txt"
using namespace std;

class Computer_Room {
public:
	Computer_Room();

	int room_ID;//机房号
	int room_num;//机房最大电脑数量
	int room_remainder;//剩余电脑数量
	int toom_reservation_num;//正在被预约中电脑的数量
};

class userID {
public:
	userID();

	string m_username;  //用户名
	string m_password;  //密码
};

class m_time {
public:
	string Time(int m_time) {
		if (m_time == 1) {
			return "上午";
		}
		else {
			return "下午";
		}
	}
};

class m_date {
public:
	string Date(int m_date) {
		switch (m_date){
		case 1:
			return "星期一";
		case 2:
			return  "星期二";
		case 3:
			return  "星期三";
		case 4:
			return  "星期四";
		case 5:
			return  "星期五";
		case 6:
			return  "星期六";
		case 7:
			return  "星期日";
		}
	}
};

class m_status {
public:
	string Status(int m_status) {
		switch (m_status) {
		case -1:
			return "审核不通过";
		case 0:
			return "已取消";
		case 1:
			return "审核中";
		case 2:
			return "审核已通过";
		}
	}
};

class reservation_status {
public:
	reservation_status() {}

	//日期
	m_date md;
	//状态
	m_status ms;
	//时间
	m_time mt;
	int m_date;//日期
	int m_time;//时间

	//1 上午
	//2 下午

	string m_username;//申请人用户名
	string m_name;//申请人姓名
	int m_room_ID;//申请的机房号
	int m_room_num;//申请电脑数量
	int m_status;//审核状态

	bool no_update;//不需要更新标志

	//-1.审核不通过
	//0.已取消
	//1.审核中
	//2.审核已通过
};

class computer_reservation_system {
public:
	//构造函数
	computer_reservation_system();
	
	//调用预约机房数据
	Computer_Room CR;

	//初始化
	void CRS_start();

	//全部申请记录
	vector<reservation_status>vrs;

	//个人申请记录
	vector<reservation_status>m_vrs;
	
	//更新电脑数据
	void computer_update();

	//机房容量
	vector<Computer_Room>crm;

	//调用申请记录
	reservation_status RS;

	//记录临时申请电脑数
	int temp_computer_num[3] = { 0,0,0 };

	//主菜单
	void Main_Menu();

	//机房数量
	int computer_room_1, computer_room_2, computer_room_3;
};

