#ifndef MENU_H
#define MENU_H

// 날짜 저장 변수, 메뉴 선택 변수 (전역변수)
int month, year, day;
char choice_menu;

// 메뉴 함수들
int Menu(void);                                             // 메뉴를 출력하는 함수
void choice_day(void);                                      // 메뉴_날짜선택 함수
#endif