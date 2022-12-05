#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <locale.h>
#include <Windows.h>
#include <CommDlg.h>
#include <Commctrl.h>
#include "resource.h"
using namespace std;

HWND ghDlg = 0;
HWND h_edit;
HWND h_boton;
HWND h_radio;
HWND h_listbox;
HWND h_combo;
HWND h_PicControl;
HWND calendario;
SYSTEMTIME st;
HINSTANCE regis;
HMENU h_menu;
HBITMAP bmp;
HINSTANCE INSTANCIA;
OPENFILENAME ofn;

char zFile[MAX_PATH];
char FileTitle[MAX_PATH];

struct nodo {
	char com[16]={""};
	char nom[16]={""};
	char contra[11]={""};
	char tipo[16]={""};
	char nomcom[51]={""};
	char ali[11]={""};
	char foton [MAX_PATH]={""};
	int revision=0;
	nodo* siguiente = nullptr;
	nodo* anterior = nullptr;
};
nodo* auxiliar = nullptr;
nodo* primero = nullptr;
nodo* auxiliar_C = nullptr;
nodo* primero_C = nullptr;
nodo* temporal = nullptr;
nodo* temporal_C = nullptr;
struct nodo_Cliente {
	char nombre[51]={""};
	char alias[16]={""};
	char tel[11]={""};
	char email[26]={""};
	char comercio[16]={""};
	nodo_Cliente* sig = nullptr;
	nodo_Cliente* ant = nullptr;
};
nodo_Cliente* auxiliar_CL = nullptr;
nodo_Cliente* primero_CL = nullptr;
nodo_Cliente* temporal_CL = nullptr;
struct nodo_promo {
	char name[51]={""};
	float promo = 0;
	float porcentaje = 0;
	char estatus[10]={""};
	char lacomer [16]={""};
	nodo_promo* sig = nullptr;
	nodo_promo* ant = nullptr;
};
nodo_promo* auxiliar_prom = nullptr;
nodo_promo* primero_prom = nullptr;
nodo_promo* temporal_prom = nullptr;
struct nodo_productos {
	nodo_productos* sigui = nullptr;
	nodo_productos* ante = nullptr;
	char nombr[26]={""};
	float precio = 0;
};
nodo_productos* prim = nullptr;
nodo_productos* aux = nullptr;
nodo_productos* tem = nullptr;
struct nodo_lista {
	char client[51]={""};
	char pro [26]={""};
	char fechas[52]={""};
	char comercios[51]={""};
	int cantidadpro = 0;
	float total = 0;
	int desc = 0;
	float titi = 0;
	nodo_lista* sigui = nullptr;
	nodo_lista* ante = nullptr;
};
nodo_lista* prime = nullptr;
nodo_lista* auxi = nullptr;
nodo_lista* temp = nullptr;
int deno = 0;
char dato1[15];
char dato2[15];
char dato3[10];
char param_name[50] = "";
char nuevo [52] = "";
//ofstream Archivo;
char comercionom [15] = "";
char Unom[51] = "";
char adm[15] = "Administrador";
char caj[15] = "Cajero";
char act[10] = "Activo";
char inact[10] = "Inactivo";
int con_adm, con_caj, con_cli, con_promact, con_promin, con_pro, con_cons ,cur,total_cons= 0;
char textolist[50] = {};
char prodd[50] = {};
char textodefault[MAX_PATH] = {};
int k,x,w,h,acumulador,i = 0;
float pase=0;
float preciooo = 0;
int numer0 = -1;
int numer3 = 2;
int numer5 = 4;
int numer10 = 11;
int numer15 = 16;
int numer25 = 26;
int numer50 = 51;
char vali[6][52] = {};
float numval1,numval2, numval3, numval4, numval5 = 0;
int mcon = 0;
char buffer[MAX_PATH];
int tamaño = 0;
BOOL numOK;
fstream Archivo;

void buscarA();
void buscarC();
void guardar_A();
void guardar_C();
void guardar_CL();
void guardar_PRO();
void guardar_PROM();
void guardar_lis();
void leer_a();
void leer_c();
void leer_cl();
void leer_pro();
void leer_prom();
void leer_list();
void valalfa(char algo[MAX_PATH],int n1,int n2);
void valletra(char algom[MAX_PATH],int nu1,int nu2);
void valnum(char alll[MAX_PATH],int num1, int num2);
void valcontra(char co[MAX_PATH], int nume1, int nume2);
void valemail(char e[MAX_PATH], int numer1, int numer2);

char INFO_U[6][52] = {};
char INFO_CL[5][52] = {};
char INFO_PROM[2][52] = {};
int INP1, INP2 = 0;



BOOL CALLBACK AltaU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ActU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK BorrarU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListaU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ContraseU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AltaCL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK LIS_CL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK BorrarCL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ActCL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AltaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ActPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK BorrarPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AltaProd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AltaConsu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ListaConsu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogoModal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	ghDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)WindowProc);
	ShowWindow(ghDlg, nCmdShow);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

BOOL CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_INITDIALOG:
		h_boton = GetDlgItem(hwnd, IDC_BUTTON1);//iniciar sesion
		h_boton = GetDlgItem(hwnd, IDC_BUTTON2);//Registrarse
		h_boton = GetDlgItem(hwnd, IDC_BUTTON3);//Salir
		h_edit = GetDlgItem(hwnd, IDC_EDIT1);//comercio
		h_edit = GetDlgItem(hwnd, IDC_EDIT2);//Nombre de usuario
		h_edit = GetDlgItem(hwnd, IDC_EDIT3);//contraseña
		setlocale(LC_CTYPE, "Spanish");

		leer_a();
		leer_c();
		leer_cl();
		leer_pro();
		leer_prom();
		leer_list();

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
			GetDlgItemText(hwnd, IDC_EDIT1, dato1, 15);
			GetDlgItemText(hwnd, IDC_EDIT2, dato2, 15);
			GetDlgItemText(hwnd, IDC_EDIT3, dato3, 10);
			if (primero == nullptr && primero_C == nullptr) {
				MessageBox(hwnd, "No hay Usuarios Registrados Aun", "MENSAJE", MB_ICONERROR);
			}
			
			else if (primero != nullptr || primero_C != nullptr) {
				buscarA();
				buscarC();
			}
			else {
				MessageBox(hwnd, "Usuario no Encontrado", "MENSAJE", MB_ICONERROR);
			}
			break;

		case IDC_BUTTON2:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG3), 0, (DLGPROC)AltaU);
			break;
			
		case IDC_BUTTON3:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}
