use espbd

create table cliente (
login char(8) not null,
senha char(8) not null,
nome char(40) not null,
endereco char(60) not null,
qtd_obras_vendidas int not null,
qtd_obras_compradas int not null,
primary key (login)
)
create table obras_literarias (
codobra int not null, 
nome char(40) not null,
editora char(40) null,
preco numeric(6,2) not null, 
tipo int not null, 
login_vendedor char(8) not null,
data date not null,
primary key (codobra),
foreign key (login_vendedor) references cliente
)
create index ixobras_clientev on
obras_literarias(login_vendedor)
create table livro (
codobra int not null, 
ISBN numeric(13,0) not null,
primary key (codobra),
foreign key (codobra) references obras_literarias
)
create table periodico (
codobra int not null, 
numero int not null, 
volume int not null,
primary key (codobra),
foreign key (codobra) references obras_literarias
)
create table compra (
codcompra int not null, 
data date not null,
login_comprador char(8) not null,
codobra int not null,
primary key (codcompra),
foreign key (login_comprador) references cliente,
foreign key (codobra) references obras_literarias
)
create index ixcompra_clientec on compra(login_comprador)
create unique index ix_compra_obra on compra(codobra)-- Questão 1create trigger controle_vendaon compra for delete as update cliente set qtd_obras_compradas = qtd_obras_compradas - 1, qtd_obras_vendidas = qtd_obras_vendidas - 1where cliente.login = (select login_comprador from deleted)-- Questão 2delete from compra where codcompra = 1