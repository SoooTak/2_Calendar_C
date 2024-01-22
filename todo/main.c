/*
    프로젝트 : 일정관리 (캘린더) 프로그램
    팀 : 1조 (A+ 조)
    팀장 : 김민상 (202311388)
    부팀장 : 박유진 (202311403) 배지환 (202111679)
    팀원 : 김남훈 (202311385) 김아영 (202311394) 서하제 (202311409) 음영민 (202311425) 최민국 (202111495) 홍태민 (202311448)
    작성일 : 2023.11.11 ~ 2023.12.03
*/

/*
    프로젝트 진행
    1. 달력 출력 (완료)
    2. 달력 달 이동 (완료)
    3. 일정 파일 생성 (일정 추가) (완료)
    4. 날짜 선택 기능 (완료)
    5. 선택한 날짜 일정 출력 기능 (날짜 선택) (완료)
    6. 일정 추가 기능 (완료)
    7. 일정 삭제 기능 (완료)
    8. 일정 수정 기능 (완료)
     8-1. 글자색 변경 기능 (완료)
    9. 예정일 기능 (완료)

     5-1. 비밀 일정 열람 기능 (패스워드)
     6-1. 비밀 일정 추가 기능
     8-2. 비밀 일정 <--> 일반 일정 변환 기능
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>       // 현재 날짜 확인
#include <windows.h>    // 콘솔창 크기 설정, 화면 클리어
#include <conio.h>      // _getch() 함수 사용 (엔터키 입력 없이 문자 입력)
#include "color.h"      // 여러 함수가 정의된 직접 정의한 헤더파일 포함
#include "calendar.h"
#include "assistant.h"
#include "menu.h"
#include "plan.h"
#include "login.h"

// 0. 메인 함수 (완)
int main(void)
{
    // 콘솔창 크기 설정 (가로 100픽셀 세로 30줄)
    system("mode con:cols=100 lines=30");
    int choice, y;

    do 
    {
        system("cls");
        printBOX();                         // 로그인창 네모 박스 그리기
        gotoxy(44, 13);                     
        printf("1. 회원가입\n");
        gotoxy(44, 14);
        printf("2. 로그인\n");
        gotoxy(44, 15);
        printf("3. 종료\n");

        gotoxy(24, 7);
        printf("  [ 프로그래밍2 ");
        textcolor(YELLOW);
        printf("1팀 ");
        textcolor(WHITE);
        printf("프로젝트 - ");
        textcolor(darkSkyBlue);
        printf("일정 관리 프로그램");
        textcolor(WHITE);
        printf("] ");

        cursor(0);                          // 커서 안 보이게
        choice = _getch() - '0';            // 엔터 입력 없이 숫자 하나 입력받기
        cursor(1);                          // 커서 보이게

        switch (choice) {
            // 회원가입
        case 1:
            addMember();
            break;

            // 로그인
        case 2:
            // 로그인 성공 시 메인 화면으로 넘어감 (달력)
            if (login()) {
                // 콘솔창 넓게 바꾸기
                system("mode con:cols=100 lines=50");
                // 오늘 날짜 구하기 (현재 시간 기준으로 tm 구조체 설정)
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                // 오늘 날짜 설정
                month = tm.tm_mon + 1;      // (0~11)이므로 +1
                year = tm.tm_year + 1900;   // 1900년도 이후부터이므로 +1900
                day = tm.tm_mday;

                // 현재 달의 달력 출력
                printCalendar(month, year);

                // 메뉴 출력
                Menu();
            }
            break;

            // 종료
        case 3:
            y = 7;                                      // y좌표
            system("cls");
            gotoxy(24, y++);
            printf("  [ 프로그래밍2 ");
            textcolor(YELLOW);
            printf("1팀 ");
            textcolor(WHITE);
            printf("프로젝트 - ");
            textcolor(darkSkyBlue);
            printf("일정 관리 프로그램");
            textcolor(WHITE);
            printf("] ");
            y++;
            gotoxy(36, y++);
            printf("[      ]  김민상 (202311388)");
            gotoxy(35, y++);
            printf("[        ] 박유진 (202311403)");
            gotoxy(35, y++);
            printf("[        ] 배지환 (202111679)");
            gotoxy(36, y++);
            printf("[      ]  김남훈 (202311385)");
            gotoxy(36, y++);
            printf("[      ]  김아영 (202311394)");
            gotoxy(36, y++);
            printf("[      ]  서하제 (202311409)");
            gotoxy(36, y++);
            printf("[      ]  음영민 (202311425)");
            gotoxy(36, y++);
            printf("[      ]  최민국 (202111495)");
            gotoxy(36, y++);
            printf("[      ]  홍태민 (202311448)");
            printf("\n");
            textcolor(RED);
            y = 9;
            gotoxy(38, y++);
            printf("팀장");
            textcolor(SkyBlue);
            gotoxy(37, y++);
            printf("부팀장");
            gotoxy(37, y++);
            printf("부팀장");
            textcolor(YELLOW);
            gotoxy(38, y++);
            printf("팀원");
            gotoxy(38, y++);
            printf("팀원");
            gotoxy(38, y++);
            printf("팀원");
            gotoxy(38, y++);
            printf("팀원");
            gotoxy(38, y++);
            printf("팀원");
            gotoxy(38, y++);
            printf("팀원");
            gotoxy(38, y++);
            textcolor(WHITE);
            gotoxy(38, 25);
            break;

            // 회원가입, 로그인, 종료 셋 다 아니면
        default:
            printf("잘못된 메뉴를 선택했습니다.\n");
            Sleep(1000);
        }
    } while (choice != 3);

    return 0;
}