BOOL CALLBACK DialogoModal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_menu = LoadMenu(INSTANCIA, MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hwnd, h_menu);
		h_boton = GetDlgItem(hwnd, actualizarinfo);
		h_edit = GetDlgItem(hwnd, cantclientes);
		h_edit = GetDlgItem(hwnd, cantpromoa);
		h_edit = GetDlgItem(hwnd, cantpromoi);
		h_edit = GetDlgItem(hwnd, cantconsu);
		h_edit = GetDlgItem(hwnd, cantconcli);
		h_edit = GetDlgItem(hwnd, NOM1);
		h_PicControl = GetDlgItem(hwnd, FOTON1);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM1, Unom);
		SetDlgItemInt(hwnd, cantpromoi, (UINT)con_promin, FALSE);
		SetDlgItemInt(hwnd, cantconsu,(UINT)con_cons , FALSE);
		SetDlgItemInt(hwnd, cantconcli, (UINT)total_cons, FALSE);
		SetDlgItemInt(hwnd, cantclientes, (UINT)con_cli, FALSE);
		SetDlgItemInt(hwnd, cantpromoa, (UINT)con_promact, FALSE);

		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case actualizarinfo:
			SetDlgItemInt(hwnd, cantpromoi, (UINT)con_promin, FALSE);
			SetDlgItemInt(hwnd, cantconsu, (UINT)con_cons, FALSE);
			SetDlgItemInt(hwnd, cantconcli, (UINT)total_cons, FALSE);
			SetDlgItemInt(hwnd, cantclientes, (UINT)con_cli, FALSE);
			SetDlgItemInt(hwnd, cantpromoa, (UINT)con_promact, FALSE);
			break;
		case ID_USUARIOS_ALTADEUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG3), 0, (DLGPROC)AltaU);
			break;

		case ID_USUARIOS_ACTUALIZARUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), 0, (DLGPROC)ActU);
			break;

		case ID_USUARIOS_BAJADEUSUARIO:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG9), 0, (DLGPROC)BorrarU);
			break;

		case ID_USUARIOS_RESTABLECERCONTRASE40004:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG6), 0, (DLGPROC)ContraseU);
			break;

		case  ID_USUARIOS_LISTADODEUSUARIOS:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG5), 0, (DLGPROC)ListaU);
			break;

		case ID_CLIENTES_ALTADECLIENTES:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG7), 0, (DLGPROC)AltaCL);
			break;

		case ID_CLIENTES_ACTUALIZARCLIENTE:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG11), 0, (DLGPROC)ActCL);
			break;

		case ID_CLIENTES_BAJADECLIENTE:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG10), 0, (DLGPROC)BorrarCL);
			break;

		case ID_CLIENTES_LISTADODECLIENTES:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG8), 0, (DLGPROC)LIS_CL);
			break;

		case ID_PROMOCIONES_ALTADEPROMOCION:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG12), 0, (DLGPROC)AltaPromo);
			break;

		case ID_PROMOCIONES_BAJADEPROMOCION:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG15), 0, (DLGPROC)BorrarPromo);
			break;

		case ID_PROMOCIONES_LISTADODEPROMOCIONES:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG13), 0, (DLGPROC)ListPromo);
			break;

		case ID_CONSUMO_ALTADEPRODUCTOS:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG16), 0, (DLGPROC)AltaProd);
			break;

		case ID_CONSUMO_ALTADECONSUMOS:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG17), 0, (DLGPROC)AltaConsu);
			break;

		case ID_CONSUMO_LISTADODECONSUMOS:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG18), 0, (DLGPROC)ListaConsu);
			break;
		case ID_SALIR_SALIR:
			guardar_A();
			guardar_C();
			guardar_CL();
			guardar_PRO();
			guardar_PROM();
			guardar_lis();
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		break;
		}
			break;

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK AltaU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, Nombre_U);
		h_edit = GetDlgItem(hwnd, ComercioU);
		h_edit = GetDlgItem(hwnd, ContraU);
		h_radio = GetDlgItem(hwnd, IDC_RADIO1);//ADMIN
		h_radio = GetDlgItem(hwnd, IDC_RADIO2);
		h_boton = GetDlgItem(hwnd, Can);
		h_boton = GetDlgItem(hwnd, regisU);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_RADIO1:
			deno = 1;
			break;
		case IDC_RADIO2:
			deno = 2;
			break;
		case regisU:
			pase = 0;
			GetDlgItemText(hwnd, ComercioU, vali[0], 16);
			GetDlgItemText(hwnd, Nombre_U, vali[1], 16);
			GetDlgItemText(hwnd, ContraU, vali[2], 11);
			valalfa(vali[0], numer5, numer15);
			valletra(vali[1], numer0, numer15);
			valcontra(vali[2], numer3, numer10);
			if (pase == 3) {
				if (deno == 1) {
					if (primero == nullptr) {
						primero = new nodo;
						GetDlgItemText(hwnd, ComercioU, primero->com, 16);
						GetDlgItemText(hwnd, Nombre_U, primero->nom, 16);
						GetDlgItemText(hwnd, ContraU, primero->contra, 11);
						strcpy_s(primero->tipo, 15, "Administrador");
						primero->revision = 0;
						primero->siguiente = nullptr;
						primero->anterior = nullptr;
						auxiliar = primero;
					}
					else {
						auxiliar = primero;
						while (auxiliar->siguiente != nullptr) {
							auxiliar = auxiliar->siguiente;
						}
						auxiliar->siguiente = new nodo;
						auxiliar->siguiente->siguiente = nullptr;
						auxiliar->siguiente->anterior = auxiliar;
						auxiliar = auxiliar->siguiente;
						GetDlgItemText(hwnd, ComercioU, auxiliar->com, 16);
						GetDlgItemText(hwnd, Nombre_U, auxiliar->nom, 16);
						GetDlgItemText(hwnd, ContraU, auxiliar->contra, 11);
						strcpy_s(auxiliar->tipo, 15, "Administrador");
						auxiliar->revision = 0;
					}
					con_adm++;
					guardar_A();
				}

				if (deno == 2) {
					if (primero_C == nullptr) {
						primero_C = new nodo;
						GetDlgItemText(hwnd, ComercioU, primero_C->com, 16);
						GetDlgItemText(hwnd, Nombre_U, primero_C->nom, 16);
						GetDlgItemText(hwnd, ContraU, primero_C->contra, 11);
						strcpy_s(primero_C->tipo, 15, "Cajero");
						primero_C->revision = 0;
						primero_C->siguiente = nullptr;
						primero_C->anterior = nullptr;
						auxiliar_C = primero_C;
					}
					else {
						auxiliar_C = primero_C;
						while (auxiliar_C->siguiente != nullptr) {
							auxiliar_C = auxiliar_C->siguiente;
						}
						auxiliar_C->siguiente = new nodo;
						auxiliar_C->siguiente->siguiente = nullptr;
						auxiliar_C->siguiente->anterior = auxiliar_C;
						auxiliar_C = auxiliar_C->siguiente;
						GetDlgItemText(hwnd, ComercioU, auxiliar_C->com, 16);
						GetDlgItemText(hwnd, Nombre_U, auxiliar_C->nom, 16);
						GetDlgItemText(hwnd, ContraU, auxiliar_C->contra, 11);
						strcpy_s(auxiliar_C->tipo, 15, "Cajero");
						auxiliar_C->revision = 0;
					}
					con_caj++;
					guardar_C();
				}

				MessageBox(hwnd, "El registro se ha realizado", "MENSAJE", MB_ICONINFORMATION);
				deno = 0;
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Vuelve a ingresar tus datos", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemText(hwnd, ComercioU, "");
				SetDlgItemText(hwnd, Nombre_U, "");
				SetDlgItemText(hwnd, ContraU, "");
			}
			break;


		case Can:
			EndDialog(hwnd, wParam);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}	
	return FALSE;
}
BOOL CALLBACK ActU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_PicControl = GetDlgItem(hwnd, Picture1);
		h_edit = GetDlgItem(hwnd, actU_n);
		h_edit = GetDlgItem(hwnd, actU_A);
		h_boton = GetDlgItem(hwnd, CargaI);
		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case CargaI:
			OPENFILENAME ofn;
			ZeroMemory(zFile, sizeof(zFile));
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "All\0*.*\0Bitmaps\0*.bmp\0";;
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\ 0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.lpstrFileTitle = FileTitle;
			ofn.nMaxFileTitle = sizeof(FileTitle);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 1;

			if (GetOpenFileName(&ofn)) {
				h_PicControl = GetDlgItem(hwnd, Picture1);
				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 180, 130, LR_LOADFROMFILE);
				SendDlgItemMessage(hwnd, Picture1 , STM_SETIMAGE ,IMAGE_BITMAP,(LPARAM)bmp);
			}
			else {
				MessageBox(hwnd, "No selecciono ningun archivo", "AVISO", MB_OK);
			}


			break;
		case IDOK:
			pase = 0;
			GetDlgItemText(hwnd, actU_n, vali[0], 51);
			GetDlgItemText(hwnd, actU_A, vali[1], 11);
			valletra(vali[0], numer5, numer50);
			valalfa(vali[1], numer3, numer10);
			if (pase == 2) {
				if (auxiliar == nullptr) {
					if (strcmp(auxiliar_C->tipo, caj) == 0) {
						strcpy_s(auxiliar_C->foton, zFile);
						GetDlgItemText(hwnd, actU_n, auxiliar_C->nomcom, 51);
						GetDlgItemText(hwnd, actU_A, auxiliar_C->ali, 11);
						auxiliar_C->revision = 1;
					}
				}
				else {
					if (strcmp(auxiliar->tipo, adm) == 0) {
						strcpy_s(auxiliar->foton, zFile);
						GetDlgItemText(hwnd, actU_n, auxiliar->nomcom, 51);
						GetDlgItemText(hwnd, actU_A, auxiliar->ali, 11);
						auxiliar->revision = 1;
					}
				}
				MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Vuelve a ingresar tus datos", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemText(hwnd, actU_n, "");
				SetDlgItemText(hwnd, actU_A, "");
			}
			
			break;

		case IDCANCEL:
			EndDialog(hwnd, wParam);
			break;

			}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, wParam);
			return true;
		}
