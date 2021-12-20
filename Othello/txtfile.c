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
		if (i >= 10) {
			fclose(file);
			return true;
		}
	}

	fclose(file);
	if (i == 0) {
		return false;
	}

	return true;
}

bool setRecord(int* _record, int _max_line)
{
	FILE* file;
	char line[255];  //  파일에서 읽어오는 행
	char target[255];  //  입력할 행
	int row = 0;
	int i;

	file = fopen("record.txt", "a+");
	target[0] = '\0';

	//  int 배열 형 매개변수를 하나의 문자열로 변환
	for (i = 0; i < 5; i++) {
		char tok[50];
		itoa(_record[i], tok, 10);
		strcat(target, tok);
		strcat(target, " ");
	}

	//  2차원 동적 배열 생성 및 초기화
	char** txt_info = malloc(sizeof(char*)*_max_line);
	for (i = 0; i < _max_line; i++) {
		if (txt_info != NULL) {
			txt_info[i] = malloc(sizeof(char) * 200);
			if (txt_info[i] != NULL)
				txt_info[i][0] = '\0';
			else
				return false;
		}
		else
			return false;
	}

	//  파일 데이터 읽기
	while((fgets(line, sizeof(line), file) != NULL)) {
		for (i = 0; i < strlen(line) + 1; i++) {
			txt_info[row][i] = line[i];
			if (i == strlen(line) + 1)
				txt_info[row][i] = '\0';
		}
		row++;
	}

	if (row < _max_line) {
		fseek(file, 0, SEEK_END);
		fputs("\n", file);
		fputs(target, file);
		fclose(file);
	}
	else {
		fclose(file);
		FILE* file_re;
		file_re = fopen("record.txt", "w");
		fseek(file_re, 0, SEEK_SET);  //  파일 포인터 첫행으로 이동
		int cnt = 0;
		for (i = 1; i < _max_line; i++) { // 기존 파일의 2번째 행부터 첫행에 출력
			fputs(txt_info[i], file_re);
		}
		fputs("\n", file_re);
		fputs(target, file_re);
		fclose(file_re);
	}
	for (int k = 0; k < _max_line; k++)
		free(txt_info[k]);
	free(txt_info);
	
	return true;
}
