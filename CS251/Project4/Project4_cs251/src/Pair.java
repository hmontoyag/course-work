
public class Pair {
	Integer x;
	Integer y;
	Integer a;
	Integer b;

	Integer sumto;
	
	public Pair(Integer x, Integer y, Integer a, Integer b,Integer sum){
		this.x=x;
		this.y=y;
		this.a=a;
		this.b=b;
		this.sumto = sum;
		
	}
	public Integer getSumto() {
		return sumto;
	}
	public void setSumto(Integer sumto) {
		this.sumto = sumto;
	}
	public Integer getX() {
		return x;
	}
	public void setX(Integer x) {
		this.x = x;
	}
	public Integer getY() {
		return y;
	}
	public void setY(Integer y) {
		this.y = y;
	}
	public Integer getA() {
		return a;
	}
	public void setA(Integer a) {
		this.a = a;
	}
	public Integer getB() {
		return b;
	}
	public void setB(Integer b) {
		this.b = b;
	}
	
	
}
