#include <windows.h>
#include "resource.h"
#include <locale.h>
#include <CommDlg.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

HWND ghDlg = 0;
HWND h_edit;
HWND Dialog2, Dialog3, Dialog4, Dialog5, Dialog6;
HWND g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15, 
g16, g17, g18, g19, g20, g21, g22, g23, g24, g25;
HWND a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15,
a16, a17, a18, a19, a20, a21, a22, a23, a24, a25;
HWND h_combobox, h_listbox1, h_listbox2, h_listbox3, h_listbox4;
HWND hPictureControl;
HWND Edit;
HMENU hMenu;
HINSTANCE hInstance;
HBITMAP hBitmap;
wchar_t contador[200000];
bool nuevo, regresar, nuevous, confirmar;
int lista = 0;


struct usuarios {
    wchar_t nomusuario[50], nombrecom[50], contraseña[50], comercio[50], alias[50];
    int numcomer = 0;
    bool Admin, NewUsuario;

    usuarios* siguiente;
};
struct clientes {
    wchar_t nomcliente[50], alias[50], telefono[50], email[50], comercio[50], fecha[50];
    int numcomer;

    clientes* siguiente;
};
struct promociones {
    wchar_t nompromo[50], fecha[50];
    float cantidad = 0, porcentaje = 0;
    bool activo;
    int numcomer;
    promociones* siguiente;
};
struct consumos {
    wchar_t consumo[50], fecha[50];
    float monto = 0, subtotal = 0, descuento = 0, total = 0;
    int numcomer;

    consumos* siguiente;
};


struct nodo {
    string dato1 = 0;
    int dato2 = 0;
    nodo* siguiente;
};


//usuarios usuario[100];
usuarios* actual = nullptr;
usuarios* buscar = new usuarios();
usuarios* lista1 = NULL;

clientes cliente[200];
clientes* buscar2 = new clientes();
clientes* lista2 = NULL;

promociones* lista3 = NULL;
promociones* buscar3 = new promociones();

consumos* lista4 = NULL;
consumos* buscar4 = new consumos();

char menu0, menu1, menu2, menu3, sinoadmin, sinoactivo;
bool UsuValid, adminuevusu, comernew, adad = true;
int i = 0;
//j = usuario actual
int j = 0;

//k = numero de usuarios
int k = 0;

//l = numero de comercios
int l = 0;

//m = numero de clientes
int m = 0;

//n = numero de promociones
int n = 0;

//ñ = numero de consumos
int ñ = 0;

wchar_t Usuario[50], Contraseña[50], Comercio[50];// , UsuariosBin;

wchar_t Buscar_Usuario[50];
wchar_t Buscar_Cliente[50];
wchar_t Buscar_Promo[50];
wchar_t Buscar_Consumo[50];

float producto;
//Lista ligada Usuarios
wchar_t usu[50], nomcom[50], cont[50], comer[50], ali[50]; int numcom; bool adm, newus;

//Lista Ligada Clientes
wchar_t nomclien[50], alic[50], tel[50], ema[50], comerc[50], fech[50]; int numcomc;

//Lista ligada Promociones
wchar_t promo[50], date[50]; float cant, por; bool act; int numcomp;

//Lista ligada Consumos
wchar_t cons[50], datec[50]; int mont, sub, desc, tot, numcomco;

void NuevoUsuario();
void agregar_usuario(usuarios*& lista1, wchar_t usu[50], wchar_t nomcom[50], wchar_t cont[50], wchar_t comer[50], wchar_t ali[50], int numcom, bool adm, bool newus);
//usuario
wchar_t usuarioq[20], contrasena[20], comercio[20], alias[20], nombre[50]; int cantus = 0;

//cliente
wchar_t clienteq[50], aliasclien[20], telefono[20], email[50], comercioclien[20], fecha[20]; int cantclien = 0;

//promocion
wchar_t promocionq[50], monto[10], porcentaje[10], activa[5]; int cantprom = 0;

//consumo
wchar_t consumoq[50], montocons[20], fechacons[20], subtotal[20], descuento[20], total[20]; int cantcons = 0;

