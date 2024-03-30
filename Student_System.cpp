#include"Student_system.h"
using namespace std;

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

class my_print_stu {
public:
	void operator()(Computer_Room CR) {
		cout << CR.room_ID << "�Ż�����ʣ���������" << CR.room_remainder << endl;
	}
};

Student::Student() {
	this->student_start_process();
}

//��ʼ��
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

	//ͬ������
	this->crs.computer_update();

	//��¼�����������
	for (vector<reservation_status>::iterator it_t = this->crs.vrs.begin(); it_t != this->crs.vrs.end(); it_t++) {
		if ((*it_t).m_status == 0 || (*it_t).m_status == -1)
			this->crs.temp_computer_num[(*it_t).m_room_ID - 1] -= (*it_t).m_room_num;
		else if((*it_t).m_status == 1 || (*it_t).m_status == 2)
			this->crs.temp_computer_num[(*it_t).m_room_ID - 1] += (*it_t).m_room_num;
	}
}

//��¼����
void Student::student_login_screen() {
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	string username, name, password;
	string temp_username, temp_name, temp_password;
	cout << "���������ѧ��" << endl;
	cin >> username;
	cout << "�������û���" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> password;

	while (ifs >> temp_username && ifs >> temp_name && ifs >> temp_password) {
			if (temp_username == username&& temp_name == name&& temp_password == password) {
				cout << "ѧ����֤��¼�ɹ���" << endl;
				this->m_Name = temp_name;
				UID.m_username = temp_username;
				UID.m_password = temp_password;
				this->student_log_in = true;

				//ͬ���ҵ�ԤԼ
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
		cout << "�û�����ѧ�Ż��������" << endl;
		system("pause");
		system("cls");
	}
	ifs.close();
}

//����ԤԼ
void Student::Apply_reservation() {
	ofstream ofs;
	ofs.open(RESERVATION_FILE, ios::out | ios::app);
	cout << "��������ʱ��Ϊ��һ������!" << endl;
	int temp_chioce, temp_chioce_1;
	cout << "����������ԤԼʱ��" << endl;
	while (1) {
		cout << "1.��һ 2.�ܶ� 3.���� 4.���� 5.����" << endl;
		cin >> temp_chioce;
		if (temp_chioce!=1&& temp_chioce != 2 && temp_chioce != 3 && temp_chioce != 4 && temp_chioce != 5) {
			cout << "�����������������" << endl;
			system("pause");
		}
		else {
			while (1) {
				cout << "1.���� 2.����" << endl;
				cin >> temp_chioce_1;
				if (temp_chioce_1 != 1 && temp_chioce_1 != 2) {
					cout << "�����������������" << endl;
					system("pause");
				}
				else {
					int temp_choice_2;
					while (1) {
						cout << "��ѡ�������" << endl; 
						for_each(crs.crm.begin(), crs.crm.end(), my_print_stu());
						cin >> temp_choice_2;
						if (temp_choice_2 != 1 && temp_choice_2 != 2 && temp_choice_2 != 3) {
							cout << "�������������������" << endl;
							system("pause");
						}
						else {
							int temp_num;
							cout << "����������ҪԤԼ������" << endl;
							cin >> temp_num;
							if (temp_num > (crs.crm.begin() + temp_choice_2-1)->room_remainder) {
								cout << "���������ѳ���ʣ���������" << endl;
								system("pause");
								system("cls");
							}
							else if(temp_num == 0){
								cout << "���������޷�����0̨����" << endl;
								system("pause");
								system("cls");
							}
							else {

								//д��ԤԼ����Ϣ
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

								//д�������Ϣ
								(crs.crm.begin() + temp_choice_2-1)->toom_reservation_num += temp_num;

								//������д���ļ�
								ofs << this->crs.RS.m_date << " " << this->crs.RS.m_time << " " << this->crs.RS.m_username 
									<< " " << this->crs.RS.m_name<< " " << this->crs.RS.m_room_ID
									<< " " << this->crs.RS.m_room_num << " " << this->crs.RS.m_status 
									<< " " << this->crs.RS.no_update << endl;

								cout << "ԤԼ�ɹ������������" << endl;
								system("pause");
								system("cls");

								//ͬ������
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

//�鿴�ҵ�ԤԼ
void Student::View_my_reservation() {

	if (crs.m_vrs.empty()) {
		cout << "����Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		/*for_each(this->crs.m_vrs.begin(), this->crs.m_vrs.end(), my_print_rs());*/
		for (vector<reservation_status>::iterator it_vrs = this->crs.vrs.begin(); it_vrs != this->crs.vrs.end(); it_vrs++) {
			if ((*it_vrs).m_name == this->m_Name) {
				cout<< "ԤԼ���ڣ�" << ((*it_vrs).md.Date((*it_vrs).m_date)) << " ʱ��Σ�" 
					<< ((*it_vrs).mt.Time((*it_vrs).m_time))
					<< " ������ţ�" << ((*it_vrs).m_room_ID) << " ������Ե�������"
					<< ((*it_vrs).m_room_num) << " ״̬��" 
					<< ((*it_vrs).ms.Status((*it_vrs).m_status)) << endl;
			}
		}
		system("pause");
		system("cls");
	}
}

//�鿴����ԤԼ
void Student::Sut_View_all_reservation() {
	if (this->crs.vrs.empty()) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		for_each(this->crs.vrs.begin(), this->crs.vrs.end(), my_print_rs());
		system("pause");
		system("cls");
	}
}

//ȡ��ԤԼ
void Student::Cancel_reservation() {
	bool exist = false;
	if (this->crs.m_vrs.empty()) {
		cout << "�ļ������ڻ�����Ϊ�գ�" << endl;
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
			cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ��������������Ҫȡ���ļ�¼���:" << endl;
			int temp_choice, i = 1;
			//��¼����ȡ����ԤԼ������
			vector<int>v_serial_number;
			while (1) {
				for (vector<reservation_status>::iterator it_m = this->crs.vrs.begin(); it_m != this->crs.vrs.end(); it_m++) {
					//�ҵ�����е�ԤԼ��¼
					if ((*it_m).m_name==this->m_Name && (*it_m).m_status == 1 && (*it_m).no_update==false) {
						v_serial_number.push_back(i);
						cout << i << ". ԤԼ���ڣ�" << ((*it_m).md.Date((*it_m).m_date)) << " ʱ��Σ�" 
							<< ((*it_m).mt.Time((*it_m).m_time))
							<< " ������ţ�" << ((*it_m).m_room_ID) << " ������Ե�������"
							<< ((*it_m).m_room_num) << " ״̬��" 
							<< ((*it_m).ms.Status((*it_m).m_status)) << endl;
						++i;
					}
				}
				cout << "��������Ҫȡ����ԤԼ��0������" << endl;
				cin >> temp_choice;
				if (temp_choice >= i) {
					cout << "�����������������룡" << endl;
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
						//���ٵ���ԤԼ������
						//������
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

						//ͬ������
						this->crs.computer_update();

						cout << "��ȡ��ԤԼ" << endl;
						system("pause");
						system("cls");
						break;
					}
				}
			}
		}
		else {
			cout << "û�п���ȡ����ԤԼ��" << endl;
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
				cout << "�����������������" << endl;
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

Student::~Student() {
	//���»����������ļ���
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