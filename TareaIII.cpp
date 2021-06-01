#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

//																Giselt G. Parra V.
//																	26.609.640

char num[20];
int i;
FILE * file, *archivo_d;

void A();
void R();
void I(char n);
void II(char n);
void III(char n);
void V(char n);
void VI(char n);
void X(char n);
void X_(char n);
void XXX(char n);
void L(char n);
void C(char n);
void CC(char n);
void C_(char n);
void D(char n);
void M(char n);
void MM(char n);
void MMM(char n);

void I(char n){
  i++;
  //cout<<"(I) "<<n<<endl;
  if (n=='V' or n=='X') III(num[i]);
  else if (n=='I') II(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void II(char n){
  i++;
  //<<"(II) "<<n<<endl;
  if (n=='I') III(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void III(char n){
  i++;
  //<<"(III) "<<n<<endl;
  if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void V(char n){
  i++;
  //<<"(V) "<<n<<endl;
  if (n=='I') VI(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void VI(char n){
  i++;
  //<<"(VI) "<<n<<endl;
  if (n=='I') II(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void X(char n){
  i++;
  //<<"(X) "<<n<<endl;
  if (n=='C' or n=='X' or n=='L') X_(num[i]);
  else if (n=='I') I(num[i]);
  else if (n=='V') V(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void X_(char n){
  i++;
  //<<"(X_) "<<n<<endl;
  if (n=='V') V(num[i]);
  else if (n=='I') I(num[i]);
  else if (n=='X') XXX(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void XXX(char n){
  i++;
  //<<"(XXX) "<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='V') V(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void L(char n){
  i++;
  //<<"(L) "<<n<<endl;
  if (n=='X') X(num[i]);
  else if (n=='I') I(num[i]);
  else if (n=='V') V(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void C(char n){
  i++;
  //<<"(C) "<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n=='C') CC(num[i]);
  else if (n=='M' or n=='D') C_(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void C_(char n){
  i++;
  //<<"(C_) "<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void CC(char n){
  i++;
  //<<"(CC) "<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n=='C') C_(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void D(char n){
  i++;
  //<<"(D) "<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n=='C') C(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void M(char n){
  i++;
  //<<"(M)"<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n=='C') C(num[i]);
  else if (n=='D') D(num[i]);
  else if (n=='M') MM(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void MM(char n){
  i++;
  //<<"(MM)"<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n=='D') D(num[i]);
  else if (n=='C') C(num[i]);
  else if (n=='M') MMM(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void MMM(char n){
  i++;
  //<<"(MMM)"<<n<<endl;
  if (n=='I') I(num[i]);
  else if (n=='X') X(num[i]);
  else if (n=='V') V(num[i]);
  else if (n=='L') L(num[i]);
  else if (n=='C') C(num[i]);
  else if (n=='D') D(num[i]);
  else if (n==0 or n==3 or n==10 or n==32) A();
  else R();
}

void Datos() {
  i=1;
  fscanf (file, "%s", num); 
  if (!feof(file)){
    fprintf(archivo_d, "%s ",num);
    //cout<<"Numero: "<<num<<endl;
    if (num[0]=='I') I(num[1]);
    else if (num[0]=='V') V(num[1]);
    else if (num[0]=='X') X(num[1]);
    else if (num[0]=='L') L(num[1]);
    else if (num[0]=='C') C(num[1]);
    else if (num[0]=='D') D(num[1]);
    else if (num[0]=='M') M(num[1]);
    else if (num[0]==0 or num[0]==3 or num[0]==10 or num[0]==32) return;
    else R();
  }
}
void A(){
	fprintf(archivo_d, "aceptada\n");
	Datos();
}
void R(){
	fprintf(archivo_d, "rechazada\n");
	Datos();
}

int main(){
	file = fopen ("tarea3.in","r");
	archivo_d = fopen("PARRA_GISELT.out", "w+");
	Datos();
	fclose(file);
	fclose(archivo_d);
	return 0;
}
