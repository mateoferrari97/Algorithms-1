#include<stdio.h>
// CONSTANTES //
#define NO_ENCONTRO -1
#define MAX_DISCOS 500
#define MAX_TITULO 30
#define MAX_TRACKS 25
#define CORTE_CODIGO 9999

// DECLARACION TIPOS //
typedef struct t_disco {
	int codigo;
	char titulo[MAX_TITULO];
	int tracks;
	float precio;
}t_disco;
typedef t_disco t_vec_disco[MAX_DISCOS];

typedef int t_vec_contador[MAX_TRACKS];

// FUNCIONES //

// punto 1 - cargamos la lista de los discos, validando cada dato //
void cargar_discos(t_vec_disco vec_discos, int *maximo_logico){
	int i = 0;
	int codigo;
	printf("BIENVENIDO A LA CARGA DE DISCOS\nINGRESANDO 9999 FINALIZA LA CARGA\n");
	do{
		printf("\nIngrese los datos del disco %i =", i+1);
		printf("\nCodigo:");
		scanf("%i", &codigo);
		fflush(stdin);
		if(codigo != CORTE_CODIGO){	
			while(codigo < 1000 || codigo > 8000){
				printf("Codigo:");
				scanf("%i", &codigo);
				fflush(stdin);
			}
			vec_discos[i].codigo = codigo;
			printf("Titulo: ");
			fgets(vec_discos[i].titulo, MAX_TITULO, stdin);
			fflush(stdin);
			do{
				printf("Tracks: ");
				scanf("%i", &vec_discos[i].tracks);
			}while(vec_discos[i].tracks < 1 || vec_discos[i].tracks > 25);	
			do{
				printf("Precio: ");
				scanf("%f", &vec_discos[i].precio);
				fflush(stdin);
			} while(vec_discos[i].precio < 0);
			*maximo_logico += 1;
			i += 1;
		}
	} while((codigo != CORTE_CODIGO) && (*maximo_logico < MAX_DISCOS));
}

// punto 2 //

void mostrar_disco(t_disco vec_discos, int posicion){
	printf("\nLos datos del disco %i son =\n",posicion+1);
	printf("Codigo:%d\n", vec_discos.codigo);
	printf("Titulo:%s", vec_discos.titulo);
	printf("Precio:%.2f\n", vec_discos.precio);
	printf("Cantidad de tracks:%d\n", vec_discos.tracks);
}

float calcular_maximo_minimo_precio(t_vec_disco vec_discos, int maximo_logico, int opcion){ // 0 si busca en minimo, 1 si busca el maximo.
	float resultado = vec_discos[0].precio;
	int i;
	if(opcion == 0){
		for(i = 0; i < maximo_logico; i++){
			if(vec_discos[i].precio < resultado){
				resultado = vec_discos[i].precio;
			}
		}
	}else{
		for(i = 0; i < maximo_logico; i++){
			if(vec_discos[i].precio > resultado){
				resultado = vec_discos[i].precio;
			}
		}
	}

	return resultado;
}

float calcular_total(t_vec_disco vec_discos, int maximo_logico){
	float resultado = 0;
	int i;
	for(i = 0; i < maximo_logico; i++){
		resultado += vec_discos[i].precio;
	}

	return resultado;
}

void mostrar_determinado_precio(t_vec_disco vec_discos, int maximo_logico, float precio){
	int i;
	for(i = 0; i < maximo_logico; i++){
		if(vec_discos[i].precio == precio){
		mostrar_disco(vec_discos[i], i);
		}
	}
}

void mostrar_promedio(t_vec_disco vec_discos, int maximo_logico){
	int i;
	float suma_precios = 0;
	float promedio = 0;
	float precio_maximo = 0;
	float precio_minimo = 0;

	precio_maximo = calcular_maximo_minimo_precio(vec_discos,maximo_logico,1);
	precio_minimo = calcular_maximo_minimo_precio(vec_discos,maximo_logico,0);
	suma_precios = calcular_total(vec_discos,maximo_logico);
	promedio = suma_precios/maximo_logico;

	printf("El precio promedio de los discos es: %.2f\n", promedio);
	printf("\nDISCOS CON MINIMO PRECIO:\n");
	mostrar_determinado_precio(vec_discos, maximo_logico, precio_minimo);
	printf("\nDISCOS CON MAXIMO PRECIO: \n");
	mostrar_determinado_precio(vec_discos, maximo_logico, precio_maximo);
}

