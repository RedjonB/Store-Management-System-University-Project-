#include <stdio.h>
#include <string.h>

char fn_artikull[250]= "C:\\detyre\\artikuj.txt";
char fn_klient[250]= "C:\\detyre\\klient.txt";
char fn_shitje[250]= "C:\\detyre\\shitje.txt";
char fn_furnizim[250]= "C:\\detyre\\furnizim.txt";

int nr_art=0;
int nr_klient=0;
int count_shitjesh=0;
int count_furnizimesh=0;

struct artikulli{
	char kodi[8];
	char kategoria[100];
	char emertimi[200];
	int  cmimi;	
}a[100];


struct klienti{
	char ID[10];
	char emri[50];
	char mbiemri[50];
	int tel;
	int shpenzim_total;
	int blerje_total;
	int piket;
}k[100];


struct shitje{
	char id_klient[10];
	int  id_fature;
	char data_sh[20];
	struct artikuj{
		char kodi[8];
		int sasi;
		int cmim;
	}artikuj_shitje[100];
	int totali_cmim;
}shitje;

struct furnizimi{
	int ID;
    char data_f[20];
		struct artikuj_f{
		char kodi[8];
		int sasi;
		int cmim;
	}artikuj_furnizim[100];
	int totali_furnizim;
}furnizim;