return FALSE;
} 
BOOL CALLBACK AltaCL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, NOMBRECL);
		h_edit = GetDlgItem(hwnd, ALIASCL);
		h_edit = GetDlgItem(hwnd, TELCL);
		h_edit = GetDlgItem(hwnd, EMAILCL);
		h_edit = GetDlgItem(hwnd, COMCL);
		h_edit = GetDlgItem(hwnd, FECHACL);
		h_boton = GetDlgItem(hwnd, GUARDARCL);
		h_boton = GetDlgItem(hwnd, REGRESARCL);
		SetDlgItemText(hwnd, COMCL, comercionom);
		SetDlgItemText(hwnd, FECHACL, __DATE__);
		h_edit = GetDlgItem(hwnd, NOM4);
		h_PicControl = GetDlgItem(hwnd, FOTON4);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM4, Unom);
		
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case GUARDARCL:
			pase = 0;
			GetDlgItemText(hwnd, NOMBRECL, vali[0], 51);
			GetDlgItemText(hwnd, ALIASCL, vali[1], 16);
			GetDlgItemText(hwnd, TELCL, vali[2], 11);
			GetDlgItemText(hwnd, EMAILCL, vali[3], 26);
			valletra(vali[0], numer5, numer50);
			valletra(vali[1], numer5, numer15);
			valnum(vali[2], numer0, numer10);
			valemail(vali[3], numer5, numer25);

			if (pase == 4) {
				if (primero_CL == nullptr) {
					primero_CL = new nodo_Cliente;
					strcpy_s(primero_CL->comercio, 16, comercionom);
					GetDlgItemText(hwnd, NOMBRECL, primero_CL->nombre, 51);
					GetDlgItemText(hwnd, ALIASCL, primero_CL->alias, 16);
					GetDlgItemText(hwnd, TELCL, primero_CL->tel, 11);
					GetDlgItemText(hwnd, EMAILCL, primero_CL->email, 26);
					primero_CL->sig = nullptr;
					primero_CL->ant = nullptr;
					auxiliar_CL = primero_CL;
				}
				else {
					auxiliar_CL = primero_CL;
					while (auxiliar_CL->sig != nullptr) {
						auxiliar_CL = auxiliar_CL->sig;
					}
					auxiliar_CL->sig = new nodo_Cliente;
					auxiliar_CL->sig->sig = nullptr;
					auxiliar_CL->sig->ant = auxiliar_CL;
					auxiliar_CL = auxiliar_CL->sig;
					strcpy_s(auxiliar_CL->comercio, 16, comercionom);
					GetDlgItemText(hwnd, NOMBRECL, auxiliar_CL->nombre, 51);
					GetDlgItemText(hwnd, ALIASCL, auxiliar_CL->alias, 16);
					GetDlgItemText(hwnd, TELCL, auxiliar_CL->tel, 11);
					GetDlgItemText(hwnd, EMAILCL, auxiliar_CL->email, 26);
				}
				MessageBox(hwnd, "El registro se ha realizado", "MENSAJE", MB_ICONINFORMATION);
				con_cli++;
				guardar_CL();
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Vuelve a ingresar tus datos", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemText(hwnd, NOMBRECL, "");
				SetDlgItemText(hwnd, ALIASCL, "");
				SetDlgItemText(hwnd, TELCL, "");
				SetDlgItemText(hwnd, EMAILCL, "");
			}
			
			break;
		case REGRESARCL:
			EndDialog(hwnd, wParam);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK AltaPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, promonom);
		h_edit = GetDlgItem(hwnd, promomon);
		h_edit = GetDlgItem(hwnd, promodesc);
		h_edit = GetDlgItem(hwnd, FECHAPROMO);
		h_boton = GetDlgItem(hwnd, GUARDARPROMO);
		h_boton = GetDlgItem(hwnd, REGRESARPROMO);
		h_radio = GetDlgItem(hwnd, IDC_RADIO7A);
		h_radio = GetDlgItem(hwnd, IDC_RADIO8I);
		h_edit = GetDlgItem(hwnd, NOM9);
		h_PicControl = GetDlgItem(hwnd, FOTON9);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON9, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM9, Unom);
		SetDlgItemText(hwnd, FECHAPROMO, __DATE__);
		break;
	case WM_COMMAND:

	switch (LOWORD(wParam))
		{
		case IDC_RADIO7A:
			deno = 1;
			break;
		case IDC_RADIO8I:
			deno = 2;
			break;
		case GUARDARPROMO:
			pase = 0;
			GetDlgItemText(hwnd, promonom, vali[0], 51);
			valletra(vali[0], numer5, numer50);
			numval1 = GetDlgItemInt(hwnd, promomon, &numOK, FALSE);
			if (numval1 >= 100) {
				pase = pase + 1;
			}
			else {
				MessageBox(hwnd, "El monto debe ser mayor a $100", "INFORMATION", MB_OK || MB_ICONINFORMATION);
			}
			numval2 = GetDlgItemInt(hwnd, promodesc, &numOK, FALSE);
			if (numval2 > 0 || numval2 < 100) {
				pase = pase + 1;
			}
			else {
				MessageBox(hwnd, "El descuento debe ser mayor a 0 y menor a 100", "INFORMATION", MB_OK || MB_ICONINFORMATION);
			}

			if (pase == 3) {
				if (primero_prom == nullptr) {
					primero_prom = new nodo_promo;
					GetDlgItemText(hwnd, promonom, primero_prom->name, 51);
					primero_prom->promo = GetDlgItemInt(hwnd, promomon, &numOK, FALSE);
					primero_prom->porcentaje = GetDlgItemInt(hwnd, promodesc, &numOK, FALSE);
					if (deno == 1) {
						strcpy_s(primero_prom->estatus, 10, act);
						con_promact++;
					}
					if (deno == 2) {
						strcpy_s(primero_prom->estatus, 10, inact);
						con_promin++;
					}
					strcpy_s(primero_prom->lacomer, comercionom);
					primero_prom->sig = nullptr;
					primero_prom->ant = nullptr;
					auxiliar_prom = primero_prom;
				}
				else {
					auxiliar_prom = primero_prom;
					while (auxiliar_prom->sig != nullptr) {
						auxiliar_prom = auxiliar_prom->sig;
					}
					auxiliar_prom->sig = new nodo_promo;
					auxiliar_prom->sig->sig = nullptr;
					auxiliar_prom->sig->ant = auxiliar_prom;
					auxiliar_prom = auxiliar_prom->sig;
					GetDlgItemText(hwnd, promonom, auxiliar_prom->name, 51);
					auxiliar_prom->promo = GetDlgItemInt(hwnd, promomon, &numOK, FALSE);
					auxiliar_prom->porcentaje = GetDlgItemInt(hwnd, promodesc, &numOK, FALSE);
					if (deno == 1) {
						strcpy_s(auxiliar_prom->estatus, 10, act);
						con_promact++;
					}
					if (deno == 2) {
						strcpy_s(auxiliar_prom->estatus, 10, inact);
						con_promin++;
					}
					strcpy_s(auxiliar_prom->lacomer, comercionom);
				}
				MessageBox(hwnd, "La promocion se ha registrado", "MENSAJE", MB_ICONINFORMATION);
				guardar_PROM();
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Vuelve a ingresar tus datos", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemText(hwnd, promonom, "");
				SetDlgItemInt(hwnd, promomon, 0, FALSE);
				SetDlgItemInt(hwnd, promodesc, 0, FALSE);
			}

			break;

		case REGRESARPROMO:
			EndDialog(hwnd, wParam);
			break;
		}
		break;
			
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;	
		}

	return FALSE;
}
BOOL CALLBACK AltaProd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, NOMPROD);
		h_edit = GetDlgItem(hwnd, PRECIOPRO);
		h_boton = GetDlgItem(hwnd, GUARDARPROD);
		h_boton = GetDlgItem(hwnd, CANCELARPROD);
		h_edit = GetDlgItem(hwnd, NOM13);
		h_PicControl = GetDlgItem(hwnd, FOTON13);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON13, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM13, Unom);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case GUARDARPROD:
			pase = 0;
			GetDlgItemText(hwnd, NOMPROD, vali[0], 26);
			numval1 = GetDlgItemInt(hwnd, PRECIOPRO, &numOK, FALSE);
			valalfa(vali[0], numer3, numer25);
			if (numval1 > 0) {
				pase = pase + 1;
			}
			else {
				MessageBox(hwnd, "El precio debe ser mayor a $0", "INFORMATION", MB_OK || MB_ICONINFORMATION);
			}

			if (pase == 2) {
				if (prim == nullptr) {
					prim = new nodo_productos;
					GetDlgItemText(hwnd, NOMPROD, prim->nombr, 26);
					prim->precio = GetDlgItemInt(hwnd, PRECIOPRO, &numOK, FALSE);
					prim->sigui = nullptr;
					prim->ante = nullptr;
					aux = prim;
				}
				else {
					aux = prim;
					while (aux->sigui != nullptr) {
						aux = aux->sigui;
					}
					aux->sigui = new nodo_productos;
					aux->sigui->sigui = nullptr;
					aux->sigui->ante = aux;
					aux = aux->sigui;
					GetDlgItemText(hwnd, NOMPROD, aux->nombr, 25);
					aux->precio = GetDlgItemInt(hwnd, PRECIOPRO, &numOK, FALSE);
				}
				MessageBox(hwnd, "El producto se ha registrado", "MENSAJE", MB_ICONINFORMATION);
				con_pro++;
				guardar_PRO();
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Vuelve a ingresar tus datos", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemText(hwnd, NOMPROD, "");
				SetDlgItemInt(hwnd, PRECIOPRO, 0, FALSE);
			}

			break;

		case CANCELARPROD:
			EndDialog(hwnd, wParam);
			break;

		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK AltaConsu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_combo = GetDlgItem(hwnd, IDC_COMBO1);
		h_combo = GetDlgItem(hwnd, IDC_COMBO2);
		h_edit = GetDlgItem(hwnd, montocons);
		h_edit = GetDlgItem(hwnd, fechacons);
		h_edit = GetDlgItem(hwnd, subtotalcons);
		h_edit = GetDlgItem(hwnd, desccons);
		h_edit = GetDlgItem(hwnd, totalcons);
		h_boton = GetDlgItem(hwnd, guardarcons);
		h_boton = GetDlgItem(hwnd, regresarconsu);
		h_edit = GetDlgItem(hwnd, NOM14);
		calendario = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
		h_PicControl = GetDlgItem(hwnd, FOTON14);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON14, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM14, Unom);
		SetDlgItemText(hwnd, fechacons, __DATE__);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case guardarcons:
			SendDlgItemMessage(hwnd, IDC_DATETIMEPICKER1, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
			_itoa_s(st.wYear, buffer, 10);
			strcpy_s(textodefault, buffer);
			strcat_s(textodefault, "/");
			_itoa_s(st.wMonth, buffer, 10);
			strcat_s(textodefault, buffer);
			strcat_s(textodefault, "/");
			_itoa_s(st.wDay, buffer, 10);
			strcat_s(textodefault, buffer);

			pase = 0;
			mcon = GetDlgItemInt(hwnd, montocons, &numOK, FALSE);
			if (mcon > 0) {
				pase = pase + 1;
			}
			else {
				MessageBox(hwnd, "El consumo debe ser mayor a 0 unidades", "INFORMATION", MB_OK || MB_ICONINFORMATION);
			}

			if (pase == 1) {
				if (prime == nullptr) {
					prime = new nodo_lista;

					strcpy_s(prime->comercios, comercionom);
					strcpy_s(prime->fechas, textodefault);
					strcpy_s(prime->client, textolist);
					strcpy_s(prime->pro, prodd);
					prime->cantidadpro = GetDlgItemInt(hwnd, montocons, &numOK, FALSE);
					prime->total = preciooo * prime->cantidadpro;
					SetDlgItemInt(hwnd, subtotalcons, (UINT)prime->total, FALSE);
					auxiliar_prom = primero_prom;
					while (auxiliar_prom != nullptr) {
						if (prime->total >= auxiliar_prom->promo) {
							if (strcmp(auxiliar_prom->estatus,act) == 0) {
								prime->titi = prime->total - (prime->total * (auxiliar_prom->porcentaje / 100));
								prime->desc = auxiliar_prom->porcentaje;
							}
							if (strcmp(auxiliar_prom->estatus, inact) == 0) {
								prime->titi = prime->total;
								prime->desc = 0;
							}
						}
						auxiliar_prom = auxiliar_prom->sig;
					}
					SetDlgItemInt(hwnd, desccons, (UINT)prime->desc, FALSE);
					SetDlgItemInt(hwnd, totalcons, (UINT)prime->titi, FALSE);
					strcpy_s(prime->fechas, __DATE__);
					total_cons = total_cons + prime->titi;
					prime->sigui = nullptr;
					prime->ante = nullptr;
					auxi = prime;
				}
				else {
					auxi = prime;
					while (auxi->sigui != nullptr) {
						auxi = auxi->sigui;
					}
					auxi->sigui = new nodo_lista;
					auxi->sigui->sigui = nullptr;
					auxi->sigui->ante = auxi;
					auxi = auxi->sigui;

					strcpy_s(auxi->comercios, comercionom);
					strcpy_s(auxi->fechas, textodefault);
					strcpy_s(auxi->client, textolist);
					strcpy_s(auxi->pro, prodd);
					auxi->cantidadpro = GetDlgItemInt(hwnd, montocons, &numOK, FALSE);
					auxi->total = preciooo * auxi->cantidadpro;
					SetDlgItemInt(hwnd, subtotalcons, (UINT)auxi->total, FALSE);
					auxiliar_prom = primero_prom;
					while (auxiliar_prom != nullptr) {
						if (auxi->total >= auxiliar_prom->promo) {
							if (strcmp(auxiliar_prom->estatus, act) == 0) {
								auxi->titi = auxi->total - (auxi->total * (auxiliar_prom->porcentaje / 100));
								auxi->desc = auxiliar_prom->porcentaje;
							}
							if (strcmp(auxiliar_prom->estatus, inact) == 0) {
								auxi->titi = auxi->total;
								auxi->desc = 0;
							}
						}
						auxiliar_prom = auxiliar_prom->sig;
					}
					SetDlgItemInt(hwnd, desccons, (UINT)auxi->desc, FALSE);
					SetDlgItemInt(hwnd, totalcons, (UINT)auxi->titi, FALSE);
					strcpy_s(auxi->fechas, __DATE__);
					total_cons = total_cons + auxi->titi;
				}
				con_cons++;
				guardar_lis();
				MessageBox(hwnd, "El consumo se ha registrado correctamente", "MENSAJE", MB_ICONINFORMATION);
				EndDialog(hwnd, wParam);
			}
			else {
				MessageBox(hwnd, "Vuelve a ingresar tus datos", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemInt(hwnd, montocons, 0, FALSE);
			}

			break;
		case IDC_COMBO1:
			if (primero_CL) {
				temporal_CL = primero_CL;
				while (temporal_CL) {
					SendDlgItemMessage(hwnd, IDC_COMBO1, CB_INSERTSTRING, 0, (LPARAM)temporal_CL->nombre);
					temporal_CL = temporal_CL->sig;
				}
			}
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_COMBO1, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_COMBO1, CB_GETLBTEXT, cur, (LPARAM)textolist);
				temporal_CL = primero_CL;
				while (strcmp(textolist, temporal_CL->nombre)!=0) {
					temporal_CL = temporal_CL->sig;
				}
			}
			break;

		case IDC_COMBO2:
			if (prim) {
				tem = prim;
				while (tem) {
					SendDlgItemMessage(hwnd, IDC_COMBO2, CB_INSERTSTRING, 0, (LPARAM)tem->nombr);
					tem = tem->sigui;
				}
			}
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_COMBO2, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_COMBO2, CB_GETLBTEXT, cur, (LPARAM)prodd);
				tem=prim;
				while (strcmp(prodd, tem->nombr) != 0 ) {
					tem = tem->sigui;
				}
				preciooo = tem->precio;
			}

			break;
		case regresarconsu:
			EndDialog(hwnd, wParam);

			break;

		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}

