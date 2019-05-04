#include "include/syscall.h"

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
#define MY_MALLOC 20
#define MY_FREE 21
#define MEM_BASE 22
#define NEW_PROCESS 23
#define KILL_PROCESS 24
#define LIST_PROCESSES 25

void sys_write(char * string, int size){
  _call_int_80( (uint64_t) WRITE, 1, (uint64_t) string, (uint64_t)size, 0, 0);
}

char sys_read(char * string, int size){
	char ret = (char) _call_int_80(READ, 1, (uint64_t) string, size, 0, 0);
  return ret;
}

void sys_clear_console(){
	_call_int_80(CLEAR_SCREEN, 0,0,0,0,0);
}

void sys_draw_pixel(int x, int y, int r, int g, int b){
	_call_int_80((uint64_t)DRAW_PIXEL, (uint64_t)x,(uint64_t) y,(uint64_t) r,(uint64_t) g,(uint64_t) b);
}

void sys_shadow_pixel(int x, int y, int r, int g, int b){
	_call_int_80((uint64_t) SHADOW_PIXEL, (uint64_t)x,(uint64_t) y,(uint64_t) r,(uint64_t) g,(uint64_t) b);
}
int sys_time(int selector){
	int ret = _call_int_80((uint64_t) TIME,(uint64_t) selector, 0,0,0,0);
  return ret;
}

void sys_swap_buffers(){
	_call_int_80((uint64_t) SWAP_BUFFERS, 0, 0, 0, 0, 0);
}

void sys_clear_shadow_buffer(){
	_call_int_80((uint64_t) CLEAR_SHADOW_BUFFER, 0, 0, 0, 0, 0);
}

void sys_color_write(char * string, int size, int foreground_color, int background_color){
	_call_int_80((uint64_t) COLOR_WRITE,(uint64_t) string,(uint64_t) size,(uint64_t) foreground_color,(uint64_t) background_color, 0);
}

void sys_reset_cursor(){
	_call_int_80((uint64_t) RESET_CURSOR, 0, 0, 0, 0, 0);
}


void sys_new_line(){
	_call_int_80((uint64_t) NEW_LINE, 0, 0, 0, 0, 0);
}

void sys_sleep(int ticks){
  _call_int_80((uint64_t) SLEEP,(uint64_t) ticks,0,0,0,0);
}

void sys_beep(){
  _call_int_80(BEEP,0,0,0,0,0);
}

void* sys_my_malloc(int size){
	void * ret = (void*) _call_int_80(MY_MALLOC,(uint64_t) size,0,0,0,0);
	return ret;
}

void sys_my_free(void* ptr){	
	_call_int_80(MY_FREE,(uint64_t) ptr,0,0,0,0);
}

void * sys_start_of_mem(){
	return (void *) _call_int_80(MEM_BASE, 0, 0,0,0,0);
}

int sys_create_process(void * function, char * name){
	return (int)_call_int_80(NEW_PROCESS, (uint64_t)function, (uint64_t) name, 0, 0, 0);
}

void sys_kill_process(int pid){
	_call_int_80(KILL_PROCESS, (uint64_t)pid, 0, 0, 0, 0);
}

void sys_print_all_procceses(){
	_call_int_80(LIST_PROCESSES, 0, 0, 0, 0, 0);
}