void save(){
	
	FILE *f;
	 int i;
	f=fopen(fn_artikull,"wb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	 for( i=0;i<nr_art; i++){
	  fwrite(&a[i],sizeof(struct artikulli),1,f);}
	 fclose(f);
	 
    f=fopen(fn_klient,"wb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	 for( i=0;i<nr_klient; i++){
	  fwrite(&k[i],sizeof(struct klienti),1,f);}
	 fclose(f); 
	 
	f=fopen(fn_shitje,"wb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	  fwrite(&shitje,sizeof(struct shitje),1,f);
	 fclose(f); 
	 
	f=fopen(fn_furnizim,"wb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	  fwrite(&furnizim,sizeof(struct furnizimi),1,f);
	 fclose(f);	 
	return;
}

void menu()
{
  printf("                                               \n ******  ");
  printf("                                               \n| M E N U |");
  printf("                                               \n ******");
  printf("\n 1 - Regjistrim Artikulli ");
  printf("\n 2 - Regjistrim Klienti");
  printf("\n 3 - Furnizim (hyrje ne dyqan)");
  printf("\n 4 - Shitje (dalje nga dyqani) ");
  printf("\n 5 - Gjendja ne magazine ");
  printf("\n 6 - Klientet qe shpenzojne  me shume (10 te paret ne vlere )");
  printf("\n 7 - Klientet qe blejne me shpesh (20 te paret)");
  printf("\n 8 - Kerkim artikulli sipas kodit (barcode)");
  printf("\n 9 - Piket e klientit.");
  printf("\n Zgjedhja juaj: ");
  fflush(stdin);
  return;
}

void Regjistrim_artikulli(){
   char kod_tmp[8];
   int i=0;	
   printf("\n Jepni kodin per artikullin :"); 
   fflush(stdin);
   gets(kod_tmp);	
   
    FILE *f;
	f=fopen(fn_artikull,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	   nr_art=0; 
	  while (fread(&a[i],sizeof(struct artikulli),1,f)){nr_art++;}
	 fclose(f);
   
   for ( i=0; i<nr_art ;i++){
    if (strcmp(kod_tmp,a[i].kodi)==0){
     printf("Ekziston nje artikull me kete kod.");
     return;}
   }	
  strcpy(a[nr_art].kodi,kod_tmp);
  printf("\nJepni emertimin e produktit:"); 
  fflush(stdin);  
  gets(a[nr_art].emertimi);
  printf("\n Jepni kategorine e artikullit :"); 
  fflush(stdin);  
  gets(a[nr_art].kategoria);	
  printf("\n Jepni cmimin e artikullit :");
  fflush(stdin);
  scanf("%d", &a[nr_art].cmimi);	
  nr_art++;
  save();
  return;
}

void Regjistrim_klienti(){
   char ID_tmp[50];
   int i;	
   printf("\n Jepni ID per klientin :"); 
   fflush(stdin);
   gets(ID_tmp);
   FILE *f;
    f=fopen(fn_klient,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	   nr_klient=0;
       while (fread(&a[nr_klient],sizeof(struct klienti),1,f)){nr_klient++;}  
	 fclose(f); 	
	 
   for(i=0; i<nr_klient;i++){
   if (strcmp(ID_tmp,k[i].ID) ==0){
     printf("Ekziston nje klient me kete ID.");
     return;}
   }	
   strcpy(k[nr_klient].ID,ID_tmp);
   printf("\nJepni emrin e klientit:"); 
   fflush(stdin);  
   scanf("%s",k[nr_klient].emri);
   fflush(stdin);
   printf("\nJepni mbiemrin e klientit:"); 
   fflush(stdin);  
   scanf("%s",k[nr_klient].mbiemri); 
   printf("\nJepni numrin e telefonit te klientit:");
   fflush(stdin);   
   scanf("%d",&k[nr_klient].tel);
   nr_klient++;
   save();
   return;
}
		
void Shitje(){
	char ID_temp[50];
	int t=0, i, zgj, zgj_1, sasia, totali, tmp_k;
	int j=0, tmp[100], total[100], s[100]; //duhen per te ruajtur indekset e produkteve qe zgjedh perdoruesi, cmimin total per cdo produkt dhe me pas i perdorim ne printim fature;
	
	printf("Jepni ID e klientit: ");
	fflush(stdin);
	gets(ID_temp);
	
	FILE *f;
	 f=fopen(fn_klient,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	   nr_klient=0;
	 while (fread(&k[i],sizeof(struct klienti),1,f)){nr_klient++;}
	 fclose(f); 
	 
	for(i=0;i<nr_klient;i++){
		if (strcmp(ID_temp,k[i].ID) == 0 ){
			t=1;
			tmp_k = i;
			break;
		}
	}
	if(t==0) {
		printf("\nNuk eshte regjistruar asnje klient me kete ID");
		return;
	}
	strcpy(shitje.id_klient,ID_temp);
	fflush(stdin);
	printf("\nJepni daten e shitjes: ");
	gets(shitje.data_sh);
	FILE *Sh;
	Sh=fopen(fn_artikull,"rb");
	if (Sh==NULL){
	   printf("\n \n   Gabim ne file");
	   return;}
	   nr_art=0; 
	while (fread(&a[nr_art],sizeof(struct artikulli),1,Sh)){nr_art++;}  
	fclose(Sh);
	Shitje: 
	for(i=0;i<nr_art;i++){
	 	printf("\n%d-%s",i+1,a[i].emertimi);
    }
	for(i=0;i<nr_art;i++){
		shitje.artikuj_shitje[i].cmim = a[i].cmimi;	
	}
	
    printf("\nJu lutem zgjidhni numrin perkates per produktin qe deshironi te shisni: ");
	scanf("%d",&zgj);
	if(zgj==0 || zgj>nr_art){
		printf("\nZgjedhja nuk eshte e vlefshme");
		goto Shitje;
	}
	printf("\nJepni sasine qe deshironi te shisni nga ky produkt: ");
	scanf("%d", &sasia);
	FILE *A;
	A=fopen(fn_furnizim,"rb");
	if (A==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	while (fread(&furnizim,sizeof(struct furnizimi),1,A));
	fclose(A);
	if(furnizim.artikuj_furnizim[zgj-1].sasi==0){
		printf("Ju nuk zoteroni sasi per kete produkt\n");
		zgj_1:
		printf ("\nDeshironi te vazhdoni me shitjen?\n 1-Po \n2-Jo");
		scanf("%d",&zgj_1);
		if(zgj_1==1) goto Shitje;
		else if(zgj_1==2) return;
		else {
		printf("\nZgjedhja nuk eshte e vlefshme.");
		goto zgj_1;}
	}
    else if (sasia > furnizim.artikuj_furnizim[zgj-1].sasi) {
		printf("\nJu nuk e zoteroni kete sasi\n");
		zgj_2:
		printf ("\nDeshironi te vazhdoni me shitjen?\n 1-Po\n2-Jo");
		scanf("%d",&zgj_1);
		if(zgj_1==1) goto Shitje;
		else if(zgj_1==2) return;
		else {
		printf("\nZgjedhja nuk eshte e vlefshme.");
		goto zgj_2;
		}
	}
	else if(sasia < 0) {
		printf("Nuk mund te kete sasi negative");
		zgj_3:
		printf ("\nDeshironi te vazhdoni me shitjen?\n 1-Po \n-Jo");
		scanf("%d",&zgj_1);
		if(zgj_1==1) goto Shitje;
		else if(zgj_1==2) return;
		else {
			printf("\nZgjedhja nuk eshte e vlefshme.");
			goto zgj_3;
		}	
	}
	else {
		s[j]=zgj-1;
		shitje.artikuj_shitje[zgj-1].sasi = sasia;
		furnizim.artikuj_furnizim[zgj-1].sasi-=sasia;
		total[j] = sasia * shitje.artikuj_shitje[zgj-1].cmim;;
	    shitje.totali_cmim+=total[j];
	    j++;
	}
		Pyetja: 
		printf ("\nDeshironi te vazhdoni me shitjen?\n1-Po \n2-Jo dhe printo fature");
		scanf("%d",&zgj_1);
		if(zgj_1==1) goto Shitje;
		else if(zgj_1==2) {
			
			printf("\n*************************************************");
			printf("\n ID Klienti: %s", shitje.id_klient );
			shitje.id_fature += count_shitjesh;
			printf(" \nID Fature: %d\n", shitje.id_fature);
			count_shitjesh++;
			for(i=0; i<j ;i++)
			{
				printf("Produkti: %s",a[s[i]].emertimi);
				printf("\nSasia: %d",shitje.artikuj_shitje[s[i]].sasi);
				printf("\nCmim: %d", total[i]);
				printf("\n\n");
			}
			printf("\nTotali i fatures eshte: %d", shitje.totali_cmim);
			printf("\nData e shitjes: %s", shitje.data_sh);
			k[tmp_k].shpenzim_total += shitje.totali_cmim;   //per te gjetur klientet qe shpenzojne me shume ;
			k[tmp_k].blerje_total++;       //per te gjetur klientet qe blejne me shpesh;
			k[tmp_k].piket += shitje.totali_cmim / 10;
			shitje.totali_cmim=0;
			save();
		}
		else {
			printf("\nZgjedhja nuk eshte e vlefshme.");
			goto Pyetja;
		}
    return;
}		
		
void Furnizim(){
	int zgjedhja,zgjedhja2,sasia,total=0,i;
	int j=0,v[100],s[100], t[100];
	furnizim.ID=count_furnizimesh;
	count_furnizimesh++;	
	FILE *f;
	f=fopen(fn_artikull,"rb");
	if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	nr_art=0;
	while (fread(&a[nr_art],sizeof(struct artikulli),1,f)){nr_art++;}  
	fclose(f);  
	for(i=0;i<nr_art;i++){
		if(a[i].cmimi<=1000){ 
			furnizim.artikuj_furnizim[i].cmim = a[i].cmimi * 0.6;
		}
		else if( a[i].cmimi>1000 && a[i].cmimi<=3000 ){
			furnizim.artikuj_furnizim[i].cmim = a[i].cmimi * 0.7;
		}
		else if(a[i].cmimi>3000 ){
			furnizim.artikuj_furnizim[i].cmim = a[i].cmimi * 0.8;
		}
	}
	printf("\nJepni daten e furnzimit: ");
	fflush(stdin);
	gets(furnizim.data_f);
	for(i=0;i<nr_art;i++){
		strcpy(furnizim.artikuj_furnizim[i].kodi, a[i].kodi);
	}
	furnizim: //nqs do te vazhdoje furnizimi
	for(i=0;i<nr_art;i++){
	 	printf("\n%d- %s",i+1,a[i].emertimi);
	}
	
	printf("\nJu lutem zgjidhni numrin perkates per produktin qe deshironi te furnizoheni: ");
	scanf("%d", &zgjedhja);
	if(zgjedhja==0 || zgjedhja>nr_art){
		printf("\nZgjedhja nuk eshte e vlefshme");
		goto furnizim;
	}
	v[j] = zgjedhja-1;  //na duhet per te printuar fature ne fund prnd ruaj indekset e produkteve qe furnizon perdoruesi;
	sasia:
	printf("Jepni sasine qe deshironi te furnizoheni me kete produkt: ");
	scanf("%d", &sasia);
	
	if(sasia > 0){
	s[j]=sasia;  //sasia per cdo produkt te furnizuar ruhet ktu;
	total = sasia * furnizim.artikuj_furnizim[zgjedhja-1].cmim;
	t[j]=total;  //cmimi ne fature per cdo produkt te furnizuar ruhet ktu;
	furnizim.totali_furnizim+=total;
	furnizim.artikuj_furnizim[zgjedhja-1].sasi+=sasia;
    }
    else {  
		printf("Nuk mund te kete sasi negative");
		goto sasia;
	}
	j++;
	Zgjedhja2:
	printf("Deshironi te vazhdoni me furnizimin?");
	printf("\n1- Po\n2- Jo dhe printo fature\n");
	scanf("%d",&zgjedhja2);
	if (zgjedhja2==1) goto furnizim;
	else if (zgjedhja2==2) {
		furnizim.ID += count_furnizimesh;
		count_furnizimesh++;
		printf("\n****************************************************\n");
		printf("\nID Fature: %d\n", furnizim.ID);
		for(i=0;i<j;i++){
			printf("Produkti: %s",a[v[i]].emertimi);
			printf("\nSasia: %d",s[i]);
			printf("\nKosto: %d", t[i]);
			printf("\n\n");
		}
		
		printf("\nTotali i furnizimit eshte: %d",furnizim.totali_furnizim);
		printf("\nData e shitjes: %s", furnizim.data_f);
		furnizim.totali_furnizim=0;
		save();
	}
	else{
		printf("\nZgjedhja nuk eshte e vlefshme.\n");
		goto Zgjedhja2;
	}
}

void Klientet_qe_shpenzojn_me_shume(){
	int temp, i, j;
	char temp_emri[50], temp_mbiemri[50];
	FILE *f;
	f=fopen(fn_klient,"rb");
	if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	nr_klient=0;
	while (fread(&k[nr_klient],sizeof(struct klienti),1,f)){nr_klient++;}  
	fclose(f);  
	for(j=0; j<nr_klient; j++){
		for(i=0 ;i < nr_klient-1; i++){
			if(k[i].shpenzim_total < k[i+1].shpenzim_total){
				temp = k[i].shpenzim_total;
				k[i].shpenzim_total = k[i+1].shpenzim_total;
				k[i+1].shpenzim_total = temp;
				
				strcpy(temp_emri, k[i].emri);
				strcpy(k[i].emri, k[i+1].emri);
				strcpy(k[i+1].emri,  temp_emri);
				
				strcpy(temp_mbiemri, k[i].mbiemri);
				strcpy(k[i].mbiemri, k[i+1].mbiemri);
				strcpy(k[i+1].mbiemri, temp_mbiemri);
			}
		}
	}
	printf("\nKlientet qe kane shpenzuar me shume jane: ");
	for(i=0; i<10; i++){ 
		printf("\n%d- %s %s ----> %d leke.", i+1, k[i].emri, k[i].mbiemri, k[i].shpenzim_total);	
	}
	return;
}
void Klientet_qe_blejne_me_shpesh(){
	int i, j, temp;
	char temp_emri[50], temp_mbiemri[50];
	
	FILE *f;
	f=fopen(fn_klient,"rb");
	if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	nr_klient=0;
	while (fread(&a[nr_klient],sizeof(struct klienti),1,f)){nr_klient++;}  
	fclose(f);  	
	
	for(j=0; j<nr_klient; j++){
		for(i=0 ;i < nr_klient-1; i++){
			if(k[i].blerje_total < k[i+1].blerje_total){
				temp = k[i].blerje_total;
				k[i].blerje_total = k[i+1].blerje_total;
				k[i+1].blerje_total = temp;
				
				strcpy(temp_emri, k[i].emri);
				strcpy(k[i].emri, k[i+1].emri);
				strcpy(k[i+1].emri, temp_emri);
				
				strcpy(temp_mbiemri, k[i].mbiemri);
				strcpy(k[i].mbiemri, k[i+1].mbiemri);
				strcpy(k[i+1].mbiemri, temp_mbiemri);
			}
		}
	}
	printf("\nKlientet qe kane blere me shpesh jane: ");
	for(i=0; i<20; i++){ 
		printf("\n%d- %s %s ----> %d here.", i+1, k[i].emri, k[i].mbiemri, k[i].blerje_total);
	}
	return;
}	


void Gjendja_ne_magazine(){
	int i;
	FILE *f;
	
	f=fopen(fn_furnizim,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	fread(&furnizim,sizeof(struct furnizimi),1,f);
	 fclose(f);
	 
	f=fopen(fn_artikull,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	nr_art=0;
	 while (fread(&a[nr_art],sizeof(struct artikulli),1,f)){nr_art++;}
	 fclose(f);

	 printf("\nGjendja ne magazine eshte: ");
	for(i=0; i<nr_art; i++){
		printf("\n%s -----> %d", a[i].emertimi, furnizim.artikuj_furnizim[i].sasi);
		printf("\n");
	}
	return;
}

void Kerkim_artikulli_sipas_kodit(){
	FILE *f;
	f=fopen(fn_artikull,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	nr_art=0;
	 while (fread(&a[nr_art],sizeof(struct artikulli),1,f)){nr_art++;}
	 fclose(f);
	 
	char tmp_kodi[8];
	int i, t=0;
	 
	 printf("\nJepni kodin e artikullit: ");
	 fflush(stdin);
	 gets(tmp_kodi);
	 
	for(i=0; i<nr_art; i++){
		if(strcmp(tmp_kodi, a[i].kodi) == 0){
	 		printf("\nArtikulli i gjetur sipas kodit eshte: %s", a[i].emertimi);
	 		return;
		}	 
	}
	printf("\nAsnje artikull nuk eshte i regjistruar me kete barcode.");
	return;
	
	 
}
 
void Piket_e_klientit(){
	char ID_tmp[8];
	int zgjedhja, leke_bonus, i, j=0, v[100], t=0;
	printf("\nJepni ID e klientit per te kontrolluar piket: ");
	fflush(stdin);
	gets(ID_tmp);
	
	FILE *f;	
	f=fopen(fn_klient,"rb");
	 if (f==NULL){
	   printf("\n \n   Gabim ne file");
	   return;} 
	nr_klient=0;
	 while (fread(&k[nr_klient],sizeof(struct klienti),1,f)){nr_klient++;}
	 fclose(f); 
	 
	for(i=0; i<nr_klient;i++){
    if (strcmp(ID_tmp,k[i].ID) ==0){
     printf("\nKlienti %s ka %d pike ne llogrine e tij", k[i].emri, k[i].piket);
     t=1;
     break;
	 }
   }
   if(t==0){
   	printf("\nNuk ekziston ky klient");
   	return;
   }
   if(k[i].piket <= 0){
   	printf("Ju nuk zoteroni pike");
   	return;
   }	
   z:
   printf("\nDeshironi te konvertoni piket ne artikuj?\n1- Po\n2- Jo\n"); 
   scanf("%d", &zgjedhja);
   if(zgjedhja==1){
		leke_bonus = k[i].piket;  // 1 pike eshte e barasvlefshme me 1 lek.
	   	
	   	//hapa filen artikull per te kontrolluar cmimin;
	   	f=fopen(fn_artikull,"rb");
		if (f==NULL){
		   printf("\n \n   Gabim ne file");
		   return;} 
		nr_art=0;
		  while (fread(&a[nr_art],sizeof(struct artikulli),1,f)){nr_art++;}
		 fclose(f);
		 
		 	//hapa filen e furnizimit per te pare gjendjen e produktit;
		f=fopen(fn_furnizim,"rb");
		 if (f==NULL){
	 		printf("\n \n   Gabim ne file");
			return;} 
		fread(&furnizim,sizeof(struct furnizimi),1,f);	
		 fclose(f);	
		 
		 perfitim_1:
		j=0;
		for(i=0; i<nr_art; i++){
			if(leke_bonus > a[i].cmimi &&  furnizim.artikuj_furnizim[i].sasi>0){
				printf("\n%d-%s", j+1, a[i].emertimi);
				v[j]=i; // perdor vektorin per te ruajtur vendin real te artikujve qe do afishohen;
				j++;
				t=1;
			}
		}
		
		if(t=0){
			printf("Nuk ka gjendje te produktit ose ju nuk zoteroni mjaftueshem pike.");
			return;
		}
		
		perfitim_2:
		printf("\nJu lutem zgjidhni numrin perkates per produktin qe deshironi te perfitoni: "); 
		scanf("%d",&zgjedhja);
		if(zgjedhja==0 || zgjedhja>j){
			printf("\nZgjedhja nuk eshte e vlefshme");
			goto perfitim_2;
		}
			
		else {
			furnizim.artikuj_furnizim[v[zgjedhja]].sasi--;
			k[v[zgjedhja]].piket -= a[v[zgjedhja]].cmimi;
			save();
			perfitim_3:
			printf("\nDeshironi te vazhdoni me perfitimin nga piket? \n1- Po\n2- Jo\n");
			scanf("%d", &zgjedhja);	 
			if(zgjedhja==1){
				goto perfitim_1;
			}
			else if(zgjedhja==2) return;
			else {
				printf("\nZgjedhja nuk eshte e vlefshme.");
				goto perfitim_3;
			}
		}		
   }
	else if(zgjedhja==2) return;
	else {
		printf("\nZgjedhja nuk eshte e vlefshme.");
		goto z;
	}	
	return;
}

int main(){

 char k;
 do{
   Zgjedhja: 
   menu();
   fflush(stdin);
   k=getchar();
   if (k=='1') Regjistrim_artikulli();
   else if (k=='2') Regjistrim_klienti();
   else if (k=='3') Furnizim();
   else if (k=='4')  Shitje();			
   else if (k=='5') Gjendja_ne_magazine ();
   else if (k=='6') Klientet_qe_shpenzojn_me_shume();
   else if (k=='7') Klientet_qe_blejne_me_shpesh(); 
   else if (k=='8') Kerkim_artikulli_sipas_kodit();
   else if (k=='9') Piket_e_klientit(); 
   else {
		printf("\nZgjedhja nuk eshte e vlefshme"); goto Zgjedhja;
   }
   printf("\n\n Shtypni nje karakter per te vazhduar...");
   fflush(stdin);
   k= getchar();   
 }while (k!='d' && k!='D' && k!=27); 
 return 0;
}