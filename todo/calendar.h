#ifndef CALENDAR_H
#define CALENDAR_H
void printCalendar(int month, int year);                    // n년 m월의 달력을 출력하는 함수
int firstDay_week(int day, int month, int year);            // 달의 1일이 무슨 요일인지 판단하는 함수 (첼러의 공식)
int numberOfDays(int month, int year);                      // n년 m월이 며칠까지 있는지 반환하는 함수
int totalday(int year, int month, int day);                 // 0년부터 해당 날짜까지 흐른 일수를 반환하는 함수
int D_day(int choiceyear, int choicemonth, int choiceday);  // 오늘 날짜 기준 해당 날짜가 며칠 남았는지 반환하는 함수
#endif
