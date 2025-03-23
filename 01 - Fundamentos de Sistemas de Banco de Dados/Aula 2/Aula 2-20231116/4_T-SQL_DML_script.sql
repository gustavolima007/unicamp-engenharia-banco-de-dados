/* SQL-DML - INSERT, UPDATE, DELETE */

use espbd
go

/* Criação de todas as tabelas da Base de Dados */

create table cliente (
codigo int not null,
nome char(20) not null,
endereco char(30) null,
cidade char(15) null,
cep char(8) null, 
uf char(2) null, 
cnpj char(20) null,
ie char(20) null,
primary key (codigo)
)
go

create table vendedor (
codigo int not null,
nome char(20) not null,
salario_fixo money not null,
faixa_comissao char(1) not null,
primary key(codigo)
)
go 

create table produto (
codigo int not null,
unidade char(3) not null,
descricao char(30) null,
val_unit money not null,
primary key(codigo)
)
go 

create table pedido (
num_pedido int not null,
prazo_entrega int not null,
codigo_c int not null,
codigo_v int not null,
primary key(num_pedido), 
foreign key (codigo_c) references cliente,
foreign key (codigo_v) references vendedor
)
go

create table item_do_pedido (
num_pedido int not null,
codigo_p int not null,
quantidade int not null,
primary key (num_pedido, codigo_p),
foreign key (num_pedido) references pedido,
foreign key (codigo_p) references produto
)
go

select * from cliente
select * from vendedor
select * from produto
select * from pedido
select * from item_do_pedido

/* Inserção de dados: INSERT */

/* Omitindo o nome das colunas - é necessário manter a ordem de criação */

insert into produto
values (108, 'kg', 'parafuso', 1.25)

select * from produto

/* Omitindo a descrição (NULL) */

insert into produto
values (111, 'm', NULL, 1.50)

select * from produto

insert into produto (codigo, unidade, val_unit)
values (109, 'cm', 1.50)

select * from produto

/* Especificando explicitamente o nome da colunas - é possível alterar a ordem de criação */

insert into produto (codigo, descricao, unidade, val_unit)
values (110, 'elástico', 'm', 2.00)

select * from produto

/* Inserindo vendedores */

insert into vendedor 
values (111, 'Carlos', 2490.00, 'A')

insert into vendedor 
values (130, 'Joana', 2780.00, 'C')

insert into vendedor 
values (209,'Jorge', 1800.00, 'C')

select * from vendedor

/* Cadastrando como clientes os vendedores cujo nome comece com a letra J */

insert into cliente (codigo, nome)
select codigo, nome
from vendedor
where nome like 'J%'

/* Alteração de dados: UPDATE */

update produto
set val_unit = 1.62
where descricao = 'parafuso'

select * from produto

update vendedor
set salario_fixo = (salario_fixo * 1.27)

select * from vendedor

update produto
set val_unit = 2.00,
    descricao = 'parafuso de aço'
where codigo = 108

select * from produto

/* Exclusão de dados: DELETE */

delete from vendedor
where salario_fixo < 2500.00

select * from vendedor

delete from vendedor

select * from vendedor

truncate table item_do_pedido

drop table item_do_pedido, pedido, produto, vendedor, cliente
go

/* Consulta a dados: SELECT */

/* Escolhendo o Banco de Dados a ser utilizado */

use pubs

/* Consultas simples */

select * 
from publishers

select pub_name, state 
from publishers

/* Eliminação de linhas replicadas do resultado da consulta */

select distinct city, state 
from authors

/* Consultas qualificadas */

select stor_name, state
from stores
where state = 'CA'

select stor_id, stor_name
from stores
where stor_id between '6380' and '7100'

select stor_id, stor_name
from stores
where stor_id not between '6380' and '7100'

select stor_name, city, state
from stores
where state in ('CA','UT')

select stor_name
from stores
where stor_name like 'B%'

select stor_name
from stores
where stor_name not like 'B%'

