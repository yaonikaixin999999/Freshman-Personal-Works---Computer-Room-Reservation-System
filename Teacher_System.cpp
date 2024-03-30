#include"Teacher_system.h"
using namespace std;

Teacher::Teacher() {
	this->teacher_start_process();
}

class my_print_rs {
public:
	void operator()(reservation_status RS) {
		cout << "预约日期：" << RS.md.Date(RS.m_date) << " 时间段："
			<< RS.mt.Time(RS.m_time) << " 学号：" << RS.m_username
			<< " 姓名：" << RS.m_name << " 机房编号：" << RS.m_room_ID
			<< " 预约数量：" << RS.m_room_num << " 预约状态："
			<< RS.ms.Status(RS.m_status) << endl;
	}
};

void Teacher::teacher_start_process() {
	this->teacher_log_in = false;
	this->m_Name = "";
	if (!this->CRS.vrs.empty()) {
		for (vector<reservation_status>::iterator it_m = this->CRS.vrs.begin(); it_m != this->CRS.vrs.end(); it_m++) {
			if ((*it_m).m_name == this->m_Name) {
				this->CRS.m_vrs.push_back((*it_m));
			}
		}
	}

	//记录申请电脑数量
	for (vector<reservation_status>::iterator it_t = this->CRS.vrs.begin(); it_t != this->CRS.vrs.end(); it_t++) {
		if ((*it_t).m_status == 0 || (*it_t).m_status == -1)
			this->CRS.temp_computer_num[(*it_t).m_room_ID - 1] -= (*it_t).m_room_num;
		else if ((*it_t).m_status == 1 || (*it_t).m_status == 2)
			this->CRS.temp_computer_num[(*it_t).m_room_ID - 1] += (*it_t).m_room_num;
	}
}

//登录界面
void Teacher::teacher_login_screen() {
	ifstream ifs;
	ifs.open(TEACHER_FILE, ios::in);
	string username, name, password;
	string temp_username, temp_name, temp_password;
	cout << "请输入您的职工号" << endl;
	cin >> username;
	cout << "请输入用户名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> password;
	while (ifs >> temp_username && ifs >> temp_name && ifs >> temp_password) {
		if (temp_username == username&& temp_name == name&& temp_password == password) {	
			cout << "教师验证登录成功！" << endl;
			this->m_Name = temp_name;
			UID.m_username = temp_username;
			UID.m_password = temp_password;
			this->teacher_log_in = true;
			system("pause");
			system("cls");
		}
	}
	if (!this->teacher_log_in) {
		cout << "用户名，职工号或密码错误！" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
}

//查看所有预约
void Teacher::Tea_View_all_reservation() {
	if (this->CRS.vrs.empty()) {
		cout << "文件不存在或数据为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		for_each(this->CRS.vrs.begin(), this->CRS.vrs.end(), my_print_rs());
		system("pause");
		system("cls");
	}
}

//审核预约
void Teacher::Audit_reservation() {
	if (this->CRS.vrs.empty()) {
		cout << "文件不存在或数据为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		int temp_choice, i = 1;
		vector<int>v_serial_number;
		cout << "待审核的预约记录如下：" << endl;
		while (1) {
			cout << "请输入您需要审核的预约序号:" << endl;
			for (vector<reservation_status>::iterator it_rs = this->CRS.vrs.begin(); it_rs != this->CRS.vrs.end(); it_rs++) {
				if ((*it_rs).no_update == false && (*it_rs).m_status == 1) {
					v_serial_number.push_back(i);
					cout << i << ". 预约日期：" << ((*it_rs).md.Date((*it_rs).m_date)) << " 时间段："
						<< ((*it_rs).mt.Time((*it_rs).m_time))
						<< " 机房编号：" << ((*it_rs).m_room_ID) << " 申请电脑的数量："
						<< ((*it_rs).m_room_num) << " 状态："
						<< ((*it_rs).ms.Status((*it_rs).m_status)) << endl;
					i++;
				}
			}
			cout << "请输入审核的预约记录，0代表返回:" << endl;
			cin >> temp_choice;
			if (temp_choice > i) {
				cout << "输入有误,请重新输入！" << endl;
				v_serial_number.clear();
				i = 1;
				system("pause");
			}
			else {
				if (temp_choice <= 0) {
					system("pause");
					system("cls");
					break;
				}
				else if (temp_choice <= i && temp_choice > 0) {
					cout << "请输入审核结果:" << endl;
					while (1) {
						int temp_choice_1;
						cout << "1.通过 2.不通过 3.取消" << endl;
						cin >> temp_choice_1;
						if (temp_choice_1 != 1 && temp_choice_1 != 2&&temp_choice_1!=3) {
							cout << "输入有误，请重新输入!" << endl;
							system("pause");
						}
						else if (temp_choice_1 == 3) {
							cout << "已取消" << endl;
							break;
							system("pause");
							system("cls");
						}
						else {
							vector<reservation_status>temp_v;
							int temp_room_ID = this->CRS.vrs[v_serial_number[temp_choice - 1] - 1].m_room_ID;

							for (vector<reservation_status>::iterator temp_it_vrs = this->CRS.vrs.begin(); temp_it_vrs != this->CRS.vrs.end(); temp_it_vrs++) {
								if ((*temp_it_vrs).m_room_ID == temp_room_ID) {
									(*temp_it_vrs).no_update = true;
									if (temp_choice_1 == 1) 
										(*temp_it_vrs).m_status = 2;
									else if (temp_choice_1 == 2)
										(*temp_it_vrs).m_status = -1;
									temp_v.push_back(*temp_it_vrs);
									this->CRS.vrs.push_back(temp_v[0]);
									temp_v.clear();
									break;
								}
							}

							cout << "审核完毕!" << endl;
							system("pause");
							system("cls");
							break;
						}
					}
					break;
				}
			}
		}
	}
}

//教师登录流程
void Teacher::teacher_system_process() {
	this->teacher_login_screen();
	if (this->teacher_log_in) {
		int temp_choice;
		while (1) {
			this->Teacher_Menu();
			cin >> temp_choice;
			if (temp_choice != 1 && temp_choice != 2 && temp_choice != 3 && temp_choice != 4 && temp_choice != 0) {
				cout << "输入错误，请重新输入" << endl;
				system("pause");
				system("cls");
			}
			else {
				if (temp_choice == 1) {
					this->Tea_View_all_reservation();
				}
				else if (temp_choice == 2) {
					this->Audit_reservation();
				}
				else {
					cout << "已注销登录" << endl;
					break;
				}
			}
		}
		if (temp_choice == 0) {
			system("pause");
			system("cls");
			return;
		}
	}
	else {
		return;
	}
}

Teacher::~Teacher() {
	//更新机房数据至文件中
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::trunc);
	for (vector<reservation_status>::iterator it_rs = this->CRS.vrs.begin(); it_rs != this->CRS.vrs.end(); it_rs++) {
		ofs << (*it_rs).m_date << " " << (*it_rs).m_time << " "
			<< (*it_rs).m_username << " " << (*it_rs).m_name << " "
			<< (*it_rs).m_room_ID << " " << (*it_rs).m_room_num << " "
			<< (*it_rs).m_status << " " << (*it_rs).no_update << endl;
	}
	//同步数据
	this->CRS.computer_update();

	ofs.close();
}