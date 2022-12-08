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
	place_t place[N_HISTORY];//감점 직전 이동경로->정수(enum) place_t 배열선언  (N_HISTORY)
		
}ifs_ele_t; //done



char* ifctele_getPlaceName(int placeIndex)
{
	return countryName[placeIndex];
}

	
void* ifctele_genElement(int index, int age, unsigned int date, int place[N_HISTORY])
{	int i;	
	ifs_ele_t*ptr;

	ptr=malloc(sizeof(ifs_ele_t));
	
	ptr->index=index;
	ptr->age=age;
	ptr->date=date;
	
	for(i=0;i<5;i++)
		ptr->place[i]=place[i];//
			
	return ptr;
} //동적메모리를잡아서 메인한테넘겨주는형태로  
	
	
int ifsele_getAge(void* obj){
	ifs_ele_t*ptr=(ifs_ele_t *)obj;
		
	return ptr->age;
} //done

int ifctele_getHistPlaceIndex(void*obj, int index);
unsigned int ifctele_getinfestedTime(void*obj);	
void ifsele_printElement(void *obj);

	
void ifsele_printElement(void *obj)
{	int i;
	ifs_ele_t*ptr=(ifs_ele_t *)obj;
	
	printf("Age: %i\n", ptr->age);
	printf("index: %i\n", ptr->index);
	printf("date: %i\n", ptr->date);
	for(i=0;i<5;i++)
		printf("palce: %s\n", countryName[ptr->place[i]]);
	/*
	for(ifs_cnt)
	{ printf(ifsarray[i].index);
	}
	*/
}
	
/*	
int function_{
	
	ifs_ele_t(ifs1);
} 
*/
