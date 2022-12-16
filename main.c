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


int trackInfester(int patient_no, int *detected_time, int *place);
int main(int argc, const char * argv[]) {
    
    int menu_selection;
    void *ifct_element;
    FILE* fp;
    int pIndex, age, time;
    int placeHist[N_HISTORY];
    
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
    		fscanf(fp,"%s",&placeHist[i]);
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
				//database에서 getdata를통해서 얻어오고 어쩌구 프린트하면됨 
				
				//ifct_element=(void*)malloc(sizeof(ifs_ele));
				
				printf("patient index :");
				scanf("%i",&pIndex);
				
				ifct_element=ifctdb_getData(pIndex);
				ifctele_genElement(pIndex,age,time,placeHist);
				ifctele_printElement(ifct_element);
				//printf("%s",ifct_element);
				
				
                break; // int ifctele_getAge(void*obj)
                
            case MENU_PLACE:
                
                
                break;
                
            case MENU_AGE:
                
                break;
                
            case MENU_TRACK:
                    
                break;
                
            default:
                printf("[ERROR Wrong menu selection! (%i), please choose between 0 ~ 4\n", menu_selection);
                break;
        }
    
    } while(menu_selection != 0);
    
    
    return 0;
}
