
public class Coordinate {
	public Integer getKey() {
		return key;
	}
	public void setKey(Integer key) {
		this.key = key;
	}
	public Integer getValue() {
		return value;
	}
	public void setValue(Integer value) {
		this.value = value;
	}
	
	public Coordinate(Integer k, Integer v){
		this.key = k;
		this.value = v;
	}
	Integer key;
	Integer value;
	
	
}
