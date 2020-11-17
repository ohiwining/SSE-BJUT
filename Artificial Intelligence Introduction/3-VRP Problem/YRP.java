import java.util.*;

public class YRP {
    private final String[] clientName = {"Home","p1","p2","p3","p4","p5","p6","p7",
            "p8","p9", "p10","p11","p12","p13","p14","p15","p16","p17","p18","p19",
            "p20", "p21","p22","p23","p24","p25","p26","p27","p28","p29","p30"};
    private final int clientNum = clientName.length;
    private final int popSize = 50;
    private int maxGen = 20000;
    private final int[][] distance = new int[clientNum][clientNum];

    private class genotype {
        int[] client = new int[clientNum];
        long fitness;
        double selectP;
        double exceptP;
        int isSelected;
    }

    private final genotype[] clients = new genotype[popSize];

    public YRP(int carNum,int []carLoad,double [] clientNeeds, double [] loc) {
        for (int i = 0; i < popSize; i++) {
            clients[i] = new genotype();
            int[] num = new int[clientNum];
            for (int j = 0; j < clientNum; j++)
                num[j] = j;
            int temp = clientNum;
            for (int j = 0; j < clientNum; j++) {
                int r=0;
                clients[i].client[j] = num[r];
                num[r] = num[temp - 1];
                temp--;
            }
            clients[i].fitness = 0;
            clients[i].selectP = 0;
            clients[i].exceptP = 0;
            clients[i].isSelected = 0;
        }
        initDistance(loc);
    }

    public void CalAll() {
        for (int i = 0; i < popSize; i++) {
            clients[i].fitness = 0;
            clients[i].selectP = 0;
            clients[i].exceptP = 0;
            clients[i].isSelected = 0;
        }
        CalFitness();
        CalSelectP();
        CalexceptP();
        CalIsSelected();
    }

    public void pad() {
        int best = 0;
        int bad = 0;
        do {
            while (clients[best].isSelected <= 1 && best < popSize - 1)
                best++;
            while (clients[bad].isSelected != 0 && bad < popSize - 1)
                bad++;
            if (clientNum >= 0) System.arraycopy(clients[best].client, 0, clients[bad].client, 0, clientNum);
            clients[best].isSelected--;
            clients[bad].isSelected++;
            bad++;
        } while (best != popSize && bad != popSize);
    }

    public void crossover() {
        int x;
        int y;
        double pxover = 0.8;
        int pop = (int) (popSize * pxover / 2);
        while (pop > 0) {
            x = (int) (Math.random() * popSize);
            y = (int) (Math.random() * popSize);
            executeCrossover(x, y);
            pop--;
        }
    }

    private void executeCrossover(int x, int y) {
        int dimension = 0;
        for (int i = 0; i < clientNum; i++)
            if (clients[x].client[i] != clients[y].client[i]) {
                dimension++;
            }
        int diffItem = 0;
        double[] diff = new double[dimension];
        for (int i = 0; i < clientNum; i++) {
            if (clients[x].client[i] != clients[y].client[i]) {
                diff[diffItem] = clients[x].client[i];
                clients[x].client[i] = -1;
                clients[y].client[i] = -1;
                diffItem++;
            }
        }
        Arrays.sort(diff);
        gpCalculate(x, dimension, diff);
        int tempDimension = dimension;
        int tempi = 0;
        while (tempDimension > 0) {
            if (clients[x].client[tempi] == -1) {
                clients[x].client[tempi] = (int) diff[dimension - tempDimension];
                tempDimension--;
            }
            tempi++;
        }
        Arrays.sort(diff);
        gpCalculate(y, dimension, diff);
        tempDimension = dimension;
        tempi = 0;
        while (tempDimension > 0) {
            if (clients[y].client[tempi] == -1) {
                clients[y].client[tempi] = (int) diff[dimension - tempDimension];
                tempDimension--;
            }
            tempi++;
        }
    }

    private void gpCalculate(int x, int dimension, double[] diff) {
        double[] temp;
        temp = gp(x, dimension);
        for (int k = 0; k < dimension; k++)
            for (int j = 0; j < dimension; j++)
                if (temp[j] == k) {
                    double item = temp[k];
                    temp[k] = temp[j];
                    temp[j] = item;
                    item = diff[k];
                    diff[k] = diff[j];
                    diff[j] = item;
                }
    }

