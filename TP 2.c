#include <stdio.h>
#include <stdbool.h>

//CONSTANTES

#define MAX_NOMBRE 50
#define MAX_LOCALIDAD 30
#define MAX_PROVINCIA 25
#define MAX_PAIS 25
#define MAX_VECTOR 10000

//ESTRUCTURAS

typedef struct{
	int codigo;
	char nombre[MAX_NOMBRE];
	char localidad[MAX_LOCALIDAD];
	char provincia[MAX_PROVINCIA];
	char pais[MAX_PAIS];
}t_sucursal;

typedef struct{
	int codigo;
	int vendedor;
	float importe;
}t_ventas;

//VECTORES

typedef t_ventas t_vec_ventas[MAX_VECTOR]; 
typedef t_sucursal t_vec_sucursal[MAX_VECTOR];

//FUNCIONES

//DECLARACIONES
void menu_principal();
void obtener_ultima_suc();
void obtener_ultima_venta();
void mostrar_archivos();
void agregar_registros();
void agregar_registros();
void procesar_ventas();
void procesar_sucursales();

// PRE MENU

void obtener_ultima_suc(FILE *suc_nuevas, int *ultima_suc_nuevas){
	t_sucursal r_sucursal;

	suc_nuevas = fopen("SUC_NUEVAS.DAT", "r");
	fread(&r_sucursal, sizeof(t_sucursal), 1, suc_nuevas);

	while(!feof(suc_nuevas)){
		*ultima_suc_nuevas = r_sucursal.codigo;
		fread(&r_sucursal, sizeof(t_sucursal), 1, suc_nuevas);
	}
	
	fclose(suc_nuevas);
}

void obtener_ultima_venta(FILE *ventas, int *ultima_suc_ventas){
	t_ventas r_ventas;
	
	ventas = fopen("VENTAS.DAT", "r");
	fread(&r_ventas, sizeof(t_ventas), 1, ventas);
	
	while(!feof(ventas)){
		*ultima_suc_ventas = r_ventas.codigo;
		fread(&r_ventas, sizeof(t_ventas), 1, ventas);
	}	
	
	fclose(ventas);
}

//PUNTO 1

void mostrar_inter(FILE *suc_inter, FILE *suc_nuevas, FILE *ventas, FILE *actualizado){
	t_sucursal r_internacional;
	
	suc_inter = fopen("SUC_INTER.DAT", "r");
	fread(&r_internacional, sizeof(t_sucursal), 1, suc_inter);

	while(!feof(suc_inter)){
		printf("Codigo de sucursal:%d\n", r_internacional.codigo);
		printf("Nombre:%s", r_internacional.nombre);
		printf("Localidad:%s", r_internacional.localidad);
		printf("Povincia:%s", r_internacional.provincia);
		printf("Pais:%s\n", r_internacional.pais);
		fread(&r_internacional, sizeof(t_sucursal), 1, suc_inter);
	}
	fclose(suc_inter);
	mostrar_archivos(suc_inter, suc_nuevas, ventas, actualizado);
}

void mostrar_nuevas(FILE *suc_inter, FILE *suc_nuevas, FILE *ventas, FILE *actualizado){
	t_sucursal r_nuevas;
	
	suc_nuevas = fopen("SUC_NUEVAS.DAT", "r");
	fread(&r_nuevas, sizeof(t_sucursal), 1, suc_nuevas);

	while(!feof(suc_nuevas)){
		printf("Codigo de sucursal:%d\n", r_nuevas.codigo);
		printf("Nombre:%s", r_nuevas.nombre);
		printf("Localidad:%s", r_nuevas.localidad);
		printf("Provincia:%s", r_nuevas.provincia);
		printf("Pais:%s\n", r_nuevas.pais);
		fread(&r_nuevas, sizeof(t_sucursal), 1, suc_nuevas);
	}
	fclose(suc_nuevas);
	mostrar_archivos(suc_inter, suc_nuevas, ventas, actualizado);
}

