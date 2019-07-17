import java.io.File;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class SwordFinder {

    public void asort(int[][] ar){
        Arrays.sort(ar, new Comparator<int[]>() {

            public int compare(int[] int1, int[] int2) {
                Integer a = int1[1];
                Integer b = int2[1];
                return a.compareTo(b);
            }
        });
    }

    public int operation(String fname){
        Scanner scanner;
        try{
            scanner = new Scanner(new File(fname));
            int N = scanner.nextInt();
            //System.out.println(N);
            int A = scanner.nextInt();
            //System.out.println(A);
            int B = scanner.nextInt();
            //System.out.println(B);

            int [][] list = new int[N][2];

            for(int i=0;i!=N;i++){
                String has = scanner.next();
                //fill if has or hasnt sword
                if(has.equals("S")){
                    list[i][0]=1;
                } else {
                    list[i][0]=0;
                }
                //System.out.println(has);
                //fill friend
                int friend = scanner.nextInt();
                list[i][1]=friend;

                //System.out.println(friend);
            }
            int numEnem = B - A + 1;
            //if theres only one friend, then all enemies have the same S or NS as it. Return that.
            if (list.length==1){
                if(list[0][0]==1){
                    return numEnem;
                } else {
                    return 0;
                }
            }
            asort(list);

            //all input is now sorted and in an array where [x][0] holds 1 for S, 0 for NS; [x][1] holds the playtime for friend x 0-(N-1)


            int enemies[] = new int[numEnem];
            // enemies[0] is A, enemies [numenem-1] is B

            //start op for N friends
            int count = 0;
            for(int i=0; i!=N-1; i++) {
                //for the first one, poblate everything before and then go after
                if(i==0){
                    int position = list[i][1] - A;
                    if(list[i][0]==1){
                        enemies[position]=1;

                        for(int j=position; j!=-1; j--){
                            enemies[j]=1;

                        }
                    }

                    //for the last one check everything after

                }  //all else
                    double currentPos = list[i][1] - A;
                    double nextPos = list[i+1][1] - A;
                System.out.println("CUR: " + currentPos);
                System.out.println("NXT: " + nextPos);
                    double mid = (currentPos + nextPos)/2;
                System.out.println(mid);

                    if(mid!=Math.floor(mid)){ //when mid isnt integer,so 4 - - - 7
                        //current UP to mid point
                        System.out.println("CASE 1");
                        if(list[i][0]==1){
                            int m = (int) Math.floor(mid);
                            for(int j = (int)currentPos; j<=m; j++){
                                enemies[j]=1;

                            }

                        }
                        //next DOWN to midpoint
                        if(list[i+1][0]==1){
                            int m = (int) Math.ceil(mid);
                            for(int j = (int)nextPos; j>=m; j--){
                                enemies[j]=1;

                            }

                        }

                    } else {
                        System.out.println("CASE 2");
                        System.out.println(mid);
                        if(list[i][0]==1){
                            int m = (int) mid;
                            for(int j = (int)currentPos; j<=m; j++){
                                enemies[j]=1;

                            }

                        }
                        if(list[i+1][0]==1){
                            int m = (int) mid;
                            for(int j = (int)nextPos; j>=m; j--){
                                enemies[j]=1;

                            }

                        }

                    }


                int position = list[i][1] - A;
                if(list[i][0]==0) {
                    enemies[position] = 0;
                }


            }

            int position = list[N-1][1]-A;
            if(list[N-1][0]==1){
                enemies[position]=1;

                for(int j=position; j!=enemies.length; j++){
                    enemies[j]=1;

                }
            }



            for (int i=0;i!=numEnem;i++){
               // System.out.println("["+i+"]"+" " + enemies[i]);
                if (enemies[i]==1){
                    count++;
                }
            }
            return count;
        } catch(Exception e){
            System.out.println("Error.");
            return -1;
        }
    }

    public static void main (String[] args) {
        String fname = args[0];
        SwordFinder sf = new SwordFinder();
        int count = sf.operation(fname);
        System.out.println(count);

    }


}
