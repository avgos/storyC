/*project 2011-2012*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 60
#define MAX_PARAGWGES 10

/***************************tipoi dedeomenwn**************************/
/*lista i opoia periexei termatika kai mi termatika*/

typedef struct node{  
  struct node *next;
  char lexi[SIZE];
}nodeT;


/*dinamikos pinakas pou kathe stoixeio tou periexei ena mi termatiko,enan pinaka apo 
deiktes pou einai oi paragwges kai ena noumero pou deixnei to pragmatiko
megethos tou pinaka*/

typedef struct pinakas{
  nodeT *paragwges_ptr[MAX_PARAGWGES];
  char mi_termatika_start[SIZE];
  int counter_paragwges;
}pinakasT;




/******************Sinartisi gia tin dimiourgia arxeiou exodou********/



/***dimiourgei to katalillo onoma gia to arxeio exodou*****/
FILE *dimiourgia_exodos(char arxeio_eisodou[]){
  
  FILE *arxeio_exodou;
  int i,counter=1; //i: metritis opou deixnei ton xaraktira '.' sto arxeio eiodou,counter: metritis gia na allazei to onoma tou arxeiou exodou
  char *onoma_exodos,*formatstring;  /*onoma_exodos:to onoma tou arxeiou exodou,
                                     formatstring: xrisimopoieite stin sprintf gia na allazei to onoma arxeiou exodou*/
  char *x_eisodos=NULL;        //opou x_exodos einai to x meros tou arxeiou eisodou 
  
  
  for(i=0;i<strlen(arxeio_eisodou);i++){
    if(arxeio_eisodou[i] == '.'){     //trexe olo to onoma tou arxeiou eisodou mexri na vreis tin teleia kai krata tin thesi sto 
      break;
    }
  }
  x_eisodos=(char *)malloc(i*sizeof(char)+1);      //to megethos tou x eisodos theloume na einai oso to x meros tou arxeiou eisodou +\0
  if(x_eisodos == NULL){
    printf("No memory for the x side of input");
    return (NULL);
  }
  
  onoma_exodos=(char *)malloc(i*sizeof(char)+6); /* to megethos tou onomatos arxeiou exodou einai osa grammata einai to arxeio
                                                                       eisodou + I.out + \0 (diladi 6 xaraktires)*/ 
  if(onoma_exodos == NULL){  
    printf("Den iparxei xwros gia to arxeio exodou\nAra ta apotelesmata ektipononte apla stin othoni\n");
    
    return (NULL);
  }
  formatstring=(char *)malloc(i*sizeof(char)+6); //kratame to sinoliko onoma sto formatstring gia na mporoume na to allazoume
  
  if(formatstring == NULL){  
    printf("No memory for formatstring");
    
    return (NULL);
  }
  
  strncpy(x_eisodos,arxeio_eisodou,i);   // apothikefse se enan pointer to x meros tou arxeiou eisodou
  x_eisodos[i]='\0';
  
  strncpy(onoma_exodos,arxeio_eisodou,i);   
  strcat(onoma_exodos,"1.out"); /*dimiourgoume to prwto onoma pou mporei na parei to arxeio exodou
                                   kai o termatikos xaraktiras  logw tis strcat mpenei aftomata*/
                                   
  arxeio_exodou=fopen(onoma_exodos,"r"); //anoigoume to arxeio me "r" gia na doume an iparxei i oxi idi sto fakelo
  while(arxeio_exodou != NULL){
     
    fclose(arxeio_exodou);              //kleinoume to arxeio
    counter+=1;                         //auxanoume ton counter
    
    formatstring=(char *)realloc(formatstring,i+counter*sizeof(int)+5);  //allazoume tin mnimi an einai to noumero exei allaxei se noumero 2,3,..,n psifiwn
    if(formatstring == NULL){
      printf("No memory for formatstring");
      break;
    }
    sprintf(formatstring,"%s%d.out",x_eisodos,counter); //dimiourgoume to kainourgio onoma gia to string

    strcpy(onoma_exodos,formatstring);  //to antigrafoume sto arxeio exodou
      
    arxeio_exodou=fopen(onoma_exodos,"r"); //anoigoume to arxeio me "r" gia na doume an iparxei i oxi idi sto fakelo
  }
  
  if(arxeio_exodou == NULL){
    arxeio_exodou=fopen(onoma_exodos,"w");
    free(formatstring);
    free(x_eisodos);
   

    return (arxeio_exodou);

  }
  
  
  return (arxeio_exodou);

}
  
    
    
  




/****************Sinartiseis gia tin apothikefsi grammatikis***************/



/**********desmevei xwro gia ena kovmo se mia lista*********/

nodeT *desmefsi_nodeT(){
  nodeT *pointer;
  
  pointer=(nodeT *)malloc(sizeof(nodeT));
  if(pointer == NULL){
    printf("No memory for nodeT");
  }
  pointer->next=NULL;
  return (pointer);
}
  