void mostrar_ventas(FILE *suc_inter, FILE *suc_nuevas, FILE *ventas, FILE *actualizado){
	t_ventas r_ventas;
	
	ventas = fopen("VENTAS.DAT", "r");
	fread(&r_ventas, sizeof(t_ventas), 1, ventas);

	while(!feof(ventas)){
		printf("Codigo de sucursal:%d\t", r_ventas.codigo);
		printf("Codigo del vendedor:%d\t", r_ventas.vendedor);
		printf("Importe:%.2f\n", r_ventas.importe);
		fread(&r_ventas, sizeof(t_ventas), 1, ventas);
	}
	fclose(ventas);
	mostrar_archivos(suc_inter, suc_nuevas, ventas, actualizado);
}

void mostrar_actualizado(FILE *suc_inter, FILE *suc_nuevas, FILE *ventas, FILE *actualizado){
	t_sucursal r_actualizado;
	
	actualizado = fopen("ACTUALIZADO.DAT", "r");
	fread(&r_actualizado, sizeof(t_sucursal), 1, actualizado);

	while(!feof(actualizado)){
		printf("Codigo de sucursal:%d\n", r_actualizado.codigo);
		printf("Nombre:%s", r_actualizado.nombre);
		printf("Localidad:%s", r_actualizado.localidad);
		printf("Povincia:%s", r_actualizado.provincia);
		printf("Pais:%s\n", r_actualizado.pais);
		fread(&r_actualizado, sizeof(t_sucursal), 1, actualizado);
	}
	fclose(actualizado);
	mostrar_archivos(suc_inter, suc_nuevas, ventas, actualizado);
}
//SUBMENU 1

void mostrar_archivos(FILE *suc_inter, FILE *suc_nuevas, FILE *ventas, FILE *actualizado){
	int opcion;
	
	printf("Seleccione el archivo que desea ver:\n\n");
	printf("1. Mostrar el archivo internacional\n");
	printf("2. Mostrar el archivo de nuevas sucursales\n");
	printf("3. Mostrar el archivo de ventas\n");
	printf("4. Mostrar el archivo actualizado(despues de procesar)\n");
	printf("5. Volver\n\n");
	
	scanf("%i", &opcion);
	fflush(stdin);
	
	switch(opcion){
		case 1:
			mostrar_inter(suc_inter, suc_nuevas, ventas, actualizado);
		break;
		case 2:
			mostrar_nuevas(suc_inter, suc_nuevas, ventas, actualizado);
		break;
		case 3:
			mostrar_ventas(suc_inter, suc_nuevas, ventas, actualizado);
		break;
		case 4:
			mostrar_actualizado(suc_inter, suc_nuevas, ventas, actualizado);
		break;
		default:
			menu_principal();
		break;	
	}
}

//PUNTO 2

void validar_entero(int *entero,int min,int max){
	
	while(*entero<=min || *entero>max){
		printf("/n Codigo invalido, ingrese nuevamente uno entre %d y %d /n Codigo :", min, max);
		scanf("%d", entero);
	}	
}

void validar_ingreso(int *ultimo_codigo,int *codigo){
	
	while((*ultimo_codigo >= *codigo) || (*codigo>9999)){
		printf("El codigo de sucursal no se ingreso ordenadamente o no es valido, por favor vuelva a ingresar el codigo para proceder con la carga. \nCodigo :");
		scanf("%d", codigo);
	}
	*ultimo_codigo = *codigo;
}

void agregar_registro_ventas(FILE *ventas, int *ultima_suc_ventas){
	t_ventas r_ventas;
	
	ventas = fopen("VENTAS.DAT", "a");
	
    printf("Ingrese codigo de sucursal:");
    scanf("%d", &r_ventas.codigo);	
    validar_ingreso(ultima_suc_ventas, &r_ventas.codigo);
	
	fflush(stdin);
    
    printf("Vendedor: ");
    scanf("%d", &r_ventas.vendedor);
    validar_entero(&r_ventas.vendedor, 0, 75);
    
    fflush(stdin);

    printf("Importe: ");
	scanf("%f", &r_ventas.importe);
    fflush(stdin);
        
    fwrite(&r_ventas, sizeof(t_ventas), 1, ventas);
    
	fclose(ventas);
}

