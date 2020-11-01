#include <iostream>
#include <cstring>
#include<algorithm>

using namespace std;

int work, machine;//��¼����������������
int totalSteps = 0, minTime = 9999;//��¼�ܲ��������ʱ��
int stepsForWorks[99];//��Ӧÿ��������Ҫ���������
int jobSteps[99];//�����Ѿ���ɵĲ���
int designated[99][99];//���շ���Ľ��
int machineWorkTime[99];//ÿ�������Ĺ���ʱ��

struct Job {
    int whichMachine;
    int time;
} job[99][99];
struct Recorder {
    int start;
    int end;
    int jobNum;
    int whichMachine;
} best[99], current[99];


void search(int step, int time) {
    if (time > minTime)//��ʱ����ʱ�䳤�����ʱ�䣬û�������ı�Ҫ
        return;
    if (step == totalSteps) {//��ǰ���״����Ӧ�����
        minTime = time;
        for (int i = 0; i < totalSteps; ++i)
            best[i] = current[i];
        return;
    }
    for (int i = 0; i < work; ++i) {
        int j = jobSteps[i];//��ȡ��������Ѿ���ɵĲ���
        if (j >= stepsForWorks[i])//����ɵı���Ҫ�Ļ��࣬������������
            continue;
        int thisMachine = job[i][j].whichMachine;
        current[step].whichMachine = thisMachine;
        current[step].jobNum = i + 1;//
        int temp = machineWorkTime[thisMachine];
        int beginTime = max(designated[i][j - 1], machineWorkTime[thisMachine]);
        current[step].start = beginTime;
        machineWorkTime[thisMachine] = beginTime + job[i][j].time;
        designated[i][j] = current[step].end = machineWorkTime[thisMachine];
        jobSteps[i]++;
        search(step + 1, max(time, machineWorkTime[thisMachine]));
        jobSteps[i]--;
        machineWorkTime[thisMachine] = temp;
    }
}


int main() {
    cout << "�����빤��������";
    cin >> work;
    cout << "���������������";
    cin >> machine;

    //��ʼ�������������
    memset(stepsForWorks, 0, sizeof(stepsForWorks));
    memset(machineWorkTime, 0, sizeof(machineWorkTime));
    memset(best, 0, sizeof(best));
    memset(designated, -1, sizeof(designated));

    //�û����빤������������������ÿһ����Ӧ����Ϣ
    for (int i = 0; i < work; ++i) {
        cout << "��" << i + 1 << "�����Ҫ������";
        cin >> stepsForWorks[i];
        totalSteps += stepsForWorks[i];
        for (int j = 0; j < stepsForWorks[i]; ++j) {
            cout << "�Ե�" << i + 1 << "������ԣ���" << j + 1 << "����Ҫ����̨���������У���Ҫ����ʱ�䣿";
            cin >> job[i][j].whichMachine >> job[i][j].time;
        }
    }
    cout << "���ڼ��㣬���Ժ�..." << endl;

    search(0, 0);//Ѱ�����Ž�
    cout << "��Ҫ�����ʱ�䣺" << minTime << endl;//������ʱ��
    int gantt[99][99];//��������ͼ
    for (int i = 0; i < totalSteps; i++)
        for (int j = best[i].start; j < best[i].end; j++)
            gantt[best[i].whichMachine][j] = best[i].jobNum;//������ͼ������������Ž�
    for (int i = 0; i < machine; i++) {
        cout << "����" << i + 1 << "��";
        for (int j = 0; j < minTime; j++)
            printf("%d%c", gantt[i][j], j == minTime - 1 ? '\n' : ' ');
    }
}