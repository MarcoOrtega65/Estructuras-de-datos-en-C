#include <stdio.h>
#include <stdlib.h>
#define TamCad 35


typedef struct nodo{
	char * Nombre;
	char * Numero;
	char * Email;
	struct nodo * Anterior;
	struct nodo * Siguiente;
}* Nodo;

void AgregarContacto(Nodo *);
void EliminarContacto(Nodo *);
void ImprimirLista(Nodo);
void Menu();
void principal();
int TamNomb(char *);

int main(int argc, char *argv[]) {
	principal();
	return 0;
}

void principal(){
	Nodo ContactoInicial = NULL;
	int Opc = 1;
	
	while(Opc != 0){
		Menu();
		fflush(stdin);
		scanf("%d", &Opc);
		
		switch(Opc){
			case 1:
				AgregarContacto(&ContactoInicial);
			break;
			case 2:
				EliminarContacto(&ContactoInicial);
			break;
			case 3:
				ImprimirLista(ContactoInicial);
			break;
			case 4:
				printf("nombre: ");
				fflush(stdin);
				gets(prueba);
				printf("El valor es: %d\n", TamNomb(prueba));
			break;
		}	
	}
}

void Menu(){
	printf("\n-----Agenda-----\n\n");
	printf("1.-Agregar Contacto\n2.-Eliminar Contacto\n3.-Mostrar Contactos\n\nOpcion: ");
}

int TamNomb(char * Nombre){
	int i = 0;
	int ValorCad = 0;
	
	if(Nombre[i] >= 97 && Nombre[i] <= 122)
		Nombre[i]-= 32;
	
	ValorCad += (int)Nombre[i];
	i++;
	
	while(i < 5 && Nombre[i] != 32){
		
		if(Nombre[i] >= 65 && Nombre[i] <= 90)
			Nombre[i]+= 32;
			
		ValorCad += (int)Nombre[i];
		i++;
	}
	
	puts(Nombre);
	
	return ValorCad;
}

Nodo GenerarNodo(){
	Nodo Contacto;
	
	Contacto = (Nodo)malloc(sizeof(Nodo));
	Contacto->Nombre = malloc(TamCad * sizeof(char));
	Contacto->Numero = malloc(TamCad * sizeof(char));
	Contacto->Email = malloc(TamCad * sizeof(char));
	
	fflush(stdin);
	
	Contacto->Anterior = NULL;
	Contacto->Siguiente = NULL;
	
	printf("Nombre: \n");
	gets(Contacto->Nombre);
	printf("Numero: \n");
	gets(Contacto->Numero);
	printf("E-mail: \n");
	gets(Contacto->Email);
	
	
	return Contacto;
}

int EstaVacia(Nodo ContactoInicial){
	if(!ContactoInicial)
		return 1;
	else
		return 0;
}

void AgregarContacto(Nodo * ContactoInicial){
	Nodo CopAgenda;
	Nodo NuevNodo;
	int i = 0;
	
	NuevNodo = (Nodo)malloc(sizeof(Nodo));
	CopAgenda = (Nodo)malloc(sizeof(Nodo));
	printf("\nisemp: %d\n", EstaVacia((*ContactoInicial)));
	
	CopAgenda = (*ContactoInicial); 
	NuevNodo = GenerarNodo();
	
	if(EstaVacia((*ContactoInicial))){
		printf("insinic\n---");
		TamNomb(NuevNodo->Nombre);
		(*ContactoInicial) = NuevNodo;
		puts((*ContactoInicial)->Nombre);
	}else{
		
		if((*ContactoInicial)->Siguiente != NULL){
			(*ContactoInicial)->Siguiente = NuevNodo; 
			printf("\nSe inseerto Sig\n");
			TamNomb(NuevNodo->Nombre);
		}
		else{
			while ((*ContactoInicial) != NULL) {
				if(TamNomb(NuevNodo->Nombre) < TamNomb((*ContactoInicial)->Nombre)){
				
					(*ContactoInicial) = (*ContactoInicial)->Siguiente;
				}
				else{
					NuevNodo->Anterior = (*ContactoInicial)->Anterior;
					(*ContactoInicial)->Anterior = NuevNodo;
					NuevNodo->Anterior->Siguiente = NuevNodo;
					NuevNodo->Siguiente = (*ContactoInicial);
					printf("i: %d", i++);
				}
			}
			(*ContactoInicial) = CopAgenda;
		}
	}
}

void EliminarContacto(Nodo * ContactoInicial){
	
	
}


int EstaVaciaNod(Nodo ContactoInicial){
	if(!ContactoInicial)
		return 1;
	else
		return 0;
}

void ImprimirLista(Nodo ContactoInicial){
	int i = 0;
	
	printf("\n-----------------Valores en la lista-----------------\n");
	while (ContactoInicial != NULL){
	//	printf("isemp: %d", EstaVaciaNod(NodInic));
		//printf("\ni: %d\t", i++);
		puts(ContactoInicial->Nombre);
		ContactoInicial = ContactoInicial->Siguiente;
	}
	printf("\n");
	
}


