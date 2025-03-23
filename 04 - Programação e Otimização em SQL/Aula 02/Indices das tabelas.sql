/* Indices das tabelas  */

CREATE INDEX idx_categoria_id ON PRODUTO (CATEGORIA_ID);
CREATE UNIQUE INDEX idx_email ON CLIENTE (EMAIL);
CREATE INDEX idx_cliente_id ON PEDIDO (CLIENTE_ID);
CREATE INDEX idx_dta_pedido ON PEDIDO (DTAPEDIDO);

