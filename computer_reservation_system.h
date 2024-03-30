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

	int room_ID;//������
	int room_num;//��������������
	int room_remainder;//ʣ���������
	int toom_reservation_num;//���ڱ�ԤԼ�е��Ե�����
};

class userID {
public:
	userID();

	string m_username;  //�û���
	string m_password;  //����
};

class m_time {
public:
	string Time(int m_time) {
		if (m_time == 1) {
			return "����";
		}
		else {
			return "����";
		}
	}
};

class m_date {
public:
	string Date(int m_date) {
		switch (m_date){
		case 1:
			return "����һ";
		case 2:
			return  "���ڶ�";
		case 3:
			return  "������";
		case 4:
			return  "������";
		case 5:
			return  "������";
		case 6:
			return  "������";
		case 7:
			return  "������";
		}
	}
};

class m_status {
public:
	string Status(int m_status) {
		switch (m_status) {
		case -1:
			return "��˲�ͨ��";
		case 0:
			return "��ȡ��";
		case 1:
			return "�����";
		case 2:
			return "�����ͨ��";
		}
	}
};

class reservation_status {
public:
	reservation_status() {}

	//����
	m_date md;
	//״̬
	m_status ms;
	//ʱ��
	m_time mt;
	int m_date;//����
	int m_time;//ʱ��

	//1 ����
	//2 ����

	string m_username;//�������û���
	string m_name;//����������
	int m_room_ID;//����Ļ�����
	int m_room_num;//�����������
	int m_status;//���״̬

	bool no_update;//����Ҫ���±�־

	//-1.��˲�ͨ��
	//0.��ȡ��
	//1.�����
	//2.�����ͨ��
};

class computer_reservation_system {
public:
	//���캯��
	computer_reservation_system();
	
	//����ԤԼ��������
	Computer_Room CR;

	//��ʼ��
	void CRS_start();

	//ȫ�������¼
	vector<reservation_status>vrs;

	//���������¼
	vector<reservation_status>m_vrs;
	
	//���µ�������
	void computer_update();

	//��������
	vector<Computer_Room>crm;

	//���������¼
	reservation_status RS;

	//��¼��ʱ���������
	int temp_computer_num[3] = { 0,0,0 };

	//���˵�
	void Main_Menu();

	//��������
	int computer_room_1, computer_room_2, computer_room_3;
};

