#include <syscall.h>

void sys_write(char * string, int size){
  _call_int_80((uint64_t) WRITE, 1, (uint64_t) string, (uint64_t)size, 0, 0);
}
char sys_read(char * string, int size){
  return _call_int_80(READ, 1, (uint64_t) string, size, 0, 0);
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
  return _call_int_80((uint64_t) TIME,(uint64_t) selector, 0,0,0,0);
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
