use master
go

/* o path em filename deve ser ajustado de acordo com a instalação do SQL-Server ou usar um path específico */

create database espbd
on
   (name = espbd_data,
   filename = 'E:\Softwares\sql_server_config\instancia_sql_server\MSSQL16.MSSQLSERVER\MSSQL\DATA\espbd.mdf',
   size = 10MB,
   maxsize = 20MB,
   filegrowth = 10%)
log on
   (name = espbd_log,
    filename = 'E:\Softwares\sql_server_config\instancia_sql_server\MSSQL16.MSSQLSERVER\MSSQL\DATA\espbd.ldf',
    size = 2MB,
    maxsize = 5MB,
    filegrowth = 10%)