/**************desmefsi mnimis tou dinamikou pinaka***************/  
  
pinakasT *desmefsi_pinakasT(int megethos){
  pinakasT *pointer;
  
  pointer=(pinakasT *)malloc(megethos*sizeof(pinakasT));
  if(pointer == NULL){
    printf("No memory for table");
  }
  
  return (pointer);
}

/*****vazei enan komvo stin lista xekinwntas panta apo ton sentinel*******/

void node_list_insert(nodeT *head,char data[]){
  nodeT *curr;
  
  
  curr=desmefsi_nodeT();
  strcpy(curr->lexi, data);
  curr->next=head->next;
  head->next = curr;
  }

/********ipologizei to plithos twn mi termatikwn sto arxeio*********/

int metritis_mi_termatikwn(FILE *grammar,char formatstring[]){
  int counter=0;
  char string[SIZE];
  
  
  while(!feof(grammar)){
    fscanf(grammar,formatstring,string);
   
    if(strcmp(string,"{") == 0){
     counter+=1; 
    }
    
  }
  fseek(grammar,0,SEEK_SET);  //xanavazoume ton pointer pou deixnei sto arxeio,xana apo tin arxi tou arxeiou
  
  
  return (counter);
}
  
/****************sinartiseis gia tin dimiourgia tis istorias***************/

/*****exagwgh mias simvoloseiras apo tin lista *****/

char *exagwgh_stoivas(nodeT *arxi){
 nodeT *komvos; 
 char *word; 
  
 if(arxi->next == NULL){
   return NULL;
 } 
 
  komvos=arxi->next;
  word=(char *)malloc(strlen(komvos->lexi)*sizeof(char));
  strcpy(word,komvos->lexi); 
  arxi->next=komvos->next;
  
  arxi->next=komvos->next;
  free(komvos);
  return word;
 
}

/*******************apodesmefsi listas************************/

void apodesmefsi_listas(nodeT *curr){
  nodeT *epomenos;
  
  while ( curr != NULL){
    epomenos=curr;
    curr=curr->next;
    free(epomenos);
  }
}


/*******************apodesmefsi mnimis************************/

void apodesmefsi_mnimis(pinakasT *pinakas,int SIZE_TABLE){
  int i,k=1,len=0;
  
  for(i=0;i<SIZE_TABLE;i++){
    for(k=1;k<=pinakas[i].counter_paragwges;k++){
	apodesmefsi_listas(pinakas[i].paragwges_ptr[k]); /*apodesmevoume prwta tin lista 
                                                      pou vriskete se kathe stoixeio tou dinamikou pinaka*/ 
    } 
  }
  
  
  pinakas=(pinakasT*)realloc(pinakas, len*sizeof(pinakasT));
  pinakas=NULL;
  free(pinakas);
}

void paragwgh(nodeT *head,nodeT *new){
  
  
  while(new!=NULL){
  
      node_list_insert(head,new->lexi);  
      new=new->next;
  }
}


/****************************************  MAIN  ***********************************/