int Precio_Global = 20;
//Ventanas-----------------------------------------------------------------------------------------------------------------------
BOOL CALLBACK WindowProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WindowProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WindowProc3(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WindowProc4(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WindowProc5(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK WindowProc6(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//Lista--
BOOL CALLBACK Lista1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Lista2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Lista3(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Lista4(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//Usuario--
BOOL CALLBACK RegistroUsuario(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ActualizarUA(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK NuevUsuario(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ResCon(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ResConAct(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Actusu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ActusuB1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//Clientes--
BOOL CALLBACK ActClien(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK NuevCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//Promociones--
BOOL CALLBACK ActProm(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK NuevPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//Consumos--
BOOL CALLBACK NuevConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ActCons(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Total(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Confirmar(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void display_file(LPWSTR path) {
    size_t i;
    char buffer[256];
    ZeroMemory(buffer, 256);
    wcstombs_s(&i, buffer, 256, path, 256 - 1);

    FILE* file;
    errno_t err;
    err = fopen_s(&file, buffer, "r");

    if (err == 0)
    {
        fseek(file, 0, SEEK_END);
        int _size = ftell(file);
        rewind(file);
        char* data = new char[_size + 1];
        fread(data, _size, _size, file);
        data[_size] = '\0';
        fclose(file);

        wchar_t wtext[256];
        ZeroMemory(wtext, 256);
        size_t len;
        mbstowcs_s(&len, wtext, 256, data, strlen(data) + 1);
        LPWSTR ptr = wtext;

        GetWindowText(g1, (LPWSTR)cliente, sizeof(cliente));
        //SetWindowText(Edit, ptr);
    }
}

void Abrir(HWND padre) {
    OPENFILENAME openfilename;

    TCHAR szFile[MAX_PATH + 1];
    ZeroMemory(szFile, sizeof(szFile));

    ZeroMemory(&openfilename, sizeof(OPENFILENAME));
    openfilename.lStructSize = sizeof(OPENFILENAME);
    openfilename.hwndOwner = padre;
    openfilename.lpstrFile = szFile;
    openfilename.nMaxFile = MAX_PATH;
    openfilename.nFilterIndex = 1;
    openfilename.lpstrFileTitle = NULL;
    openfilename.nMaxFileTitle = 0;
    openfilename.lpstrInitialDir = NULL;
    openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&openfilename))
    {
        display_file(openfilename.lpstrFile/*, paramEdit*/);
    }
    else
    {
        //MessageBox(NULL, TEXT("Could not open this file"), TEXT("File I/O Error"), MB_ICONSTOP);
    }
}

void write_file(LPWSTR path) {
    char buffer[256];
    ZeroMemory(buffer, 256);
    size_t i;
    wcstombs_s(&i, buffer, 256, path, 256 - 1);

    FILE* file;
    errno_t err;
    err = fopen_s(&file, buffer, "w");

    if (err == 0)
    {
        int size = GetWindowTextLength(g1);
        LPSTR _data = new char[size + 1];
        GetWindowTextA(g1, _data, size + 1);

        fwrite(_data, size + 1, 1, file);
        fclose(file);
    }
}

void Guardar(HWND padre) {
    OPENFILENAME openfilename;

    TCHAR szFile[MAX_PATH + 1];
    ZeroMemory(szFile, sizeof(szFile));

    ZeroMemory(&openfilename, sizeof(OPENFILENAME));
    openfilename.lStructSize = sizeof(OPENFILENAME);
    openfilename.hwndOwner = padre;
    openfilename.lpstrFile = szFile;
    openfilename.nMaxFile = MAX_PATH;
    openfilename.lpstrFilter = TEXT("All\0 * .*\0Binario (.bin)\0 * .bin\0Texto (.txt)\0 * .txt\0");
    //openfilename.lpstrFilter = TEXT("All\0 * .*\0Text\0 * .txt\0");
    openfilename.nFilterIndex = 1;
    openfilename.lpstrFileTitle = NULL;
    openfilename.nMaxFileTitle = 0;
    openfilename.lpstrInitialDir = NULL;
    openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetSaveFileName(&openfilename))
    {
        write_file(openfilename.lpstrFile);
    }
    else
    {
       // MessageBox(NULL, TEXT("Could not save this file"), TEXT("File I/O Error"), MB_ICONSTOP);
    }
}
//void Guardar(HWND hwnd) {
//    OPENFILENAME ofn;
//
//    TCHAR szFile[MAX_PATH + 1]; //260 caracteres
//
//    ZeroMemory(&ofn, sizeof(ofn));
//
//    ofn.lStructSize = sizeof(OPENFILENAME);
//    ofn.hwndOwner = hwnd;
//    ofn.lpstrFilter = TEXT("All\0 * .*\0Bitmaps\0 * .bmp\0");
//    ofn.lpstrFile = szFile;
//    //ofn.lpstrFile[0] = ‘\0’;
//    ofn.nMaxFile = MAX_PATH;
//    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
//    ofn.nFilterIndex = 2;
//
//    if (GetOpenFileName(&ofn)) {
//        display_file(ofn.lpstrFile);
//    }
//else {
////Si el usuario no seleccionó una imagen, qué se debe de hacer?
//}
//
//}

//Main---------------------------------------------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    wcscpy_s(usu, L"usuario 0");
    wcscpy_s(nomcom, L"Usuario Numero Cero");
    wcscpy_s(cont, L"contrasena 0");
    wcscpy_s(comer, L"comercio 0");
    wcscpy_s(ali, L"Usuario No. 0");
    numcom = 0;
    adm = true;
    newus = false;

    agregar_usuario(lista1, usu, nomcom, cont, comer, ali, numcom, adm, newus);
    setlocale(LC_ALL, "spanish");
    ghDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)WindowProc1);
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
//WindowProc---------------------------------------------------------------------------------------------------------------------
BOOL CALLBACK WindowProc1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   
        switch (uMsg)
        {
        case WM_CREATE:
        case WM_INITDIALOG:
           /* g14 = NULL;
            g15 = NULL;*/
            g1 = NULL;
            g2 = NULL;
            hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
            SetMenu(hwnd, hMenu);
            
            g1 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g1, L"usuario");
                        
            g2 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g2, L"contraseña");

            break;

        case WM_COMMAND:
           
            switch (LOWORD(wParam)) {
            case ID_ARCHIVO_ABRIR:
                Abrir(hwnd);
                break;
            case ID_ARCHIVO_GUARDAR:
                MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
                break;
            case ID_ARCHIVO_GUARDARCOMO:
                Guardar(hwnd);
                break;
            case ID_SALIR_SALIRSINGUARDAR:
                DestroyWindow(hwnd);
                DestroyMenu(hMenu);
                DestroyWindow(ghDlg);
                break;
            case IDC_BUTTON1:
                                         
                GetWindowText(g1, (LPWSTR)usuarioq, sizeof(usuarioq));
                GetWindowText(g2, (LPWSTR)contrasena, sizeof(contrasena));
                wcscpy_s(Usuario, usuarioq);
                wcscpy_s(Contraseña, contrasena);
                UsuValid = false;
                actual = lista1;
                j = 0;
                while ((actual != nullptr) && ((wcscmp(Usuario, actual->nomusuario) != 0) || (wcscmp(Contraseña, actual->contraseña) != 0))) {

                    actual = actual->siguiente;
                    //j++;
                }

                if (actual != nullptr) {
                    UsuValid = true;
                }

                if (UsuValid == true) {
                    if (actual->NewUsuario == true) {
                        DialogBox(NULL, MAKEINTRESOURCE(IDD_DATAUSU), hwnd, (DLGPROC)ActualizarUA);
                        if (regresar == false) {
                            if (adad == true) {
                                MessageBox(hwnd, L"Se le han otorgado permisos de administrador al ser el primer usuario.", L"Aviso", MB_ICONEXCLAMATION);
                                actual->Admin = true;
                                adad = false;
                                Dialog2 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)WindowProc2);
                                ShowWindow(Dialog2, SW_SHOW);
                            }
                        }
                    }
                    /*CAMBIAR TEXTO
                    SetWindowText(h_edit, (LPWSTR)usuario);*/
                    
                }
                
                else if (UsuValid == false) {
                    MessageBox(hwnd, L"Usuario y/o contraseña incorrectos.", L"Aviso", MB_ICONEXCLAMATION);
                }
                break;
            case IDC_BUTTON2:
                
                DialogBox(NULL, MAKEINTRESOURCE(IDD_REGISTRO), hwnd, (DLGPROC)RegistroUsuario);
                
                break;
            case IDC_BUTTON3:
                
             
                DestroyWindow(hwnd);

               
                break;
            

            }
            break;
        case WM_CLOSE:
          
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            return 0;

        case WM_DESTROY:
            
            PostQuitMessage(0);
            break;

        }
   
        return FALSE;
    
}
BOOL CALLBACK WindowProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        hBitmap = (HBITMAP)LoadImage(NULL, L"Perfil.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_STATIC7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
        hPictureControl = GetDlgItem(hwnd, IDC_STATIC7);

        a1 = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(a1, actual->nomusuario);
        a2 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a2, actual->comercio);
        a3 = GetDlgItem(hwnd, IDC_STATIC3);
        if (actual->Admin == true) {
            SetWindowText(a3, L"Admin: Si");
        }
        else {
            SetWindowText(a3, L"Admin: No");
        }
       /* _itow_s(cantus, contador, 200000, 10);
        g1 = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(g1, contador);
        g2 = GetDlgItem(hwnd, IDC_STATIC5);
        _itow_s(cantclien, contador, 200000, 10);
        SetWindowText(g2, contador);
        g3 = GetDlgItem(hwnd, IDC_STATIC6);
        _itow_s(cantprom, contador, 200000, 10);
        SetWindowText(g3, contador);
        g4 = GetDlgItem(hwnd, IDC_STATIC7_);
        _itow_s(cantcons, contador, 200000, 10);
        SetWindowText(g4, contador);
        g5 = GetDlgItem(hwnd, IDC_STATIC8);
        SetWindowText(g5, L"0$");*/
       

        break;

    
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            Abrir(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            Guardar(hwnd);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1:
            //DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)WindowProc2);
            Dialog3 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, (DLGPROC)WindowProc3);
            ShowWindow(Dialog3, SW_SHOW);
            
            SetWindowText(a1, actual->nomusuario);
            
            SetWindowText(a2, actual->comercio);
            
            if (actual->Admin == true) {
                SetWindowText(a3, L"Admin: Si");
            }
            else {
                SetWindowText(a3, L"Admin: No");
            }
            break;
        case IDC_BUTTON2:
            //DialogBox(NULL, MAKEINTRESOURCE(IDD_REGISTRO), hwnd, (DLGPROC)RegistroUsuario);
           /* h_edit = GetDlgItem(hwnd, IDD_DIALOG4);
            SetWindowText(h_edit, L"Menú de clientes");*/
            Dialog4 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)WindowProc4);
            ShowWindow(Dialog4, SW_SHOW);
            break;
        case IDC_BUTTON3:
            Dialog5 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)WindowProc5);
            ShowWindow(Dialog5, SW_SHOW);
            //return 0;
            break;
        case IDC_BUTTON4:
            Dialog6 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)WindowProc6);
            ShowWindow(Dialog6, SW_SHOW);
            break;
        case IDC_BUTTON5:
           
            //ShowWindow(ghDlg, SW_SHOW);
            DestroyWindow(hwnd);
           
           
            
            break;
        case IDC_BUTTON6:
            DeleteObject((HBITMAP)hBitmap);
            EndDialog(hwnd, wParam);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
           
            break;
        case IDC_BUTTON7:
            cantus++;
            cantclien++;
            cantprom++;
            cantcons++;
           /* _itow_s(cantus, contador, 200000, 10);
         
            SetWindowText(g1, contador);
            
            _itow_s(cantclien, contador, 200000, 10);
            SetWindowText(g2, contador);
          
            _itow_s(cantprom, contador, 200000, 10);
            SetWindowText(g3, contador);
        
            _itow_s(cantcons, contador, 200000, 10);
            SetWindowText(g4, contador);*/
       
         
            SetWindowText(g5, L"240$");
            break;

        }
        break;
    case WM_CLOSE:
        
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK WindowProc3(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
       

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            Abrir(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            Guardar(hwnd);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1: //Actualizar Usuario
            
                DialogBox(NULL, MAKEINTRESOURCE(IDD_DATAUSU), hwnd, (DLGPROC)ActualizarUA);
            
            break;
        case IDC_BUTTON2: //Alta de Nuevo Usuario
           if (actual->Admin == true) {
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWUSUARIO), hwnd, (DLGPROC)NuevUsuario);
           }
           else {
               MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONEXCLAMATION);
           }
            break;
        case IDC_BUTTON3: //Listado de Usuarios
            if (actual->Admin == true) {
                
                DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista1);
                if (regresar == false) {
                    DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC), hwnd, (DLGPROC)Actusu);
                }

            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;
        case IDC_BUTTON4: //Restablecer Contraseña
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)ResCon);
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;
        case IDC_BUTTON5:

            DestroyWindow(hwnd);
                        
            break;
        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK WindowProc4(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    /*wchar_t CLASS_NAME[] = L"Menú de clientes";*/
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        
        /*h_edit = GetDlgItem(hwnd, IDD_DIALOG4);
        SetWindowText(h_edit, L"Menú de clientes");*/
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Opciones de clientes>");
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit,L"Seleccione una opción");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit,L"Alta de Clientes");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Listado de Clientes");
        break;


    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ARCHIVO_ABRIR:
            Abrir(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            Guardar(hwnd);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        
        case IDC_BUTTON1: //Alta de clientes
            nuevo = true;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWCLIEN), hwnd, (DLGPROC)NuevCliente);

            break;
        case IDC_BUTTON2: //Listado de clientes
            if (m != 0) {
                nuevo = false;

                DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista2);
                if (regresar == false) {
                    DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC2), hwnd, (DLGPROC)ActClien);
                }
                break;
            }
            else {
                MessageBox(hwnd, L"No hay clientes registrados", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;
        case IDC_BUTTON5:
            DestroyWindow(hwnd);

           
            break;
       
        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK WindowProc5(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Opciones de promociones>");
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Seleccione una opción");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Alta de Promociones");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Listado de Promociones");
       
        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            Abrir(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            Guardar(hwnd);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1:
            nuevo = true;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWPROM), hwnd, (DLGPROC)NuevPromo);

            break;
        case IDC_BUTTON2:
            if (n != 0) {
                nuevo = false;
               
                DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista3);
                if (regresar == false) {
                    DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC3), hwnd, (DLGPROC)ActProm);
                }
            }
            else {
                MessageBox(hwnd, L"No hay promociones registrados", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;
        case IDC_BUTTON5:
            DestroyWindow(hwnd);

            
           
            break;

        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK WindowProc6(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDD_DIALOG4);
        SetWindowText(h_edit, L"Menú de consumos");
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Opciones de consumos>");
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Seleccione una opción");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Alta de Consumos");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Listado de Consumos");
        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            Abrir(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            Guardar(hwnd);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1:
           
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWCONS), hwnd, (DLGPROC)NuevConsumo);
            if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_TOTAL), hwnd, (DLGPROC)Total);
            }
            break;
        case IDC_BUTTON2:
            lista = 4;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista4);
            if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_TOTAL), hwnd, (DLGPROC)Total);
            }
            break;

        case IDC_BUTTON5:
            DestroyWindow(hwnd);

            break;

        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
