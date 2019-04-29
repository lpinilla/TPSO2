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


	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	initialize_list(memory_location, 1024*1024); //creo que le puse 1mb de memoria
	*((char *) memory_location)='h';
	*((char *) memory_location + 1)='o';
	*((char *) memory_location + 2)='l';
	*((char *) memory_location + 3)='a';
	init_graphics();
	//initial_info();
	
	ncPrint("Loading IDT");
	ncNewline();
	load_idt();
	ncNewline();
	ncPrint("Done IDT");

	
	/*ncPrint("Initial address of memory");
	ncPrintHex((uint64_t)&memory_location);*/
	//clear_screen();
	return getStackBase();
}


int main()
{
	draw_string("Hola \n");
	//to_userland();
	// inicializamos el scheduler
	init_scheduler(scheduler);
	// creamos el proceso testing 1
	process_t t1 = create_process(testing_process1);
	// creamos el proceso testing 2
	process_t t2 = create_process(testing_process2);
	// lo agregamos al scheduler
	add_process(scheduler, t1);
	add_process(scheduler, t2);
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

void initial_info(){

	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();

	ncPrint("[Finished]");
	ncClear();
}

