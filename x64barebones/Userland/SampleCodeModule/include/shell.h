#ifndef _SHELL_H_
#define _SHELL_H_

/*
PARA AGREGAR UN COMANDO HAY QUE AGREGARLO EN EL DEFINE EN ORDEN, DESPUES EN EL VECTOR DE FUNCIONES EN EL MISMO NUMERO DEL
DEFINE Y DESPUES EN EL VECTOR DE STRINGS ENE EL NUMERO DEL DEFINE -1 (podriamos cambiar esto para que sea mas consistente)
*/
#include <utilities.h>
#include <string.h>
#include <syscall.h>
#include <time.h>
#include <syscall.h>
#include <pong.h>
#include <openlg.h>
#include <time.h>

#define RETURN_ADRESS 0xDEADC0DE

#define INVALID_COMMAND 0
#define PONG_COMMAND 1
#define TIME_COMMAND 2
#define SHUTDOWN_COMMAND 3
#define BEEP_COMMAND 4
#define MAKE_DIV 5
#define AYUDA 6
#define SCAN_F 7
#define PRINT_F 8
#define INVALID 9

#define COMMANDS 9

#define MAX_LENGTH 20

typedef void (*func)();

void try_scan_f();
void invalid_command();
void play_pong();
void show_time();
void shutdown();
void print_user();
void make_beep();
void make_div();
void ayuda();
void try_invalid_function();
void try_print_f();
uint64_t * shell();


#endif
