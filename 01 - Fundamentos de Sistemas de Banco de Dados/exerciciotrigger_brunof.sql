
CREATE DATABASE FATURAMENTO

USE FATURAMENTO


CREATE TABLE produto
(
	codproduto int not null identity(1,1),
	nome char (30) not null,
	preço money not null,
	qtdestoque int not null
	primary key(codproduto)
);

CREATE TABLE notafiscal
(
	numnota int not null identity(1,1),
	valortotal money not null,
	primary key(numnota)
);

CREATE TABLE itemnotafiscal
(
	numnota int not null,
	codproduto int not null,
	quantidade int not null,
	primary key(numnota, codproduto),
	foreign key(numnota) references notafiscal(numnota),
	foreign key(codproduto) references produto(codproduto)
);

CREATE TABLE fatura
(
	numfatura int not null identity(1,1),
	dtvencimento date not null,
	dtpagamento date null,
	valor money not null,
	numnota int not null,
	primary key(numfatura),
	foreign key(numnota) references notafiscal(numnota)
);


select * from fatura
select * from itemnotafiscal
select * from notafiscal
select * from produto

/* a) Toda vez que um item de nota fiscal for incluído, seja atualizada a quantidade em estoque do
produto e o valor total da nota fiscal;  */

create trigger inclusaoitemnota
on itemnotafiscal for insert
as
	if not exists(select * from inserted i inner join notafiscal n
					on i.numnota = n.numnota)
		begin
			print 'Esse item não contém um número de nota válido'
			rollback transaction
		end
	else
		begin
			UPDATE notafiscal
			SET valortotal = valortotal + (select p.preço * i.quantidade
											from produto p inner join inserted i
											on p.codproduto = i.codproduto)
			WHERE numnota = (select numnota from inserted);

			UPDATE produto
			SET qtdestoque = qtdestoque - (select quantidade from inserted)
			WHERE codproduto = (select codproduto from inserted);

			if @@rowcount = 0
				rollback transaction
		end


insert into notafiscal values(0)
insert into itemnotafiscal values(11, 6, 1)
insert into itemnotafiscal values(10, 2, 2)

insert into itemnotafiscal values(11, 1, 3)
insert into itemnotafiscal values(11, 4, 2)


	
/*	b) Toda vez que um item de nota fiscal for excluído, seja atualizada a quantidade em estoque do
produto e o valor total da nota fiscal; */

create trigger excluiritemnf
on itemnotafiscal for delete
as
begin
			UPDATE notafiscal
			SET valortotal = valortotal - (select p.preço * d.quantidade
											from produto p inner join deleted d
											on p.codproduto = d.codproduto)
			WHERE numnota = (select numnota from deleted);

			UPDATE produto
			SET qtdestoque = qtdestoque + (select quantidade from deleted)
			WHERE codproduto = (select codproduto from deleted);

			if @@rowcount = 0
				rollback transaction
		end

/* chamada dos triggers */
delete from itemnotafiscal WHERE numnota = 10 and codproduto = 2
delete from itemnotafiscal WHERE numnota = 11 and codproduto = 6

/* c) Toda vez que for alterada a quantidade de um item de nota fiscal, seja atualizada a quantidade em
estoque do produto e o valor total da nota fiscal; */

create trigger alterar_qtditemnotafiscal on
itemnotafiscal for UPDATE
as
if update(quantidade)
	begin
		update notafiscal
		set valortotal = valortotal + (select p.preço * (i.quantidade - d.quantidade) -- preço X (qtd inserida - qtd deletada)
										from produto p inner join inserted i
										on p.codproduto = i.codproduto inner join deleted d
										on i.numnota = d.numnota and
										   i.codproduto = d.codproduto)
		where numnota = (select numnota from inserted)

		update produto
		set qtdestoque = qtdestoque - (select i.quantidade - d.quantidade
										from inserted i inner join deleted d
										on i.codproduto = d.codproduto and
										   i.numnota = d.numnota) 
		where codproduto = (select codproduto from inserted)
		if @@rowcount = 0
			rollback transaction
	end

	sp_helptext alterar_qtditemnotafiscal

/* chamando a trigger */
update  itemnotafiscal
set quantidade = 4
WHERE numnota = 11 and codproduto = 4


/* d) Toda vez que uma fatura for paga (atualização da data de pagamento), seja excluída da tabela
fatura e incluída em uma tabela faturapaga (a ser criada).  */

create table faturapaga
(
	numfatura int,	
	numnota int,
	data date default getdate(),
	primary key(numfatura, numnota),	
	foreign key (numnota) references notafiscal	
)
alter trigger updatedtpagamento on   -- inserted e deleted tabela fatura
fatura for update
as
if update(dtpagamento) 
	begin
		delete from fatura
		where numfatura = (select numfatura from deleted)

		insert into faturapaga(numfatura, numnota)
			select numfatura, numnota from deleted		

		if @@rowcount = 0
			rollback transaction
	end
	

	update fatura set dtpagamento = '2023-11-20' where numfatura = 18