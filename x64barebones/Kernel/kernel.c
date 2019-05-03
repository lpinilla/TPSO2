#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <graphics.h>
#include <time.h>
#include <idt_loader.h>
#include <mem_manager.h>
#include <process.h>
#include <scheduler.h>
#include <interrupts.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;
static void * const memory_location = (void *) 0x700000;

void testing_process1();
void testing_process2();

typedef int (*EntryPoint)();

void initial_info(void);


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void to_userland(){
		//ACA ES DONDE SALTA A USERLAND, COMENTAR ESTA LINEA SI QUEREMOS PROBAR COSAS DE KERNEL
		((EntryPoint)sampleCodeModuleAddress)();
}

void * initializeKernelBinary(){
	
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	load_idt();

	initialize_list(memory_location, 1024*1024); //creo que le puse 1mb de memoria
	init_graphics();

	// inicializamos el scheduler
	init_scheduler();

	return getStackBase();
}

void child1_process(){
	for(int i=0; i<30; i++){
		draw_string("1111111111111111111111111\n");
	}
	//Siempre vamos a tener que matar a cada proceso al final por nuestra cuenta,
	// el scheduler nuestro no tiene manera de saber cuando un proceso termino, si no se lo indicamos
	// ya sea haciendo kill_process() o haciendo set_state P_TERMINATE, cualquiera de los dos funciona
	kill_process();
}

void child2_process(){
	while(1){
		draw_string("2222222222222222222222222\n");
	}
}

void father_process(){

	process_t c1 = create_process((uint64_t)child1_process, "First Child Process");
	process_t c2 = create_process((uint64_t)child2_process, "Second Child Process");
	run_process(c1);
	run_process(c2);
	print_current_processes();
	//haltcpu();

	while(1){
		draw_string("FFFFFFFFFFFFFFFFFFFFFFFFF\n");
	}
}

int main()
{
	//Por como esta armado el scheduler siempre vamos a tener un primer proceso que crea a los demas
	process_t father = create_process((uint64_t)father_process, "Father Process");
	run_process(father);
	
	return 0;
}

