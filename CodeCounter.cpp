//www.guanhaobo.cn
#include <io.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
vector<string> files; //�洢�ļ�·��
vector<string> type;  //ָ����չ��

//��ȡ·��path�����е��ļ������������ļ�����ģ����洢��files��
void getFiles(string path, vector<string> &files)
{
    //�ļ����
    long hFile = 0;
    //�ļ���Ϣ
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        { //�����Ŀ¼,����֮
            //�������,�����б�
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

//��ȡ�ļ�����
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

//�ж��Ƿ���Ŀ����չ��
bool isTarget(string path)
{
    if (type.size() == 0)
        return true;
    string name = path.substr(path.find_last_of(".") + 1);
    if (find(type.begin(), type.end(), name) != type.end())
        return true;
    return false;
}

int main()
{
    string filePath;
    cout << "��������Ŀ�ļ��е�·����";
    cin >> filePath;
    //������չ��
    type.push_back("java");
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
            cout << files[i] << "    ������" << num << endl;
        }
    }
    cout << endl
         << "��������" << ans << endl;
    return 0;
}