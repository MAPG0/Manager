#include <stdio.h>

typedef struct{
char nombre [30];
int popularidad;
int energia;
int energia_max;
int fans;
}Idol;


void mostrar(const Idol *i);
int limitar(int valor, int minimo, int maximo);
void ensayar(Idol *i);
void descansar(Idol *i);
int esta_activa(const Idol *i);
int colaboracion(Idol *a, Idol *b);





int main(void) {

    // HU-01: DEFINIR LAS INTEGRANTES

    Idol Jennie = {"jennie", 50, 100, 100, 12000};
    Idol rose = {"rose", 50, 100, 100, 12000 };

    Idol *p = &Jennie;

    printf("\nHU-01: DATOS INICIALES\n");
    mostrar(&Jennie);

    // HU-02: ACCESO A CAMPOS Y APUNTADORES
    

    printf("\n HU-02: APUNTADORES \n");

    printf("Acceso con (Jennie.fans): %d\n", Jennie.fans);
    printf("Acceso con ((*p).fans): %d\n", (*p).fans);
    printf("Acceso con (p->fans): %d\n", p->fans);

    printf("Direccion de Jennie: %p\n", (void *)&Jennie);
    printf("Direccion guardada en p: %p\n", (void *)p);


    
    // HU-03: MOSTRAR UNA INTEGRANTE


    printf("\nHU-03: MOSTRAR\n");

    mostrar(&Jennie);
    
    // HU-04: LIMITAR UN VALOR


    printf("\n HU-04: LIMITAR \n");

    printf("Caso 1 (-5): %d\n", limitar(-5, 0, 100));
    printf("Caso 2 (40): %d\n", limitar(40, 0, 100));
    printf("Caso 3 (150): %d\n", limitar(150, 0, 100));



    // HU-05: ENSAYAR 20 VECES


    printf("\n HU-05: ENSAYAR\n");

    Jennie.energia = 100;
    Jennie.popularidad = 50;

    for (int i=0; i < 20; i++) {
        ensayar(&Jennie);
    }

    mostrar(&Jennie);


    // HU-06: DESCANSAR 20 VECES
    

    printf("\n HU-06: DESCANSAR \n");

    Jennie.energia = 0;

    for (int i = 0; i < 20; i++) {
        descansar(&Jennie);
    }

    mostrar(&Jennie);
    // HU-06: ENSAYAR Y DESCANSAR ALTERNADAMENTE

    printf("\nHU-06: ALTERNAR\n");

    Jennie.energia = 100;

    for (int i = 0; i < 5; i++) {

        ensayar(&Jennie);

        printf("Despues de ensayar %d: energia = %d\n",
               i + 1, Jennie.energia);

        descansar(&Jennie);

        printf("Despues de descansar %d: energia = %d\n",
               i + 1, Jennie.energia);
    }


    // HU-07: COMPROBAR SI ESTA ACTIVA
    

    printf("\n HU-07: ESTA ACTIVA \n");

    Jennie.energia = 0;
    printf("Energia 0: %d\n", esta_activa(&Jennie));

    Jennie.energia = 1;
    printf("Energia 1: %d\n", esta_activa(&Jennie));

  


    // HU-09: COLABORACION

    printf("\n HU-09: COLABORACION \n");

    Jennie.energia = 100;
    rose.energia = 100;

    Jennie.popularidad = 50;
    rose.popularidad = 50;

    printf("Misma integrante: %d\n",
           colaboracion(&Jennie, &Jennie));

    printf("Con NULL: %d\n",
           colaboracion(NULL, &rose));

    printf("Colaboracion valida: %d\n",
           colaboracion(&Jennie, &rose));

    mostrar(&Jennie);
    mostrar(&rose);


    // HU-10: DINAMICA POR TURNOS


    printf("\nHU-10: DINAMICA POR TURNOS\n");

    // Reiniciamos la energia para esta prueba.
    Jennie.energia = 100;
    rose.energia = 100;

    Idol *turno = &Jennie;
    Idol *otra = &rose;

    while (esta_activa(turno) && esta_activa(otra)) {

        ensayar(turno);

        printf("%s ensaya. Energia: %d\n",
               turno->nombre, turno->energia);

        // Intercambio de apuntadores.
        Idol *temporal = turno;
        turno = otra;
        otra = temporal;
    }

    printf("\nResultado de la dinamica:\n");

    if (esta_activa(&Jennie)) {
        printf("%s conserva energia: %d\n",
               Jennie.nombre, Jennie.energia);
    } else if (esta_activa(&rose)) {
        printf("%s conserva energia: %d\n",
               rose.nombre, rose.energia);
    } else {
        printf("Ambas integrantes se quedaron sin energia.\n");
    }


    
}


void mostrar(const Idol *i){
printf("Nombre de Idol  %s\n",i->nombre);
printf("popularidad de Idol  %d\n",i->popularidad);
printf("Energia de Idol  %d\n",i->energia);
printf("Energia Maxima de Idol  %d\n",i->energia_max);
printf("fans de jennie  %d\n",i->fans);
}

int limitar(int valor, int minimo, int maximo){
if (valor < minimo){
return minimo;
}if(valor > maximo){
return maximo;
}
return valor;

}
void ensayar(Idol *i){

i->popularidad +=5 ;
i->energia =limitar(i->energia-20,0,i->energia_max) ;

}
void descansar(Idol *i){
    i->energia = limitar(i->energia + 30, 0, i->energia_max);
}

int esta_activa(const Idol *i) {
    if (i->energia > 0) {
    
        return 1;
    }

    return 0;
}

int colaboracion(Idol *a, Idol *b) {

    if (a == NULL || b == NULL || a == b) {
        return 0;
    }

    a->popularidad += 10;
    b->popularidad += 10;

    a->energia = limitar(a->energia - 15, 0, a->energia_max);
    b->energia = limitar(b->energia - 15, 0, b->energia_max);

    printf("%s y %s hicieron una colaboracion.\n",
           a->nombre, b->nombre);

    return 1;
}
