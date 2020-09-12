#include "IF.h"
#include "Header.h"
#include <iostream>
#include <string>
#include <vector>
template <typename T>
bool verificaCond(T p1, T p2, int op);

int IF(std::vector<std::string> pals, int pal, Funcs& fun);


int IF(std::vector<std::string> pals, int pal, Funcs& fun){
  int pFim = 0;
  bool acontece = false;
  int i = 0;

  while (pFim == 0){
    if(pals[pal+i] == "nao_para_perder" || pals[pal+i] == "NaoParaPerder"){
      pFim = i;
    }
    i++;
  }

  float p, p_;
  int p1 = 0, p2 = 0;

  for(int i = 0; i < fun.intN_get().size(); i++){
    if (pals[pal+1] == fun.intN_get()[i]){
      p1 = i;
    }
    else if (pals[pal+3] == fun.intN_get()[i])
      p2 = i;
  }

  p = fun.intV_get()[p1];
  p_ = fun.intV_get()[p2];

  if(pals[pal+2] == ">"){
    if (p > p_)
      acontece = true;
  }
  else if (pals[pal+2] == "<"){
    if(p < p_)
      acontece = true;

  }
  else if (pals[pal+2] == "=="){
    if(p == p_)
      acontece = true;
    
  }
  else if (pals[pal+2] == "!="){
    if(p != p_)
      acontece = true;
    
  }

  i = 5;
  if(acontece){
    // std::cout<<"Acontece :)"<<pal+4<<'\n'<<p<<" - "<<p_<<'\n';
    while(pals[pal+i] != "nao_para_perder" && pals[pal+i] != "NaoParaPerder"){
      IdFunc(pals,pal+i,fun);
      i++;
    }
    acontece = false;
    return pFim;
  }
  else{
    return pFim;
  }
  

}



//Provavelmente sera usado mais para a frente, mas nao agora
template <typename T>
bool verificaCond(T p1, T p2, int op){
  //op
  // 0 -> == ; 1 -> >  ; 2 -> <
  // 3 -> >= ; 4 -> <= ; 5 !=
  switch(op){
    case 0:
      if (p1 == p2)
        return true;
      return false;
      break;

    case 1:
      if(p1 > p2)
        return true;
      return false;
      break;

    case 2:
      if(p1 < p2)
        return true;
      return false;
      break;
    
    case 3: 
      if(p1 >= p2)
        return true;
      return false;
      break;

    case 4:
      if(p1 <= p2)
        return true;
      return false;
      break;

    case 5:
      if(p1 != p2)
        return true;
      return false;
      break;

    default:
      break;
  }

  return false;


}





   /////////
  //WHILE//
 /////////

 
int WHILE(std::vector<std::string> pals, int pal, Funcs& fun){
  // VamosBrilhar x == x    ComoUmDiamante Ed: x NessaGeracaoMarcante
  // pal         pal+1+2+3  pal+4                  pValeTudo
  int i = 5; // int i = 5 pq vamos verificar qual a proxima palava que pode ser o NessaGeracaoMarcante, n pode ser nenhuma antes de pals[pal+5]
  
  int pValeTudo = 0, op =0;

  if(pals[pal+2] == "=="){
      op = 0;
    }
    else if(pals[pal+2] == ">"){
      op = 1;
    }
    else if(pals[pal+2] == "<"){
      op = 2;
    }
    else if(pals[pal+2] == ">="){
      op = 3;
    }
    else if(pals[pal+2] == "<="){
      op = 4;
    }
    else if(pals[pal+2] == "!="){
      op = 5;
    }

  bool acontece = verificaCond(pals[pal+1], pals[pal+2], op);

  while(pValeTudo == 0){
    if(pals[pal+i] == "EmUmaGeracaoMarcante" || pals[pal+i] == "em_uma_geracao_marcante"){
      pValeTudo = i;
    }
    i++;
  }
  // std::cout<<"Acontece: "<<IF(pals,pal, fun, 2)<<"\n";
  while(acontece){
    i = 5;
    while(i<pValeTudo){
      IdFunc(pals,pal+i,fun);
      i++;

    }
    acontece = verificaCond(pals[pal+1], pals[pal+2], op);
    
  };

  return pValeTudo;
}

int ELSE(std::vector<std::string> pals, int pal, Funcs& fun, int op){
  int i = 5;
  bool acontece = verificaCond(pals[pal+1], pals[pal+2], op);
  int pValeTudo = 0;
  while(pValeTudo == 0){
    if(pals[pal+i] == "DeDificuldades" || pals[pal+i] == "de_dificuldades") 
      pValeTudo = i;
    i++;
  }

  if(!acontece){
    i = 5;
    while(pals[pal+i] != "DeDificuldades" || pals[pal+i] != "de_dificuldades"){
      IdFunc(pals, pal+i, fun);
      i++;
    }
  }

  return pValeTudo;

}