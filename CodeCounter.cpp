/*************************************************
*   ���ߣ��غƲ�
*   ���ڣ�2020-05-04
*   ���������������鿴��
*   ���ӣ�https://github.com/ghb123/CodeCounter
**************************************************/
#include <bits/stdc++.h>
#include <io.h>
using namespace std;
/* �洢�ļ�·�� */
vector<string> files;

/* ָ����չ�� */
vector<string> type;

/* ���ܻ�ȡ·��path�����е��ļ�·�����������ļ�����ģ����洢��files�� */
void getFiles(string path, vector<string> &files)
{
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

/* ��ȡ�ļ����� */
int getLineNum(string path)
{
    int ans = 0, first = 1;
    char ch = ' ';
    FILE *fp = fopen(path.c_str(), "r");
    if (fp == NULL)
        return 0;
    while (ch != EOF)
    {
        ch = fgetc(fp);
        if (ch == '\n')
            ans++;
    }
    return ans + 1;
}

/* �ж��Ƿ���Ŀ����չ�� */
bool isTarget(string path)
{
    if (type.size() == 0)
        return true;
    string name = path.substr(path.find_last_of(".") + 1);
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    if (find(type.begin(), type.end(), name) != type.end())
        return true;
    return false;
}

/* ������ */
int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cout << "error" << endl;
        return -1;
    }
    string filePath = argv[1];
    //������չ��
    for (int i = 2; i < argc; i++)
        type.push_back(argv[i]);
    //��ȡ�����ļ���·��
    getFiles(filePath, files);
    int num, ans = 0;
    for (int i = 0; i < files.size(); i++)
    {
        //�����Ŀ����չ�������ȡ����
        if (isTarget(files[i]))
        {
            num = getLineNum(files[i]);
            ans += num;
            cout << files[i] << "\t������" << num << endl;
        }
    }
    cout << endl
         << "��������" << ans << endl;
    return 0;
}