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
	place_t place[N_HISTORY];//감점 직전 이동경로를 저장할 place_t 배열을 선언해 생성함
		
}ifs_ele_t; //done



char* ifctele_getPlaceName(int placeIndex) //placeindex를 입력받아 placeName을 출력하는 함수 
{
	return countryName[placeIndex];
}

	
void* ifctele_genElement(int index, int age, unsigned int date, int place[N_HISTORY])
{	int i;	
	ifs_ele_t*ptr;

	ptr=malloc(sizeof(ifs_ele_t)*N_HISTORY); //동적메모리의 크기를 잡아서 ptr포인터에 할당함 
	
	ptr->index=index;
	ptr->age=age;
	ptr->date=date;
	for(i=0;i<5;i++){
		ptr->place[i]=place[i];}//
	return ptr;
} 
	
	
int ifctele_getAge(void* obj)  //환자의 나잇값 출력 함수 
{
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr포인터에 입력받은 obj포인터 대입 
		
	return ptr->age; //나잇값 반환 
} 

int ifctele_getHistPlaceIndex(void*obj, int index) //환자의 이동장소 출력 함수
{	int i=0;
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr포인터에 입력받은 obj포인터 대입
		
	return (ptr->place[index]); //환자가 이동한 장소 반환 
}

unsigned int ifctele_getinfestedTime(void*obj) //환자의 감염시점 출력 함수
{
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr포인터에 입력받은 obj포인터 대입
	 
	return (ptr->date); //환자가 감염된 시점 반환
}

	
void ifctele_printElement(void *obj)  //환자의 각 정보 출력 함수
{	int i=0;
	ifs_ele_t*ptr=(ifs_ele_t *)obj; //ptr포인터에 입력받은 obj포인터 대입
	
	printf("index: %i\n", ptr->index);
	printf("Age: %i\n", ptr->age);
	printf("date: %i\n", ptr->date);
	printf("place:");
	for(i;i<N_HISTORY;i++) //환자가 이동한 장소가 5개이니 그만큼 반복  
	{  
		printf("%s(%i)   ", ifctele_getPlaceName(ptr->place[i]),ptr->date-4+i); //환자의 이동 장소 출력, 괄호로 각 장소를 이동할 때마다의 시점 출력 
	}
	printf("\n");
	
}

int isMet(int now_patient,int i_patient)
{	int i,j;
	void *ifct_element1,*ifct_element2;
	int met_time=0,a;
	int move_place_index[20],move_place_index_i[20]; //now_patient의 이동경로 배열 
	char move_place_name[20],move_place_name_i[20];
	ifs_ele_t*ptr1;
	ifs_ele_t*ptr2;
	int place1[20],place2[20];
	
	a=ifctdb_getData(now_patient);
	ifct_element1=&a;
	move_place_index[20]=ifctele_getHistPlaceIndex(ifct_element1,now_patient); //now_patient의 이동경로 index를 저장  
	
	ifct_element2=ifctdb_getData(i_patient);
	move_place_index_i[20]=ifctele_getHistPlaceIndex(ifct_element2,i_patient); //i_patient의 이동경로 index를 저장
	
	for(i=2;i<N_HISTORY;i++)
	{  
        place1[i]=move_place_index[i]; //now_patient의 이동경로를 ptr1에 저장 
        place2[i]=move_place_index_i[i]; //i_patient의 이동경로를 ptr1에 저장 
        
		if(place1[i-2]==place2[i]) //now_patient와 i_patient의 이동경로 장소 이름 비교 
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