BOOL CALLBACK ListaU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;

	case WM_INITDIALOG:
		h_listbox=GetDlgItem(hwnd,IDC_LIST1);
		h_edit = GetDlgItem(hwnd, comlis);
		h_edit = GetDlgItem(hwnd, nomulis);
		h_edit = GetDlgItem(hwnd, nomcomlis);
		h_edit = GetDlgItem(hwnd, conlis);
		h_edit = GetDlgItem(hwnd, alilis);
		h_radio = GetDlgItem(hwnd, IDC_RADIO3);
		h_radio = GetDlgItem(hwnd, IDC_RADIO4);
		h_boton= GetDlgItem(hwnd,ACTUALIZAR);
		h_boton = GetDlgItem(hwnd, REGRESAR);
		h_boton = GetDlgItem(hwnd, ELIMINAR);
		h_boton = GetDlgItem(hwnd, ACTLISTA3);
		h_edit = GetDlgItem(hwnd, NOM2);
		h_PicControl = GetDlgItem(hwnd, FOTON2);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM2, Unom);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ACTLISTA3:
			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			if (deno == 1) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
				if (primero) {
					temporal = primero;
					while (temporal) {
						if (strcmp(temporal->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)temporal->nom);
						}
						temporal = temporal->siguiente;

					}
				}
			}


			if (deno == 2) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
				if (primero_C) {
					temporal_C = primero_C;
					while (temporal_C) {
						if (strcmp(temporal_C->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)temporal_C->nom);
						}
						temporal_C = temporal_C->siguiente;
					}
				}
			}


			break;

		case IDC_RADIO3:
			deno = 0;
			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			if (primero) {
					temporal = primero;
					while (temporal) {
						if (strcmp(temporal->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)temporal->nom);
						}
						temporal = temporal->siguiente;
					}
				}
			guardar_A();
			deno = 1;
			break;

		case IDC_RADIO4:
			deno = 0;
			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);
			if (primero_C) {
					temporal_C = primero_C;
					while (temporal_C) {
						if (strcmp(temporal_C->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)temporal_C->nom);
						}
						temporal_C = temporal_C->siguiente;
					}
				}
			guardar_C();
			deno = 2;
			break;

		case ACTUALIZAR:
			deno = 0;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)ActU);
			break;
		case ELIMINAR:
			deno = 0;
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG9), hwnd, (DLGPROC)BorrarU);
			break;
		case REGRESAR:
			deno = 0;
			EndDialog(hwnd, wParam);
			break;
		case IDC_LIST1: {
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, cur, (LPARAM)textolist);
				if (deno == 1) {
					if (primero) {
						temporal = primero;
						while (temporal) {
							if (strcmp(temporal->nom, textolist) == 0) {
								SetDlgItemText(hwnd, comlis, temporal->com);
								SetDlgItemText(hwnd, nomulis, temporal->nom);
								SetDlgItemText(hwnd, conlis, temporal->contra);
								if (temporal->revision == 1) {
									SetDlgItemText(hwnd, nomcomlis, temporal->nomcom);
									SetDlgItemText(hwnd, alilis, temporal->ali);
									strcpy_s(INFO_U[3], temporal->nomcom);
									strcpy_s(INFO_U[4], temporal->ali);
								}
								else {
									SetDlgItemText(hwnd, nomcomlis, "No hay datos");
									SetDlgItemText(hwnd, alilis, "No hay datos");
									strcpy_s(INFO_U[3], "");
									strcpy_s(INFO_U[4], "");
								}
								strcpy_s(INFO_U[0],temporal->com);
								strcpy_s(INFO_U[1], temporal->nom);
								strcpy_s(INFO_U[2], temporal->contra);
								strcpy_s(INFO_U[5], temporal->tipo);
								temporal = temporal->siguiente;
							}
							else {
								temporal = temporal->siguiente;
							}
						}
					}
				}

				if (deno == 2) {
					if (primero_C) {
						temporal_C = primero_C;
						while (temporal_C) {
							if (strcmp(temporal_C->nom, textolist) == 0) {
								SetDlgItemText(hwnd, comlis, temporal_C->com);
								SetDlgItemText(hwnd, nomulis, temporal_C->nom);
								SetDlgItemText(hwnd, conlis, temporal_C->contra);
								if (temporal_C->revision == 1) {
									SetDlgItemText(hwnd, nomcomlis, temporal_C->nomcom);
									SetDlgItemText(hwnd, alilis, temporal_C->ali);
									strcpy_s(INFO_U[3], temporal_C->nomcom);
									strcpy_s(INFO_U[4], temporal_C->ali);
								}
								else {
									SetDlgItemText(hwnd, nomcomlis, "No hay datos");
									SetDlgItemText(hwnd, alilis, "No hay datos");
									strcpy_s(INFO_U[3], "");
									strcpy_s(INFO_U[4], "");
								}
								strcpy_s(INFO_U[0], temporal_C->com);
								strcpy_s(INFO_U[1], temporal_C->nom);
								strcpy_s(INFO_U[2], temporal_C->contra);
								strcpy_s(INFO_U[5], temporal_C->tipo);
								temporal_C = temporal_C->siguiente;
							}
							else {
								temporal_C = temporal_C->siguiente;
							}
						}
					}
				}

				else {
				}

			}
		}break;

		}
		break;


	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}
	return FALSE;
}
BOOL CALLBACK LIS_CL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_listbox = GetDlgItem(hwnd, IDC_LIST3);
		h_edit = GetDlgItem(hwnd, nomcllis);
		h_edit = GetDlgItem(hwnd, alicllis);
		h_edit = GetDlgItem(hwnd, telecllis);
		h_edit = GetDlgItem(hwnd, emailcllis);
		h_edit = GetDlgItem(hwnd, comcllis);
		h_boton = GetDlgItem(hwnd, ACTCLLIS);
		h_boton = GetDlgItem(hwnd, ELICLLIS);
		h_boton = GetDlgItem(hwnd, REGCLLIS);
		h_boton = GetDlgItem(hwnd, ACTLISTA1);
		h_edit = GetDlgItem(hwnd, NOM5);
		h_PicControl = GetDlgItem(hwnd, FOTON5);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON5, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM5, Unom);
		if (primero_CL) {
			temporal_CL = primero_CL;
			while (temporal_CL) {
				if (strcmp(temporal_CL->comercio, comercionom) == 0) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)temporal_CL->nombre);
				}
				temporal_CL = temporal_CL->sig;
			}
		}

		break;

	case WM_COMMAND:
		

		switch (LOWORD(wParam))
		{
		case ACTLISTA1:
			SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_RESETCONTENT, 0, 0);
			if (primero_CL) {
				temporal_CL = primero_CL;
				while (temporal_CL) {
					if (strcmp(temporal_CL->comercio, comercionom) == 0) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)temporal_CL->nombre);
					}
					temporal_CL = temporal_CL->sig;
				}	
			}
			guardar_CL();
			break;
		case ACTCLLIS:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG11), hwnd, (DLGPROC)ActCL);
			break;
		case ELICLLIS:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG10), hwnd, (DLGPROC)BorrarCL);
			break;
		case REGCLLIS:
			EndDialog(hwnd, wParam);
			break;
		case IDC_LIST3:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST3, LB_GETTEXT, cur, (LPARAM)textolist);
				if (primero_CL) {
					temporal_CL = primero_CL;
					while (temporal_CL) {
						if (strcmp(temporal_CL->nombre, textolist) == 0) {
							SetDlgItemText(hwnd, telecllis, temporal_CL->tel);
							SetDlgItemText(hwnd, nomcllis, temporal_CL->nombre);
							SetDlgItemText(hwnd, alicllis, temporal_CL->alias);
							SetDlgItemText(hwnd, emailcllis, temporal_CL->email);
							SetDlgItemText(hwnd, comcllis, temporal_CL->comercio);
							strcpy_s(INFO_CL[0], temporal_CL->nombre);
							strcpy_s(INFO_CL[1], temporal_CL->alias);
							strcpy_s(INFO_CL[2], temporal_CL->tel);
							strcpy_s(INFO_CL[3], temporal_CL->email);
							strcpy_s(INFO_CL[4], temporal_CL->comercio);
							temporal_CL = temporal_CL->sig;
						}
						else {
							temporal_CL = temporal_CL->sig;
						}
					}
				}
				guardar_CL();
			}
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ListPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_listbox = GetDlgItem(hwnd, IDC_LIST5);
		h_edit = GetDlgItem(hwnd, promonomlis);
		h_edit = GetDlgItem(hwnd, promonlis);
		h_edit = GetDlgItem(hwnd, promodesclis);
		h_edit = GetDlgItem(hwnd, estatuslis);
		h_boton = GetDlgItem(hwnd, promoactlis);
		h_boton = GetDlgItem(hwnd, promoelim);
		h_boton = GetDlgItem(hwnd, promoreglis);
		h_boton = GetDlgItem(hwnd, ACTLISTA6);
		h_edit = GetDlgItem(hwnd, NOM10);
		h_PicControl = GetDlgItem(hwnd, FOTON10);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON10, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM10, Unom);
		if (primero_prom) {
			temporal_prom = primero_prom;
			while (temporal_prom) {
				if (strcmp(temporal_prom->lacomer, comercionom) == 0) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST5), LB_ADDSTRING, 0, (LPARAM)temporal_prom->name);
				}
				temporal_prom = temporal_prom->sig;
			}
		}

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ACTLISTA6:
			SendMessage(GetDlgItem(hwnd, IDC_LIST5), LB_RESETCONTENT, 0, 0);
			if (primero_prom) {
				temporal_prom = primero_prom;
				while (temporal_prom) {
					if (strcmp(temporal_prom->lacomer, comercionom) == 0) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST5), LB_ADDSTRING, 0, (LPARAM)temporal_prom->name);
					}
					temporal_prom = temporal_prom->sig;
				}
			}
			break;
		case promoelim:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG15), hwnd, (DLGPROC)BorrarPromo);
			break;
		case promoactlis:
			DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG14), hwnd, (DLGPROC)ActPromo);
			break;
		case promoreglis:
			EndDialog(hwnd, wParam);
			break;
		case IDC_LIST5:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST5, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST5, LB_GETTEXT, cur, (LPARAM)textolist);
				if (primero_prom) {
					temporal_prom = primero_prom;
					while (temporal_prom) {
						if (strcmp(temporal_prom->name, textolist) == 0) {
							SetDlgItemText(hwnd, promonomlis, temporal_prom->name);
							SetDlgItemInt(hwnd, promonlis, (UINT)temporal_prom->promo,FALSE);
							SetDlgItemInt(hwnd, promodesclis, (UINT)temporal_prom->porcentaje,FALSE);
							SetDlgItemText(hwnd, estatuslis, temporal_prom->estatus);

							strcpy_s(INFO_PROM[0], temporal_prom->name);
							INP1= temporal_prom->promo;
							INP2= temporal_prom->porcentaje;
							strcpy_s(INFO_PROM[1], temporal_prom->estatus);
							temporal_prom = temporal_prom->sig;
						}
						else {
							temporal_prom = temporal_prom->sig;
						}
					}
				}
			}
			guardar_PROM();
			break;
		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ListaConsu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_listbox = GetDlgItem(hwnd, IDC_LIST7);
		h_edit = GetDlgItem(hwnd, cienteliscons);
		h_edit = GetDlgItem(hwnd, prodliscons);
		h_edit = GetDlgItem(hwnd, unidadesconslis);
		h_edit = GetDlgItem(hwnd, subtotalconslis);
		h_edit = GetDlgItem(hwnd, descconslis);
		h_edit = GetDlgItem(hwnd, totalconslis);
		h_boton = GetDlgItem(hwnd, IDBACKLIS);
		h_boton = GetDlgItem(hwnd, ACTLISTA7);
		h_edit = GetDlgItem(hwnd, NOM15);
		h_PicControl = GetDlgItem(hwnd, FOTON15);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON15, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM15, Unom);
		if (primero_CL) {
			temporal_CL = primero_CL;
			while (temporal_CL) {
				if (strcmp(temporal_CL->comercio, comercionom) == 0) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST7), LB_ADDSTRING, 0, (LPARAM)temporal_CL->nombre);
				}
				temporal_CL = temporal_CL->sig;
			}
		}

		break;
	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
		case ACTLISTA7:
			SendMessage(GetDlgItem(hwnd, IDC_LIST7), LB_RESETCONTENT, 0, 0);
			if (primero_CL) {
				temporal_CL = primero_CL;
				while (temporal_CL) {
					if (strcmp(temporal_CL->comercio, comercionom) == 0) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST7), LB_ADDSTRING, 0, (LPARAM)temporal_CL->nombre);
					}
					temporal_CL = temporal_CL->sig;
				}
			}
			break;
		case IDBACKLIS:
			EndDialog(hwnd, wParam);
			break;
		}
		case IDC_LIST7:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST7, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST7, LB_GETTEXT, cur, (LPARAM)textolist);
				if (prime) {
					temp = prime;
					while (temp) {
						if (strcmp(temp->client, textolist) == 0) {
							if (temp->total == 0) {
								MessageBox(hwnd, "El cliente seleccionado no ha realizado ningun consumo", "AVISO", MB_OK);
							}
							else {
								SetDlgItemText(hwnd, cienteliscons, temp->client);
								SetDlgItemText(hwnd, prodliscons, temp->client);
								SetDlgItemInt(hwnd, unidadesconslis, (UINT)temp->cantidadpro, FALSE);
								SetDlgItemInt(hwnd, subtotalconslis, (UINT)temp->total, FALSE);
								SetDlgItemInt(hwnd, descconslis, (UINT)temp->desc, FALSE);
								SetDlgItemInt(hwnd, totalconslis, (UINT)temp->titi, FALSE);
								total_cons = 0 + temp->titi;
							}
							temp = temp->sigui;
						}
						else {
							temp = temp->sigui;
						}
					}
				}
			}
			guardar_lis();
			break;
		
		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}

