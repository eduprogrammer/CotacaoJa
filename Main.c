/*
	Desenvolvido por Eduardo Marques Braga de Faria.
	########## Analista de Dados e Desenvolvedor de Software para Windows, Linux e Android ############
	Recife/PE, Brasil.
	Fone: (81) 98860-0704
	E-mail: edumfariabraga@gmail.com
*/

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <shellapi.h>
#include <ShlObj.h>

#include "resource.h"


#define BUTTON_NEW_ITEM 1
#define BUTTON_START 2
#define RB_MEAN 3
#define RB_MEDIAN 4
#define RB_LITTLE 5
#define BUTTON_FINISH 6

#pragma warning(disable: 4996)

//main window
HWND mainWindow;

//variables - welcome layout
HWND welcomeTitle;
HWND welcomeLabelOne;
HWND welcomeLabelTwo;
HWND welcomeInstruction;
HWND welcomeFoot;

//variables - new job layout
HWND newjobLabelItem;
HWND newjobEditItem;
HWND newjobButtonItem;
HWND newjobLabelData;
HWND newjobEditData;
HWND newjobLabelName;
HWND newjobEditName;
HWND newjobButtonStart;
HWND newjobLabelCV;
HWND newjobEditCV;
HWND newjobTextData;
HWND newjobLabelObject;
HWND newjobEditObject;
HWND newjobLabelFont;
HWND newjobComboBoxFont;
HWND newjobLabelPriceOne;
HWND newjobLabelPriceTwo;
HWND newjobLabelPriceThree;
HWND newjobLabelPriceFour;
HWND newjobLabelPriceFive;
HWND newjobEditPriceOne;
HWND newjobEditPriceTwo;
HWND newjobEditPriceThree;
HWND newjobEditPriceFour;
HWND newjobEditPriceFive;
HWND newjobLabelQtOne;
HWND newjobLabelQtTwo;
HWND newjobLabelQtThree;
HWND newjobLabelQtFour;
HWND newjobLabelQtFive;
HWND newjobEditQtOne;
HWND newjobEditQtTwo;
HWND newjobEditQtThree;
HWND newjobEditQtFour;
HWND newjobEditQtFive;
HWND newjobLabelFinalOne;
HWND newjobLabelFinalTwo;
HWND newjobLabelFinalThree;
HWND newjobLabelFinalFour;
HWND newjobLabelFinalFive;
HWND newjobEditFinalOne;
HWND newjobEditFinalTwo;
HWND newjobEditFinalThree;
HWND newjobEditFinalFour;
HWND newjobEditFinalFive;
HWND newJobLabelMethod;
HWND newJobRbMean;
HWND newJobRbMedian;
HWND newJobRbLittle;
HWND newJobButtonFinish;

//global variables
char* result;
char* saveResult;
char* data;
char* name;
double total = 0;