//Listas--------------------------------------------------------------------------------------------------------------------------
int index;
void listado_usuario(usuarios* lista1) {

    if (lista1 == nullptr) {

    }
    while (lista1 != nullptr) {
        if (actual->numcomer == lista1->numcomer) {
            SendMessage(h_listbox1, LB_ADDSTRING, (WPARAM)0, (LPARAM)lista1->nomusuario);
        }
        lista1 = lista1->siguiente;

    }

}
void listado_clientes(clientes* lista2) {

    if (lista2 == nullptr) {
        SendMessage(h_listbox2, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"No hay clientes para este comercio");
    }
    while (lista2 != nullptr) {
        if (actual->numcomer == lista2->numcomer) {
            SendMessage(h_listbox2, LB_ADDSTRING, (WPARAM)0, (LPARAM)lista2->nomcliente);
        }
        lista2 = lista2->siguiente;

    }

}
void listado_promociones(promociones* lista3) {
    if (lista3 == nullptr) {
        SendMessage(h_listbox3, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"No hay promociones para este comercio");
    }
   
    while (lista3 != nullptr) {
        if (actual->numcomer == lista3->numcomer) {
            SendMessage(h_listbox3, LB_ADDSTRING, (WPARAM)0, (LPARAM)lista3->nompromo);
        }
        lista3 = lista3->siguiente;

    }
    
}
void listado_consumos(consumos* lista4) {
    if (lista4 == nullptr) {
        SendMessage(h_listbox4, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"No hay consumos para este comercio");
    }

    while (lista4 != nullptr) {
        if (actual->numcomer == lista4->numcomer) {
            SendMessage(h_listbox4, LB_ADDSTRING, (WPARAM)0, (LPARAM)lista4->consumo);
        }
        lista4 = lista4->siguiente;

    }

}
BOOL CALLBACK Lista1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        /*if (lista == 1) {*/
            h_edit = GetDlgItem(hwnd, IDC_STATIC1);
            SetWindowText(h_edit, L"<Listado de usuarios>");

            h_edit = GetDlgItem(hwnd, IDC_STATIC2);
            SetWindowText(h_edit, L"Seleccione un usuario");

            h_edit = GetDlgItem(hwnd, IDC_STATIC3);
            SetWindowText(h_edit, actual->comercio);
            h_listbox1 = GetDlgItem(hwnd, IDC_LIST1);
            //SendMessage(h_listbox1, LB_ADDSTRING, (WPARAM)0, (LPARAM)usuario);

            listado_usuario(lista1);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            //usuarios* buscar = new usuarios();
            buscar = lista1;
