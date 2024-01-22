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

// 2. 메뉴 출력 함수
int Menu(void)
{
    //메뉴 선택_x를 입력할 때까지 무한 반복
    while (1)
    {
        // 메뉴 출력 좌표 이동
        gotoxy(23, 32);
        cursor(0);
        printf("[ -1달 : A,  +1달 : D,  날짜 선택 : C,  로그아웃 : X ]");

        // 메뉴 입력창 좌표 이동
        choice_menu = _getch(); // _getch() : 엔터키 없이 키 하나를 입력받을 수 있음

        // +1달 이동
        if (choice_menu == 'd' || choice_menu == 'D')
        {
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
            printCalendar(month, year);
        }

        // -1달 이동
        else if (choice_menu == 'a' || choice_menu == 'A')
        {
            month--;
            if (month < 1)
            {
                month = 12;
                year--;
            }
            printCalendar(month, year);
        }

        // 날짜 선택
        else if (choice_menu == 'c' || choice_menu == 'C')
            choice_day();

        // 종료
        else if (choice_menu == 'x' || choice_menu == 'X')
        {
            system("mode con:cols=100 lines=30");
            return 0;
        }

        // 다른 입력 => 다시 입력받기
        else
            continue;
    }
}

// 2-1. 메뉴_날짜 선택 함수
void choice_day(void)
{
    int choiceday;                              // 날짜 선택 변수
    int checkday = numberOfDays(month, year);   // 날짜 범위 확인하는 변수
    int DDay;
    while (1)
    {
        // 화면 초기화 & 달력 출력
        printCalendar(month, year);

        cursor(1);
        gotoxy(40, 32);
        printf("[ 날짜 선택 :    ]");
        gotoxy(41, 33);
        printf("[ 선택 취소 : 0 ]");

        gotoxy(54, 32);
        scanf("%d", &choiceday);

        // 입력한 날짜가 음수이거나, 해당 달의 마지막 날짜보다 크면
        if (choiceday > checkday || choiceday < 0)
        {
            gotoxy(35, 33);
            printf("잘못된 날짜입니다. (1 ~ %d일)", checkday);
            Sleep(1000);
        }

        // 입력한 날짜가 0이면 메인 화면으로 돌아가기
        else if (choiceday == 0)
        {
            printCalendar(month, year);
            break;
        }

        // 날짜 선택
        else
        {
            // 일정 관련 메뉴를 선택해 수행하면 다시 이곳으로 돌아오기
        reset:
            printCalendar(month, year);

            gotoxy(38, 32);
            printf("      [ %d월 %d일 ]      ", month, choiceday);

            // 오늘 날짜 기준 디데이 설정
            gotoxy(59, 32);
            DDay = D_day(year, month, choiceday);
            if (DDay > 0)
                printf("[ D + %2d ]", DDay);
            else if (DDay < 0)
                printf("[ D - %2d ]", -DDay);
            else
                printf("[ D - Day ]");

            cursor(0);
            gotoxy(25, 33);
            printf("[ 일정 추가 : A,  일정 수정 : S,  일정 삭제 : D ]");
            gotoxy(27, 34);
            printf("[ 날짜 선택 : C,  처음 화면으로 돌아가기 : F ]");

            // 선택한 날의 일정 출력 함수
            printPlan(year, month, choiceday);

            choice_menu = _getch();

            // 다른 날짜 선택
            if (choice_menu == 'c' || choice_menu == 'C')
                continue;

            // 처음 화면으로
            else if (choice_menu == 'f' || choice_menu == 'F')
            {
                system("cls");
                printCalendar(month, year);
                break;
            }

            // 일정 추가 메뉴
            else if (choice_menu == 'a' || choice_menu == 'A')
            {
                printCalendar(month, year);                               // 화면 초기화 (달력 출력)
                gotoxy(38, 32);
                printf("      [ %d월 %d일 ]      ", month, choiceday);    // 선택한 날짜
                printPlan(year, month, choiceday);                        // 선택한 날의 일정 출력
                addPlan(year, month, choiceday);                          // 선택한 날의 일정을 추가
                goto reset;                                               // reset으로 이동
            }

            // 일정 수정 메뉴
            else if (choice_menu == 's' || choice_menu == 'S')
            {
                printCalendar(month, year);
                gotoxy(38, 32);
                printf("      [ %d월 %d일 ]      ", month, choiceday);
                printPlan(year, month, choiceday);
                editPlan(year, month, choiceday);
                goto reset;
            }

            // 일정 삭제 메뉴
            else if (choice_menu == 'd' || choice_menu == 'D')
            {
                printCalendar(month, year);
                gotoxy(38, 32);
                printf("      [ %d월 %d일 ]      ", month, choiceday);
                printPlan(year, month, choiceday);
                deletePlan(year, month, choiceday);
                goto reset;
            }

            // 다른 입력 => 다시 입력받기
            else
                goto reset;
        }
    }
}