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
	
	for(i=0;i<ifctdb_len();i++) //i는 ifctdb_len의 길이만큼 반복
	{
		
		met_time=isMet(patient_no,i);  
		
		if(met_time>0) //만약 두 환자가 서로 만났다면 
		{
			if(met_time<*detected_time) //지금까지 만난 환자들의 만난시간(dectected_time) 중 만난시간(met_time)이 가장 이르다면 
			{
				infester=i; //전파자는 i번째 환자 
		
				return infester; //전파자 값을 반환 
			}
		}
		else //지금까지 만난 환자 중 만난시간이 가장 이르지 않을 때 
			return patient_no; //입력된 환자가 전파자이므로 입력된환자 값 출력 
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
	while(3==fscanf(fp,"%i %i %i",&pIndex,&age,&time)) //fscanf의 반환값이 개수라는걸 이용 
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
    		printf("%i번째 환자 감염 경로:\n");
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
				scanf("%i",&pIndex); //입력받은 값을 pIndex에저장 
				
				ifct_element=ifctdb_getData(pIndex); //ifct_element를 출력                                                                               
				ifctele_genElement(pIndex,age,time,placeHist); //각 값들을 대입하여 ifct_element구조체를 생성 
				ifctele_printElement(ifct_element); //ifct_element를 출력 
				
				
			         
				
				
                break; 
                
            case MENU_PLACE:
            	
            	
                printf("place name:");
                scanf("%s", &placename); //사용자가 입력한 장소를 placename에 저장 
                
                
				int cnt=0;
                for(i=0;i<ifctdb_len();i++) //i는 ifctdb_len의 길이만큼 반복
				{
                	ifct_element=ifctdb_getData(i);  //ifct_element를 i만큼의 환자 수 만큼 받아옴
					
                	
                	for(j=3;j<N_HISTORY;j++) //j는 장소 배열의 0~4 중 3,4번째만 받아오기 위해 j=3,j=4시행 
					{	
						place_index=ifctele_getHistPlaceIndex(ifct_element,j); //장소indexf함수를 이용해 place_index에 그 값을 저장 
						
                		if(strcmp(placename,ifctele_getPlaceName(place_index))==0) //사용자가 입력한 placename 값과 각 환자의 장소배열값 중 3,4 값이 같을 때 
						{
                			cnt++; //cnt횟수 1회 증가 
                			printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
							ifctele_printElement(ifct_element); //ifct_element값을 출력 
							printf("\n");
                			printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");						
					
						}
					}
				}
				printf("There are %i patients detected in %s\n",cnt,placename);
                
                break;
                
            case MENU_AGE:
                
                printf("minimal age:"); 
                scanf("%i", &min); //사용자가 입력한 값을 나이값의 최소값으로 저장 
                printf("maximal age:");
                scanf("%i", &max); //사용자가 입력한 값을 나이값의 최대값으로 저장 
                
                for(i=0;i<ifctdb_len();i++) //i는 ifctdb_len의 길이만큼 반복 
				{
                	ifct_element=ifctdb_getData(i); //ifct_element를 i만큼의 환자 수 만큼 받아옴 
                	range_age=ifctele_getAge(ifct_element);//range_age(사용자가 입력한 나이값의 범위)=ifctele_getAge함수에 ifct_element를 대입한 값 
                	
                	if(min<range_age<max) //입력한 최솟값(min)<range_age<입력한 최댓값(max)일 때 
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
                	ifct_element=ifctdb_getData(pIndex); //ifct_element를 출력                                                                               
					ifctele_genElement(pIndex,age,time,placeHist);
                	
                	a=ifctele_getinfestedTime(ifct_element); //ifctele_getinfestedTime함수를 통해 ifct_element의 감염 시기를 a에저장함 
                	time_1=&a; //a를 time_1포인터에 할당 
                	
                	infester=trackInfester(pIndex,time_1,ifct_element); //전파자=trackInfester함수에 pIndex,time_1,ifct_element를 대입했을 때의 출력값 
					
                	if(infester!=pIndex) //infester(전파자)가 입력한 환자의 값(pIndex)와 같지 않을 때 
					{
                		place_index=ifctele_getHistPlaceIndex(ifct_element,pIndex); //장소index값= 입력한 환자의 값(pIndex)을 장소index함수에 대입한 값  
						printf("--> [TRACKING] patient %i is infected by %i (time : %i, place : %s) \n", pIndex, infester, ifctele_getinfestedTime(ifct_element),ifctele_getPlaceName(place_index) );
                		printf("The first infector of %i is %i\n", pIndex, infester);
                	}
					else //infester(전파자)= 입력한 환자의 값(pIndex) 일 때 
                		printf("%i patient is the first infector",infester); //력한 환자의 값(pIndex)이 최초전파자(infester)가 됨 
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
