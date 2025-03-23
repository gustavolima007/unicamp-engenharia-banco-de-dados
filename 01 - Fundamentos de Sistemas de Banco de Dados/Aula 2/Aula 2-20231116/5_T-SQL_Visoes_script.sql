-- Visões

use espbd
go

create table produto (
codproduto int not null,
nome varchar(60) not null, 
preco numeric(5,2) not null,
primary key (codproduto)
)
go

create table fornecedor (
codfornecedor int not null,
nome varchar(60) not null, 
endereco varchar(70) not null,
primary key (codfornecedor)
)
go

create table produtofornecedor (
codproduto int not null,
codfornecedor int not null,
primary key (codproduto, codfornecedor),
foreign key (codproduto) references produto,
foreign key (codfornecedor) references fornecedor
)
go

insert into produto values (1, 'caneta', 5.00)
insert into produto values (2, 'borracha', 2.50)
insert into produto values (3, 'caderno', 10.00)

insert into fornecedor values (1, 'ABC', 'XXXXX')
insert into fornecedor values (2, 'DEF', 'YYYYY')

insert into produtofornecedor values (2,1)
insert into produtofornecedor values (3,1)
insert into produtofornecedor values (1,2)
insert into produtofornecedor values (3,2)

select * from produto
select * from fornecedor
select * from produtofornecedor

create view visaofornecproduto
as 
select f.nome nomefornecedor, p.nome nomeproduto 
from fornecedor f inner join produtofornecedor pf 
         on f.codfornecedor = pf.codfornecedor 
         inner join produto p 
         on pf.codproduto = p.codproduto 


select * from visaofornecproduto
where nomeproduto = 'caneta'

select distinct nomefornecedor from visaofornecproduto

select nome nomefornecedor from fornecedor

create view semtabela
as
select getdate() as DataAtual,@@language as LinguagemAtual

select * from semtabela

execute sp_helptext visaofornecproduto

drop view visaofornecproduto, semtabela

drop table produtofornecedor, fornecedor, produto