select au_fname, au_lname
from authors
where au_fname like '%en%'

select stor_name
from stores	
where stor_name like '[BN]%'

select stor_name
from stores	
where stor_name like '[A-E]%'

select stor_id, stor_name
from stores
where stor_id like '70_6'

/* Consultas com várias condições */

select stor_name, city, state
from stores
where state = 'CA' and city = 'Fremont'

select stor_name, city, state
from stores
where state = 'CA' or city = 'Portland'

select title_id, type, advance
from titles
where (type = 'business' or type = 'psychology') and advance > 5000

/* Atribuições de nomes às colunas do resultado */ 

select au_fname 'Primeiro nome', au_lname Sobrenome
from authors

/* Uso de operadores aritméticos */

select title_id, advance + price
from titles
where type = 'business'

select title Titulo, (price * ytd_sales) Vendas
from titles
where price * ytd_sales > 80000 and type = 'business'

/* Tratamento do valor nulo */

select title, price
from titles
where price is null

/* Ordenação de linhas do resultado */

select title, type, price
from titles
order by price

select title, type, price
from titles
where type = 'business'
order by price desc

select title, type, price
from titles
order by type asc, price desc

select title Titulo,(ytd_sales*price) Vendas
from titles
where type = 'business'
order by ytd_sales*price

select title Titulo,(ytd_sales*price) Vendas
from titles
where type = 'business'
order by Vendas

/* Uso de funções de agregação */

select count(*)
from titles

select max(advance)
from titles

select sum(ytd_sales)
from titles
where type = 'psychology'

select avg(price)
from titles

select avg(price)
from titles
where type = 'business'

select avg(distinct price)
from titles
where type = 'business'

/* Organização de dados em grupos */

select type Gênero, avg(price) 'Preço Médio'
	from titles
	group by type

select title_id, stor_id, sum(qty)
from sales
group by title_id, stor_id

select title_id, avg(price)
from titles
where advance < 3000
group by title_id

/* Estabelecendo condições sobre grupos */

select type Gênero, avg(price) 'Preço Médio'
from titles
group by type
having avg(price) > 12.00

/* Produto Cartesiano */

select *
from  titles cross join publishers

/* Junção interior */

select publishers.pub_id, pub_name, titles.pub_id, title_id, title
from titles inner join publishers
     on publishers.pub_id = titles.pub_id

select stores.stor_id, stor_name, title_id, ord_num, qty
from sales inner join stores
     on sales.stor_id  = stores.stor_id

/* Colocando apelido para o nome das tabelas */

select p.pub_id, pub_name, t.pub_id, title_id, title
from titles t inner join publishers p
     on p.pub_id = t.pub_id

select st.stor_id, stor_name, title_id, ord_num, qty
from sales sa inner join stores st
     on sa.stor_id  = st.stor_id

/* Junção contendo outros critérios */

select s.stor_id, stor_name, title_id, ord_num, qty
from sales sl inner join stores s
     on sl.stor_id = s.stor_id 
where qty < 35

/* Junção envolvendo mais de duas tabelas */

select au_fname, au_lname, title
from authors a inner join titleauthor ta
     on a.au_id = ta.au_id
     inner join titles t
     on ta.title_id = t.title_id

/* Junção exterior */

select a.au_id, au_fname, au_lname, ta.au_id
from authors a left outer join titleauthor ta
     on a.au_id = ta.au_id

select a.au_id, au_fname, au_lname, ta.au_id
from titleauthor ta right outer join authors a
     on a.au_id = ta.au_id

select a.au_id, au_fname, au_lname, ta.au_id
from authors a full outer join titleauthor ta
     on a.au_id = ta.au_id

/* Autores que ainda não tem obras literárias cadastradas */

select a.au_id, au_fname, au_lname, ta.au_id
from authors a left outer join titleauthor ta
     on a.au_id = ta.au_id
where ta.au_id is NULL

