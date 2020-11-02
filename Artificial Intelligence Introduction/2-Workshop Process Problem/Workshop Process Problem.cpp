/*This cpp source file is written in UTF-8 encoding,
 *But compiling in GBK encoding is better.*/

#include <iostream>
#include <cstring>
#include<algorithm>

using namespace std;

int work, machine;//记录工作量、机器数量
int totalSteps = 0, minTime = 9999;//记录总步数、最短时间
int stepsForWorks[99];//对应每个工作需要几步来完成
int jobSteps[99];//工作已经完成的步数
int designated[99][99];//最终分配的结果
int machineWorkTime[99];//每个机器的工作时间

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
    if (time > minTime)//此时传入时间长于最短时间，没有搜索的必要
        return;
    if (step == totalSteps) {//当前最好状况对应的情况
        minTime = time;
        for (int i = 0; i < totalSteps; ++i)
            best[i] = current[i];
        return;
    }
    for (int i = 0; i < work; ++i) {
        int j = jobSteps[i];//获取这个工作已经完成的步数
        if (j >= stepsForWorks[i])//已完成的比需要的还多，不用再搜索了
            continue;
        int thisMachine = job[i][j].whichMachine;
        current[step].whichMachine = thisMachine;
        current[step].jobNum = i + 1;//标记执行当前工作的机器
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
    cout << "请输入工作数量：";
    cin >> work;
    cout << "请输入机器数量：";
    cin >> machine;

    //初始化所有数组变量
    memset(stepsForWorks, 0, sizeof(stepsForWorks));
    memset(machineWorkTime, 0, sizeof(machineWorkTime));
    memset(best, 0, sizeof(best));
    memset(designated, -1, sizeof(designated));

    //用户输入工作数量、机器数量、每一步对应的信息
    for (int i = 0; i < work; ++i) {
        cout << "第" << i + 1 << "项工作需要几步：";
        cin >> stepsForWorks[i];
        totalSteps += stepsForWorks[i];
        for (int j = 0; j < stepsForWorks[i]; ++j) {
            cout << "对第" << i + 1 << "项工作而言，第" << j + 1 << "步需要在哪台机器上运行？需要多少时间？";
            cin >> job[i][j].whichMachine >> job[i][j].time;
        }
    }
    cout << "正在计算，请稍后..." << endl;

    search(0, 0);//寻找最优解
    cout << "需要的最短时间：" << minTime << endl;//输出最短时间
    int gantt[99][99];//画出甘特图
    for (int i = 0; i < totalSteps; i++)
        for (int j = best[i].start; j < best[i].end; j++)
            gantt[best[i].whichMachine][j] = best[i].jobNum;//将甘特图的数组存入最优解
    for (int i = 0; i < machine; i++) {
        cout << "机器" << i + 1 << "：";
        for (int j = 0; j < minTime; j++)
            printf("%d%c", gantt[i][j], j == minTime - 1 ? '\n' : ' ');
    }
}