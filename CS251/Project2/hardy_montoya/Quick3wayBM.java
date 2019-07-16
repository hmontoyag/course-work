import edu.princeton.cs.algs4.Insertion;

public class Quick3wayBM {
	
	private Quick3wayBM() { }
	
	public static void sort(Comparable[] a) {
       
        sort(a, 0, a.length - 1);
        assert isSorted(a);
    }
	public static Comparable median(Comparable x, Comparable y, Comparable z){
		if(y.compareTo(x)>0){
			if(z.compareTo(y)>0){
				return y;
			}else if (z.compareTo(x)>0){
				return z;
			} else {
				return x;
			}
		}else{
			if(z.compareTo(x)>0){
				return x;
			}else if(x.compareTo(y)>0){
				return z;
			} else {
				return y;
			}
		}
	}

   public static Comparable medianOf3(Comparable[]a,int l, int h){
	   int size = h-l+1;
	   int t = (size-1)/2;
		Comparable v=median(a[l],a[l+t],a[l+t*2]);
		return v;
   }
   public static void doInsertion(Comparable[] a, int l,int h){
		
			int size = h-l+1;
			Comparable[] b = new Comparable[size];
			for(int i=0;i!=size;i++){
	    		b[i]=a[l+i];
	    	}
	    	Insertion.sort(b);
	    	for(int i=0;i!=size;i++){
	    		a[l+i]=b[i];
	    	}
	    	//StdOut.println("(Insertion Sort, "+l+", "+h+")");
	}
   public static Comparable tukey(Comparable[]a, int l, int h){
		int size = h-l+1;
	    int t = (size-1)/8;
		Comparable m1 = median(a[l],a[l+t],a[l+t*2]);
		Comparable m2 = median(a[l+t*3],a[l+t*4],a[l+t*5]);
		Comparable m3 = median(a[l+t*6],a[l+t*7],a[l+t*8]);
		Comparable v = median(m1,m2,m3);
		return v;
   }
	
	
	// quicksort the subarray a[lo .. hi] using 3-way partitioning
    private static void sort(Comparable[] a, int lo, int hi) { 
//    	StdOut.println("------------------------");
    	if(isSorted(a)==true){return;}
        if (hi <= lo) {return;}
        int size = hi-lo+1;
//        StdOut.println("HI: " + hi+", LO: "+ lo);
        
        
        //INSERTION SORT?
        if(size<=8){ // Insertion Sort
        	doInsertion(a,lo,hi);
        	StdOut.println("(Insertion Sort, " + lo+", "+hi+")");
        	return;            	
        //TUKEY OR THE OTHER THEN?
        } else {
        	Comparable v;
        	String method;
        	if (size>8 && size<=40){ //Median of 3
//        		StdOut.println("MEDIANOF3 for Size "+size);
        		v=medianOf3(a,lo,hi);
        		method = "Median of 3, ";
        	} else {
//        		StdOut.println("TUKEY FOR SIZE " + size);
        		//size > 40, use Tukey
        		v=tukey(a,lo,hi);
        		method = "Tukey Ninther, ";
        	}
        	int leftDone=0;
        	int when = 0;
        	setSides:{for(int l=lo;l!=hi;l++){
        		if(a[l]==v&&leftDone==0){
        			exch(a,lo,l);
        			leftDone=1;
        			when = l;
        		} else if(a[l]==v&&leftDone==1&&l>when){
        			exch(a,hi,l);
        			break setSides;
        		}
        		
        	}}
//       	StdOut.println("SIDES SET FOR V");
//        	for(int f =0; f!=a.length;f++){
//        		StdOut.print("["+f+"]: "+a[f] + " ");
//        	}
//        	StdOut.println();
//        	for(int f =0; f!=a.length;f++){
//        		StdOut.print(a[f] + " ");
//        	}
//        	StdOut.println();
        	int i = lo+1, j=hi-1,p=lo,q=hi;       
            
        bigLoop: {while (i <= j) {
        			while(a[i].compareTo(v)==-1&&i<j){i++;}
        			while(a[j].compareTo(v)==1&&i<j){j--;}
        			if(i>=j){
        				if(a[i].compareTo(a[j])==0&&a[j].compareTo(v)==0){
        					exch(a,j,q-1);
        					q--;
        				}
        				j--;
        				
        				break bigLoop;
        			}
        			
        			exch(a,i,j);
        			if(a[i].compareTo(v)==0){
        				exch(a,i,p+1);
        				i++;
        				p++;
//        				StdOut.println("a-i ex");
        			}
        			if(a[j].compareTo(v)==0&&i<j){
        				exch(a,j,q-1);
        				j--;
        				q--;
//        				StdOut.println("a-j ex");
        			}
        			
        			
        			
        	}
        	
        	
        	}//here ends the else that allows for V,
        	 //However you can send stuff after it ends since the Insertion sort doesnt reach this part anyways
//        	StdOut.println("WITH V AT SIDES");
//        	for(int f =0; f!=a.length;f++){
//        		StdOut.print(a[f] + " ");
//        	}
//        	StdOut.println();
        	//CHECK FOR a bug i couldnt explain, but this actually solves it somehow? while still meeting the formula for p,q,hi,lo
        	if(a[i].compareTo(v)==-1){
        		i++;
        		j++;
        	}
        	StdOut.println("("+method+lo+", "+v+", "+p+", "+i+", "+j+", "+q+", "+hi+")");
//        	StdOut.println("with values at side");
//        	for(int f =0; f!=a.length;f++){
//        		StdOut.print("["+f+"]: "+a[f] + " ");
//        	}
//        	StdOut.println();
        	//MOVE VALUES TO MIDDLE
        	//
        	//values at left if any
        	int ss=j;
        	
        		
        	
        	for(int t=0;lo+t<=p;t++){
        		if((p+t)==j){break;}
        		exch(a,lo+t,j-t);
        		ss=j-t;
        	}
        	int ee=i;
        	for(int n=0;hi-n>=q;n++){
        		if((q-(i+n))==0){break;}
        		exch(a,hi-n,i+n);
        		ee=i+n;;
        	}
//        	StdOut.println("END");
//        	for(int f =0; f!=a.length;f++){
//        		StdOut.print("["+f+"]: "+a[f] + " ");
//        	}
//        	StdOut.println();
//        	StdOut.println("-----------------------------------");
        	int start=-1;
        	int end=-1;
        	//this operation isnt TOO costly, but could be removed with a proper formula for the higher and lower limit of the recursions
        	for(int f=0;f!=a.length;f++){
        		if(a[f]==v&&start==-1){
        			start=f;
        		}
        		if(a[f]!=v&&start>-1){
        			end=f;
        			start--;
        			break;
        		}
        	}
//        	StdOut.println("START: "+start+" END: "+end);
//        	StdOut.println("SS: "+ss+" EE: "+ee);
        	//check borders?
        
        	sort(a, lo, start);
            sort(a, end, hi);
        }
        assert isSorted(a, lo, hi);
    	
	}
        
       
    
    
    private static boolean less(Comparable v, Comparable w) {
    	return v.compareTo(w) < 0;
    }
    
    private static void exch(Comparable[] a, int i, int j) {
        Comparable swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
    
    private static boolean isSorted(Comparable[] a) {
        return isSorted(a, 0, a.length - 1);
    }

    private static boolean isSorted(Comparable[] a, int lo, int hi) {
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }
    
    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; i++) {
            StdOut.println("["+i+"]: "+ a[i]);
        }
    }


    
    public static void main (String[] args){
    	int size = StdIn.readInt();
    	Comparable a[] = new Comparable[size];
    	int i=0;
    	while(StdIn.isEmpty()==false){
    		a[i]=StdIn.readInt();
    		i++;
    	}
    	
//    	int k = (size)/8;
//    	Comparable m1=median(a[0],a[k],a[k*2]);
//    	Comparable m2 = median(a[k*3],a[k*4],a[k*5]);
//    	Comparable m3 = median(a[k*6],a[k*7],a[k*8]);
//    	Comparable mm = Quick3wayBM.median(m1, m2, m3);
//    	StdOut.println("MEDIAN AT FIRST BY TUKEY: " + mm);
    	Quick3wayBM.sort(a);
    //	show(a);
//    	boolean x = isSorted(a);
//    	StdOut.println(x);
    	
    	
    }
}
