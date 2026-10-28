#include <stdio.h>

typedef struct {
    char nombre[30];
    int bonus;
    int vigencia;
} Cancion;

typedef struct {
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
    Cancion *cancion;
} Idol;


typedef struct {
    char nombre[30];
    Idol miembros[4];
    int n;
    Idol *lider;
} Grupo;

void mostrar(const Idol *i);
int limitar(int valor, int minimo, int maximo);
void ensayar(Idol *i);
void descansar(Idol *i);
int esta_activa(const Idol *i);
int colaboracion(Idol *a, Idol *b);
void asignar_cancion(Idol *i, Cancion *c);
int popularidad_total(const Idol *i);
int cambiar_lider(Grupo *g, Idol *nueva);
void mostrar_grupo(const Grupo *g);
int contar_activas(const Grupo *g);
Idol *idol_mas_cansada(Grupo *g);


int main(void) {

    // HU-01: DEFINIR LAS INTEGRANTES

    Idol Jennie = {"jennie", 50, 100, 100, 12000, NULL};
    Idol rose = {"rose", 50, 100, 100, 12000, NULL};

    Cancion discos[2] = {
        {"Starlight", 10, 3},
        {"Nova", 5, 6}
    };

    Idol *p = &Jennie;

    printf("\nHU-01: DATOS INICIALES\n");
    mostrar(&Jennie);


    // HU-02: ACCESO A CAMPOS Y APUNTADORES

    printf("\nHU-02: APUNTADORES\n");

    printf("Acceso con (Jennie.fans): %d\n", Jennie.fans);
    printf("Acceso con ((*p).fans): %d\n", (*p).fans);
    printf("Acceso con (p->fans): %d\n", p->fans);

    printf("Direccion de Jennie: %p\n", (void *)&Jennie);
    printf("Direccion guardada en p: %p\n", (void *)p);


    // HU-03: MOSTRAR UNA INTEGRANTE

    printf("\nHU-03: MOSTRAR\n");

    mostrar(&Jennie);


    // HU-04: LIMITAR UN VALOR

    printf("\nHU-04: LIMITAR\n");

    printf("Caso 1 (-5): %d\n", limitar(-5, 0, 100));
    printf("Caso 2 (40): %d\n", limitar(40, 0, 100));
    printf("Caso 3 (150): %d\n", limitar(150, 0, 100));


    // HU-05: ENSAYAR 20 VECES

    printf("\nHU-05: ENSAYAR\n");

    Jennie.energia = 100;
    Jennie.popularidad = 50;

    for (int i = 0; i < 20; i++) {
        ensayar(&Jennie);
    }

    mostrar(&Jennie);


    // HU-06: DESCANSAR 20 VECES

    printf("\nHU-06: DESCANSAR\n");

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

    printf("\nHU-07: ESTA ACTIVA\n");

    Jennie.energia = 0;
    printf("Energia 0: %d\n", esta_activa(&Jennie));

    Jennie.energia = 1;
    printf("Energia 1: %d\n", esta_activa(&Jennie));


    // HU-09: COLABORACION

    printf("\nHU-09: COLABORACION\n");

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


    // HU-12: ESTRUCTURA CANCION

    printf("\nHU-12: ESTRUCTURA CANCION\n");

    printf("Cancion: %s | Bonus: %d | Vigencia: %d\n",
           discos[0].nombre, discos[0].bonus, discos[0].vigencia);

    printf("Cancion: %s | Bonus: %d | Vigencia: %d\n",
           discos[1].nombre, discos[1].bonus, discos[1].vigencia);


    // HU-13: IDOL CON CANCIÓN OPCIONAL

    printf("\nHU-13: IDOL CON CANCIÓN OPCIONAL\n");

    // Comprobamos la cancion de Jennie.
    if (Jennie.cancion == NULL) {
        printf("%s no tiene una cancion asignada.\n", Jennie.nombre);
    } else {
        printf("%s tiene asignada la cancion: %s\n",
               Jennie.nombre, Jennie.cancion->nombre);
    }

    // Comprobamos la cancion de Rose.
    if (rose.cancion == NULL) {
        printf("%s no tiene una cancion asignada.\n", rose.nombre);
    } else {
        printf("%s tiene asignada la cancion: %s\n",
               rose.nombre, rose.cancion->nombre);
    }


    // HU-14: ASIGNAR Y QUITAR UNA CANCION

    printf("\nHU-14: ASIGNAR Y QUITAR UNA CANCION\n");

    // Asignamos la misma cancion a las dos integrantes.
    asignar_cancion(&Jennie, &discos[0]);
    asignar_cancion(&rose, &discos[0]);

    printf("\nAsignacion de canciones:\n");

    printf("%s tiene asignada: %s\n",
           Jennie.nombre, Jennie.cancion->nombre);

    printf("%s tiene asignada: %s\n",
           rose.nombre, rose.cancion->nombre);

    // Comprobamos si ambas apuntan a la misma cancion.
    printf("¿Comparten la misma cancion?: %s\n",
           Jennie.cancion == rose.cancion ? "Si" : "No");

    printf("Direccion de la cancion de Jennie: %p\n",
           (void *)Jennie.cancion);

    printf("Direccion de la cancion de Rose: %p\n",
           (void *)rose.cancion);

    // Quitamos la cancion de Jennie.
    asignar_cancion(&Jennie, NULL);

    printf("\nDespues de quitar la cancion a Jennie:\n");

    if (Jennie.cancion == NULL) {
        printf("%s no tiene una cancion asignada.\n",
               Jennie.nombre);
    }

    if (rose.cancion != NULL) {
        printf("%s conserva la cancion: %s\n",
               rose.nombre, rose.cancion->nombre);
    }

    // Comprobamos que pasar una integrante NULL no provoque fallos.
    asignar_cancion(NULL, &discos[1]);

    printf("\nPrueba con integrante NULL: la funcion no fallo.\n");


    // HU-15: POPULARIDAD TOTAL CON BONO DE CANCION

    printf("\nHU-15: POPULARIDAD TOTAL CON BONO DE CANCION\n");

    // Asignamos Starlight a Jennie y Rose.
    asignar_cancion(&Jennie, &discos[0]);
    asignar_cancion(&rose, &discos[0]);

    printf("Popularidad de Jennie: %d\n",
           popularidad_total(&Jennie));

    printf("Popularidad de Rose: %d\n",
           popularidad_total(&rose));

    // Comprobamos que una idol sin cancion no reciba bono.
    asignar_cancion(&Jennie, NULL);

    printf("Jennie sin cancion: %d\n",
           popularidad_total(&Jennie));

    // Volvemos a asignar Starlight a Jennie.
    asignar_cancion(&Jennie, &discos[0]);

    // Quitamos la vigencia de la cancion compartida.
    discos[0].vigencia = 0;

    printf("\nDespues de poner discos[0].vigencia = 0:\n");

    printf("Popularidad de Jennie: %d\n",
           popularidad_total(&Jennie));

    printf("Popularidad de Rose: %d\n",
           popularidad_total(&rose));

    // Restauramos la vigencia para las siguientes pruebas.
    discos[0].vigencia = 3;


    // HU-16: DEFINIR EL GRUPO

    printf("\nHU-16: DEFINIR EL GRUPO\n");

    Grupo g = {0};

    // Definimos el nombre del grupo.
    snprintf(g.nombre, sizeof(g.nombre), "Lumina");

    // Creamos la tercera integrante.
    Idol lisa = {"lisa", 50, 100, 100, 10000, NULL};

    // Agregamos las tres integrantes al grupo.
    g.miembros[0] = Jennie;
    g.miembros[1] = rose;
    g.miembros[2] = lisa;

    g.n = 3;
    g.lider = NULL;

    // Asignamos canciones a las integrantes del grupo.
    asignar_cancion(&g.miembros[0], &discos[0]);
    asignar_cancion(&g.miembros[1], &discos[0]);
    asignar_cancion(&g.miembros[2], &discos[1]);

    printf("Nombre del grupo: %s\n", g.nombre);
    printf("Numero de integrantes: %d\n", g.n);

    printf("Lider inicial: %s\n",
           g.lider == NULL ? "NULL" : g.lider->nombre);


    // HU-17: CAMBIAR LA LIDER DEL GRUPO

    printf("\nHU-17: CAMBIAR LA LIDER DEL GRUPO\n");

    // Cambiamos la lider a la primera integrante.
    printf("Cambiar lider a miembro 0: %d\n",
           cambiar_lider(&g, &g.miembros[0]));

    if (g.lider != NULL) {
        printf("Lider actual: %s\n", g.lider->nombre);
        printf("Fans de la lider: %d\n", g.lider->fans);
    }

    // Guardamos la direccion de la lider actual.
    Idol *lider_anterior = g.lider;

    // Probamos con NULL.
    printf("Cambiar lider con NULL: %d\n",
           cambiar_lider(&g, NULL));

    printf("La lider sigue siendo la misma: %s\n",
           g.lider == lider_anterior ? "Si" : "No");

    // Probamos con el grupo NULL.
    printf("Cambiar lider con grupo NULL: %d\n",
           cambiar_lider(NULL, &g.miembros[0]));

    // Creamos una idol externa con el mismo nombre.
    Idol externa = g.miembros[0];

    printf("Cambiar lider con idol externa: %d\n",
           cambiar_lider(&g, &externa));

    printf("La lider sigue siendo la misma: %s\n",
           g.lider == lider_anterior ? "Si" : "No");

    // La posicion 3 esta fuera de las tres integrantes reales.
    printf("Cambiar lider con miembro 3: %d\n",
           cambiar_lider(&g, &g.miembros[3]));

    printf("La lider sigue siendo la misma: %s\n",
           g.lider == lider_anterior ? "Si" : "No");


    // HU-18: MOSTRAR EL GRUPO

    printf("\nHU-18: MOSTRAR EL GRUPO\n");

    mostrar_grupo(&g);

    // Comprobamos que la funcion soporte NULL.
    printf("\nPrueba con grupo NULL:\n");

    mostrar_grupo(NULL);

    printf("La funcion termino sin fallar.\n");


    // HU-19: CONTAR INTEGRANTES ACTIVAS

    printf("\nHU-19: CONTAR INTEGRANTES ACTIVAS\n");

    // Dos integrantes activas y una sin energia.
    g.miembros[0].energia = 100;
    g.miembros[1].energia = 0;
    g.miembros[2].energia = 50;

    printf("Integrantes activas: %d\n",
           contar_activas(&g));

    // Probamos con NULL.
    printf("Grupo NULL: %d\n",
           contar_activas(NULL));

    // Probamos con un grupo vacio.
    Grupo vacio = {0};

    printf("Grupo vacio: %d\n",
           contar_activas(&vacio));


    // HU-20: ENCONTRAR A LA INTEGRANTE MAS CANSADA

    printf("\nHU-20: ENCONTRAR A LA INTEGRANTE MAS CANSADA\n");

    // Definimos las energias de las integrantes.
    g.miembros[0].energia = 80;
    g.miembros[1].energia = 0;
    g.miembros[2].energia = 40;

    // Buscamos a la integrante con menos energia.
    Idol *cansada = idol_mas_cansada(&g);

    // Comprobamos que el resultado no sea NULL.
    if (cansada != NULL) {

        printf("Integrante mas cansada: %s\n",
               cansada->nombre);

        printf("Energia antes de descansar: %d\n",
               cansada->energia);

        // Descansamos a la integrante encontrada.
        descansar(cansada);

        printf("Energia despues de descansar: %d\n",
               cansada->energia);

        printf("Energia guardada en el grupo: %d\n",
               g.miembros[1].energia);

    } else {
        printf("No hay integrantes en el grupo.\n");
    }

    // Probamos con un grupo NULL.
    printf("Grupo NULL devuelve NULL: %s\n",
           idol_mas_cansada(NULL) == NULL ? "Si" : "No");

    // Probamos con un grupo vacio.
    printf("Grupo vacio devuelve NULL: %s\n",
           idol_mas_cansada(&vacio) == NULL ? "Si" : "No");


    return 0;
}


