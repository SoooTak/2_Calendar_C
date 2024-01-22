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
#include "login.h"

// 아이디 중복 검사
int checkDupID(const char* id)
{
    FILE* file = fopen("member.txt", "r");

    if (file == NULL) {
        perror("파일 열기 실패\n");
        return 1;
    }

    MEMBER currentMember;
    
    while (fscanf(file, "%s %s", currentMember.id, currentMember.password) == 2) {
        if (strcmp(id, currentMember.id) == 0) {
            fclose(file);
            return 0; // 중복됨
        }
    }

    fclose(file);
    return 1; // 중복 없음
}

// 회원가입 함수
void addMember()
{
    FILE* file = fopen("member.txt", "a");

    if (file == NULL) {
        gotoxy(44, 20);
        perror("파일 열기 실패\n");
        Sleep(1000);
        return;
    }

    MEMBER newMember;

    system("cls");
    printBOX();
    gotoxy(38, 13);
    printf("아이디: ");
    scanf("%s", newMember.id);

    // 중복 검사 추가
    if (!checkDupID(newMember.id)) {
        fclose(file);
        gotoxy(38, 20);
        printf("이미 존재하는 아이디입니다.\n");
        Sleep(1000);
        return;
    }

    getchar();
    gotoxy(38, 15);
    printf("비밀번호: ");
    scanf("%s", newMember.password);
    getchar();
    fprintf(file, "%s %s\n", newMember.id, newMember.password);

    fclose(file);
    gotoxy(44, 20);
    for (int i = 0; i < 15; i++)
    {
        char addOK[15] = { "회원가입 성공!" };
        printf("%c", addOK[i]);
        Sleep(100);
    }
    Sleep(1000);
}

// 로그인 함수
int login()
{
    FILE* file = fopen("member.txt", "r");

    if (file == NULL) {
        gotoxy(38, 20);
        perror("파일 열기 실패");
        return 0;
    }

    char inputUsername[MAX_ID];
    char inputPassword[MAX_PASSWORD];

    system("cls");
    printBOX();

    gotoxy(38, 13);
    printf("아이디: ");
    scanf("%s", inputUsername);

    gotoxy(38, 15);
    printf("비밀번호: ");
    scanf("%s", inputPassword);

    MEMBER currentMember;

    while (fscanf(file, "%s %s", currentMember.id, currentMember.password) == 2) {
        if (strcmp(inputUsername, currentMember.id) == 0 && strcmp(inputPassword, currentMember.password) == 0) {
            fclose(file);
            gotoxy(44, 20);
            for (int i = 0; i < 13; i++)
            {
                char loginOK[13] = { "로그인 성공!" };
                printf("%c", loginOK[i]);
                Sleep(100);
            }
            Sleep(1000);
            return 1; // 로그인 성공
        }
    }

    fclose(file);
    gotoxy(44, 20);
    printf("로그인 실패.\n");
    Sleep(1000);
    return 0; // 로그인 실패
}