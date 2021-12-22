#include "common.h"

void checkFile()
{
	FILE* file_record, * file_backup;

	file_record = fopen("record.txt", "a");
	file_backup = fopen("backup.txt", "a");

	fclose(file_record);
	fclose(file_backup);
}

bool getRecord(int(*_record)[5])
{
	FILE* file;
	char line[255];
	file = fopen("record.txt","r");
	int i = 0;

	while (fgets(line, sizeof(line), file) != NULL) {
		int j = 0;
		char* ptr = strtok(line, " ");
		while (ptr != NULL) {
			_record[i][j++] = atoi(ptr);
			ptr = strtok(NULL, " ");
		}
		i++;
		if (i == MAXLINE)
			break;
	}

	fclose(file);
	if (i == 0)
		return false;
	else
		return true;
}

bool setRecord(int* _record)
{
	FILE* file;
	char line[255];  //  파일에서 읽어오는 행
	char target[255];  //  입력할 행
	char txt_info[MAXLINE][255];
	int row = 0;
	int i;

	file = fopen("record.txt", "a+");
	target[0] = '\0';

	//  int 배열 형 매개변수를 하나의 문자열로 변환
	for (i = 0; i < 5; i++) {
		char tok[50];
		itoa(_record[i], tok, 10);
		strcat(target, tok);
		if (i != 4)
			strcat(target, " ");
		//else
		//	strcat(target, "\n");
	}
	//  파일 데이터 읽기
	while((fgets(line, sizeof(line), file) != NULL)) {
		for (i = 0; i < strlen(line) + 1; i++) {
			if (i == strlen(line) + 1)
				txt_info[row][i] = '\0';
			else
				txt_info[row][i] = line[i];
		}
		row++;
		if (row == MAXLINE)
			break;
	}

	if (row < MAXLINE) {
		fseek(file, 0, SEEK_END);
		fputs(target, file);
		fclose(file);
	}
	else {
		fclose(file);
		FILE* file_re;
		file_re = fopen("record.txt", "w");
		fseek(file_re, 0, SEEK_SET);  //  파일 포인터 첫행으로 이동
		for (int k = 1; k < MAXLINE; k++) { // 기존 파일의 2번째 행부터 첫행에 출력
			fputs(txt_info[k], file_re);
		}
		fputs("\n", file_re);
		fputs(target, file_re);
		fclose(file_re);
	}

	return true;
}

bool getBackup()
{
	FILE* file;
	char line[255];
	int i = 0;
	bool file_empty = true;

	file = fopen("backup.txt", "r");

	for (i = 0; i < 10; i++) {
		//  올바른 문법형식이 아닌경우 return false
		if (fgets(line, sizeof(line), file) == NULL)
			return false;

		file_empty = false;
		int j = 0;
		char* ptr = strtok(line, " ");
		while (ptr != NULL) {
			g_map[i][j++] = atoi(ptr);
			ptr = strtok(NULL, " ");
		}
	}
	//  마지막 한줄 읽기-playtime
	if (fgets(line, sizeof(line), file) != NULL) {
		g_playtime = atoi(line);
	}

	fclose(file);
	if (file_empty)
		return false;
	else
		return true;
}

bool setBackup()
{
	FILE* file;
	file = fopen("backup.txt", "w");
	int i, j;
	char tok[50], ptime[10];

	if (file == NULL)
		return false;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			itoa(g_map[i][j], tok, 10);
			fputs(tok, file);
			if (j != 9)
				fputs(" ", file);
			else
				fputs("\n", file);
		}
	}
	itoa(g_playtime, ptime, 10);
	fputs(ptime, file);

	fclose(file);
	return true;
}
