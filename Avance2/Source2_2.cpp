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
HWND h_edit, Edit;
HWND Dialog2, Dialog3, Dialog4, Dialog5, Dialog6;
HWND g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15,
g16, g17, g18, g19, g20, g21, g22, g23, g24, g25, g26, a27, a28, a29, a30, a31;
HWND a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15,
a16, a17, a18, a19, a20, a21, a22, a23, a24, a25;
HWND h_combobox, h_listbox1, h_listbox2, h_listbox3, h_listbox4;
HWND hPictureControl;
HMENU hMenu;
HINSTANCE hInstance;
HBITMAP hBitmap1, hBitmap2, hBitmap3, hBitmap4;
wchar_t buffer[256];
wchar_t contador1[200000], contador2[200000], contador3[200000], contador4[200000], contador5[200000], ArchivoUsuario[100];
char archivousuario[100];
int a, b, c, d;
float fe;
bool nuevo, regresar, nuevous, confirmar;
//int lista = 0;


struct usuarios {
    wchar_t nomusuario[50], nombrecom[50], contraseña[50], comercio[50], alias[50], imagen[100];
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
    float porcentaje = 0;
    bool activo;
    int cantidad, numcomer;
    promociones* siguiente;
};
struct consumos {
    wchar_t consumo[50], fecha[50], cliente[50];
    float subtotal = 0, descuento = 0, total = 0;
    int monto, numcomer;

    consumos* siguiente;
};

//usuarios usuario[100];
usuarios* actual = nullptr;
usuarios* buscar1 = new usuarios();
usuarios* lista1 = NULL;
usuarios* contar1 = new usuarios();
usuarios* validar1 = new usuarios();
usuarios* guardar1 = new usuarios();

//clientes cliente[200];
clientes* buscar2 = new clientes();
clientes* lista2 = NULL;
clientes* contar2 = new clientes();
clientes* validar2 = new clientes();

promociones* lista3 = NULL;
promociones* buscar3 = new promociones();
promociones* contar3 = new promociones();
promociones* validar3 = new promociones();

consumos* lista4 = NULL;
consumos* buscar4 = new consumos(); 
consumos* contar4 = new consumos();

char menu0, menu1, menu2, menu3, sinoadmin, sinoactivo;
bool UsuValid, adminuevusu, comernew, Cvalid/*, adad = true*/;
int CV1, CV2, CV3, CV4, CV5;
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

wchar_t Usuario[50], Contraseña[50], Comercio[50];
wchar_t Validar1[] = L"0123456789", Validar2[] = L"!#$%&/()='?¡¿@´¨*+{[]}-_<>~", Validar3[] = L"abcdefghijklmnñopqrstuvwxyz", Validar4[] = L"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";

wchar_t Buscar_Usuario[50];
wchar_t Buscar_Cliente[50];
wchar_t Buscar_Promo[50];
wchar_t Buscar_Consumo[50];
wchar_t Cliente_Consumo[50];
wchar_t Consumo_Cliente[50];

float producto;
//Lista ligada Usuarios
wchar_t usu[50], nomcom[50], cont[50], comer[50], ali[50], img[100]; int numcom; bool adm, newus;

//Lista Ligada Clientes
wchar_t nomclien[50], alic[50], tel[50], ema[50], comerc[50], fech[50]; int numcomc;

//Lista ligada Promociones
wchar_t promo[50], date[50]; float por; bool act; int cant, numcomp;

//Lista ligada Consumos
wchar_t cons[50], datec[50], ccons[50]; float  sub, desc, tot; int numcomco, mont;

//void NuevoUsuario();
//void agregar_usuario(usuarios*& lista1, wchar_t usu[50], wchar_t nomcom[50], wchar_t cont[50], wchar_t comer[50], wchar_t ali[50], int numcom, bool adm, bool newus, wchar_t imagen[100]);
//usuario
wchar_t usuarioq[20], contrasena[20], comercio[20], alias[20], nombre[50]; int cantus = 0;

//cliente
wchar_t clienteq[50], aliasclien[20], telefono[20], email[50], comercioclien[20], fecha[20]; int cantclien = 0;

//promocion
wchar_t promocionq[50], monto[10], porcentaje[10], activa[5]; int cantprom = 0;

//consumo
wchar_t consumoq[50], montocons[20], fechacons[20], subtotal[20], descuento[20], total[20]; int cantcons = 0;

//wchar_t ValidCont[];

