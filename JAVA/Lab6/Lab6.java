/*
 * ID: 18080128
 * Name: 孙晨伟
 * Title: 实验六
 * Date：2020-5-29
 */

import java.io.*;
import java.util.Scanner;

class Question1 {//文件的复制

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Please input source file directory:");
        String sourceFile = sc.nextLine();
        System.out.println("Please input target file directory:");//用户输入要复制的文件和目标文件的路径
        String targetFile = sc.nextLine();
        File source = new File(sourceFile);
        File target = new File(targetFile);//创建文件对象

        try {
            FileReader fr = new FileReader(source);//创建读取和写入对象
            FileWriter fw = new FileWriter(target);
            char[] c = new char[500];
            int length = fr.read(c);
            System.out.println("Read " + length + " chars");//告知用户读取字符数量
            fw.write(c);//开始复制
            fr.close();//关闭读取和写入对象
            fw.close();
        } catch (IOException ioe) {//文件未找到时报错
            System.out.println("File not found!");
        } catch (Exception e) {//其它类型报错
            System.out.println("Error!");
        } finally {//提示程序运行完成
            System.out.println("Completed.");
        }
    }
}

class Question2 {//计算总和和平均值

    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));//创建Buffer读取类，实例化时直接从系统输入
        try {
            System.out.println("How many numbers to input?");//输入数字的个数
            int num = Integer.parseInt(br.readLine());
            int sum = 0;
            for (int i = 0; i < num; i++) {//依次输入数据
                System.out.println("Please input " + i + " of " + num + " numbers:");
                sum += Integer.parseInt(br.readLine());//从系统读取数据
            }
            System.out.println("Sum: " + sum + "\nAverage: " + sum / 1.0 / num);//计算总和和平均值
        } catch (Exception e) {//任何类型的报错都会提示error
            System.out.println("Error!");
        }

    }
}

class Question3AND4 {//文件的加密和解密

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StringBuilder result = new StringBuilder();

        /*以下是加密部分*/
        System.out.println("Please input source file directory:");
        String sourceFile = sc.nextLine();
        System.out.println("Please input target file directory:");//用户输入源文件和加密文件的路径
        String targetFile = sc.nextLine();
        File source = new File(sourceFile);
        File target = new File(targetFile);
        char[] encoder = {'T', 'O', 'I', 'A', 'N', 'D', 'E', 'G', 'H', 'Z', 'B', 'K', 'F', 'J', 'M', 'C', 'L', 'P', 'Y', 'V', 'X', 'Q', 'R', 'W', 'U', 'S'};//加密方式
        char[] contentArray = new char[500];

        try {
            FileReader fr = new FileReader(source);
            FileWriter fw = new FileWriter(target);
            fr.read(contentArray);//读取源文件
            fr.close();//读取完毕就可以关闭
            for (char i : contentArray) {
                int flag = 0;
                if (i == '\0')//此时已经读取完毕，可以结束循环
                    break;
                else if (i == ' ') {//空格不属于加密方法里的，需要单另进行判断
                    result.append(' ');
                    continue;
                }
                for (char letter = 'A'; letter <= 'Z'; letter++) {//当输入字符为A到Z时进行加密
                    if (letter == i)
                        break;
                    flag++;
                }
                result.append(encoder[flag]);//添加到结果中
            }
            fw.write(result.toString().toCharArray());//将结果转换为char数组并写入文件
            fw.close();//关闭文件写入对象
        } catch (Exception e) {//任何类型的错误都会报错
            System.out.println("Error!");
        } finally {
            System.out.println("Encoding completed.");//提示用户加密动作已完成
        }


        /*以下是解密部分*/
        System.out.println("Please input encoded file directory:");//用户输入要解密文件和目标文件的路径
        String encodedFile = sc.nextLine();
        System.out.println("Please input decoded file directory:");
        String decodedFile = sc.nextLine();
        File encode = new File(encodedFile);
        File decode = new File(decodedFile);
        StringBuilder newSb = new StringBuilder();

        try {
            FileReader newFr = new FileReader(encode);//创建文件读写对象
            FileWriter newFw = new FileWriter(decode);
            char[] toDecode = new char[500];
            newFr.read(toDecode);//开始读取
            newFr.close();//读取完毕，关闭读取对象
            for (char i : toDecode) {
                if (i == '\0')
                    break;
                else if (i == ' ') {
                    newSb.append(' ');//和加密方式相同
                    continue;
                }
                int flag = 0;
                for (char c : encoder) {
                    if (i == c)
                        break;
                    flag++;
                }
                int newflag = 0;
                char letter;
                for (letter = 'A'; letter <= 'Z'; letter++) {//进行解密
                    if (newflag == flag)
                        break;
                    newflag++;
                }
                newSb.append(letter);
            }
            newFw.write(newSb.toString().toCharArray());//写入文件
            newFw.close();//关闭文件写入对象
        } catch (Exception e) {//任何类型的错误都会报错
            System.out.println("Error!");
        } finally {
            System.out.println("Decoding completed.");//提示用户解密动作已完成
        }
    }
}