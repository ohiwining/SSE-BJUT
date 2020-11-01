/* Name：孙晨伟
 * ID：18080128
 * Course：人工智能导论
 */
#include<iostream>
#include<vector>

using namespace std;

typedef struct aNode {
    int data[3][3];//存放当前节点的具体信息
    int toDist;//距离目标还有多少步
    int alreadyGone;//已经走过了多少步
    int index;//用作下标，便于统计
} Node;

Node initial, target;//初始状态和目标状态的节点

vector<Node> nodes;//存放所有已经扫描过的节点

void swap(int &a, int &b) {
    //用于交换两个数
    int temp = a;
    a = b;
    b = temp;
}

void print(Node node) {
    //输出一个节点的数据信息
    for (auto &i:node.data) {
        for (int j:i)
            if (j==0)
                cout<<"  ";//将0作为空格输出
            else
                cout << j << ' ';
        cout << endl;
    }
}

bool isEqual(int index, int aTarget[3][3]) {
    //判断nodes中下标为index的数据是否和目标数据相同
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (nodes[index].data[i][j] != aTarget[i][j])
                return false;
    return true;
}

void assign(Node &node, int index) {
    //取出一个扫描过节点并存入一个单独的节点中
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            node.data[i][j] = nodes[index].data[i][j];
}

int prefer() {
    //偏好节点，从已经扫描过的节点中取权重最小的一个
    //即已走过的步数+距离目标步数最小的节点
    int distance = 10000;
    int index;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i].toDist == 10000)
            continue;
        else if ((nodes[i].toDist + nodes[i].alreadyGone) < distance) {
            index = i;
            distance = nodes[i].toDist + nodes[i].alreadyGone;
        }
    }
    return index;
}

bool notSearchedYet(Node &node) {
    //将传入节点与已经扫描过的所有节点一一比较
    //看该节点是否已经存在
    for (int i = 0; i < nodes.size(); ++i) {
        if (isEqual(i, node.data))
            return false;
    }
    return true;
}

int howManyStepsLeft(Node &node, int data[3][3]) {
    //计算距离目标还有几步
    int steps = 0;
    bool flag = false;
    for (int a = 0; a < 3; ++a)
        for (int b = 0; b < 3; ++b)
            for (int c = 0; c < 3; ++c) {
                for (int d = 0; d < 3; ++d)
                    if (node.data[a][b] == data[c][d]) {
                        steps += abs(a - c) + abs(b - d);//通过计算横向距离和纵向距离来进行比较
                        flag = true;
                        break;
                    } else
                        flag = false;
                if (flag)
                    break;
            }
    return steps;
}

void up(int index, int x, int y) {
    //将可用数字向上移动，0将向下移动
    Node temp;
    assign(temp, index);
    int distance;
    if (x > 0) {
        swap(temp.data[x][y], temp.data[x - 1][y]);
        if (notSearchedYet(temp)) {
            //如果往这个方向走还没有扫描过，则将这种情况添加到已扫描节点中，下同
            distance = howManyStepsLeft(temp, target.data);
            temp.index = index;
            temp.toDist = distance;
            temp.alreadyGone = nodes[index].alreadyGone + 1;
            nodes.push_back(temp);
        }
    }
}

void down(int index, int x, int y) {
    //将可用数字向下移动，0将向上移动
    Node temp;
    assign(temp, index);
    int distance;
    if (x < 2) {
        swap(temp.data[x][y], temp.data[x + 1][y]);
        if (notSearchedYet(temp)) {
            distance = howManyStepsLeft(temp, target.data);
            temp.index = index;
            temp.toDist = distance;
            temp.alreadyGone = nodes[index].alreadyGone + 1;
            nodes.push_back(temp);
        }
    }
}

void left(int index, int x, int y) {
    // 将可用数字向左移动，0将向右移动
    Node temp;
    assign(temp, index);
    int distance;
    if (y > 0) {
        swap(temp.data[x][y], temp.data[x][y - 1]);
        if (notSearchedYet(temp)) {
            distance = howManyStepsLeft(temp, target.data);
            temp.index = index;
            temp.toDist = distance;
            temp.alreadyGone = nodes[index].alreadyGone + 1;
            nodes.push_back(temp);
        }
    }
}

void right(int index, int x, int y) {
    //将可用数字向右移动，0将向左移动
    Node temp;
    assign(temp, index);
    int distance;
    if (y < 2) {
        swap(temp.data[x][y], temp.data[x][y + 1]);
        if (notSearchedYet(temp)) {
            distance = howManyStepsLeft(temp, target.data);
            temp.index = index;
            temp.toDist = distance;
            temp.alreadyGone = nodes[index].alreadyGone + 1;
            nodes.push_back(temp);
        }
    }
}

void goToNext(int index) {
    //对当前状况下一步的所有可能逐一分析并决定到底要走哪一步
    int x, y;
    bool flag;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (nodes[index].data[i][j] == 0) {
                x = i;
                y = j;
                flag = true;
                break;
            } else
                flag = false;
        }
        if (flag)
            break;
    }

    up(index, x, y);//向上走的情况
    down(index, x, y);//向下走的情况
    left(index, x, y);//向左走的情况
    right(index, x, y);//向右走的情况
    nodes[index].toDist = 10000;
}

void printSteps(int index, vector<Node> &nodes2) {
    //调用这个函数的时候已经找到最佳路线
    //此时只需要把路线输出即可
    nodes2.push_back(nodes[index]);
    index = nodes[index].index;
    while (index != 0) {
        nodes2.push_back(nodes[index]);
        index = nodes[index].index;
    }
    for (int i = int(nodes2.size() - 1); i >= 0; --i) {
        cout << "Step " << nodes2.size() - i << " :" << endl;
        print(nodes2[i]);
    }
}

int main() {
    int init[3][3] = {8, 0, 5, 2, 1, 4, 6, 7, 3};//初始状态
    int tar[3][3] = {1, 2, 3, 8, 0, 4, 7, 6, 5};//理想目标
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            initial.data[i][j] = init[i][j];//将初始和目标存入两个Node结构体中
            target.data[i][j] = tar[i][j];
        }
    }

    nodes.push_back(initial);//将初始状态存入已扫描过的节点群中
    while (true) {
        int index = prefer();//取得当前状态下最佳节点的下标
        if (isEqual(index, target.data)) {//此时已到达目标
            vector<Node> nodes2;//用来存放最短路径
            cout << "Start: " << endl;
            print(initial);//首先输出初始状态
            printSteps(index, nodes2);//输出最短路径
            cout << "Done!" << endl;
            break;
        } else {//此时还未到达目标
            goToNext(index);//需要进行下一步处理
        }
    }
    system("pause");
}
