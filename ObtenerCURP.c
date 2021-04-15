/*
	PROGRAMA QUE CALCULA EL CURP DE UNA PERSNA
*/

# include <stdio.h>
# include <stdlib.h>
# define TAMNom 8
# define TAMFec 10
# define TAMEntNac 27
# define TAMCurp 18

void Principal();
void CrearArrays();
void SettArrays();
void IngresarDatos();
void ObtenerCurp();
void Abrir_Archivo();
void Cargar_Estados(FILE *);
void ObtenerClave(char []);
void ObtenerCurp();
void ObtenerLetrasCurp();


char *CURP;
char *Nombre;
char *Fecha;
char *EntNac;
char Genero;
char ClaEst[2];


int main(int argc, char *argv[]) {
	Principal();
	return 0;
}

void Principal(){
	int i;
	CrearArrays();
	
	printf("\t----Programa para Crear el CURP-----\n");
	
	IngresarDatos();
	
	ObtenerCurp();
	
	system("cls");
	
	printf("\n\n\n---------------------------------------\n\tCURP: ");
	
	for(i = 0; i < TAMCurp; i++){
		printf("%c", CURP[i]);
	}
	
	printf("\n---------------------------------------\n\n\n\n\n");
}

void CrearArrays(){
	Nombre = malloc(TAMNom * sizeof(char));	
	Fecha = malloc(TAMFec * sizeof(char));
	EntNac = malloc(TAMEntNac * sizeof(char));
	CURP = malloc(TAMCurp * sizeof(char));
	
	SettArrays();
}

void SettArrays(){
	int i;
	
	for(i = 0; i < TAMNom; i ++){
		Nombre[i] = '*';
	}
	
	for(i = 0; i < TAMFec; i ++){
		Fecha[i] = '*';
	}
	
	for(i = 0; i < TAMEntNac; i ++){
		EntNac[i] = '*';
	}
	
	for(i = 0; i < TAMCurp; i ++){
		CURP[i] = '*';
	}
	
}

void IngresarDatos(){
	
	fflush(stdin);
	
	printf("\n\nIngrese su nombre con mayusculas y separado por espacios (APELLIDOPATERNO APELLIDOMATERNO NOMBRES):\n");
	gets(Nombre);
	
	printf("\nIngrese su Fecha de nacimiento separado por '/'(dd/mm/aaaa):\n");
	gets(Fecha);
	
	printf("\nGenero (H: Hombre, M: Mujer):\n");
	scanf("%c", &Genero);
	
	fflush(stdin);
	
	printf("\nEntidad de Nacimiento con mayusculas (MEXICO, AGUASCALIENTES, etc)\n");
	gets(EntNac);
	
	Abrir_Archivo();
}
//-----------------------MANERJADOR DE ARCHIVOS-------------------------

void Abrir_Archivo(){
	FILE *Man_Arch = NULL;
	
	Man_Arch = fopen ("Estados.txt", "r");
		
	
	if(Man_Arch == NULL){
		printf("No fue posible abrir el archivo\n");
	}
	
	Cargar_Estados(Man_Arch);

}

void Cargar_Estados(FILE *Man_Arch){
	char buffer[TAMEntNac];
	int i, j;
	int Res = 0;
	
	for(i = 0; i < 32; i++){
		
		if(Res)
			break;
									
		fgets(buffer, TAMEntNac, Man_Arch);
		
		for(j = 2; EntNac[j-2] != '\0'; j++){
			
			if(buffer[j] != EntNac[j-2]){
				
				Res = 0;
				break;
			}
			else
				Res = 1;
		}	
	}
	
	fclose(Man_Arch);		//cerramos el archivo ya que no se cupa denuevo
	
	ObtenerClave(buffer);
	
}

//-------------------------------------------------------------------------------------

void ObtenerCurp(){	
	int i, j;
	char buffer[TAMFec];
	
	for(i = 0; i < TAMFec; i ++){
		buffer[i] = '*';
	}
	
	ObtenerLetrasCurp();		//funcion que obtiene las letras del nombre del usuario
	
	CURP[10] = Genero; 			//insertamos el genero
		
	for(i = 0; i < 2; i++){		//Cambiamos la posicion de la fecha 
		
		buffer[i] = Fecha[i + 8];
		buffer[i + 2] = Fecha[i + 3];
		buffer[i +4] = Fecha[i];
	}
	
	for(i = 0; i < 6; i++){				// damos de alta la fecha en el curp
		CURP[i + 4] = buffer[i];
	}
	
	for(i = 0; i < 2; i++){
		CURP[i + 11] = ClaEst[i]; 		//asignamos la clave de estadoOrte
	}
	
}

void ObtenerLetrasCurp(){
	int i, j, k, l;
	int res = 0;
	int lim = 0;
	char Vocales[] = {'A', 'E', 'I', 'O', 'U'};
	char Consonantes[] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z'};
	
	
	
	for(i = 0; i < TAMNom; i++){
		if(res)
			break;
			
		if(!i)
			CURP[i] = Nombre[i]; //Primera posicion del Curp
		
		for(j = 0; j < 21; j++){
			if(Nombre[i] == Consonantes[j]){
				CURP[13] = Nombre[i];		
				res = 1;
				break;
			}
		}
	}
	
	res = 0;
	
	//OBTENIENDO LA SEGUNDA POSICION DEL ARRAY
	for(i = 1; Nombre[i] != 32; i++){
		if(res)
			break;
			
		for(j = 0; j < 5; j++){
			if(Nombre[i] == Vocales[j]){
				CURP[1] = Vocales[j];
				res = 1;
				break;
			}
		}
	}
	//OBTENEMOS LA TERCERA POSICION DEL ARRAY
	
	res = 0;
	j = 0;
	
	for(i = 0; i < TAMNom; i++){
		if(j){
			switch(res){
				case 1:		//despues del primer espacio esta su segundo apellido
					CURP[2] = Nombre[i];	//se asigna la primera letr del apellido
					
					for(k = i+1; k < TAMNom; k++){
						if(lim)
							break;

						for(l = 0; j < 21; l++){
							if(Nombre[k] == Consonantes[l]){
								CURP[14] = Nombre[k];		//se asigna la primer consonante del apellido
								lim = 1;
								break;
							}
						}
					}
					
					j = 0;
				break;	
				case 2:		//despues del segundo espacio esta su Nombre
					CURP[3] = Nombre[i]; //se asigna la primera letr del nombre
					
					lim = 0;
					
					for(k = i+1; k < TAMNom; k++){
						if(lim)
							break;

						for(l = 0; l < 21; l++){
							if(Nombre[k] == Consonantes[l]){		
								CURP[15] = Nombre[k];		//se asigna la primer consonante del nombre
								lim = 1;
								break;
							}
						}
					}
					j = 0;
				break;
			}
		}
		
		if(Nombre[i] == 32){
			res +=1;
			j = 1;
		}
	}
}
void ObtenerClave(char buffer []){
	int i;
	
	for(i = 0; i < 2; i++){
		ClaEst[i] = buffer[i];
	}
}
