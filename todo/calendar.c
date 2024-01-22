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

// 1. 달력 출력 함수 (완)
void printCalendar(int month, int year) {
    // 화면 클리어
    system("cls");

    // n년 n월 출력
    gotoxy(45, 1);
    printf("%d년 %d월", year, month);

    // 달력 요일 출력
    gotoxy(20, 3);
    printf("============================================================");
    gotoxy(25, 4);
    printf("일      월      화      수      목      금      토");
    gotoxy(20, 5);
    printf("============================================================");

    int set_y = 7;                                  // 커서 이동 y좌표
    int day;                                        // 날짜 (n일)
    int startDay = firstDay_week(1, month, year);   // 매달 1일의 요일 [ 일(0) 월(1) 화(2) 수(3) 목(4) 금(5) 토(6) ]

    // 일요일 날짜를 기준으로 출력 좌표 설정 (24 + 8칸 간격 * 요일, set_y)
    gotoxy(24 + 8 * startDay, set_y);

    // n일 출력 (1일부터 n월의 마지막날까지)
    for (day = 1; day <= numberOfDays(month, year); day++)
    {
        // 날짜 + 시작 요일을 7로 나눈 나머지에 따라 요일 결정 [ 0(토), 1(일), 2(월), 3(화), 4(수), 5(목), 6(금) ]

        // 일요일은 빨간색으로 출력
        if ((day + startDay) % 7 == 1)
        {
            textcolor(RED);
            printf("%3d     ", day);
            textcolor(WHITE);
        }

        // 토요일은 하늘색으로 출력한 뒤 일요일로 넘어가기 전에 줄 바꾸기
        else if ((day + startDay) % 7 == 0)
        {
            textcolor(darkSkyBlue);
            printf("%3d     ", day);
            textcolor(WHITE);
            set_y += 4;
            gotoxy(24, set_y);
        }

        // 나머지는 흰색으로 출력 (8칸 간격 - 글씨 3칸 + 빈칸 5칸)
        else
            printf("%3d     ", day);
    }
    gotoxy(20, 31);
    printf("============================================================");
}

// (보조) n년 n월 1일이 무슨 요일인지 반환하는 함수 (완)
int firstDay_week(int day, int month, int year) {
    // 첼러의 공식 사용 -> 1월, 2월은 전년도 13, 14월로 계산
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }

    // 첼러의 공식의 원래 결과값 - [ 토(0) 일(1) 월(2) 화(3) 수(4) 목(5) 금(6) ]
    int h = (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;

    // 일요일을 0으로 하기 위해 h - 1 실행 (한 칸씩 당겨짐)
    h--;

    // 토요일은 -1이 되므로 6으로 바꿔주기
    if (h == -1)
        return 6;

    // 최종적으로 [ 일(0) 월(1) 화(2) 수(3) 목(4) 금(5) 토(6) ]
    else
        return h;
}

// (보조) n년 n월은 며칠까지 있는지 계산하는 함수 (윤년 포함) (완)
int numberOfDays(int month, int year) {
    if (month == 2)
    {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
            return 29;
        else
            return 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

// (보조) 0년부터 해당 날짜까지 일수를 반환하는 암수 (완)
int totalday(int year, int month, int day)
{
    int month_day[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (numberOfDays(2, year) == 29)
        month_day[1] = 29;

    int total = 365 * (year - 1);

    total += (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

    for (int i = 0; i < month - 1; i++)
        total += month_day[i];

    total += day;
    return total;
}

// (보조) 선택한 날짜는 오늘 날짜로부터 며칠 남았는지/지났는지 반환하는 함수
int D_day(int choiceyear, int choicemonth, int choiceday)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // 오늘 날짜 설정
    int t_month = tm.tm_mon + 1;      // (0~11)이므로 +1
    int t_year = tm.tm_year + 1900;   // 1900년도 이후부터이므로 +1900
    int t_day = tm.tm_mday;

    int todayTotal = totalday(t_year, t_month, t_day);
    int selectTotal = totalday(choiceyear, choicemonth, choiceday);

    return (todayTotal - selectTotal);
}