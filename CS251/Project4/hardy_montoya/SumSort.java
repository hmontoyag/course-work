import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.ToIntFunction;
import java.util.function.ToLongFunction;

import edu.princeton.cs.algs4.Quick;
public class SumSort implements Comparator<Comparable[]>{
	Integer list[];
	Integer sorted[];
	Integer s1[][];
	Integer sums[][];
	int n;
	Integer matches[][];
	Integer sortedMatches[][];
	//Integer ogs[][];
	public SumSort(int n){
		list = new Integer[n];
		
	
		this.n = n;
	
	}
	
	public void Sort(Integer[][] arr)
	{   
	    
	    Arrays.sort(arr, new Comparator<Integer[]>()
	    {
	        public int compare(Integer[] int1, Integer[] int2)
	        {
	            Integer numOfKeys1 = int1[0];
	            Integer numOfKeys2 = int2[0];
	            if(numOfKeys1.equals(numOfKeys2)){
	            	numOfKeys1 = int1[1];
	            	numOfKeys2 = int2[1];
	            }
	            return numOfKeys1.compareTo(numOfKeys2);
	        }
	    });
   
	}
	
	public void doSums(){
		int c = 0;
		sums = new Integer[n*(n-1)/2][3];
		for(int i=0;i!=n-1;i++){
			for(int j=i+1;j!=n;j++){				
				sums[c][0] = list[i]+list[j];
				sums[c][1] = i;
				sums[c][2] = j;
				c++;
			}
		}
		//ogs = sums.clone();
	//	StdOut.println(c);
	//	StdOut.println(sums.length);
//		sums = new Integer[c][3];
//		for(int i =0; i!=sums.length;i++){
//			sums[i][0]=s1[i][0];
//			sums[i][1]=s1[i][1];
//			sums[i][2]=s1[i][2];
//		}
//		for(int i=0;i!=sums.length;i++){
//			for(int j=0;j!=sums[0].length;j++){
//				StdOut.print("[" + sums[i][j] + "] ");
//			}
//			StdOut.println();
//		}
//		
	}

	
	public void eval(){
		matches = new Integer[n*(n-1)/2][4];
		int c = 0;
		for(int i = 0; i!=sums.length-1;i++){
			int j=i+1;			
			while(sums[i][0].equals(sums[j][0])){
				if(c+1==matches.length){
					resize();
				}
				matches[c][0]=sums[i][1];
				matches[c][1]=sums[i][2];
				matches[c][2]=sums[j][1];
				matches[c][3]=sums[j][2];
				j++;
				c++;			
			}
		}
		//StdOut.println(c);
		sortedMatches = new Integer[c][4];
		for(int i=0;i!=c;i++){
				sortedMatches[i][0]=matches[i][0];
				sortedMatches[i][1]=matches[i][1];
				sortedMatches[i][2]=matches[i][2];
				sortedMatches[i][3]=matches[i][3];
			
		}
			//StdOut.println();
		
		Sort(sortedMatches);
		int cc = 0;
		
		a:{for(int i=0;i!=sortedMatches.length;i++){
				int a = sortedMatches[i][0].intValue();
				int b = sortedMatches[i][1].intValue();
				int x = sortedMatches[i][2].intValue();
				int y = sortedMatches[i][3].intValue();
				
				if((a!=b)&&(a!=x)&&(a!=y)&&(b!=x)&&(b!=y)&&(x!=y)){
					if(b>a){
						if(x>a&&y>x){
							//StdOut.println(a + " " + b + " " + x + " " + y);
							cc++;
						}
					}
				}
		
		}}
		StdOut.println(cc);
		for(int i=0;i!=sortedMatches.length;i++){
			int a = sortedMatches[i][0].intValue();
			int b = sortedMatches[i][1].intValue();
			int x = sortedMatches[i][2].intValue();
			int y = sortedMatches[i][3].intValue();
			
			if((a!=b)&&(a!=x)&&(a!=y)&&(b!=x)&&(b!=y)&&(x!=y)){
				if(b>a){
					if(x>a&&y>x){
						StdOut.println(a + " " + b + " " + x + " " + y);
					}
				}
			}
		}
		
		
	}
	
	public void resize(){
		matches = Arrays.copyOf(matches, matches.length*2);
	}
	
	
	
	
	public static void main (String[] args){
	
		
		int n = StdIn.readInt();
		//StdOut.println(n);
		SumSort ss = new SumSort(n);
		for(int i=0;i!=n;i++){
			ss.list[i]=StdIn.readInt();
		}
		Stopwatch timer = new Stopwatch();
		ss.doSums();
		ss.Sort(ss.sums);
		ss.eval();
		double time = timer.elapsedTime();
		//StdOut.println(time);
		
	}
	
	public int compare(Comparable[] o1, Comparable[] o2) {
		// TODO Auto-generated method stub
		return 0;
	}

	public Comparator<Comparable[]> reversed() {
		// TODO Auto-generated method stub
		return null;
	}

	public Comparator<Comparable[]> thenComparing(
			Comparator<? super Comparable[]> other) {
		// TODO Auto-generated method stub
		return null;
	}

	public <U> Comparator<Comparable[]> thenComparing(
			Function<? super Comparable[], ? extends U> keyExtractor,
			Comparator<? super U> keyComparator) {
		// TODO Auto-generated method stub
		return null;
	}

	public <U extends Comparable<? super U>> Comparator<Comparable[]> thenComparing(
			Function<? super Comparable[], ? extends U> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public Comparator<Comparable[]> thenComparingInt(
			ToIntFunction<? super Comparable[]> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public Comparator<Comparable[]> thenComparingLong(
			ToLongFunction<? super Comparable[]> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public Comparator<Comparable[]> thenComparingDouble(
			ToDoubleFunction<? super Comparable[]> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T extends Comparable<? super T>> Comparator<T> reverseOrder() {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T extends Comparable<? super T>> Comparator<T> naturalOrder() {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T> Comparator<T> nullsFirst(Comparator<? super T> comparator) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T> Comparator<T> nullsLast(Comparator<? super T> comparator) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T, U> Comparator<T> comparing(
			Function<? super T, ? extends U> keyExtractor,
			Comparator<? super U> keyComparator) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T, U extends Comparable<? super U>> Comparator<T> comparing(
			Function<? super T, ? extends U> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T> Comparator<T> comparingInt(
			ToIntFunction<? super T> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T> Comparator<T> comparingLong(
			ToLongFunction<? super T> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}

	public static <T> Comparator<T> comparingDouble(
			ToDoubleFunction<? super T> keyExtractor) {
		// TODO Auto-generated method stub
		return null;
	}
	
}
