#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <stdlib.h> 
using namespace std;

//	Giselt G. Parra G. 26.609.640
//	versión definitiva 

int i,e,o,u,t,ma,cuenta;
string linea;
FILE *file,*archivo_d;
queue<int> idos;
vector<int> orden;
char stringg[100];

struct S{
    int t1,t0,n,f;
    bool al;
    vector<int> refe;
};
S s[200];

void Datos(){
  //                                      leer estados
  i=0;
  e=0;
  while(i==0){
    e++;
    fscanf(file,"%s",stringg);
    if(fgetc(file) == '\n') i=1;
  }

  //                                inicializar estados
  for (i=0; i<e; i++) {
    s[i].n = 0;
    s[e].al = true;
    s[o].f = 0;
    s[o].al = false;
    ma = 1;
  }
  //                                  leer finales 
  i=0;
  u=0;
  while(i==0){
    fscanf(file,"%s",stringg);
    linea = std::string(stringg);
    o=atoi(linea.c_str());
    s[o].n = 1;
    s[o].f = 1;
    s[e+1].al = true;
    u++;
    if(fgetc(file) == '\n')i=1;
  }
  if (u==e){ma=0;} //si todos son finales
  //                                 leer transiciones
  for (i=0; i<e*2; i++) {
    fscanf(file,"%s",stringg);
    linea = std::string(stringg);
    o=atoi(linea.c_str());

    fscanf(file,"%s",stringg);
    linea = std::string(stringg);
    u=atoi(linea.c_str());

    fscanf(file,"%s",stringg);
    linea = std::string(stringg);
    t=atoi(linea.c_str());

    s[u].al = true;
    if (t==0)s[o].t0 = u;
    else if (t==1)s[o].t1 = u;
  }
  s[0].al = true;
}

void Mostrar(){
  for (i=0; i<e; i++) {
    if (s[i].n == 0) fprintf(archivo_d,"F\n");
    fprintf(archivo_d,"%d %d 0\n",i,s[i].t0);
    fprintf(archivo_d,"%d %d 1\n\n",i,s[i].t1);
  }
}

void MostrarN(){
  //                                         nuevos estados
  for (i=0; i<orden.size(); i++) {
    for (o=0; o<s[orden[i]].refe.size(); o++)  {
		if (o+1 < s[orden[i]].refe.size()) fprintf(archivo_d,"%d-",s[orden[i]].refe[o]);
		else fprintf(archivo_d,"%d ",s[orden[i]].refe[o]);
	}
    fprintf(archivo_d," ");
  }
  //                                     nuevos estados finales
  fprintf(archivo_d,"\n");
   for (i=0; i<orden.size(); i++) {
    if(s[orden[i]].f ==1 ){
      for (o=0; o<s[orden[i]].refe.size(); o++) 
		if (o+1 < s[orden[i]].refe.size()) fprintf(archivo_d,"%d-",s[orden[i]].refe[o]);
		else fprintf(archivo_d,"%d ",s[orden[i]].refe[o]);
      fprintf(archivo_d," ");
    }
  }
  fprintf(archivo_d,"\n");
  //                                     nuevas transiciones
  for (i=0; i<orden.size(); i++) {
      for (o=0; o<s[orden[i]].refe.size(); o++){
		 //0
			if (o+1 < s[orden[i]].refe.size()) fprintf(archivo_d,"%d-",s[orden[i]].refe[o]);
			else fprintf(archivo_d,"%d ",s[orden[i]].refe[o]);
      }
      fprintf(archivo_d," ");
        for (u=0; u<s[s[orden[i]].t0].refe.size(); u++){
			if (u+1 < s[s[orden[i]].t0].refe.size()) fprintf(archivo_d,"%d-",s[s[orden[i]].t0].refe[u]);
			else fprintf(archivo_d,"%d ",s[s[orden[i]].t0].refe[u]);
      }
      fprintf(archivo_d," 0\n");
      //1
      for (o=0; o<s[orden[i]].refe.size(); o++){
			if (o+1 < s[orden[i]].refe.size()) fprintf(archivo_d,"%d-",s[orden[i]].refe[o]);
			else fprintf(archivo_d,"%d ",s[orden[i]].refe[o]);
      }
      fprintf(archivo_d," ");
        for (u=0; u<s[s[orden[i]].t1].refe.size(); u++){
			if (u+1 < s[s[orden[i]].t1].refe.size()) fprintf(archivo_d,"%d-",s[s[orden[i]].t1].refe[u]);
			else fprintf(archivo_d,"%d ",s[s[orden[i]].t1].refe[u]);
      }
      fprintf(archivo_d," 1\n");
  }
}

 void M(){
   for (int nose=0; nose<ma+1;nose++){ 
    for(int cur=0; cur<ma+1; cur++){
      t=0;
      for(int ii=0; ii<e; ii++){
        for(int io=ii+1; io<e; io++){
          if (s[ii].n == cur and s[io].n == cur and s[ii].al and s[io].al){
              
              //0
              if (s[s[ii].t0].n != s[s[io].t0].n){
                if (t==0){
                  t=1; ma++;
                  s[ma+e].al = true;
                }
                if (s[s[ii].t0].n != cur)  idos.push(ii); 
                else  idos.push(io);
              }

              //1
              else if (s[s[ii].t1].n != s[s[io].t1].n){
                if (t==0){
                  t=1; ma++;
                  s[ma+e].al = true;
                }
                if (s[s[ii].t1].n != cur) idos.push(ii); 
                else  idos.push(io); 
              }
          }
        }
      }
      while (!idos.empty()){
        s[idos.front()].n = ma;
        idos.pop();
      }
    }
   }
 }

