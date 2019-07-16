import edu.princeton.cs.algs4.BinarySearchST;
import edu.princeton.cs.algs4.StdOut;
import java.util.ArrayList;

public class FilterA {
    BinarySearchST<Integer,Integer> st;
    int n;
    ArrayList<Integer> delList;

    public FilterA(int n){
        this.n=n;
        this.st = new BinarySearchST<>();
        this.delList = new ArrayList<Integer>();

    }
    public void printSort(){
        for(int i = 0; i!=st.size();i++){
            int k = st.select(i);
            StdOut.print(k);
            StdOut.println(" "+st.get(k));
        }
    }
    public void check(){
        for(int i=0;i!=st.size()-1;i++){
            int k = st.select(i);
           in:{ for(int j = i+1; j!=st.size();j++){
                int com = st.select(j);
                if(st.get(k)<st.get(com)){
                    Integer a = new Integer(k);
                    delList.add(a);
                    break in;
                }
            }}
        }
    }
    public void cull(){
        for(int i=0;i!=delList.size();i++){
            Integer d = delList.get(i);
            st.delete(d);
        }
    }


    public static void main (String[] args){
        int n = StdIn.readInt();
        FilterA f = new FilterA(n);
        while(StdIn.isEmpty()==false){
            int key = StdIn.readInt();
            int val = StdIn.readInt();
            f.st.put(key,val);
        }

    
        f.check();
//        StdOut.println("..............");
//        for(int i = 0; i!=f.delList.size();i++){
//            StdOut.println(f.delList.get(i));
//        }
//        StdOut.println("..............");
        f.cull();
        f.printSort();

    }

}