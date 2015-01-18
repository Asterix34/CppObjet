#ifndef GUI_H
#define GUI_H

#include "main.hpp"
#include <stdio.h>

class Gui
{
    public:
        Gui();
        virtual ~Gui();

        void render();
        // method to add message to console
        // this is a variadic function, the ... means there might be
        // a number of arguments behind, like with printf
        void message(const TCODColor &col, const char *text, ...);
    protected:
        TCODConsole *con;
        // message in console - we'll need to keep track
        struct Message {
            char *text;
            TCODColor color;
            Message(const char *text, const TCODColor &color);
            ~Message();
        };
        // pointer list of message
        TCODList<Message *> log;

        // method to render any kind of bar
        void renderBar(int x, int y, int width, const char *name,
                float value, float maxValue, const TCODColor &barColor,
                const TCODColor &backColor);
        //
        void renderMouseLook();
    private:
};

#endif // GUI_H
