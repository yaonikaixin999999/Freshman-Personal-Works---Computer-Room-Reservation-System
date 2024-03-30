#include<iostream>
#include"computer_reservation_system.h"
#include"Student_system.h"
#include"Teacher_system.h"
#include"Administrator_system.h"
using namespace std;

computer_reservation_system::computer_reservation_system() {
	this->CRS_start();
}

Computer_Room::Computer_Room() {
	this->room_ID = NULL;
	this->room_num = NULL;
	this->room_remainder = NULL;
	this->toom_reservation_num = NULL;
}

userID::userID() {
	this->m_username = "";
	this->m_password = "";
}

//初始化
void computer_reservation_system::CRS_start() {
	crm.reserve(3);
	ifstream ifs;
	//int temp_room_id, temp_room_num;
	ifs.open(COMPUTER_ROOM_FILE, ios::in);
	//读出机房信息数据文件
	while (ifs >> CR.room_ID && ifs >> CR.room_num&&ifs>>CR.room_remainder&&ifs>>CR.toom_reservation_num) {
		crm.push_back(CR);
	}
	ifs.close();

	m_vrs.clear();
	ifstream ifs_rs;
	ifs_rs.open(RESERVATION_FILE,ios::in);

	//写入机房信息数据
	while (ifs_rs >> RS.m_date && ifs_rs >> RS.m_time && ifs_rs 
		>> RS.m_username && ifs_rs >> RS.m_name &&ifs_rs 
		>> RS.m_room_ID && ifs_rs >> RS.m_room_num && ifs_rs 
		>> RS.m_status && ifs_rs>>RS.no_update) {
		vrs.push_back(RS);
	}

	this->computer_update();
	ifs_rs.close();
}

void computer_reservation_system::computer_update() {
	//同步机房剩余的电脑
	int temp_num[3] = { 0,0,0 };
	for (vector<reservation_status>::iterator it_d = this->vrs.begin(); it_d != this->vrs.end(); it_d++) {
		for (vector<Computer_Room>::iterator it_c = this->crm.begin(); it_c != this->crm.end(); it_c++) {
			if ((*it_c).room_ID == (*it_d).m_room_ID) {

				if ((*it_d).m_status == 1 || (*it_d).m_status == 2)
					temp_num[(*it_d).m_room_ID - 1] += (*it_d).m_room_num;
				else if ((*it_d).m_status == -1 || (*it_d).m_status == 0)
					temp_num[(*it_d).m_room_ID - 1] -= (*it_d).m_room_num;
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (temp_num[i] != this->temp_computer_num[i]) {
			this->crm[i].toom_reservation_num = temp_num[i];
			this->crm[i].room_remainder = this->crm[i].room_num - this->crm[i].toom_reservation_num;
		}
	}
}


//主菜单
void computer_reservation_system::Main_Menu() {
	cout << "======================  欢迎来到传智播客机房预约系统  ====================="
		<< endl;
	cout << endl << "请输入您的身份" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.学生代表           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.老    师           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.管 理 员           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.退    出           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//学生菜单
void Student::Student_Menu() {
	cout << "欢迎学生：" << Student::m_Name << " 登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.申请预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看我的预约        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看所有预约        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.取消预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.退出登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//教师菜单
void Teacher::Teacher_Menu() {
	cout << "欢迎教师：" << this->m_Name << " 登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.查看所有预约        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.审核预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.退出登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//管理员菜单
void Administrator::Administrator_menu() {
	cout << "欢迎管理员："<<UID.m_username<<" 登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.退出登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}