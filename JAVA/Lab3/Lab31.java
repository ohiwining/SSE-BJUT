class Lab31
{
    public static void main(String args[])
    {
        String s1=new String("you are a student"),
                s2=new String("how are you");
        if(s1.equals(s2))//使用equals方法判断s1与s2是否相同
        {System.out.println("s1与s2相同");}
	else{System.out.println("s1与s2不同");}

        String s3=new String("22030219851022024");
        if(s3.startsWith("220302")) //判断s3的前缀是否是“220302”
        {System.out.println("吉林省的身份证号码");}

        String s4=new String("你"),
                s5=new String("我");
        if(s4.compareTo(s5)>0) //比较s4与s5的大小
        {System.out.println("按字典序\'你\'大于\'我\'");}
	else 	{System.out.println("按字典序\'你\'小于\'我\'");}

        int position=0;
        String path="C:\\java\\jsp\\A.java";
        position=path.lastIndexOf("\\");//获取path中最后出现目录分隔符号的位置
        System.out.println("C:\\java\\jsp\\A.java中最后出现\\的位置："+position);
        String fileName=path.substring(position+1);//获取path中文件名“A.java”的子字符串
        System.out.println("C:\\java\\jsp\\A.java中含有的文件名："+fileName);

        String s6=new String("100"),
                s7=new String("123.678");
        int n1=Integer.parseInt(s6);//将s6转换为int型数据
        double n2=Double.parseDouble(s7);//将s7转换为double型数据
        double m=n1+n2;
        System.out.println(m);
        String s8=String.valueOf(m);//String类调用valueOf(double n)方法将m转换为字符串对象
        position=s8.indexOf(".");
        String temp=s8.substring(position+1);
        System.out.println("数字"+m+"有"+temp.length()+"位小数");
        String s9=new String("ABCDEF");
        char a[]=s9.toCharArray();//将s9存放到数组a中
        for(int i=a.length-1;i>=0;i--)
        {System.out.print(" "+a[i]);}
    }}