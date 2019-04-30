#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct zoznam{
	char signatura[12];
	char isbn[15];
	char nazov[102];
	char autori[102];
	int datum;
	int preukaz;
	struct zoznam *dalsi;
} ZOZNAM;

void n_nacitanie_zaznamov(FILE **subor, ZOZNAM **zaciatok, ZOZNAM **koniec){
	if ((*subor = fopen("kniznica.txt", "r")) == NULL)printf("Zaznamy neboli nacitane\n");
    else {
    	ZOZNAM *pomoc;
    	if(*zaciatok!=NULL){
    		while(*zaciatok != NULL){
    			pomoc=*zaciatok;
    			(*zaciatok) = (*zaciatok)->dalsi;
    			free((void*)pomoc);
  			}
  			*koniec=*zaciatok;
    	}
    	char hviezda[5];
    	int i=0;
    	while(!feof(*subor)){
	    	if (*zaciatok == NULL) {
	    		*zaciatok =(ZOZNAM *) malloc(sizeof(ZOZNAM));
	    		fgets(hviezda,5,*subor);
	    		fgets((*zaciatok)->signatura, 12, *subor);
	    		fgets((*zaciatok)->isbn, 15, *subor);
	    		fgets((*zaciatok)->nazov, 102, *subor);
	    		fgets((*zaciatok)->autori, 102, *subor);
	    		fscanf(*subor,"%d",&((*zaciatok)->datum));
	   			fscanf(*subor,"%d",&((*zaciatok)->preukaz));
	   			fgets(hviezda,5,*subor);
	   			(*zaciatok)->dalsi = NULL;
	   			*koniec = *zaciatok;
    			i++;
	  		}
	  		else {
	   			pomoc = (ZOZNAM *)malloc(sizeof(ZOZNAM));
	   			fgets(hviezda,5,*subor);
	   			if(feof(*subor))break;
	   			fgets(pomoc->signatura, 12, *subor);
    			fgets(pomoc->isbn, 15, *subor);
				fgets(pomoc->nazov, 102, *subor);
	   			fgets(pomoc->autori, 102, *subor);
	   			fscanf(*subor,"%d",&(pomoc->datum));
	    		fscanf(*subor,"%d",&(pomoc->preukaz));
	    		fgets(hviezda,5,*subor);
	    		pomoc->dalsi = NULL;
	    		(*koniec)->dalsi = pomoc;
	    		(*koniec) = pomoc;
	    		i++;
	    	} 			
   	 	}
   	printf("Nacitalo sa %d zaznamov\n",i);
   	if(*subor!=NULL)fclose(*subor);
	}
}

void v_vypis_zoznamu(ZOZNAM *zaciatok){
  int i=0;
  while (zaciatok != NULL) {
	i++; 
    printf("%d.\nsignatura: %s",i, zaciatok->signatura); 
    printf("isbn: %s",zaciatok->isbn);
    printf("nazov: %s", zaciatok->nazov); 
    printf("autori: %s",zaciatok->autori);
    printf("datum: %d\n",zaciatok->datum);
    printf("preukaz: %d\n",zaciatok->preukaz);
    zaciatok = zaciatok->dalsi;
  }
}

void p_pridanie_zaznamu(ZOZNAM **zaciatok,ZOZNAM **koniec){
	int k,i=0;
	char enter[2];
	ZOZNAM *help;
	help=*zaciatok;
	strcpy(enter,  "\nn");
	scanf("%d ",&k);
	if(k>0){
		if(*zaciatok==NULL){
			(*zaciatok) =(ZOZNAM *) malloc(sizeof(ZOZNAM));
			gets((*zaciatok)->signatura);
			strncat((*zaciatok)->signatura,enter,1);
			gets((*zaciatok)->isbn);
			strncat((*zaciatok)->isbn,enter,1);
			gets((*zaciatok)->nazov);
			strncat((*zaciatok)->nazov,enter,1);
			gets((*zaciatok)->autori);
			strncat((*zaciatok)->autori,enter,1);
			scanf("%d",&((*zaciatok)->datum));
			scanf("%d",&((*zaciatok)->preukaz));
			(*zaciatok)->dalsi = NULL;
	   		*koniec = *zaciatok;
		}
		else {
			while((help->dalsi!=NULL)&&(i<k-2)){
				i++;
				help=help->dalsi;
			}
			
			ZOZNAM *novy = (ZOZNAM*)malloc(sizeof(ZOZNAM));
			ZOZNAM *stary = (ZOZNAM*)malloc(sizeof(ZOZNAM));
			gets(novy->signatura);
			strncat(novy->signatura,enter,1);
			gets(novy->isbn);
			strncat(novy->isbn,enter,1);
			gets(novy->nazov);
			strncat(novy->nazov,enter,1);
			gets(novy->autori);
			strncat(novy->autori,enter,1);
			scanf("%d",&(novy->datum));
			scanf("%d",&(novy->preukaz));
	   		if(k==1){
	   			*stary=**zaciatok;
	   			**zaciatok=*novy;
	   			*novy=*stary;
	   			(*zaciatok)->dalsi=novy;
	   			novy->dalsi=(*zaciatok)->dalsi->dalsi;
			   }
			else {
				novy->dalsi=help->dalsi;
	   			help->dalsi = novy;
			}
		}
	}
}

