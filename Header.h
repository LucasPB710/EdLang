#pragma once
#include <vector>
#include <iostream>

int IdFunc(std::vector<std::string> pals, int pal);

class Funcs{
  public:
    //void if_();
    //
    void print(std::string inp);
    void print(int inp);

    //gets
    std::vector<int> intV_get();
    std::vector<std::string> intN_get();
    std::vector<std::string> strV_get();
    std::vector<std::string> strN_get();
    int intS_get();


    //sets
    void intV_set(int inp);
    void intN_set(std::string inp);
    void intS_set(int inp);
    void strN_set(std::string inp);
    void strV_set(std::string inp);



  private:
    std::vector<int> intVars;
    std::vector<std::string> intNames;
    std::vector<std::string> strNames;
    std::vector<std::string> strVars;
    int intSize;
};