void agregar_registro_nuevas(FILE *suc_nuevas,int *ultima_suc_nuevas){
	t_sucursal r_sucursal;
	
	suc_nuevas = fopen("SUC_NUEVAS.DAT", "a");
	
	printf("Ingrese codigo de sucursal: ");
    scanf("%d", &r_sucursal.codigo);
    validar_ingreso(ultima_suc_nuevas, &r_sucursal.codigo);
    fflush(stdin);
    
    printf("Nombre: ");
    fgets(r_sucursal.nombre, MAX_NOMBRE, stdin);
    fflush(stdin);

    printf("Localidad: ");
    fgets(r_sucursal.localidad, MAX_LOCALIDAD, stdin);
    fflush(stdin);

    printf("Provincia: ");
    fgets(r_sucursal.provincia, MAX_PROVINCIA, stdin);
    fflush(stdin);

    printf("Pais: ");
    fgets(r_sucursal.pais, MAX_PAIS, stdin);
    fflush(stdin);
        
    fwrite(&r_sucursal, sizeof(t_sucursal), 1, suc_nuevas);
    
    fclose(suc_nuevas);
}


//SUBMENU 2

void agregar_registros(FILE *suc_nuevas, FILE *ventas, int *ultima_suc_nuevas, int *ultima_suc_ventas){
	int opcion;
	
	printf("Seleccione el archivo que desea modificar:\n\n");
	printf("1_Agregar ventas\n");
	printf("2_Agregar nuevas sucursales\n");
	printf("3_Volver\n\n");
	
	scanf("%i", &opcion);
	fflush(stdin);
	switch(opcion){
		case 1:
			agregar_registro_ventas(ventas, ultima_suc_ventas);
			agregar_registros(suc_nuevas, ventas, ultima_suc_nuevas, ultima_suc_ventas);
		break;	
		case 2:
			agregar_registro_nuevas(suc_nuevas, ultima_suc_nuevas);
			agregar_registros(suc_nuevas, ventas, ultima_suc_nuevas, ultima_suc_ventas);
		break;
		default:
			menu_principal();
		break;		
	}
	
}

//PUNTO 3

void procesar_ventas(FILE *ventas){
	ventas = fopen("VENTAS.DAT", "r");
    t_ventas r_ventas;
	int codigo, vendedor;
	float importes_sucursal = 0, importes_vendedor = 0;
	
    if(ventas == NULL){
    	printf("El archivo no existe.\n");
    }
	else{
        fread(&r_ventas, sizeof(t_ventas), 1, ventas);
        while(!feof(ventas)){
        	codigo = r_ventas.codigo;
            importes_sucursal = 0;
            printf("\nDatos sucursal %d = \n", codigo);
            while(!feof(ventas) && (codigo == r_ventas.codigo)){
            	vendedor = r_ventas.vendedor;
            	importes_vendedor = 0;
            	while(!feof(ventas) && (codigo == r_ventas.codigo) && (vendedor == r_ventas.vendedor)){
            		importes_vendedor += r_ventas.importe;
            		fread(&r_ventas, sizeof(t_ventas), 1, ventas);
				} 
				printf("El vendedor %d vendio = $%.2f \n", codigo, importes_vendedor);
				importes_sucursal += importes_vendedor;
			}
			printf("Total sucursal = $%.2f \n\n", importes_sucursal);
        }
    }
    fclose(ventas);

	menu_principal();
}
//PUNTO 4

