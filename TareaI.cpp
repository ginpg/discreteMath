#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>  
using namespace std;

//																Giselt Parra, 26.609.640
//																		Seccion C1
string linea;
ifstream entrada;
int i, j, l, num, cuenta = 0;
FILE *archivo_d = fopen("PARRA_GISELT.out", "w+");
vector<string> po, poo;
size_t found;

//Actividades
struct A{
  int i,j,l,ht,hl,hi;
};

//Eventos
struct V {
  int id;
  int fp = 0, fr = -1, cr = 0;
  vector<A> listaf,listab;
};

class Grafo {
public:
  V v[100];
  A  aux;
  vector<A> orden, criticos, muestra;
  int ultimo = 0, o, n_a = 0, n_criticos = 0;

  Grafo() {}

  //Lectura de datos
  void Datos() {
    getline(entrada, linea);
    while (linea != "0") {
      
      found = linea.find("-");
      po.push_back(linea.substr(0,found));
      po.push_back(linea.substr(found+1,linea.size()) );
      i = atoi(po[0].c_str());
      v[i].id = i;
      
      found = po[1].find(" ");
      poo.push_back(po[1].substr(0,found));
      poo.push_back(po[1].substr(found+1,linea.size()) );
      j = atoi(poo[0].c_str());
      l = atoi(poo[1].c_str());
      
      aux.i = i;
      aux.j = j;
      if (j > ultimo)
                ultimo = j;
      aux.l = l;
      v[j].listab.push_back(aux);
      v[i].listaf.push_back(aux);
      orden.push_back(aux);
      n_a++;
      getline(entrada, linea);
      po.clear();
      poo.clear();
    }
    
    v[ultimo].id = ultimo;
    entrada.close();
}
  
  void CPM() {
	//FORWARD
    for (o = 1; o < ultimo + 1; o++) {
      for(std::size_t it=0; it < v[o].listaf.size();++it) {
        if (v[v[o].listaf[it].j].fp < (v[o].fp + v[o].listaf[it].l)){
          v[v[o].listaf[it].j].fp = (v[o].fp + v[o].listaf[it].l);
  
        }
      }
    }
    for (o = 1; o < ultimo + 1; o++) {
      for(std::size_t it=0; it < v[o].listaf.size();++it) {
        if (v[v[o].listaf[it].j].fp < (v[o].fp + v[o].listaf[it].l)){
          v[v[o].listaf[it].j].fp = (v[o].fp + v[o].listaf[it].l);
        }
      }
    }
    fprintf(archivo_d, "%d\n", v[ultimo].fp);
    v[ultimo].fr = v[ultimo].fp;
    
	//BACKWARD
    for (o = ultimo; o > 0; o--) {
      for(std::size_t it=0; it < v[o].listab.size();++it) {
    
        if (v[v[o].listab[it].i].fr == -1){
          v[v[o].listab[it].i].fr = (v[o].fr - v[o].listab[it].l);
      }
        else {
          if (v[v[o].listab[it].i].fr > (v[o].fr - v[o].listab[it].l)){
            v[v[o].listab[it].i].fr = (v[o].fr - v[o].listab[it].l);
          }
        }
      }
    }

    
    for (o = ultimo; o > 0; o--) {
      for(std::size_t it=0; it < v[o].listab.size();++it) {
        if (v[v[o].listab[it].i].fr == -1){
          v[v[o].listab[it].i].fr = (v[o].fr - v[o].listab[it].l);
      }
        else {
          if (v[v[o].listab[it].i].fr > (v[o].fr - v[o].listab[it].l)){
            v[v[o].listab[it].i].fr = (v[o].fr - v[o].listab[it].l);
          }
        }
      }
    }
    
  }
  
  //Limpieza de los datos del grafo para trabajar con el siguiente caso
  void Reset(){
    for (o = 1; o < ultimo + 1; o++) {
      v[o].listab.clear();
      v[o].listaf.clear();
      criticos.clear();
      v[o].fp = 0;
      v[o].fr = -1;
    }
    n_a = ultimo = 0;
  }
  
  //Calculo de holguras, actividades criticas y los eventos que perteneces a ellas 
  void Calculo() {
    for(std::size_t it=0; it < n_a;++it) {
      orden[it].ht = v[orden[it].j].fr - v[orden[it].i].fp - orden[it].l; 
      orden[it].hl = v[orden[it].j].fp - v[orden[it].i].fp - orden[it].l; 
      orden[it].hi = v[orden[it].j].fp - v[orden[it].i].fr - orden[it].l;
      if (orden[it].hi < 0)
        {orden[it].hi = 0;}
        
      if ((orden[it].ht == 0) and (orden[it].hl == 0) and (orden[it].hi == 0)){
        criticos.push_back(orden[it]);
        v[orden[it].j].cr = v[orden[it].i].cr = 1;
      }
    }
  }
  
  //Escribirlos caminos criticos
  void Criticos(int y) {
   if (y == ultimo){
      for(std::size_t it=0; it < muestra.size();++it){
        fprintf(archivo_d,"%d-%d ",muestra[it].i,muestra[it].j);
      }
    fprintf(archivo_d,"\n");
    return;
  }

      for(std::size_t it=0; it < v[y].listaf.size();++it) {
        for(std::size_t ite=0; ite < criticos.size();++ite){
          if (y == criticos[ite].i and v[y].listaf[it].j == criticos[ite].j){
            muestra.push_back(criticos[ite]);
            Criticos(criticos[ite].j);
            muestra.pop_back();
          }
        
        }
      }
  }
  
  //Escribir las holguras
  void Holguras(){
    for(std::size_t it=0; it < n_a;++it){
      fprintf(archivo_d, "%d-%d %d %d %d\n", orden[it].i, orden[it].j, orden[it].ht, orden[it].hl, orden[it].hi);
    }
    fprintf(archivo_d, "\n");
  }
  };

int main() {
  int casos;
  entrada.open("tarea1.in", ios::in);
  getline(entrada, linea);
  casos = atoi(linea.c_str());

  for (int u = 1; u < casos + 1; u++) {
    fprintf(archivo_d, "Caso %d:\n", u);
    Grafo g;
    if (u != 1) {
      entrada.open("tarea1.in", ios::in);
      for (int x = 0; x < cuenta + u; x++){
        getline(entrada, linea);
		}
    }
    g.Datos();
    g.CPM();
    g.Calculo();
    g.Criticos(1);
    g.Holguras();
    cuenta = cuenta + g.n_a;
    g.Reset();
  }
  entrada.close();
  fclose(archivo_d);
}
