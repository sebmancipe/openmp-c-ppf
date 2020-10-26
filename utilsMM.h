/*
# * Archivo: utilsMM.h
# * Autor: Sebastian Mancipe <sebastian.mancipe@correo.usa.edu.co>
# * Última Modificación: 14 de Octubre, 2020
# * ----------------------------------------------------------------
# * El archivo utilsMM.h contiene la definción de las funciones implementadas
# * por el módulo utilsMM.c para ser usadas en el archivo MM1C.c. Principalmente
# * se encuentran inicialización de argumentos, tomas de tiempos y presentación
# * de resultados.
*/

extern void argsInit(int argc, char *argv[]); // Inicialización de argumentos
extern void mmStart(int threadId); // Incio de toma de tiempo
extern void mmStop(int threadId); // Fin de toma de tiempo
extern int mmParallel(void); // Inicializar datos
extern void mmEnd(void); // Presentar datos
