use pubs

select * from titles a
where a.title like '%sili%'
and a.price between 15 and 30;

select a.title_id, a.type gêneros, a.title títulos from titles a
order by a.title_id desc, a.title asc;

select a.* from titles a
order by a.pubdate asc;

use pubs
select A.price, a.pub_id from titles a
WHERE A.PRICE < 10.00
group by  A.price, a.pub_id;


select c.city, a.title_id, a.title from titles a
INNER JOIN sales B ON A.title_id = B.title_id
INNER JOIN stores C ON B.stor_id = C.stor_id	
where a.title_id in ('BU7832', 'PS3333');


select a.title títulos, a.price, a.type gêneros, c.stor_name  from titles a
INNER JOIN sales B ON A.title_id = B.title_id
INNER JOIN stores C ON B.stor_id = C.stor_id	
where a.type = 'popular_comp';

select a.title, b.pub_name from titles a
INNER JOIN publishers b on a.pub_id = b.pub_id
where b.pub_name = 'New Moon Books';

select a.title títulos, c.stor_name, a.pubdate from titles a
INNER JOIN sales B ON A.title_id = B.title_id
INNER JOIN stores C ON B.stor_id = C.stor_id	
order by a.pubdate asc;

select a.stor_name, a.state from stores a
order by a.state asc;

use pubs

select title_id, avg(PRICE) from titles
group by title_id