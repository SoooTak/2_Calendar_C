#ifndef LOGIN_H
#define LOGIN_H
#define MAX_MEMBER 100
#define MAX_ID 50
#define MAX_PASSWORD 50

char infoMessage[100];

typedef struct member
{
	char id[MAX_ID];
	char password[MAX_PASSWORD];
}MEMBER;

// 로그인 관련 함수
int checkDupID(const char* id);
void addMember();
int login();

#endif
