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

// 2-1-1. 일정 출력 함수 
void printPlan(int year, int month, int day)
{
    FILE* fp = NULL;                                    // 파일 포인터

    char str[BUFSIZ], title[BUFSIZ], content[BUFSIZ];   // 파일에 저장된 일정의 제목, 내용을 저장하는 변수
    int i = 36;                                         // 커서 Y 좌표
    int count = 1;                                      // 파일에서 줄을 읽어들인 수
    int fpYear, fpMonth, fpDay;                         // 파일에 저장된 일정의 날짜를 저장하는 변수
    int color;                                          // 파일에 저장된 일정 제목의 색상을 저장하는 변수

    fp = fopen("Plan.txt", "r+");                       // 입출력용 파일 열기 (일정 파일)

    // 만약 파일을 찾지 못하면
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    gotoxy(28, i);
    while (fgets(str, sizeof(str), fp) != NULL)         // 한 줄씩 읽어들임, NULL이 나올 때까지
    {
        sscanf(str, "%d/%d/%d, %[^,], %[^,], %d", &fpYear, &fpMonth, &fpDay, title, content, &color);   // 날짜, 제목, 내용, 색상 추출
        if (fpYear == year && fpMonth == month && fpDay == day)                                         // 파일에 저장된 날짜가 선택한 날짜와 같으면
        {
            // 번호. [제목] : 내용 형식으로 출력
            printf("%2d. [", count);
            textcolor(color);
            printf("%7s", title);
            textcolor(WHITE);
            printf(" ] : %s\n", content);
            count++;
            i++;
            gotoxy(28, i);
        }
    }
    fclose(fp);                                         // 파일 닫기
}

// 2-1-2. 일정 추가 함수
void addPlan(int year, int month, int day)
{
    FILE* fp;
    char title[9], content[40];             // 제목, 내용

    getchar();
    // 제목 입력
    cursor(1);
    gotoxy(28, 33);
    printf("제목 (한글 3글자까지) : ");
    fgets(title, sizeof(title), stdin);
    title[strlen(title) - 1] = '\0';        // 개행 문자 제거

    // 내용 입력
    gotoxy(28, 34);
    printf("내용 : ");
    fgets(content, sizeof(content), stdin);
    content[strlen(content) - 1] = '\0';

    fp = fopen("Plan.txt", "a+");           // Plan.txt 파일 열기 (없으면 생성)

    if (fp == NULL)                         // 파일 열기 실패
    {
        gotoxy(28, 35);
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 일정 추가
    fprintf(fp, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, title, content, WHITE);
    fclose(fp);

    // 일정 추가가 완료되면 다시 일정 메뉴로 (2-1의 reset으로)
    gotoxy(38, 35);
    printf("일정이 추가되었습니다.\n");
    Sleep(1000);
}

// 2-1-3. 일정 수정 함수
void editPlan(int year, int month, int day) {
    FILE* fp, * tempFile;
    char str[256], title[9], content[40], newTitle[7], newContent[40];      // 제목, 내용, 새로운 제목, 새로운 내용
    int fileYear, fileMonth, fileDay, color;                                // 연/월/일, 제목 색상
    int count = 1, choice, number, newYear, newMonth, newDay, newColor;     // 읽은 줄 수, 변경할 항목 선택, 변경할 일정 번호, 새로운 연/월/일, 새로운 제목 색상
    int found = 0;                                                          // 바꾸려는 일정이 정말 있는지, 수정이 되었는지 확인

    // 변경할 일정 번호 선택
    cursor(1);
    gotoxy(38, 33);
    printf("변경할 일정의 번호 : ");
    scanf("%d", &number);
    getchar();                              // 버퍼 제거

    fp = fopen("Plan.txt", "r+");           // Plan 파일 열기
    tempFile = fopen("temp.txt", "w+");     // 임시 파일 (임시 파일에 변경 내용을 저장 후, 임시 파일의 이름을 Plan으로 바꾼 뒤 기존 Plan 파일 삭제) 열기

    if (fp == NULL || tempFile == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 한 줄씩 읽음 (바꿀 일정 찾기)
    while (fgets(str, sizeof(str), fp))
    {
        sscanf(str, "%d/%d/%d, %[^,], %[^,], %d", &fileYear, &fileMonth, &fileDay, title, content, &color); // 날짜, 제목, 내용, 제목 색상 추출

        // 연/월/일이 같은 문장을 찾았을 때
        if (fileYear == year && fileMonth == month && fileDay == day)
        {
            // 줄을 읽은 횟수 == 내가 바꾸려 하는 일정의 번호 일 때
            if (count == number)
            {
                gotoxy(24, 34);
                printf("변경할 항목 (1. 날짜, 2. 제목, 3. 내용, 4. 제목 색상)");
                choice = _getch() - '0';    // 문자 하나를 엔터키 없이 입력받음. - '0'을 한 이유는 입력받은 문자를 숫자로 바꾸기 위함

                switch (choice)
                {
                    // 날짜 변경
                case 1:
                    gotoxy(28, 35);
                    printf("새로운 날짜 (yyyy mm dd): ");
                    scanf("%d %d %d", &newYear, &newMonth, &newDay);
                    getchar();                                          // 버퍼 지우기

                    // 새로운 연/월/일, 나머지는 그대로 저장하기
                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", newYear, newMonth, newDay, title, content, color);

                    // 찾았다 & 수정했다는 표시
                    found = 1;

                    break;

                    // 제목 변경
                case 2:
                    gotoxy(28, 35);
                    printf("새로운 제목 (한글 3글자 제한): ");
                    fgets(newTitle, sizeof(newTitle), stdin);
                    newTitle[strlen(newTitle)] = '\0';
                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, newTitle, content, color);
                    found = 1;
                    break;

                    // 내용 변경
                case 3:
                    gotoxy(28, 35);
                    printf("새로운 내용: ");
                    fgets(newContent, sizeof(newContent), stdin);
                    newContent[strlen(newContent) - 1] = '\0';
                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, title, newContent, color);
                    // 찾았다는 표시
                    found = 1;
                    break;

                    // 제목 색상 변경
                case 4:
                    gotoxy(28, 35);
                    printf("새로운 색상 (0~15): ");
                    scanf("%d", &newColor);
                    getchar();

                    // 열거체에 있는 번호 (0~15)를 벗어나면 흰색(15)으로 자동 설정 
                    if (newColor > 15 || newColor < 0)
                    {
                        gotoxy(28, 35);
                        printf("잘못된 색상입니다. 흰색으로 변경합니다.");
                        newColor = 15;
                    }

                    fprintf(tempFile, "%04d/%02d/%02d, %s, %s, %d\n", year, month, day, title, content, newColor);
                    // 찾았다는 표시
                    found = 1;
                    break;

                    // 다른 문자 입력시
                default:
                    gotoxy(28, 35);
                    printf("잘못된 선택입니다.\n");
                    break;
                }
            }
            // 같은 연/월/일이지만 내가 수정하려는 일정이 아닐 때
            else
                fputs(str, tempFile);   // 변경하지 않는 일정 그대로 복사
            count++;
        }
        // 다른 연/월/일이고 내가 수정하려는 일정도 아닐 때
        else
            fputs(str, tempFile);       // 다른 날짜의 일정 그대로 복사
    }

    fclose(fp);
    fclose(tempFile);

    if (found == 0)
    {
        gotoxy(25, 35);
        printf("번호에 해당하는 일정이 없거나 수정하지 못했습니다.");
        Sleep(1000);
        return;
    }

    remove("Plan.txt");             // 원래 파일 삭제
    rename("temp.txt", "Plan.txt"); // 임시 파일을 원래 파일로 이름 변경

    gotoxy(28, 35);
    printf("                                                                                        ");
    gotoxy(38, 35);
    printf("일정이 수정되었습니다.");
    Sleep(1000);
    // 바뀐 일정을 다시 출력하고 2-1의 reset으로 이동
    printPlan(year, month, day);

}

