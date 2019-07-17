
public class Cuckoo {
	Integer r = 256;
	Integer map[][] = new Integer[r][2]; //[x][0] are keys, [x][1] are values
	long a1, a2;
	double _e = 0.05;
	int size = 0;
	boolean verbose;
	
	public Cuckoo(long a, long b) {
		a1 = a;
		a2 = b;
	}
	
	
	
	
	public void delete(Integer key) {
		for(int i=0;i!=map[0].length;i++) {
			if(map[i][0].equals(key)) {
				map[i][1] = null;
				map[i][0] = null;
				size--;
				break;
			}
		}
	}

	public void contains(Integer key) {
		for(int i=0;i!=map[0].length;i++) {
			if(map[i][0].equals(key)) {
				StdOut.println("yes");
				return;
			}
		}
		StdOut.println("no");
	}

	public void get(Integer key) {
		for(int i=0;i!=map[0].length;i++) {
			if(map[i][0].equals(key)) {
				StdOut.println(map[i][1]);
				return;
			}
		}
		StdOut.println("none");
	
	}

	public void size() {

		StdOut.println(size);
		return;
	}
	
	public void setVerbose(boolean x) {
		if (x==true) {
			verbose = true;
		} else {
			verbose = false;
		}
	}

	public static void main (String[] args){
	
		
//		long a = 9516234881L;
//		Object k = new Integer(23);
//		int key = k.hashCode();
//		long h = (a*key);
//		double p = Math.pow(2,16);
//		h = (long) (h/p);
//		h = h%256;
//		StdOut.println(h);
	}
}
