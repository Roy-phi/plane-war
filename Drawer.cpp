//Copyright 2021 zbt
//license: MIT
//Author zbt
//This is plane war core class: Drawer, Draw the prop, control menu, and bomb dynamic process;

#include "Drawer.h"

namespace drawer {
    //basic draw option tools
    void Drawer::Set_window_size(const int& screen_H, const int& screen_W)//
    {
        system("title PLANE WAR");//
        char cmd[30];
        sprintf_s(cmd, "mode con cols=%d lines=%d", screen_W * 2, screen_H);//
        system(cmd);        //system(mode con cols=88 lines=88)

        //hide cursor
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO CursorInfo;
        GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
        CursorInfo.bVisible = false; //隐藏控制台光标
        SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
    }

    void Drawer::Set_cursor_position(const COORD &posi)//
    {
        COORD position;
        position.X = posi.X * 2;
        position.Y = posi.Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    }

    void Drawer::Set_cursor_position(const int& x, const int& y)
    {
        COORD position;
        position.X = x * 2;
        position.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    }

    void Drawer::Set_color(const int &colorID)//
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
    }

    void Drawer::Set_back_color()//
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_BLUE |
            BACKGROUND_BLUE |
            BACKGROUND_GREEN |
            BACKGROUND_RED);
    }

    //draw 
    void Drawer::Draw_start_menu(Controller& game_controller)
    {
        Draw_clear();
        //draw menu
        Set_color(11);
        Set_cursor_position(32, 19);
        cout << "MENU";
        Sleep(100);
        Set_cursor_position(34, 21);
        Set_back_color();
        cout << "Help";
        Sleep(100);
        Set_cursor_position(34, 23);
        Set_color(11);
        cout << "Start";
        Sleep(100);
        Set_cursor_position(34, 25);
        cout << "Excit";
        Set_cursor_position(0, 31);

        //select menu
        int key;
        int tmp_select = 0;
        bool flag = false;
        while ((key = _getch()))
        {
            switch (key)
            {
            case 72://up
                if (tmp_select > 0)
                {
                    switch (tmp_select)
                    {
                    case 1:
                        Set_cursor_position(34, 21);
                        Set_back_color();
                        cout << "Help";
                        Set_cursor_position(34, 23);
                        Set_color(11);
                        cout << "Start";

                        --tmp_select;
                        break;
                    case 2:
                        Set_cursor_position(34, 23);
                        Set_back_color();
                        cout << "Start";
                        Set_cursor_position(34, 25);
                        Set_color(11);
                        cout << "Excit";

                        --tmp_select;
                        break;
                    }
                }
                break;

            case 80://down
                if (tmp_select < 2)
                {
                    switch (tmp_select)
                    {
                    case 0:
                        Set_cursor_position(34, 23);
                        Set_back_color();
                        cout << "Start";
                        Set_cursor_position(34, 21);
                        Set_color(11);
                        cout << "Help";

                        ++tmp_select;
                        break;
                    case 1:
                        Set_cursor_position(34, 25);
                        Set_back_color();
                        cout << "Excit";
                        Set_cursor_position(34, 23);
                        Set_color(11);
                        cout << "Start";

                        ++tmp_select;
                        break;
                    }
                }
                break;

            case 13://enter
                flag = true;
                break;

            default:
                break;
            }

            if (flag)
            {
                if (tmp_select == 0)
                {
                    Draw_help();  //draw help, and press enter to return;
                    flag = false;
                }
                else if(tmp_select==2){
                    game_controller.Excit();
                    break;
                }
                else {
                    break;
                }
            }
            Set_cursor_position(0, 31);
        }

    }

    void Drawer::Draw_select(Controller& game_controller)//选择界面
    {
        Draw_clear();
        //initial select interface
        Set_color(3);
        Set_cursor_position(13, 26);
        cout << "                          ";
        Set_cursor_position(13, 27);
        cout << "                          ";
        Set_cursor_position(6, 21);
        cout << "Select game mode";
        Set_cursor_position(6, 22);
        cout << "(down/up select, enter confirm)";

        Set_cursor_position(27, 22);
        Set_back_color();  //default select first selection
        cout << "easy";
        Set_cursor_position(27, 24);
        Set_color(3);
        cout << "medium";
        Set_cursor_position(27, 26);
        cout << "hard";
        Set_cursor_position(27, 28);
        cout << "extremely hard";
        Set_cursor_position(0, 31);

        //down/up select, enter confirm
        int key;   //input key value
        int select=0;//record selected option, default select first selection

        bool flag = false;//记录是否键入Enter键标记，初始置为否

        while ((key = _getch()))
        {
            switch (key)//检测输入键
            {
            case 72://UP上方向键
                if (select > 0)//当此时选中项为第一项时，UP上方向键无效
                {
                    switch (select)
                    {
                    case 1:
                        Set_cursor_position(27, 22);//给待选中项设置背景色
                        Set_back_color();
                        cout << "easy";

                        Set_cursor_position(27, 24);//将已选中项取消我背景色
                        Set_color(3);
                        cout << "medium";

                        --select;
                        break;
                    case 2:
                        Set_cursor_position(27, 24);
                        Set_back_color();
                        cout << "medium";

                        Set_cursor_position(27, 26);
                        Set_color(3);
                        cout << "hard";

                        --select;
                        break;
                    case 3:
                        Set_cursor_position(27, 26);
                        Set_back_color();
                        cout << "hard";

                        Set_cursor_position(27, 28);
                        Set_color(3);
                        cout << "extremely hard";

                        --select;
                        break;
                    }
                }
                break;

            case 80://DOWN下方向键
                if (select < 3)
                {
                    switch (select)
                    {
                    case 0:
                        Set_cursor_position(27, 24);
                        Set_back_color();
                        cout << "medium";
                        Set_cursor_position(27, 22);
                        Set_color(3);
                        cout << "easy";

                        ++select;
                        break;
                    case 1:
                        Set_cursor_position(27, 26);
                        Set_back_color();
                        cout << "hard";
                        Set_cursor_position(27, 24);
                        Set_color(3);
                        cout << "medium";

                        ++select;
                        break;
                    case 2:
                        Set_cursor_position(27, 28);
                        Set_back_color();
                        cout << "extremely hard";
                        Set_cursor_position(27, 26);
                        Set_color(3);
                        cout << "hard";

                        ++select;
                        break;
                    }
                }
                break;

            case 13://Enter回车键
                flag = true;
                break;
            default://无效按键
                break;
            }

            if (flag)
            {
                game_controller.Set_hard_level(static_cast<hard_level>(select));
                break; //输入Enter回车键确认，退出检查输入循环
            }

            Set_cursor_position(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验
        }
        //if start game, clear menu
        {
            Set_cursor_position(6, 21);
            cout << "                                   ";
            Set_cursor_position(6, 22);
            cout << "                                   ";
            Set_cursor_position(27, 22);
            cout << "                                   ";
            Set_cursor_position(27, 24);
            cout << "                                   ";
            Set_cursor_position(27, 26);
            cout << "                                   ";
            Set_cursor_position(27, 28);
            cout << "                                   ";
        }
    }

    void Drawer::Draw_help()
    {
        Set_color(3);
        Set_cursor_position(40, 26);
        cout << " I will teach you the rules, and please press enter";
        int key;
        while (key = _getch())
        {
            if (key == 13)
            {
                break;
            }
        }
    }

    void Drawer::Draw_prop(const prop::Prop& p)
    {
        Set_color(13);
        const COORD posi = p.Get_position();
        std::vector<int> shape= p.Get_shape();
        std::vector<int>::size_type size = shape.size();
        for (std::vector<int>::size_type row = 0; row < size; ++row) {
            Draw_line(posi.X + (size / 2 - shape[row]), posi.Y + row, 2*shape[row]);
            /*for(unsigned int x= posi.X + (size / 2 - shape[row]);x<posi.X+ (size / 2 + shape[row]);++x)
            {
                Draw_point(x,posi.Y+row);
             }*/
        }
    }

    void Drawer::Draw_point(const unsigned int& x,const unsigned int &y) {
        Set_cursor_position(x,y);
        //cout << "■";
        printf_s("■");
    }

    void Drawer::Draw_line(const unsigned int& x, const unsigned int& y,const  int len) {
        Set_cursor_position(x, y);
        //cout << "■";
        for (unsigned int i = 0; i < len; ++i)
        {
            printf_s("■");
        }
    }

    void Drawer::Draw_bomb(const prop::Prop& p) {
        const COORD posi = p.Get_position();
        std::vector<int>::size_type size = p.Get_size();

        Set_color(15);
        for (std::vector<int>::size_type row = 0; row < size; ++row) {
            for (unsigned int x = posi.X; x < posi.X + size; ++x)
            {
                Draw_point(x, posi.Y + row);
            }
        }
        Set_color(13);
    }

    void Drawer::Draw_static( const Controller& game_controller) {
        Set_cursor_position(0, 0);
        cout << " BEAT PLANE NUM: " << game_controller.Get_beat_num();
        Set_cursor_position(0, 1);
        cout << " CATCH TOOL NUM: " << game_controller.Get_catch_tool_num();
        Set_cursor_position(0, 2);
        cout << " time: " << game_controller.Get_time();
    }

    void Drawer::Draw_info(const int i)
    {
        Set_cursor_position(0, 3);
        cout << " info : " << i;
    }

    void Drawer::Draw_clear()const {
        system("cls");
    }
}