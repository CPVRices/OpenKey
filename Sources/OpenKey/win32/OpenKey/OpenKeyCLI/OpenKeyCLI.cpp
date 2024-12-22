#include <Windows.h>
#include <iostream>
#include <cstdlib>

#define _CRT_SECURE_NO_WARNINGS 1

#define EN 69
#define VN 72
#define EN_TEXT ((getenv("OKC_EN") != NULL) ? getenv("OKC_EN") : "EN")
#define VN_TEXT ((getenv("OKC_VN") != NULL) ? getenv("OKC_VN") : "VN")
#define COMM_ERROR "process communication error"

#define OP_TOGGLE 69420
#define OP_GET 69421
#define OP_CONTROL_PANEL 69422

#define APP_CLASS L"OpenKeyVietnameseInputMethod"

int sig(int signum) {
	HWND previousInstance = FindWindow(APP_CLASS, NULL);
	if (previousInstance) {
		int result = (int)SendMessage(previousInstance, WM_USER + signum, 0, 0);
		return result;
	}
	else {
		printf("OpenKey is not running.");
		exit(1);
	}
}

void print_resp(int resp) {
	switch (resp) {
	case EN:
		printf(EN_TEXT);
		break;
	case VN:
		printf(VN_TEXT);
		break;
	default:
		printf(COMM_ERROR);
		break;
	}
}

void help() {
	printf("use /get, /toggle, /controlpanel\n");
	printf("CLI extension coded by pi.kt\n");
	printf("customize the messages with OKC_EN and OKC_VN environment variables (must not contain %% signs)");
	exit(1);
}

int main(int argc, const char **argv)
{
	if (argc == 1) {
		print_resp(sig(OP_GET));
		return 0;
	}

	if (argc != 2 || strcmp(argv[1], "/help") == 0)
		help();

	if (strcmp(argv[1], "/toggle") == 0) {
		print_resp(sig(OP_TOGGLE));
		return 0;
	}

	if (strcmp(argv[1], "/get") == 0) {
		print_resp(sig(OP_GET));
		return 0;
	}

	if (strcmp(argv[1], "/controlpanel") == 0) {
		sig(OP_CONTROL_PANEL);
		return 0;
	}

	help();
};