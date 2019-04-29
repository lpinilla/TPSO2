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
	char buffer[10];
	(cpuVendor(buffer));
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);

	initialize_list(memory_location, 1024*1024); //creo que le puse 1mb de memoria
	init_graphics();
	load_idt();
	// inicializamos el scheduler
	init_scheduler(scheduler);
	// creamos el proceso testing 1
	process_t t1 = create_process(testing_process1);
	// creamos el proceso testing 2
	process_t t2 = create_process(testing_process2);
	draw_string("Hola4 \n");
	// lo agregamos al scheduler
	add_process(scheduler, t1);
	add_process(scheduler, t2);
	/*ncPrint("Initial address of memory");
	ncPrintHex((uint64_t)&memory_location);*/
	//clear_screen();
	return getStackBase();
}


int main()
{
	return 0;
}

void testing_process1(){
	while(1){
		draw_string("Soy el proceso 1 \n");
	}
}
void testing_process2(){
	while(1){
		draw_string("Soy el proceso 2 \n");
	}
}

