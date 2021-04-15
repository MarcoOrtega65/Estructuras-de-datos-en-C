#include <stdio.h>
#include <stdlib.h>
# define TamDatIns 20

typedef struct NodArb {
	struct NodArb *Izquierdo;
	char Dato; 
	struct NodArb *Derecho;
}* ARBOL;

void inOrder(ARBOL);
void insertNode(ARBOL *, char);
void postOrder(ARBOL);
void preOrder(ARBOL);
void Principal();

int main(int argc, char *argv[]) {
	Principal();
	return 0;
}

void Principal(){
	ARBOL Arbol = NULL;
	char * DatIns;
	int i = 0;
	
	
	DatIns = malloc(TamDatIns * sizeof(char));
	
	printf("Ingrese los datos a insertar\n");
	gets(DatIns);
	
	printf("\n");
	
	while(DatIns[i] != '\0'){
		insertNode(&Arbol,  DatIns[i]);
		i++;
	}
	
	printf("\nValores en inOrden\n");
	inOrder(Arbol);
	printf("\nValores en preOrden\n");
	preOrder(Arbol);
	printf("\nValores en postOrden\n");
	postOrder(Arbol);
}

void insertNode(ARBOL * Arbol, char Insertar ){
	
	if ( *Arbol == NULL ) {
		*Arbol = malloc( sizeof( ARBOL ) );

		if ( *Arbol != NULL ) {
			( *Arbol )->Dato = Insertar;
			( *Arbol )->Izquierdo = NULL;
			( *Arbol )->Derecho = NULL;
		}
		else {
			printf( "%d No hay memoria dispobile.\n", Insertar );
		}
	}
	else {
		if ( Insertar < ( *Arbol )->Dato ) {
			insertNode( &( ( *Arbol )->Izquierdo ),  Insertar);
		}
		else if ( Insertar > ( *Arbol )->Dato ) {
			insertNode( &( ( *Arbol )->Derecho ), Insertar );
		}
	}
}

void inOrder( ARBOL Arbol ){
	if ( Arbol != NULL ) {
		inOrder( Arbol->Izquierdo );
		printf( "%3c", Arbol->Dato );
		inOrder( Arbol->Derecho );
	}
}

void preOrder( ARBOL Arbol ){ 
	if ( Arbol != NULL ) {
		printf( "%3c", Arbol->Dato );
		preOrder( Arbol->Izquierdo );
		preOrder( Arbol->Derecho );
	}
}

void postOrder(  ARBOL Arbol ){
	if ( Arbol != NULL ) {
		postOrder( Arbol->Izquierdo );
		postOrder( Arbol->Derecho );
		printf( "%3c", Arbol->Dato );
	} 
}



