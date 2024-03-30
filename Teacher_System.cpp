#include"Teacher_system.h"
using namespace std;

Teacher::Teacher() {
	this->teacher_start_process();
}

class my_print_rs {
public:
	void operator()(reservation_status RS) {
		cout << "ԤԼ���ڣ�" << RS.md.Date(RS.m_date) << " ʱ��Σ�"
			<< RS.mt.Time(RS.m_time) << " ѧ�ţ�" << RS.m_username
			<< " ������" << RS.m_name << " ������ţ�" << RS.m_room_ID
			<< " ԤԼ������" << RS.m_room_num << " ԤԼ״̬��"
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

	//��¼�����������
	for (vector<reservation_status>::iterator it_t = this->CRS.vrs.begin(); it_t != this->CRS.vrs.end(); it_t++) {
		if ((*it_t).m_status == 0 || (*it_t).m_status == -1)
			this->CRS.temp_computer_num[(*it_t).m_room_ID - 1] -= (*it_t).m_room_num;
		else if ((*it_t).m_status == 1 || (*it_t).m_status == 2)
			this->CRS.temp_computer_num[(*it_t).m_room_ID - 1] += (*it_t).m_room_num;
	}
}

//��¼����
void Teacher::teacher_login_screen() {
	ifstream ifs;
	ifs.open(TEACHER_FILE, ios::in);
	string username, name, password;
	string temp_username, temp_name, temp_password;
	cout << "����������ְ����" << endl;
	cin >> username;
	cout << "�������û���" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> password;
	while (ifs >> temp_username && ifs >> temp_name && ifs >> temp_password) {
		if (temp_username == username&& temp_name == name&& temp_password == password) {	
			cout << "��ʦ��֤��¼�ɹ���" << endl;
			this->m_Name = temp_name;
			UID.m_username = temp_username;
			UID.m_password = temp_password;
			this->teacher_log_in = true;
			system("pause");
			system("cls");
		}
	}
	if (!this->teacher_log_in) {
		cout << "�û�����ְ���Ż��������" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
}

//�鿴����ԤԼ
void Teacher::Tea_View_all_reservation() {
	if (this->CRS.vrs.empty()) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		for_each(this->CRS.vrs.begin(), this->CRS.vrs.end(), my_print_rs());
		system("pause");
		system("cls");
	}
}

//���ԤԼ
void Teacher::Audit_reservation() {
	if (this->CRS.vrs.empty()) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		int temp_choice, i = 1;
		vector<int>v_serial_number;
		cout << "����˵�ԤԼ��¼���£�" << endl;
		while (1) {
			cout << "����������Ҫ��˵�ԤԼ���:" << endl;
			for (vector<reservation_status>::iterator it_rs = this->CRS.vrs.begin(); it_rs != this->CRS.vrs.end(); it_rs++) {
				if ((*it_rs).no_update == false && (*it_rs).m_status == 1) {
					v_serial_number.push_back(i);
					cout << i << ". ԤԼ���ڣ�" << ((*it_rs).md.Date((*it_rs).m_date)) << " ʱ��Σ�"
						<< ((*it_rs).mt.Time((*it_rs).m_time))
						<< " ������ţ�" << ((*it_rs).m_room_ID) << " ������Ե�������"
						<< ((*it_rs).m_room_num) << " ״̬��"
						<< ((*it_rs).ms.Status((*it_rs).m_status)) << endl;
					i++;
				}
			}
			cout << "��������˵�ԤԼ��¼��0������:" << endl;
			cin >> temp_choice;
			if (temp_choice > i) {
				cout << "��������,���������룡" << endl;
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
					cout << "��������˽��:" << endl;
					while (1) {
						int temp_choice_1;
						cout << "1.ͨ�� 2.��ͨ�� 3.ȡ��" << endl;
						cin >> temp_choice_1;
						if (temp_choice_1 != 1 && temp_choice_1 != 2&&temp_choice_1!=3) {
							cout << "������������������!" << endl;
							system("pause");
						}
						else if (temp_choice_1 == 3) {
							cout << "��ȡ��" << endl;
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

							cout << "������!" << endl;
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

//��ʦ��¼����
void Teacher::teacher_system_process() {
	this->teacher_login_screen();
	if (this->teacher_log_in) {
		int temp_choice;
		while (1) {
			this->Teacher_Menu();
			cin >> temp_choice;
			if (temp_choice != 1 && temp_choice != 2 && temp_choice != 3 && temp_choice != 4 && temp_choice != 0) {
				cout << "�����������������" << endl;
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
					cout << "��ע����¼" << endl;
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
	//���»����������ļ���
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::trunc);
	for (vector<reservation_status>::iterator it_rs = this->CRS.vrs.begin(); it_rs != this->CRS.vrs.end(); it_rs++) {
		ofs << (*it_rs).m_date << " " << (*it_rs).m_time << " "
			<< (*it_rs).m_username << " " << (*it_rs).m_name << " "
			<< (*it_rs).m_room_ID << " " << (*it_rs).m_room_num << " "
			<< (*it_rs).m_status << " " << (*it_rs).no_update << endl;
	}
	//ͬ������
	this->CRS.computer_update();

	ofs.close();
}