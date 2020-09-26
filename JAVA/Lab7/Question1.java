/*
 * ID:18080128
 * Name:孙晨伟
 * Title：实验七-第一题
 * Date：2020-6-4
 */

class Process {//一套流程的类，存放了一整套工作流程
    boolean canDrive;
    boolean canUnload;//标识是否可以卸货或是拉货

    Process() {
        canDrive = false;
        canUnload = false;//初始条件是既不能拉货也不能卸货
    }

    public synchronized void onTheRun(int id) {//流程开始进行
        switch (id) {
            case 1://此时是司机
                while (!canDrive)
                    try {
                        System.out.println("正在呼叫装运工...");
                        wait();//此时搬运工还没有搬货
                    } catch (InterruptedException ignored) {
                    }
                System.out.println("司机上车...成功！");
                break;
            case 2://此时是搬运工
                while (!canUnload)
                    try {
                        System.out.println("正在呼叫仓库管理员...");
                        wait();//此时仓库大门还没有打开
                    } catch (InterruptedException ignored) {
                    }
                System.out.println("正在搬运货物...成功！");
                canDrive = true;
                notifyAll();
                break;
            case 3://此时是仓库管理人员
                System.out.println("仓库大门已开启!");
                canUnload = true;
                notifyAll();//为了防止唤醒失败，故唤醒所有线程
                break;
        }
    }
}

class Driver extends Thread {//运货司机类
    Process process;

    Driver(Process pro) {
        process = pro;
    }

    public void run() {
        System.out.println("运货司机已到场。");
        process.onTheRun(1);
    }
}

class Loader extends Thread {//卸货工人类
    Process process;

    Loader(Process pro) {
        process = pro;
    }

    public void run() {
        System.out.println("装运工已到场。");
        process.onTheRun(2);
    }
}

class Manager extends Thread {//仓库管理人员类
    Process process;

    Manager(Process pro) {
        process = pro;
    }

    public void run() {
        System.out.println("仓库管理员已到场。");
        process.onTheRun(3);
    }
}


public class Question1 {
    public static void main(String[] args) {
        Process pro = new Process();//流程开始进行

        new Driver(pro).start();//初始化工人线程并传入共同使用的参数
        new Loader(pro).start();
        new Manager(pro).start();
    }
}