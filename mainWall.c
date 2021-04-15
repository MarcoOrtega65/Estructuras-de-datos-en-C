#include <stdio.h>
#include <stdlib.h>
#define TamNom 30

typedef struct nodo{
	int Prioridad;
	int NumProd;
	struct nodo *Siguiente;
}*Nodo;

typedef struct cola{
	Nodo NodInic;
	Nodo NodFin;
	int Tam;
}*Cola;

typedef struct caja{
	char * Cajero;
	int Num;
	Cola COLA;
	struct caja * Siguiente;
}*Caja;

void AbrirCaja(Caja *, Caja *, int);
void AgregarCliente(Caja *);
void CerrarCaja(Caja *);
void DespacharCliente(Caja *);
Caja GenCaja(Caja, int);
Nodo GenNod();
void ImprimirCaja(Caja);
void ImprimirColaClientes(Nodo);
int isEmptyCajas(Caja);
int isEmptyCola(Cola);
void MenuInic();
Nodo NodParaImp(Caja, int);
void Principal();

int main(int argc, char *argv[]) {
	Principal();
	return 0;
}

void Principal(){
	Caja CajInic = NULL;
	Caja CajFin = NULL;
	int TamCaja = 1;
	int Opcion = 1;
	
	while(Opcion){
		system("pause");
		system("cls");
		
		MenuInic();
		fflush(stdin);
		scanf("%d", &Opcion);
	
		switch(Opcion){
			case 1:			//AGREGAR CLIENTE
				if(isEmptyCajas(CajInic))
					printf("No hay cajas abiertas\n");
				else
					AgregarCliente(&CajInic);
			break;
			case 2:			//DESPACHAR CLIENTE
				DespacharCliente(&CajInic);
			break;
			case 3:			//ABRIR CAJA
				AbrirCaja(&CajInic, &CajFin, TamCaja);
				TamCaja ++;
			break;
			case 4:			//CERRAR CAJA
				if(!isEmptyCajas(CajInic))
  					CerrarCaja(&CajInic);			///REVISAR
				else
					printf("No hay cajas abiertas\n");
				//TamCaja --;
			break;
			case 5:			//IMPRIMIR CAJAS
				if(!isEmptyCajas(CajInic))
					ImprimirCaja(CajInic);
				else
					printf("\nNo hay cajas\n");
			break;
			case 6:			//IMPRIMIR CLIENTTES
				if(!isEmptyCajas(CajInic))
					ImprimirColaClientes(NodParaImp(CajInic, TamCaja));
				else
					printf("No hay cajas abiertas\n");
			break;
			case 7:
				Opcion = 0;
			break;
			default:
				printf("\nOpcion inalida, intente de nuevo\n");
				Opcion = 1;
			break;
		}
	}
	
}

Caja GenCaja(Caja CajInic, int TamCaja){
	Caja CajaNueva;
	
	CajaNueva = (Caja)malloc(sizeof(Caja));
	CajaNueva->Cajero = (char*)malloc(TamNom * sizeof(char));
	CajaNueva->Siguiente = NULL;
	CajaNueva->COLA = NULL;
	
	printf("Se abre una nueva caja con el numero %d \nIngrese el nombre del cajero: \n", TamCaja);
	
	CajaNueva->Num = TamCaja;
  	
	fflush(stdin);
	
	gets(CajaNueva->Cajero);
  	
	return CajaNueva;
}

void AbrirCaja(Caja * CajInic, Caja * CajFin, int TamCaja){
	Caja Temporal, NewCaja;
	
	Temporal = (Caja)malloc(sizeof(Caja));
	NewCaja = (Caja)malloc(sizeof(Caja));
	NewCaja = GenCaja((*CajInic), TamCaja);
	
	if (isEmptyCajas((*CajInic)))
		(*CajFin) = (*CajInic) = NewCaja;
	else {
		Temporal = (*CajFin);
		(*CajFin) = NewCaja;
		Temporal->Siguiente = NewCaja;
	}
}

void CerrarCaja(Caja * CajInic){
	Caja Temporal;
	int NumCaja;
	Temporal = (Caja)malloc(sizeof(Caja));
	
	if(isEmptyCola((*CajInic)->COLA)){
		
		printf("\nSe intena.\n");
		Temporal = (*CajInic);
		(*CajInic) = (*CajInic)->Siguiente;
		printf("\nSe Cerro con exito la caja: %d.\n", Temporal->Num);
	}
	else{
		printf("\nAun hay clientes en la caja\n");
	}
	
}

