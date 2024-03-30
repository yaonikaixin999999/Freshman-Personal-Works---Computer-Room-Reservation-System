#include"Student_system.h"
using namespace std;

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

class my_print_stu {
public:
	void operator()(Computer_Room CR) {
		cout << CR.room_ID << "号机房的剩余电脑数量" << CR.room_remainder << endl;
	}
};

Student::Student() {
	this->student_start_process();
}

//初始化
void Student::student_start_process() {
	this->student_log_in = false;
	this->m_Name = "";
	if (!this->crs.vrs.empty()) {
		for (vector<reservation_status>::iterator it_m = this->crs.vrs.begin(); it_m != this->crs.vrs.end(); it_m++) {
			if ((*it_m).m_name == this->m_Name) {
				this->crs.m_vrs.push_back((*it_m));
			}
		}
	}

	//同步数据
	this->crs.computer_update();

	//记录申请电脑数量
	for (vector<reservation_status>::iterator it_t = this->crs.vrs.begin(); it_t != this->crs.vrs.end(); it_t++) {
		if ((*it_t).m_status == 0 || (*it_t).m_status == -1)
			this->crs.temp_computer_num[(*it_t).m_room_ID - 1] -= (*it_t).m_room_num;
		else if((*it_t).m_status == 1 || (*it_t).m_status == 2)
			this->crs.temp_computer_num[(*it_t).m_room_ID - 1] += (*it_t).m_room_num;
	}
}

