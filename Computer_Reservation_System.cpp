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

//��ʼ��
void computer_reservation_system::CRS_start() {
	crm.reserve(3);
	ifstream ifs;
	//int temp_room_id, temp_room_num;
	ifs.open(COMPUTER_ROOM_FILE, ios::in);
	//����������Ϣ�����ļ�
	while (ifs >> CR.room_ID && ifs >> CR.room_num&&ifs>>CR.room_remainder&&ifs>>CR.toom_reservation_num) {
		crm.push_back(CR);
	}
	ifs.close();

	m_vrs.clear();
	ifstream ifs_rs;
	ifs_rs.open(RESERVATION_FILE,ios::in);

	//д�������Ϣ����
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
	//ͬ������ʣ��ĵ���
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


//���˵�
void computer_reservation_system::Main_Menu() {
	cout << "======================  ��ӭ�������ǲ��ͻ���ԤԼϵͳ  ====================="
		<< endl;
	cout << endl << "�������������" << endl;
	cout << "\t\t -------------------------------\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          1.ѧ������           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          2.��    ʦ           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          3.�� �� Ա           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t|          0.��    ��           |\n";
	cout << "\t\t|                               |\n";
	cout << "\t\t -------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//ѧ���˵�
void Student::Student_Menu() {
	cout << "��ӭѧ����" << Student::m_Name << " ��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����ԤԼ        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.ȡ��ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.�˳���¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//��ʦ�˵�
void Teacher::Teacher_Menu() {
	cout << "��ӭ��ʦ��" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.�鿴����ԤԼ        |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.�˳���¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����Ա�˵�
void Administrator::Administrator_menu() {
	cout << "��ӭ����Ա��"<<UID.m_username<<" ��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.�˳���¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}