//function prototypes
LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
void newJobLayout();
void goCotacao();
void newItem();
void endCotacao();
void exportCsv();
void exportTxt();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int iCmdShow)
{
	//declare
	MSG msg;
	char* app_name;
	WNDCLASS wndclass;
	HMENU hMenu;

	//initializes

	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	app_name = "CotacaoJaV2";

	memset(&wndclass, 0, sizeof(WNDCLASS));
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = app_name;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;

	//functions
	if (!RegisterClass(&wndclass))
	{
		return 0;
	}

	mainWindow = CreateWindow(app_name, "Cotação Já 2.0", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(mainWindow, iCmdShow);
	UpdateWindow(mainWindow);

	SetMenu(mainWindow, hMenu);

	//widgets - welcome layout
	welcomeTitle = CreateWindow("static", "Cotação Já - v2.0", WS_CHILD | WS_VISIBLE, 280, 0, 350, 80, mainWindow, NULL, hInstance, NULL);
	welcomeLabelOne = CreateWindow("static", "Dedicado especialmente a todos os compradores públicos", WS_CHILD | WS_VISIBLE, 270, 150, 400, 30, mainWindow, NULL, hInstance, NULL);
	welcomeLabelTwo = CreateWindow("static", "Visite: https://gestgov.discourse.group/c/nelca", WS_CHILD | WS_VISIBLE, 310, 170, 400, 30, mainWindow, NULL, hInstance, NULL);
	welcomeInstruction = CreateWindow("static", "Selecione uma opção no menu acima", WS_CHILD | WS_VISIBLE, 280, 200, 400, 60, mainWindow, NULL, hInstance, NULL);
	welcomeFoot = CreateWindow("static", "Autor: Eduardo Marques || Contato: edumfariabraga@gmail.com || Fone: (81)98860-0704", WS_CHILD | WS_VISIBLE, 200, 420, 800, 30, mainWindow, NULL, hInstance, NULL);

	//widgets - new job layout
	newjobLabelItem = CreateWindow("static", "Item:", WS_CHILD, 700, 30, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditItem = CreateWindow("edit", "1", WS_CHILD | WS_BORDER, 760, 30, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobButtonItem = CreateWindow("button", "Novo Item", WS_CHILD | BS_PUSHBUTTON, 830, 30, 100, 20, mainWindow, (HMENU)1, hInstance, NULL);
	newjobLabelData = CreateWindow("static", "Data:", WS_CHILD, 50, 380, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditData = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 380, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelName = CreateWindow("static", "Nome:", WS_CHILD, 230, 380, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditName = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 300, 380, 200, 20, mainWindow, NULL, hInstance, NULL);
	newjobButtonStart = CreateWindow("button", "Cotar", WS_CHILD | BS_PUSHBUTTON, 510, 380, 60, 20, mainWindow, (HMENU)2, hInstance, NULL);
	newJobButtonFinish = CreateWindow("button", "FINALIZAR COTAÇÃO", WS_CHILD | BS_PUSHBUTTON, 580, 370, 150, 40, mainWindow, (HMENU)6, hInstance, NULL);
	newjobTextData = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE, 50, 270, 790, 100, mainWindow, NULL, hInstance, NULL);
	newjobLabelObject = CreateWindow("static", "Objeto:", WS_CHILD, 50, 80, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditObject = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 80, 400, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelFont = CreateWindow("static", "Fonte de preço:", WS_CHILD, 530, 80, 150, 20, mainWindow, NULL, hInstance, NULL);
	newjobComboBoxFont = CreateWindow("combobox", NULL, WS_CHILD | CBS_DROPDOWNLIST | CBS_HASSTRINGS, 690, 80, 200, 150, mainWindow, NULL, hInstance, NULL);
	newjobLabelPriceOne = CreateWindow("static", "Preço 1:", WS_CHILD, 50, 110, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelPriceTwo = CreateWindow("static", "Preço 2:", WS_CHILD, 50, 140, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelPriceThree = CreateWindow("static", "Preço 3:", WS_CHILD, 50, 170, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelPriceFour = CreateWindow("static", "Preço 4:", WS_CHILD, 50, 200, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelPriceFive = CreateWindow("static", "Preço 5:", WS_CHILD, 50, 230, 60, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditPriceOne = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 110, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditPriceTwo = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 140, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditPriceThree = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 170, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditPriceFour = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 200, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditPriceFive = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 120, 230, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelQtOne = CreateWindow("static", "Quantidade 1:", WS_CHILD, 220, 110, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelQtTwo = CreateWindow("static", "Quantidade 2:", WS_CHILD, 220, 140, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelQtThree = CreateWindow("static", "Quantidade 3:", WS_CHILD, 220, 170, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelQtFour = CreateWindow("static", "Quantidade 4:", WS_CHILD, 220, 200, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelQtFive = CreateWindow("static", "Quantidade 5:", WS_CHILD, 220, 230, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditQtOne = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 330, 110, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditQtTwo = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 330, 140, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditQtThree = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 330, 170, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditQtFour = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 330, 200, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditQtFive = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 330, 230, 90, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelFinalOne = CreateWindow("static", "Valor Total:", WS_CHILD, 430, 110, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelFinalTwo = CreateWindow("static", "Valor Total:", WS_CHILD, 430, 140, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelFinalThree = CreateWindow("static", "Valor Total:", WS_CHILD, 430, 170, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelFinalFour = CreateWindow("static", "Valor Total:", WS_CHILD, 430, 200, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobLabelFinalFive = CreateWindow("static", "Valor Total:", WS_CHILD, 430, 230, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditFinalOne = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 540, 110, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditFinalTwo = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 540, 140, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditFinalThree = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 540, 170, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditFinalFour = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 540, 200, 100, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditFinalFive = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 540, 230, 100, 20, mainWindow, NULL, hInstance, NULL);
	newJobLabelMethod = CreateWindow("static", "Critério:", WS_CHILD, 710, 140, 100, 20, mainWindow, NULL, hInstance, NULL);
	newJobRbMean = CreateWindow("button", "Média", WS_CHILD | BS_AUTORADIOBUTTON, 710, 170, 100, 20, mainWindow, (HMENU)3, hInstance, NULL);
	newJobRbMedian = CreateWindow("button", "Mediana", WS_CHILD | BS_AUTORADIOBUTTON, 710, 200, 100, 20, mainWindow, (HMENU)4, hInstance, NULL);
	newJobRbLittle = CreateWindow("button", "Menor valor", WS_CHILD | BS_AUTORADIOBUTTON, 710, 230, 100, 20, mainWindow, (HMENU)5, hInstance, NULL);
	newjobLabelCV = CreateWindow("static", "Coeficiente de variação:", WS_CHILD, 820, 140, 200, 20, mainWindow, NULL, hInstance, NULL);
	newjobEditCV = CreateWindow("edit", NULL, WS_CHILD | WS_BORDER, 860, 170, 60, 20, mainWindow, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
	
}

//build function prototypes
LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
	//declare
	HFONT hFont;
	LOGFONT logfont;
	HFONT hFontInstruction;
	LOGFONT logfontInstruction;
	HDC hdc;
	HDC hdcCompact;
	HBITMAP hBitmap;
	PAINTSTRUCT ps;
	BITMAP bitmap;

	switch (msg)
	{
	case WM_CREATE:
		result = (char*)malloc(1024 * 100);
		strcpy(result, "[*] Relatório de cotação.\r\n\r\n");
		data = (char*)malloc(50);
		name = (char*)malloc(100);

		//open nelca group link in user default Web Browser
		ShellExecute(NULL, "open", "https://gestgov.discourse.group/c/nelca", NULL, NULL, SW_SHOWDEFAULT);

		break;

	case WM_PAINT:
		
		
		//welcome title font
		ZeroMemory(&logfont, sizeof(LOGFONT));
		logfont.lfCharSet = ANSI_CHARSET;
		logfont.lfHeight = 80;
		logfont.lfItalic = TRUE;
		logfont.lfPitchAndFamily = FF_ROMAN;
		logfont.lfWeight = FW_BOLD;
		logfont.lfWidth = 20;
		hFont = CreateFontIndirect(&logfont);
		SendMessage(welcomeTitle, WM_SETFONT, hFont, TRUE);

		//welcome instruction font
		memset(&logfontInstruction, 0, sizeof(LOGFONT));
		logfontInstruction.lfCharSet = ANSI_CHARSET;
		logfontInstruction.lfHeight = 50;
		logfontInstruction.lfPitchAndFamily = FF_ROMAN;
		logfontInstruction.lfUnderline = TRUE;
		logfontInstruction.lfWeight = 10;
		logfontInstruction.lfWidth = 10;
		hFontInstruction = CreateFontIndirect(&logfontInstruction);
		SendMessage(welcomeInstruction, WM_SETFONT, hFontInstruction, TRUE);

		//welcome bitmap
		ZeroMemory(&bitmap, sizeof(BITMAP));
		ZeroMemory(&ps, sizeof(PAINTSTRUCT));
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
		hdc = BeginPaint(mainWindow, &ps);
		hdcCompact = CreateCompatibleDC(hdc);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		SelectObject(hdcCompact, hBitmap);
		int x = bitmap.bmWidth;
		int y = bitmap.bmHeight;
		StretchBlt(hdc, 850, 300, 100, 100, hdcCompact, 0, 0, x, y, MERGECOPY);
		DeleteDC(hdcCompact);
		DeleteDC(hdc);

		break;

	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return GetStockObject(NULL_BRUSH);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_ARQUIVO_NOVACOTA40001:
		
			//addning combo box items
			SendMessage(newjobComboBoxFont, CB_ADDSTRING, 0, (LPARAM)"ComprasNET");
			SendMessage(newjobComboBoxFont, CB_ADDSTRING, 0, (LPARAM)"Outros Entes Públicos");
			SendMessage(newjobComboBoxFont, CB_ADDSTRING, 0, (LPARAM)"Domínio Amplo / Espec.");
			SendMessage(newjobComboBoxFont, CB_ADDSTRING, 0, (LPARAM)"Fornecedor");
			SendMessage(newjobComboBoxFont, CB_SETCURSEL, 0, 0);

			newJobLayout();
			break;

		case ID_ARQUIVO_EXPORTARPARAEXCEL:
			exportCsv();
			break;

		case ID_ARQUIVO_EXPORTARPARAARQUIVODETEXTO:
			exportTxt();
			break;

		case ID_SOBRE_SOBREOPROGRAMA:
			MessageBox(mainWindow, "Cotação Já é um programa destinado principalmente aos compradores públicos, particularmente os envolvidos nas licitações. Por intermédio desta ferramenta, o gestor público encontra auxílio na cotação de preços, calculando segurança os preços de mercado através de métodologia de cálculo avançada, como o desvio-padrão, o coeficiente de variação, menor preço, média e mediana. Atualmente, o programa encontra-se na versão 2 e melhorias futuras poderão ser disponibilizadas pelo programador responsável. \r\n\r\nCréditos: Eduardo Marques (Analista de Dados e Desenvolvedor de Software\r\nLinguagem de programação: C\r\nLicença: Livre distribuição e utilização\r\nAno: 2020\r\n\r\nE-mail: edumfariabraga@gmail.com\r\nFone: (81)98860-0704 (Recife, Brasil)", "Sobre o programa", MB_ICONINFORMATION);
			break;

		case BUTTON_START:
			goCotacao();
			break;

		case BUTTON_NEW_ITEM:
			newItem();
			break;

		case BUTTON_FINISH:
			endCotacao();
			break;
		}
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void newJobLayout()
{
	//hide main widgets
	ShowWindow(welcomeLabelOne, SW_HIDE);
	ShowWindow(welcomeLabelTwo, SW_HIDE);
	ShowWindow(welcomeInstruction, SW_HIDE);

	//show new widgets
	ShowWindow(newjobLabelItem, SW_SHOW);
	ShowWindow(newjobEditItem, SW_SHOW);
	ShowWindow(newjobButtonItem, SW_SHOW);
	ShowWindow(newjobLabelData, SW_SHOW);
	ShowWindow(newjobEditData, SW_SHOW);
	ShowWindow(newjobLabelName, SW_SHOW);
	ShowWindow(newjobEditName, SW_SHOW);
	ShowWindow(newjobButtonStart, SW_SHOW);
	ShowWindow(newjobLabelCV, SW_SHOW);
	ShowWindow(newjobEditCV, SW_SHOW);
	ShowWindow(newjobTextData, SW_SHOW);
	ShowWindow(newjobLabelObject, SW_SHOW);
	ShowWindow(newjobEditObject, SW_SHOW);
	ShowWindow(newjobLabelFont, SW_SHOW);
	ShowWindow(newjobComboBoxFont, SW_SHOW);
	ShowWindow(newjobLabelPriceOne, SW_SHOW);
	ShowWindow(newjobLabelPriceTwo, SW_SHOW);
	ShowWindow(newjobLabelPriceThree, SW_SHOW);
	ShowWindow(newjobLabelPriceFour, SW_SHOW);
	ShowWindow(newjobLabelPriceFive, SW_SHOW);
	ShowWindow(newjobEditPriceOne, SW_SHOW);
	ShowWindow(newjobEditPriceTwo, SW_SHOW);
	ShowWindow(newjobEditPriceThree, SW_SHOW);
	ShowWindow(newjobEditPriceFour, SW_SHOW);
	ShowWindow(newjobEditPriceFive, SW_SHOW);
	ShowWindow(newjobLabelQtOne, SW_SHOW);
	ShowWindow(newjobLabelQtTwo, SW_SHOW);
	ShowWindow(newjobLabelQtThree, SW_SHOW);
	ShowWindow(newjobLabelQtFour, SW_SHOW);
	ShowWindow(newjobLabelQtFive, SW_SHOW);
	ShowWindow(newjobEditQtOne, SW_SHOW);
	ShowWindow(newjobEditQtTwo, SW_SHOW);
	ShowWindow(newjobEditQtThree, SW_SHOW);
	ShowWindow(newjobEditQtFour, SW_SHOW);
	ShowWindow(newjobEditQtFive, SW_SHOW);
	ShowWindow(newjobLabelFinalOne, SW_SHOW);
	ShowWindow(newjobLabelFinalTwo, SW_SHOW);
	ShowWindow(newjobLabelFinalThree, SW_SHOW);
	ShowWindow(newjobLabelFinalFour, SW_SHOW);
	ShowWindow(newjobLabelFinalFive, SW_SHOW);
	ShowWindow(newjobEditFinalOne, SW_SHOW);
	ShowWindow(newjobEditFinalTwo, SW_SHOW);
	ShowWindow(newjobEditFinalThree, SW_SHOW);
	ShowWindow(newjobEditFinalFour, SW_SHOW);
	ShowWindow(newjobEditFinalFive, SW_SHOW);
	ShowWindow(newJobLabelMethod, SW_SHOW);
	ShowWindow(newJobRbMean, SW_SHOW);
	ShowWindow(newJobRbMedian, SW_SHOW);
	ShowWindow(newJobRbLittle, SW_SHOW);
	ShowWindow(newJobButtonFinish, SW_SHOW);
	
}

void goCotacao()
{
	//declare
	char *object, *font, *item, *method, *cv;
	char *p1, *p2, *p3, *p4, *p5, *q1, *q2, *q3, *q4, *q5, *vt1, *vt2, *vt3, *vt4, *vt5;
	char temp[50] = { 0 };
	char temp_message[200] = { 0 };
	int cb_index, cur_item, num_items;
	double i_p1, i_p2, i_p3, i_p4, i_p5;
	double i_q1, i_q2, i_q3, i_q4, i_q5;
	double i_vt1, i_vt2, i_vt3, i_vt4, i_vt5;
	double mean, std_dv, cv_double, median, little;

	//initializes
	object = (char*)malloc(500);
	font = (char*)malloc(200);
	item = (char*)malloc(50);
	method = (char*)malloc(50);
	cv = (char*)malloc(50);
	p1 = (char*)malloc(50);
	p2 = (char*)malloc(50);
	p3 = (char*)malloc(50);
	p4 = (char*)malloc(50);
	p5 = (char*)malloc(50);
	q1 = (char*)malloc(50);
	q2 = (char*)malloc(50);
	q3 = (char*)malloc(50);
	q4 = (char*)malloc(50);
	q5 = (char*)malloc(50);
	vt1 = (char*)malloc(50);
	vt2 = (char*)malloc(50);
	vt3 = (char*)malloc(50);
	vt4 = (char*)malloc(50);
	vt5 = (char*)malloc(50);
	data = (char*)malloc(50);
	name = (char*)malloc(100);
	

	//get text values
	GetWindowText(newjobEditObject, object, 500);
	cb_index = SendMessage(newjobComboBoxFont, CB_GETCURSEL, 0, 0);
	switch (cb_index)
	{
	case 0:
		font = "Art. 4°, inciso I - IN 5/14 - MP (ComprasNET)";
		break;

	case 1:
		font = "Art. 4°, inciso II - IN 5/14 - MP (Outros Entes Públicos)";
		break;

	case 2:
		font = "Art. 4°, inciso III - IN 5/14 - MP (Domínio Amplo / Mídia Especializada)";
		break;

	case 3:
		font = "Art. 4°, inciso IV - IN 5/14 - MP (Pesquisa junto a Fornecedor)";
		break;
	}

	
	GetWindowText(newjobEditItem, item, 50);
	cur_item = atoi(item);
	GetWindowText(newjobEditPriceOne, p1, 50);
	GetWindowText(newjobEditPriceTwo, p2, 50);
	GetWindowText(newjobEditPriceThree, p3, 50);
	GetWindowText(newjobEditPriceFour, p4, 50);
	GetWindowText(newjobEditPriceFive, p5, 50);
	GetWindowText(newjobEditQtOne, q1, 50);
	GetWindowText(newjobEditQtTwo, q2, 50);
	GetWindowText(newjobEditQtTwo, q3, 50);
	GetWindowText(newjobEditQtTwo, q4, 50);
	GetWindowText(newjobEditQtTwo, q5, 50);
	GetWindowText(newjobEditFinalOne, vt1, 50);
	GetWindowText(newjobEditFinalTwo, vt2, 50);
	GetWindowText(newjobEditFinalThree, vt3, 50);
	GetWindowText(newjobEditFinalFour, vt4, 50);
	GetWindowText(newjobEditFinalFive, vt5, 50);
	GetWindowText(newjobEditData, data, 50);
	GetWindowText(newjobEditName, name, 100);

	//get number ofvalid items
	num_items = 0;
	if (strcmp("", p1) != 0)
		num_items++;
	if (strcmp("", p2) != 0)
		num_items++;
	if (strcmp("", p3) != 0)
		num_items++;
	if (strcmp("", p4) != 0)
		num_items++;
	if (strcmp("", p5) != 0)
		num_items++;
	

	//functions
	if (SendDlgItemMessage(mainWindow, RB_MEAN, BM_GETCHECK, 0, 0) != 0)
	{
		//mean
		method = "Média";
		switch (num_items)
		{
		case 1:
			
			MessageBox(mainWindow, "A utilização de menos de 3 (três) preços na cotação contraria a jurisprudência do TCU. Tal procedimento requer justificativa expressa no referido processo administrativo de aquisição.", "Atenção", MB_OK);
			
			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;

			cv = "0";

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			SetWindowText(newjobEditCV, cv);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			strcat(result, "0\r\n");
			strcat(result, "Coeficiente de Variação: ");
			strcat(result, "0\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += i_vt1;
			
			break;

		case 2:
			
			MessageBox(mainWindow, "A utilização de menos de 3 (três) preços na cotação contraria a jurisprudência do TCU. Tal procedimento requer justificativa expressa no referido processo administrativo de aquisição.", "Atenção", MB_OK);
			
			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			mean = (i_vt1 + i_vt2) / 2;
			
			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2)) / 1);
			cv_double = (std_dv / mean) * 100;

			if (cv_double > 25)
			{
				int res = MessageBox(mainWindow, "O coeficiente de variação é maior do que 25%. Nesse caso, existem potencialmente preços superestimados ou subestimados. Para retificar a distorção, recomanda-se a utilização da média ou mediana.", "Atenção", MB_OK);
			
			}
			else
			{
				//nothing
			}

			
			
			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", mean);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += mean;


			break;

		case 3:
			
			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			mean = (i_vt1 + i_vt2 + i_vt3) / 3;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2)) / 2);
			cv_double = (std_dv / mean) * 100;

			if (cv_double > 25)
			{
				MessageBox(mainWindow, "O coeficiente de variação é maior do que 25%. Nesse caso, existem potencialmente preços superestimados ou subestimados. Para retificar a distorção, recomanda-se a utilização da média ou mediana.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", mean);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += mean;

			break;

		case 4:
			
			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			i_p4 = atof(p4);
			i_q4 = atof(q4);
			i_vt4 = i_p4 * i_q4;
			mean = (i_vt1 + i_vt2 + i_vt3 + i_vt4) / 4;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2) + pow((i_vt4 -mean), 2)) / 3);
			cv_double = (std_dv / mean) * 100;

			if (cv_double > 25)
			{
				MessageBox(mainWindow, "O coeficiente de variação é maior do que 25%. Nesse caso, existem potencialmente preços superestimados ou subestimados. Para retificar a distorção, recomanda-se a utilização da média ou mediana.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", i_vt4);
			SetWindowText(newjobEditFinalFour, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 4: ");
			sprintf(temp, "%f", i_p4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 4: ");
			sprintf(temp, "%f", i_q4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 4): ");
			sprintf(temp, "%f", i_vt4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", mean);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += mean;

			break;

		case 5:
			
			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			i_p4 = atof(p4);
			i_q4 = atof(q4);
			i_vt4 = i_p4 * i_q4;
			i_p5 = atof(p5);
			i_q5 = atof(q5);
			i_vt5 = i_p5 * i_q5;
			mean = (i_vt1 + i_vt2 + i_vt3 + i_vt4 + i_vt5) / 5;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2) + pow((i_vt4 - mean), 2) + pow((i_vt5 - mean), 2)) / 4);
			cv_double = (std_dv / mean) * 100;

			if (cv_double > 25)
			{
				MessageBox(mainWindow, "O coeficiente de variação é maior do que 25%. Nesse caso, existem potencialmente preços superestimados ou subestimados. Para retificar a distorção, recomanda-se a utilização da média ou mediana.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", i_vt4);
			SetWindowText(newjobEditFinalFour, temp);
			sprintf(temp, "%f", i_vt5);
			SetWindowText(newjobEditFinalFive, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 4: ");
			sprintf(temp, "%f", i_p4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 4: ");
			sprintf(temp, "%f", i_q4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 4): ");
			sprintf(temp, "%f", i_vt4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 5: ");
			sprintf(temp, "%f", i_p5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 5: ");
			sprintf(temp, "%f", i_q5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 5): ");
			sprintf(temp, "%f", i_vt5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", mean);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += mean;

			break;

		default:
			MessageBox(mainWindow, "Não há preços válidos para calcular a média. Prencha ao menos uma linha naos campos preço e quantidade.", "Aviso", MB_ICONEXCLAMATION);
			break;
		}
		
	}
	else if (SendDlgItemMessage(mainWindow, RB_MEDIAN, BM_GETCHECK, 0, 0) != 0)
	{
		//median
		method = "Mediana";
		switch (num_items)
		{
		case 1:

			MessageBox(mainWindow, "A utilização de menos de 3 (três) preços na cotação contraria a jurisprudência do TCU. Tal procedimento requer justificativa expressa no referido processo administrativo de aquisição.", "Atenção", MB_OK);

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;

			cv = "0";

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			SetWindowText(newjobEditCV, cv);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			strcat(result, "0\r\n");
			strcat(result, "Coeficiente de Variação: ");
			strcat(result, "0\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += i_vt1;

			break;

		case 2:

			MessageBox(mainWindow, "A utilização de menos de 3 (três) preços na cotação contraria a jurisprudência do TCU. Tal procedimento requer justificativa expressa no referido processo administrativo de aquisição.", "Atenção", MB_OK);
			
			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			mean = (i_vt1 + i_vt2) / 2;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2)) / 1);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar a mediana, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}


			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", mean);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += mean;

			break;

		case 3:

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			mean = (i_vt1 + i_vt2 + i_vt3) / 3;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2)) / 2);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar a mediana, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

	

			//first value
			double cur_values3[3] = { i_vt1, i_vt2, i_vt3 };
			double arrayv3[3] = {0};
			
			if (cur_values3[0] <= cur_values3[1] && cur_values3[0] <= cur_values3[2])
			{
				arrayv3[0] = cur_values3[0];
			}

			if (cur_values3[1] <= cur_values3[0] && cur_values3[1] <= cur_values3[2])
			{
				arrayv3[0] = cur_values3[1];
			}

			if (cur_values3[2] <= cur_values3[0] && cur_values3[2] <= cur_values3[1])
			{
				arrayv3[0] = cur_values3[2];
			}

			//second value
			if (cur_values3[0] <= cur_values3[1] && cur_values3[0] >= cur_values3[2])
			{
				arrayv3[1] = cur_values3[0];
			}

			if (cur_values3[0] <= cur_values3[2] && cur_values3[0] >= cur_values3[1])
			{
				arrayv3[1] = cur_values3[0];
			}

			if (cur_values3[1] <= cur_values3[0] && cur_values3[1] >= cur_values3[2])
			{
				arrayv3[1] = cur_values3[1];
			}

			if (cur_values3[1] <= cur_values3[2] && cur_values3[1] >= cur_values3[0])
			{
				arrayv3[1] = cur_values3[1];
			}

			if (cur_values3[2] <= cur_values3[0] && cur_values3[2] >= cur_values3[1])
			{
				arrayv3[1] = cur_values3[2];
			}

			if (cur_values3[2] <= cur_values3[1] && cur_values3[2] >= cur_values3[0])
			{
				arrayv3[1] = cur_values3[2];
			}

			//third value
			if (cur_values3[0] >= cur_values3[1] && cur_values3[0] >= cur_values3[2])
			{
				arrayv3[2] = cur_values3[0];
			}

			if (cur_values3[1] >= cur_values3[0] && cur_values3[1] >= cur_values3[2])
			{
				arrayv3[2] = cur_values3[1];
			}

			if (cur_values3[2] >= cur_values3[0] && cur_values3[2] >= cur_values3[1])
			{
				arrayv3[2] = cur_values3[2];
			}

			median = arrayv3[1];
			

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", median);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += median;

			break;

		case 4:

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			i_p4 = atof(p4);
			i_q4 = atof(q4);
			i_vt4 = i_p4 * i_q4;
			mean = (i_vt1 + i_vt2 + i_vt3 + i_vt4) / 4;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2) + pow((i_vt4 - mean), 2)) / 3);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar a mediana, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

	

			//first value
			double cur_values[4] = { i_vt1, i_vt2, i_vt3, i_vt4};
			double arrayv[4] = { 0 };

			if (cur_values[0] <= cur_values[1] && cur_values[0] <= cur_values[2] && cur_values[0] <= cur_values[3])
			{
				arrayv[0] = cur_values[0];
			}

			if (cur_values[1] <= cur_values[0] && cur_values[1] <= cur_values[2] && cur_values[1] <= cur_values[3] )
			{
				arrayv[0] = cur_values[1];
			}

			if (cur_values[2] <= cur_values[0] && cur_values[2] <= cur_values[1] && cur_values[2] <= cur_values[3] )
			{
				arrayv[0] = cur_values[2];
			}

			if (cur_values[3] <= cur_values[0] && cur_values[3] <= cur_values[1] && cur_values[3] <= cur_values[2])
			{
				arrayv[0] = cur_values[3];
			}

			//second value
			if (cur_values[0] <= cur_values[1] && cur_values[0] <= cur_values[2] && cur_values[0] >= cur_values[3] )
			{
				arrayv[1] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[1] && cur_values[0] <= cur_values[3] && cur_values[0] >= cur_values[2])
			{
				arrayv[1] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[2] && cur_values[0] <= cur_values[1] && cur_values[0] >= cur_values[3])
			{
				arrayv[1] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[2] && cur_values[0] <= cur_values[3] && cur_values[0] >= cur_values[1])
			{
				arrayv[1] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[3] && cur_values[0] <= cur_values[1] && cur_values[0] >= cur_values[2])
			{
				arrayv[1] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[3] && cur_values[0] <= cur_values[2] && cur_values[0] >= cur_values[1])
			{
				arrayv[1] = cur_values[0];
			}

			if (cur_values[1] <= cur_values[0] && cur_values[1] <= cur_values[2] && cur_values[1] >= cur_values[3])
			{
				arrayv[1] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[0] && cur_values[1] <= cur_values[3] && cur_values[1] >= cur_values[2])
			{
				arrayv[1] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[2] && cur_values[1] <= cur_values[0] && cur_values[1] >= cur_values[3])
			{
				arrayv[1] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[2] && cur_values[1] <= cur_values[3] && cur_values[1] >= cur_values[0])
			{
				arrayv[1] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[3] && cur_values[1] <= cur_values[0] && cur_values[1] >= cur_values[2])
			{
				arrayv[1] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[3] && cur_values[1] <= cur_values[2] && cur_values[1] >= cur_values[0])
			{
				arrayv[1] = cur_values[1];
			}

			if (cur_values[2] <= cur_values[0] && cur_values[2] <= cur_values[1] && cur_values[2] >= cur_values[3])
			{
				arrayv[1] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[0] && cur_values[2] <= cur_values[3] && cur_values[2] >= cur_values[1])
			{
				arrayv[1] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[1] && cur_values[2] <= cur_values[0] && cur_values[2] >= cur_values[3])
			{
				arrayv[1] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[1] && cur_values[2] <= cur_values[3] && cur_values[2] >= cur_values[0])
			{
				arrayv[1] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[3] && cur_values[2] <= cur_values[0] && cur_values[2] >= cur_values[1])
			{
				arrayv[1] = cur_values[2];
			}

			if (cur_values[2] <= cur_values[3] && cur_values[2] <= cur_values[1] && cur_values[2] >= cur_values[0])
			{
				arrayv[1] = cur_values[2];
			}


			if (cur_values[3] <= cur_values[0] && cur_values[3] <= cur_values[1] && cur_values[3] >= cur_values[2])
			{
				arrayv[1] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[0] && cur_values[3] <= cur_values[2] && cur_values[3] >= cur_values[1])
			{
				arrayv[1] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[1] && cur_values[3] <= cur_values[0] && cur_values[3] >= cur_values[2])
			{
				arrayv[1] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[1] && cur_values[3] <= cur_values[2] && cur_values[3] >= cur_values[0])
			{
				arrayv[1] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[2] && cur_values[3] <= cur_values[0] && cur_values[3] >= cur_values[1])
			{
				arrayv[1] = cur_values[3];
			}

			if (cur_values[3] <= cur_values[2] && cur_values[3] <= cur_values[1] && cur_values[3] >= cur_values[0])
			{
				arrayv[1] = cur_values[3];
			}

			//third value

			if (cur_values[0] <= cur_values[1] && cur_values[0] >= cur_values[2] && cur_values[0] >= cur_values[3])
			{
				arrayv[2] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[1] && cur_values[0] >= cur_values[3] && cur_values[0] >= cur_values[2])
			{
				arrayv[2] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[2] && cur_values[0] >= cur_values[1] && cur_values[0] >= cur_values[3])
			{
				arrayv[2] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[2] && cur_values[0] >= cur_values[3] && cur_values[0] >= cur_values[1])
			{
				arrayv[2] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[3] && cur_values[0] >= cur_values[1] && cur_values[0] >= cur_values[2])
			{
				arrayv[2] = cur_values[0];
			}

			if (cur_values[0] <= cur_values[3] && cur_values[0] >= cur_values[2] && cur_values[0] >= cur_values[1])
			{
				arrayv[2] = cur_values[0];
			}

			if (cur_values[1] <= cur_values[0] && cur_values[1] >= cur_values[2] && cur_values[1] >= cur_values[3])
			{
				arrayv[2] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[0] && cur_values[1] >= cur_values[3] && cur_values[1] >= cur_values[2])
			{
				arrayv[2] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[2] && cur_values[1] >= cur_values[0] && cur_values[1] >= cur_values[3])
			{
				arrayv[2] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[2] && cur_values[1] >= cur_values[3] && cur_values[1] >= cur_values[0])
			{
				arrayv[2] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[3] && cur_values[1] >= cur_values[0] && cur_values[1] >= cur_values[2])
			{
				arrayv[2] = cur_values[1];
			}

			if (cur_values[1] <= cur_values[3] && cur_values[1] >= cur_values[2] && cur_values[1] >= cur_values[0])
			{
				arrayv[2] = cur_values[1];
			}

			if (cur_values[2] <= cur_values[0] && cur_values[2] >= cur_values[1] && cur_values[2] >= cur_values[3])
			{
				arrayv[2] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[0] && cur_values[2] >= cur_values[3] && cur_values[2] >= cur_values[1])
			{
				arrayv[2] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[1] && cur_values[2] >= cur_values[0] && cur_values[2] >= cur_values[3])
			{
				arrayv[2] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[1] && cur_values[2] >= cur_values[3] && cur_values[2] >= cur_values[0])
			{
				arrayv[2] = cur_values[2];
			}
			if (cur_values[2] <= cur_values[3] && cur_values[2] >= cur_values[0] && cur_values[2] >= cur_values[1])
			{
				arrayv[2] = cur_values[2];
			}

			if (cur_values[2] <= cur_values[3] && cur_values[2] >= cur_values[1] && cur_values[2] >= cur_values[0])
			{
				arrayv[2] = cur_values[2];
			}


			if (cur_values[3] <= cur_values[0] && cur_values[3] >= cur_values[1] && cur_values[3] >= cur_values[2])
			{
				arrayv[2] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[0] && cur_values[3] >= cur_values[2] && cur_values[3] >= cur_values[1])
			{
				arrayv[2] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[1] && cur_values[3] >= cur_values[0] && cur_values[3] >= cur_values[2])
			{
				arrayv[2] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[1] && cur_values[3] >= cur_values[2] && cur_values[3] >= cur_values[0])
			{
				arrayv[2] = cur_values[3];
			}
			if (cur_values[3] <= cur_values[2] && cur_values[3] >= cur_values[0] && cur_values[3] >= cur_values[1])
			{
				arrayv[2] = cur_values[3];
			}

			if (cur_values[3] <= cur_values[2] && cur_values[3] >= cur_values[1] && cur_values[3] >= cur_values[0])
			{
				arrayv[2] = cur_values[3];
			}

			//fourth value

			if (cur_values[0] >= cur_values[1] && cur_values[0] >= cur_values[2] && cur_values[0] >= cur_values[3])
			{
				arrayv[3] = cur_values[0];
			}

			if (cur_values[1] >= cur_values[0] && cur_values[1] >= cur_values[2] && cur_values[1] >= cur_values[3])
			{
				arrayv[3] = cur_values[1];
			}

			if (cur_values[2] >= cur_values[0] && cur_values[2] >= cur_values[1] && cur_values[2] >= cur_values[3])
			{
				arrayv[3] = cur_values[2];
			}

			if (cur_values[3] >= cur_values[0] && cur_values[3] >= cur_values[1] && cur_values[3] >= cur_values[2])
			{
				arrayv[3] = cur_values[3];
			}

			median = ((arrayv[1] + arrayv[2]) / 2);

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", i_vt4);
			SetWindowText(newjobEditFinalFour, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 4: ");
			sprintf(temp, "%f", i_p4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 4: ");
			sprintf(temp, "%f", i_q4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 4): ");
			sprintf(temp, "%f", i_vt4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de Mercado: ");
			sprintf(temp, "%f", median);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += median;

			break;

		case 5:

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			i_p4 = atof(p4);
			i_q4 = atof(q4);
			i_vt4 = i_p4 * i_q4;
			i_p5 = atof(p5);
			i_q5 = atof(q5);
			i_vt5 = i_p5 * i_q5;
			mean = (i_vt1 + i_vt2 + i_vt3 + i_vt4 + i_vt5) / 5;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2) + pow((i_vt4 - mean), 2) + pow((i_vt5 -mean), 2)) / 4);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar a mediana, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			
			double cur_values5[5] = { i_vt1, i_vt2, i_vt3, i_vt4, i_vt5};
			double arrayv5[5] = { 0 };

			//first value
			if (cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[0];
			}

			if (cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[1];
			}

			if (cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[2];
			}

			if (cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[3];
			}

			if (cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[0] = cur_values5[4];
			}

			//second value
			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[0];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[1];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[2];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[3];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[1] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[1] = cur_values5[4];
			}


			//third value

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[4] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[0];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[4] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[1];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[4] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[2];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[4] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[3];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[3] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[2] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[2] = cur_values5[4];
			}

			//fourth value

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[4] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[1] && cur_values5[0] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[0] >= cur_values5[4] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[2] && cur_values5[0] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[0];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[4] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[0] && cur_values5[1] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[1] >= cur_values5[4] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[2] && cur_values5[1] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[1];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[4] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[0] && cur_values5[2] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[2] >= cur_values5[4] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[1] && cur_values5[2] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[2];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[4] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[0] && cur_values5[3] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[3] >= cur_values5[4] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[1] && cur_values5[3] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[3];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[3] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[2] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[2])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[0] && cur_values5[4] <= cur_values5[1])
			{
				arrayv5[3] = cur_values5[4];
			}

			if (cur_values5[4] >= cur_values5[3] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[1] && cur_values5[4] <= cur_values5[0])
			{
				arrayv5[3] = cur_values5[4];
			}

			//fifth value

			if (cur_values5[0] >= cur_values5[1] && cur_values5[0] >= cur_values5[2] && cur_values5[0] >= cur_values5[3] && cur_values5[0] >= cur_values5[4])
			{
				arrayv5[4] = cur_values5[0];
			}

			if (cur_values5[1] >= cur_values5[0] && cur_values5[1] >= cur_values5[2] && cur_values5[1] >= cur_values5[3] && cur_values5[1] >= cur_values5[4])
			{
				arrayv5[4] = cur_values5[1];
			}

			if (cur_values5[2] >= cur_values5[0] && cur_values5[2] >= cur_values5[1] && cur_values5[2] >= cur_values5[3] && cur_values5[2] >= cur_values5[4])
			{
				arrayv5[4] = cur_values5[2];
			}

			if (cur_values5[3] >= cur_values5[0] && cur_values5[3] >= cur_values5[1] && cur_values5[3] >= cur_values5[2] && cur_values5[3] >= cur_values5[4])
			{
				arrayv5[4] = cur_values5[3];
			}

			if (cur_values5[4] >= cur_values5[0] && cur_values5[4] >= cur_values5[1] && cur_values5[4] >= cur_values5[2] && cur_values5[4] >= cur_values5[3])
			{
				arrayv5[4] = cur_values5[4];
			}
			

			
		

			
			median = arrayv5[2];

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", i_vt4);
			SetWindowText(newjobEditFinalFour, temp);
			sprintf(temp, "%f", i_vt5);
			SetWindowText(newjobEditFinalFive, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 4: ");
			sprintf(temp, "%f", i_p4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 4: ");
			sprintf(temp, "%f", i_q4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 4): ");
			sprintf(temp, "%f", i_vt4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 5: ");
			sprintf(temp, "%f", i_p5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 5: ");
			sprintf(temp, "%f", i_q5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 5): ");
			sprintf(temp, "%f", i_vt5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de Mercado: ");
			sprintf(temp, "%f", median);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += median;

			

			break;
		}
		
	}
	else if (SendDlgItemMessage(mainWindow, RB_LITTLE, BM_GETCHECK, 0, 0) != 0)
	{
		//little
		method = "Menor Valor";
		switch (num_items)
		{
		case 1:

			MessageBox(mainWindow, "A utilização de menos de 3 (três) preços na cotação contraria a jurisprudência do TCU. Tal procedimento requer justificativa expressa no referido processo administrativo de aquisição.", "Atenção", MB_OK);

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;

			cv = "0";

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			SetWindowText(newjobEditCV, cv);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			strcat(result, "0\r\n");
			strcat(result, "Coeficiente de Variação: ");
			strcat(result, "0\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += i_vt1;

			break;

		case 2:

			MessageBox(mainWindow, "A utilização de menos de 3 (três) preços na cotação contraria a jurisprudência do TCU. Tal procedimento requer justificativa expressa no referido processo administrativo de aquisição.", "Atenção", MB_OK);

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			
			if (i_vt1 <= i_vt2)
			{
				mean = i_vt1;
			}

			if (i_vt1 >= i_vt2)
			{
				mean = i_vt2;
			}
			
			

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2)) / 1);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar o menor valor, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", mean);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += mean;

			break;

		case 3:

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			mean = (i_vt1 + i_vt2 + i_vt3) / 3;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2)) / 2);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar o menor valor, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			//first value
			double cur_values3[3] = { i_vt1, i_vt2, i_vt3 };
			double arrayv3[3] = { 0 };

			if (cur_values3[0] <= cur_values3[1] && cur_values3[0] <= cur_values3[2])
			{
				arrayv3[0] = cur_values3[0];
			}

			if (cur_values3[1] <= cur_values3[0] && cur_values3[1] <= cur_values3[2])
			{
				arrayv3[0] = cur_values3[1];
			}

			if (cur_values3[2] <= cur_values3[0] && cur_values3[2] <= cur_values3[1])
			{
				arrayv3[0] = cur_values3[2];
			}


			median = arrayv3[0];


			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de mercado: ");
			sprintf(temp, "%f", median);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += median;

			break;

		case 4:

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			i_p4 = atof(p4);
			i_q4 = atof(q4);
			i_vt4 = i_p4 * i_q4;
			mean = (i_vt1 + i_vt2 + i_vt3 + i_vt4) / 4;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2) + pow((i_vt4 - mean), 2)) / 3);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar o menor valor, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}

			//first value
			double cur_values[4] = { i_vt1, i_vt2, i_vt3, i_vt4 };
			double arrayv[4] = { 0 };

			if (cur_values[0] <= cur_values[1] && cur_values[0] <= cur_values[2] && cur_values[0] <= cur_values[3])
			{
				arrayv[0] = cur_values[0];
			}

			if (cur_values[1] <= cur_values[0] && cur_values[1] <= cur_values[2] && cur_values[1] <= cur_values[3])
			{
				arrayv[0] = cur_values[1];
			}

			if (cur_values[2] <= cur_values[0] && cur_values[2] <= cur_values[1] && cur_values[2] <= cur_values[3])
			{
				arrayv[0] = cur_values[2];
			}

			if (cur_values[3] <= cur_values[0] && cur_values[3] <= cur_values[1] && cur_values[3] <= cur_values[2])
			{
				arrayv[0] = cur_values[3];
			}

			
			median = arrayv[0];

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", i_vt4);
			SetWindowText(newjobEditFinalFour, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 4: ");
			sprintf(temp, "%f", i_p4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 4: ");
			sprintf(temp, "%f", i_q4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 4): ");
			sprintf(temp, "%f", i_vt4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de Mercado: ");
			sprintf(temp, "%f", median);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += median;

			break;

		case 5:

			i_p1 = atof(p1);
			i_q1 = atof(q1);
			i_vt1 = i_p1 * i_q1;
			i_p2 = atof(p2);
			i_q2 = atof(q2);
			i_vt2 = i_p2 * i_q2;
			i_p3 = atof(p3);
			i_q3 = atof(q3);
			i_vt3 = i_p3 * i_q3;
			i_p4 = atof(p4);
			i_q4 = atof(q4);
			i_vt4 = i_p4 * i_q4;
			i_p5 = atof(p5);
			i_q5 = atof(q5);
			i_vt5 = i_p5 * i_q5;
			mean = (i_vt1 + i_vt2 + i_vt3 + i_vt4 + i_vt5) / 5;

			std_dv = sqrt((pow((i_vt1 - mean), 2) + pow((i_vt2 - mean), 2) + pow((i_vt3 - mean), 2) + pow((i_vt4 - mean), 2) + pow((i_vt5 - mean), 2)) / 4);
			cv_double = (std_dv / mean) * 100;

			if (cv_double <= 25)
			{
				MessageBox(mainWindow, "Não há necessidade de utilizar o menor valor, pois o coeficiente de variação é menor ou igual a 25%. Nesse caso, trata-se de uma amostra homogênea e a preterição do critério da média pode causar a distorção do valor de mercado.", "Atenção", MB_OK);
			}
			else
			{
				//nothing
			}


			double cur_values5[5] = { i_vt1, i_vt2, i_vt3, i_vt4, i_vt5 };
			double arrayv5[5] = { 0 };

			//first value
			if (cur_values5[0] <= cur_values5[1] && cur_values5[0] <= cur_values5[2] && cur_values5[0] <= cur_values5[3] && cur_values5[0] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[0];
			}

			if (cur_values5[1] <= cur_values5[0] && cur_values5[1] <= cur_values5[2] && cur_values5[1] <= cur_values5[3] && cur_values5[1] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[1];
			}

			if (cur_values5[2] <= cur_values5[0] && cur_values5[2] <= cur_values5[1] && cur_values5[2] <= cur_values5[3] && cur_values5[2] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[2];
			}

			if (cur_values5[3] <= cur_values5[0] && cur_values5[3] <= cur_values5[1] && cur_values5[3] <= cur_values5[2] && cur_values5[3] <= cur_values5[4])
			{
				arrayv5[0] = cur_values5[3];
			}

			if (cur_values5[4] <= cur_values5[0] && cur_values5[4] <= cur_values5[1] && cur_values5[4] <= cur_values5[2] && cur_values5[4] <= cur_values5[3])
			{
				arrayv5[0] = cur_values5[4];
			}

			median = arrayv5[0];

			sprintf(temp, "%f", i_vt1);
			SetWindowText(newjobEditFinalOne, temp);
			sprintf(temp, "%f", i_vt2);
			SetWindowText(newjobEditFinalTwo, temp);
			sprintf(temp, "%f", i_vt3);
			SetWindowText(newjobEditFinalThree, temp);
			sprintf(temp, "%f", i_vt4);
			SetWindowText(newjobEditFinalFour, temp);
			sprintf(temp, "%f", i_vt5);
			SetWindowText(newjobEditFinalFive, temp);
			sprintf(temp, "%f", cv_double);
			SetWindowText(newjobEditCV, temp);

			strcat(result, "N° do item: ");
			sprintf(temp, "%d", cur_item);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Objeto: ");
			strcat(result, object);
			strcat(result, "\r\n");
			strcat(result, "Fonte de preço: ");
			strcat(result, font);
			strcat(result, "\r\n");
			strcat(result, "Preço 1: ");
			sprintf(temp, "%f", i_p1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 1: ");
			sprintf(temp, "%f", i_q1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 1): ");
			sprintf(temp, "%f", i_vt1);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 2: ");
			sprintf(temp, "%f", i_p2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 2: ");
			sprintf(temp, "%f", i_q2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 2): ");
			sprintf(temp, "%f", i_vt2);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 3: ");
			sprintf(temp, "%f", i_p3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 3: ");
			sprintf(temp, "%f", i_q3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 3): ");
			sprintf(temp, "%f", i_vt3);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 4: ");
			sprintf(temp, "%f", i_p4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 4: ");
			sprintf(temp, "%f", i_q4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 4): ");
			sprintf(temp, "%f", i_vt4);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Preço 5: ");
			sprintf(temp, "%f", i_p5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Quantidade 5: ");
			sprintf(temp, "%f", i_q5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor Total (Item 5): ");
			sprintf(temp, "%f", i_vt5);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Valor de Mercado: ");
			sprintf(temp, "%f", median);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Critério utilizado: ");
			strcat(result, method);
			strcat(result, "\r\n");
			strcat(result, "Desvio Padrão Amostral: ");
			sprintf(temp, "%f", std_dv);
			strcat(result, temp);
			strcat(result, "\r\n");
			strcat(result, "Coeficiente de Variação: ");
			sprintf(temp, "%f", cv_double);
			strcat(result, temp);
			strcat(result, "\r\n\r\n");
			SetWindowText(newjobTextData, result);

			strcpy(temp_message, "Item ");
			sprintf(temp, "%d", cur_item);
			strcat(temp_message, temp);
			strcat(temp_message, " adicionado com sucesso.\r\n");
			MessageBox(mainWindow, temp_message, "Novo cadastro", MB_OK);

			total += median;

			break;
		}

		
	}
	else
	{
		MessageBox(mainWindow, "Selecione ao menos um critério para aferição do valor de mercado (média, mediana ou menor valor.)", "Aviso", MB_ICONEXCLAMATION);
	}

}

void newItem()
{
	//declare
	char* get_item;
	int temp_item;
	char temp[100] = { 0 };

	//initializes
	get_item = (char*)malloc(50);
	GetWindowText(newjobEditItem, get_item, 50);
	temp_item = atoi(get_item);
	temp_item++;
	sprintf(temp, "%d", temp_item);
	SetWindowText(newjobEditItem, temp);

	//functions
	SetWindowText(newjobEditObject, "");
	SetWindowText(newjobEditPriceOne, "");
	SetWindowText(newjobEditPriceTwo, "");
	SetWindowText(newjobEditPriceThree, "");
	SetWindowText(newjobEditPriceFour, "");
	SetWindowText(newjobEditPriceFive, "");
	SetWindowText(newjobEditQtOne, "");
	SetWindowText(newjobEditQtTwo, "");
	SetWindowText(newjobEditQtThree, "");
	SetWindowText(newjobEditQtFour, "");
	SetWindowText(newjobEditQtFive, "");
	SetWindowText(newjobEditFinalOne, "");
	SetWindowText(newjobEditFinalTwo, "");
	SetWindowText(newjobEditFinalThree, "");
	SetWindowText(newjobEditFinalFour, "");
	SetWindowText(newjobEditFinalFive, "");
	SetWindowText(newjobEditCV, "");
}

void endCotacao()
{
	//declare
	char* total_items = (char*)malloc(100);
	char temp[20] = { 0 };
	GetWindowText(newjobEditItem, total_items, 100);

	strcat(result, "Total de itens pesquisados: ");
	strcat(result, total_items);
	strcat(result, "\r\n");
	strcat(result, "Valor Global dos Itens: ");
	sprintf(temp, "%f", total);
	strcat(result, temp);
	strcat(result, "\r\n");
	strcat(result, "Data da cotação: ");
	strcat(result, data);
	strcat(result, "\r\n");
	strcat(result, "Responsável pela cotação: ");
	strcat(result, name);
	strcat(result, "\r\n");
	SetWindowText(newjobTextData, result);
	MessageBox(mainWindow, "Cotação encerrada com sucesso. Visualize o relatório completo no campo de texto do programa ou salve-o no formato desejado, escolhendo uma das opções do menu.", "Sucesso", MB_ICONINFORMATION);
	
	//functions
	saveResult = result;
	//free(result);
	//free(data);
	//free(name);
	total = 0;
	result = (char*)malloc(1024 * 100);
	data = (char*)malloc(50);
	name = (char*)malloc(100);
	
}

void exportCsv()
{
	//declare
	OPENFILENAME ofn;
	FILE* file;
	char path[252] = { 0 };


	//initializes
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.hwndOwner = mainWindow;
	ofn.lpstrFile = path;
	ofn.lpstrFileTitle = "Cotação Já v2.0";
	ofn.lpstrFilter = "Arquivo do Excel (.csv)\0*.csv\0";
	ofn.lpstrInitialDir = NULL;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = sizeof(path);
	
	//functions
	if (GetSaveFileName(&ofn) == TRUE)
	{
		strcat(path, ".csv");
		file = fopen(path, "w");
		if (!file)
		{
			MessageBox(mainWindow, "Falha ao salvar arquivo.", "Erro", MB_ICONERROR);
		}
		else
		{
			fwrite(saveResult, 102400, 1, file);
			fclose(file);
		}
		
	}
}

void exportTxt()
{
	//declare
	OPENFILENAME ofn;
	FILE* file;
	char path[252] = { 0 };


	//initializes
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.hwndOwner = mainWindow;
	ofn.lpstrFile = path;
	ofn.lpstrFileTitle = "Cotação Já v2.0";
	ofn.lpstrFilter = "Arquivo de Texto (.txt)\0*.txt\0";
	ofn.lpstrInitialDir = NULL;
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = sizeof(path);

	//functions
	if (GetSaveFileName(&ofn) == TRUE)
	{
		strcat(path, ".txt");
		file = fopen(path, "w");
		if (!file)
		{
			MessageBox(mainWindow, "Falha ao salvar arquivo.", "Erro", MB_ICONERROR);
		}
		else
		{
			fwrite(saveResult, 102400, 1, file);
			fclose(file);
		}

	}
}