// punto 3 //
void ordenar_discos(t_vec_disco vec_discos, int maximo_logico){
	int i = 0, cambio = 1, j;
	t_disco aux;
	while((cambio == 1) && (i < maximo_logico)){
		i =+ 1;
		for(j = 0; j < maximo_logico-i; j++){
			cambio = 0;
			if(vec_discos[j].codigo > vec_discos[j+1].codigo){
				aux = vec_discos[j];
				vec_discos[j] = vec_discos[j+1];
				vec_discos[j+1] = aux;
				cambio = 1;
			}
		}
	}
}
void mostrar_discos(t_vec_disco vec_discos, int maximo_logico){
	int i;
	printf("Datos ordenados por codigo.\n");
	for(i = 0; i < maximo_logico; i++){
		mostrar_disco(vec_discos[i], i);	
	}
}
// punto 4 //

int buscar_codigo_binaria(t_vec_disco vec_discos, int maximo_logico, int codigo){
	int inicio = 0, fin = maximo_logico-1, i = 0;
	while((inicio <= fin) && (vec_discos[i].codigo != codigo)){
		i = (inicio + fin) / 2;
		if(codigo < vec_discos[i].codigo){
			fin = i-1;
		}		
		else if(codigo > vec_discos[i].codigo)
			inicio = i+1;
		}
	if(vec_discos[i].codigo != codigo){
		return NO_ENCONTRO;
	}
	return i;
}
void mostrar_buscar_disco(t_vec_disco vec_discos, int maximo_logico){
	int codigo_buscado,resultado;
	do{
		printf("\nIngrese el codigo a buscar:");
		scanf("%d", &codigo_buscado);
		resultado = buscar_codigo_binaria(vec_discos, maximo_logico, codigo_buscado);	
	}while(resultado == NO_ENCONTRO);

	mostrar_disco(vec_discos[resultado], resultado);
}

// punto 5 - iniciamos contador en cero y cargamos el contador con los datos de los discos //
void iniciar_contador_tracks(t_vec_contador vec_contador){
	int i;
	for(i = 0; i < MAX_TRACKS; i++){
		vec_contador[i] = 0;
	}	
}

void cargar_contador_tracks(t_vec_contador vec_contador, t_vec_disco vec_discos, int maximo_logico){
	int i;
	for(i = 0; i < maximo_logico; i++){
		vec_contador[vec_discos[i].tracks-1]++;
	}
}
void mostrar_contador_tracks(t_vec_contador vec_contador){
	int i;
	for(i = 0; i < MAX_TRACKS; i++){
		printf("\nCantidad de discos con %i tracks = %i", i+1, vec_contador[i]);
	}
}

// MAIN //

int main(){
int codigo_buscado = 0;
int maximo_logico = 0;
t_vec_disco vec_discos;
t_vec_contador vec_contador;

// PUNTO 1 //

printf("PARTE A = \n\n");
cargar_discos(vec_discos, &maximo_logico);

// PUNTO 2 //
printf("\n\nPARTE B = \n\n");
mostrar_promedio(vec_discos, maximo_logico);

// PUNTO 3 //
printf("\n\nPARTE C = \n\n");
ordenar_discos(vec_discos, maximo_logico);
mostrar_discos(vec_discos, maximo_logico);

// PUNTO 4 //
printf("\n\nPARTE D = \n\n");
mostrar_buscar_disco(vec_discos, maximo_logico);

// PUNTO 5 //
printf("\n\nPARTE E = \n\n");
iniciar_contador_tracks(vec_contador);
cargar_contador_tracks(vec_contador, vec_discos, maximo_logico);
mostrar_contador_tracks(vec_contador);
}

