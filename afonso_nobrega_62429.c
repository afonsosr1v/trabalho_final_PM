#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio_ext.h>

#define TRUE 1
#define FALSE 0

struct LUGAR {
	char occupied;
	char name[100];
	char checked_in;	//estrutura a ser usada no programa todo
	int id_luggage;
	int id_reservation_code;
};


int contar(FILE * fp, const char *palavra) {				//contar as ocorrencias de uma palavra num ficheiro de texto
	char str[20];
	char *pos;
	int i, cont;
	
	cont=0;
	
	while((fgets(str, 20, fp))!=NULL) {
		i=0;
		
		while((pos=strstr(str + i, palavra))!=NULL)  {
			i=(pos-str) + 1;
			
			cont++;
		}
	}
	return cont;
}


int structure() {				//não devia fazer isto com printfs
	char escolha[10];
	char plane[20];
	int exec, turis;
	FILE * fp;
	fflush(stdin); //fpurge não estava a funcionar
	
	printf("Please indicate the aircraft type (Ex. A318): ");
	scanf(" %s", escolha);
	__fpurge(stdin);
	printf("\n %s as been selected\n", escolha);
	

	if ((strcmp(escolha, "a318")==0) || (strcmp(escolha, "A318")==0)) {
		strcpy(plane, "Airbus318");
		fp=fopen(plane, "r");
		turis=contar(fp, "abcdef");
		fclose(fp);
		fflush(fp);
		fp=fopen(plane, "r");
		exec=contar(fp, "abcd") - turis;		// '-turis' pq abcd tambem aparece nas filas turisticas
		fclose(fp);
		fflush(fp);
		
		printf("Airbus318: Executive rows=%d, Touristic rows=%d\n", exec, turis);
	}
	else if ((strcmp(escolha, "a319")==0) || (strcmp(escolha, "A319")==0)) {
		strcpy(plane, "Airbus319");
		fp=fopen(plane, "r");
		turis=contar(fp, "abcdef");
		fclose(fp);
		fflush(fp);
		fp=fopen(plane, "r");
		exec=contar(fp, "abcd") - turis;
		fclose(fp);
		fflush(fp);
		printf("Airbus318: Executive rows=%d, Touristic rows=%d\n", exec, turis);
	}
	else if ((strcmp(escolha, "a320")==0) || (strcmp(escolha, "A320")==0)) {
		strcpy(plane, "Airbus320");
		fp=fopen(plane, "r");
		turis=contar(fp, "abcdef");
		fclose(fp);
		fflush(fp);
		fp=fopen(plane, "r");
		exec=contar(fp, "abcd") - turis;
		fclose(fp);
		fflush(fp);
		printf("Airbus318: Executive rows=%d, Touristic rows=%d\n", exec, turis);
	}
	else if ((strcmp(escolha, "a321")==0) || (strcmp(escolha, "A321")==0)) {
		strcpy(plane, "Airbus321");
		fp=fopen(plane, "r");
		turis=contar(fp, "abcdef");
		fclose(fp);
		fflush(fp);
		fp=fopen(plane, "r");
		exec=contar(fp, "abcd") - turis;
		fclose(fp);
		fflush(fp);
		printf("Airbus318: Executive rows=%d, Touristic rows=%d\n", exec, turis);

	}
	return 1;
}
int occup() {						//diagrama para mostrar a "planta" do avião
	int fila, aviao, SI;
	char lugarx;
	int seek;
	char flname[20];
	int i, ix, j, jx, exec, turis;
	FILE * fp;
	struct LUGAR lugar;
	struct LUGAR reserva;
	
	printf("Whats the flight code? ");
	scanf(" %s", flname);
	
	fp=fopen(flname, "r+b");	
	fread(&aviao, sizeof(int), 1, fp);			//ler o tipo de avião do programa
	
	printf("\n Occupied seats are marked with a '.'\n");
	
	
	if (aviao==318) {
		ix= 19;
		exec=3;
		turis=16;
	}
	else if (aviao==319) {
		ix=22;
		exec=4;
		turis=18;
	}
	else if (aviao==320) {
		ix=27;
		exec=5;
		turis=22;
	}
	else if (aviao==321) {
		ix=33;
		exec=6;
		turis=27;
	}
	
	i=0;
	j=0;
	jx=0;						//jx vai contar os lugares visto que incrementa em todos menos na linha de numeros de fila
	
	for(j=0; j<7; j++) {				//Provavelmente havia forma mais simples de fazer isto
		i=0;
		
		
		if((j==0)||(j==6)) {
			for(i=0; i<ix; i++) {
				if(i<exec) {
					printf("  ");
				}
				else if (i>=exec) {
					SI=0;					//limpar só para ter a certeza que não há erros
					SI=(4*exec)+((i-exec)*6)+jx; 		//fórmula que relaciona o i e o j com posições no ficheiro para lugares turisticos
					seek=0;
					seek=sizeof(struct LUGAR)*SI+sizeof(int);
				
					fseek(fp, seek , SEEK_SET);
					fread(&lugar, sizeof(struct LUGAR), 1, fp);
					
					if(lugar.occupied=='0') {
						switch (j) {
							case 0 : printf(" a"); break;
							case 6 : printf(" f"); break;
						}
					}
					else {
						printf(" .");
					}
				}
			
			}
		jx=jx+1;
		}
		else if (j==3) {
			for (i=0; i<ix; i++) {
				if (i<9) {
					printf(" %d", i+1);
				}
				else {
					printf("%d", i+1);
				}
			}
		}
		else {
			
			for (i=0; i<ix; i++) {
				
			
				if(i<exec) {
					SI=0;
					SI=i*4+jx-1;			//fórmula que relaciona o i e o j com posições no ficheiro para lugares executivos
					seek=0;
					seek=sizeof(struct LUGAR)*SI+sizeof(int);
				
					fseek(fp, seek , SEEK_SET);
					fread(&lugar, sizeof(struct LUGAR), 1, fp);
					
					if(lugar.occupied=='0') {
						switch(j) {
							case 1: printf(" a"); break;
							case 2: printf(" b"); break;
							case 4: printf(" c"); break;
							case 5: printf(" d"); break;
						}
					}
					else {
						printf(" .");
					}
				}
				else if (i>=exec) {
					SI=0;
					SI=(4*exec)+((i-exec)*6)+jx;	//fórmula que relaciona o i e o j com posições no ficheiro para lugares turisticos
					seek=0;
					seek=sizeof(struct LUGAR)*SI+sizeof(int);
				
					fseek(fp, seek , SEEK_SET);
					fread(&lugar, sizeof(struct LUGAR), 1, fp);
					
					if (lugar.occupied=='0') {
						switch(j) {
							case 1: printf(" b"); break;
							case 2: printf(" c"); break;
							case 4: printf(" d"); break;
							case 5: printf(" e"); break;
						}
					}
					else {
						printf(" .");
					}
				}
		
			}
		jx=jx+1;
		}
	printf ("\n");
	}
	printf("\n");
	fclose(fp);
	fflush(fp);
	return 1;
}

