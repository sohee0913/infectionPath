//
//  main.c
//  infestPath
//
//  Created by Juyeop Kim on 2022/10/20.
//

#include <stdio.h>
#include <string.h>
#include "ifct_element.h"
#include "ifct_database.h"

#define MENU_PATIENT        1
#define MENU_PLACE          2
#define MENU_AGE            3
#define MENU_TRACK          4
#define MENU_EXIT           0

#define TIME_HIDE           2


int trackInfester(int patient_no, int *detected_time, int *place)
{	int i,met_time=0;
	int infester;
	
	for(i=0;i<ifctdb_len();i++) //i�� ifctdb_len�� ���̸�ŭ �ݺ�
	{
		
		met_time=isMet(patient_no,i);  
		
		if(met_time>0) //���� �� ȯ�ڰ� ���� �����ٸ� 
		{
			if(met_time<*detected_time) //���ݱ��� ���� ȯ�ڵ��� �����ð�(dectected_time) �� �����ð�(met_time)�� ���� �̸��ٸ� 
			{
				infester=i; //�����ڴ� i��° ȯ�� 
		
				return infester; //������ ���� ��ȯ 
			}
		}
		else //���ݱ��� ���� ȯ�� �� �����ð��� ���� �̸��� ���� �� 
			return patient_no; //�Էµ� ȯ�ڰ� �������̹Ƿ� �Էµ�ȯ�� �� ��� 
	}
}