// 2-1-4. 일정 삭제 함수
void deletePlan(int year, int month, int day) {
    FILE* fp, * tempFile;
    char str[256], title[9], content[40];
    int fileYear, fileMonth, fileDay, color;
    int count = 1, number;
    int found = 0;

    cursor(1);
    gotoxy(38, 33);
    printf("삭제할 일정의 번호 : ");
    scanf("%d", &number);
    getchar(); // 개행 문자 제거

    fp = fopen("Plan.txt", "r+"); // 파일 열기
    tempFile = fopen("temp.txt", "w+"); // 임시 파일 열기

    if (fp == NULL || tempFile == NULL)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    while (fgets(str, sizeof(str), fp))
    {
        sscanf(str, "%d/%d/%d, %[^,], %[^,], %d", &fileYear, &fileMonth, &fileDay, title, content, &color); // 날짜, 제목, 내용 추출

        if (fileYear == year && fileMonth == month && fileDay == day)
        {
            if (count != number)
                fputs(str, tempFile); // 삭제하지 않는 일정 그대로 복사
            if (count == number)
                found = 1;
            count++;
        }
        else {
            fputs(str, tempFile); // 다른 날짜의 일정 그대로 복사
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove("Plan.txt"); // 원래 파일 삭제
    rename("temp.txt", "Plan.txt"); // 임시 파일을 원래 파일로 이름 변경

    if (found == 0)
    {
        gotoxy(32, 35);
        printf("번호에 해당하는 일정이 없습니다.");
        Sleep(1000);
        return;
    }

    gotoxy(28, 35);
    printf("                                                                                        ");
    gotoxy(38, 35);
    printf("일정이 삭제되었습니다.");
    Sleep(1000);
    printPlan(year, month, day);
}