int pnreservs() {
	int fila, aviao, SI;
	char lugarx, ocupado;
	int seek;
	char flname[20];
	int i, ix, j, jx, exec, turis;
	FILE * fp;
	struct LUGAR lugar;
	
	printf("Qual o voo? ");
	scanf(" %s", flname);
	fp=fopen(flname, "r+b");	
	
	for(i=0;i<200;i++) {
		seek=sizeof(struct LUGAR)*(i+1)+sizeof(int);
		fseek(fp, seek , SEEK_SET);
		ocupado='0';				//se isto não estiver aqui ocorrem situações inesperadas
		fread(&lugar, sizeof(struct LUGAR), 1, fp);
		ocupado=lugar.occupied;
		if(ocupado=='1') {
			printf(" %s,", lugar.name);
		}
		ocupado='0';				//se isto não estiver aqui ocorrem situações inesperadas
	}
	fclose(fp);
	fflush(fp);
	return 1;

}

int reserv() {
	
	int fila, aviao, SI, XI;
	char lugarx, occup;
	int lugarnum, seek, lugg, code;
	char nome[100];
	char flname[20];
	int i, ix, j, jx, exec, turis;
	FILE * fp;
	struct LUGAR lugar;
	struct LUGAR reserva;
	

	
	printf("Whats the flight code? ");
	scanf(" %s", flname);
	
	fp=fopen(flname, "r+b");	
	fread(&aviao, sizeof(int), 1, fp);
	
	
	printf("\n Occupied seats are marqued with a '.'\n");			//podia estar aqui o occup() em vez disto tudo
	
	if (aviao==318) {
		ix= 19;
		exec=3;
		turis=16;
	}
	else if (aviao==319) {
		ix=22;
		exec=4;
		turis=18;
	}
	else if (aviao==320) {
		ix=27;
		exec=5;
		turis=22;
	}
	else if (aviao==321) {
		ix=33;
		exec=6;
		turis=27;
	}
	
	i=0;
	j=0;
	jx=0;
	
	for(j=0; j<7; j++) {				
		i=0;
		
		
		if((j==0)||(j==6)) {
			for(i=0; i<ix; i++) {
				if(i<exec) {
					printf("  ");
				}
				else if (i>=exec) {
					SI=0;
					SI=(4*exec)+((i-exec)*6)+jx;
					seek=0;
					seek=sizeof(struct LUGAR)*SI+sizeof(int);
				
					fseek(fp, seek , SEEK_SET);
					fread(&lugar, sizeof(struct LUGAR), 1, fp);
					occup=lugar.occupied;
					
					
					if(occup=='0') {
						switch (j) {
							case 0 : printf(" a"); break;
							case 6 : printf(" f"); break;
						}
					}
					else {
						printf(" .");
					}
				}
			
			}
		jx=jx+1;
		}
		else if (j==3) {
			for (i=0; i<ix; i++) {
				if (i<9) {
					printf(" %d", i+1);
				}
				else {
					printf("%d", i+1);
				}
			}
		}
		else {
			
			for (i=0; i<ix; i++) {
				
			
				if(i<exec) {
					SI=0;
					SI=i*4+jx-1;
					seek=0;
					seek=sizeof(struct LUGAR)*SI+sizeof(int);
				
					fseek(fp, seek , SEEK_SET);
					fread(&lugar, sizeof(struct LUGAR), 1, fp);
					
					if(lugar.occupied=='0') {
						switch(j) {
							case 1: printf(" a"); break;
							case 2: printf(" b"); break;
							case 4: printf(" c"); break;
							case 5: printf(" d"); break;
						}
					}
					else {
						printf(" .");
					}
				}
				else if (i>=exec) {
					SI=0;
					SI=(4*exec)+((i-exec)*6)+jx;
					seek=0;
					seek=sizeof(struct LUGAR)*SI+sizeof(int);
				
					fseek(fp, seek , SEEK_SET);
					fread(&lugar, sizeof(struct LUGAR), 1, fp);
					
					if (lugar.occupied=='0') {
						switch(j) {
							case 1: printf(" b"); break;
							case 2: printf(" c"); break;
							case 4: printf(" d"); break;
							case 5: printf(" e"); break;
						}
					}
					else {
						printf(" .");
					}
				}
		
			}
		jx=jx+1;
		}
	printf ("\n");
	}
	
	
	fclose(fp);
	fflush(fp);
	
	fp=fopen(flname, "r+b");

	
	printf("Whats the row? ");
	scanf(" %d", &fila);
	printf("Whats the seat? ");
	scanf(" %c", &lugarx);
	__fpurge(stdin);
	printf("Whats the costumer's name? ");
	fgets(nome, 100, stdin);
	__fpurge(stdin);
	printf("O nome é: %s", nome);
	printf("Whats the luggage ID? ");
	scanf(" %d", &lugg);
	__fpurge(stdin);
	printf("Whats the reservation code? ");
	scanf(" %d", &code);
	
	//printf("Para confirmar:\n Nome: %s\n Lugg: %d\nID: %d\n", nome, lugg, code);		IGNORAR ISTO, foi só para propósitos de debugging

	
	if(fila>exec) {
		switch(lugarx) {
			case 'a':
			case 'A': lugarnum=0; break;
			case 'b':
			case 'B': lugarnum=1; break;
			case 'c': 
			case 'C': lugarnum=2; break;
			case 'd':
			case 'D': lugarnum=3; break;
			case 'e':
			case 'E': lugarnum=4; break;
			case 'f': 
			case 'F': lugarnum=5; break;
		}
		//struct LUGAR reserva = {'1'; nome[100]; '0'; lugg; code};				Não estava a funcionar, fiz manualmente da proxima linha
		reserva.occupied='1';
		strcpy(reserva.name, nome);
		reserva.checked_in='0';
		reserva.id_luggage=lugg;
		reserva.id_reservation_code=code;
		
		//printf("Para confirmar:\n Nome: %s\n Lugg: %d\nID: %d\n", reserva.name, reserva.id_luggage, reserva.id_reservation_code);			IGNORAR ISTO, foi só para propósitos de debugging	
		XI=0;
		XI=4*exec+(fila-1-exec)*6+lugarnum;				//O objetivo é relacionar as variaveis com a posição dos lugares no ficheiro
		seek=0;
		seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
		occup=0;
		fseek(fp, seek, SEEK_SET);
		fread(&lugar, sizeof(struct LUGAR), 1, fp);
		occup=lugar.occupied;
	
		if(occup=='1') {
			printf("Already Taken");
			return 0;
		}
		else {
			seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
			fseek(fp, seek, SEEK_SET);
			fwrite(&reserva, sizeof(struct LUGAR), 1, fp);
			
			if(fwrite!=0) {
				printf("Reserved with success!\n");
			}
			else {
				printf("ERROR writing on file!\n");
			}
		}
		
	}
	else {
		switch(lugarx) {
			case 'a':
			case 'A': lugarnum=1; break;
			case 'b': 
			case 'B': lugarnum=2; break;
			case 'c': 
			case 'C': lugarnum=3; break;
			case 'd': 
			case 'D': lugarnum=4; break;
		}
		
		
		
		//struct LUGAR reserva = {'1'; nome[100]; '0'; lugg; code};			 //não está a guardar bem as coisas
		reserva.occupied='1';
		strcpy(reserva.name, nome);					//alternativa manual mas funcional
		reserva.checked_in='0';
		reserva.id_luggage=lugg;
		reserva.id_reservation_code=code;

		XI=0;
		XI=((fila-1)*4) + lugarnum-1;		
		seek=0;					
		seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
		occup=0;
		fseek(fp, seek, SEEK_SET);
		fread(&lugar, sizeof(struct LUGAR), 1, fp);
		occup=lugar.occupied;
		if(occup=='1') {
			printf("Already Taken!\n");
		}
		else {
			seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
			fseek(fp, seek, SEEK_SET);
			fwrite(&reserva, sizeof(struct LUGAR), 1, fp);
			
			if(fwrite!=0) {
				printf("Reserved with success!\n");
			}
			else {
				printf("ERROR writing on file!\n");
			}
		}
	}
	
	
	fclose(fp);
	fflush(fp);
	
	return 1;

}

