/*
 * Name: 孙晨伟
 * NO. 18080128
 * Date: 2020-5-7
 * Title：实验三-第三题
 */

//注：本程序为了可读性强尽可能将行数优化到了最小

import java.util.Scanner;

public class Lab33 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);


        //这部分用户将输入三组号码，输入的过程中就直接统计每个数字出现的频率
        String[] telNums = new String[3];//号码数组
        int[] number = new int[10];//频率数组
        System.out.println("请输入三组电话号码：");
        for (int i = 0; i < 3; i++) {
            telNums[i] = sc.next();
            char[] numbers = telNums[i].toCharArray();//将号码转为char数组便于统计
            for (char c : numbers) {
                number[Integer.parseInt(String.valueOf(c))]++;//直接通过查找下标来存储对应频数
            }
        }


        //这部分通过遍历频率数组来求出最高频率的数字
        System.out.println("每个数字出现的频率：");
        int highest = 0;//最高的频数
        int highIndex = 0;//最高的频数所对应的下标，即对应的数字
        for (int i = 0; i < 10; i++) {
            System.out.print(i + ":" + number[i] + ", ");
            if (number[i] > highest) {
                highest = number[i];
                highIndex = i;
            }
        }


        //这部分将最高频数字和8互换，采用了边互换边输出的方式
        System.out.println("\n将高频数字与8互换：");
        char charHighIndex = String.valueOf(highIndex).toCharArray()[0];
        //将频数最高的数字转为char型（因为直接转换会按ascii码来进行，故先转为string，再转为char数组，再取数组0号位）
        for (String i : telNums) {
            StringBuffer sb = new StringBuffer("");
            char[] numbers = i.toCharArray();
            for (char c : numbers) {
                if (c == charHighIndex)
                    sb.append('8');
                else if (c == '8')
                    sb.append(charHighIndex);//通过append来依次添加字符
                else
                    sb.append(c);
            }
            System.out.println(sb);//每转换完一组电话就输出，下次转换不用请求新的变量
        }
    }
}