select a.au_id, au_fname, au_lname  -- não é necessário listar o ta.au_id
from authors a left outer join titleauthor ta
     on a.au_id = ta.au_id
where ta.au_id is NULL

/* Subconsultas */

select title
	from titles
	where pub_id = (select pub_id
			        from publishers
			        where pub_name = 'New Moon Books')

select title
from titles
where title_id = (select title_id
		          from titleauthor
		          where au_id = (select au_id
				                 from authors
				                 where au_lname = 'Blotchet-Halls'))

select title
from titles
where title_id in (select title_id
		          from titleauthor
		          where au_id in (select au_id
				                  from authors
				                  where au_lname = 'Ringer'))

select au_fname, au_lname, title
from authors a inner join titleauthor ta
     on a.au_id = ta.au_id
     inner join titles t
     on ta.title_id = t.title_id
where au_lname = 'Ringer'

/* Transações */

use espbd
go

create table cliente (
codigo numeric(10,0) not null,
nome char(30) not null,
endereco char(30) not null,
telefone numeric(10,0) null,
tipo tinyint not null,
primary key (codigo)
)
go

create table pfisica (
codigo numeric(10,0) not null,
rg char(10) not null,
cpf numeric(10,0) not null,
primary key (codigo),
foreign key (codigo) references cliente
)
go

create table pjuridica (
codigo numeric(10,0) not null,
cnpj numeric(10,0) not null,
nfantasia char(30) not null,
primary key (codigo),
foreign key (codigo) references cliente
)
go
 
create table conta (
numero numeric(8,0) not null,
tipo tinyint not null,
saldo money not null,
conjunta char(1)  not null,
primary key (numero, tipo)
)
go

create table cliente_conta (
codigo numeric(10,0) not null,
numero numeric(8,0) not null,
tipo tinyint not null,
primary key(codigo, numero, tipo),
foreign key (codigo) references cliente,
foreign key (numero, tipo) references conta
)
go

select * from cliente
select * from pfisica
select * from conta
select * from cliente_conta

begin transaction
insert into cliente 
values (1, 'Jose da Silva', 'Av. 1, 1111, Rio Claro-SP', 5554444, 0)
if @@rowcount > 0  /* insercao de cliente bem sucedida */
begin
   insert into pfisica
   values (1, '3333333', 123456789)
   if  @@rowcount > 0  /* insercao de pessoa física bem sucedida */
      commit transaction
  else
      rollback transaction
 end
 else
     rollback transaction

select * from cliente
select * from pfisica
select * from conta
select * from cliente_conta

begin transaction
insert into conta
values (1, 0, 500.00, 'N')
if @@rowcount > 0 /* inserção de conta corrente bem sucedida */
begin
      insert into cliente_conta
      values (1, 1, 0)
      if @@rowcount > 0
         commit transaction
     else 
         rollback transaction
end
else
     rollback transaction

select * from cliente
select * from pfisica
select * from conta
select * from cliente_conta
 
begin transaction
insert into conta
values (1, 1, 500.00, 'N')
if @@rowcount > 0 /* inserção de conta poupança bem sucedida */
begin
      insert into cliente_conta
      values (1, 1, 1)
      if @@rowcount > 0
        commit transaction
      else
        rollback transaction
end
else
     rollback transaction

select * from cliente
select * from pfisica
select * from conta
select * from cliente_conta

begin transaction
update conta
set saldo  = saldo + 50.00
where numero = 1 and tipo = 1
if @@rowcount > 0  /* credito em poupanca bem sucedido */
begin
      update conta
      set saldo  = saldo - 50.00
      where numero = 1 and tipo = 0
      if  @@rowcount > 0  /* debito em conta corrente bem sucedido */
          commit transaction
      else
          rollback transaction
end
else
      rollback transaction

select * from cliente
select * from pfisica
select * from conta
select * from cliente_conta

drop table cliente_conta, conta, pfisica, pjuridica, cliente