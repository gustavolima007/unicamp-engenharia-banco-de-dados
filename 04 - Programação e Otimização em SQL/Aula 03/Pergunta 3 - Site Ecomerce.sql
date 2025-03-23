CREATE DATABASE ecommerce;

use ecommerce; 



CREATE TABLE Cadastro_Cliente (
    ID INT PRIMARY KEY,
    Nome VARCHAR(255),
    Email VARCHAR(255),
    Telefone VARCHAR(20),
    CPF VARCHAR(14),
    Data_Nascimento DATE
);

CREATE TABLE Cadastro_Produto (
    ID INT PRIMARY KEY,
    Nome VARCHAR(255),
    Descricao TEXT,
    Preco DECIMAL(10, 2),
    Estoque INT
);

CREATE TABLE Cadastro_Fornecedor (
    ID INT PRIMARY KEY,
    Nome VARCHAR(255),
    Email VARCHAR(255),
    Telefone VARCHAR(20),
    Tipo_Fornecedor VARCHAR(50)
);

CREATE TABLE Pedido_Cliente (
    ID INT PRIMARY KEY,
    Cliente_ID INT,
    Data_Pedido DATE,
    Total DECIMAL(10, 2),
    Status VARCHAR(50),
    Metodo_Pagamento VARCHAR(50),
    FOREIGN KEY (Cliente_ID) REFERENCES Cadastro_Cliente(ID)
);

CREATE TABLE Pedido_Compra (
    ID INT PRIMARY KEY,
    Fornecedor_ID INT,
    Data_Compra DATE,
    Total DECIMAL(10, 2),
    Cliente_ID INT,
    Produto_ID INT,
    Quantidade INT,
    Status VARCHAR(50),
    FOREIGN KEY (Fornecedor_ID) REFERENCES Cadastro_Fornecedor(ID),
    FOREIGN KEY (Cliente_ID) REFERENCES Cadastro_Cliente(ID),
    FOREIGN KEY (Produto_ID) REFERENCES Cadastro_Produto(ID)
);

CREATE TABLE Cadastro_Endereco_Cliente (
    ID INT PRIMARY KEY,
    Cliente_ID INT,
    Endereco VARCHAR(255),
    Cidade VARCHAR(100),
    Estado VARCHAR(50),
    CEP VARCHAR(10),
    FOREIGN KEY (Cliente_ID) REFERENCES Cadastro_Cliente(ID)
);

CREATE TABLE Carga_Recebimento (
    ID INT PRIMARY KEY,
    Fornecedor_ID INT,
    Produto_ID INT,
    Quantidade INT,
    Data_Recebimento DATE,
    Status VARCHAR(50),
    FOREIGN KEY (Fornecedor_ID) REFERENCES Cadastro_Fornecedor(ID),
    FOREIGN KEY (Produto_ID) REFERENCES Cadastro_Produto(ID)
);

CREATE TABLE Carga_Expedicao (
    ID INT PRIMARY KEY,
    Cliente_ID INT,
    Produto_ID INT,
    Quantidade INT,
    Data_Expedicao DATE,
    Status VARCHAR(50),
    FOREIGN KEY (Cliente_ID) REFERENCES Cadastro_Cliente(ID),
    FOREIGN KEY (Produto_ID) REFERENCES Cadastro_Produto(ID)
);

CREATE TABLE Carga_Transporte (
    ID INT PRIMARY KEY,
    Cliente_ID INT,
    Produto_ID INT,
    Quantidade INT,
    Data_Transporte DATE,
    Status VARCHAR(50),
    FOREIGN KEY (Cliente_ID) REFERENCES Cadastro_Cliente(ID),
    FOREIGN KEY (Produto_ID) REFERENCES Cadastro_Produto(ID)
);
