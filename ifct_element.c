//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};

typedef struct ifs_ele{
	int index; 
	int age;
	int date;
	place_t place[N_HISTORY];//���� ���� �̵���θ� ������ place_t �迭�� ������ ������
		
}ifs_ele_t; //done



char* ifctele_getPlaceName(int placeIndex) //placeindex�� �Է¹޾� placeName�� ����ϴ� �Լ� 
{
	return countryName[placeIndex];
}

	
void* ifctele_genElement(int index, int age, unsigned int date, int place[N_HISTORY])
{	int i;	
	ifs_ele_t*ptr;

	ptr=malloc(sizeof(ifs_ele_t)*N_HISTORY); //�����޸��� ũ�⸦ ��Ƽ� ptr�����Ϳ� �Ҵ��� 
	
	ptr->index=index;
	ptr->age=age;
	ptr->date=date;
	for(i=0;i<5;i++){
		ptr->place[i]=place[i];}//
	return ptr;
} 
	
	
int ifctele_getAge(void* obj)  //ȯ���� ���հ� ��� �Լ� 
{
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr�����Ϳ� �Է¹��� obj������ ���� 
		
	return ptr->age; //���հ� ��ȯ 
} 

int ifctele_getHistPlaceIndex(void*obj, int index) //ȯ���� �̵���� ��� �Լ�
{	int i=0;
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr�����Ϳ� �Է¹��� obj������ ����
		
	return (ptr->place[index]); //ȯ�ڰ� �̵��� ��� ��ȯ 
}

unsigned int ifctele_getinfestedTime(void*obj) //ȯ���� �������� ��� �Լ�
{
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr�����Ϳ� �Է¹��� obj������ ����
	 
	return (ptr->date); //ȯ�ڰ� ������ ���� ��ȯ
}

	
void ifctele_printElement(void *obj)  //ȯ���� �� ���� ��� �Լ�
{	int i=0;
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr�����Ϳ� �Է¹��� obj������ ����
	
	printf("index: %i\n", ptr->index);
	printf("Age: %i\n", ptr->age);
	printf("date: %i\n", ptr->date);
	printf("place:");
	for(i;i<N_HISTORY;i++) //ȯ�ڰ� �̵��� ��Ұ� 5���̴� �׸�ŭ �ݺ�  
	{  
		printf("%s(%i)   ", ifctele_getPlaceName(ptr->place[i]),ptr->date-4+i); //ȯ���� �̵� ��� ���, ��ȣ�� �� ��Ҹ� �̵��� �������� ���� ��� 
	}
	printf("\n");
	
}

int isMet(int now_patient,int i_patient)
{	int i,j;
	void *ifct_element1,*ifct_element2;
	int met_time=0,a;
	int move_place_index[20],move_place_index_i[20]; //now_patient�� �̵���� �迭 
	char move_place_name[20],move_place_name_i[20];
	ifs_ele_t*ptr1;
	ifs_ele_t*ptr2;
	int place1[20],place2[20];
	
	a=ifctdb_getData(now_patient);
	ifct_element1=&a;
	move_place_index[20]=ifctele_getHistPlaceIndex(ifct_element1,now_patient); //now_patient�� �̵���� index�� ����  
	
	ifct_element2=ifctdb_getData(i_patient);
	move_place_index_i[20]=ifctele_getHistPlaceIndex(ifct_element2,i_patient); //i_patient�� �̵���� index�� ����
	
	for(i=2;i<N_HISTORY;i++)
	{  
        place1[i]=move_place_index[i]; //now_patient�� �̵���θ� ptr1�� ���� 
        place2[i]=move_place_index_i[i]; //i_patient�� �̵���θ� ptr1�� ���� 
        
		if(place1[i-2]==place2[i]) //now_patient�� i_patient�� �̵���� ��� �̸� �� 
		{	
			met_time==(ifctele_getinfestedTime(ifct_element2)-(4-i));
			
			return met_time;
		}
		else
			return -1;
	
	}
}

int coverTimeToIndex(int time, int infestedTime)
{
	int index=-1;
	
	if(time<=infestedTime && time > infestedTime-N_HISTORY)
	{
		index=N_HISTORY-(infestedTime-time)-1; 
	}
	return index;
}

/*	
int function_{
	
	ifs_ele_t(ifs1);
} 
*/