//            wchar_t Buscar_Usuario[50];
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Buscar_Usuario);
            //GetWindowText(h_listbox1, (LPWSTR)Buscar_Usuario, sizeof(Buscar_Usuario));
            while ((buscar != nullptr) && ((wcscmp(Buscar_Usuario, buscar->nomusuario)!=0) || (actual->numcomer != buscar->numcomer))) {

                buscar = buscar->siguiente;
            }
            //DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC), hwnd, (DLGPROC)Actusu);
            regresar = false;
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);
            break;
           
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
BOOL CALLBACK Lista2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Listado de clientes>");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Seleccione un cliente");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, actual->comercio);
        h_listbox2 = GetDlgItem(hwnd, IDC_LIST1);
        //SendMessage(h_listbox2, LB_ADDSTRING, (WPARAM)0, (LPARAM)cliente);

        listado_clientes(lista2);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
           
            buscar2 = lista2;
            
            wcscpy_s(Buscar_Cliente, L"NULL");
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Buscar_Cliente);
        
            if (wcscmp(Buscar_Cliente, L"No hay clientes para este comercio") == 0) {
                MessageBox(hwnd, L"No hay clientes registrados", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else if (wcscmp(Buscar_Cliente, L"NULL") == 0) {
                MessageBox(hwnd, L"No se seleccionó una opción", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else {
                while ((buscar2 != nullptr) && ((wcscmp(Buscar_Cliente, buscar2->nomcliente) != 0) || (actual->numcomer != buscar2->numcomer))) {

                    buscar2 = buscar2->siguiente;
                }
                regresar = false;
            }
            //DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC), hwnd, (DLGPROC)Actusu);
            
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);
            break;

        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
BOOL CALLBACK Lista3(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Listado de promociones>");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Seleccione una promocion");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, actual->comercio);
        h_listbox3 = GetDlgItem(hwnd, IDC_LIST1);
        //SendMessage(h_listbox2, LB_ADDSTRING, (WPARAM)0, (LPARAM)cliente);

        listado_promociones(lista3);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            buscar3 = lista3;
            wcscpy_s(Buscar_Promo, L"NULL");
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Buscar_Promo);
            
            if (wcscmp(Buscar_Promo, L"No hay promociones para este comercio") == 0) {
                MessageBox(hwnd, L"No hay promociones registradas", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else if (wcscmp(Buscar_Promo, L"NULL") == 0) {
                MessageBox(hwnd, L"No se seleccionó una opción", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else {
                while ((buscar3 != nullptr) && ((wcscmp(Buscar_Promo, buscar3->nompromo) != 0) || (actual->numcomer != buscar3->numcomer))) {

                    buscar3 = buscar3->siguiente;
                }
                regresar = false;
            }
            //DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC), hwnd, (DLGPROC)Actusu);

            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);
            break;

        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
BOOL CALLBACK Lista4(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Listado de consumos>");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Seleccione un consumo");
        
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Comercio: #");
        h_combobox = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)consumoq);

        listado_consumos(lista4);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            EndDialog(hwnd, wParam);
            break;

        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
//Usuarios------------------------------------------------------------------------------------------------------------------------
void agregar_usuario(usuarios*& lista1, wchar_t usu[50], wchar_t nomcom[50], wchar_t cont[50], wchar_t comer[50], wchar_t ali[50], int numcom, bool adm, bool newus) {

    usuarios* nuevo_usuario = new usuarios();
    usuarios* aux;
    wcscpy_s(nuevo_usuario->nomusuario, usu);
    wcscpy_s(nuevo_usuario->nombrecom, nomcom);
    wcscpy_s(nuevo_usuario->contraseña, cont);
    wcscpy_s(nuevo_usuario->comercio, comer);
    wcscpy_s(nuevo_usuario->alias, ali);
    nuevo_usuario->numcomer = numcom;
    nuevo_usuario->Admin = adm;
    nuevo_usuario->NewUsuario = newus;
    nuevo_usuario->siguiente = nullptr;

    if (lista1 == nullptr) {  //si la lista esta vacia
        lista1 = nuevo_usuario;  //agregamos el primer elemento a la lista
    }
    else {
        aux = lista1;  //aux apunta al inicio de la lista

        while (aux->siguiente != nullptr) {  //recorrer la lista
            aux = aux->siguiente;  //avanzamos posiciones en la lista
        }
        aux->siguiente = nuevo_usuario;  //se agrega el nuevo nodo a la lista
    }
    // MessageBox(hwnd, L"Usuario registrado", L"Aviso", MB_ICONEXCLAMATION);
    // cout << "\n>Usuario registrado" << endl;
    k++;
}
void borrar_usuario(usuarios*& lista1, wchar_t Buscar_Usuario[50]) {

    usuarios* aux_borrar;
    usuarios* anterior = nullptr;
    aux_borrar = lista1;


    while ((aux_borrar != nullptr) && ((wcscmp(Buscar_Usuario, aux_borrar->nomusuario) != 0) || (actual->numcomer != aux_borrar->numcomer))) {

        anterior = aux_borrar;
        aux_borrar = aux_borrar->siguiente;
    }

    if (aux_borrar == nullptr) { //El elemento no ha sido encontrado
        // cout << endl << ">Usuario no encontrada" << endl;
    }
    else if (anterior == nullptr) {  //El elemento a eliminar es el primero

        lista1 = lista1->siguiente;
        delete aux_borrar;
        //cout << endl << ">Usuario eliminado" << endl;
    }
    else {  //El elemento a eliminar no es el primero
        anterior->siguiente = aux_borrar->siguiente;
        delete aux_borrar;
        //cout << endl << ">Usuario eliminado" << endl;
    }
    k--;
}

BOOL CALLBACK RegistroUsuario(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo usuario");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese nueva contraseña");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese nuevo comercio");

        g3 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g3,L"usuario");

        g4 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g4, L"contraseña");

        g5 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g5, L"Comercio");
        /*g1 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(g1, usuario);*/
        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g3, (LPWSTR)usu, sizeof(usu));
            GetWindowText(g4, (LPWSTR)cont, sizeof(cont));
            GetWindowText(g5, (LPWSTR)comer, sizeof(comer));
            wcscpy_s(nomcom, L"{PENDIENTE}");
            wcscpy_s(ali, L"{PENDIENTE}");
            newus = true;
            adm = false;

            actual = lista1;
            comernew = false;
            while ((actual != nullptr) && (wcscmp(comer,actual->comercio) != 0)) {

                actual = actual->siguiente;

            }

            if (actual == nullptr) {
                comernew = true;
            }
            if (comernew == false) {
                numcom = actual->numcomer;
            }
            else {
                l++;
                numcom = l;
            }
            newus = true;
            agregar_usuario(lista1, usu, nomcom, cont, comer, ali, numcom, adm, newus);
            //DestroyWindow(hwnd);
            EndDialog(hwnd, wParam);
           
            break;
        case IDC_BUTTON2:
           
            //DestroyWindow(hwnd);
            EndDialog(hwnd, wParam);
            //ShowWindow(ghDlg, SW_SHOW);
            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);
        
        break;

    

    }

    return FALSE;
}
BOOL CALLBACK ActualizarUA(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo nombre completo");
       
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese nuevo alias");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese nueva foto de usuario");

        g6 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g6, L"nombre completo");

        g7 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g7, L"alias");

       /* g3 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g3, L"{PENDIENTE}");*/

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g6, (LPWSTR)nombre, sizeof(nombre));
            GetWindowText(g7, (LPWSTR)alias, sizeof(alias));
            wcscpy_s(actual->nombrecom, nombre);
            wcscpy_s(actual->alias, alias);
            actual->NewUsuario = false;
            regresar = false;
            //GetWindowText(g1, (LPWSTR)usuario, sizeof(usuario));
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON3:
            Abrir(hwnd);
            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

   

    }

    return FALSE;
}
BOOL CALLBACK NuevUsuario(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo usuario");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese contraseña");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Establesca administrador");

        g8 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g8, L"usuario");

        g9 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g9, L"contrasena");

        g10 = GetDlgItem(hwnd, IDC_CHECK1);
        SetWindowText(g10, L"Admin");

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g8, (LPWSTR)usu, sizeof(usu));
            GetWindowText(g9, (LPWSTR)cont, sizeof(cont));
            wcscpy_s(comer, actual->comercio);
            wcscpy_s(nomcom, L"{PENDIENTE}");
            wcscpy_s(ali, L"{PENDIENTE}");
            numcom = actual->numcomer;
            IsDlgButtonChecked(hwnd, IDC_CHECK1);

            if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                adm = true;
            }
            else if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                adm = false;
            }
            newus = true;
            agregar_usuario(lista1, usu, nomcom, cont, comer, ali, numcom, adm, newus);
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            EndDialog(hwnd, wParam);
            break;
            //return TRUE;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
