USE ERP_DB;


/* listagem de todas as categorias com pelo menos 3 produtos cadastrados (JOIN) */
SELECT c.categoria_id, c.nome AS nome_categoria, COUNT(a.produto_id) AS total_produtos
FROM categoria c
INNER JOIN CATEGORIA_PRODUTO b ON c.categoria_id = b.categoria_id
INNER JOIN produto a ON b.produto_id = a.produto_id
GROUP BY c.categoria_id, c.nome
HAVING COUNT(a.produto_id) >= 3
order by c.categoria_id asc;

select * from CATEGORIA_PRODUTO



/* Listagem dos clientes cujo nome contenham sequencia de letras 'CA'*/
select * from cliente a
where a.nome like 'ca%';

/* Listagem de todos os produtos ccom valor entre 10 e 20*/
select a.produto_id, a.nome, a.preco from produto a 
where a.preco between 10 and 20
order by a.preco desc;


/* Listagem dos 10 clientes que fizeram a maior quantidade de compras (Agrupamento)*/

select * from PEDIDO a
join cliente b on a.cliente_id = b.cliente_id
order by a.total desc
limit 10;





