#include <stdio.h>
#include <stdib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

 //Domh proiontwn

typedef struct {
char perigrafh[50];
float timh;
int sum1; // metrhths antikeimenwn
int sum2; //metrhths poulhmenwn antikeimenwn
int sum3; // metrhths antikeimenwn pou zhtountai
char failed[100][50];
int sum4; //metrhths apotyxhmenwn 
} proion;

#define num_proiontwn 30
#define num_pelatwn 10
#define paraggelies_ana_pelath 10

Katalogos_Proiontwn[num_proiontwn]; 

//////arxikopoihsh katalogou///////////////////

void arxikopoihsh_katalogou() 
{
   for (int=0;i< num_proiontwn;i++)
   {
    printf(Katalogos_Proiontwn[i].perigrafh,"Proion %d",i);
    Katalogos_Proiontwn[i].timh = (float()(rand()% 100 + 1); // tyxaies times mexri to 100
    Katalogos_Proiontwn[i].sum1=2; // metrhths antikeimenwn
    Katalogos_Proiontwn[i].sum2=0; // metrhths poul.ant
    Katalogos_Proiontwn[i].sum3=0; // metrhths ant. pou zht
    Katalogos_Proiontwn[i].sum4=0; // metrhths apot. ant
   }

}
 ////// synarthsh gia anafora /////////////////

 void ektypwsh_anaforas () {
 int synolikes_zhthseis=0;
 int epityxhmenes_paraggelies=0;
 int apotyxhmenes_paraggelies=0;
 float synoliko_eisodhma=0.0; 
 
 printf("Anafora Katalogou\n ");
 for (int=0; i<num_proiontwn;i++)
 {
   printf("Proion: %s\n ",Katalogos_Proiontwn[i].perigrafh);
   printf("Aithmata: %d\n",Katalogos_Proiontwn[i].sum3);
   printf("Pwlhthenta: &d\n",Katalogos_Proiontwn[i].sum2);
   printf("Apotyxwntes xrhstes: ");
     for (int j=0 ;j< Katalogos_Proiontwn[i].sum4;j++ )
      {
       printf("%s", Katalogos_Proiontwn[i].failed[j]); 
      }
      printf("\n\n");
      synolikes_zhthseis += Katalogos_Proiontwn[i].sum3;
      epityxhmenes_paraggelies += Katalogos_Proiontwn[i].sum2;
      apotyxhmenes_paraggelies += Katalogos_Proiontwn[i].sum4;
      synoliko_eisodhma += Katalogos_Proiontwn[i].sum2 * Katalogos_Proiontwn[i].timh;
 }
 printf("Oi synolikes paraggelies einai: %d\n",synolikes_zhthseis);
 printf("Oi epityxhmenes paraggelies einai: %d\n",epityxhmenes_paraggelies);
 printf("Oi apotyxhmenes paraggelies einai: %d\n",apotyxhmenes_paraggelies);
 printf("O synolikos tziros einai: %d\n",synoliko_eisodhma);

 }  

///////////////////////////////////////////////////////////////////////////////////////


 int main () {

srand(time(NULL));
arxikopoihsh_katalogou();

int pipes[num_pelatwn][2]; //Xrhsimopoioume to pipe gia paraggelies apo pelates
int apanthseis_pipes[num_pelatwn][2]; // Xrhsimopoioume auto to pipe gia apanthseis pros tous pelates

// Dhmiourgia dioxeuteysewn

for (int i = 0; i< num_pelatwn ;i++ ) 
  {
    if (pipe(pipes[i])== -1 || pipe(apanthseis_pipes[i])== -1) 
      {
        perror("Apetyxe h dhmiourgia pipe");
        exit(APOTYXIA_EXIT);   
      }
  }
  for (int i=0 ; i < num_pelatwn; i++)
     {
      pid_t pid = fork();
      if ( pid == -1)
        {
          perror("Apetyxe h fork ");
          exit(APOTYXIA_EXIT);
        } else if ( pid == 0) {
            close(pipes[i][0]); // A SXOLIO) 0 einai o pelaths B SXOLIO)kleinoume to read end ths dioxeteyshs gia paraggelies
            close(apanthseis_pipes[i][1]); //Kleinoume kai to writw end  ths dioxeuteyshs gia apanthseis se paraggelies
            char onoma[50];
            printf(onoma,"Pelaths_%d",i);
            for (int j = 0; j < paraggelies_ana_pelath; j++ ) 
            {
             sleep(1); //Anamonh enos deuteroleptou
              
             int id_proiontos = rand() % num_proiontwn; // tyxaia epilogh proiontos
             write(pipes[i][1], &id_proiontos,sizeof(int));

             char apanthsh[100]; 
             read(apanthseis_pipes[i][0],apanthsh,sizeof(apanthsh));
             printf("%s: %s: \n",onoma,apanthsh); 
            }
            close(pipes[i][1]);
            close(apanthseis_pipes[i][0]);
          exit(EPITYXIA_EXIT);
        }
     }

     //patrikh diergasia
     for (int = 0; i < num_pelatwn; i++ )
     {
        close(pipes[i][1]);
        close(apanthseis_pipes[i][0]);
     }
     for (int epexergasmenes_par = 0; epexergasmenes_par < num_pelatwn * paraggelies_ana_pelath;){
       for (int i= 0; i < num_pelatwn; i++){
        int id_proiontos;
        if(read(pipes[i][0],&id_proiontos,sizeof(int)) > 0 ){
            Katalogos_Proiontwn[id_proiontos].sum3++;
            char apanthsh[100];
             
            if(Katalogos_Proiontwn[id_proiontos].sum1>0){
                Katalogos_Proiontwn[id_proiontos].sum1 --; //afairei apo ta ant. epeidh poulithhkan
                Katalogos_Proiontwn[id_proiontos].sum2 ++; //auxanei ton arithmo pwlhseis proiontwn 
                printf(apanthsh,"H paraggelia gia %s einai epityxhs ", Katalogos_Proiontwn[id_proiontos].perigrafh);
            } else { 
              printf(apanthsh,"H paraggelia gia %s einai apotyxhs.Exantlithkan ola ta proionta!",Katalogos_Proiontwn[id_proiontos].perigrafh);
                   printf(Katalogos_Proiontwn[id_proiontos].failed[Katalogos_Proiontwn[id_proiontos].sum4++], "Pelaths_%d",i);
                   }
                   write(apanthseis_pipes[i][1],apanthsh,strlen(apanthsh)+1); // xrhsimopoioume thn strlen gia na upologoisoume to meegthos ths "apanthsh" ektos apo to NULL pou thn termatizei
                   epexergasmenes_par++;
                   sleep(1); //xronos gia na perasei h paraggelia       
                    }
                   }
                 }
    for ( int i = 0; i < num_pelatwn; i++)
    {
     wait(NULL); //Perimenoume gia termatismo pelatwn  
    }  
    ektypwsh_anaforas(); //Anafora e-shop
    return 0;           
 }