BOOL CALLBACK ResConAct(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, contrasena);


        g11 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g11, L"nueva contraseña");

        

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g11, (LPWSTR)contrasena, sizeof(contrasena));
            wcscpy_s(actual->contraseña, contrasena);
            regresar = false;
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);

            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
BOOL CALLBACK ResConAct2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, contrasena);


        g23 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g23, L"nueva contraseña");



        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g23, (LPWSTR)contrasena, sizeof(contrasena));
            wcscpy_s(buscar->contraseña, contrasena);
            regresar = false;
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);

            break;
        }
        break;
    case WM_CLOSE:
        EndDialog(hwnd, wParam);

        //EndDialog(ghDlg, wParam);
        break;

    }

    return FALSE;
}
BOOL CALLBACK Actusu(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:
        hBitmap = (HBITMAP)LoadImage(NULL, L"Perfil.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_STATIC7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
        hPictureControl = GetDlgItem(hwnd, IDC_STATIC7);

        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Actualizar usuario");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Eliminar usuario");
        a4 = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(a4, buscar->nomusuario);
        a5 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a5, buscar->nombrecom);
        a6 = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(a6, buscar->alias);
        a7 = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(a7, buscar->comercio);
        a8 = GetDlgItem(hwnd, IDC_STATIC5);
        if (buscar->Admin == true) {
            SetWindowText(a8, L"Admin: Si");
        }
        else {
            SetWindowText(a8, L"Admin: No");
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case IDC_BUTTON1:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_ACTUS), hwnd, (DLGPROC)ActusuB1);
            //CloseWindow(hwnd);
            
            SetWindowText(a4, buscar->nomusuario);
           
            SetWindowText(a5, buscar->nombrecom);
            
            SetWindowText(a6, buscar->alias);
           
            SetWindowText(a7, buscar->comercio);
            
            if (buscar->Admin == true) {
                SetWindowText(a8, L"Admin: Si");
            }
            else {
                SetWindowText(a8, L"Admin: No");
            }
            break;
        case IDC_BUTTON2:
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
                if (confirmar == true) {
                    if (wcscmp(actual->nomusuario, Buscar_Usuario) == 0) {
                        MessageBox(hwnd, L"No puede eliminar el usuario actual", L"Aviso", MB_ICONEXCLAMATION);
                    }
                    else {
                        borrar_usuario(lista1, Buscar_Usuario);
                        MessageBox(hwnd, L"Usuario Eliminado", L"Eliminar usuario", MB_ICONEXCLAMATION);
                        EndDialog(hwnd, wParam);
                    }
                }
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONEXCLAMATION);
            }
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap);
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}
BOOL CALLBACK ActusuB1(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:
        /* hBitmap = (HBITMAP)LoadImage(NULL, L"Perfil.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
         SendDlgItemMessage(hwnd, IDC_STATIC7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
         hPictureControl = GetDlgItem(hwnd, IDC_STATIC7);*/
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo usuario");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese nuevo nombre completo");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese nuevo alias");

        h_edit = GetDlgItem(hwnd, IDC_CHECK1);
        SetWindowText(h_edit, L"Administrador:");
        if (actual->Admin) {
            SendDlgItemMessage(hwnd, IDC_CHECK1, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
        }
        else {
            SendDlgItemMessage(hwnd, IDC_CHECK1, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
        }
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Ingrese nueva foto de usuario");

        g12 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g12, buscar->nomusuario);

        g13 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g13, buscar->nombrecom);

        g14 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g14, buscar->alias);

        

        break;
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case IDC_BUTTON1:

            GetWindowText(g12, (LPWSTR)usuarioq, sizeof(usuarioq));
            GetWindowText(g13, (LPWSTR)nombre, sizeof(nombre));
            GetWindowText(g14, (LPWSTR)alias, sizeof(alias));
            
            wcscpy_s(buscar->nomusuario, usuarioq);
            wcscpy_s(buscar->nombrecom, nombre);
            wcscpy_s(buscar->alias, alias);

            EndDialog(hwnd, wParam);
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON2:

            EndDialog(hwnd, wParam);
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON3:
            Abrir(hwnd);
            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap);
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}
BOOL CALLBACK ResCon(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        /*h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"<Opciones de clientes>");*/
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Seleccione una opción");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Restablecer mi contrasena");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Restablecer otro usuario");
        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1:
          
            DialogBox(NULL, MAKEINTRESOURCE(IDD_RESTABLECER), hwnd, (DLGPROC)ResConAct);

            break;
        case IDC_BUTTON2:
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista1);
                //regresar = false;
                if (regresar == false) {
                    DialogBox(NULL, MAKEINTRESOURCE(IDD_RESTABLECER), hwnd, (DLGPROC)ResConAct2);
                }
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;

        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);
        

        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}

