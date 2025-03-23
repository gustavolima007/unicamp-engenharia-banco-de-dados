-- Procedimentos Armazenados

use espbd
go

create table cliente (
codigo numeric(10,0) not null,
nome char(30) not null,
endereco char(30) not null,
telefone numeric(10,0) null,
primary key (codigo)
)
go

insert into cliente 
values (1, 'Jose da Silva', 'Av. 1, 1111, Rio Claro-SP', 5554444)
insert into cliente 
values (2, 'Jorge Campos', 'Rua 2, 2222, Rio Claro-SP', 3337777)
insert into cliente 
values (3, 'Gisele', 'Av. 10, 3333, Rio Claro-SP', 2225555)

create procedure buscacliente
@nomebusca varchar(30)
as
select codigo, nome
from cliente
where nome like '%' + @nomebusca + '%'


select * from cliente

exec buscacliente 'se'

exec buscacliente 'jo'

alter procedure buscacliente
@nomebusca varchar(30) = '%'
as
select codigo, nome
from cliente
where nome like '%' + @nomebusca + '%'

exec sp_helptext buscacliente

exec buscacliente
exec buscacliente 'se'
exec buscacliente 'jo'

alter procedure buscacliente
@nomebusca varchar(30) = '%'
as
select codigo, nome
from cliente
where nome like '%' + @nomebusca + '%'
return @@rowcount

declare @retorno int
exec @retorno = buscacliente 'se'
print @retorno

create procedure buscacodigo
@codigobusca numeric(10,0),
@nomecliente char(30) output
as
select @nomecliente = nome
from cliente
where codigo = @codigobusca

declare @result char(30)  
exec buscacodigo 3, @result output
print @result

drop table cliente

drop procedure buscacliente, buscacodigo

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
foreign key (codigo) 
    references cliente
)
go

create table pjuridica (
codigo numeric(10,0) not null,
cnpj numeric(10,0) not null,
nfantasia char(30) not null,
primary key (codigo),
foreign key (codigo) 
    references cliente
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
foreign key (codigo) 
    references cliente,
foreign key (numero, tipo) 
    references conta
)
go

create procedure ins_pessoa_fisica
@codigo numeric(10,0),
@nome char(30),
@endereco char(30),
@telefone numeric(10,0),
@rg char(10),
@cpf numeric(10,0)
as 
begin transaction
insert into cliente 
values (@codigo, @nome, @endereco, @telefone, 0)
if @@rowcount > 0  /* insercao de cliente bem sucedida */
begin
      insert into pfisica
      values (@codigo, @rg, @cpf)
      if  @@rowcount > 0  /* insercao de pessoa física bem sucedida */
      begin
            commit transaction
            return 1
      end
     else
     begin
           rollback transaction
           return 0
     end
end
else
begin
      rollback transaction
      return 0
end

declare @ret int
exec @ret =  ins_pessoa_fisica 1, 'Antonio', 'Av.0, 111', 222222, '000000', 12121212
print @ret

select * from cliente
select * from pfisica

create procedure ins_conta
@codigo numeric(10,0),
@numero numeric(8,0),
@tipo tinyint,
@saldo money,
@conjunta char(1)
as
begin transaction
insert into conta
values (@numero, @tipo, @saldo, @conjunta)
if @@rowcount > 0 /* inserção de conta corrente bem sucedida */
begin
      insert into cliente_conta
      values (@codigo, @numero, @tipo)
      if @@rowcount > 0
      begin
            commit transaction
            return 1
     end
     else
     begin 
            rollback transaction
            return 0
     end
end
else
begin
      rollback transaction
      return 0
end

declare @ret int
exec @ret =  ins_conta 1, 1, 0, 500, 'N'
print @ret

execute sp_helptext ins_conta

create procedure trans_completa
@codigo numeric(10,0),
@nome char(30),
@endereco char(30),
@telefone numeric(10,0),
@rg char(10),
@cpf numeric(10,0), /* atributos de conta */
@numero numeric(8,0), /* atributos de conta corrente */
@saldo_cc money, /* atributos de conta poupança */
@saldo_p money, /* atributos de conta */
@conjunta char(1)
as
   declare @retorno int
   begin transaction
      exec @retorno = ins_pessoa_fisica @codigo, @nome, @endereco, @telefone, @rg, @cpf
      if @retorno > 0  /* inserção de cliente pessoa física bem sucedida */
begin
      exec @retorno = ins_conta @codigo, @numero, 0, @saldo_cc, @conjunta
      if @retorno > 0  /* inserção de conta corrente bem sucedida */
      begin
            exec @retorno = ins_conta @codigo, @numero, 1, @saldo_p, @conjunta
	      if @retorno > 0   /* inserção de conta poupança bem sucedida */
	            commit transaction
	      else      /* inserção de conta poupança mal sucedida */
	            rollback transaction
      end
            else     /* inserção de conta corrente mal sucedida */
                  rollback transaction
     end
    else
    	rollback transaction
     return @retorno
     

declare @ret int
exec @ret =  trans_completa 2, 'Gisele', 'Av.1, 1222', 242424, '111111', 12121212,  2, 500.00, 500.00, 'N'
print @ret

select * from cliente
select * from pfisica
select * from conta
select * from cliente_conta

drop table cliente_conta, conta, pfisica, pjuridica, cliente