BOOL CALLBACK BorrarU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, BCOM);
		h_edit = GetDlgItem(hwnd, BORNOM);
		h_edit = GetDlgItem(hwnd, BORCON);
		h_edit = GetDlgItem(hwnd, BORNOMC);
		h_edit = GetDlgItem(hwnd, BOALI);
		h_boton = GetDlgItem(hwnd, BORU);
		h_boton = GetDlgItem(hwnd, BACKB);
		SetDlgItemText(hwnd, BCOM, INFO_U[0]);
		SetDlgItemText(hwnd, BORNOM, INFO_U[1]);
		SetDlgItemText(hwnd, BORCON, INFO_U[2]);
		SetDlgItemText(hwnd, BORNOMC, INFO_U[3]);
		SetDlgItemText(hwnd, BOALI, INFO_U[4]);
		h_edit = GetDlgItem(hwnd, NOM6);
		h_PicControl = GetDlgItem(hwnd, FOTON6);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON6, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM6, Unom);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case BORU:
			MessageBox(hwnd, "¿Esta seguro que desea eliminar al usuario seleccionado?", "MENSAJE", MB_ICONQUESTION|MB_YESNO);
			if (IDNO != true) {
				if(strcmp(INFO_U[5], adm)==0){
						auxiliar = primero;
						if (strcmp(auxiliar->nom,INFO_U[1])==0) {
							primero->anterior = nullptr;
							primero = primero->siguiente;
							delete auxiliar;

							MessageBox(hwnd, "La cuenta con la que ingreso ya no existe", "SESION INEXISTENTE", MB_ICONINFORMATION | MB_OK);
							EndDialog(hwnd, wParam);
							PostQuitMessage(0);
						}
						else {	
							while (auxiliar != nullptr && strcmp(auxiliar->nom, INFO_U[1]) != 0) {
								auxiliar = auxiliar->siguiente;
							}
							if (auxiliar != nullptr) {
								if (strcmp(auxiliar->nom, INFO_U[1]) == 0) {
									temporal = auxiliar;
									temporal->anterior->siguiente = temporal->siguiente;
									if (temporal->siguiente != nullptr) {
										temporal->siguiente->anterior = temporal->anterior;
									}
									delete temporal;
								}
							}
						}
						con_adm--;
				}

				if (strcmp(INFO_U[5], caj) == 0) {
					auxiliar_C = primero_C;
					if (strcmp(auxiliar_C->nom, INFO_U[1]) == 0) {
						primero_C->anterior = nullptr;
						primero_C = primero_C->siguiente;
						delete auxiliar_C;
					}
					else {
						while (auxiliar_C != nullptr && strcmp(auxiliar_C->nom, INFO_U[1]) != 0) {
							auxiliar_C = auxiliar_C->siguiente;
						}
						if (auxiliar_C != nullptr) {
							if (strcmp(auxiliar_C->nom, INFO_U[1]) == 0) {
								temporal_C = auxiliar_C;
								temporal_C->anterior->siguiente = temporal_C->siguiente;
								if (temporal_C->siguiente != nullptr) {
									temporal_C->siguiente->anterior = temporal_C->anterior;
								}
								delete temporal_C;
							}
						}
					}
					con_caj--;
				}
				MessageBox(hwnd, "El usuario se ha borrado", "MENSAJE", MB_ICONINFORMATION);
				}	
				EndDialog(hwnd, wParam);
			break;

		case BACKB:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK BorrarCL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, BNOMCL);
		h_edit = GetDlgItem(hwnd, BALICL);
		h_edit = GetDlgItem(hwnd, BTELCL);
		h_edit = GetDlgItem(hwnd, ITECELB);//EMAIL
		h_edit = GetDlgItem(hwnd, BCOMCLI);
		h_boton = GetDlgItem(hwnd, IELICL);
		h_boton = GetDlgItem(hwnd, IREGCL);
		SetDlgItemText(hwnd, BNOMCL, INFO_CL[0]);
		SetDlgItemText(hwnd, BALICL, INFO_CL[1]);
		SetDlgItemText(hwnd, BTELCL, INFO_CL[2]);
		SetDlgItemText(hwnd, ITECELB, INFO_CL[3]);
		SetDlgItemText(hwnd, BCOMCLI, INFO_CL[4]);
		h_edit = GetDlgItem(hwnd, NOM7);
		h_PicControl = GetDlgItem(hwnd, FOTON7);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM7, Unom);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IELICL:
			MessageBox(hwnd, "¿Esta seguro que desea eliminar al cliente seleccionado?", "MENSAJE", MB_ICONQUESTION | MB_YESNO);
			if (IDNO != true) {
				auxiliar_CL = primero_CL;
				if (strcmp(auxiliar_CL->nombre, INFO_CL[0]) == 0) {
					primero_CL->ant = nullptr;
					primero_CL = primero_CL->sig;
					delete auxiliar_CL;
				}
				else {
					while (auxiliar_CL != nullptr && strcmp(auxiliar_CL->nombre, INFO_CL[0]) != 0) {
						auxiliar_CL = auxiliar_CL->sig;
					}
					if (auxiliar_CL != nullptr) {
						if (strcmp(auxiliar_CL->nombre, INFO_CL[0]) == 0) {
							temporal_CL = auxiliar_CL;
							temporal_CL->ant->sig = temporal_CL->sig;
							if (temporal_CL->sig != nullptr) {
								temporal_CL->sig->ant = temporal_CL->ant;
							}
							delete temporal_CL;
						}
					}
				}
				MessageBox(hwnd, "El cliente se ha eliminado", "MENSAJE", MB_ICONINFORMATION);
				con_cli--;
			}
			EndDialog(hwnd, wParam);
			break;
		case IREGCL:
			EndDialog(hwnd, wParam);
			break;

		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK BorrarPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_listbox = GetDlgItem(hwnd, IDC_LIST6);
		h_edit = GetDlgItem(hwnd, BPN);
		h_edit = GetDlgItem(hwnd, BPM);
		h_edit = GetDlgItem(hwnd, BPD);
		h_edit = GetDlgItem(hwnd, BPE);
		h_boton = GetDlgItem(hwnd, BPELIMINAR);
		h_boton = GetDlgItem(hwnd, BPREGRESAR);
		h_boton = GetDlgItem(hwnd, ACTLISTA4);
		SetDlgItemText(hwnd, BPN, INFO_PROM[0]);
		SetDlgItemText(hwnd, BPE, INFO_PROM[1]);
		SetDlgItemInt(hwnd, BPM, (UINT)INP1,FALSE);
		SetDlgItemInt(hwnd, BPD, (UINT)INP2, FALSE);
		h_edit = GetDlgItem(hwnd, NOM12);
		h_PicControl = GetDlgItem(hwnd, FOTON12);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON12, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM12, Unom);
		if (primero_prom) {
			temporal_prom = primero_prom;
			while (temporal_prom) {
				if (strcmp(temporal_prom->lacomer, comercionom) == 0) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST6), LB_ADDSTRING, 0, (LPARAM)temporal_prom->name);
				}
				temporal_prom = temporal_prom->sig;
			}
		}

		break;
	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{
		case ACTLISTA4:
			SendMessage(GetDlgItem(hwnd, IDC_LIST6), LB_RESETCONTENT, 0, 0);
			if (primero_prom) {
				temporal_prom = primero_prom;
				while (temporal_prom) {
					if (strcmp(temporal_prom->lacomer, comercionom) == 0) {
						SendMessage(GetDlgItem(hwnd, IDC_LIST6), LB_ADDSTRING, 0, (LPARAM)temporal_prom->name);
					}
					temporal_prom = temporal_prom->sig;
				}
			}
			break;
		case BPELIMINAR:
			MessageBox(hwnd, "¿Esta seguro que desea eliminar la promocion seleccionada?", "MENSAJE", MB_ICONQUESTION | MB_YESNO);
			if (IDNO != true) {
				auxiliar_prom = primero_prom;
				if (strcmp(auxiliar_prom->name, INFO_PROM[0]) == 0) {
					primero_prom->ant = nullptr;
					primero_prom = primero_prom->sig;
					delete auxiliar_prom;
				}
				else {
					while (auxiliar_prom != nullptr && strcmp(auxiliar_prom->name, INFO_PROM[0]) != 0) {
						auxiliar_prom = auxiliar_prom->sig;
					}
					if (auxiliar_prom != nullptr) {
						if (strcmp(auxiliar_prom->name, INFO_PROM[0]) == 0) {
							temporal_prom = auxiliar_prom;
							temporal_prom->ant->sig = temporal_prom->sig;
							if (temporal_prom->sig != nullptr) {
								temporal_prom->sig->ant = temporal_prom->ant;
							}
							delete temporal_prom;
						}
					}
				}
				if (con_promact != 0) {
					con_promact--;
					con_promin++;
				}
				else {
				con_promin++;
				}
				MessageBox(hwnd, "La promocion se ha eliminado", "MENSAJE", MB_ICONINFORMATION);
				EndDialog(hwnd, wParam);
			}
			break;
		case BPREGRESAR:
			EndDialog(hwnd, wParam);
			break;
		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}