//Clientes------------------------------------------------------------------------------------------------------------------------
void agregar_cliente(clientes*& lista2, wchar_t nomclien[50], wchar_t alic[50], wchar_t tel[50], wchar_t ema[50], wchar_t comerc[50], wchar_t fech[50], int numcomc) {

    clientes* nuevo_cliente = new clientes();
    clientes* aux;

    wcscpy_s(nuevo_cliente->nomcliente, nomclien);
    wcscpy_s(nuevo_cliente->alias, alic);
    wcscpy_s(nuevo_cliente->telefono, tel);
    wcscpy_s(nuevo_cliente->email, ema);
    wcscpy_s(nuevo_cliente->comercio, comerc);
    wcscpy_s(nuevo_cliente->fecha, fech);
    nuevo_cliente->numcomer = numcomc;
    nuevo_cliente->siguiente = nullptr;

    if (lista2 == nullptr) {  //si la lista esta vacia
        lista2 = nuevo_cliente;  //agregamos el primer elemento a la lista
    }
    else {
        aux = lista2;  //aux apunta al inicio de la lista

        while (aux->siguiente != nullptr) {  //recorrer la lista
            aux = aux->siguiente;  //avanzamos posiciones en la lista
        }
        aux->siguiente = nuevo_cliente;  //se agrega el nuevo nodo a la lista
    }
    m++;
}
void borrar_cliente(clientes*& lista2, wchar_t Buscar_Cliente[50]) {

    clientes* aux_borrar;
    clientes* anterior = nullptr;
    aux_borrar = lista2;

    while ((aux_borrar != nullptr) && ((wcscmp(Buscar_Cliente, aux_borrar->nomcliente) != 0) || (actual->numcomer != aux_borrar->numcomer))) { //recorrer la lista

        anterior = aux_borrar;
        aux_borrar = aux_borrar->siguiente;
    }

    if (aux_borrar == nullptr) { //El elemento no ha sido encontrado
        //cout << endl << ">Cliente no encontrado" << endl;
    }
    else if (anterior == nullptr) {  //El elemento a eliminar es el primero

        lista2 = lista2->siguiente;
        delete aux_borrar;
       // cout << endl << ">Cliente eliminado" << endl;
    }
    else {  //El elemento a eliminar no es el primero
        anterior->siguiente = aux_borrar->siguiente;
        delete aux_borrar;
       // cout << endl << ">Cliente eliminado" << endl;
    }
   // system("pause");
    m--;
}
BOOL CALLBACK NuevCliente(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo cliente");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese alias");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese telefono");

        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Ingrese correo electronico");
           
        h_edit = GetDlgItem(hwnd, IDC_STATIC6);
        SetWindowText(h_edit, L"Ahora");
        
        if (nuevo == true) {
            g15 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g15, L"nuevo cliente");
            g16 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g16, L"alias");
            g17 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g17, L"telefono");
            g18 = GetDlgItem(hwnd, IDC_EDIT4);
            SetWindowText(g18, L"correo");
           
            break;
        }
        else {
            g15 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g15, buscar2->nomcliente);
            g16 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g16, buscar2->alias);
            g17 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g17, buscar2->telefono);
            g18 = GetDlgItem(hwnd, IDC_EDIT4);
            SetWindowText(g18, buscar2->email);
        }


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            /*case ID_ARCHIVO_GUARDAR:
                MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
                break;
            case ID_ARCHIVO_GUARDARCOMO:
                MessageBox(hwnd, L"mensaje", L"ttulo", MB_ICONEXCLAMATION);
                break;*/
        case IDC_BUTTON1:
            if (nuevo == true) {
                GetWindowText(g15, (LPWSTR)nomclien, sizeof(nomclien));
                GetWindowText(g16, (LPWSTR)alic, sizeof(alic));
                GetWindowText(g17, (LPWSTR)tel, sizeof(tel));
                GetWindowText(g18, (LPWSTR)ema, sizeof(ema));
                wcscpy_s(fecha, L"Ahora");
                wcscpy_s(comerc, actual->comercio);
                numcomc = actual->numcomer;

                agregar_cliente(lista2, nomclien, alic, tel, ema, comerc, fech, numcomc);
                MessageBox(hwnd, L"Cliente Registrado", L"Registrar cliente", MB_ICONEXCLAMATION);
            }
            else {
                GetWindowText(g15, (LPWSTR)nomclien, sizeof(nomclien));
                GetWindowText(g16, (LPWSTR)alic, sizeof(alic));
                GetWindowText(g17, (LPWSTR)tel, sizeof(tel));
                GetWindowText(g18, (LPWSTR)ema, sizeof(ema));
                wcscpy_s(fecha, L"Ahora");
                wcscpy_s(comerc, actual->comercio);

                wcscpy_s(buscar2->nomcliente, nomclien);
                wcscpy_s(buscar2->alias, alic);
                wcscpy_s(buscar2->telefono, tel);
                wcscpy_s(buscar2->email, ema);
                wcscpy_s(buscar2->comercio, comerc);
                wcscpy_s(buscar2->fecha, fech);
                buscar2->numcomer = actual->numcomer;
                MessageBox(hwnd, L"Cliente Actualizado", L"Actualizar cliente", MB_ICONEXCLAMATION);                
            }
            EndDialog(hwnd, wParam);

            break;
        case IDC_BUTTON2:
          
            EndDialog(hwnd, wParam);
            break;

        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK ActClien(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:
        

        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Actualizar cliente");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Eliminar cliente");
        a9 = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(a9, buscar2->nomcliente);
        a10 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a10, buscar2->alias);
        a11 = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(a11, buscar2->comercio);
        a12 = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(a12, buscar2->email);
        a13 = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(a13, buscar2->telefono);
        a14 = GetDlgItem(hwnd, IDC_STATIC6);
        SetWindowText(a14, buscar2->fecha);

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case IDC_BUTTON1:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWCLIEN), hwnd, (DLGPROC)NuevCliente);
            //CloseWindow(hwnd);
            
            SetWindowText(a9, buscar2->nomcliente);
            
            SetWindowText(a10, buscar2->alias);
            
            SetWindowText(a11, buscar2->comercio);
            
            SetWindowText(a12, buscar2->email);
            
            SetWindowText(a13, buscar2->telefono);
           
            SetWindowText(a14, buscar2->fecha);

            break;
        case IDC_BUTTON2:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
            if (confirmar == true) {
                borrar_cliente(lista2, Buscar_Cliente);
                MessageBox(hwnd, L"Cliente Eliminado", L"Eliminar cliente", MB_ICONEXCLAMATION);
                EndDialog(hwnd, wParam);
            }
            
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap);
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}

