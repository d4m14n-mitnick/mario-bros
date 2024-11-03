#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/terminal.hpp>
#include <iostream>
#include <thread>

using namespace std;
using namespace ftxui;

int posicionX(int posicion, int velocidad, int tiempo){
    return posicion + velocidad * tiempo;
}

int main(int argc, char const *argv[])
{
    std::string reset_position;
    int frame = 0;

    int vix = 50;
    int viy = 78;

    while (true)
    {
        Screen pantalla = Screen::Create(Dimension::Full(), Dimension::Full());
        
        auto can = Canvas(400,400);

        int viy = 78-frame;

        // Cohete

        // Cuerpo
        for (int i = viy-12; i <= viy-3; ++i)
        {
            can.DrawPoint(vix, i, true, Color::White); // Linea del centro
            can.DrawPoint(vix-1, i, true, Color::White); // Linea izquierda
            can.DrawPoint(vix+1, i, true, Color::White); // Linea derecha
        }

        // Alas laterales
        for (int i = -4; i <= 4; ++i)
        {
            can.DrawPoint(vix + i, viy-8, true, Color::White); // Alas superiores
            can.DrawPoint(vix + i, viy-6, true, Color::White); // Alas inferiores
        }

        // Base
        for (int i = -2; i <= 2; ++i)
        {
            can.DrawPoint(vix + i, viy-1, true, Color::White); // Parte superior
            can.DrawPoint(vix + i, viy, true, Color::White); // Parte inferior
        }

        // Llamas
        for (int i = -1; i <= 1; ++i)
        {
            can.DrawPoint(vix + i, viy+4, true, Color::Red1);
            can.DrawPoint(vix + i, viy+5, true, Color::Red1);
            can.DrawPoint(vix + i, viy+6, true, Color::Yellow1);
        }
        can.DrawPoint(vix, viy+7, true, Color::Yellow1);

        // Estrellas
        for (int x = -13; x < 500; x=x+14)
        {
            for (int y = 0; y < 500; y=y+14)
            {
                can.DrawPoint(x, y, true, Color::GrayDark);
            }
        }

        // Tierra
        can.DrawBlockCircleFilled(50, 100, 20, Color::DarkBlue);
        can.DrawBlockEllipseFilled(47,90,14,8, Color::DarkGreen);
        can.DrawBlockEllipseFilled(56,108,8,8, Color::DarkGreen);

        // Luna
        can.DrawBlockCircleFilled(95,55,6, Color::GrayLight);

        
        Element lienzo = bgcolor(Color::DarkBlue, canvas(&can));
        Render(pantalla, lienzo);
        
        std::cout << reset_position;
        pantalla.Print();
        reset_position = pantalla.ResetPosition(true);
        
        this_thread::sleep_for(0.5s);
        frame++;
    }
    
}