set serveroutput on size 32000

-- Question 1: Retailer detail
create or replace procedure RetailerDetail (id IN Retailers.RetailerId%TYPE) as

    total integer;
    pid integer;
    ordertotal integer;
    pname varchar(30);
    rname varchar(30);
    rid integer;
    rad varchar(30);
    
BEGIN

  select retailername, retailerid, address into rname, rid, rad from retailers where retailerid = id;
  select count(*) into total from orders where retailerid=rid;
  select productid, cc into pid, ordertotal from (select productid, sum(orders.count) as cc from orders where retailerid=rid group by productid order by cc desc) where rownum=1;
  select productname into pname from products where productid = pid;
  dbms_output.put_line('Retailer Name: '||rname);
  dbms_output.put_line('Retailer Address: '||rad);
  dbms_output.put_line('Retailer Total Orders: '||total);
  dbms_output.put_line('Most Popular Product: '||pname);
  dbms_output.put_line('Total Sold: ' ||ordertotal);

END RetailerDetail;
/

-- make test cases yourselves
BEGIN
RetailerDetail(1);
end;
/

-- Queation 2: Monthly delay report
create or replace procedure MonthlyDelayReport as
	cursor c1 is select distinct extract(month from orderdate) as mon, extract(year from orderdate) as yea from orders where status='DELAYED' order by yea, mon asc;
    delayedcount number(10);
    cursor c2 is select distinct retailerid, extract(month from orderdate) as mon, extract(year from orderdate) as yea from orders where status='DELAYED';
    rname varchar(30);
BEGIN
	for x in c1 loop
        select count(*) into delayedCount from (select * from orders where extract(month from orderdate)=x.mon and extract(year from orderdate)=x.yea and status='DELAYED');
        dbms_output.put_line('Delayed orders in '||x.yea||'-'||x.mon||': '||delayedCount);
        dbms_output.put_line('Retailers with delayed orders:');
        
       for y in c2 loop
       		if x.mon = y.mon and x.yea = y.yea then
            	select retailername into rname from retailers where retailers.retailerid = y.retailerid;
             	dbms_output.put_line('- '||rname);
        	end if;
        end loop;
    end loop;

END MonthlyDelayReport;
/
BEGIN
	MonthlyDelayReport;
End;
/

-- Question 3: Find the product with least profit in each category
create or replace procedure LeastProfitProduct as
 cursor c1 is select pid as pid, t2.category as cat, t3.res as res from (select t1.pid, category, ((t1.pricesum/tots)-exfactoryprice) as res from products join (select productid as pid, count(productid) as tots, sum(unitprice) as pricesum from orders group by productid order by productid asc) t1 on products.productid=t1.pid) t2 inner join
(select category, MIN(((t1.pricesum/tots)-exfactoryprice)) as res from products join (select productid as pid, count(productid) as tots, sum(unitprice) as pricesum from orders group by productid order by productid asc) t1 on products.productid=t1.pid group by category) t3 on t2.category=t3.category
and t2.res=t3.res;
cursor c2 is select category as cat from products group by category;
pname varchar(30);
BEGIN
	for y in c2 loop
     dbms_output.put_line('Least profit in '||y.cat);
        for x in c1 loop
            if x.cat=y.cat then
        
                select productname into pname from products where productid=x.pid;
                dbms_output.put_line('- '||pname||': '||x.res);
                
            end if;
        end loop;
    end loop;
END LeastProfitProduct;
/

BEGIN
	LeastProfitProduct;
END;
/

-- Queation 4: New table for retailer product category distribution
create table RetailerCatergoryTable(RetailerId integer, Electronic integer, Apparel integer, Books integer, primary key(RetailerId));
create or replace procedure RetailerProductCatergory as
cursor c1 is select retailerid from retailers;
    ec number(5);
    ac number(5);
    bc number(5);
BEGIN
	for x in c1 loop
        select count(orderid) into bc from orders join products on orders.productid=products.productid where retailerid=x.retailerid and category='books';
        select count(orderid) into ec from orders join products on orders.productid=products.productid where retailerid=x.retailerid and category='electronics';
        select count(orderid) into ac from orders join products on orders.productid=products.productid where retailerid=x.retailerid and category='apparel';
        insert into RetailerCatergoryTable(RetailerId, Electronic, Apparel, Books) values (x.retailerid, ec, ac, bc);
    
    end loop;
END RetailerProductCatergory;
/

BEGIN
RetailerProductCatergory;
END;
/
select * from RetailerCatergoryTable;

drop table RetailerCatergoryTable;


-- Question 5: Exception Handle
create or replace procedure CustomerProductInfo(cid IN Customers.CustomerId%TYPE, pid IN Products.ProductId%TYPE) as
 
 cursor c2 is select orderdate from orders where customerid=cid and productid=pid;
    cc number(5);
    pp number(5);
    
BEGIN
		select customerid into cc from customers where customerid=cid;
        select productid into pp from products where productid=pid;
        dbms_output.put_line('Records of customer id '||cid||' with product id '||pid||':');
        
        for y in c2 loop
            dbms_output.put_line(y.orderdate);
        end loop;
EXCEPTION
	when no_data_found then
            dbms_output.put_line('Invalid customer id or product id!');
END CustomerProductInfo;
/

BEGIN
CustomerProductInfo(1,1);
END;
/

BEGIN
CustomerProductInfo(-1,1);
END;
/

BEGIN
CustomerProductInfo(2,5);
END;
/

BEGIN
CustomerProductInfo(1,10);
END;
/
