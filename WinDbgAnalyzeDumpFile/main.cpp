#include <Windows.h>
#include <DbgHelp.h>
#include <ctime>
#include <stdio.h>  // 添加这个头文件用于sprintf_s
#include <string>   // 添加这个用于字符串处理
#pragma comment(lib, "DbgHelp.lib")

LONG ApplicationCrashHandler(EXCEPTION_POINTERS* pException) {
    // 获取当前时间并格式化
    time_t now;
    time(&now);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);

    // 创建带时间戳的文件名
    char dumpFileName[MAX_PATH];
    snprintf(dumpFileName, MAX_PATH, "crash_%04d%02d%02d_%02d%02d%02d.dmp",
        timeInfo.tm_year + 1900,
        timeInfo.tm_mon + 1,
        timeInfo.tm_mday,
        timeInfo.tm_hour,
        timeInfo.tm_min,
        timeInfo.tm_sec);

    // 创建Dump文件
    HANDLE hDumpFile = CreateFileA(dumpFileName,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hDumpFile == INVALID_HANDLE_VALUE) {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    // Dump信息
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;

    // 写入Dump文件内容
    BOOL bSuccess = MiniDumpWriteDump(GetCurrentProcess(),
        GetCurrentProcessId(),
        hDumpFile,
        MiniDumpNormal,//最小，通常几MB
        &dumpInfo,
        NULL,
        NULL);

    CloseHandle(hDumpFile);

    return bSuccess ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
}

void fun(int* p) {
    p[0] = 0;
}
int main(int argc, char* argv[]) {
    //注册异常处理函数  
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    fun(NULL);
    return 0;

}