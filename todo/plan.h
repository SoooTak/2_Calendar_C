#ifndef PLAN_H
#define PLAN_H
// 파일 처리 관련 함수들
void printPlan(int year, int month, int day);               // 파일에서 특정 일정을 읽어들여 출력하는 함수
void addPlan(int year, int month, int day);                 // 일정을 입력하면 파일에 저장하는 함수
void editPlan(int year, int month, int day);                // 일정 파일을 일정을 수정한 파일로 교체하는 함수 (일정 수정)
void deletePlan(int year, int month, int day);              // 특정 날짜의 특정 일정을 삭제하는 함수

#endif