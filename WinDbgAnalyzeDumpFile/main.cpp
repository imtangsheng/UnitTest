#include <Windows.h>
#include <DbgHelp.h>
#include <ctime>
#include <stdio.h>  // ������ͷ�ļ�����sprintf_s
#include <string>   // �����������ַ�������
#pragma comment(lib, "DbgHelp.lib")

LONG ApplicationCrashHandler(EXCEPTION_POINTERS* pException) {
    // ��ȡ��ǰʱ�䲢��ʽ��
    time_t now;
    time(&now);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);

    // ������ʱ������ļ���
    char dumpFileName[MAX_PATH];
    snprintf(dumpFileName, MAX_PATH, "crash_%04d%02d%02d_%02d%02d%02d.dmp",
        timeInfo.tm_year + 1900,
        timeInfo.tm_mon + 1,
        timeInfo.tm_mday,
        timeInfo.tm_hour,
        timeInfo.tm_min,
        timeInfo.tm_sec);

    // ����Dump�ļ�
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

    // Dump��Ϣ
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
    dumpInfo.ExceptionPointers = pException;
    dumpInfo.ThreadId = GetCurrentThreadId();
    dumpInfo.ClientPointers = TRUE;

    // д��Dump�ļ�����
    BOOL bSuccess = MiniDumpWriteDump(GetCurrentProcess(),
        GetCurrentProcessId(),
        hDumpFile,
        MiniDumpNormal,//��С��ͨ����MB
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
    //ע���쳣������  
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
    fun(NULL);
    return 0;

}