BOOL CALLBACK ContraseU(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_listbox = GetDlgItem(hwnd, IDC_LIST2);
		h_edit = GetDlgItem(hwnd, NUEVACONTRAU);
		h_radio = GetDlgItem(hwnd, IDC_RADIO5);
		h_radio = GetDlgItem(hwnd, IDC_RADIO6);
		h_boton = GetDlgItem(hwnd, guardarcontra);
		h_boton = GetDlgItem(hwnd, regresarcontra);
		h_boton = GetDlgItem(hwnd, ACTLISTA2);
		h_edit = GetDlgItem(hwnd, NOM3);
		h_PicControl = GetDlgItem(hwnd, FOTON3);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON3, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM3, Unom);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ACTLISTA2:
			SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_RESETCONTENT, 0, 0);
			if (deno == 1) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_RESETCONTENT, 0, 0);
				if (primero) {
					temporal = primero;
					while (temporal) {
						if (strcmp(temporal->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)temporal->nom);
						}
						temporal = temporal->siguiente;
					}
				}
			}


			if (deno == 2) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_RESETCONTENT, 0, 0);
				if (primero_C) {
					temporal_C = primero_C;
					while (temporal_C) {
						if (strcmp(temporal_C->com, comercionom) == 0){
							SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)temporal_C->nom);
					}
					temporal_C = temporal_C->siguiente;
					}
				}
			}


			break;
		case IDC_RADIO5:

			if (deno == 2) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_RESETCONTENT, 0, 0);
				if (primero) {
					temporal = primero;
					while (temporal) {
						if (strcmp(temporal->com, comercionom) == 0){
							SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)temporal->nom);
					}
						temporal = temporal->siguiente;
					}
				}
			}
			else {
				if (primero) {
					temporal = primero;
					while (temporal) {
						if (strcmp(temporal->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)temporal->nom);
						}
						temporal = temporal->siguiente;
					}
				}
			}
			deno = 1;
			break;

		case IDC_RADIO6:
			if (deno == 1) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_RESETCONTENT, 0, 0);
				if (primero_C) {
					temporal_C = primero_C;
					while (temporal_C) {
						if (strcmp(temporal_C->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)temporal_C->nom);
						}
						temporal_C = temporal_C->siguiente;
					}
				}
			}
			else {
				if (primero_C) {
					temporal_C = primero_C;
					while (temporal_C) {
						if (strcmp(temporal_C->com, comercionom) == 0) {
							SendMessage(GetDlgItem(hwnd, IDC_LIST2), LB_ADDSTRING, 0, (LPARAM)temporal_C->nom);
						}
						temporal_C = temporal_C->siguiente;
					}
				}
			}
			deno = 2;
			break;

		case IDC_LIST2: {
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, cur, (LPARAM)textolist);
			}
		}break;

		case guardarcontra:
			pase = 0;
			GetDlgItemText(hwnd, NUEVACONTRAU, nuevo, 11);
			valcontra(nuevo, numer3, numer10);
			if (pase == 1) {
				if (deno == 1) {
					if (primero) {
						temporal = primero;
						while (temporal) {
							if (strcmp(temporal->nom, textolist) == 0) {
								GetDlgItemText(hwnd, NUEVACONTRAU, nuevo, 11);
								strcpy_s(temporal->contra,nuevo);
								temporal = temporal->siguiente;
							}
							else {
								temporal = temporal->siguiente;
							}
						}
					}
				}

				if (deno == 2) {
					if (primero_C) {
						temporal_C = primero_C;
						while (temporal_C) {
							if (strcmp(temporal_C->nom, textolist) == 0) {
								GetDlgItemText(hwnd, NUEVACONTRAU, nuevo, 11);
								strcpy_s(temporal_C->contra, nuevo);
								temporal_C = temporal_C->siguiente;
							}
							else {
								temporal_C = temporal_C->siguiente;
							}
						}
					}
				}

				MessageBox(hwnd, "La contraseña se ha actualizado correctamente", "MENSAJE", MB_ICONINFORMATION);
				EndDialog(hwnd, wParam);
			}
		
			else {
				MessageBox(hwnd, "Vuelve a ingresar la nueva contraseña", "INFORMACION", MB_OK || MB_ICONINFORMATION);
				SetDlgItemText(hwnd, NUEVACONTRAU, "");
			}
			break;

		case regresarcontra:
			EndDialog(hwnd, wParam);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ActCL(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_listbox = GetDlgItem(hwnd, IDC_LIST4);
		h_edit = GetDlgItem(hwnd, nomactcl);
		h_edit = GetDlgItem(hwnd, aliactcl);
		h_edit = GetDlgItem(hwnd, telactcl);
		h_edit = GetDlgItem(hwnd, emailactcl);//EMAIL
		h_edit = GetDlgItem(hwnd, comactcl);
		h_boton = GetDlgItem(hwnd, guardaractcl);
		h_boton = GetDlgItem(hwnd, regresaractcl);
		h_boton = GetDlgItem(hwnd, ACTLISTA5);
		h_edit = GetDlgItem(hwnd, NOM8);
		h_PicControl = GetDlgItem(hwnd, FOTON8);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON8, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM8, Unom);
		if (primero_CL) {
			temporal_CL = primero_CL;
			while (temporal_CL) {
				SendMessage(GetDlgItem(hwnd, IDC_LIST4), LB_ADDSTRING, 0, (LPARAM)temporal_CL->nombre);
				temporal_CL = temporal_CL->sig;
			}
		}
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ACTLISTA5:
			SendMessage(GetDlgItem(hwnd, IDC_LIST4), LB_RESETCONTENT, 0, 0);
			if (primero_CL) {
				temporal_CL = primero_CL;
				while (temporal_CL) {
					SendMessage(GetDlgItem(hwnd, IDC_LIST4), LB_ADDSTRING, 0, (LPARAM)temporal_CL->nombre);
					temporal_CL = temporal_CL->sig;
				}
			}
			break;

		case IDC_LIST4:
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				cur = SendDlgItemMessage(hwnd, IDC_LIST4, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_LIST4, LB_GETTEXT, cur, (LPARAM)textolist);
				if (primero_CL) {
					temporal_CL = primero_CL;
					while (temporal_CL) {
						if (strcmp(temporal_CL->nombre, textolist) == 0) {
							SetDlgItemText(hwnd, telactcl, temporal_CL->tel);
							SetDlgItemText(hwnd, nomactcl, temporal_CL->nombre);
							SetDlgItemText(hwnd, aliactcl, temporal_CL->alias);
							SetDlgItemText(hwnd, emailactcl, temporal_CL->email);
							SetDlgItemText(hwnd, comactcl, temporal_CL->comercio);
							temporal_CL = temporal_CL->sig;
						}
						else {
							temporal_CL = temporal_CL->sig;
						}
					}
				}
			}
			break;
		case guardaractcl:
			temporal_CL = primero_CL;
			while (strcmp(temporal_CL->nombre, textolist) != 0) {
				temporal_CL = temporal_CL->sig;
			}
			pase = 0;
			GetDlgItemText(hwnd, aliactcl, INFO_CL[1], 51);
			GetDlgItemText(hwnd, telactcl, INFO_CL[2], 51);
			GetDlgItemText(hwnd, emailactcl, INFO_CL[3], 51);

			if (strcmp(temporal_CL->alias, INFO_CL[1]) != 0) {
				valletra(INFO_CL[1], numer5, numer15);
				if (pase == 1) {
					strcpy_s(temporal_CL->alias, INFO_CL[1]);
					MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
					EndDialog(hwnd, wParam);
				}
				else{
					MessageBox(hwnd, "Vuelve a ingresar los nuevos datos", "INFORMATION", MB_OK || MB_ICONINFORMATION);
					SetDlgItemText(hwnd, nomactcl, "");
					SetDlgItemText(hwnd, aliactcl, "");
					SetDlgItemText(hwnd, telactcl, "");
					SetDlgItemText(hwnd, emailactcl, "");
				}
			}
			else if (strcmp(temporal_CL->tel, INFO_CL[2]) != 0) {
				valnum(INFO_CL[2], numer0, numer10);
				if (pase == 1) {
				strcpy_s(temporal_CL->tel, INFO_CL[2]);
				MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
				EndDialog(hwnd, wParam);
			}
				else {
					MessageBox(hwnd, "Vuelve a ingresar los nuevos datos", "INFORMATION", MB_OK || MB_ICONINFORMATION);
					SetDlgItemText(hwnd, nomactcl, "");
					SetDlgItemText(hwnd, aliactcl, "");
					SetDlgItemText(hwnd, telactcl, "");
					SetDlgItemText(hwnd, emailactcl, "");
				}
			}
			else if (strcmp(temporal_CL->email, INFO_CL[3]) != 0) {
				valemail(INFO_CL[3], numer5, numer25);
				if (pase == 1) {
					strcpy_s(temporal_CL->email, INFO_CL[3]);
					MessageBox(hwnd, "La informacion se ha actualizado", "MENSAJE", MB_ICONINFORMATION);
					EndDialog(hwnd, wParam);
				}
				else {
					MessageBox(hwnd, "Vuelve a ingresar los nuevos datos", "INFORMATION", MB_OK || MB_ICONINFORMATION);
					SetDlgItemText(hwnd, nomactcl, "");
					SetDlgItemText(hwnd, aliactcl, "");
					SetDlgItemText(hwnd, telactcl, "");
					SetDlgItemText(hwnd, emailactcl, "");
				}
			}
			else {
				MessageBox(hwnd, "No ingreso ningun cambio", "AVISO", MB_OK || MB_ICONEXCLAMATION);
				EndDialog(hwnd, wParam);
			}
			
			break;
		case regresaractcl:
			EndDialog(hwnd, wParam);
			break;
		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}
BOOL CALLBACK ActPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		MessageBox(hwnd, "Nose", "a", MB_CANCELTRYCONTINUE);
		break;
	case WM_INITDIALOG:
		h_edit = GetDlgItem(hwnd, lecnom);
		h_edit = GetDlgItem(hwnd, lecmon);
		h_edit = GetDlgItem(hwnd, lecdesc);
		h_edit = GetDlgItem(hwnd, lecfecha);
		h_boton = GetDlgItem(hwnd, actguarprom);
		h_boton = GetDlgItem(hwnd, actcanprom);
		h_radio = GetDlgItem(hwnd, IDC_RADIO9A);
		h_radio = GetDlgItem(hwnd, IDC_RADIO10I);
		SetDlgItemText(hwnd, lecnom, INFO_PROM[0]);
		SetDlgItemText(hwnd, lecfecha, __DATE__);
		SetDlgItemInt(hwnd, lecmon, (UINT)INP1, FALSE);
		SetDlgItemInt(hwnd, lecdesc, (UINT)INP2, FALSE);
		h_edit = GetDlgItem(hwnd, NOM11);
		h_PicControl = GetDlgItem(hwnd, FOTON11);
		bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 70, 50, LR_LOADFROMFILE);
		SendDlgItemMessage(hwnd, FOTON11, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		SetDlgItemText(hwnd, NOM11, Unom);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_RADIO9A:
			deno = 1;
			break;
		case IDC_RADIO10I:
			deno = 2;
			break;
		case actguarprom:
			if (primero_prom) {
				temporal_prom = primero_prom;
				while (temporal_prom) {
					if (strcmp(temporal_prom->name, INFO_PROM[0]) == 0) {
						if (deno == 1) {
				strcpy_s(temporal_prom->estatus, act);
				con_promact++;
				con_promin--;
			}
						if (deno == 2) {
				strcpy_s(temporal_prom->estatus, inact);
				con_promin++;
				con_promact--;
			}
						temporal_prom = temporal_prom->sig;
					}
					else {
						temporal_prom = temporal_prom->sig;
					}
				}
			}
			MessageBox(hwnd, "La promocion se ha actualizado correctamente", "MENSAJE", MB_ICONINFORMATION);
			EndDialog(hwnd, wParam);
			break;
		case actcanprom:
			EndDialog(hwnd, wParam);
			break;

		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, wParam);
		return true;
	}

	return FALSE;
}



