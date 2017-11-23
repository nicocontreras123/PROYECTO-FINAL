#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
	// Número mágico extraído desde el archivo.
	uint8_t magikNumber[4];
	// Ancho y alto de la matriz.
	uint32_t N;
	uint32_t M;
	// Cantidad de bacterias (población)
	uint32_t cantidad;
} DescriptorBacterias;



int main(){
	
	
	FILE *fr, *fw;
	int entero, entero_h;
	DescriptorBacterias db;
	
	fr = fopen("bacterias.bin", "rb");
	
	// Lee desde el archivo los datos y son almacenados en la estructra DescriptorBacterias
	// fread(Puntero_destino, Tamano_lectura, Cantidad_a_leer, Puntero_FILE)
	fread(&db, sizeof(DescriptorBacterias), 1, fr);
	
	

	bool entorno = true;
	int estados = 1;
	
	bool campo[db.N][db.N];
	int i, j;
	for(i = 0; i<db.N; i++){
		for(j=0;j<db.N;j++){
			campo[i][j] = false;
		}
	}
	printf("bacterias iniciales: %d\n",db.cantidad);
	//se inicia la matriz
	
	campo[7][8] = true;
	campo[8][8] = true;
	campo[9][8] = true;
	campo[9][9] = true;
	campo[8][10] = true;
	//se crea la matriz en pantalla
	
	
	printf("Matriz inicial:\n");
	
	for(i = 0; i<=db.N+1;i++){
		printf("_");
	}
	printf("\n");
	for(i=0; i<db.N; i++){
		printf("|");
		for(j=0; j<db.N; j++){
			if(campo[i][j]){
				printf(" * ");
			}else{
				printf(" . ");
			}
		}
		printf("|\n");
	}
	for(i=0; i<= db.N+1; i++){
		printf("_");
	}
	printf("\n");
	int a;
	printf("¿Cuantos ciclos desea itinerar?: ");
	scanf("%d", &a);
	do{
		printf("Ciclo nro %d", a);
		printf("\n");
		bool carga[db.N][db.N];
		
		//Limpiamos la matriz para el siguente ciclo
		for(i=0; i<db.N; i++){
			for(j=0;j<db.N; j++){
				carga[i][j]= false;
			}
		}
		
		//Una bacteria con dos o tres vecinas sigue viva
		//Osea si tiene menos de dos vecinas MUERE
		//Una bacteria muerta renace si está rodeada con exactamente 3 bacterias vecinas vivas.
		//Por lo que si tiene mas de 3 vecinoas MUERE.
		
		for(i=0; i<db.N; i++){
			int im, in;
			im = i+1;
			in = i-1;
			for(j=0; j<db.N; j++){
				int jm, jn;
				jm = j+1;
				jn = j-1;
				
				if(entorno){
					if(im >= db.N){
						im=0;
					}
					if(in<0){
						in = db.N -1;
					}
					if(jm >= db.N){
						jm = 0;
					}
					if(jn<0){
						jn = db.N -1;
					}
				}
				
				//una bacteria muerta renace si tiene exactamente 3 vecinos vivos
				int vecino = 0;
				if(campo[in][j]){
					vecino++;
				}
				if(campo[in][jm]){
					vecino++;
				}
				if(campo[i][jm]){
					vecino++;
				}
				if(campo[im][jm]){
					vecino++;
				}
				if(campo[im][j]){
					vecino++;
				}
				if(campo[im][jn]){
					vecino++;
				}
				if(campo[i][jn]){
					vecino++;
				}
				if(campo[in][jn]){
					vecino++;
				}
				
				if(campo[i][j] && vecino <2){
					carga[i][j] = false;
				} 
				if(campo[i][j] && (vecino == 2 || vecino == 3)){
					carga[i][j] = true;
				}
				if(campo[i][j] && vecino > 3){
					carga[i][j] = false;
				}
				if(!campo[i][j] && vecino == 3){
					carga[i][j] = true;
				}
			}
		}
		
		memcpy(campo, carga, sizeof(campo));
		
		//se genera la nueva matriz
		
		for(i = 0; i <= db.N + 1; i++)
            	printf("_");
        	printf("\n");
        	for(i = 0; i < db.N; i++){
            printf("|");
            for(j = 0; j < db.N; j++){
                if(campo[i][j])
                    printf(" * ");
                else
                    printf(" . ");
            }
            printf("|\n");
        }
        for(i = 0; i <= db.N + 1; i++)
            printf("_");
        printf("\n");
        a=a-1;
        sleep(1);
	}while(a!=0);
	
	fclose(fr);
	
	// Se abre un nuevo archivo para escritura
	fw = fopen("salida.bin","wb");
	
	// se escribe un entero en el archivo
	// fwrite(Puntero_datos_origen, tamano_datos, cantidad_datos, puntero_FILE);
	entero = 999;
	fwrite(&entero, sizeof(int), 1, fw);
	
	// se escribe un entero que fue inicializado como número hexadecimal
	entero_h = 0xCAFEBABE;
	fwrite(&entero_h, sizeof(int), 1, fw);
	
	// se cierra el archivo para confirmar la escritura del buffer.
	fclose(fw);

	
	
	return 0;
}
