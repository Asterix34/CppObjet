#include "Gui.h"
#include <cstdarg>


// for bars
static const int PANEL_HEIGHT=7;
static const int BAR_WIDTH=20;

// for log
static const int MSG_X = BAR_WIDTH + 2;
static const int MSG_HEIGHT = PANEL_HEIGHT - 1;

Gui::Gui()
{
    con = new TCODConsole(engine.screenWidth,PANEL_HEIGHT);
}

Gui::~Gui()
{
    delete con;
    log.clearAndDelete();
}

/* for Message struct */
Gui::Message::Message(const char *text, const TCODColor &color) :
    text(strdup(text)), color(color) {
    // the strdup will duplicate the text variable and call malloc
    // btw this is C not C++
}

Gui::Message::~Message() {
    // with strdup we need a free here
    free(text);
}

void Gui::render() {
    // clear first
    con->setDefaultBackground(TCODColor::black);
    con->clear();

    // draw the health bar
    renderBar(1, 1, BAR_WIDTH, "HP", // x, y, width, title
              engine.player->destructible->m_hp, engine.player->destructible->m_maxHp, // cur, max
              TCODColor::lightRed, TCODColor::darkerRed ); // bar color, bg color

    int y=1;
    for (Message **iterator = log.begin(); iterator != log.end(); iterator++) {
        Message *message = *iterator;
        con->setDefaultForeground(message->color);
        con->print(MSG_X, y, message->text);
        y++;
    }

    /* here we would darken for a fading - imo would be better
     to use alpha if possible, this bloc stays here as example */
    /*int y=1;
    float colorCoef=0.4f;
    for (Message **it=log.begin(); it != log.end(); it++) {
        Message *message=*it;
        con->setDefaultForeground(message->col * colorCoef);
        con->print(MSG_X,y,message->text);
        y++;
        if ( colorCoef < 1.0f ) {
            colorCoef+=0.3f;
        }
    }*/

    // handle mouse inspection
    renderMouseLook();

    // draw GUI to game window
    TCODConsole::blit(con, 0, 0, engine.screenWidth, PANEL_HEIGHT, // from
            TCODConsole::root, 0, engine.screenHeight-PANEL_HEIGHT); // to
}

void Gui::renderBar(int x, int y, int w, const char*name,
            float value, float maxValue, const TCODColor &barColor,
            const TCODColor &backColor) {

    // fill the background
    con->setDefaultBackground(backColor);
    con->rect(x, y, w, 1, false, TCOD_BKGND_SET );

    // compute value
    int barWidth = (int)( value / maxValue * w);
    if (barWidth > 0) {
        // draw the bar
        con->setDefaultBackground(barColor);
        con->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
    }

    // write value on top of bar
    con->setDefaultForeground(TCODColor::white);
    con->printEx(x+w/2, y, TCOD_BKGND_NONE, TCOD_CENTER,
                 "%s : %g/%g", name, value, maxValue);

}

void Gui::message(const TCODColor &color, const char *text, ...) {
    // build text
    va_list ap;
    char buffer[128];
    va_start(ap, text);
    vsprintf(buffer, text, ap);
    va_end(ap);
    /* that whole bloc of magic works with the variative method, this is C,
    fortunately we don't need to understand because vsprintf does the job */

    char *lineBegin = buffer;
    char *lineEnd;

    // if list is too long, remove the last msg
    do {
        // make room for the new message
        if (log.size() == MSG_HEIGHT ) {
            Message *toRemove = log.get(0);
            log.remove(toRemove);
            delete toRemove;
        }

        // now detect end of line
        lineEnd = strchr( lineBegin, '\n');
        if ( lineEnd ) // if one found
            *lineEnd = '\0'; // replace with \0 which is end of string in C

        // now that string is splitted, we can add the first part in the log
        Message *msg = new Message(lineBegin, color);
        log.push(msg);

        // go to the next line
        lineBegin = lineEnd + 1;
    } while ( lineEnd );

}


void Gui::renderMouseLook() {
    if ( !engine.gmap->isInFov( engine.mouse.cx, engine.mouse.cy ))
        return;

    /* once again, here is some C, we could use string instead */
    char buffer[128]="";
    bool first = true;

    for (Unit **iterator=engine.units.begin(); iterator != engine.units.end(); iterator++) {
        Unit *unit = *iterator;
        // find actors under the mouse cursor
        if (unit->m_x == engine.mouse.cx && unit->m_y == engine.mouse.cy) {
            if (first) {
                first = false;
            } else {
                strcat(buffer, ", ");
            }
            strcat(buffer, unit->m_name);
        }
    }
        // display the list of actors under the mouse cursor
    con->setDefaultForeground(TCODColor::lightGrey);
    con->print(1,0,buffer);
}
