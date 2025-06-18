#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <spectrum.h>
#include <arch/zx/betadisk.h>

// zcc +zx -vn -lndos specfetch.c -create-app -ospecfetch.bin

const char* get_model_name(int model) {
	static const char models[7][22] = {
		"unknown",
		"48K",
		"128K or +2",
		"+2A or Pentagon",
		"+3",
		"+2A/+3 with bus fixed",
		"TS2068"
	};
	if (model < 0 || model > 6) return models[0];
	return models[model];
}

const char* getdisk() {
	const char *disks[] = { "None", "Disciple", "+3DOS", "TRDOS" };
	uint8_t i = 0;
	if(zx_disciple()) i = 1;
	if(zx_plus3fdc()) i = 2;
	if(trdos_installed()) i = 3;
	return disks[i];
}

void main() {
	zx_border(2);
	textbackground(0);
	zx_cls();

	int x,y;
	x = 14;
	y = 0;
	printf("\x01\x20");
	for(y=1;y<21;y++) {
		gotoxy(x-4,y);
		textbackground(RED);
		printf(" ");
		textbackground(YELLOW);
		printf(" ");
		textbackground(GREEN);
		printf(" ");
		textbackground(CYAN);
		printf(" ");
		if(y % 2 == 0) x--;
	}
	printf("\x01\x40");
	textbackground(BLACK);

	gotoxy(32, 2);
	textcolor(MAGENTA);
	printf("specfetch");
	textcolor(WHITE);
	gotoxy(32,3);
	printf("--------------");
	textcolor(MAGENTA);
	gotoxy(32,5);
	printf("Model:");
	gotoxy(32,6);
	printf("Mode:");
	gotoxy(32,7);
	printf("BASIC:");
	gotoxy(32,8);
	printf("Vars:");
	gotoxy(32,9);
	printf("Joystick:");
	gotoxy(32,10);
	printf("Soundchip:");
	gotoxy(32,11);
	printf("Disk:");
	textcolor(WHITE);
	gotoxy(44,5);
	printf("%s", get_model_name(zx_model()));
	gotoxy(44,6);
	printf("%s", zx_128mode() ? "128K" : "48K");
	gotoxy(44,7);
	printf("%d bytes", zx_basic_length());
	gotoxy(44,8);
	printf("%d bytes", zx_var_length());
	gotoxy(44,9);
	printf("%s", zx_kempston() ? "Kempston" : "None");
	gotoxy(44,10);
	printf("%s", zx_soundchip() ? "AY-3-8912" : "Beepy");
	gotoxy(44,11);
	printf("%s", getdisk());
	if(zx_extsys()) {
		gotoxy(44,13);
		textcolor(RED);
		printf("BASIC relocated");
	}

	printf("\x01\x20");
	uint8_t coloursordered[8] = { BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE };
	gotoxy(16,15);

	for(x=0;x<8;x++) {
		if(x==4) gotoxy(16,16);
		textbackground(coloursordered[x]);
		printf("  ");
	}
	getch();
}
