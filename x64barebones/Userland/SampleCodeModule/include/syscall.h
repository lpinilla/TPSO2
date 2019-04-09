#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stdint.h>
#include <call_int_80.h>

#define READ 3
#define WRITE 4
#define DRAW_PIXEL 5
#define X_RES 6
#define Y_RES 7
#define CLEAR_SCREEN 8
#define SHADOW_PIXEL 9
#define MOVE_EVERYTHING_UP 10
#define SWAP_BUFFERS 11
#define CLEAR_SHADOW_BUFFER 12
#define TIME 13
#define INIT_GRAPHICS 14
#define COLOR_WRITE 15
#define RESET_CURSOR 16
#define BEEP 17
#define SLEEP 18
#define NEW_LINE 19

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

#endif