int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    char placename[20];
    int place_index,range_age;
    int min,max;
	int infester,first_infester; 
	int now_patient;
	int *time_1,a,j;
    //------------- 1. loading patient info file ------------------------------
    //1-1. FILE pointer open
    if (argc != 2)
    {
        printf("[ERROR] syntax : infestPath (file path).");
        return -1;
    }
    
    fp = fopen(argv[1],"r");
    if (fp == NULL)
    {
        printf("[ERROR] Failed to open database file!! (%s)\n", argv[1]);
        return -1;
    }
    
    //1-2. loading each patient informations
    int i;
	while(3==fscanf(fp,"%i %i %i",&pIndex,&age,&time)) //fscanf�� ��ȯ���� ������°� �̿� 
    {
    	for(i=0;i<5;i++){
    		fscanf(fp,"%i",&placeHist[i]);
			}

    	ifct_element=ifctele_genElement(pIndex,age,time,placeHist);
    	ifctdb_addTail(ifct_element);
	
		
		//ifctele_printElement(ifct_element);
    	//age=ifctele_getAge(ifct_element);
    	
	}
	
	//ifsele_getelement(...); 
    //1-3. FILE pointer close
    fclose(fp);
    
    /*
    {
    	for(i=0;i<5;i++)
    		printf("%i��° ȯ�� ���� ���:\n");
    		printf("%s", ifctele_getPlaceName(placeHist[i]));
		printf("\n"); 
	}
    */
    do {
        printf("\n=============== INFECTION PATH MANAGEMENT PROGRAM (No. of patients : %i) =============\n", ifctdb_len());
        printf("1. Print details about a patient.\n");                      //MENU_PATIENT
        printf("2. Print list of patients infected at a place.\n");        //MENU_PLACE
        printf("3. Print list of patients in a range of age.\n");          //MENU_AGE
        printf("4. Track the root of the infection\n");                     //MENU_TRACK
        printf("0. Exit.\n");                                               //MENU_EXIT
        printf("=============== ------------------------------------------------------- =============\n\n");
        
        printf("Select a menu :");
        scanf("%d", &menu_selection);
        fflush(stdin);
        
        switch(menu_selection)
        {
            case MENU_EXIT:
                printf("Exiting the program... Bye bye.\n");
                break;
                
            case MENU_PATIENT:
				
				

				printf("patient index :");
				scanf("%i",&pIndex); //�Է¹��� ���� pIndex������ 
				
				ifct_element=ifctdb_getData(pIndex); //ifct_element�� ���                                                                               
				ifctele_genElement(pIndex,age,time,placeHist); //�� ������ �����Ͽ� ifct_element����ü�� ���� 
				ifctele_printElement(ifct_element); //ifct_element�� ��� 
				
				
			         
				
				
                break; 
                
            case MENU_PLACE:
            	
            	
                printf("place name:");
                scanf("%s", &placename); //����ڰ� �Է��� ��Ҹ� placename�� ���� 
                
                
				int cnt=0;
                for(i=0;i<ifctdb_len();i++) //i�� ifctdb_len�� ���̸�ŭ �ݺ�
				{
                	ifct_element=ifctdb_getData(i);  //ifct_element�� i��ŭ�� ȯ�� �� ��ŭ �޾ƿ�
					
                	
                	for(j=3;j<N_HISTORY;j++) //j�� ��� �迭�� 0~4 �� 3,4��°�� �޾ƿ��� ���� j=3,j=4���� 
					{	
						place_index=ifctele_getHistPlaceIndex(ifct_element,j); //���indexf�Լ��� �̿��� place_index�� �� ���� ���� 
						
                		if(strcmp(placename,ifctele_getPlaceName(place_index))==0) //����ڰ� �Է��� placename ���� �� ȯ���� ��ҹ迭�� �� 3,4 ���� ���� �� 
						{
                			cnt++; //cntȽ�� 1ȸ ���� 
                			printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
							ifctele_printElement(ifct_element); //ifct_element���� ��� 
							printf("\n");
                			printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");						
					
						}
					}
				}
				printf("There are %i patients detected in %s\n",cnt,placename);
                
                break;
                
            case MENU_AGE:
                
                printf("minimal age:"); 
                scanf("%i", &min); //����ڰ� �Է��� ���� ���̰��� �ּҰ����� ���� 
                printf("maximal age:");
                scanf("%i", &max); //����ڰ� �Է��� ���� ���̰��� �ִ밪���� ���� 
                
                for(i=0;i<ifctdb_len();i++) //i�� ifctdb_len�� ���̸�ŭ �ݺ� 
				{
                	ifct_element=ifctdb_getData(i); //ifct_element�� i��ŭ�� ȯ�� �� ��ŭ �޾ƿ� 
                	range_age=ifctele_getAge(ifct_element);//range_age(����ڰ� �Է��� ���̰��� ����)=ifctele_getAge�Լ��� ifct_element�� ������ �� 
                	
                	if(min<range_age<max) //�Է��� �ּڰ�(min)<range_age<�Է��� �ִ�(max)�� �� 
					{
						printf("===================================================================\n");
						ifctele_printElement(ifct_element);
						printf("===================================================================\n");
					}
            	}
                break;
                
            case MENU_TRACK:
                
                printf("patient index:");
                scanf("%i", &pIndex);
                while(0<=pIndex<ifctdb_len()+1)
                {	
                	ifct_element=ifctdb_getData(pIndex); //ifct_element�� ���                                                                               
					ifctele_genElement(pIndex,age,time,placeHist);
                	
                	a=ifctele_getinfestedTime(ifct_element); //ifctele_getinfestedTime�Լ��� ���� ifct_element�� ���� �ñ⸦ a�������� 
                	time_1=&a; //a�� time_1�����Ϳ� �Ҵ� 
                	
                	infester=trackInfester(pIndex,time_1,ifct_element); //������=trackInfester�Լ��� pIndex,time_1,ifct_element�� �������� ���� ��°� 
					
                	if(infester!=pIndex) //infester(������)�� �Է��� ȯ���� ��(pIndex)�� ���� ���� �� 
					{
                		place_index=ifctele_getHistPlaceIndex(ifct_element,pIndex); //���index��= �Է��� ȯ���� ��(pIndex)�� ���index�Լ��� ������ ��  
						printf("--> [TRACKING] patient %i is infected by %i (time : %i, place : %s) \n", pIndex, infester, ifctele_getinfestedTime(ifct_element),ifctele_getPlaceName(place_index) );
                		printf("The first infector of %i is %i\n", pIndex, infester);
                	}
					else //infester(������)= �Է��� ȯ���� ��(pIndex) �� �� 
                		printf("%i patient is the first infector",infester); //���� ȯ���� ��(pIndex)�� ����������(infester)�� �� 
                		break;
				}
                
                
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    	return 0;
	}
