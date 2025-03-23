-- Gatilhos

use espbd
go

create table produto (
codproduto int not null,
nome varchar(60) not null, 
preco numeric(5,2) not null,
primary key (codproduto)
)
go

create table notafiscal ( 
numeronota numeric(10,0) not null, 
valortotal numeric(10,2) not null,
primary key (numeronota)
) 
go

create table itemnotafiscal  (
numeronota numeric(10,0) not null, 
codproduto int not null, 
quantidade int not null,
primary key (numeronota,codproduto),
foreign key (numeronota) references notafiscal,
foreign key (codproduto) references produto
)
go

create trigger inclusaoitemnota
on itemnotafiscal for insert
as
	update notafiscal 
    set valortotal = valortotal + (select i.quantidade * p.preco 
     	                           from produto p inner join inserted i 
            		                    on p.codproduto = i.codproduto) 
   	where numeronota = (select numeronota from inserted) 
	if @@rowcount = 0
  	   rollback transaction

execute sp_helptext 'inclusaoitemnota'

insert into produto values (1, 'lapis', 1.50)
insert into produto values (2, 'borracha', 2.00)
insert into produto values (3, 'caneta', 3.50)

insert into notafiscal values (1, 0)

insert into itemnotafiscal values (1, 2, 10)
insert into itemnotafiscal values (1, 3, 2)
insert into itemnotafiscal values (1, 1, 2)

select * from produto
select * from itemnotafiscal
select * from notafiscal

drop trigger inclusaoitemnota

create trigger exclusaonota
on notafiscal for delete 
as 
   	-- excluir todos os itens relacionados (mesmo numeronota que deleted) 
   	delete from itemnotafiscal 
   	where numeronota in (select numeronota from deleted)
    if @@rowcount = 0
       rollback transaction

delete from notafiscal
where numeronota = 1

execute sp_helpconstraint itemnotafiscal

alter table itemnotafiscal
drop constraint FK__itemnotaf__numer__73BA3083 -- alterar de acordo com o resultado da execução da sp_helpconstraint

insert into itemnotafiscal values (0, 3, 2) -- gera inconsistência incluindo item para uma nota não cadastrada

delete from itemnotafiscal -- excluindo linha inconsistente
where numeronota = 0

create trigger inclusaoitemnota -- criando novamente o gatilho para inserção incluindo a checagem de nota cadastrada
on itemnotafiscal for insert
as
   if not exists (select * 
           	      from inserted i inner join notafiscal n                             
                       on i.numeronota = n.numeronota)
   begin
      print 'Esse item não contém um número de nota válido'
      rollback transaction
   end
   else begin
      update notafiscal 
      set valortotal = valortotal + (select i.quantidade * p.preco 
 		                             from produto p inner join inserted i 
            		                      on p.codproduto = i.codproduto) 
      where numeronota = (select numeronota from inserted) 
      if @@rowcount = 0
         rollback transaction
   end


create trigger alteracaoitemnota 
on itemnotafiscal for update 
as 
if update(quantidade) 
begin 
   update notafiscal 
   set valortotal = valortotal + (select p.preco * (i.quantidade - d.quantidade) 
                                  from produto p inner join inserted i                  
                                       on p.codproduto = i.codproduto 
                                       inner join deleted d                  
                                       on i.codproduto = d.codproduto and 
                                          i.numeronota = d.numeronota)
   where numeronota = (select numeronota from inserted)
   if @@rowcount = 0
        rollback transaction
end 

update itemnotafiscal set quantidade = 5
where numeronota = 1 and codproduto = 2

update itemnotafiscal set quantidade = 4
where numeronota = 1 and codproduto = 3 

select * from produto
select * from itemnotafiscal
select * from notafiscal

drop table itemnotafiscal, notafiscal, produto