int changeseat() {
	int i;
	char flname[20];
	int aviao, ix, exec, turis, XI, fila, filad, lugarnum, seek;
	char lugar, lugard, lugarx, occupa;
	FILE * fp;
	struct LUGAR origem;
	struct LUGAR destino;
	struct LUGAR hold;
	
	occup();			//desta vez lembrei-me de por o occup()

	printf("Whats the flight code again? ");
	scanf(" %s", flname);
	
	fp=fopen(flname, "r+b");	
	fread(&aviao, sizeof(int), 1, fp);
	
	if (aviao==318) {
		ix= 19;
		exec=3;
		turis=16;
	}
	else if (aviao==319) {
		ix=22;
		exec=4;
		turis=18;
	}
	else if (aviao==320) {
		ix=27;
		exec=5;
		turis=22;
	}
	else if (aviao==321) {
		ix=33;
		exec=6;
		turis=27;
	}
		
	fclose(fp);
	fflush(fp);
	
	fp=fopen(flname, "r+b");
	
	
	printf("Whats the row? ");
	scanf(" %d", &fila);
	__fpurge(stdin);
	printf("Whats the seat? ");
	scanf(" %c", &lugarx);
	__fpurge(stdin);
	if(fila>exec) {
		switch(lugarx) {
			case 'a':
			case 'A': lugarnum=0; break;
			case 'b':
			case 'B': lugarnum=1; break;
			case 'c': 
			case 'C': lugarnum=2; break;
			case 'd':
			case 'D': lugarnum=3; break;
			case 'e':
			case 'E': lugarnum=4; break;
			case 'f': 
			case 'F': lugarnum=5; break;
		}
		XI=0;
		XI=4*exec+(fila-1-exec)*6+lugarnum;
		seek=0;
		seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
		occupa='0';
		fseek(fp, seek, SEEK_SET);
		fread(&origem, sizeof(struct LUGAR), 1, fp);
		occupa=origem.occupied;
	
		if(occupa=='0') {
			printf("Noone here!\n");
			return 1;
		}
		else {
			printf("Which seat would you like to go to? ");
			scanf(" %d%c", &filad, &lugard);
			__fpurge(stdin);
			destino.occupied=origem.occupied;
			strcpy(destino.name, origem.name);
			destino.checked_in=origem.checked_in;
			destino.id_luggage=origem.id_luggage;
			destino.id_reservation_code=origem.id_reservation_code;
			
			origem.occupied='0';
			strcpy(origem.name, " ");
			origem.checked_in='0';
			origem.id_luggage=0;
			origem.id_reservation_code=0;
			
			seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
			fseek(fp, seek, SEEK_SET);
			fwrite(&origem, sizeof(struct LUGAR), 1, fp);
			
			
			
			
			if(filad>exec) {
				switch(lugard) {
					case 'a':
					case 'A': lugarnum=0; break;
					case 'b':
					case 'B': lugarnum=1; break;
					case 'c': 
					case 'C': lugarnum=2; break;
					case 'd':
					case 'D': lugarnum=3; break;
					case 'e':
					case 'E': lugarnum=4; break;
					case 'f': 
					case 'F': lugarnum=5; break;
				}
			
				XI=4*exec+(filad-1-exec)*6+lugarnum;
				seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
				fseek(fp, seek, SEEK_SET);
				fread(&hold, sizeof(struct LUGAR), 1, fp);
				if(hold.occupied=='1') {
					printf("Already taken!");
					return 0;
				}
				else {
					seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
					fseek(fp, seek, SEEK_SET);
					fwrite(&destino, sizeof(struct LUGAR), 1, fp);
					printf("Seat has been changed!");
				}
			}
			else {
				switch(lugard) {
					case 'a':
					case 'A': lugarnum=1; break;
					case 'b': 
					case 'B': lugarnum=2; break;
					case 'c': 
					case 'C': lugarnum=3; break;
					case 'd': 
					case 'D': lugarnum=4; break;
				}
				XI=((filad-1)*4) + lugarnum-1;
				
				seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
				fseek(fp, seek, SEEK_SET);
				fread(&hold, sizeof(struct LUGAR), 1, fp);
				if(hold.occupied=='1') {
					printf("Already taken!");
					return 0;
				}
				else {
					seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
					fseek(fp, seek, SEEK_SET);
					fwrite(&destino, sizeof(struct LUGAR), 1, fp);
					printf("Seat has been changed!");
				}
			}
		}
	}		
	else {
		switch(lugarx) {
			case 'a':
			case 'A': lugarnum=1; break;
			case 'b': 
			case 'B': lugarnum=2; break;
			case 'c': 
			case 'C': lugarnum=3; break;
			case 'd': 
			case 'D': lugarnum=4; break;
		}
		XI=0;
		XI=((fila-1)*4) + lugarnum-1;
		seek=0;
		seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
		occupa='0';
		fseek(fp, seek, SEEK_SET);
		fread(&origem, sizeof(struct LUGAR), 1, fp);
		occupa=origem.occupied;
	
		if(occupa=='0') {
			printf("Noone here!\n");
			return 0;
		}
		else {
			printf("Which seat would you like to go to? ");
			scanf(" %d%c", &filad, &lugard);
			__fpurge(stdin);
			destino.occupied=origem.occupied;
			strcpy(destino.name, origem.name);
			destino.checked_in=origem.checked_in;
			destino.id_luggage=origem.id_luggage;
			destino.id_reservation_code=origem.id_reservation_code;
			
			origem.occupied='0';
			strcpy(origem.name, " ");
			origem.checked_in='0';
			origem.id_luggage=0;
			origem.id_reservation_code=0;
			
			seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
			fseek(fp, seek, SEEK_SET);
			fwrite(&origem, sizeof(struct LUGAR), 1, fp);
			
			if(filad>exec) {
				switch(lugard) {
					case 'a':
					case 'A': lugarnum=0; break;
					case 'b':
					case 'B': lugarnum=1; break;
					case 'c': 
					case 'C': lugarnum=2; break;
					case 'd':
					case 'D': lugarnum=3; break;
					case 'e':
					case 'E': lugarnum=4; break;
					case 'f': 
					case 'F': lugarnum=5; break;
				}
			
				XI=4*exec+(filad-1-exec)*6+lugarnum;
				seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
				fseek(fp, seek, SEEK_SET);
				fread(&hold, sizeof(struct LUGAR), 1, fp);
				if(hold.occupied=='1') {
					printf("Already taken!");
					return 0;
				}
				else {
					seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
					fseek(fp, seek, SEEK_SET);
					fwrite(&destino, sizeof(struct LUGAR), 1, fp);
					printf("Seat has been changed!");
				}
			}
			else {
				switch(lugard) {
					case 'a':
					case 'A': lugarnum=1; break;
					case 'b': 
					case 'B': lugarnum=2; break;
					case 'c': 
					case 'C': lugarnum=3; break;
					case 'd': 
					case 'D': lugarnum=4; break;
				}
				XI=((filad-1)*4) + lugarnum-1;
				
				seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
				fseek(fp, seek, SEEK_SET);
				fread(&hold, sizeof(struct LUGAR), 1, fp);
				if(hold.occupied=='1') {
					printf("Already taken!");
					return 0;
				}
				else{
					seek=(sizeof(struct LUGAR)*XI)+sizeof(int);
					fseek(fp, seek, SEEK_SET);
					fwrite(&destino, sizeof(struct LUGAR), 1, fp);
					printf("Seat has been changed!");
				}
			}
		}
	}	
	fclose(fp);
	fflush(fp);
	return 1;
}