void procesar_sucursales(FILE *suc_inter, FILE *suc_nuevas, FILE *errores, FILE *actualizado){
    t_sucursal r_internacional, r_nuevas;
	
	suc_inter = fopen("SUC_INTER.DAT", "r");
	suc_nuevas = fopen("SUC_NUEVAS.DAT", "r");
	actualizado = fopen("ACTUALIZADO.DAT", "w");
	errores = fopen("errores.txt", "w");
	
	fread(&r_internacional, sizeof(t_sucursal), 1, suc_inter);
	fread(&r_nuevas, sizeof(t_sucursal), 1, suc_nuevas);
	
	while(!(feof(suc_inter)) && !(feof(suc_nuevas))){
		if(r_internacional.codigo < r_nuevas.codigo){
			fwrite(&r_internacional, sizeof(t_sucursal), 1, actualizado);
			fread(&r_internacional, sizeof(t_sucursal), 1, suc_inter);
		}
		else if(r_internacional.codigo > r_nuevas.codigo){
			fwrite(&r_nuevas, sizeof(t_sucursal), 1, actualizado);
			fread(&r_nuevas, sizeof(t_sucursal), 1, suc_nuevas);			
		}
		else{
			fprintf(errores, "Codigo de sucursal:%d\t Nombre:%s\t Localidad:%s\t Provincia:%s\t Pais:%s\t", r_nuevas.codigo, r_nuevas.nombre, r_nuevas.localidad, r_nuevas.provincia, r_nuevas.pais);
			fwrite(&r_internacional, sizeof(t_sucursal), 1, actualizado);
			fread(&r_internacional, sizeof(t_sucursal), 1, suc_inter);
			fread(&r_nuevas, sizeof(t_sucursal), 1, suc_nuevas);
		}
	}
	
	while(!feof(suc_inter)){
		fwrite(&r_internacional, sizeof(t_sucursal), 1, actualizado);
		fread(&r_internacional, sizeof(t_sucursal), 1, suc_inter);
	}
	while(!feof(suc_nuevas)){
		fwrite(&r_nuevas, sizeof(t_sucursal), 1, actualizado);
		fread(&r_nuevas, sizeof(t_sucursal), 1, suc_nuevas);
	}
	fclose(suc_inter);
    fclose(suc_nuevas);
    fclose(actualizado);
    fclose(errores);
    
    menu_principal();
}

//MENU PRINCIPAL

void menu_principal(){
	FILE *suc_inter;
	FILE *suc_nuevas;
	FILE *ventas;
	FILE *errores;
	FILE *actualizado;
	int opcion;
	int ultima_suc_ventas,ultima_suc_nuevas;
	
	// pre-cond SUPONIENDO QUE YA HAY ARCHIVOS CARGADOS CON ANTERIORIDAD Y ORDENADAMENTE
	
	obtener_ultima_suc(suc_nuevas, &ultima_suc_nuevas);
	obtener_ultima_venta(ventas, &ultima_suc_ventas);
	
	// SE PROCEDE CON LAS ACCIONES DEL PROGRAMA
	
	printf("Elija una opcion:\n\n");
	printf("1_Ver archivos\n");
	printf("2_Ingresar nuevas ventas o sucursales\n");
	printf("3_Ver datos de la ventas del ultimo mes\n");
	printf("4_Procesar las nuevas sucursales\n");
	printf("5_Cerrar programa\n");
	
	scanf("%i", &opcion);
	fflush(stdin);
	
	switch(opcion){
		case 1:
			mostrar_archivos(suc_inter, suc_nuevas, ventas, actualizado); //SUBMENU 1 PUNTO 1
		break;
		case 2:
			agregar_registros(suc_nuevas, ventas, &ultima_suc_nuevas, &ultima_suc_ventas); //SUBMENU 2 PUNTO 2
		break;
		case 3:
			procesar_ventas(ventas); //PUNTO 3
		break;
		case 4:
			procesar_sucursales(suc_inter, suc_nuevas, errores, actualizado); //PUNTO 4
		break;	
		default:
			return;
		break;	
	}
}

int main(){
	
	menu_principal();
}