//Funciones
void buscarA() {
	if (primero) {
		auxiliar = primero;
		while (auxiliar) {
			if (strcmp(auxiliar->nom, dato2)==0 && strcmp(auxiliar->contra, dato3)==0) {
				if (auxiliar->revision == 0) {
					DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), 0, (DLGPROC)ActU);
				}
				strcpy_s(comercionom, 15 , auxiliar->com);
				strcpy_s(Unom, 51, auxiliar->nomcom);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2), 0, (DLGPROC)DialogoModal);
				guardar_A();
			}
			else {
				auxiliar = auxiliar->siguiente;
			}
		}
	}
}
void buscarC() {
	if (primero_C) {
		auxiliar_C = primero_C;
		while (auxiliar_C) {
			if (strcmp(auxiliar_C->nom, dato2) == 0 && strcmp(auxiliar_C->contra, dato3) == 0) {
				if (auxiliar_C->revision == 0) {
					DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), 0, (DLGPROC)ActU);
				}
				strcpy_s(comercionom,auxiliar_C->com);
				strcpy_s(Unom, auxiliar_C->nomcom);
				DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2), 0, (DLGPROC)DialogoModal);
				guardar_A();
			}

			else {
				auxiliar_C = auxiliar_C->siguiente;
			}
		}
	}
}

void guardar_A() {

	Archivo.open("Usuario.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		auxiliar = primero;

		while (auxiliar != nullptr) {

			Archivo.write(reinterpret_cast<char*>(auxiliar), sizeof(nodo));
			auxiliar = auxiliar->siguiente;
		}

	}


	Archivo.close();

}
void guardar_C() {

	Archivo.open("Cajero.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		auxiliar_C = primero_C;

		while (auxiliar_C != nullptr) {

			Archivo.write(reinterpret_cast<char*>(auxiliar_C), sizeof(nodo));
			auxiliar_C = auxiliar_C->siguiente;
		}

	}


	Archivo.close();

}
void guardar_CL() {

	Archivo.open("Cliente.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		auxiliar_CL = primero_CL;

		while (auxiliar_CL != nullptr) {

			Archivo.write(reinterpret_cast<char*>(auxiliar_CL), sizeof(nodo_Cliente));
			auxiliar_CL = auxiliar_CL->sig;
		}

	}


	Archivo.close();

}
void guardar_PRO() {

	Archivo.open("Productos.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		aux = prim;

		while (aux != nullptr) {

			Archivo.write(reinterpret_cast<char*>(aux), sizeof(nodo_productos));
			aux = aux->sigui;
		}

	}


	Archivo.close();

}
void guardar_PROM() {

	Archivo.open("Promociones.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		auxiliar_prom = primero_prom;

		while (auxiliar_prom != nullptr) {

			Archivo.write(reinterpret_cast<char*>(auxiliar_prom), sizeof(nodo_promo));
			auxiliar_prom = auxiliar_prom->sig;
		}

	}


	Archivo.close();

}
void guardar_lis() {

	Archivo.open("Lista.bin", ios::out | ios::binary);

	if (Archivo.is_open()) {

		auxi = prime;

		while (auxi != nullptr) {

			Archivo.write(reinterpret_cast<char*>(auxi), sizeof(nodo_lista));
			auxi = auxi->sigui;
		}

	}


	Archivo.close();

}

void leer_a() {
	Archivo.open("Usuario.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			nodo* l = new nodo;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(nodo));
				Archivo.read(reinterpret_cast<char*>(l), sizeof(nodo));
				if (primero == nullptr) {
					primero = new nodo;
					strcpy_s(primero->com, l->com);
					strcpy_s(primero->nom, l->nom);
					strcpy_s(primero->contra, l->contra);
					strcpy_s(primero->tipo, l->tipo);
					strcpy_s(primero->ali, l->ali);
					strcpy_s(primero->nomcom, l->nomcom);
					strcpy_s(primero->foton, l->foton);
					primero->revision = l->revision;
					primero->siguiente = nullptr;
					primero->anterior = nullptr;
					auxiliar = primero;
					k++;
				}
				else {
					auxiliar = primero;
					while (auxiliar->siguiente != nullptr) {
						auxiliar = auxiliar->siguiente;
					}
					auxiliar->siguiente = new nodo;
					auxiliar->siguiente->siguiente = nullptr;
					auxiliar->siguiente->anterior = auxiliar;
					auxiliar = auxiliar->siguiente;
					strcpy_s(auxiliar->com, l->com);
					strcpy_s(auxiliar->nom, l->nom);
					strcpy_s(auxiliar->contra, l->contra);
					strcpy_s(auxiliar->tipo, l->tipo);
					strcpy_s(auxiliar->ali, l->ali);
					strcpy_s(auxiliar->nomcom, l->nomcom);
					strcpy_s(auxiliar->foton, l->foton);
					auxiliar->revision = l->revision;
					k++;
				}
			}
			k = 0;

			if (primero->com == "") {
				primero->siguiente = nullptr;
				primero = nullptr;
			}
			else {
				temporal = auxiliar;
				if (temporal->siguiente == nullptr) {
					temporal->anterior->siguiente = temporal->siguiente;
					if (temporal->siguiente != nullptr) {
						temporal->siguiente->anterior = temporal->anterior;
					}
					delete temporal;
				}
			}
		}
	}
	else {
		MessageBox(NULL, "El archivo no se pudo abrir", "ERROR", MB_OK || MB_ICONERROR);
	}
	Archivo.close();
}
void leer_c() {
	Archivo.open("Cajero.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			nodo* le = new nodo;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(nodo));
				Archivo.read(reinterpret_cast<char*>(le), sizeof(nodo));
				if (primero_C == nullptr) {
					primero_C = new nodo;
					strcpy_s(primero_C->com, le->com);
					strcpy_s(primero_C->nom, le->nom);
					strcpy_s(primero_C->contra, le->contra);
					strcpy_s(primero_C->tipo, le->tipo);
					strcpy_s(primero_C->ali, le->ali);
					strcpy_s(primero_C->nomcom, le->nomcom);
					strcpy_s(primero_C->foton, le->foton);
					primero_C->revision = le->revision;
					primero_C->siguiente = nullptr;
					primero_C->anterior = nullptr;
					auxiliar_C = primero_C;
					k++;
				}
				else {
					auxiliar_C = primero_C;
					while (auxiliar_C->siguiente != nullptr) {
						auxiliar_C = auxiliar_C->siguiente;
					}
					auxiliar_C->siguiente = new nodo;
					auxiliar_C->siguiente->siguiente = nullptr;
					auxiliar_C->siguiente->anterior = auxiliar;
					auxiliar_C = auxiliar->siguiente;
					strcpy_s(auxiliar_C->com, le->com);
					strcpy_s(auxiliar_C->nom, le->nom);
					strcpy_s(auxiliar_C->contra, le->contra);
					strcpy_s(auxiliar_C->tipo, le->tipo);
					strcpy_s(auxiliar_C->ali, le->ali);
					strcpy_s(auxiliar_C->nomcom, le->nomcom);
					strcpy_s(auxiliar_C->foton, le->foton);
					auxiliar_C->revision = le->revision;
					k++;
				}
			}
			k = 0;
			if (primero_C->com == "") {
				primero_C->siguiente = nullptr;
				primero_C = nullptr;
			}
			else {
				temporal_C = auxiliar_C;
				if (temporal_C->siguiente != nullptr) {
					temporal_C->anterior->siguiente = temporal_C->siguiente;
					if (temporal_C->siguiente != nullptr) {
						temporal_C->siguiente->anterior = temporal_C->anterior;
					}
					delete temporal_C;
				}
			}
		}
	}
	else {
		MessageBox(NULL, "El archivo no se pudo abrir", "ERROR", MB_OK || MB_ICONERROR);
	}
	Archivo.close();
}
void leer_cl() {
	Archivo.open("Cliente.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			nodo_Cliente* lec = new nodo_Cliente;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(nodo_Cliente));
				Archivo.read(reinterpret_cast<char*>(lec), sizeof(nodo_Cliente));
				if (primero_CL == nullptr) {
					primero_CL = new nodo_Cliente;

					strcpy_s(primero_CL->nombre, lec->nombre);
					strcpy_s(primero_CL->alias, lec->alias);
					strcpy_s(primero_CL->tel, lec->tel);
					strcpy_s(primero_CL->email, lec->email);
					strcpy_s(primero_CL->comercio, lec->comercio);
					primero_CL->sig = nullptr;
					primero_CL->ant = nullptr;
					auxiliar_CL = primero_CL;
					k++;
				}
				else {
					auxiliar_CL = primero_CL;
					while (auxiliar_CL->sig != nullptr) {
						auxiliar_CL = auxiliar_CL->sig;
					}
					auxiliar_CL->sig = new nodo_Cliente;
					auxiliar_CL->sig->sig = nullptr;
					auxiliar_CL->sig->ant = auxiliar_CL;
					auxiliar_CL = auxiliar_CL->sig;

					strcpy_s(auxiliar_CL->nombre, lec->nombre);
					strcpy_s(auxiliar_CL->alias, lec->alias);
					strcpy_s(auxiliar_CL->tel, lec->tel);
					strcpy_s(auxiliar_CL->email, lec->email);
					strcpy_s(auxiliar_CL->comercio, lec->comercio);
					k++;
				}
			}
			k = 0;
			if (primero_CL->nombre == "") {
				primero_CL->sig = nullptr;
				primero_CL = nullptr;
			}
			else {
				temporal_CL = auxiliar_CL;
				if (temporal_CL->sig != nullptr) {
					temporal_CL->ant->sig = temporal_CL->sig;
					if (temporal_CL->sig != nullptr) {
						temporal_CL->sig->ant = temporal_CL->ant;
					}
					delete temporal_CL;
				}
			}
		}
	}
	else {
		MessageBox(NULL, "El archivo no se pudo abrir", "ERROR", MB_OK || MB_ICONERROR);
	}
	Archivo.close();
}
void leer_pro() {
	Archivo.open("Productos.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			nodo_productos* lect = new nodo_productos;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(nodo_productos));
				Archivo.read(reinterpret_cast<char*>(lect), sizeof(nodo_productos));
				if (prim == nullptr) {
					prim = new nodo_productos;
					strcpy_s(prim->nombr, lect->nombr);
					prim->precio = lect->precio;
					prim->sigui = nullptr;
					prim->ante = nullptr;
					aux = prim;
					k++;
				}
				else {
					aux = prim;
					while (aux->sigui != nullptr) {
						aux = aux->sigui;
					}
					aux->sigui = new nodo_productos;
					aux->sigui->sigui = nullptr;
					aux->sigui->ante = aux;
					aux = aux->sigui;
					strcpy_s(aux->nombr, lect->nombr);
					aux->precio = lect->precio;
					k++;
				}
			}
			k = 0;
			if (prim->nombr == "") {
				prim->sigui = nullptr;
				prim = nullptr;
			}
			else {
				tem = aux;
				if (tem->sigui != nullptr) {
					tem->ante->sigui = tem->sigui;
					if (tem->sigui != nullptr) {
						tem->sigui->ante = tem->ante;
					}
					delete tem;
				}
			}
		}
	}
	else {
		MessageBox(NULL, "El archivo no se pudo abrir", "ERROR", MB_OK || MB_ICONERROR);
	}
	Archivo.close();
}
void leer_prom() {
	Archivo.open("Promociones.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			nodo_promo* lectu = new nodo_promo;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(nodo_promo));
				Archivo.read(reinterpret_cast<char*>(lectu), sizeof(nodo_promo));
				if (primero_prom == nullptr) {
					primero_prom = new nodo_promo;
					strcpy_s(primero_prom->name, lectu->name);
					strcpy_s(primero_prom->lacomer, lectu->lacomer);
					primero_prom->promo = lectu->promo;
					primero_prom->porcentaje = lectu->porcentaje;
					strcpy_s(primero_prom->estatus, lectu->estatus);
					primero_prom->sig = nullptr;
					primero_prom->ant = nullptr;
					auxiliar_prom = primero_prom;
					k++;
				}
				else {
					auxiliar_prom = primero_prom;
					while (auxiliar_prom->sig != nullptr) {
						auxiliar_prom = auxiliar_prom->sig;
					}
					auxiliar_prom->sig = new nodo_promo;
					auxiliar_prom->sig->sig = nullptr;
					auxiliar_prom->sig->ant = auxiliar_prom;
					auxiliar_prom = auxiliar_prom->sig;
					strcpy_s(auxiliar_prom->lacomer, lectu->lacomer);
					strcpy_s(auxiliar_prom->name, lectu->name);
					auxiliar_prom->promo = lectu->promo;
					auxiliar_prom->porcentaje = lectu->porcentaje;
					strcpy_s(auxiliar_prom->estatus, lectu->estatus);

					k++;
				}
			}
			k = 0;
			if (primero_prom->name == "") {
				primero_prom->sig = nullptr;
				primero_prom = nullptr;
			}
			else {
				temporal_prom = auxiliar_prom;
				if (temporal_prom->sig != nullptr) {
					temporal_prom->ant->sig = temporal_prom->sig;
					if (temporal_prom->sig != nullptr) {
						temporal_prom->sig->ant = temporal_prom->ant;
					}
					delete temporal_prom;
				}
			}
		}
	}
	else {
		MessageBox(NULL, "El archivo no se pudo abrir", "ERROR", MB_OK || MB_ICONERROR);
	}
	Archivo.close();
}
void leer_list() {
	Archivo.open("Lista.bin", ios::in | ios::binary);
	if (Archivo.is_open()) {
		Archivo.seekg(0, ios::end);
		tamaño = Archivo.tellg();
		if (tamaño != 0) {
			nodo_lista* lectur = new nodo_lista;
			while (!Archivo.eof()) {
				Archivo.seekg(k * sizeof(nodo_lista));
				Archivo.read(reinterpret_cast<char*>(lectur), sizeof(nodo_lista));
				if (prime == nullptr) {
					prime = new nodo_lista;
					strcpy_s(prime->client, lectur->client);
					strcpy_s(prime->pro, lectur->pro);
					strcpy_s(prime->fechas, lectur->fechas);
					strcpy_s(prime->comercios, lectur->comercios);
					prime->cantidadpro = lectur->cantidadpro;
					prime->total = lectur->total;
					prime->desc = lectur->desc;
					prime->titi = lectur->titi;
					prime->sigui = nullptr;
					prime->ante = nullptr;
					auxi = prime;
					k++;
				}
				else {
					auxi = prime;
					while (auxi->sigui != nullptr) {
						auxi = auxi->sigui;
					}
					auxi->sigui = new nodo_lista;
					auxi->sigui->sigui = nullptr;
					auxi->sigui->ante = auxi;
					auxi = auxi->sigui;
					strcpy_s(auxi->client, lectur->client);
					strcpy_s(auxi->pro, lectur->pro);
					strcpy_s(auxi->fechas, lectur->fechas);
					strcpy_s(auxi->comercios, lectur->comercios);
					auxi->cantidadpro = lectur->cantidadpro;
					auxi->total = lectur->total;
					auxi->desc = lectur->desc;
					auxi->titi = lectur->titi;
					k++;
				}
			}
			k = 0;
			if (prime->client == "") {
				prime->sigui = nullptr;
				prime = nullptr;
			}
			else {
				temp = auxi;
				if (temp->sigui != nullptr) {
					temp->ante->sigui = temp->sigui;
					if (temp->sigui != nullptr) {
						temp->sigui->ante = temp->ante;
					}
					delete temp;
				}
			}
		}
	}
	else {
		MessageBox(NULL, "El archivo no se pudo abrir", "ERROR", MB_OK || MB_ICONERROR);
	}
	Archivo.close();
}

