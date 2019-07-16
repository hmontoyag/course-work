import edu.princeton.cs.algs4.WeightedQuickUnionUF;


public class Percolation {
	
	int n;
	int grid[][];
	int opened[];
	
	WeightedQuickUnionUF uf;
	
	public Percolation(int n){
		this.n=n;
		this.grid=new int[n][n];
		this.opened = new int[n*n];
		this.uf = new WeightedQuickUnionUF(n*n);
		
		for(int i =0;i!=n;i++){for(int j=0;j!=n;j++){this.grid[n-1-i][j]=-1;}}//i*n+j;}}
		for(int i=0;i!=n*n;i++){opened[i]=-1;}
	}
	
	public boolean isOpen(int x, int y){
		if(this.opened[x+this.n*y]!=-1){
			return true;
		}
		return false;
	}
	
	public void open(int x, int y){
		if(x>=n||y>=n){
			//StdOut.println("Out of Bounds");
			return;
		}
		if(isOpen(x,y)){
			//StdOut.println("Opened before.");
			return;
		}
		opened[x+n*y]=x+y*n;
		int i=x;
		int j=y;
		//ESTO ESTA BIEN, te tomo un culo asi que ni lo toques.
		//conversion para orientacion:
		int t = y;
		y=x;
		x=n-1-t;
		
		////
		grid[x][y]=i+j*n;;
		int N=1,S=1,E=1,W=1;
		//Check boundaries
		if(i==0){W=0;}
		if(i==n-1){E=0;}
		if(j==0){S=0;}
		if(j==n-1){N=0;}
		
		if(E==1){	if(isOpen(i+1,j)){	uf.union(i+j*n, i+1+(j)*n);	
			}
		}
		if(W==1){	if(isOpen(i-1,j)){	uf.union(i+j*n, i-1+(j)*n);
			}
		}
		if(N==1){	if(isOpen(i,j+1)){	uf.union(i+j*n, i+(j+1)*n);
			}
		}
		if(S==1){	if(isOpen(i,j-1)){	uf.union(i+j*n, i+(j-1)*n);
			}
		}
	}

	public boolean isFull(int x,int y){
		
		if(isOpen(x,y)==false){return false;}
		for(int i =0; i!=n;i++){
			if(uf.connected((n*n)-1-i, x+n*y)){
				return true;
			}
		}
		return false;
	}
		
	
	public boolean percolates(){
		for(int i=0; i!=n-1;i++){
			if(isFull(i,0)){
				return true;
			}
		}
		return false;
		
	}
		
		
		
		
		
		
		
		
		
	
	
	
	public static void main (String[] args){
		//Percolation p = new Percolation(5);
		Stopwatch timer = new Stopwatch();
		int n = StdIn.readInt();
		Percolation p = new Percolation(n);
		while(StdIn.isEmpty()==false){
			int x= StdIn.readInt();
			//StdOut.print(x + ", ");
			int y = StdIn.readInt();
			//StdOut.println(y);
			p.open(x,y);
			
		}
		if(p.percolates()){
			StdOut.println("Yes");
			
		} else { StdOut.println("No");
		
		}

//		StdArrayIO.print(p.grid);
		//StdArrayIO.print(p.opened);
//		p.open(0,0);
//		p.open(0,1);
//		p.open(4,0);
//		p.open(1,1);
//		p.open(1,2);
//		p.open(4,4);
//		p.open(4,3);
//		p.open(3,3);
//		p.open(2,2);
//		//p.open(3,2);
//		StdArrayIO.print(p.grid);
//		StdOut.print(p.percolates());
		
		
	}
	
	
	
	
}