int assign() {				//em principio está funcional //yup, está funcional
	char flname[20];
	int i, total;
	int aviao;
	FILE * fp;
	struct LUGAR lugar;
	
	
	printf("Write the plane type: A");			//se tiver tempo pedir uma string e guardar só o inteiro em vez de pedir o logo o inteiro //não tive tempo
	scanf("%d", &aviao);
	printf("Write the flight code [Ex: TP1234]: ");
	scanf(" %s", flname);

	fp = fopen(flname, "wb");
	
		switch(aviao) {							//escrever o inteiro no primeiro espaço do ficheiro para ler rapidamente o tipo de avião quando o tiver que abrir
			case 318 : fwrite(&aviao, sizeof(int), 1, fp);
				total=108;
				break;
			case 319 : fwrite(&aviao, sizeof(int), 1, fp);
				total=124;
				break;
			case 320 : fwrite(&aviao, sizeof(int), 1, fp);
				total=152;
				break;
			case 321 : fwrite(&aviao, sizeof(int), 1, fp);
				total=186;
				break;
		} 
		
	for (i=0; i<total; i++) {						//encher o ficheiro de lugares vazios
		lugar.occupied='0';
		strcpy(lugar.name, " ");
		lugar.checked_in='0';
		lugar.id_luggage=0;
		lugar.id_reservation_code=0;
		fwrite(&lugar, sizeof(struct LUGAR), 1, fp);
	}
	
	fclose(fp);
	fflush(fp);
	
	return 1;
	
}

