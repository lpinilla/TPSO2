#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <graphics.h>
#include <time.h>
#include <idt_loader.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

void initial_info(void);
void video_tests(void);
void init_game();


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

	//initial_info();
	ncPrint("Loading IDT");
	ncNewline();
	ncNewline();
	ncPrint("Done IDT");

	init_graphics();
	load_idt();
	to_userland();
	//video_tests();
	//clear_screen();
	//init_game();
	return getStackBase();
}


int main()
{
	//to_userland();
	return 0;
}
/*
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

void video_tests(){
	draw_pixel(100,100, 255,0,0);
	draw_fill_square(0,0,255,255,255, 10);
	draw_char('>');
	draw_string("TPArqui");
	draw_char(':');
	for(int i = 0; i < 50; i++){
		draw_number(i);
		new_line();
	}
	//move_everything_up3();
	draw_fill_square(300,300, 255,0,255, 100);
	erase_character();
	//Writing test

	for(int i = 0; i < 1000; i++){
		draw_number(i);
	}
	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < number_of_digits(i); j++){
			erase_character();
		}
	}
	draw_string("Erased!");
	shadow_fill_square(300,300, 0xFF, 0x0, 0xFF, 100);
	swap_buffers();

}
*/
