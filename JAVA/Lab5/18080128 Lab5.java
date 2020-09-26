/*
 * ID:18080128
 * Name:孙晨伟
 * Title：实验五
 * Date：2020-5-21
 */

import java.util.*;

class Question1 {
    static class InputException extends Exception {
    }//自定义输入异常类

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入数字：");
        int choice = sc.nextInt();
        try {
            switch (choice) {//switch来进行不同数字的判断逻辑
                case 1:
                    System.out.println("《C语言程序设计》");
                    break;
                case 2:
                    System.out.println("《Java程序设计》");
                    break;
                case 3:
                    System.out.println("《Android应用》");
                    break;
                default:
                    throw new InputException();//当输入数字超出范围时抛出输入一场错误
            }
        } catch (InputException e) {
            System.out.println("请输入1~3！");//提醒用户输入有误
        }
    }
}

class Question2 {
    static class IDException extends Exception {
    }//定义id输入错误异常类

    static class PasswdException extends Exception {
    }//定义密码输入错误异常类

    static class LockedException extends Exception {
    }//定义用户权限被锁定异常类

    static class User {//定义用户类
        public int id;
        public int passwd;
        public boolean locked;

        User(int id, int passwd, boolean locked) {
            this.id = id;
            this.passwd = passwd;
            this.locked = locked;
        }

        void verifyPasswd() throws PasswdException {
            Scanner sc = new Scanner(System.in);
            System.out.println("请输入密码");
            if (sc.nextInt() != this.passwd)
                throw new PasswdException();
        }//判断密码输入

        void verifyLocked() throws LockedException {
            if (this.locked)
                throw new LockedException();
        }//判断用户是否拥有操作权限
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        User[] userList = new User[3];//创建用户数组，模拟数据库
        userList[0] = new User(13579, 13579, true);//录入三个用户
        userList[1] = new User(24680, 24680, false);
        userList[2] = new User(12345, 12345, false);
        try {
            System.out.println("请输入账号：");//用户输入账号
            int id = sc.nextInt();
            int flag;
            for (flag = 0; flag < userList.length; flag++) {//遍历数据库搜索id
                if (userList[flag].id == id)
                    break;
            }
            if (flag == userList.length)//true表示所输入id不在数据库中
                throw new IDException();
            userList[flag].verifyPasswd();//判断密码是否正确
            userList[flag].verifyLocked();//判断是否有操作权限
            System.out.println("登陆成功！");
        } catch (IDException e) {
            System.out.println("该ID不存在！");//所输入id不在数据库中
        } catch (PasswdException e) {
            System.out.println("密码错误！");//密码输入错误
        } catch (LockedException e) {
            System.out.println("该用户没有操作权限！");//提醒权限不足
        } finally {
            System.out.println("程序执行完毕。");
        }

    }
}

class Question3 {
    static class IllegalSignException extends Exception {
    }//定义运算符输入错误异常类

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            System.out.println("请输入两个整数：");
            int op1 = sc.nextInt();//直接输入数字，输入错误时系统会自动抛出异常
            int op2 = sc.nextInt();
            System.out.println("请输入运算符：");
            String op = sc.next();
            switch (op) {
                case "+":
                    System.out.println("结果为：" + (op1 + op2));
                    break;
                case "-":
                    System.out.println("结果为：" + (op1 - op2));
                    break;
                case "*":
                    System.out.println("结果为：" + (op1 * op2));
                    break;
                case "/":
                    if (op2 == 0)//此时除数为0，抛出异常
                        throw new ArithmeticException();
                    System.out.println("结果为：" + (op1 / op2));
                    break;
                default://此时输入运算符不在规定运算符之内
                    throw new IllegalSignException();
            }
        } catch (ArithmeticException e) {//除数为0的状况
            System.out.println("除数不能为0");
        } catch (InputMismatchException e) {//数字输入不正确的情况
            System.out.println("数字输入有误！");
        } catch (IllegalSignException e) {//运算符输入错误的情况
            System.out.println("运算符输入有误！");
        } finally {
            System.out.println("程序执行完毕。");
        }
    }
}