// HU-03: MOSTRAR UNA INTEGRANTE

void mostrar(const Idol *i) {

    if (i == NULL) {
        return;
    }

    printf("Nombre de Idol  %s\n", i->nombre);
    printf("popularidad de Idol  %d\n", i->popularidad);
    printf("Energia de Idol  %d\n", i->energia);
    printf("Energia Maxima de Idol  %d\n", i->energia_max);
    printf("fans de %s  %d\n", i->nombre, i->fans);
}


// HU-04: LIMITAR UN VALOR

int limitar(int valor, int minimo, int maximo) {

    if (valor < minimo) {
        return minimo;
    }

    if (valor > maximo) {
        return maximo;
    }

    return valor;
}


// HU-05: ENSAYAR

void ensayar(Idol *i) {

    if (i == NULL) {
        return;
    }

    i->popularidad += 10;

    i->energia = limitar(i->energia - 20, 0, i->energia_max);
}


// HU-06: DESCANSAR

void descansar(Idol *i) {

    if (i == NULL) {
        return;
    }

    i->energia = limitar(i->energia + 30, 0, i->energia_max);
}


// HU-07: COMPROBAR SI ESTA ACTIVA

int esta_activa(const Idol *i) {

    if (i == NULL) {
        return 0;
    }

    return i->energia > 0;
}


