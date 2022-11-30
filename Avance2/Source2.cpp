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
HWND g1, g2, g3, g4, g5;
HWND h_combobox;
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
    bool Admin = 0;
    bool NewUsuario;

    usuarios* siguiente;
};
struct clientes {
    string nomcliente;
    string alias;
    string telefono;
    string email;
    string comercio;
    string fecha;
    int numcomer;

    clientes* siguiente;
};
struct promociones {
    string nompromo;
    float cantidad = 0;
    float porcentaje = 0;
    bool activo;
    string fecha;
    int numcomer;
    promociones* siguiente;
};
struct consumos {
    //{PENDIENTE}
};


struct nodo {
    string dato1 = 0;
    int dato2 = 0;
    nodo* siguiente;
};


usuarios usuario[100];
clientes cliente[200];

usuarios* lista1 = NULL;
clientes* lista2 = NULL;
promociones* lista3 = NULL;


usuarios* actual = nullptr;

char menu0, menu1, menu2, menu3, sinoadmin, sinoactivo;
bool UsuValid, adminuevusu;
int i = 0;
//j = usuario actual
int j = 0;
//k = numero de usuarios
int k = 0;
//l = numero de comercios
int l = 0;
//m = numero de clientes
int m = 0;

int n = 0;
wchar_t Usuario[50], Contraseña[50], Comercio[50];// , UsuariosBin;
float producto;
//Lista ligada Usuarios
wchar_t usu[50], nomcom[50], cont[50], comer[50], ali[50]; int numcom; bool adm, newus;
//Lista Ligada Clientes
string nomclien, alic, tel, ema, comerc, fech; int numcomc;
//Lista ligada Promociones
string promo, date; float cant, por; bool act; int numcomp;

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
               
                         
                         
                         
                GetWindowText(g1, (LPWSTR)Usuario, sizeof(Usuario));
                GetWindowText(g2, (LPWSTR)Contraseña, sizeof(Contraseña));
                UsuValid = true;
                actual = lista1;
                j = 0;
                while ((actual != nullptr) && ((Usuario != actual->nomusuario) || (Contraseña != actual->contraseña))) {

                    actual = actual->siguiente;
                    j++;
                }

                if (actual != nullptr) {
                    UsuValid = true;
                }

                if (UsuValid == true) {
                    if (newus == true) {
                        DialogBox(NULL, MAKEINTRESOURCE(IDD_DATAUSU), hwnd, (DLGPROC)ActualizarUA);
                        //MessageBox(hwnd, L"Se le han otorgado permisos de administrador al ser el primer usuario.", L"Aviso", MB_ICONEXCLAMATION);
                    }
                    /*CAMBIAR TEXTO
                    SetWindowText(h_edit, (LPWSTR)usuario);*/
                    Dialog2 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)WindowProc2);
                    ShowWindow(Dialog2, SW_SHOW);
                }
                else {
                    MessageBox(hwnd, L"Usuario y/o contraseña incorrectos.", L"Aviso", MB_ICONEXCLAMATION);
                }
                break;
            case IDC_BUTTON2:
                nuevous = true;
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

        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, usuarioq);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, comercio);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Admin: Si");

        _itow_s(cantus, contador, 200000, 10);
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
        SetWindowText(g5, L"0$");
       

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
            _itow_s(cantus, contador, 200000, 10);
         
            SetWindowText(g1, contador);
            
            _itow_s(cantclien, contador, 200000, 10);
            SetWindowText(g2, contador);
          
            _itow_s(cantprom, contador, 200000, 10);
            SetWindowText(g3, contador);
        
            _itow_s(cantcons, contador, 200000, 10);
            SetWindowText(g4, contador);
       
         
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
        case IDC_BUTTON1:
            
            //CloseWindow(hwnd);
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DATAUSU), hwnd, (DLGPROC)ActualizarUA);
            break;
        case IDC_BUTTON2:
           
            //CloseWindow(hwnd);
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWUSUARIO), hwnd, (DLGPROC)NuevUsuario);
            break;
        case IDC_BUTTON3:
            lista = 1;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista1);
             if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC), hwnd, (DLGPROC)Actusu);
            }//return 0;
            break;
        case IDC_BUTTON4:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)ResCon);
           
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
        
        case IDC_BUTTON1:
            nuevo = true;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWCLIEN), hwnd, (DLGPROC)NuevCliente);

            break;
        case IDC_BUTTON2:
            nuevo = false;
            lista = 2;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista2);
            if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC2), hwnd, (DLGPROC)ActClien);
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
            nuevo = false;
            lista = 3;
            DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista3);
            if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC3), hwnd, (DLGPROC)ActProm);
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
            SetWindowText(h_edit, L"Comercio: #");
            h_combobox = GetDlgItem(hwnd, IDC_LIST1);
            SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)usuario);
         
            wchar_t j[2];
            wchar_t dummy[60];
            ZeroMemory(dummy, 120);
            for (int i = 1; i <= 5; i++) {
                wcscpy_s(dummy,L"usuario");
                _itow_s(i, j,2,10);
                wcscat_s(dummy, j);
                SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)dummy);
            }
        //else if (lista == 2) {
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        //    SetWindowText(h_edit, L"<Listado de clientes>");
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        //    SetWindowText(h_edit, L"Seleccione un cliente");
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        //    SetWindowText(h_edit, L"Comercio: #");
        //    h_combobox = GetDlgItem(hwnd, IDC_COMBO1);
        //    SendMessage(h_combobox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Cliente");
        //}
        //else if (lista == 3) {
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        //    SetWindowText(h_edit, L"<Listado de promociones>");
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        //    SetWindowText(h_edit, L"Seleccione una promocion");
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        //    SetWindowText(h_edit, L"Comercio: #");
        //    h_combobox = GetDlgItem(hwnd, IDC_COMBO1);
        //    SendMessage(h_combobox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Promocion");
        //}
        //else if (lista == 4) {
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        //    SetWindowText(h_edit, L"<Listado de consumos>");
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        //    SetWindowText(h_edit, L"Seleccione un consumo");
        //    int i = 1;
        //    h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        //    SetWindowText(h_edit, L"Comercio: #");
        //    //SetWindowText(h_edit, L i);
        //    h_combobox = GetDlgItem(hwnd, IDC_COMBO1);
        //    SendMessage(h_combobox, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Consumo");

        

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
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
        SetWindowText(h_edit, L"Comercio: #");
        h_combobox = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)cliente);

        wchar_t j[2];
        wchar_t dummy[60];
        ZeroMemory(dummy, 120);
        for (int i = 1; i <= 5; i++) {
            wcscpy_s(dummy, L"cliente");
            _itow_s(i, j, 2, 10);
            wcscat_s(dummy, j);
            SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)dummy);
        }

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
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
        SetWindowText(h_edit, L"Comercio: #");
        h_combobox = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"Promocion");

        wchar_t j[2];
        wchar_t dummy[60];
        ZeroMemory(dummy, 120);
        for (int i = 1; i <= 5; i++) {
            wcscpy_s(dummy, L"promocion");
            _itow_s(i, j, 2, 10);
            wcscat_s(dummy, j);
            SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)dummy);
        }

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
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

        wchar_t j[2];
        wchar_t dummy[60];
        ZeroMemory(dummy, 120);
        for (int i = 1; i <= 5; i++) {
            wcscpy_s(dummy, L"orden");
            _itow_s(i, j, 2, 10);
            wcscat_s(dummy, j);
            SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)dummy);
        }

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

        g1 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g1,L"usuario");

        g2 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g2, L"contraseña");

        g3 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g3, L"Comercio");
        /*g1 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(g1, usuario);*/
        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g1, (LPWSTR)usu, sizeof(usu));
            GetWindowText(g2, (LPWSTR)cont, sizeof(cont));
            GetWindowText(g3, (LPWSTR)comer, sizeof(comer));
            /* wcscpy_s(nomcom, L"{PENDIENTE}");
             wcscpy_s(ali, L"{PENDIENTE}");*/
            newus = true;
            adm = false;

           /* actual = lista1;
            
            while ((actual != nullptr) && (comer.compare(actual->comercio) != 0)) {

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
            }*/
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

        g1 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g1, L"nombre completo");

        g2 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g2, L"alias");

       /* g3 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g3, L"{PENDIENTE}");*/

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g1, (LPWSTR)nombre, sizeof(nombre));
            GetWindowText(g2, (LPWSTR)alias, sizeof(alias));
            //GetWindowText(g1, (LPWSTR)usuario, sizeof(usuario));
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON2:
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

        g1 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g1, L"usuario");

        g2 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g2, L"contrasena");

        g3 = GetDlgItem(hwnd, IDC_CHECK1);
        SetWindowText(g3, L"Admin");

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            EndDialog(hwnd, wParam);
           
        case IDC_BUTTON2:
            EndDialog(hwnd, wParam);
            
            return TRUE;
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


        g1 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g1, L"nueva contraseña");

        

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g1, (LPWSTR)contrasena, sizeof(contrasena));
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
        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(h_edit, usuarioq);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, nombre);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, alias);
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, comercio);
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, L"Admin: Si");
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

            break;
        case IDC_BUTTON2:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
            if (confirmar == true) {
                MessageBox(hwnd, L"Usuario Eliminado", L"Eliminar usuario", MB_ICONEXCLAMATION);
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

        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Ingrese nueva foto de usuario");

        g1 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g1, usuarioq);

        g2 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g2, nombre);

        g3 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g3, alias);

        

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

            GetWindowText(g1, (LPWSTR)usuario, sizeof(usuario));
            GetWindowText(g2, (LPWSTR)nombre, sizeof(nombre));
            GetWindowText(g3, (LPWSTR)alias, sizeof(alias));

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
            MessageBox(hwnd, L"mensaje", L"ttulo", MB_ICONEXCLAMATION);
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
            
            DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista1);
            //regresar = false;
            if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_RESTABLECER), hwnd, (DLGPROC)ResConAct);
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
}
//void listado_usuario(usuarios* lista1) {
//
//
//    cout << endl;
//    if (lista1 == nullptr) {
//        //cout << ">No hay Usuarios registradas" << endl;
//        system("pause");
//    }
//    while (lista1 != nullptr) {
//        if (actual->numcomer == lista1->numcomer) {
//            cout << "> [" << lista1->nomusuario << "]" << endl;
//        }
//        lista1 = lista1->siguiente;
//
//    }
//
//}
//Clientes------------------------------------------------------------------------------------------------------------------------
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
            g1 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g1, L"nuevo cliente");
            g2 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g2, L"alias");
            g3 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g3, L"telefono");
            g4 = GetDlgItem(hwnd, IDC_EDIT4);
            SetWindowText(g4, L"correo");
           
            break;
        }
        else {
            g1 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g1, clienteq);
            g2 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g2, aliasclien);
            g3 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g3, telefono);
            g4 = GetDlgItem(hwnd, IDC_EDIT4);
            SetWindowText(g4, email);
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
            GetWindowText(g1, (LPWSTR)cliente, sizeof(cliente));
            GetWindowText(g2, (LPWSTR)aliasclien, sizeof(aliasclien));
            GetWindowText(g3, (LPWSTR)telefono, sizeof(telefono));
            GetWindowText(g4, (LPWSTR)email, sizeof(email));
            wcscpy_s(fecha, L"Ahora");
            wcscpy_s(comercioclien, comercio);
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
        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(h_edit, clienteq);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, aliasclien);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, comercioclien);
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, email);
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, telefono);
        h_edit = GetDlgItem(hwnd, IDC_STATIC6);
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
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWCLIEN), hwnd, (DLGPROC)NuevCliente);
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON2:
            DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
            if (confirmar == true) {
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

        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, L"Ahora");

        if (nuevo == true) {
            g1 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g1, L"nueva promocion");
            g2 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g2, L"nuevo monto");
            g3 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g3, L"nuevo porcentaje");
            
            break;
        }
        else {
            g1 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g1, promocionq);
            g2 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g2, monto);
            g3 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g3, porcentaje);
            
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
            GetWindowText(g1, (LPWSTR)promocionq, sizeof(promocionq));
            GetWindowText(g2, (LPWSTR)monto, sizeof(monto));
            GetWindowText(g3, (LPWSTR)porcentaje, sizeof(porcentaje));
            wcscpy_s(fecha, L"Ahora");
            wcscpy_s(activa, L"Si");
            
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


        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Actualizar promocion");
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
//Consumos------------------------------------------------------------------------------------------------------------------------
BOOL CALLBACK NuevConsumo(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_CREATE:
    case WM_INITDIALOG:
        g2 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g2, L"monto");
        h_combobox = GetDlgItem(hwnd, IDC_LIST1);
        SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)consumoq);

        wchar_t j[2];
        wchar_t dummy[60];
        ZeroMemory(dummy, 120);
        for (int i = 1; i <= 5; i++) {
            wcscpy_s(dummy, L"Cliente");
            _itow_s(i, j, 2, 10);
            wcscat_s(dummy, j);
            SendMessage(h_combobox, LB_ADDSTRING, (WPARAM)0, (LPARAM)dummy);
        }


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

            GetWindowText(g2, (LPWSTR)montocons, sizeof(montocons));
           
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
