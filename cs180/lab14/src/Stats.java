import java.io.*;
import java.net.FileNameMap;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * Created by hmontoya on 12/3/15.
 */
public class Stats {

    static HashMap<String, Integer> wins(BufferedReader br)throws IOException{
        HashMap<String, Integer> map = new HashMap<String, Integer>();
        String line;

        while ((line = br.readLine()) != null) {
            String[] t = line.split(" ");
//
            if (t[0].equals("0")) {
                for (int i = 1; i < 6; i ++) {
                    Integer count = map.get(t[i]);
                    if (count == null) {
                        map.put(t[i], 1);
                    } else {
                        map.put(t[i], map.get(t[i]) + 1);
                    }
                }

            } else {
                for (int i = 7; i < 12; i ++) {
//                    System.out.println(t.length);
//                    System.out.println(i);
                    Integer count = map.get(t[i]);
                    if (count == null) {
                        map.put(t[i], 1);
                    } else {
                        map.put(t[i], map.get(t[i]) + 1);
                    }
                }

            }

        }
        return map;
    }

    static String winner(HashMap<String, Integer> map) {
        int high = 0;
        String winner = "";
        Iterator it = map.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry pair = (Map.Entry)it.next();
            int score = Integer.parseInt(pair.getValue().toString());
            if (score > high) {
                winner = pair.getKey().toString();
                high = score;
//                System.out.println(winner);
//                System.out.println(score);
            }
        }
        return winner;
    }


    public static void main(String[] args) {
        Stats a = new Stats();

        try {
            File file = new File("results");
            BufferedReader r = new BufferedReader(new FileReader(file));
            try {
                System.out.println(a.winner(a.wins(r)));
            } catch (IOException f) {

            }
        } catch (FileNotFoundException e) {
        }

    }
}
