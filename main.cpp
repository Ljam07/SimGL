#include <iostream>
#include "Playground/Playground.h"

int main(int, char**){
    Application* app = CreateApplication();
    app->Run();
    delete app;
    std::cout << "\nFinished Running\n";
}
