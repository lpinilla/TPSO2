#include <interrupts.h>
#include <time.h>
#include <naiveConsole.h>
#include <graphics.h> // testeando
#include <lib.h>

static unsigned long ticks = 0;

void timer_handler(void * stack_pointer) {
	ticks++;
	context_switch(stack_pointer);
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void time_wait(int n_ticks){
	_sti();
	int goal_ticks = ticks + n_ticks;
	while(ticks < goal_ticks){
		_hlt();
	}
}
