#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <stdint.h>
#include "./call_int_80.h"
#include "./utilities.h"

typedef enum {P_READY, P_RUNNING, P_WAITING, P_TERMINATE} pstate_t;

void sys_write(char * string, int size);
char sys_read(char * string, int size);
void sys_clear_console();
void sys_draw_pixel(int x, int y, int r, int g, int b);
void sys_shadow_pixel(int x, int y, int r, int g, int b);
void sys_swap_buffers(void);
void sys_clear_shadow_buffer();
void sys_color_write(char * string, int size, int foreground_color, int background_color);
void sys_reset_cursor(void);
void sys_beep(void);
void sys_sleep(int ticks);
void sys_new_line(void);
int sys_time(int selector);
void * sys_my_malloc(int size);
void sys_my_free(void* ptr);
void * sys_start_of_mem();
int sys_create_process(void * function, char * name);
void sys_kill_process(int pid);
void sys_print_all_procceses();
pstate_t sys_get_process_state(int pid);

#endif
