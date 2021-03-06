#include <iostream>
#include <cctype> //isdigit
#include <vector>
#include <string>
#include <algorithm>
#include "Header.h"


int IdFunc(std::vector<std::string> pals, int pal, Funcs& fun);

int IdFunc(std::vector<std::string> pals, int pal, Funcs& fun){

  bool intJaExiste = false;
  int posInt;

  if(pals[pal] == "Melancia" || pals[pal] == "melancia"){
    //verifica se todos caracteres sao inteiros
    int d = 0;
    for(int i =0; i<pals[pal+2].size();i++){

      if(isdigit(pals[pal+2][i]))
        d++;
      else if(pals[pal+2][i] == '.' || pals[pal+2][i] == '-')
        d++;
    }

    for(int i = 0; i<fun.intN_get().size(); i ++){
      if (pals[pal+1] == fun.intN_get()[i]){
        posInt = i;
        intJaExiste = true;
      }
    }


    if (intJaExiste){
      fun.intN_set(pals[pal+1]);
      fun.intV_change(stof(pals[pal+2]),posInt);
      return 2;
    }
    else{
      if(d == pals[pal+2].size()){
        fun.intV_set(stof(pals[pal+2]));
        fun.intN_set(pals[pal+1]);
      }
      else
        std::cout<<"Valor da string nao é numerico\nPalavra: "<<pals[pal+2]<<"\n";
     return 2;
    }

  }

  else if(pals[pal] == "Ed:" || pals[pal] == "EdP:" || pals[pal] == "edp:" || pals[pal] == "ed:"){

    int tipo = -1; //0 - stringJaExistente; 1 - float ja existente; 2 - float nova; 3 - string nova

    //checa se é string
    for(int i =0; i<fun.strN_get().size(); i++){

      if(pals[pal+1] == fun.strN_get()[i]){
        fun.print(fun.strV_get()[i]);
        tipo = 0;
      }

    }

    //checa se é uma int
    if (tipo == -1){
    for (int i = 0; i<fun.intN_get().size();i++){

      if(pals[pal+1] == fun.intN_get()[i]){
        fun.print(fun.intV_get()[i]);
        tipo = 1;
      }

    }
    }

  //verifica se é um digito
    if (tipo == -1){
      int d =0;
      for (int i =0; i<pals[pal+1].size(); i++){   
        if(isdigit(pals[pal+1][i]) || pals[pal+1][i] == '.' || pals[pal+1][i] == '-')
          d++;
      }

      if(d == pals[pal+1].size()){
        fun.print(pals[pal+1]);
        tipo = 2;
      }
    }


    //Verifica se é uma string
    if(tipo == -1){
      if (pals[pal+1][0] == '"' && pals[pal+1][pals[pal+1].size()-1] == '"'){
        pals[pal+1].erase(pals[pal+1].begin());
        pals[pal+1].erase(pals[pal+1].length()-1);
        for(int i = 0; i<pals[pal+1].length(); i++){
          if(pals[pal+1][i] == '\\' && pals[pal+1][i+1] == '_'){
            pals[pal+1].erase(pals[pal+1].begin()+i);
            pals[pal+1][i] = ' ';
          }
        }
        fun.print(pals[pal+1]);

      }

    }
    

    if(pals[pal][2] == 'P' || pals[pal][2] == 'p'){
        fun.printL();
    }


    return 1;
  }

  else if(pals[pal] == "Lenha" || pals[pal] == "lenha"){  

    int pValeTudo = 0, i = 0, posStr;
    bool strJaExiste = false;

    while(pValeTudo == 0 ){
      if(pals[pal+i] == "ValeTudo" || pals[pal+i] == "vale_tudo")
        pValeTudo = i;
      else if (i>=1000){
        std::cout<<"Nao foi possivel encontrar ValeTudo ou vale_tudo\n";
        return 0;
        pValeTudo = -2;
      }
      i++;
    }

    if ((pals[pal+2] == "ValeNada" || pals[pal+2] == "vale_nada" )&& pValeTudo >0){

      for(int i = 0;i<fun.strN_get().size(); i++){
        if(pals[pal+1] == fun.strN_get()[i]){
          strJaExiste = true;
          posStr = i;
        }

      }

      //fun.strV_set(pals[pal+3]);
      std::string Inp;

      for(int j = 1;j<pValeTudo-2;j++){
        Inp.append(pals[pal+2+j]);
        Inp += ' ';
      }
      Inp.erase(Inp.length()-1);

      if(strJaExiste){
        fun.strV_change(Inp, posStr);
      }

      else{
        fun.strV_set(Inp);
        fun.strN_set(pals[pal+1]);
      }
      return pValeTudo;

    }
    else if(pals[pal+2] != "vale_nada" || pals[pal+2] != "ValeNada")
      std::cout<<"Erro de sintaxe, esperado vale nada e vale tudo\n";

  }

   /////////////////////
  //INICIO MATEMATICA//
 /////////////////////

  else if(pals[pal] == "Chico+" || pals[pal] == "Chico-" || pals[pal] == "Chico*" || pals[pal] == "Chico/" || pals[pal] == "Chico+*" || pals[pal] == "Chico++"|| pals[pal] == "Chico+-" || pals[pal] == "Chico+/"
       || pals[pal] == "chico+" || pals[pal] == "chico-" || pals[pal] == "chico*" || pals[pal] == "chico/" || pals[pal] == "chico+*" || pals[pal] == "chico++"|| pals[pal] == "chico+-" || pals[pal] == "chico+/"){
    float p1,p2;
    //float resultado;
    bool achado = false, v1 = false, v2 = false; //E -> verifica se o numero que nao existe na lista de ints é um numero
    int intPos;

    for(int i = 0; i<fun.intN_get().size(); i++){
      if (pals[pal+1] == fun.intN_get()[i]){
        p1 = fun.intV_get()[i];
        i = fun.intN_get().size();
        achado = true;
        v1 = true;

      }
    }

    if(!achado){

      int d = 0;
      for (int i = 0; i < pals[pal+1].length(); i++){
        if(isdigit(pals[pal+1][i])||pals[pal+1][i] == '.'|| pals[pal+1][i] == '-'){
          d++;
        }
      }
      if(d == pals[pal+1].length()){
        v1 = true;
        p1 = stof(pals[pal+1]);

      }
    }

    achado = false;

    for(int i = 0; i<fun.intN_get().size(); i++){
      if (pals[pal+2] == fun.intN_get()[i]){
        p2 = fun.intV_get()[i];
        i = fun.intN_get().size();
        achado = true;
        
        v2 = true;
      }
    }

    if(!achado){

      int d = 0;
      for (int i = 0; i < pals[pal+2].length(); i++){
        if(isdigit(pals[pal+2][i])||pals[pal+2][i] == '.'|| pals[pal+2][i] == '-'){
          d++;
        }
      }
      if(d == pals[pal+2].length()){
        v2 = true;
        p2 = stof(pals[pal+2]);
      }
    }

    if (v1 == false && v2 == false){
      std::cout<<"\nDOIS VALORES INVALIDOS (CHICO), argumentos: <"<<pals[pal+1]<<" "<<pals[pal+2]<<"> PALAVRA: "<<pal<<"\n"; return 3;
    }
    else if (v1 == false && v2 == true ){
      std::cout<<"\nVALOR INVALIDO (CHICO), argumento <"<<pals[pal+1]<<"> PALAVRA: "<<pal<<"\n"; return 3;
    }
    else if(v2 == false && v1 == true ){
      std::cout<<"\nVALOR INVALIDO (CHICO), argumento: <"<<pals[pal+2]<<"> PALAVRA: "<<pal<<"\n"; return 3;
    }

    achado = false;

    for(int i =0; i < fun.intN_get().size(); i++){
      if(pals[pal+3] == fun.intN_get()[i]){
        achado = true;
        intPos = i;
      }
    }

    if(achado && (pals[pal] == "Chico+" || pals[pal] == "Chico-" || pals[pal] == "Chico*" || pals[pal] == "Chico/" ||
                  pals[pal] == "chico+" || pals[pal] == "chico-" || pals[pal] == "chico*" || pals[pal] == "chico/")){
      if(pals[pal][5] == '+')
        fun.intV_change(p1+p2, intPos);
      else if(pals[pal][5] == '-')
        fun.intV_change(p1-p2,intPos);
      else if(pals[pal][5] == '*')
        fun.intV_change(p1*p2,intPos);
      else if(pals[pal][5] == '/')
        fun.intV_change(p1/p2,intPos);

    }

    //ESPECIFICO PRO FATORIAL
    else if(achado && (pals[pal] == "Chico++" || pals[pal] == "chico++") || (pals[pal] == "Chico+-" || pals[pal] == "chico+-") ||
                       (pals[pal] == "chico+*"|| pals[pal] == "chico++") || (pals[pal] == "chico+/" || pals[pal] == "chico+/")){

      int temp = fun.intV_get()[intPos];

      if(pals[pal][6] == '*'){
        fun.intV_change(p1*p2*temp, intPos);
      }

      if(pals[pal][6] == '-'){
        fun.intV_change(p1-p2-temp, intPos);
      }

      if(pals[pal][6] == '+'){
        fun.intV_change(p1+p2+temp, intPos);
      }

      if(pals[pal][6] == '/'){
        fun.intV_change(p1/p2/temp, intPos);
      }

      // switch(pals[pal][6]){
      //   case('*'):
      //     fun.intV_change(p1*p2*temp, intPos);
      //     std::cout<<"jorge";
      //     break;
      //   case('+'):
      //     fun.intV_change(p1+p2+temp, intPos);
      //     std::cout<<"jorge";
      //     break;
      //   case('-'):
      //     fun.intV_change(p1-p2-temp, intPos);
      //     break;
      //   case('/'):
      //     fun.intV_change(p1/p2/temp, intPos);
      //     break;
      //   default:
      //     break;

      // }

    }

    else{
      fun.intN_set(pals[pal+3]);
      if(pals[pal][5] == '+'){
        fun.intV_set(p1+p2);
      }
      else if(pals[pal][5] == '-'){
        fun.intV_set(p1-p2);
      }
      else if(pals[pal][5] == '*'){
        fun.intV_set(p1*p2);
      }
      else if(pals[pal][5] == '/'){
        fun.intV_set(p1/p2);
      }
      }

    return 3;

  }

  //INPUT
  //-> WhatIsThe: Nome_da_int_string Valor
  else if(pals[pal] == "WhatIsThe:" || pals[pal] == "what_is_the:"){ 
    //verfica se existe e é int ou string
    bool existe = false;
    int pos;
    int tipo; //1-string 2-int
    std::string inp;
    getline(std::cin,inp);
    // std::cin.ignore();

    if(fun.strN_get().size() > 0){
      for(int i =0; i < fun.strN_get().size();i++){
        if(pals[pal+1] == fun.strN_get()[i]){
          pos = i;
          existe = true;
          tipo = 1;
          i = fun.strN_get().size();
        }
      }
    }
    
    if(fun.intN_get().size() > 0){
      for(int i =0; i < fun.intN_get().size();i++){
        if(pals[pal+1] == fun.intN_get()[i]){
          pos = i;
          existe = true;
          tipo = 2;
          i = fun.intN_get().size();
        }
      }
    }

    if(!existe){
      int d = 0;
      for(int i = 0; i<inp.length(); i++){
        if(isdigit(inp[i]) || inp[i] == '.' || inp[i] == '-')
          d++;
      }
      if(d == inp.length())
        tipo = 2;
      else
        tipo = 1;
    }

    if(existe){
      
      switch(tipo){
        case 1:
          fun.strV_change(inp, pos);
          return 1;
          break;
        case 2:
          fun.intV_change(stof(inp), pos);
          return 1;
          break;
        default:
          return 1;
          break;        
      }
    }

    else if(!existe){
      switch(tipo){
        case 1:
          fun.strV_set(inp);
          fun.strN_set(pals[pal+1]);
          return 1;
          break;
        case 2:
          fun.intV_set(stof(inp));
          fun.intN_set(pals[pal+1]);
          return 1;
          break;
        default:
          return 1;
          break;        
      }
    }
    return 1;

  }

  //DeTorar -> str.lengh()
  else if (pals[pal] == "DeTorar" || pals[pal] == "de_torar"){
    int strPos;
    int fPos;
    int tam;
    std::string str;
    bool FExiste = false, SExiste = false;

    for(int i = 0; i<fun.strN_get().size(); i++){
      if(pals[pal+1] == fun.strN_get()[i]){
        strPos = i;
        SExiste = true;
        i = fun.strN_get().size();
      }
    }

    for(int i = 0; i<fun.intN_get().size(); i++){
      if(pals[pal+2] == fun.intN_get()[i]){
        FExiste = true;
        fPos = i;
        i = fun.intN_get().size();
      }
    }

    if(SExiste){
      str = fun.strV_get()[strPos];
      tam = fun.strV_get()[strPos].length();
    }
    else{
      str = pals[pal+1];
    }
    if(str[0] == '"' && str[str.length()-1] == '"'){
      str.erase(str.begin());
      str.erase(str.length()-1);
    }
    
    if(FExiste){
      if(SExiste){
        fun.intV_change(tam, fPos);
       }
       else{
        fun.intV_change(str.length(), fPos);
       }
    }
    else{
      if(SExiste)
        fun.intV_set(tam);
      else
        fun.intV_set(str.length());
      fun.intN_set(pals[pal+2]);
    }
    
    
  }

  //CocoSeco -> reverte a string
  else if(pals[pal] == "coco_seco" || pals[pal] == "CocoSeco"){
    std::string str;
    bool jaExst = false;
    int sPos;

    if(pals[pal+1][0] == '"'){
      str = pals[pal+1];
      str.erase(str.begin());
      str.erase(str.length()-1);

    }
       

    else{
      for(int i = 0; i<fun.strN_get().size(); i++){
        if(pals[pal+1] == fun.strN_get()[i]){
          str = fun.strV_get()[i];
        }
        if(pals[pal+2] == fun.strN_get()[i]){
          jaExst = true;
          sPos = i;
        }
      }
    }

    std::reverse(str.begin(), str.end());

    if(jaExst){
      fun.strV_change(str,sPos);
    }
    else{
      fun.strV_set(str);
      fun.strN_set(pals[pal+2]);
    }
    
  }

  


  return 0;
}

  ///////////////
 //Gets e Sets//
///////////////

std::vector<float> Funcs::intV_get(){
  return intVars;
}

void Funcs::intV_set(float inp){
 intVars.push_back(inp);
}

void Funcs::intV_change(float inp, int pos){
 intVars[pos] = inp;
}

std::vector<std::string> Funcs::intN_get(){
  return intNames;
}

void Funcs::intN_set(std::string inp){
 intNames.push_back(inp);
}


std::vector<std::string> Funcs::strV_get(){ return strVars; }
std::vector<std::string> Funcs::strN_get(){ return strNames; }

void Funcs::strN_set(std::string inp){
  strNames.push_back(inp);
}

void Funcs::strV_set(std::string inp){
  strVars.push_back(inp);
}

void Funcs::strV_change(std::string inp, int pos){
  strVars[pos] = inp;
}



void Funcs::printL(){std::cout<<'\n';}
void Funcs::print(std::string inp){ std::cout<<inp;}
void Funcs::print(float inp){std::cout<<inp;}