Nodo NodParaImp(Caja CajInic, int Tam){
	int Opc;
	int i = 1;
	
	printf("Ingrese el numero de la caja a imprimir: \n");
	scanf("%d", &Opc);
	
	if(Opc < Tam){
		while (i <= Opc){
			if(i == Opc && !isEmptyCola(CajInic->COLA))
				return CajInic->COLA->NodInic;
			else
				CajInic = CajInic->Siguiente;
			i++;
		}
	}
	else
		printf("Opcion invalida");
	
}

Nodo GenNod(){
	Nodo nodoNuevo;
	
	nodoNuevo = (Nodo)malloc(sizeof(Nodo));
	nodoNuevo->Siguiente = NULL;
	
	printf("Ingrese la prioridad:\n");
	scanf("%d", &nodoNuevo->Prioridad);
	
	printf("Ingrese la cantidad de productos:\n");
	scanf("%d", &nodoNuevo->NumProd);
	
	return nodoNuevo;
}

void AgregarCliente(Caja * CajInic){
	Nodo Temporal, NewNod;
	Caja InicCopy;
	int i = 1;
	
	NewNod = GenNod();
	InicCopy = (*CajInic);
  	
  	while (i <= NewNod->Prioridad){
		if(i == NewNod->Prioridad){
			if (isEmptyCola((*CajInic)->COLA)){
				(*CajInic)->COLA = (Cola)malloc(sizeof(Cola));
				(*CajInic)->COLA->NodInic = (*CajInic)->COLA->NodFin = NewNod;
			}
			else {
				Temporal = (*CajInic)->COLA->NodFin;
				(*CajInic)->COLA->NodFin = NewNod;
				Temporal->Siguiente = NewNod;
			}
			(*CajInic)->COLA->Tam ++;
		}
		
		(*CajInic) = (*CajInic)->Siguiente;
		i ++;
	}
	
	(*CajInic) = InicCopy;
}

void DespacharCliente(Caja * CajInic){
	Nodo Temporal;
	Caja InicCopy;
	int NumCaja;
	int i = 1;
	
	InicCopy = (Caja)malloc(sizeof(Caja));
	Temporal = (Nodo)malloc(sizeof(Nodo));
	
	InicCopy = (*CajInic);
	
	printf("\nIngrese el numero de la caja que desea despachar: \n");
	scanf("%d", &NumCaja);
	
	while (i <= NumCaja){
		if(i == NumCaja){
			if(!isEmptyCola((*CajInic)->COLA)){
				Temporal = (*CajInic)->COLA->NodInic;
				(*CajInic)->COLA->NodInic = (*CajInic)->COLA->NodInic->Siguiente;
				(*CajInic)->COLA->Tam--;
				printf("\nSe despacho con exito.\n");
			}
			else{
				printf("\nCola Vacia\n");
			}
		}
		(*CajInic) = (*CajInic)->Siguiente;
		i ++;
	}
	
	free(Temporal);
	(*CajInic) = InicCopy;
}

void MenuInic(){

	printf("----------------Wallmart----------------\n");
	printf("\nMenu de opciones\n");
	printf("1-Agregar Cliente\n2-Despachar Cliente\n3-Abrir Caja\n4-Cerrar Caja\n5-Imprimir Cajas\n6-Impimir Clientes\n7-Salir\n");
	printf("\nOpcion: ");
}

int isEmptyCajas(Caja CAJAS){		//ESTA VACIA
	
	if(!CAJAS){
		return 1;
	} else
		return 0;
}

int isEmptyCola(Cola COLA){		//ESTA VACIA
	
	if(!COLA){
		return 1;
	} else
		return 0;
}

void ImprimirColaClientes(Nodo NodInic){
	printf("\n-----------------Valores en la cola-----------------\n");
	printf("\nProductos:\n");

	while (NodInic != NULL) {
		printf(" %d -->", NodInic->NumProd);
		NodInic = NodInic->Siguiente;
	}
	printf(" NULL");
	printf("\n");
	
}

void ImprimirCaja(Caja CajInic){		//funcion para imprimir el nodo
	printf("\n-----------------Cajas disponiles-----------------\n");
	
	while (!isEmptyCajas(CajInic)){
		printf("Numero de Caja: %d\n", CajInic->Num);
		printf("Cajero: ");
		puts(CajInic->Cajero);
		CajInic = CajInic->Siguiente;
		printf("\n");
	}
}
