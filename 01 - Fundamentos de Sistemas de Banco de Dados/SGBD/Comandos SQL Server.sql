use espbd

-- 
execute sp_helptext 'inclusaoitemnota'


execute sp_helpconstraint itemnotafiscal


-- Quest�o 1create trigger controle_vendaon compra for delete as update cliente set qtd_obras_compradas = qtd_obras_compradas - 1, qtd_obras_vendidas = qtd_obras_vendidas - 1where cliente.login = (select login_comprador from deleted)-- Quest�o 2delete from compra where codcompra = 1