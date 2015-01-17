#ifndef UNIT_H
#define UNIT_H


class Unit
{
    public:
        Unit();
        Unit(int x, int y, char icon);
        virtual ~Unit();
        int m_x, m_y;
        char m_icon;
    protected:
    private:
};

#endif // UNIT_H