void valalfa(char algo[MAX_PATH], int n1, int n2) {
	x = 0;
	w = 0;
	acumulador = strlen(algo);
	if (acumulador > n1 && acumulador < n2) {
		pase = pase+.5;
		for (i = 0; i <= acumulador; i++) {
				if (isspace(algo[i])) {
					x++;
				}
		
				if (isalnum(algo[i])) {
					w++;
				}
			}

				if (x + w == acumulador) {
					pase=pase+.5;
				}
				else {
					MessageBox(NULL, "Solo se permiten caracteres alfanumericos y espacios", "ERROR", MB_OK || MB_ICONERROR);
				}
	}
	else {
		strcpy_s(textodefault, "El numero de caracteres va desde  ");
		_itoa_s(n1, buffer, 10);
		strcat_s(textodefault, buffer);
		strcat_s(textodefault, " a ");
		_itoa_s(n2, buffer, 10);
		strcat_s(textodefault, buffer);
		MessageBox(NULL, textodefault, "ERROR", MB_OK || MB_ICONERROR);
	}
	
}
void valletra(char algom[MAX_PATH], int nu1, int nu2) {
	x = 0;
	w = 0;
	acumulador = strlen(algom);
	if (acumulador > nu1 && acumulador < nu2)
	{
		pase =pase+ .5;
		for (i = 0; i <= acumulador; i++) {
			if (isspace(algom[i])) {
				x++;
			}
			if (isalpha(algom[i])) {
				x++;
			}
			if (isdigit(algom[i])) {
				w++;
			}
		}
		if (w != 0) {
			MessageBox(NULL, "Solo se permiten letras", "ERROR", MB_OK || MB_ICONERROR);
		}
		else {
			pase =pase+ .5;
		}
	
		
		}
	else{
		strcpy_s(textodefault, "El numero de caracteres va desde  ");
		_itoa_s(nu1, buffer, 10);
		strcat_s(textodefault, buffer);
		strcat_s(textodefault, " a ");
		_itoa_s(nu2, buffer, 10);
		strcat_s(textodefault, buffer);
		MessageBox(NULL, textodefault, "ERROR", MB_OK || MB_ICONERROR);
	}
	
}
void valnum(char alll[MAX_PATH],int num1, int num2) {
	x = 0;
	w = 0;
	acumulador = strlen(alll);
	if (acumulador > num1 && acumulador < num2)
	{
		pase = pase+.5;
		for (i = 0; i <= acumulador; i++) {
				if (isspace(alll[i])) {
					x++;
				}
				if (isalpha(alll[i])) {
					x++;
				}
				if (isdigit(alll[i])) {
					w++;
				}
			}
			if (w - x != acumulador) {
				MessageBox(NULL, "Solo se permiten caracteres numericos", "ERROR", MB_OK || MB_ICONERROR);
			}
			else {
				pase=pase+.5;
			}
	}
	else {
		strcpy_s(textodefault, "El numero de caracteres va desde  ");
		_itoa_s(num1, buffer, 10);
		strcat_s(textodefault, buffer);
		strcat_s(textodefault, " a ");
		_itoa_s(num2, buffer, 10);
		strcat_s(textodefault, buffer);
		MessageBox(NULL, textodefault, "ERROR", MB_OK || MB_ICONERROR);
	}
	
}
void valcontra(char co[MAX_PATH],int nume1, int nume2) {
	x = 0;
	w = 0;
	acumulador = strlen(co);
	if (acumulador > nume1 && acumulador < nume2) {
		pase = pase +.5;
		for (i = 0; i <= acumulador - 1; i++) {
				if (!isalnum(co[i])) {
					if (!isspace(co[i])) {
						x++;
					}
				}
				if (isalpha(co[i])) {
					h++;
				}
				if (isdigit(co[i])) {
					w++;
				}
			}
			if (x != 0 && h != 0 && w != 0) {
				pase = pase +.5;
			}
			else {
				MessageBox(NULL, "La contraseña debe tener 1 numero, 1 letra y 1 caracter especial", "ERROR", MB_OK || MB_ICONERROR);
			}
	}
	else {
		strcpy_s(textodefault, "El numero de caracteres va desde  ");
		_itoa_s(nume1, buffer, 10);
		strcat_s(textodefault, buffer);
		strcat_s(textodefault, " a ");
		_itoa_s(nume2, buffer, 10);
		strcat_s(textodefault, buffer);
		MessageBox(NULL, textodefault, "ERROR", MB_OK || MB_ICONERROR);
	}
	
}
void valemail(char e[MAX_PATH], int numer1, int numer2) {
	x = 0;
	w = 0;
	acumulador = strlen(e);
	if (acumulador > numer1 && acumulador < numer2) {
		pase = pase +.5;

		if (strchr(e, '@') != NULL) {
			pase =pase + .25;
		}
		if (strchr(e, '.') != NULL) {
			pase = pase+.25;
		}

		if(pase==.5||pase==.75) {
			MessageBox(NULL, "La contraseña debe tener formato email", "ERROR", MB_OK || MB_ICONERROR);
		}
	}
	else {
		strcpy_s(textodefault, "El numero de caracteres va desde  ");
		_itoa_s(numer1, buffer, 10);
		strcat_s(textodefault, buffer);
		strcat_s(textodefault, " a ");
		_itoa_s(numer2, buffer, 10);
		strcat_s(textodefault, buffer);
		MessageBox(NULL, textodefault, "ERROR", MB_OK || MB_ICONERROR);
	}

}