wchar_t PH[50];
float Precio_Global = 23.2;
wchar_t PG[20];
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
BOOL CALLBACK TotalA(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Total(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Confirmar(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void ContadorMaestro(HWND hwnd) {
    k = 0, m = 0, n = 0, ñ = 0;
    contar1 = lista1;
    while (contar1 != nullptr) {
        k++;
        contar1 = contar1->siguiente;
    }
    contar2 = lista2;
    while (contar2 != nullptr) {
        m++;
        contar2 = contar2->siguiente;
    }
    contar3 = lista3;
    while (contar3 != nullptr) {
        n++;
        contar3 = contar3->siguiente;
    }
    contar4 = lista4;
    while (contar4 != nullptr) {
        ñ++;
        contar4 = contar4->siguiente;
    }
    k--, m--, n--, ñ--;
}
void Contador(HWND hwnd) {
    
    a = 0;
    contar2 = lista2;
    while (contar2 != nullptr) {
        if (contar2->numcomer == actual->numcomer) {
            a++;
        }
        contar2 = contar2->siguiente;
    }
   

    b = 0;
    contar3 = lista3;
    while (contar3 != nullptr) {
        if ((contar3->activo == true) && (actual->numcomer == contar3->numcomer)) {
            b++;
        }
        contar3 = contar3->siguiente;
    }
    

    c = 0;
    contar3 = lista3;
    while (contar3 != nullptr) {
        if ((contar3->activo == false) && (actual->numcomer == contar3->numcomer)) {
            c++;
        }
        contar3 = contar3->siguiente;
    }
   

    d = 0;
    contar4 = lista4;
    while (contar4 != nullptr) {
        if (actual->numcomer == contar4->numcomer) {
            d++;
        }
        contar4 = contar4->siguiente;
    }
    

    fe = 0;
    contar4 = lista4;
    while (contar4 != nullptr) {
        if (actual->numcomer == contar4->numcomer) {
            fe += contar4->total;
        }
        contar4 = contar4->siguiente;
    }
    
}
void ContraValid(HWND hwnd, wchar_t cont[50]) {
    Cvalid = false;
    CV1 = 0, CV2 = 0;
    while (CV1 < 10) {
        CV2 = 0;
        while (CV2 < 27) {
            if (cont[CV1] == Validar3[CV2]) {

                Cvalid = true;
                CV1 = 10;
                CV2 = 27;
            }
            else {
                Cvalid = false;
            }
            CV2++;
        }
        CV1++;
    }
    if (Cvalid == true) {
        CV1 = 0, CV2 = 0;
        while (CV1 < 10) {
            CV2 = 0;
            while (CV2 < 10) {
                if (cont[CV1] == Validar1[CV2]) {

                    Cvalid = true;
                    CV1 = 10;
                    CV2 = 10;
                }
                else {
                    Cvalid = false;
                }
                CV2++;
            }
            CV1++;
        }
    }
    if (Cvalid == true) {
        CV1 = 0, CV2 = 0;
        while (CV1 < 10) {
            CV2 = 0;
            while (CV2 < 27) {
                if (cont[CV1] == Validar2[CV2]) {

                    Cvalid = true;
                    CV1 = 10;
                    CV2 = 27;
                }
                else {
                    Cvalid = false;
                }
                CV2++;
            }
            CV1++;
        }
    }
    
}
void VANUMSIM(HWND hwnd, wchar_t PH[50]) {
    Cvalid = false;
    CV1 = 0;
    while ((PH[CV1] != L'\0') && (CV1 < 50)) {
        CV2 = 0;
        while (CV2 < 10) {
            CV3 = 0;
            while (CV3 < 27) {
                if ((PH[CV1] == Validar1[CV2]) || (PH[CV1] == Validar2[CV3])) {

                    Cvalid = false;
                    CV1 = 50;
                    CV2 = 10;
                    CV3 = 27;
                }
                else {
                    Cvalid = true;
                }
                CV3++;
            }
            CV2++;
        }
        CV1++;
    }
}
void VASIM(HWND hwnd, wchar_t PH[50]) {
    Cvalid = false;
    CV1 = 0;
    while ((PH[CV1] != L'\0') && (CV1 < 50)) {
        CV3 = 0;
        while (CV3 < 27) {
            if (PH[CV1] == Validar2[CV3]) {
                Cvalid = false;
                CV1 = 50;
                CV3 = 27;
            }
            else {
                Cvalid = true;
            }
            CV3++;
        }
        CV1++;
    }
}
//Archivos-----------------------------------------------------------------------------------------------------------------------

//void manejo_de_archivos()
//{
//    ofstream archivo;
//    archivo.open("ejemplo.txt");
//    archivo << "Escribiendo en el archivo. \n";
//    archivo.close();
//
//    string line;
//    ifstream myfile;
//    myfile.open("ejemplo.txt");
//    if (myfile.is_open())
//    {
//        /*myfile >> line;*/
//        while (getline(myfile, line))
//        {
//            cout << line << '\n';
//        }
//        myfile.close();
//    }
//    else
//    {
//        cout << "Unable to open file" << endl;
//    }
//}
//void manejo_de_archivos_binario()
//{
//    fstream Archivo;
//    struct nodo
//    {
//        int a;
//        char b[12];
//    };
//    nodo* actual = new nodo;
//    actual->a = 34;
//    strcpy_s(actual->b, 12, "Hola mundo!");
//
//    Archivo.open("Archivo.bin", ios::out | ios::binary);
//    if (Archivo.is_open())
//    {
//        Archivo.write(reinterpret_cast<char*>(actual), sizeof(nodo));
//    }
//    else
//    {
//        cout << "Unable to open file" << endl;
//    }
//    Archivo.close();
//
//    Archivo.open("Archivo.bin", ios::in | ios::binary);
//    if (Archivo.is_open())
//    {
//        int size = Archivo.tellg();
//
//        int i = 0;
//        nodo* Temp = new nodo;
//        Archivo.seekg(i * sizeof(nodo));
//        Archivo.read(reinterpret_cast<char*>(Temp), sizeof(nodo));
//
//        nodo lista;
//        lista.a = Temp->a;
//        strcpy_s(lista.b, 12, Temp->b);
//        delete Temp;
//    }
//    else
//    {
//        cout << "Unable to open file" << endl;
//    }
//    Archivo.close();
//}
//void manejo_de_archivos_wchar_t()
//{
//    wofstream archivo;
//    archivo.open("Archivo.bin");
//    wchar_t variable[20] = L"Hola mundo";
//    archivo << variable;
//    archivo.close();
//
//    wstring line;
//    wifstream myfile;
//    myfile.open("Archivo.bin");
//    if (myfile.is_open())
//    {
//        while (getline(myfile, line))
//        {
//            wcout << line << '\n';
//        }
//        myfile.close();
//    }
//    else
//    {
//        
//    }
//}
//void display_file(LPWSTR path)
//{
//    size_t i;
//    char buffer[256];
//    ZeroMemory(buffer, 256);
//    wcstombs_s(&i, buffer, 256, path, 256 - 1);
//
//    FILE* file;
//    errno_t err;
//    err = fopen_s(&file, buffer, "r");
//
//    if (err == 0)
//    {
//        fseek(file, 0, SEEK_END);
//        int _size = ftell(file);
//        rewind(file);
//        char* data = new char[_size + 1];
//        fread(data, _size, _size, file);
//        data[_size] = '\0';
//        fclose(file);
//
//        wchar_t wtext[256];
//        ZeroMemory(wtext, 256);
//        size_t len;
//        mbstowcs_s(&len, wtext, 256, data, strlen(data) + 1);
//        LPWSTR ptr = wtext;
//
//        SetWindowText(Edit, ptr);
//    }
//}
//void funcion_abrir(HWND padre)
//{
//    OPENFILENAME openfilename;
//
//    TCHAR szFile[MAX_PATH + 1];
//    ZeroMemory(szFile, sizeof(szFile));
//
//    ZeroMemory(&openfilename, sizeof(OPENFILENAME));
//    openfilename.lStructSize = sizeof(OPENFILENAME);
//    openfilename.hwndOwner = padre;
//    openfilename.lpstrFile = szFile;
//    openfilename.nMaxFile = MAX_PATH;
//    openfilename.nFilterIndex = 1;
//    openfilename.lpstrFileTitle = NULL;
//    openfilename.nMaxFileTitle = 0;
//    openfilename.lpstrInitialDir = NULL;
//    openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
//
//    if (GetOpenFileName(&openfilename))
//    {
//        display_file(openfilename.lpstrFile/*, paramEdit*/);
//    }
//    else
//    {
//        MessageBox(NULL, TEXT("Could not open this file"), TEXT("File I/O Error"), MB_ICONSTOP);
//    }
//}
//void write_file(LPWSTR path)
//{
//    char buffer[256];
//    ZeroMemory(buffer, 256);
//    size_t i;
//    wcstombs_s(&i, buffer, 256, path, 256 - 1);
//
//    FILE* file;
//    errno_t err;
//    err = fopen_s(&file, buffer, "w");
//
//    if (err == 0)
//    {
//        /*int size = GetWindowTextLength(Edit);
//        LPSTR _data = new char[size + 1];
//        GetWindowTextA(Edit, _data, size + 1);
//
//        fwrite(_data, size + 1, 1, file);*/
//
//        fstream Archivo;
//        Archivo.open(archivousuario, ios::out | ios::binary);
//        if (Archivo.is_open()) {
//            usuarios* guardar = new usuarios;
//            while (guardar != nullptr) {
//                guardar = lista1;
//                guardar = guardar->siguiente;
//                lista1 = lista1->siguiente;
//                Archivo.write(reinterpret_cast<char*>(guardar), sizeof(usuarios));
//            }
//                //Archivo << lista1->nomusuario;
//               
//            
//                MessageBox(NULL, TEXT("Guardado"), TEXT("Archivo"), MB_ICONINFORMATION);
//        }
//        else {
//            MessageBox(NULL, TEXT("No se pudo guardar el archivo"), TEXT("Archivo"), MB_ICONEXCLAMATION);
//        }
//        Archivo.close();
//       
//        
//        fclose(file);
//    }
//}
//void funcion_guardar(HWND padre)
//{
//    OPENFILENAME openfilename;
//
//    TCHAR szFile[MAX_PATH + 1];
//    ZeroMemory(szFile, sizeof(szFile));
//
//    ZeroMemory(&openfilename, sizeof(OPENFILENAME));
//    openfilename.lStructSize = sizeof(OPENFILENAME);
//    openfilename.hwndOwner = padre;
//    openfilename.lpstrFile = szFile;
//    openfilename.lpstrFilter = TEXT("All\0 * .*\0Binario (.bin)\0 * .bin\0");
//    openfilename.nMaxFile = MAX_PATH;
//    openfilename.nFilterIndex = 1;
//    openfilename.lpstrFileTitle = NULL;
//    openfilename.nMaxFileTitle = 0;
//    openfilename.lpstrInitialDir = NULL;
//    openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
//
//    if (GetSaveFileName(&openfilename))
//    {
//        size_t PJ = 0;
//        wcscpy_s(ArchivoUsuario, openfilename.lpstrFile);
//        wcstombs_s(&PJ, archivousuario, sizeof(archivousuario), ArchivoUsuario, 100);
//        write_file(openfilename.lpstrFile);
//        
//    }
//    else
//    {
//        MessageBox(NULL, TEXT("Could not save this file"), TEXT("File I/O Error"), MB_ICONEXCLAMATION);
//    }
//}


void AbrirU(HWND hwnd) {
    usuarios* abrir = new usuarios;
    fstream Archivo;
    Archivo.open("Usuarios.bin", ios::in | ios::binary);
    if (Archivo.is_open()) {
       /* Archivo.read(reinterpret_cast<char*>(k), sizeof(k));*/
        int i = 0, size = Archivo.tellg();
        usuarios* Aux = nullptr;
        while (Archivo.good()) {
            Aux = new usuarios;
            ZeroMemory(Aux, sizeof(usuarios));
            Archivo.seekg(i * sizeof(usuarios));
            Archivo.read(reinterpret_cast<char*>(Aux), sizeof(usuarios));
            i++;
            if (lista1 == nullptr) {
                lista1 = Aux;
                lista1->siguiente = nullptr;
                abrir = lista1;
                
            }
            else {
                /*if (wcscmp(Aux->contraseña, L"") == 0) {

                }
                else {*/
                abrir = lista1;
                while (abrir->siguiente != nullptr) {
                    abrir = abrir->siguiente;
                }
                abrir->siguiente = Aux;
                abrir->siguiente->siguiente = nullptr;
                abrir = abrir->siguiente;
                /*}*/
            }
        }
        MessageBox(NULL, TEXT("Usuarios cargados"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo abrir el archivo de usuarios"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
}
void GuardarU(HWND hwnd) {
    usuarios* guardar = new usuarios;
    fstream Archivo;
    Archivo.open("Usuarios.bin", ios::out | ios::trunc | ios::binary);
    if (Archivo.is_open()) {
        //Archivo.write(reinterpret_cast<char*>(k), sizeof(k));
        guardar = lista1;
        while (guardar != nullptr) {
            Archivo.write(reinterpret_cast<char*>(guardar), sizeof(usuarios));
            guardar = guardar->siguiente;
            
            
        }
        //Archivo << lista1->nomusuario;


        MessageBox(NULL, TEXT("Usuarios guardados"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo guardar el archivo de usuarios"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
    Archivo.close();

}

void AbrirCl(HWND hwnd) {
    clientes* abrir = new clientes;
    
       
    fstream Archivo;
    Archivo.open("Clientes.bin", ios::in | ios::binary);
    if (Archivo.is_open()) {
        
        int i = 0, size = Archivo.tellg();
        clientes* Aux = nullptr;
        while (Archivo.good()) {
            Aux = new clientes;
            ZeroMemory(Aux, sizeof(clientes));
            
            Archivo.seekg(i * sizeof(clientes));
            Archivo.read(reinterpret_cast<char*>(Aux), sizeof(clientes));
            i++;
            if (lista2 == nullptr) {
                lista2 = Aux;
                lista2->siguiente = nullptr;
                abrir = lista2;

            }
            else {
                /*if (wcscmp(Aux->contraseña, L"") == 0) {

                }
                else {*/
                abrir = lista2;
                while (abrir->siguiente != nullptr) {
                    abrir = abrir->siguiente;
                }
                abrir->siguiente = Aux;
                abrir->siguiente->siguiente = nullptr;
                abrir = abrir->siguiente;
                /*}*/
            }

            

        }
        MessageBox(NULL, TEXT("Clientes cargados"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo abrir el archivo de clientes"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
}
void GuardarCl(HWND hwnd) {
    clientes* guardar = new clientes;
    
    
    
    fstream Archivo;
    Archivo.open("Clientes.bin", ios::out | ios::trunc | ios::binary);
    if (Archivo.is_open()) {
        
        guardar = lista2;
        while (guardar != nullptr) {
            Archivo.write(reinterpret_cast<char*>(guardar), sizeof(clientes));
            guardar = guardar->siguiente;


        }
       

        MessageBox(NULL, TEXT("Clientes guardados"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo guardar el archivo de clientes"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
    Archivo.close();

}

void AbrirP(HWND hwnd) {
    promociones* abrir = new promociones;
    fstream Archivo;
    Archivo.open("Promociones.bin", ios::in | ios::binary);
    if (Archivo.is_open()) {
        int i = 0, size = Archivo.tellg();
        promociones* Aux = nullptr;
        while (Archivo.good()) {
            Aux = new promociones;
            ZeroMemory(Aux, sizeof(promociones));
            Archivo.seekg(i * sizeof(promociones));
            Archivo.read(reinterpret_cast<char*>(Aux), sizeof(promociones));
            i++;
            if (lista3 == nullptr) {
                lista3 = Aux;
                lista3->siguiente = nullptr;
                abrir = lista3;

            }
            else {
                /*if (wcscmp(Aux->contraseña, L"") == 0) {

                }
                else {*/
                abrir = lista3;
                while (abrir->siguiente != nullptr) {
                    abrir = abrir->siguiente;
                }
                abrir->siguiente = Aux;
                abrir->siguiente->siguiente = nullptr;
                abrir = abrir->siguiente;
                /*}*/
            }
        }
        MessageBox(NULL, TEXT("Promociones cargadas"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo abrir el archivo de promociones"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
}
void GuardarP(HWND hwnd) {
    promociones* guardar = new promociones;
    fstream Archivo;
    Archivo.open("Promociones.bin", ios::out | ios::trunc | ios::binary);
    if (Archivo.is_open()) {
        guardar = lista3;
        while (guardar != nullptr) {
            Archivo.write(reinterpret_cast<char*>(guardar), sizeof(promociones));
            guardar = guardar->siguiente;


        }
        //Archivo << lista1->nomusuario;


        MessageBox(NULL, TEXT("Promociones guardadas"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo guardar el archivo de promociones"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
    Archivo.close();

}

void AbrirCo(HWND hwnd) {
    consumos* abrir = new consumos;
    fstream Archivo;
    Archivo.open("Consumos.bin", ios::in | ios::binary);
    if (Archivo.is_open()) {
        int i = 0, size = Archivo.tellg();
        consumos* Aux = nullptr;
        while (Archivo.good()) {
            Aux = new consumos;
            ZeroMemory(Aux, sizeof(consumos));
            Archivo.seekg(i * sizeof(consumos));
            Archivo.read(reinterpret_cast<char*>(Aux), sizeof(consumos));
            i++;
            if (lista4 == nullptr) {
                lista4 = Aux;
                lista4->siguiente = nullptr;
                abrir = lista4;

            }
            else {
                /* if (wcscmp(Aux->contraseña, L"") == 0) {

                 }
                 else {*/
                abrir = lista4;
                while (abrir->siguiente != nullptr) {
                    abrir = abrir->siguiente;
                }
                abrir->siguiente = Aux;
                abrir->siguiente->siguiente = nullptr;
                abrir = abrir->siguiente;
                /*}*/
            }
        }
        MessageBox(NULL, TEXT("Consumos cargados"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo abrir el archivo de consumos"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
}
void GuardarCo(HWND hwnd) {
    consumos* guardar = new consumos;
    fstream Archivo;
    Archivo.open("Consumos.bin", ios::out | ios::trunc | ios::binary);
    if (Archivo.is_open()) {
        guardar = lista4;
        while (guardar != nullptr) {
            Archivo.write(reinterpret_cast<char*>(guardar), sizeof(consumos));
            guardar = guardar->siguiente;


        }
        //Archivo << lista1->nomusuario;


        MessageBox(NULL, TEXT("Consumos guardados"), TEXT("Archivo"), MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, TEXT("No se pudo guardar el archivo de consumos"), TEXT("Archivo"), MB_ICONEXCLAMATION);
    }
    Archivo.close();

}

void AbrirCont(HWND hwnd) {
    
    struct contadores
    {
        int l;
    };
   
    
    fstream Archivo;
    Archivo.open("numcomer.bin", ios::in | ios::binary);
    if (Archivo.is_open()) {



        int size = Archivo.tellg();

        int i = 0;
        contadores* Temp = new contadores;
        Archivo.seekg(i * sizeof(contadores));
        Archivo.read(reinterpret_cast<char*>(Temp), sizeof(contadores));

        //contadores lista;
        /*lista.*/l = Temp->l;

        //delete Temp;



    }
    
}
void GuardarCont(HWND hwnd) {
    
    struct contadores
    {
        int l;
    };

    
    contadores* guardar = new contadores;
    guardar->l = l;

    fstream Archivo;
    Archivo.open("numcomer.bin", ios::out | ios::trunc | ios::binary);
    if (Archivo.is_open()) {
        //guardar = elemento;
        Archivo.write(reinterpret_cast<char*>(guardar), sizeof(contadores));


        
    }
    
    Archivo.close();

}

void AbrirImagen(HWND hwnd) {
    OPENFILENAME ofn;

    TCHAR zFile[MAX_PATH]; //260 caracteres

    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = TEXT("ALL\0 * .*\0Bitmaps\0 * .bmp\0");
    ofn.lpstrFile = zFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(zFile);
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.nFilterIndex = 2;

    if(GetOpenFileName(&ofn) == TRUE) {
        wcscpy_s(img, ofn.lpstrFile);
    }
    else {
        wcscpy_s(img, L"Perfil.bmp");
    }

}

//Main---------------------------------------------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    /*wcscpy_s(usu, L"usuario 0");
    wcscpy_s(nomcom, L"Usuario Numero Cero");
    wcscpy_s(cont, L"contrasena 0");
    wcscpy_s(comer, L"comercio 0");
    wcscpy_s(ali, L"Usuario No. 0");
    wcscpy_s(img, L"Perfil.bmp");
    numcom = 0;
    adm = true;
    newus = false;

    agregar_usuario(lista1, usu, nomcom, cont, comer, ali, numcom, adm, newus, img);*/
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
                AbrirU(hwnd);
                AbrirCl(hwnd);
                AbrirP(hwnd);
                AbrirCo(hwnd);
                AbrirCont(hwnd);
                ContadorMaestro(hwnd);
                break;
            case ID_ARCHIVO_GUARDAR:
                GuardarU(hwnd);
                GuardarCl(hwnd);
                GuardarP(hwnd);
                GuardarCo(hwnd);
                GuardarCont(hwnd);
                break;
           
            case ID_SALIR_GUARDARYSALIR:
                GuardarU(hwnd);
                GuardarCl(hwnd);
                GuardarP(hwnd);
                GuardarCo(hwnd);
                GuardarCont(hwnd);
                DestroyWindow(hwnd);
                DestroyMenu(hMenu);
                DestroyWindow(ghDlg);
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
                            //if (adad == true) {
                            //    MessageBox(hwnd, L"Se le han otorgado permisos de administrador al ser el primer usuario de su comercio.", L"Aviso", MB_ICONINFORMATION);
                            //    //actual->Admin = true;
                            //    adad = false;
                            //   
                            //}
                            Dialog2 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)WindowProc2);
                            ShowWindow(Dialog2, SW_SHOW);
                        }
                    }
                    else {
                        Dialog2 = CreateDialog(NULL, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)WindowProc2);
                        ShowWindow(Dialog2, SW_SHOW);
                    }
                    
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
        a30 = GetDlgItem(hwnd, IDC_STATIC9);
        SetWindowText(a30, actual->nombrecom);
        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
        
        a20 = GetDlgItem(hwnd, IDC_STATIC4);
       
        a21 = GetDlgItem(hwnd, IDC_STATIC5);
       
        a22 = GetDlgItem(hwnd, IDC_STATIC6);
    
        a23 = GetDlgItem(hwnd, IDC_STATIC7_);
       
        a24 = GetDlgItem(hwnd, IDC_STATIC8);
        
        Contador(hwnd);
        _itow_s(a, contador1, 200000, 10);
        SetWindowText(a20, contador1);
        _itow_s(b, contador2, 200000, 10);
        SetWindowText(a21, contador2);
        _itow_s(c, contador3, 200000, 10);
        SetWindowText(a22, contador3);
        _itow_s(d, contador4, 200000, 10);
        SetWindowText(a23, contador4);
        swprintf_s(contador5, L"%.1f", fe);
        SetWindowText(a24, contador5);

        break;

    
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            AbrirU(hwnd);
            AbrirCl(hwnd);
            AbrirP(hwnd);
            AbrirCo(hwnd);
            AbrirCont(hwnd);
            ContadorMaestro(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            GuardarU(hwnd);
            GuardarCl(hwnd);
            GuardarP(hwnd);
            GuardarCo(hwnd);
            GuardarCont(hwnd);
            break;
        case ID_SALIR_GUARDARYSALIR:
            GuardarU(hwnd);
            GuardarCl(hwnd);
            GuardarP(hwnd);
            GuardarCo(hwnd);
            GuardarCont(hwnd);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
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
            DeleteObject((HBITMAP)hBitmap2);
            EndDialog(hwnd, wParam);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
           
            break;
        case IDC_BUTTON7:

           
            SetWindowText(a1, actual->nomusuario);
           
            SetWindowText(a2, actual->comercio);
           
            if (actual->Admin == true) {
                SetWindowText(a3, L"Admin: Si");
            }
            else {
                SetWindowText(a3, L"Admin: No");
            }
            SetWindowText(a30, actual->nombrecom);
            hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

            Contador(hwnd);
            _itow_s(a, contador1, 200000, 10);
            SetWindowText(a20, contador1);
            _itow_s(b, contador2, 200000, 10);
            SetWindowText(a21, contador2);
            _itow_s(c, contador3, 200000, 10);
            SetWindowText(a22, contador3);
            _itow_s(d, contador4, 200000, 10);
            SetWindowText(a23, contador4);
            swprintf_s(contador5, L"%.1f", fe);
            SetWindowText(a24, contador5);

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
        a27 = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(a27, actual->nombrecom);

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            AbrirU(hwnd);
            AbrirCont(hwnd);
            ContadorMaestro(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            GuardarU(hwnd);
            GuardarCont(hwnd);
            break;
        case ID_SALIR_GUARDARYSALIR:
            GuardarU(hwnd);
            GuardarCl(hwnd);
            GuardarP(hwnd);
            GuardarCo(hwnd);
            GuardarCont(hwnd);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1: //Actualizar Usuario
            
                DialogBox(NULL, MAKEINTRESOURCE(IDD_DATAUSU), hwnd, (DLGPROC)ActualizarUA);
                
                SetWindowText(a27, actual->nombrecom);

               
                hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
                SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
            break;
        case IDC_BUTTON2: //Alta de Nuevo Usuario
           if (actual->Admin == true) {
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWUSUARIO), hwnd, (DLGPROC)NuevUsuario);
           }
           else {
               MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
           }
            break;
        case IDC_BUTTON3: //Listado de Usuarios
            if (actual->Admin == true) {
                
                DialogBox(NULL, MAKEINTRESOURCE(IDD_LISTA), hwnd, (DLGPROC)Lista1);
                if (regresar == false) {
                    DialogBox(NULL, MAKEINTRESOURCE(IDD_SELEC), hwnd, (DLGPROC)Actusu);
                }
                
                SetWindowText(a27, actual->nombrecom);

               
                hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
                SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
            }
            break;
        case IDC_BUTTON4: //Restablecer Contraseña
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, (DLGPROC)ResCon);
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
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

        a28 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a28, actual->nombrecom);

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_ARCHIVO_ABRIR:
            AbrirCl(hwnd);
            ContadorMaestro(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            GuardarCl(hwnd);
            break;
        case ID_ARCHIVO_GUARDARCOMO:
            //Guardar(hwnd);
            break;
        case ID_SALIR_GUARDARYSALIR:
            GuardarU(hwnd);
            GuardarCl(hwnd);
            GuardarP(hwnd);
            GuardarCo(hwnd);
            GuardarCont(hwnd);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
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
       
        a29 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a29, actual->nombrecom);

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            AbrirP(hwnd);
            ContadorMaestro(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            GuardarP(hwnd);
            break;
        case ID_SALIR_GUARDARYSALIR:
            GuardarU(hwnd);
            GuardarCl(hwnd);
            GuardarP(hwnd);
            GuardarCo(hwnd);
            GuardarCont(hwnd);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1:
            if (actual->Admin == true) {
                nuevo = true;
                DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWPROM), hwnd, (DLGPROC)NuevPromo);
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
            }
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

        a31 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a31, actual->nombrecom);

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap2 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_ARCHIVO_ABRIR:
            AbrirCo(hwnd);
            ContadorMaestro(hwnd);
            break;
        case ID_ARCHIVO_GUARDAR:
            GuardarCo(hwnd);
            break;
        case ID_SALIR_GUARDARYSALIR:
            GuardarU(hwnd);
            GuardarCl(hwnd);
            GuardarP(hwnd);
            GuardarCo(hwnd);
            GuardarCont(hwnd);
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case ID_SALIR_SALIRSINGUARDAR:
            DestroyWindow(hwnd);
            DestroyMenu(hMenu);
            DestroyWindow(ghDlg);
            break;
        case IDC_BUTTON1:
           
            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWCONS), hwnd, (DLGPROC)NuevConsumo);
            if (regresar == false) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_TOTAL), hwnd, (DLGPROC)TotalA);
            }
            break;
        case IDC_BUTTON2:
            //lista = 4;
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
void listado_consclien(consumos* lista4) {
    if (lista4 == nullptr) {
        SendMessage(h_listbox4, LB_ADDSTRING, (WPARAM)0, (LPARAM)L"No hay consumos para este comercio");
    }

    while (lista4 != nullptr) {
        if (wcscmp(buscar2->nomcliente, lista4->cliente) == 0) {
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
            buscar1 = lista1;
//            wchar_t Buscar_Usuario[50];
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Buscar_Usuario);
            //GetWindowText(h_listbox1, (LPWSTR)Buscar_Usuario, sizeof(Buscar_Usuario));
            while ((buscar1 != nullptr) && ((wcscmp(Buscar_Usuario, buscar1->nomusuario)!=0) || (actual->numcomer != buscar1->numcomer))) {

                buscar1 = buscar1->siguiente;
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
        h_listbox4 = GetDlgItem(hwnd, IDC_LIST1);
        

        listado_consumos(lista4);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            buscar4 = lista4;
            wcscpy_s(Buscar_Consumo, L"NULL");
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Buscar_Consumo);

            if (wcscmp(Buscar_Consumo, L"No hay consumos para este comercio") == 0) {
                MessageBox(hwnd, L"No hay consumos registrados", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else if (wcscmp(Buscar_Consumo, L"NULL") == 0) {
                MessageBox(hwnd, L"No se seleccionó una opción", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else {
                while ((buscar4 != nullptr) && ((wcscmp(Buscar_Consumo, buscar4->consumo) != 0) || (actual->numcomer != buscar4->numcomer))) {

                    buscar4 = buscar4->siguiente;
                }
                regresar = false;
            }
            EndDialog(hwnd, wParam);
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
void agregar_usuario(usuarios*& lista1, wchar_t usu[50], wchar_t nomcom[50], wchar_t cont[50], wchar_t comer[50], wchar_t ali[50], int numcom, bool adm, bool newus, wchar_t img[100]) {

    usuarios* nuevo_usuario = new usuarios();
    usuarios* aux;
    wcscpy_s(nuevo_usuario->nomusuario, usu);
    wcscpy_s(nuevo_usuario->nombrecom, nomcom);
    wcscpy_s(nuevo_usuario->contraseña, cont);
    wcscpy_s(nuevo_usuario->comercio, comer);
    wcscpy_s(nuevo_usuario->alias, ali);
    wcscpy_s(nuevo_usuario->imagen, img);
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
        SendMessage(g3, EM_SETLIMITTEXT, 15, 0);

        g4 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g4, L"contraseña");
        SendMessage(g4, EM_SETLIMITTEXT, 10, 0);

        g5 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g5, L"Comercio");
        SendMessage(g5, EM_SETLIMITTEXT, 15, 0);

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g3, (LPWSTR)usu, sizeof(usu));
            wcscpy_s(PH, usu);
            VANUMSIM(hwnd, PH);

            if (Cvalid == true) {
                validar1 = lista1;
                while ((validar1 != nullptr) && (wcscmp(usu, validar1->nomusuario) != 0)) {

                    validar1 = validar1->siguiente;

                }
                if (validar1 == nullptr) {
                    GetWindowText(g4, (LPWSTR)cont, sizeof(cont));

                    ContraValid(hwnd, cont);



                    if (Cvalid == true) {
                        GetWindowText(g5, (LPWSTR)comer, sizeof(comer));
                        wcscpy_s(nomcom, L"{PENDIENTE}");
                        wcscpy_s(ali, L"{PENDIENTE}");
                        wcscpy_s(img, L"Perfil.bmp");
                        newus = true;
                       /* adm = false;*/

                        actual = lista1;
                        comernew = false;
                        while ((actual != nullptr) && (wcscmp(comer, actual->comercio) != 0)) {

                            actual = actual->siguiente;

                        }

                        if (actual == nullptr) {
                            comernew = true;
                        }
                        if (comernew == false) {
                            numcom = actual->numcomer;
                            adm = false;
                            
                        }
                        else {
                            l++;
                            numcom = l;
                            adm = true;
                           /* adad = true;*/
                            MessageBox(hwnd, L"Se le han otorgado permisos de administrador al ser el primer usuario de su comercio.", L"Aviso", MB_ICONINFORMATION);
                        }
                        newus = true;
                        agregar_usuario(lista1, usu, nomcom, cont, comer, ali, numcom, adm, newus, img);
                        //DestroyWindow(hwnd);
                        MessageBox(hwnd, L"Usuario Registrado", L"Nuevo usuario", MB_ICONINFORMATION);
                        EndDialog(hwnd, wParam);
                    }
                    else {

                        MessageBox(hwnd, L"La contraseña tiene que tener un numero, un simbolo, y una letra sin espacios", L"Aviso", MB_ICONEXCLAMATION);
                    }
                }
                else {

                    MessageBox(hwnd, L"Ya hay un usuario con ese nombre", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            else {

                MessageBox(hwnd, L"El nombre de usuario solo puede llevar letras", L"Aviso", MB_ICONEXCLAMATION);
            }
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

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap1 = (HBITMAP)LoadImage(NULL, actual->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);

        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo nombre completo");
       
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese nuevo alias");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese nueva foto de usuario");

        g6 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g6, actual->nombrecom);
        SendMessage(g6, EM_SETLIMITTEXT, 50, 0);

        g7 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g7, actual->alias);
        SendMessage(g7, EM_SETLIMITTEXT, 10, 0);

        
        wcscpy_s(img, actual->imagen);
        

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
           
            GetWindowText(g6, (LPWSTR)nombre, sizeof(nombre));
            wcscpy_s(PH, nombre);
            VANUMSIM(hwnd, PH);
            if (Cvalid == true) {
                
                GetWindowText(g7, (LPWSTR)alias, sizeof(alias));
                wcscpy_s(PH, alias);
                VASIM(hwnd, PH);
                if (Cvalid == true) {
                    wcscpy_s(actual->nombrecom, nombre);
                    wcscpy_s(actual->alias, alias);
                    wcscpy_s(actual->imagen, img);
                    actual->NewUsuario = false;
                    regresar = false;
                    MessageBox(hwnd, L"Usuario Actualizado", L"Actualizar usuario", MB_ICONINFORMATION);
                    EndDialog(hwnd, wParam);
                }
                else {

                    MessageBox(hwnd, L"El alias solo puede llevar letras", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            else {

                MessageBox(hwnd, L"El nombre solo puede llevar letras", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;
        case IDC_BUTTON2:
            regresar = true;
            EndDialog(hwnd, wParam);
            break;
        case IDC_BUTTON3:

            AbrirImagen(hwnd);
            
            hBitmap1 = (HBITMAP)LoadImage(NULL, img, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);
            
            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap1);
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
        SendMessage(g8, EM_SETLIMITTEXT, 15, 0);

        g9 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g9, L"contrasena");
        SendMessage(g9, EM_SETLIMITTEXT, 10, 0);

        g10 = GetDlgItem(hwnd, IDC_CHECK1);
        SetWindowText(g10, L"Admin");

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g8, (LPWSTR)usu, sizeof(usu));
            
            Cvalid = false;
            CV1 = 0, CV2 = 0;
            while ((usu[CV1] != L'\0') && (CV1 < 15)) {
                CV2 = 0;
                while (CV2 < 10) {
                    if (usu[CV1] == Validar1[CV2]) {

                        Cvalid = false;
                        CV1 = 15;
                        CV2 = 10;
                    }
                    else {
                        Cvalid = true;
                    }
                    CV2++;
                }
                CV1++;
            }
            if (Cvalid == true) {
                validar1 = lista1;
                while ((validar1 != nullptr) && (wcscmp(usu, validar1->nomusuario) != 0)) {

                    validar1 = validar1->siguiente;

                }
                if (validar1 == nullptr) {
                    GetWindowText(g9, (LPWSTR)cont, sizeof(cont));
                    ContraValid(hwnd, cont);



                    if (Cvalid == true) {
                        wcscpy_s(comer, actual->comercio);
                        wcscpy_s(nomcom, L"{PENDIENTE}");
                        wcscpy_s(ali, L"{PENDIENTE}");
                        wcscpy_s(img, L"Perfil.bmp");
                        numcom = actual->numcomer;
                        IsDlgButtonChecked(hwnd, IDC_CHECK1);

                        if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                            adm = true;
                        }
                        else if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                            adm = false;
                        }
                        newus = true;
                        agregar_usuario(lista1, usu, nomcom, cont, comer, ali, numcom, adm, newus, img);
                        MessageBox(hwnd, L"Usuario Registrado", L"Nuevo usuario", MB_ICONINFORMATION);
                        EndDialog(hwnd, wParam);
                    }
                    else {

                        MessageBox(hwnd, L"La contraseña tiene que tener un numero, un simbolo, y una letra sin espacios", L"Aviso", MB_ICONEXCLAMATION);
                    }
                }
                else {

                    MessageBox(hwnd, L"Ya hay un usuario con ese nombre", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            else {

                MessageBox(hwnd, L"El nombre de usuario no puede llevar numeros", L"Aviso", MB_ICONEXCLAMATION);
            }

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
        SetWindowText(h_edit, actual->contraseña);


        g11 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g11, L"nueva contraseña");
        SendMessage(g11, EM_SETLIMITTEXT, 10, 0);
        

        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g11, (LPWSTR)cont, sizeof(cont));
            
            ContraValid(hwnd, cont);

            if (Cvalid == true) {
            wcscpy_s(actual->contraseña, cont);
            regresar = false;
            MessageBox(hwnd, L"Contraseña Actualizada", L"Actualizar contraseña", MB_ICONINFORMATION);
            EndDialog(hwnd, wParam);
            }
            else {

                MessageBox(hwnd, L"La contraseña tiene que tener un numero, un simbolo, y una letra sin espacios", L"Aviso", MB_ICONEXCLAMATION);
            }
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
        SetWindowText(h_edit, buscar1->contraseña);


        g23 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g23, L"nueva contraseña");
        SendMessage(g23, EM_SETLIMITTEXT, 10, 0);


        break;


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
            GetWindowText(g23, (LPWSTR)cont, sizeof(cont));
            ContraValid(hwnd, cont);
            if (Cvalid == true) {
                wcscpy_s(buscar1->contraseña, cont);
                MessageBox(hwnd, L"Contraseña Actualizada", L"Actualizar contraseña", MB_ICONINFORMATION);
                regresar = false;
                EndDialog(hwnd, wParam);
            }
            else {

                MessageBox(hwnd, L"La contraseña tiene que tener un numero, un simbolo, y una letra sin espacios", L"Aviso", MB_ICONEXCLAMATION);
            }
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

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap3 = (HBITMAP)LoadImage(NULL, buscar1->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);

        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
        SetWindowText(h_edit, L"Actualizar usuario");
        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
        SetWindowText(h_edit, L"Eliminar usuario");
        a4 = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(a4, buscar1->nomusuario);
        a5 = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(a5, buscar1->nombrecom);
        a6 = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(a6, buscar1->alias);
        a7 = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(a7, buscar1->comercio);
        a8 = GetDlgItem(hwnd, IDC_STATIC5);
       
        if (buscar1->Admin == true) {
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
            
            SetWindowText(a4, buscar1->nomusuario);
           
            SetWindowText(a5, buscar1->nombrecom);
            
            SetWindowText(a6, buscar1->alias);
           
            SetWindowText(a7, buscar1->comercio);
            
            if (buscar1->Admin == true) {
                SetWindowText(a8, L"Admin: Si");
            }
            else {
                SetWindowText(a8, L"Admin: No");
            }
            hBitmap3 = (HBITMAP)LoadImage(NULL, buscar1->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap3);
            break;
        case IDC_BUTTON2:
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
                if (confirmar == true) {
                    if (wcscmp(actual->nomusuario, Buscar_Usuario) == 0) {
                        MessageBox(hwnd, L"No puede eliminar el usuario actual", L"Aviso", MB_ICONSTOP);
                    }
                    else {
                        borrar_usuario(lista1, Buscar_Usuario);
                        MessageBox(hwnd, L"Usuario Eliminado", L"Eliminar usuario", MB_ICONINFORMATION);
                        EndDialog(hwnd, wParam);
                    }
                }
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
            }
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap3);
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

        hPictureControl = GetDlgItem(hwnd, IDC_PICTUREC);
        hBitmap4 = (HBITMAP)LoadImage(NULL, buscar1->imagen, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
        SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);
        

        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, L"Ingrese nuevo usuario");

        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        SetWindowText(h_edit, L"Ingrese nuevo nombre completo");

        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        SetWindowText(h_edit, L"Ingrese nuevo alias");

        h_edit = GetDlgItem(hwnd, IDC_CHECK1);
        SetWindowText(h_edit, L"Administrador");
        if (buscar1->Admin) {
            SendDlgItemMessage(hwnd, IDC_CHECK1, BM_SETCHECK, (WPARAM)BST_CHECKED, 0);
        }
        else {
            SendDlgItemMessage(hwnd, IDC_CHECK1, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
        }
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        SetWindowText(h_edit, L"Ingrese nueva foto de usuario");

        g12 = GetDlgItem(hwnd, IDC_EDIT1);
        SetWindowText(g12, buscar1->nomusuario);
        SendMessage(g12, EM_SETLIMITTEXT, 15, 0);

        g13 = GetDlgItem(hwnd, IDC_EDIT2);
        SetWindowText(g13, buscar1->nombrecom);
        SendMessage(g13, EM_SETLIMITTEXT, 50, 0);

        g14 = GetDlgItem(hwnd, IDC_EDIT3);
        SetWindowText(g14, buscar1->alias);
        SendMessage(g14, EM_SETLIMITTEXT, 10, 0);
        
        wcscpy_s(img, buscar1->imagen);
        
        
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
            wcscpy_s(PH, usuarioq);
            VANUMSIM(hwnd, PH);
            if (Cvalid == true) {

                validar1 = lista1;
                while ((validar1 != nullptr) && ((wcscmp(usuarioq, validar1->nomusuario) != 0) || (wcscmp(usuarioq, buscar1->nomusuario) == 0))) {

                    validar1 = validar1->siguiente;

                }
                if (validar1 == nullptr) {
                    GetWindowText(g13, (LPWSTR)nombre, sizeof(nombre));
                    wcscpy_s(PH, nombre);
                    VANUMSIM(hwnd, PH);
                    if (Cvalid == true) {
                        GetWindowText(g14, (LPWSTR)alias, sizeof(alias));
                        wcscpy_s(PH, alias);
                        VASIM(hwnd, PH);
                        if (Cvalid == true) {
                            wcscpy_s(buscar1->nomusuario, usuarioq);
                            wcscpy_s(buscar1->nombrecom, nombre);
                            wcscpy_s(buscar1->alias, alias);         
                            wcscpy_s(buscar1->imagen, img);
                            buscar1->NewUsuario = false;
                            MessageBox(hwnd, L"Usuario Actualizado", L"Actualizar usuario", MB_ICONINFORMATION);
                            EndDialog(hwnd, wParam);
                        }
                        else {

                            MessageBox(hwnd, L"El alias solo puede llevar caracteres alfanumericos", L"Aviso", MB_ICONEXCLAMATION);
                        }
                    }
                    else {

                        MessageBox(hwnd, L"El nombre solo puede llevar letras", L"Aviso", MB_ICONEXCLAMATION);
                    }
                }
                else {
                    MessageBox(hwnd, L"Ya hay un usuario con ese nombre", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            else {

                MessageBox(hwnd, L"El nombre de usuario no puede llevar numeros", L"Aviso", MB_ICONEXCLAMATION);
            }
            break;
        case IDC_BUTTON2:

            EndDialog(hwnd, wParam);
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON3:
            AbrirImagen(hwnd);
            
            hBitmap4 = (HBITMAP)LoadImage(NULL, img, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
            SendDlgItemMessage(hwnd, IDC_PICTUREC, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap4);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        DeleteObject((HBITMAP)hBitmap4);
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
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
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
           
       

        g24 = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
        GetWindowText(g24, (LPWSTR)fech, sizeof(fech));
        h_edit = GetDlgItem(hwnd, IDC_STATIC6);
        SetWindowText(h_edit, fech);
        
        if (nuevo == true) {
            g15 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g15, L"nuevo cliente");
            g16 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g16, L"alias");
            g17 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g17, L"telefono");
            g18 = GetDlgItem(hwnd, IDC_EDIT4);
            SetWindowText(g18, L"correo");
           
            
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
        SendMessage(g15, EM_SETLIMITTEXT, 50, 0);
        SendMessage(g16, EM_SETLIMITTEXT, 15, 0);
        SendMessage(g17, EM_SETLIMITTEXT, 10, 0);
        SendMessage(g18, EM_SETLIMITTEXT, 25, 0);
        break;

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
                wcscpy_s(PH, nomclien);
                VANUMSIM(hwnd, PH);

                if (Cvalid == true) {
                    validar2 = lista2;
                    while ((validar2 != nullptr) && (wcscmp(nomclien, validar2->nomcliente) != 0)) {

                        validar2 = validar2->siguiente;

                    }
                    if (validar2 == nullptr) {
                        GetWindowText(g16, (LPWSTR)alic, sizeof(alic));
                        wcscpy_s(PH, alic);
                        VANUMSIM(hwnd, PH);
                        if (Cvalid == true) {
                            GetWindowText(g17, (LPWSTR)tel, sizeof(tel));
                            Cvalid = false;
                            CV1 = 0;
                            while (CV1 < 10) {
                               
                                if (tel[CV1] == L'\0') {
                                    Cvalid = false;
                                    CV1 = 10;

                                }
                                else {
                                    Cvalid = true;
                                }
                                    
                                CV1++;
                            }
                            if (Cvalid == true) {
                                GetWindowText(g18, (LPWSTR)ema, sizeof(ema));
                                Cvalid = false;
                                CV1 = 0;
                                while (CV1 < 10) {
                                    CV2 = 0;
                                    while (CV2 < 27) {
                                        if (ema[CV1] == Validar3[CV2]) {

                                            Cvalid = true;
                                            CV1 = 10;
                                            CV2 = 27;
                                        }
                                        else {
                                            Cvalid = false;
                                        }
                                        CV2++;
                                    }
                                    CV1++;
                                }
                                if (Cvalid == true) {
                                    Cvalid = false;
                                    CV1 = 0;
                                    while (CV1 < 25) {

                                        if (ema[CV1] == L'@') {
                                            Cvalid = true;
                                            CV1 = 25;

                                        }
                                        else {
                                            Cvalid = false;
                                        }

                                        CV1++;
                                    }
                                }
                                if (Cvalid == true) {
                                    Cvalid = false;
                                    CV1 = 0;
                                    while (CV1 < 25) {

                                        if (ema[CV1] == L'.') {
                                            Cvalid = true;
                                            CV1 = 25;

                                        }
                                        else {
                                            Cvalid = false;
                                        }

                                        CV1++;
                                    }
                                }
                               
                                if (Cvalid==true){
                                GetWindowText(g24, (LPWSTR)fech, sizeof(fech));
                                //wcscpy_s(fecha, L"Ahora");
                                wcscpy_s(comerc, actual->comercio);
                                numcomc = actual->numcomer;

                                agregar_cliente(lista2, nomclien, alic, tel, ema, comerc, fech, numcomc);
                                MessageBox(hwnd, L"Cliente Registrado", L"Registrar cliente", MB_ICONINFORMATION);
                                EndDialog(hwnd, wParam);
                                }
                                else {
                                    MessageBox(hwnd, L"Ingrese un correo válido", L"Aviso", MB_ICONEXCLAMATION);
                                }
                            }
                            else {
                                MessageBox(hwnd, L"Ingrese un teléfono válido", L"Aviso", MB_ICONEXCLAMATION);
                            }
                        }
                        else {
                            MessageBox(hwnd, L"El alias solo puede contener letras", L"Aviso", MB_ICONEXCLAMATION);
                        }
                    }
                    else {
                        MessageBox(hwnd, L"Ya hay un cliente registrado con ese nombre", L"Aviso", MB_ICONEXCLAMATION);
                    }
                }
                else {
                    MessageBox(hwnd, L"El nombre solo puede contener letras", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            else {
                GetWindowText(g15, (LPWSTR)nomclien, sizeof(nomclien));
                wcscpy_s(PH, nomclien);
                VANUMSIM(hwnd, PH);

                if (Cvalid == true) {
                    validar2 = lista2;
                    while ((validar2 != nullptr) && ((wcscmp(nomclien, validar2->nomcliente) != 0) || (wcscmp(nomclien, buscar2->nomcliente) == 0))) {

                        validar2 = validar2->siguiente;

                    }
                    if (validar2 == nullptr) {
                        GetWindowText(g16, (LPWSTR)alic, sizeof(alic));
                        wcscpy_s(PH, alic);
                        VANUMSIM(hwnd, PH);
                        if (Cvalid == true) {
                            GetWindowText(g17, (LPWSTR)tel, sizeof(tel));
                            Cvalid = false;
                            CV1 = 0;
                            while (CV1 < 10) {

                                if (tel[CV1] == L'\0') {
                                    Cvalid = false;
                                    CV1 = 10;

                                }
                                else {
                                    Cvalid = true;
                                }

                                CV1++;
                            }
                            if (Cvalid == true) {
                                GetWindowText(g18, (LPWSTR)ema, sizeof(ema));
                                Cvalid = false;
                                CV1 = 0;
                                while (CV1 < 10) {
                                    CV2 = 0;
                                    while (CV2 < 27) {
                                        if (ema[CV1] == Validar3[CV2]) {

                                            Cvalid = true;
                                            CV1 = 10;
                                            CV2 = 27;
                                        }
                                        else {
                                            Cvalid = false;
                                        }
                                        CV2++;
                                    }
                                    CV1++;
                                }
                                if (Cvalid == true) {
                                    Cvalid = false;
                                    CV1 = 0;
                                    while (CV1 < 25) {

                                        if (ema[CV1] == L'@') {
                                            Cvalid = true;
                                            CV1 = 25;

                                        }
                                        else {
                                            Cvalid = false;
                                        }

                                        CV1++;
                                    }
                                }
                                if (Cvalid == true) {
                                    Cvalid = false;
                                    CV1 = 0;
                                    while (CV1 < 25) {

                                        if (ema[CV1] == L'.') {
                                            Cvalid = true;
                                            CV1 = 25;

                                        }
                                        else {
                                            Cvalid = false;
                                        }

                                        CV1++;
                                    }
                                }

                                if (Cvalid == true) {
                                    GetWindowText(g24, (LPWSTR)fech, sizeof(fech));
                                    //wcscpy_s(fecha, L"Ahora");
                                    wcscpy_s(comerc, actual->comercio);

                                    wcscpy_s(buscar2->nomcliente, nomclien);
                                    wcscpy_s(buscar2->alias, alic);
                                    wcscpy_s(buscar2->telefono, tel);
                                    wcscpy_s(buscar2->email, ema);
                                    wcscpy_s(buscar2->comercio, comerc);
                                    wcscpy_s(buscar2->fecha, fech);
                                    buscar2->numcomer = actual->numcomer;
                                    MessageBox(hwnd, L"Cliente Actualizado", L"Actualizar cliente", MB_ICONINFORMATION);
                                    EndDialog(hwnd, wParam);
                                }
                                else {
                                    MessageBox(hwnd, L"Ingrese un correo válido", L"Aviso", MB_ICONEXCLAMATION);
                                }
                            }
                            else {
                                MessageBox(hwnd, L"Ingrese un teléfono válido", L"Aviso", MB_ICONEXCLAMATION);
                            }
                        }
                        else {
                            MessageBox(hwnd, L"El alias solo puede contener letras", L"Aviso", MB_ICONEXCLAMATION);
                        }
                    }
                    else {
                        MessageBox(hwnd, L"Ya hay un cliente registrado con ese nombre", L"Aviso", MB_ICONEXCLAMATION);
                    }
                }
                else {
                MessageBox(hwnd, L"El nombre solo puede contener letras", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
           
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

        h_listbox4 = GetDlgItem(hwnd, IDC_LIST1);


        listado_consclien(lista4);

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
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
                if (confirmar == true) {
                    borrar_cliente(lista2, Buscar_Cliente);
                    MessageBox(hwnd, L"Cliente Eliminado", L"Eliminar cliente", MB_ICONEXCLAMATION);
                    EndDialog(hwnd, wParam);
                }
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONEXCLAMATION);
            }
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON3:
            wcscpy_s(Consumo_Cliente, L"NULL");
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Consumo_Cliente);

            if (wcscmp(Consumo_Cliente, L"NULL") == 0) {
                MessageBox(hwnd, L"No se seleccionó una opción", L"Aviso", MB_ICONEXCLAMATION);
                
            }
            else {
                buscar4 = lista4;
                while ((buscar4 != nullptr) && ((wcscmp(Consumo_Cliente, buscar4->consumo) != 0))) {

                    buscar4 = buscar4->siguiente;
                }
                DialogBox(NULL, MAKEINTRESOURCE(IDD_TOTAL), hwnd, (DLGPROC)Total);
            }
            

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        //DeleteObject((HBITMAP)hBitmap);
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
        
        g25 = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);
        GetWindowText(g25, (LPWSTR)date, sizeof(date));
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        SetWindowText(h_edit, date);
        

        if (nuevo == true) {
            g19 = GetDlgItem(hwnd, IDC_EDIT1);
            SetWindowText(g19, L"nueva promocion");
            g20 = GetDlgItem(hwnd, IDC_EDIT2);
            SetWindowText(g20, L"nuevo monto");
            g21 = GetDlgItem(hwnd, IDC_EDIT3);
            SetWindowText(g21, L"nuevo porcentaje");
            
          
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
        SendMessage(g19, EM_SETLIMITTEXT, 50, 0);
      
        break;

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
                wcscpy_s(PH, promo);
                VANUMSIM(hwnd, PH);
                if (Cvalid == true) {
                    GetWindowText(g20, (LPWSTR)monto, sizeof(monto));
                    cant = _wtof(monto);
                    validar3 = lista3;
                    while ((validar3 != nullptr) && ((wcscmp(promo, validar3->nompromo) != 0) && (cant != validar3->cantidad))) {

                        validar3 = validar3->siguiente;

                    }
                    if (validar3 == nullptr) {

                        if (cant > 100) {
                            GetWindowText(g21, (LPWSTR)porcentaje, sizeof(porcentaje));
                            por = _wtof(porcentaje);
                            if (por > 0 && por < 100) {
                                GetWindowText(g25, (LPWSTR)date, sizeof(date));

                                IsDlgButtonChecked(hwnd, IDC_CHECK1);
                                numcomp = actual->numcomer;

                                if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
                                    act = true;
                                }
                                else if (SendDlgItemMessage(hwnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
                                    act = false;
                                }


                                agregar_promo(lista3, promo, date, cant, por, act, numcomp);
                                MessageBox(hwnd, L"Promocion Registrada", L"Registrar promocion", MB_ICONINFORMATION);
                                EndDialog(hwnd, wParam);
                            }
                            else {
                                MessageBox(hwnd, L"El descuento tiene que ser menor al 100% y mayoR a 0", L"Aviso", MB_ICONEXCLAMATION);
                            }
                        }
                        else {
                            MessageBox(hwnd, L"El monto tiene que ser mayor a 100", L"Aviso", MB_ICONEXCLAMATION);
                        }

                    }
                    else {
                        MessageBox(hwnd, L"Ya hay una promoción registrada con ese nombre o monto", L"Aviso", MB_ICONEXCLAMATION);
                    }

                }
                else {
                    MessageBox(hwnd, L"El nombre de la promoción solo puede contener letras", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            else {
                GetWindowText(g19, (LPWSTR)promo, sizeof(promo));
                wcscpy_s(PH, promo);
                VANUMSIM(hwnd, PH);
                if (Cvalid == true) {
                    GetWindowText(g20, (LPWSTR)monto, sizeof(monto));
                    cant = _wtof(monto);
                    validar3 = lista3;

                    while ((validar3 != nullptr) && (((wcscmp(promo, validar3->nompromo) != 0) || (wcscmp(promo, buscar3->nompromo) == 0)) && ((cant != validar3->cantidad) || (cant == buscar3->cantidad)))) {

                        validar3 = validar3->siguiente;

                    }
                    if (validar3 == nullptr) {
                        buscar3->cantidad = _wtof(monto);
                        if (buscar3->cantidad > 100) {
                            GetWindowText(g21, (LPWSTR)porcentaje, sizeof(porcentaje));


                            buscar3->porcentaje = _wtof(porcentaje);
                            if (buscar3->porcentaje > 0 && buscar3->porcentaje < 100) {
                                GetWindowText(g25, (LPWSTR)date, sizeof(date));
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

                                MessageBox(hwnd, L"Promocion Actualizada", L"Actualizar promocion", MB_ICONINFORMATION);
                                EndDialog(hwnd, wParam);
                            }
                            else {
                                MessageBox(hwnd, L"El descuento tiene que ser menor al 100% y mayoR a 0", L"Aviso", MB_ICONEXCLAMATION);
                            }
                        }
                        else {
                            MessageBox(hwnd, L"El monto tiene que ser mayor a 100", L"Aviso", MB_ICONEXCLAMATION);
                        }
                    }

                    else {
                        MessageBox(hwnd, L"Ya hay una promoción registrada con ese nombre o monto", L"Aviso", MB_ICONEXCLAMATION);
                    }
                }
                else {
                    MessageBox(hwnd, L"El nombre de la promoción solo puede contener letras", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
            

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
        wcscat_s(dummy, L"%");
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
            if (actual->Admin == true) {
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
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
            }
            break;
        case IDC_BUTTON2:
            if (actual->Admin == true) {
                DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
                if (confirmar == true) {
                    borrar_promo(lista3, Buscar_Promo);
                    MessageBox(hwnd, L"Promocion Eliminada", L"Eliminar promocion", MB_ICONINFORMATION);
                    EndDialog(hwnd, wParam);
                }
            }
            else {
                MessageBox(hwnd, L"No tiene acceso a esta opción.", L"Aviso", MB_ICONSTOP);
            }
            //CloseWindow(hwnd);

            break;
        case IDC_BUTTON5:
            EndDialog(hwnd, wParam);


            break;
        }
        break;
    case WM_CLOSE:
        //DeleteObject((HBITMAP)hBitmap);
        DestroyWindow(hwnd);
        DestroyMenu(hMenu);
        //DestroyWindow(ghDlg);
        break;
    }
    return FALSE;
}
//Consumos------------------------------------------------------------------------------------------------------------------------
void agregar_comsumo(consumos*& lista4, wchar_t cons[50], wchar_t datec[50], wchar_t ccons[50], int mont, int sub, int desc, int tot, int numcomco) {

    consumos* nuevo_consumo = new consumos();
    consumos* aux;

    wcscpy_s(nuevo_consumo->consumo, cons);
    wcscpy_s(nuevo_consumo->fecha, datec);
    wcscpy_s(nuevo_consumo->cliente, ccons);
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
       
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        //_itow_s(Precio_Global, PG, 20, 10);
        swprintf_s(PG, L"%.1f", Precio_Global);
        SetWindowText(h_edit, PG);
        g26 = GetDlgItem(hwnd, IDC_DATETIMEPICKER1);

        h_listbox2 = GetDlgItem(hwnd, IDC_LIST1);
        listado_clientes(lista2);


    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
           
        case IDC_BUTTON1:
            
            buscar2 = lista2;

            wcscpy_s(Cliente_Consumo, L"NULL");
            index = SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
            SendDlgItemMessage(hwnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)Cliente_Consumo);

            if (wcscmp(Cliente_Consumo, L"No hay clientes para este comercio") == 0) {
                MessageBox(hwnd, L"No hay clientes registrados", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else if (wcscmp(Cliente_Consumo, L"NULL") == 0) {
                MessageBox(hwnd, L"No se seleccionó una opción", L"Aviso", MB_ICONEXCLAMATION);
                regresar = true;
            }
            else {
                while ((buscar2 != nullptr) && ((wcscmp(Cliente_Consumo, buscar2->nomcliente) != 0) || (actual->numcomer != buscar2->numcomer))) {

                    buscar2 = buscar2->siguiente;
                }
                regresar = false;


                //regresar = false;
                wchar_t j[2];
                wcscpy_s(cons, L"Orden #");
                _itow_s(ñ + 1, j, 2, 10);
                wcscat_s(cons, j);
                wcscat_s(cons, L": ");
                wcscat_s(cons, Cliente_Consumo);
                wcscpy_s(ccons, Cliente_Consumo);
                //desc = 20;





                GetWindowText(g22, (LPWSTR)montocons, sizeof(montocons));


                mont = _wtof(montocons);
                if (mont != 0) {
                    GetWindowText(g26, (LPWSTR)datec, sizeof(datec));
                    buscar3 = lista3;
                    while ((buscar3 != nullptr) && ((mont != buscar3->cantidad) || (actual->numcomer != buscar3->numcomer) || (buscar3->activo == false))) {

                        buscar3 = buscar3->siguiente;
                    }
                    if (buscar3 == nullptr) {
                        desc = 0;
                    }
                    else {
                        desc = buscar3->porcentaje;
                    }
                    sub = mont * Precio_Global;
                    tot = (sub - (sub * desc / 100));
                    numcomco = actual->numcomer;

                    agregar_comsumo(lista4, cons, datec, ccons, mont, sub, desc, tot, numcomco);

                    EndDialog(hwnd, wParam);
                }
                else {
                    MessageBox(hwnd, L"El monto no puede ser 0", L"Aviso", MB_ICONEXCLAMATION);
                }
            }
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
//BOOL CALLBACK ActCons(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//    switch (uMsg) {
//    case WM_CREATE:
//    case WM_INITDIALOG:
//
//
//        h_edit = GetDlgItem(hwnd, IDC_BUTTON1);
//        SetWindowText(h_edit, L"Actualizar ");
//        h_edit = GetDlgItem(hwnd, IDC_BUTTON2);
//        SetWindowText(h_edit, L"Eliminar promocion");
//        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
//        SetWindowText(h_edit, buscar4->consumo);
//        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
//        _itow_s(buscar4->monto, montocons, 2, 10);
//        SetWindowText(h_edit, montocons);
//        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
//        _itow_s(buscar4->de)
//        SetWindowText(h_edit, porcentaje);
//        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
//        SetWindowText(h_edit, activa);
//        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
//        SetWindowText(h_edit, fecha);
//
//        break;
//    case WM_COMMAND:
//        switch (LOWORD(wParam))
//        {
//        case ID_ARCHIVO_GUARDAR:
//            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
//            break;
//        case ID_ARCHIVO_GUARDARCOMO:
//            MessageBox(hwnd, L"mensaje", L"titulo", MB_ICONEXCLAMATION);
//            break;
//        case IDC_BUTTON1:
//            DialogBox(NULL, MAKEINTRESOURCE(IDD_NEWPROM), hwnd, (DLGPROC)NuevPromo);
//            CloseWindow(hwnd);
//           
//            break;
//        case IDC_BUTTON2:
//            DialogBox(NULL, MAKEINTRESOURCE(IDD_CONFIRMAR), hwnd, (DLGPROC)Confirmar);
//            if (confirmar == true) {
//                MessageBox(hwnd, L"Promocion Eliminada", L"Eliminar promocion", MB_ICONEXCLAMATION);
//                EndDialog(hwnd, wParam);
//            }
//            
//            CloseWindow(hwnd);
//
//            break;
//        case IDC_BUTTON5:
//            EndDialog(hwnd, wParam);
//
//
//            break;
//        }
//        break;
//    case WM_CLOSE:
//        DeleteObject((HBITMAP)hBitmap);
//        DestroyWindow(hwnd);
//        DestroyMenu(hMenu);
//        DestroyWindow(ghDlg);
//        break;
//    }
//    return FALSE;
//}
BOOL CALLBACK TotalA(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:


        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(h_edit, cons);
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, datec);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        //_itow_s(sub, subtotal, 20, 10);
        swprintf_s(subtotal, L"%.1f", sub);
        SetWindowText(h_edit, subtotal);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        //_itow_s(desc, descuento, 20, 10);
        swprintf_s(descuento, L"%.1f", desc);
        wcscat_s(descuento, L"%");
        SetWindowText(h_edit, descuento);
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        //_itow_s(tot, total, 20, 10);
        swprintf_s(total, L"%.1f", tot);
        SetWindowText(h_edit, total);
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        wcscat_s(montocons, L" piezas");
        SetWindowText(h_edit, montocons);

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
BOOL CALLBACK Total(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
    case WM_INITDIALOG:


        h_edit = GetDlgItem(hwnd, IDC_STATIC0);
        SetWindowText(h_edit, buscar4->consumo);
        h_edit = GetDlgItem(hwnd, IDC_STATIC1);
        SetWindowText(h_edit, buscar4->fecha);
        h_edit = GetDlgItem(hwnd, IDC_STATIC2);
        //_itow_s(buscar4->subtotal, subtotal, 20, 10);
        swprintf_s(subtotal, L"%.1f", buscar4->subtotal);
        SetWindowText(h_edit, subtotal);
        h_edit = GetDlgItem(hwnd, IDC_STATIC3);
        //_itow_s(buscar4->descuento, descuento, 20, 10);
        swprintf_s(descuento, L"%.1f", buscar4->descuento);
        wcscat_s(descuento, L"%");
        SetWindowText(h_edit, descuento);
        h_edit = GetDlgItem(hwnd, IDC_STATIC4);
        //_itow_s(buscar4->total, total, 20, 10);
        swprintf_s(total, L"%.1f", buscar4->total);
        SetWindowText(h_edit, total);
        h_edit = GetDlgItem(hwnd, IDC_STATIC5);
        _itow_s(buscar4->monto, montocons, 20, 10);
        wcscat_s(montocons, L" piezas");
        SetWindowText(h_edit, montocons);
      


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