int main (int argc,char *argv[]){
  
  FILE *grammar=NULL,*exodos=NULL; //opou grammar einai to arxeio eisodou kai exodos einai to arxeio exodou
  char string[SIZE],formatstring[5]; // opou string kai formastring voithiko sting gia tin metavivasi dedomenwn kai tin sprintf
  pinakasT *pinakas; //dinamikos pinakas
  int SIZE_TABLE,i=0; //SIZE_TABLE sinoliko megethos pinaka,i metritis pou deixnei sto stoixeio tou dinamikou pinaka
  
  nodeT *arxi;   //i arxi tis stoivas pou tha xrisimopoihthei gia na dimiourgisoume tin istoria kai telos gia na doume pote teleiwnei i stoiva
  char *word=0;  //einai i lexi pou exagoume apo tin stoiva,mporei na einai mi termatiki i termatiki
  int random_num=0;    //to position einai i thesi pou vriskei to mi_termatiko,opou random_num einai tixaia thesi pou paragei i sinartisi
  int lexeis=0; //to lexeis xrisimopoieiete gia na allazoume tin seira sto arxeio exodou kathe fora pou ftanoume tis 60 lexeis
  
  
  
  /*elegxos an dothike to arxeio eisodou*/
  if(argc != 2){
    printf("Not enough arguments\n");
    return 1;
 }
  
   /*anoigma tou arxeiou gia diavasma*/
  grammar= fopen(argv[1],"r");
  
  /*elegxos an anoixthike to arxeio */
  if(grammar == NULL){
      printf("Could not open file %s for reading\n", argv[1]);
      return 1;
  }
  /*dimiourgia katalilou onomatos tou arxeiou exodou*/
  exodos=dimiourgia_exodos(argv[1]);  
  if(exodos==NULL){
      printf("to arxeio den dimiourgithike\n");
  }
  
  sprintf(formatstring,"%%%ds",(SIZE-1));

  /*ipologismos sinolikou megethous tou dinamikou pinaka*/
  SIZE_TABLE=metritis_mi_termatikwn(grammar,formatstring);

  /*dinamiki desmefsi tou pinaka*/
  pinakas=desmefsi_pinakasT(SIZE_TABLE);

  /*an i desmefsi tou pinaka den egine termatise anepitixws to programma*/
  if(pinakas == NULL){   
    return (1);
  }
  
  while(!feof(grammar)){
    fscanf(grammar, formatstring,string);
    
    /*diavasma strings tou arxeiou mexri na vrei to xaraktira '{'*/
    if(strcmp(string,"{") == 0){
      fscanf(grammar, formatstring,string);                                         //diavazei to mi termatiko
      
      strcpy(pinakas[i].mi_termatika_start,string);                                 // antegrapse to mi termatiko ston pinaka sto pedio mi_termatika_start
      pinakas[i].counter_paragwges=0;
      
      fscanf(grammar, formatstring,string);                                         //diavazei epomeni lexi apo to mi termatiko

    
	while(strcmp(string,"}") != 0){                                             //mexris otou na teleiwsoun oles oi paragwges
	    pinakas[i].counter_paragwges++;                                         //auxise tis paragwges
	    pinakas[i].paragwges_ptr[pinakas[i].counter_paragwges]=desmefsi_nodeT();//desmefsi gia to head tis listas
	    while(strcmp(string,";") != 0){                                         //mexris otou na teleiwsei i mia paragwgh 
	      
		node_list_insert(pinakas[i].paragwges_ptr[pinakas[i].counter_paragwges],string);/*desmevei kai dimiourgei mia lista opou kathe stoixeio
		                                                                                  tis listas eisagete apo tin arxi,etsi wste otan ta 
		                                                                                  exagoume na dimiourgeite protasi apo to aristero pros
		                                                                                  to dexi meros*/
		fscanf(grammar, formatstring,string);
	    }
	    fscanf(grammar, formatstring,string);
	}
	i++;             //epomeno stoixeio tou pinaka
    }
  }
  
  srand((int) time(NULL));//thetoume stin srand me seed i opoia einai i trexousa wra
  
  
  arxi=desmefsi_nodeT();//desmefsi tou prwtou komvou tis stoivas  
  node_list_insert(arxi,"<start>");//eisagwgh prwtou komvou me lexi to start
  
  word=exagwgh_stoivas(arxi);  //exagei kathe stoixeio tis stoivas apo ta aristera pros ta dexia

  
  while(word != NULL){
    
    for(i=0;i<SIZE_TABLE;i++){
     if(strcmp(word,pinakas[i].mi_termatika_start) == 0){     //mexri na vrei tin lexi pou exagagame ston dinamiko pinaka sto pedio me ta mi termatika   
	random_num=rand()%(pinakas[i].counter_paragwges)+1;  /*epilegoume mia tixaia paragwgh apo tis idi iparxouses
	                                                         sto sigkekrimeno stoixeio tou pinaka*/
	paragwgh(arxi,pinakas[i].paragwges_ptr[random_num]->next );
	word=exagwgh_stoivas(arxi);
	break;
      }
     }
      
      if(i == SIZE_TABLE){
	
	lexeis+=strlen(word)+1;   //kratame to athroisma twn grammatwn wste otan ftasoume 60 i parapanw na allaxoume grammi
	
        if(exodos != NULL){     //an den iparxei kapoio provlima me to arxeio exodou
	  fprintf(exodos,"%s",word);    //apothikevei mia lexi sto arxeio exodou
	  fputc(' ',exodos);   //apothikevei kai ena keno sto arxeio exodou  
	  word=exagwgh_stoivas(arxi);
	}
	else{   //an iparxei kapoio provlima me to arxeio exodou
	  printf("%59s ",word); //ektipwnei tin lexi mazi me ena keno stin othoni
	  word=exagwgh_stoivas(arxi);
     
	}
	if(lexeis >= SIZE){
	  if(exodos == NULL){       //an iparxei provlima me to arxeio exodou ektipwse stin othoni
	    printf("\n");
	  }
	  else{
	    fprintf(exodos,"\n");   //alliws grapse to sto arxeio exodou
	  }
	  lexeis=0;                  //midenismos twn lexewn gia na xanaxrisimopoihthei
	}

      }
      
  }
  
  /*apodesmevei ton pinaka kai lista pou desmefsame*/
  apodesmefsi_mnimis(pinakas,SIZE_TABLE);  
  
  if(exodos != NULL ){
    fflush(exodos);    //apothikevei tis allages sto arxeio exodou
    fclose(exodos);    // kleinei to arxeio_exodou
  }
  fclose(grammar);    //kleinei to arxeio eisodou

  
  
  
  return 0;
}

