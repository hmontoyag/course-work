import java.util.Arrays;
import java.util.Comparator;
import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.function.ToIntFunction;
import java.util.function.ToLongFunction;


public class ArrayPractice implements Comparator<Comparable[]>{
	public void Sort(Integer[][] theArray)
	{   
	    
	    Arrays.sort(theArray, new Comparator<Integer[]>()
	    {
	        public int compare(Integer[] int1, Integer[] int2)
	        {
	            Integer numOfKeys1 = int1[0];
	            Integer numOfKeys2 = int2[0];
	            return numOfKeys1.compareTo(numOfKeys2);
	        }
	    });
   
	}
		
	public static void main(String[] args){
		Integer ar[][] = new Integer[3][3];
		for(int i=0;i!=3;i++){
			ar[0][i]=i+1*10;
		}
		for(int i=0;i!=3;i++){
			ar[1][i]=i+1*100;
		}
		for(int i=0;i!=3;i++){
			ar[2][i]=1+i;
		}
		ar[2][1]=21;
		for(int i=0;i!=3;i++){
			for(int j=0;j!=3;j++){
				StdOut.print(ar[i][j]+ " | ");
			}
			StdOut.println();
		}
		ArrayPractice a = new ArrayPractice();
		a.Sort(ar);
		for(int i=0;i!=3;i++){
			for(int j=0;j!=3;j++){
				StdOut.print(ar[i][j]+ " | ");
			}
			StdOut.println();
		}
		
		
		
		
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