//Promociones---------------------------------------------------------------------------------------------------------------------
void agregar_promo(promociones*& lista3, wchar_t promo[50], wchar_t date[50], float cant, float por, bool act, int numcomp) {

    promociones* nueva_promo = new promociones();
    promociones* aux;

    wcscpy_s(nueva_promo->nompromo, promo); 
    wcscpy_s(nueva_promo->fecha, date);
    nueva_promo->cantidad = cant;
    nueva_promo->porcentaje = por;
    nueva_promo->activo = act;
    nueva_promo->numcomer = numcomp;
    nueva_promo->siguiente = nullptr;

    if (lista3 == nullptr) {  //si la lista esta vacia
        lista3 = nueva_promo;  //agregamos el primer elemento a la lista
    }
    else {
        aux = lista3;  //aux apunta al inicio de la lista

        while (aux->siguiente != nullptr) {  //recorrer la lista
            aux = aux->siguiente;  //avanzamos posiciones en la lista
        }
        aux->siguiente = nueva_promo;  //se agrega el nuevo nodo a la lista
    }
    //cout << "\n>Promocion registrada" << endl;
    n++;
}

void borrar_promo(promociones*& lista3, wchar_t Buscar_Promo[50]) {

    promociones* aux_borrar;
    promociones* anterior = nullptr;
    aux_borrar = lista3;

    while ((aux_borrar != nullptr) && ((wcscmp(Buscar_Promo, aux_borrar->nompromo) != 0) || (actual->numcomer != aux_borrar->numcomer))) {
         //recorrer la lista

        anterior = aux_borrar;
        aux_borrar = aux_borrar->siguiente;
    }

    if (aux_borrar == nullptr) { //El elemento no ha sido encontrado
        //cout << endl << ">Promocion no encontrada" << endl;
    }
    else if (anterior == nullptr) {  //El elemento a eliminar es el primero

        lista3 = lista3->siguiente;
        delete aux_borrar;
       // cout << endl << ">Promocion eliminada" << endl;
    }
    else {  //El elemento a eliminar no es el primero
        anterior->siguiente = aux_borrar->siguiente;
        delete aux_borrar;
       // cout << endl << ">Promocion eliminada" << endl;
    }
    
    n--;
}
BOOL CALLBACK NuevPromo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese el nombre");
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese el monto");
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese el porcentaje");
        h_edit = GetDlgItem(hwnd, IDC_CHECK1);
        SetWindowText(h_edit, L"Promocion activa");
        if (buscar3->activo == true) {
            SendDlgItemMessage(hwnd, IDC_CHECK1, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
        }
        else {
            SendDlgItemMessage(hwnd, IDC_CHECK1, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
        }
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, L"Ahora");

        if (nuevo == true) {
            g19 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g19, L"nueva promocion");
            g20 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g20, L"nuevo monto");
            g21 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g21, L"nuevo porcentaje");
            
            break;
        }
        else {
            wchar_t dummy[60];
            
            g19 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g19, buscar3->nompromo);
            g20 = GetDlgItem(hwnd, IDC_EDIT2);
            _itow_s(buscar3->cantidad, dummy, 60, 10);
            SetWindowText(g20, dummy);
            g21 = GetDlgItem(hwnd, IDC_EDIT3);
            _itow_s(buscar3->porcentaje, dummy, 60, 10);
            SetWindowText(g21, dummy);
            
        }


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
            /*case ID_ARCHIVO_GUARDAR:
                MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
                break;
            case ID_ARCHIVO_GUARDARCOMO:
                MessageBox(hwnd, L"mensaje", L"ttulo", MB_ICONEXCLAMATION);
                break;*/
        case IDC_BUTTON1:
            if (nuevo == true) {
                GetWindowText(g19, (LPWSTR)promo, sizeof(promo));
                GetWindowText(g20, (LPWSTR)monto, sizeof(monto));
                GetWindowText(g21, (LPWSTR)porcentaje, sizeof(porcentaje));
                wcscpy_s(date, L"Ahora");
                cant = _wtof(monto);
                por = _wtof(porcentaje);
                IsDlgButtonChecked(hwnd, IDC_CHECK1);
                numcomp = actual->numcomer;

                if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    act = true;
                }
                else if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                    act = false;
                }
                

                agregar_promo(lista3, promo, date, cant, por, act, numcomp);
                MessageBox(hwnd, L"Promocion Registrada", L"Registrar promocion", MB_ICONEXCLAMATION);
            }
            else {
                GetWindowText(g19, (LPWSTR)promo, sizeof(promo));
                GetWindowText(g20, (LPWSTR)monto, sizeof(monto));
                GetWindowText(g21, (LPWSTR)porcentaje, sizeof(porcentaje));
                wcscpy_s(date, L"Ahora");
                buscar3->cantidad = _wtof(monto);
                buscar3->porcentaje = _wtof(porcentaje);
                IsDlgButtonChecked(hwnd, IDC_CHECK1);
                if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                    buscar3->activo = true;
                }
                else if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                    buscar3->activo = false;
                }
                wcscpy_s(buscar3->nompromo, promo);
                wcscpy_s(buscar3->fecha, date);
                buscar3->numcomer = actual->numcomer;
               
                MessageBox(hwnd, L"Promocion Actualizada", L"Actualizar promocion", MB_ICONEXCLAMATION);
            }
            EndDialog(hwnd, wParam);

            break;
        case IDC_BUTTON2:

            EndDialog(hwnd, wParam);
            break;

        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK ActProm(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:
        wchar_t dummy[60];

        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Actualizar promocion");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Eliminar promocion");
        a15 = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(a15, buscar3->nompromo);
        a16 = GetDlgItem(hwnd, IDC_STATIC2);
        _itow_s(buscar3->cantidad, dummy, 60, 10);
        SetWindowText(a16, dummy);
        a17 = GetDlgItem(hwnd, IDC_STATIC3);
        _itow_s(buscar3->porcentaje, dummy, 60, 10);
        SetWindowText(a17, dummy);
        a18 = GetDlgItem(hwnd, IDC_STATIC4);
        if (buscar3->activo == true) {
            SetWindowText(a18, L"Si");
        }
        else {
            SetWindowText(a18, L"No");
        }
        a19 = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(a19, buscar3->fecha);

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case IDC_BUTTON1:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWPROM), hwnd, (DLGPROC)NuevPromo);
            //CloseWindow(hwnd);
            
            SetWindowText(a15, buscar3->nompromo);
            
            _itow_s(buscar3->cantidad, dummy, 60, 10);
            SetWindowText(a16, dummy);
           
            _itow_s(buscar3->porcentaje, dummy, 60, 10);
            SetWindowText(a17, dummy);
           
            if (buscar3->activo == true) {
                SetWindowText(a18, L"Si");
            }
            else {
                SetWindowText(a18, L"No");
            }
            
            SetWindowText(a19, buscar3->fecha);
            break;
        case IDC_BUTTON2:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
            if (confirmar == true) {
                borrar_promo(lista3, Buscar_Promo);
                MessageBox(hwnd, L"Promocion Eliminada", L"Eliminar promocion", MB_ICONEXCLAMATION);
                EndDialog(hwnd, wParam);
            }
            
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap);
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}
//Consumos------------------------------------------------------------------------------------------------------------------------
void agregar_comsumo(consumos*& lista4, wchar_t cons[50], wchar_t datec[50], int mont, int sub, int desc, int tot, int numcomco) {

    consumos* nuevo_consumo = new consumos();
    consumos* aux;

    wcscpy_s(nuevo_consumo->consumo, cons);
    wcscpy_s(nuevo_consumo->fecha, datec);
    nuevo_consumo->monto = mont;
    nuevo_consumo->subtotal = sub;
    nuevo_consumo->descuento = desc;
    nuevo_consumo->total = tot;
    nuevo_consumo->numcomer = numcomco;
    nuevo_consumo->siguiente = nullptr;

    if (lista4 == nullptr) {  //si la lista esta vacia
        lista4 = nuevo_consumo;  //agregamos el primer elemento a la lista
    }
    else {
        aux = lista4;  //aux apunta al inicio de la lista

        while (aux->siguiente != nullptr) {  //recorrer la lista
            aux = aux->siguiente;  //avanzamos posiciones en la lista
        }
        aux->siguiente = nuevo_consumo;  //se agrega el nuevo nodo a la lista
    }
    //cout << "\n>Promocion registrada" << endl;
    ñ++;
}