void z_zmazanie_zaznamu(ZOZNAM **zaciatok){
  	int i=0,pocet=0;
  	ZOZNAM *pred,*po,*pomoc;
  	po = *zaciatok;
  	pred=*zaciatok;
  	char retazec[102], *pom, c,help[102];
  	scanf("%c",&c);
  	gets(retazec);
  	strupr(retazec);
	while(po!=NULL){
		strcpy(help,po->autori);
		strupr(help);
  		pom=strstr(help,retazec);
		if(pom!=NULL){
  			if(i==0){
  				pomoc=*zaciatok;
  				*zaciatok=(*zaciatok)->dalsi;
  				free((void *)pomoc);
  				pred=*zaciatok;
  				po=*zaciatok;
  				i--;
			}
			else{
				pred->dalsi=po->dalsi;
				pomoc=po;
				po=po->dalsi;
				free((void*)pomoc);
			}
			pocet++;
		}
		else {
			pred=po;
			po=po->dalsi;	
		}     	
	i++;
	}
	printf("Vymazalo sa %d zaznamov\n",pocet);
}

void h_vyhladavanie_podla_preukazu(ZOZNAM *zaciatok){
  int i=0,c;
  scanf("%d",&c);
  	while (zaciatok != NULL) {
		if(zaciatok->preukaz==c){
			i++; 
    		printf("%d.\nsignatura: %s",i, zaciatok->signatura); 
   			printf("isbn: %s",zaciatok->isbn);
    		printf("nazov: %s", zaciatok->nazov); 
    		printf("autori: %s",zaciatok->autori);
			printf("datum: %d\n",zaciatok->datum);
			printf("preukaz: %d\n",zaciatok->preukaz);
			}    	
		zaciatok = zaciatok->dalsi;
	}
	if(i==0)printf("Pre dane cislo preukazu neevidujeme vypozicky\n");
}

void a_aktualizacia_podla_datumu(ZOZNAM *zaciatok){
  int i=0,d;
  scanf("%d",&d);
  	while (zaciatok != NULL) {
		if(d>=zaciatok->datum){
			i++; 
			zaciatok->datum=zaciatok->datum+10000;
			}    	
		zaciatok = zaciatok->dalsi;
	}
	printf("Aktualizovalo sa %d zaznamov\n",i);
}

int main(){		
	FILE *subor=NULL;
	ZOZNAM *zaciatok, *koniec;
	zaciatok = koniec = NULL;
	int c;
    char vstup;
    while (1) {
    	vstup=getchar();
        switch(vstup){
            case 'n':n_nacitanie_zaznamov(&subor,&zaciatok,&koniec);break;
            case 'v':v_vypis_zoznamu(zaciatok);break;
            case 'p':p_pridanie_zaznamu(&zaciatok,&koniec);break;
            case 'z':z_zmazanie_zaznamu(&zaciatok);break; //prv 
            case 'h':h_vyhladavanie_podla_preukazu(zaciatok);break;
            case 'a':a_aktualizacia_podla_datumu(zaciatok);break;
            case 'k':{
	            	ZOZNAM *pomoc;
	    			if(zaciatok!=NULL){
	    				while(zaciatok != NULL){
	    					pomoc=zaciatok;
	    					zaciatok = zaciatok->dalsi;
	    					free((void*)pomoc);
	  					}
	  					koniec=zaciatok;
	    			}
					return 0;
				}break;
        }
    }
    return 0;
}
