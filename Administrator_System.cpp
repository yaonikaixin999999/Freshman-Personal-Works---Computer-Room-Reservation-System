#include"Administrator_system.h"
using namespace std;

class my_print_crs {
public:
	void operator()(Computer_Room CR) {
		cout << "������ţ�" << CR.room_ID << " ���������" << CR.room_num << " ʣ�����������" << CR.room_remainder << endl;
	}
};

Administrator::Administrator() {
	this->administrator_start_process();
}

//��ʼ��
void Administrator::administrator_start_process() {
	this->Administrator_log_in = false;
	this->UID.m_username = "";
	this->CRS.computer_update();
}

//����Ա��¼����
void Administrator::administrator_login_screen() {
	ifstream ifs;
	ifs.open(ADMINISTRATOR_FILE, ios::in);
	string username,  password;
	string temp_username, temp_password;
	cout << "���������Ĺ���Ա��" << endl;
	cin >> username;
	cout << "����������" << endl;
	cin >> password;
	while (getline(ifs, temp_username, ' ')) {
		if (temp_username == username) {
			getline(ifs, temp_password, '\n');
			if (temp_password == password) {
				cout << "����Ա��֤��¼�ɹ���" << endl;
				UID.m_username = username;
				this->Administrator_log_in= true;
				system("pause");
				system("cls");
			}
		}
	}
	if (!this->Administrator_log_in) {
		cout << "�˺Ż��������" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
}

//����˺�
void Administrator::Add_username() {
	int temp_choice;
	cout << "����������˺ŵ����ͣ�" << endl;
	while (1) {
		cout << "1.ѧ�� 2.��ʦ" << endl;
		cin >> temp_choice;
		if (temp_choice != 1 && temp_choice != 2) {
			cout << "�����������������!" << endl;
		}
		else if(temp_choice==1) {
			ofstream ofs;
			ofs.open(STUDENT_FILE,ios::out|ios::app);
			string username, name, password;
			cout << "������ѧ��" << endl;
			cin >> username;
			cout << "����������" << endl;
			cin >> name;
			cout << "����������" << endl;
			cin >> password;
			ofs << username << " " << name << " " << password << endl;
			cout << "��ӳɹ�" << endl;
			ofs.close();
			system("pause");
			system("cls");

			break;
		}
		else if (temp_choice==2) {
			ofstream ofs;
			ofs.open(TEACHER_FILE, ios::out | ios::app);
			string username, name, password;
			cout << "������ְ����" << endl;
			cin >> username;
			cout << "����������" << endl;
			cin >> name;
			cout << "����������" << endl;
			cin >> password;
			ofs << username << " " << name << " " << password << endl;
			cout << "��ӳɹ�" << endl;
			ofs.close();
			system("pause");
			system("cls");

			break;
		}
	}
}

//�鿴�˺�
void Administrator::View_username() {
	int temp_choice;
	cout << "������鿴����:" << endl;
	while (1) {
		cout << "1.�鿴����ѧ�� 2.�鿴������ʦ" << endl;
		cin >> temp_choice;
		if (temp_choice != 1 && temp_choice != 2) {
			cout << "�����������������" << endl;
		}
		else if (temp_choice==1) {
			ifstream ifs;
			ifs.open(STUDENT_FILE, ios::in);
			if (ifs.is_open()) {
				string temp_username, temp_name, temp_password;
				cout << "����ѧ����Ϣ���£�" << endl;
				while (ifs.is_open()) {
					getline(ifs, temp_username, ' ');
					if (temp_username != "") {
						cout << "ѧ�ţ�" << temp_username;
						getline(ifs, temp_name, ' ');
						cout << " ������" << temp_name;
						getline(ifs, temp_password, '\n');
						cout << " ���룺" << temp_password << endl;
					}
					else
						break;
				}
			}
			else {
				cout << "�ļ������ڻ�����Ϊ��" << endl;
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
				cout << "������ʦ��Ϣ���£�" << endl;
				while (ifs >> temp_username && ifs >> temp_name && ifs >> temp_password) {
					cout << "ְ���ţ�" << temp_username;
					cout << " ������" << temp_name;
					cout << " ���룺" << temp_password << endl;
				}
			}
			else {
				cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
			}
			ifs.close();
			system("pause");
			system("cls");
			break;
		}
	}
}

//�鿴����
void Administrator::View_computer_room() {
	for_each(CRS.crm.begin(), CRS.crm.end(), my_print_crs());
	system("pause");
	system("cls");
}

//���ԤԼ
void Administrator::clear_reservation() {
	ofstream ofs;
	ofs.open(RESERVATION_FILE,ios::out);
	if (!ofs.is_open()) {
		cout << "�ļ�������" << endl;
	}
	else {
		ofs.open(RESERVATION_FILE, ios::trunc);
		this->CRS.vrs.clear();
		this->CRS.computer_update();
		cout << "ԤԼ��¼�����" << endl;
	}
	system("pause");
	system("cls");
	ofs.close();
}

//����Ա��¼����
void Administrator::Administrator_system_process() {
	this->administrator_login_screen();
	if (this->Administrator_log_in) {
		int temp_choice;
		while (1) {
			this->Administrator_menu();
			cin >> temp_choice;
			if (temp_choice != 1 && temp_choice != 2 && temp_choice != 3 && temp_choice != 4 && temp_choice != 0) {
				cout << "�����������������" << endl;
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