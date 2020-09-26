import java.util.Scanner;
public class Student_Management {
    private static int how_many;
    public static class Student{
        int ID;
        String name;
        int math;
        int english;
        int sum;
        float average;
        private void set_stu_inf(int a,String b,int c,int d)
        {
            ID=a;
            name=b;
            math=c;
            english=d;
            sum=math+english;
            average=(float)sum/2;
        }
        private void printout(){
            System.out.print("ID:"+ID+"\n");
            System.out.print("Name:"+name+"\n");
            System.out.print("Math:"+math+"\n");
            System.out.print("English:"+english+"\n");
            System.out.print("Sum score:"+sum+"\n");
            System.out.print("Aver score"+average+"\n");
        }
    }
    private static Student recruitment(){
        Student temp=new Student();
        int input_id,input_math,input_english;
        String input_name;
        Scanner sc=new Scanner(System.in);
        System.out.print("Input ID:\n");
        input_id = sc.nextInt();
        System.out.print("Input name:\n");
        String a=sc.nextLine();
        input_name = sc.nextLine();
        System.out.print("Input math score:\n");
        input_math = sc.nextInt();
        System.out.print("Input english score:\n");
        input_english = sc.nextInt();
        temp.set_stu_inf(input_id,input_name,input_math,input_english);
        how_many++;
        return temp;
    }
    private static void calculate(Student [] group){
        int all_score=0;
        float all_aver;
        for(int a=0;a<how_many;a++)
        {
            all_score+=group[a].sum;
        }
        all_aver=(float)all_score/(float)how_many;
        System.out.print("Average score:"+all_aver);
    }
    private static void menu(){
        System.out.print("1-Add a student\n");
        System.out.print("2-List all student\n");
        System.out.print("3-Calculate average score\n");
        System.out.print("4-Exit\n");
        System.out.print("Please input your choice:");
    }
    public static void main(String [] argc){
        int choice;
        Student[] group;
        group=new Student[30];
        Scanner sc=new Scanner(System.in);
        while(true) {
            menu();
            choice = sc.nextInt();
            switch (choice) {
                case 1:group[how_many]=recruitment();
                    break;
                case 2:for(int loop=0;loop<how_many;loop++) {
                    group[loop].printout();
                }
                    break;
                case 3:calculate(group);
                    break;
                case 4:
                    return;
                default:
                    System.out.print("Wrong input!\n");
            }
        }
    }
}