// HU-09: COLABORACION

int colaboracion(Idol *a, Idol *b) {

    if (a == NULL || b == NULL) {
        return 0;
    }

    if (a == b) {
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


// HU-14: ASIGNAR Y QUITAR UNA CANCION

void asignar_cancion(Idol *i, Cancion *c) {

    if (i == NULL) {
        return;
    }

    i->cancion = c;
}


// HU-15: POPULARIDAD TOTAL CON BONO DE CANCION

int popularidad_total(const Idol *i) {

    if (i == NULL) {
        return 0;
    }

    // Solo sumamos el bono si existe una cancion vigente.
    if (i->cancion != NULL && i->cancion->vigencia > 0) {
        return i->popularidad + i->cancion->bonus;
    }

    return i->popularidad;
}


// HU-17: CAMBIAR LA LIDER DEL GRUPO

int cambiar_lider(Grupo *g, Idol *nueva) {

    if (g == NULL || nueva == NULL) {
        return 0;
    }

    if (g->n <= 0 || g->n > 4) {
        return 0;
    }

    // Buscamos la direccion de la integrante dentro del grupo.
    for (Idol *p = g->miembros;
         p < g->miembros + g->n;
         p++) {

        if (p == nueva) {
            g->lider = nueva;
            return 1;
        }
    }

    return 0;
}


// HU-18: MOSTRAR EL GRUPO

void mostrar_grupo(const Grupo *g) {

    if (g == NULL) {
        return;
    }

    if (g->n < 0 || g->n > 4) {
        return;
    }

    printf("\nGrupo: %s\n", g->nombre);
    printf("Numero de integrantes: %d\n", g->n);

    // Recorremos el grupo usando apuntadores.
    for (const Idol *p = g->miembros;
         p < g->miembros + g->n;
         p++) {

        printf("\n");
        mostrar(p);
    }
}


// HU-19: CONTAR INTEGRANTES ACTIVAS

int contar_activas(const Grupo *g) {

    if (g == NULL || g->n <= 0 || g->n > 4) {
        return 0;
    }

    int contador = 0;

    // Recorremos el arreglo usando apuntadores.
    for (const Idol *p = g->miembros;
         p < g->miembros + g->n;
         p++) {

        if (esta_activa(p)) {
            contador++;
        }
    }

    return contador;
}


// HU-20: ENCONTRAR A LA INTEGRANTE MAS CANSADA

Idol *idol_mas_cansada(Grupo *g) {

    if (g == NULL || g->n <= 0 || g->n > 4) {
        return NULL;
    }

    Idol *cansada = g->miembros;

    // Buscamos a la integrante con menor energia.
    for (Idol *p = g->miembros + 1;
         p < g->miembros + g->n;
         p++) {

        if (p->energia < cansada->energia) {
            cansada = p;
        }
    }

    return cansada;
}
