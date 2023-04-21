#pragma once
#include <Windows.h>

// double buffering
static int screenIndex; // 콘솔 접근 인덱스
static HANDLE screen[2]; // 콘솔 2개

void ScreenInit(); // 콘솔 2개를 준비하는 함수
void ScreenFlipping(); // 화면에 보여줄 콘솔을 스위칭 하는 함수
void ScreenClear(); // 스크린을 빈공간으로 지우는 함수
void ScreenPrint(int x, int y, const char* string);