void borrar_consumo(consumos*& lista4, wchar_t Buscar_Consumo[50]) {

    consumos* aux_borrar;
    consumos* anterior = nullptr;
    aux_borrar = lista4;

    while ((aux_borrar != nullptr) && ((wcscmp(Buscar_Consumo, aux_borrar->consumo) != 0) || (actual->numcomer != aux_borrar->numcomer))) {
        //recorrer la lista

        anterior = aux_borrar;
        aux_borrar = aux_borrar->siguiente;
    }

    if (aux_borrar == nullptr) { //El elemento no ha sido encontrado
        //cout << endl << ">Promocion no encontrada" << endl;
    }
    else if (anterior == nullptr) {  //El elemento a eliminar es el primero

        lista4 = lista4->siguiente;
        delete aux_borrar;
        // cout << endl << ">Promocion eliminada" << endl;
    }
    else {  //El elemento a eliminar no es el primero
        anterior->siguiente = aux_borrar->siguiente;
        delete aux_borrar;
        // cout << endl << ">Promocion eliminada" << endl;
    }

    ñ--;
}
BOOL CALLBACK NuevConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        g22 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g22, L"monto");
        h_listbox2 = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(h_listbox2, LB_ADDSTRING, (WPARAM)0, (LPARAM)consumoq);

        listado_clientes(lista2);


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
           
        case IDC_BUTTON1:
            regresar = false;
            wcscpy_s(consumoq, L"orden0");
            wcscpy_s(fechacons, L"Ahora");
            wcscpy_s(subtotal, L"300$");
            wcscpy_s(descuento, porcentaje);
            wcscat_s(descuento, L"%");
            wcscpy_s(total, L"240$");

            GetWindowText(g22, (LPWSTR)montocons, sizeof(montocons));
           
            EndDialog(hwnd, wParam);

            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);
            break;

        }
        break;
    case WM_CLOSE:

        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;

    }

    return FALSE;
}
BOOL CALLBACK ActCons(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:


        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Actualizar ");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Eliminar promocion");
        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(h_edit, promocionq);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, monto);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, porcentaje);
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, activa);
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, fecha);

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_GUARDAR:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
            break;
        case IDC_BUTTON1:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWPROM), hwnd, (DLGPROC)NuevPromo);
            //CloseWindow(hwnd);
           
            break;
        case IDC_BUTTON2:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
            if (confirmar == true) {
                MessageBox(hwnd, L"Promocion Eliminada", L"Eliminar promocion", MB_ICONEXCLAMATION);
                EndDialog(hwnd, wParam);
            }
            
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap);
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}
BOOL CALLBACK Total(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:


        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(h_edit, consumoq);
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, fechacons);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, subtotal);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, descuento);
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, total);
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, clienteq);
      

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
      
        case IDC_BUTTON1:
            
            EndDialog(hwnd, wParam);

            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        
        EndDialog(hwnd, wParam);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}

BOOL CALLBACK Confirmar(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:

        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Está seguro que quiere realizar esta acción?");
        
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {

        case IDC_BUTTON1:
            confirmar = true;
            EndDialog(hwnd, wParam);

            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON2:
            confirmar = false;
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:

        EndDialog(hwnd, wParam);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}
