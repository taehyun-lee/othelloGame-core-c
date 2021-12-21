#pragma once

/*
* 홈경로에 record.txt, backup.txt가 있는지 확인 및 생성하는 함수
*/
void checkFile();

/*
* record.txt파일의 데이터를 가지고오는 함수
* @param _record : 파일의 데이터를 저장되는 변수
* @param _max_line : 읽어올 수 있는 최대 행의 개수
* p1_score, p2_score, winner, playtime, date
* @return 빈파일인 경우 false를 리턴 정보가 존재할 시 true를 리턴
*/
bool getRecord(int(*_record)[5], int _max_line);

/*
* record.txt파일에 데이터를 입력하는 함수
* 최대 행 개수가 초과 될 경우 가장 과거의 레코드 삭제 후 업데이트
* 반드시 _record는 길이가 5인 배열 주소이어야 한다
* @param _record : 저장할 데이터
* @param _max_line : 최대 행 개수
* p1_score, p2_score, winner, playtime, date
*/
bool setRecord(int* _record, int _max_line);

/*
* backup.txt파일에서 데이터를 가지고오는 함수
* @return 빈파일인 경우 false를 리턴, 정보가 존재할 시 true를 리턴
*/
bool getBackup();

/*
* backup.txt파일에 데이터를 입력하는 함수
* @param _map : 저장할 데이터
* @return 정상적으로 파일에 출력이 되었을 경우 true 리턴
*/
bool setBackup(int(*_map)[10]);
