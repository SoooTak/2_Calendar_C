#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>       // 현재 날짜 확인
#include <windows.h>    // 콘솔창 크기 설정, 화면 클리어
#include <conio.h>      // _getch() 함수 사용 (엔터키 입력 없이 문자 입력)
#include "color.h"
#include "calendar.h"
#include "assistant.h"
#include "menu.h"
#include "plan.h"

// (보조) 좌표 이동 함수 (완)
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// (보조) 텍스트 색 변경 함수 (완)
void textcolor(int colorNum) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

// (보조) 로그인 화면 사각형 그리는 함수
void printBOX(void) {
    int i, y = 10;
    gotoxy(34, y);
    printf("┌");
    for (i = 0; i < 30; i++)
        printf("─");
    printf("┐");
    for (i = 1; i <= 7; i++)
    {
        gotoxy(34, ++y);
        printf("│%30s│", " ");
    }
    gotoxy(34, ++y);
    printf("└");
    for (i = 0; i < 30; i++)
        printf("─");
    printf("┘");
}

// (보조) 콘솔창 커서 안 보이게 하는 함수 0 - 숨김 1 - 보임
void cursor(int n)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = n;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}