//登录界面
void Student::student_login_screen() {
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	string username, name, password;
	string temp_username, temp_name, temp_password;
	cout << "请输入你的学号" << endl;
	cin >> username;
	cout << "请输入用户名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> password;

	while (ifs >> temp_username && ifs >> temp_name && ifs >> temp_password) {
			if (temp_username == username&& temp_name == name&& temp_password == password) {
				cout << "学生验证登录成功！" << endl;
				this->m_Name = temp_name;
				UID.m_username = temp_username;
				UID.m_password = temp_password;
				this->student_log_in = true;

				//同步我的预约
				for (vector<reservation_status>::iterator it_vrs = this->crs.vrs.begin(); it_vrs != this->crs.vrs.end(); it_vrs++) {
					if ((*it_vrs).m_name == this->m_Name) {
						this->crs.m_vrs.push_back(*it_vrs);
					}
				}

				system("pause");
				system("cls");			
			}
	}
	if (!this->student_log_in) {
		cout << "用户名，学号或密码错误！" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
}

//申请预约
void Student::Apply_reservation() {
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::out | ios::app);
	cout << "机房开放时间为周一至周五!" << endl;
	int temp_chioce, temp_chioce_1;
	cout << "请输入申请预约时间" << endl;
	while (1) {
		cout << "1.周一 2.周二 3.周三 4.周四 5.周五" << endl;
		cin >> temp_chioce;
		if (temp_chioce!=1&& temp_chioce != 2 && temp_chioce != 3 && temp_chioce != 4 && temp_chioce != 5) {
			cout << "输入错误，请重新输入" << endl;
			system("pause");
		}
		else {
			while (1) {
				cout << "1.上午 2.下午" << endl;
				cin >> temp_chioce_1;
				if (temp_chioce_1 != 1 && temp_chioce_1 != 2) {
					cout << "输入错误，请重新输入" << endl;
					system("pause");
				}
				else {
					int temp_choice_2;
					while (1) {
						cout << "请选择机房：" << endl; 
						for_each(crs.crm.begin(), crs.crm.end(), my_print_stu());
						cin >> temp_choice_2;
						if (temp_choice_2 != 1 && temp_choice_2 != 2 && temp_choice_2 != 3) {
							cout << "输入错误，请重新数输入" << endl;
							system("pause");
						}
						else {
							int temp_num;
							cout << "请输入您想要预约的数量" << endl;
							cin >> temp_num;
							if (temp_num > (crs.crm.begin() + temp_choice_2-1)->room_remainder) {
								cout << "输入有误！已超过剩余电脑数量" << endl;
								system("pause");
								system("cls");
							}
							else if(temp_num == 0){
								cout << "输入有误！无法申请0台电脑" << endl;
								system("pause");
								system("cls");
							}
							else {

								//写入预约的信息
								this->crs.RS.m_date = temp_chioce;
								this->crs.RS.m_time = temp_chioce_1;
								this->crs.RS.m_username = UID.m_username;
								this->crs.RS.m_name = this->m_Name;
								this->crs.RS.m_room_ID = temp_choice_2;
								this->crs.RS.m_room_num = temp_num;
								this->crs.RS.m_status = 1;
								this->crs.RS.no_update = false;
								crs.vrs.push_back(this->crs.RS);
								crs.m_vrs.push_back(this->crs.RS);

								//写入机房信息
								(crs.crm.begin() + temp_choice_2-1)->toom_reservation_num += temp_num;

								//将数据写入文件
								ofs << this->crs.RS.m_date << " " << this->crs.RS.m_time << " " << this->crs.RS.m_username 
									<< " " << this->crs.RS.m_name<< " " << this->crs.RS.m_room_ID
									<< " " << this->crs.RS.m_room_num << " " << this->crs.RS.m_status 
									<< " " << this->crs.RS.no_update << endl;

								cout << "预约成功！正在审核中" << endl;
								system("pause");
								system("cls");

								//同步数据
								this->crs.computer_update();
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}
	ofs.close();
}

//查看我的预约
void Student::View_my_reservation() {

	if (crs.m_vrs.empty()) {
		cout << "数据为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		/*for_each(this->crs.m_vrs.begin(), this->crs.m_vrs.end(), my_print_rs());*/
		for (vector<reservation_status>::iterator it_vrs = this->crs.vrs.begin(); it_vrs != this->crs.vrs.end(); it_vrs++) {
			if ((*it_vrs).m_name == this->m_Name) {
				cout<< "预约日期：" << ((*it_vrs).md.Date((*it_vrs).m_date)) << " 时间段：" 
					<< ((*it_vrs).mt.Time((*it_vrs).m_time))
					<< " 机房编号：" << ((*it_vrs).m_room_ID) << " 申请电脑的数量："
					<< ((*it_vrs).m_room_num) << " 状态：" 
					<< ((*it_vrs).ms.Status((*it_vrs).m_status)) << endl;
			}
		}
		system("pause");
		system("cls");
	}
}

//查看所有预约
void Student::Sut_View_all_reservation() {
	if (this->crs.vrs.empty()) {
		cout << "文件不存在或数据为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		for_each(this->crs.vrs.begin(), this->crs.vrs.end(), my_print_rs());
		system("pause");
		system("cls");
	}
}

//取消预约
void Student::Cancel_reservation() {
	bool exist = false;
	if (this->crs.m_vrs.empty()) {
		cout << "文件不存在或数据为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		/*vector<vector<reservation_status>>temp_vrs;*/
		for (vector<reservation_status>::iterator it = this->crs.m_vrs.begin(); it != this->crs.m_vrs.end(); it++) {
			if ((*it).m_status == 1) {
				exist = true;
				/*temp_vrs.push_back();*/
			}
		}
		if (exist) {
			cout << "审核中或预约成功的记录可以取消，请输入您想要取消的记录序号:" << endl;
			int temp_choice, i = 1;
			//记录可以取消的预约的索引
			vector<int>v_serial_number;
			while (1) {
				for (vector<reservation_status>::iterator it_m = this->crs.vrs.begin(); it_m != this->crs.vrs.end(); it_m++) {
					//找到审核中的预约记录
					if ((*it_m).m_name==this->m_Name && (*it_m).m_status == 1 && (*it_m).no_update==false) {
						v_serial_number.push_back(i);
						cout << i << ". 预约日期：" << ((*it_m).md.Date((*it_m).m_date)) << " 时间段：" 
							<< ((*it_m).mt.Time((*it_m).m_time))
							<< " 机房编号：" << ((*it_m).m_room_ID) << " 申请电脑的数量："
							<< ((*it_m).m_room_num) << " 状态：" 
							<< ((*it_m).ms.Status((*it_m).m_status)) << endl;
						++i;
					}
				}
				cout << "请输入想要取消的预约，0代表返回" << endl;
				cin >> temp_choice;
				if (temp_choice >= i) {
					cout << "输入有误，请重新输入！" << endl;
					v_serial_number.clear();
					i=1;
					system("pause");
				}
				else {
					if (temp_choice <= 0) {
						system("pause");
						system("cls");
						break;
					}
					else if(temp_choice <= i&&temp_choice>0){
						vector<reservation_status>temp_v;
						//减少电脑预约的数量
						//机房号
						int temp_room_ID = this->crs.vrs[v_serial_number[temp_choice - 1]-1].m_room_ID;

						for (vector<reservation_status>::iterator temp_it_vrs = this->crs.vrs.begin(); temp_it_vrs != this->crs.vrs.end(); temp_it_vrs++) {
							if ((*temp_it_vrs).m_name == this->m_Name && (*temp_it_vrs).m_room_ID == temp_room_ID) {
								(*temp_it_vrs).no_update = true;
								temp_v.push_back(*temp_it_vrs);
								/*(*temp_it_vrs).m_status = 0;*/
								temp_v[0].m_status = 0;
								this->crs.vrs.push_back(temp_v[0]);
								temp_v.clear();
								break;
							}
						}

						//同步数据
						this->crs.computer_update();

						cout << "已取消预约" << endl;
						system("pause");
						system("cls");
						break;
					}
				}
			}
		}
		else {
			cout << "没有可以取消的预约！" << endl;
			system("pause");
			system("cls");
		}
	}
}

void Student::student_system_process() {
	this->student_login_screen();
	if (this->student_log_in) {
		int temp_choice;
		while (1) {
			this->Student_Menu();
			cin >> temp_choice;
			if (temp_choice != 1 && temp_choice != 2 && temp_choice != 3 && temp_choice != 4 && temp_choice != 0) {
				cout << "输入错误，请重新输入" << endl;
				system("pause");
				system("cls");
			}
			else {
				if (temp_choice == 1) {
					this->Apply_reservation();
				}
				else if(temp_choice==2){
					this->View_my_reservation();
				}
				else if (temp_choice==3) {
					this->Sut_View_all_reservation();
				}
				else if (temp_choice == 4) {
					this->Cancel_reservation();
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

Student::~Student() {
	//更新机房数据至文件中
	ofstream ofs;
	ofs.open(RESERVATION_FILE,ios::trunc);
	for (vector<reservation_status>::iterator it_rs = this->crs.vrs.begin(); it_rs != this->crs.vrs.end(); it_rs++) {
		ofs << (*it_rs).m_date << " " << (*it_rs).m_time << " "
			<< (*it_rs).m_username << " " << (*it_rs).m_name << " "
			<< (*it_rs).m_room_ID << " " << (*it_rs).m_room_num << " "
			<< (*it_rs).m_status <<" " << (*it_rs).no_update<<endl;
	}

	ofs.close();
}