    private double[] gp(int individual, int dimension) {
        double[] temp = new double[dimension];
        double[] temp1 = new double[dimension];
        int p = 2 * dimension + 3;
        while (!isSushu(p))
            p++;
        for (int i = 0; i < dimension; i++) {
            temp[i] = 2 * Math.cos(2 * Math.PI * (i + 1) / p) * (individual + 1);
            temp[i] = temp[i] - (int) temp[i];
            if (temp[i] < 0)
                temp[i] = 1 + temp[i];
        }
        if (dimension >= 0) System.arraycopy(temp, 0, temp1, 0, dimension);
        Arrays.sort(temp1);
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++)
                if (temp[j] == temp1[i])
                    temp[j] = i;
        return temp;
    }

    public void mutate() {
        double random;
        int temp;
        int temp1;
        int temp2;
        for (int i = 0; i < popSize; i++) {
            random = Math.random();
            double pmultation = 0.05;
            if (random <= pmultation) {
                temp1 = (int) (Math.random() * (clientNum));
                temp2 = (int) (Math.random() * (clientNum));
                temp = clients[i].client[temp1];
                clients[i].client[temp1] = clients[i].client[temp2];
                clients[i].client[temp2] = temp;

            }
        }
    }

    private void initDistance(double [] locations) {
        for (int i=0;i<31;i++){
            for (int j=0;j<31;j++){
                if(i==j)
                    distance[i][j]=0;
                else{
                    distance[i][j]= (int) (10000*Math.sqrt(Math.pow(locations[2*i]-locations[2*j],2)+Math.pow(locations[2*i+1]-locations[2*j+1],2)));
                }
            }
        }
    }

    private void CalFitness() {
        for (int i = 0; i < popSize; i++) {
            for (int j = 0; j < clientNum - 1; j++)
                clients[i].fitness += distance[clients[i].client[j]][clients[i].client[j + 1]];
            clients[i].fitness += distance[clients[i].client[0]][clients[i].client[clientNum - 1]];
        }
    }

    private void CalSelectP() {
        long sum = 0;
        for (int i = 0; i < popSize; i++)
            sum += clients[i].fitness;
        for (int i = 0; i < popSize; i++)
            clients[i].selectP = (double) clients[i].fitness / sum;

    }

    private void CalexceptP() {
        for (int i = 0; i < popSize; i++)
            clients[i].exceptP = clients[i].selectP * popSize;
    }

    private void CalIsSelected() {
        int needSelecte = popSize;
        for (int i = 0; i < popSize; i++)
            if (clients[i].exceptP < 1) {
                clients[i].isSelected++;
                needSelecte--;
            }
        double[] temp = new double[popSize];
        for (int i = 0; i < popSize; i++) {
            temp[i] = clients[i].exceptP * 10;
        }
        int j = 0;
        while (needSelecte != 0) {
            for (int i = 0; i < popSize; i++) {
                if ((int) temp[i] == j) {
                    clients[i].isSelected++;
                    needSelecte--;
                    if (needSelecte == 0)
                        break;
                }
            }
            j++;
        }
    }

    private boolean isSushu(int x) {
        if (x < 2) return false;
        for (int i = 2; i <= x / 2; i++)
            if (x % i == 0 && x != 2) return false;
        return true;
    }

    private boolean isSame(long[] x) {
        for (int i = 0; i < x.length - 1; i++)
            if (x[i] != x[i + 1])
                return false;
        return true;
    }

    private void printBestRoute() {
        CalAll();
        long temp = clients[0].fitness;
        int index = 0;
        for (int i = 1; i < popSize; i++) {
            if (clients[i].fitness < temp) {
                temp = clients[i].fitness;
                index = i;
            }
        }
        System.out.println("\n最佳路径的序列：");
        for (int j = 0; j < clientNum; j++) {
            String[] clientEnd = {clientName[clients[index].client[j]]};
            for (String s : clientEnd) {
                System.out.print(s + " ");
            }
        }
    }
    public void run() {
        int range = 2000;
        long[] result = new long[range];
        for (int i = 0; i < range; i++)
            result[i] = i;
        int index = 0;
        int num = 1;
        while (maxGen > 0) {
            CalAll();
            pad();
            crossover();
            mutate();
            maxGen--;
            long temp = clients[0].fitness;
            for (int i = 1; i < popSize; i++)
                if (clients[i].fitness < temp) {
                    temp = clients[i].fitness;
                }
            System.out.println("第"+ num +"代最优解: " + temp);
            result[index] = temp;
            if (isSame(result))
                break;
            index++;
            if (index == range)
                index = 0;
            num++;
        }
        printBestRoute();
    }

    public static void main(String[] args) {
        int carNum=5;
        int clientNum=30;
        int []carLoad={4,4,4,4,4};
        double[]clientNeeds={0.1904,0.3689,0.4607,0.9816,0.1564,0.8555,0.6448,0.3763,0.1909,
                0.4283,0.4820,0.1206,0.5895,0.2262,0.3846,0.5830,0.2518,0.2904,0.6171,0.2653,
                0.8244,0.9827,0.7302,0.3439,0.5841,0.1078,0.9063,0.8797,0.8178,0.2607};
        double [] locations={
                0.0424,0.0714,
                0.5216,0.0967,
                0.8181,0.8175,
                0.7224,0.1499,
                0.6596,0.5186,
                0.9730,0.6490,
                0.8003,0.4538,
                0.4324,0.8253,
                0.0835,0.1332,
                0.1734,0.3909,
                0.8314,0.8034,
                0.0605,0.3993,
                0.5269,0.4168,
                0.6569,0.6280,
                0.2920,0.4317,
                0.0155,0.9841,
                0.1672,0.1062,
                0.3724,0.1981,
                0.4897,0.3395,
                0.9516,0.9203,
                0.0527,0.7379,
                0.2691,0.4228,
                0.5479,0.9427,
                0.4177,0.9831,
                0.3015,0.7011,
                0.6663,0.5391,
                0.6981,0.6665,
                0.1781,0.1280,
                0.9991,0.1711,
                0.0326,0.5612,
                0.8819,0.6692};
        YRP tsp = new YRP(carNum,carLoad,clientNeeds,locations);
        tsp.run();
    }
}
