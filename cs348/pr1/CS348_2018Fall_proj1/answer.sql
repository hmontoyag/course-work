-- Query1
select Category, count(*) as NumberOfProducts from Product group by Category order by NumberOfProducts desc;

-- Query2
select category, to_char(avg(exfactoryprice),'99999999990.00') as AveragePrice from product group by category order by AveragePrice desc;

-- Query3
select unique productid, productname from product join company on product.companyid=company.companyid where company.state='CA' or company.state='IN' order by productid asc;

-- Query4
select retailerid,retailerinventory.productid, (t1.OrderTotal - totalstock) as PrepareNumber from retailerinventory join (select productid, sum(orders.count) as OrderTotal from orders where orders.status = 'PENDDING' group by productid) t1 on retailerinventory.productid = t1.productid where ordertotal > totalstock order by retailerid, productid asc;

-- Query5
select * from(select productname, sum(orders.count) as NumberOfItemsSold from orders join product on orders.productid=product.productid group by productname order by NumberOfItemsSold desc)  where rownum <= 3;

-- Query6
select * from (select firstname, lastname, t1.total as TotalAmount from customer join (select customerid, to_char(sum(unitprice*orders.count),'99999999990.00') as total from orders group by customerid order by total desc) t1 on t1.customerid = customer.customerid) where rownum <=3;

-- Query7
select * from (select retailer.retailerid, retailer.retailername, t1.NumberOfOrders from retailer join (select retailerid, count(retailerid) as NumberOfOrders from orders group by retailerid) t1 on t1.retailerid=retailer.retailerid order by t1.NumberOfOrders desc) where rownum<=2;

-- Query8
select * from (select retailer.retailerid, retailername, t1.NetProfit from retailer join (select retailerid, to_char(sum(((unitprice - exfactoryprice)*orders.count)),'99999999990.00') as NetProfit from orders join product on orders.productid=product.productid group by retailerid) t1 on t1.retailerid=retailer.retailerid order by NetProfit desc) where rownum <=2;

-- Query9
select * from (select company.companyid, companyname, TotalCount from company join (select companyid, sum(t1.Total) as TotalCount from product join (select productid, sum(orders.count) as Total from orders group by productid) t1 on t1.productid=product.productid group by companyid) t2 on company.companyid = t2.companyid order by TotalCount desc) where rownum <=3;


-- Query10
select * from (select retailer.retailerid, retailername, NumberOfDistinctCustomers from retailer join (select retailerid, count(*) as NumberOfDistinctCustomers from (select unique customerid, retailerid from orders) group by retailerid order by NumberOfDistinctCustomers  desc) t1 on retailer.retailerid=t1.retailerid) where rownum <=2;