int fill() {									//não tive tempo :(
	printf("não implementado\n");
	return 0;
}

int histo() {									//não tive tempo :( parecia interessante
	printf("não implementado\n");
	return 0;
}

int files() {									//não tive tempo :(
	printf("não implementado\n");
	return 0;
}

int menu() {										// !!! NÃO ESQUECER DE FAZER LOOP DO MENU	//tá feito
	int escolha;
	printf("\t Aircraft Business\n");
	printf("0 - Exit\n");
	printf("1 - Show the Structure of a Plane\n");
	printf("2 - Show the occupancy of a flight\n");
	printf("3 - Show the passenger names with a reservation for the flight\n");
	printf("\n");
	printf("4 - Reserve a flight with seat number\n");
	printf("5 - Change the seat of a Reservation\n");
	printf("6 - Assign a plane to a specific flight (opening of a flight\n");
	printf("\n");
	printf("7 - Fill in a flight with random passengers\n");
	printf("\n");
	printf("8 - Histogram of flight occupancy per type of seat\n");
	printf("9 - Generation of the files ''names'' and ''surnames''\n");
	printf("\nSelection: ");
	scanf(" %d", &escolha);
	
		switch(escolha) {
			case 0 : printf("goodbye\n");
				exit(1);
			case 1 : structure(); break;
			case 2 : occup(); break;
			case 3 : pnreservs(); break;
			case 4 : reserv(); break;
			case 5 : changeseat(); break;
			case 6 : assign(); break;
			case 7 : fill(); break;
			case 8 : histo(); break;
			case 9 : files(); break;
		}
	
}

int main() {			//loop do menu
	int i;
	do {
	i=menu();
	
	}while(i!=0);
}

	
	
	
	
	
	
	