void Cadenas(){
  int indice;
  fscanf(file,"%s",stringg);
  linea = std::string(stringg);
  cuenta++;
  while (linea[0]!=70 and linea[1]!=67){     
    indice = orden[0];
    u=0;
    for (i=0; i<linea.size(); i++){
      if (linea[i]=='0') indice = s[indice].t0;
      else if (linea[i]=='1')indice = s[indice].t1;
      else if (linea[0]==78 and linea[1]==85 and linea[2]==76 and (linea[3]==76 or linea[3]==0)) {indice = orden[0];break;}
      else  u = 1;
    }
    if (s[indice].f == 1 and u==0) fprintf(archivo_d,"Aceptada\n");
    else if (u==1 or s[indice].f == 0)fprintf(archivo_d,"Rechazada\n");
    fscanf(file,"%s",stringg);
    linea = std::string(stringg);
    cuenta++;
  }
  fclose(file);
}

 void Reset(){
   for (i=0; i<200; i++){
    s[i].n = -1;
    s[i].f = 0;
    s[i].al = false;
    s[i].refe.clear();
   }
   orden.clear();
   fprintf(archivo_d,"\n");
 }
int main(){
  file = fopen ("tarea4.in","r");
  archivo_d = fopen("PARRA_GISELT.out", "w+");
  fscanf(file,"%s",stringg);
  linea = std::string(stringg);
  int casos = atoi(linea.c_str());
  cuenta=1;
  for (int p = 1; p < casos + 1; p++) {
      fprintf(archivo_d, "Caso %d:\n", p);
      if (p != 1) {
        file = fopen ("tarea4.in","r");
        for (int x = 0; x < cuenta; x++){
            i=0;
            while(i==0){ 
              fscanf(file,"%s",stringg);
              linea = std::string(stringg);
              if(fgetc(file) == '\n')i=1;
            }
        }
      }
      Datos();
      cuenta = cuenta + e*2 +2;
      M();
      for(o=0;o<e;o++){
        if (s[s[o].n+e].al){
          s[s[o].n+e].t0 = s[s[o].t0].n+e;
          s[s[o].n+e].t1 = s[s[o].t1].n+e;
          s[s[o].n+e].f = s[o].f;
          s[s[o].n+e].al = false;
          s[s[o].n+e].refe.push_back(o);
          orden.push_back(s[o].n+e);
        for (i=o+1;i<=e;i++){
            if (s[i].al and s[i].n == s[o].n) s[s[o].n+e].refe.push_back(i);
        }
        }
      }
      MostrarN();
      Cadenas();      
      Reset();      
  }
  fclose(archivo_d);
  return 0;
}

