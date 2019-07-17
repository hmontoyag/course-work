echo exit | sqlplus hmontoya@csora/a0axT5SE @drop.sql >/dev/null
echo exit | sqlplus hmontoya@csora/a0axT5SE @create.sql >/dev/null
echo exit | sqlplus hmontoya@csora/a0axT5SE @init.sql >/dev/null

javac -cp .:ojdbc8.jar Project3.java
java -cp .:ojdbc8.jar Project3 input.txt output.txt
