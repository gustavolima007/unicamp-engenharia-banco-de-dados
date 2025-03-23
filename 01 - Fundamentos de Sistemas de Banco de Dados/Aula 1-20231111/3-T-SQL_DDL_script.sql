use espbd
go

/* Criação de todas as tabelas da Base de Dados */

create table cliente (
codigo int not null,
nome char(20) not null,
endereco char(30) not null,
cidade char(15) not null,
cep char(8) not null, 
uf char(2) not null, 
cnpj char(20) not null,
ie char(20) not null,
primary key (codigo),
unique (cnpj),
unique (ie)
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

create index ix_ped_cli
on pedido (codigo_c)
go

create index ix_ped_vend
on pedido (codigo_v)
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

/* não precisa criar índice para a FK (num_pedido), pois já existe um índice composto 
   criado automaticamente para a PK (num_pedido, codigo_p), que também é utilizado somente 
   para a coluna num_pedido, por ser a primeira coluna da PK */

create index ix_item_prod
on item_do_pedido (codigo_p)
go

/* Remoção de todas as tabelas da Base de Dados */

-- drop table item_do_pedido, pedido, produto, vendedor, cliente
