#include"Administrator_system.h"
using namespace std;

class my_print_crs {
public:
	void operator()(Computer_Room CR) {
		cout << "机房编号：" << CR.room_ID << " 最大容量：" << CR.room_num << " 剩余电脑数量：" << CR.room_remainder << endl;
	}
};

Administrator::Administrator() {
	this->administrator_start_process();
}

//初始化
void Administrator::administrator_start_process() {
	this->Administrator_log_in = false;
	this->UID.m_username = "";
	this->CRS.computer_update();
}

//管理员登录界面
void Administrator::administrator_login_screen() {
	ifstream ifs;
	ifs.open(ADMINISTRATOR_FILE, ios::in);
	string username,  password;
	string temp_username, temp_password;
	cout << "请输入您的管理员号" << endl;
	cin >> username;
	cout << "请输入密码" << endl;
	cin >> password;
	while (getline(ifs, temp_username, ' ')) {
		if (temp_username == username) {
			getline(ifs, temp_password, '\n');
			if (temp_password == password) {
				cout << "管理员验证登录成功！" << endl;
				UID.m_username = username;
				this->Administrator_log_in= true;
				system("pause");
				system("cls");
			}
		}
	}
	if (!this->Administrator_log_in) {
		cout << "账号或密码错误！" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
}

//添加账号
void Administrator::Add_username() {
	int temp_choice;
	cout << "请输入添加账号的类型：" << endl;
	while (1) {
		cout << "1.学生 2.老师" << endl;
		cin >> temp_choice;
		if (temp_choice != 1 && temp_choice != 2) {
			cout << "输入错误，请重新输入!" << endl;
		}
		else if(temp_choice==1) {
			ofstream ofs;
			ofs.open(STUDENT_FILE,ios::out|ios::app);
			string username, name, password;
			cout << "请输入学号" << endl;
			cin >> username;
			cout << "请输入姓名" << endl;
			cin >> name;
			cout << "请输入密码" << endl;
			cin >> password;
			ofs << username << " " << name << " " << password << endl;
			cout << "添加成功" << endl;
			ofs.close();
			system("pause");
			system("cls");

			break;
		}
		else if (temp_choice==2) {
			ofstream ofs;
			ofs.open(TEACHER_FILE, ios::out | ios::app);
			string username, name, password;
			cout << "请输入职工号" << endl;
			cin >> username;
			cout << "请输入姓名" << endl;
			cin >> name;
			cout << "请输入密码" << endl;
			cin >> password;
			ofs << username << " " << name << " " << password << endl;
			cout << "添加成功" << endl;
			ofs.close();
			system("pause");
			system("cls");

			break;
		}
	}
}

//查看账号
void Administrator::View_username() {
	int temp_choice;
	cout << "请输入查看内容:" << endl;
	while (1) {
		cout << "1.查看所有学生 2.查看所有老师" << endl;
		cin >> temp_choice;
		if (temp_choice != 1 && temp_choice != 2) {
			cout << "输入错误，请重新输入" << endl;
		}
		else if (temp_choice==1) {
			ifstream ifs;
			ifs.open(STUDENT_FILE, ios::in);
			if (ifs.is_open()) {
				string temp_username, temp_name, temp_password;
				cout << "所有学生信息如下：" << endl;
				while (ifs.is_open()) {
					getline(ifs, temp_username, ' ');
					if (temp_username != "") {
						cout << "学号：" << temp_username;
						getline(ifs, temp_name, ' ');
						cout << " 姓名：" << temp_name;
						getline(ifs, temp_password, '\n');
						cout << " 密码：" << temp_password << endl;
					}
					else
						break;
				}
			}
			else {
				cout << "文件不存在或数据为空" << endl;
			}
			ifs.close();
			system("pause");
			system("cls");
			break;
		}
		else if (temp_choice==2) {
			ifstream ifs;
			ifs.open(TEACHER_FILE, ios::in);
			if (ifs.is_open()) {
				string temp_username, temp_name, temp_password;
				cout << "所有老师信息如下：" << endl;
				while (ifs >> temp_username && ifs >> temp_name && ifs >> temp_password) {
					cout << "职工号：" << temp_username;
					cout << " 姓名：" << temp_name;
					cout << " 密码：" << temp_password << endl;
				}
			}
			else {
				cout << "文件不存在或者记录为空" << endl;
			}
			ifs.close();
			system("pause");
			system("cls");
			break;
		}
	}
}

//查看机房
void Administrator::View_computer_room() {
	for_each(CRS.crm.begin(), CRS.crm.end(), my_print_crs());
	system("pause");
	system("cls");
}

//清空预约
void Administrator::clear_reservation() {
	ofstream ofs;
	ofs.open(RESERVATION_FILE,ios::out);
	if (!ofs.is_open()) {
		cout << "文件不存在" << endl;
	}
	else {
		ofs.open(RESERVATION_FILE, ios::trunc);
		this->CRS.vrs.clear();
		this->CRS.computer_update();
		cout << "预约记录已清空" << endl;
	}
	system("pause");
	system("cls");
	ofs.close();
}

//管理员登录流程
void Administrator::Administrator_system_process() {
	this->administrator_login_screen();
	if (this->Administrator_log_in) {
		int temp_choice;
		while (1) {
			this->Administrator_menu();
			cin >> temp_choice;
			if (temp_choice != 1 && temp_choice != 2 && temp_choice != 3 && temp_choice != 4 && temp_choice != 0) {
				cout << "输入错误，请重新输入" << endl;
				system("pause");
				system("cls");
			}
			else {
				if (temp_choice == 1) {
					this->Add_username();
				}
				else if (temp_choice == 2) {
					this->View_username();
				}
				else if (temp_choice == 3) {
					this->View_computer_room();
				}
				else if (temp_choice == 4) {
					this->clear_reservation();
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