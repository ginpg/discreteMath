#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <string.h>
using namespace std;

//																Giselt Parra, 26.609.640
//											Seccion C1 (la salida esta escrita sin acentos para evitar inconvenientes)
    string linea;
    queue<char> cb,cd;
    ifstream entrada;
    int n_a,cuenta = 0;
    FILE *archivo_d = fopen("PARRA_GISELT.out", "w+");
    vector<char> orden;

    //Vertices
    struct Vertice {
      char id;
      int ub, ud, nro, th;
      vector <char> lista, vj, vjd;
    };
    Vertice v[27];

    //Lectura de datos
    void Datos() {
        getline(entrada, linea);
        while (linea.size() > 2) {
          v[linea[0]-'a'].lista.push_back(linea[2]);
          v[linea[0]-'a'].th = 1;
          v[linea[2]-'a'].th = 1;
          n_a++;
          getline(entrada, linea);
        }
        entrada.close();
}
    void Ordenamiento(){
        int i,j,temp;
        for (int o=0; o<27; o++){
             if (v[o].th == 1){
                for (i=v[o].lista.size()-1; i > 0; i--){
                    for (j=0; j < i; j++) {
                        if (v[v[o].lista[j]-'a'].nro > v[v[o].lista[j+1]-'a'].nro) {
                            temp = v[o].lista[j];
                            v[o].lista[j] = v[o].lista[j+1];
                            v[o].lista[j+1] = temp;
                        }
                    }
                }
             }
        }
}

    void A_Ordenamiento(){
        int i,j,temp;
        for (int o=0; o<27; o++){
             if (v[o].th == 1){
                for (i=v[o].vj.size()-1; i > 0; i--){
                    for (j=0; j < i; j++) {
                        if (v[v[o].vj[j]-'a'].id > v[v[o].vj[j+1]-'a'].id) {
                            temp = v[o].vj[j];
                            v[o].vj[j] = v[o].vj[j+1];
                            v[o].vj[j+1] = temp;
                        }
                    }
                }
             }
        }
}

    void P_Ordenamiento(){
        int i,j,temp;
        for (int o=0; o<27; o++){
             if (v[o].th == 1){
                for (i=v[o].vjd.size()-1; i > 0; i--){
                    for (j=0; j < i; j++) {
                        if (v[v[o].vjd[j]-'a'].id > v[v[o].vjd[j+1]-'a'].id) {
                            temp = v[o].vjd[j];
                            v[o].vjd[j] = v[o].vjd[j+1];
                            v[o].vjd[j+1] = temp;
                        }
                    }
                }
             }
        }
}

    void Reset(){
         for (int i=0; i<27; i++){
             v[i].id = '-';
             v[i].th = 0;
             v[i].ud = v[i].ub =0;
             v[i].nro = -1;
             v[i].lista.clear();
             v[i].vj.clear();
             v[i].vjd.clear();
         }
         n_a = 0;
         orden.clear();
}

//                                                                 BFS
   void BFS(char p){
        cb.push(p);
        while (!cb.empty()){
              for(std::size_t it=0; it < v[cb.front()-'a'].lista.size();++it){
                              if (v[v[cb.front()-'a'].lista[it]-'a'].ub == 0){
                                  v[cb.front()-'a'].ub = 1;
                                  v[v[cb.front()-'a'].lista[it]-'a'].ub = 1;
                                  cb.push( v[cb.front()-'a'].lista[it]);
                                  v[cb.front()-'a'].vj.push_back(v[cb.front()-'a'].lista[it]);
                              }
              }
              cb.pop();
        }

}
//                                                                 DFS
  void DFS(char p){
            for(std::size_t it=0; it < v[p-'a'].lista.size();++it){
                              if (v[v[p-'a'].lista[it]-'a'].ud == 0){
                                  v[p-'a'].ud = 1;
                                  v[v[p-'a'].lista[it]-'a'].ud = 1;
                                  DFS(v[p-'a'].lista[it]);
                                  v[p-'a'].vjd.push_back(v[p-'a'].lista[it]);
                              }
            }
}
int main() {
  int casos,i=0;
  Reset();
  entrada.open("tarea2.in", ios::in);
  getline(entrada, linea);
  casos = atoi(linea.c_str());

  for (int u = 1; u < casos + 1; u++) {
    fprintf(archivo_d, "Caso %d:\n", u);
    if (u != 1) {
      entrada.open("tarea2.in", ios::in);
      for (int x = 0; x < cuenta + u; x++){
        getline(entrada, linea);
		}
    }
    getline(entrada, linea);
    i=0;
    while (i<linea.size() and (linea[i]>96 and linea[i]<123)){
          orden.push_back(linea[i]);
          v[linea[i]-'a'].id = linea[i];
          v[linea[i]-'a'].nro = i/2;
          i= i+2;
    }
    Datos();
    Ordenamiento();
    //                                           BFS
    for (std::size_t ite=0; ite < orden.size();++ite){
        if (v[orden[ite]-'a'].ub == 0 and v[orden[ite]-'a'].th == 1){ BFS(orden[ite]);}
	}
    //                                          DFS
    for (std::size_t ite=0; ite < orden.size();++ite){
        if (v[orden[ite]-'a'].ud == 0 and v[orden[ite]-'a'].th == 1){DFS(orden[ite]);}
    }
 
    A_Ordenamiento();
    P_Ordenamiento();
    
    fprintf(archivo_d, "Busqueda en profundidad:\n");
    for (int i=0; i<27; i++){
        if (v[i].th == 1){
                   if (v[i].ud == 0){
                    fprintf(archivo_d,"%c\n",v[i].id);
                    }
                    for(std::size_t it=0; it < v[i].vjd.size();++it){
                        fprintf(archivo_d, "%c %c\n",v[i].id,v[i].vjd[it]);
                    }
        }
    }

    fprintf(archivo_d, "Busqueda en amplitud:\n");
    for (int i=0; i<27; i++){
        if (v[i].th == 1){
                   if (v[i].ud == 0){
                    fprintf(archivo_d,"%c\n",v[i].id);
                    }
                    for(std::size_t it=0; it < v[i].vj.size();++it){
                        fprintf(archivo_d, "%c %c\n",v[i].id,v[i].vj[it]);
                    }
        }
    }
    cuenta = cuenta + n_a + 1;
    Reset();
    fprintf(archivo_d,"\n");
  }
  entrada.close();
  fclose(archivo_d);
  return 0;
}
