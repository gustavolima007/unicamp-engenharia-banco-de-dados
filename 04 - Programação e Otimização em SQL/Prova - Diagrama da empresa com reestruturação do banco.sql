/* Prova - Diagrama da empresa com reestruturação do banco */
/* drop database energia_pura; */

CREATE DATABASE energia_pura;

use energia_pura; 

CREATE TABLE Empresa (
    CNPJ VARCHAR(18) PRIMARY KEY,
    Nome VARCHAR(255),
    Endereco VARCHAR(255),
    Contato VARCHAR(255),
    Socios TEXT,
    Funcionarios TEXT
);

CREATE TABLE Terreno (
    ID INT PRIMARY KEY,
    Localizacao VARCHAR(255),
    Area DECIMAL(10, 2),
    Tipo_terreno VARCHAR(50),
    Potencial_eolico DECIMAL(10, 2),
    Infraestrutura TEXT,
    Situacao_juridica VARCHAR(50),
    Licenciamento TEXT
);

CREATE TABLE Parque_Eolico (
    ID INT PRIMARY KEY,
    Nome VARCHAR(255),
    Localizacao VARCHAR(255),
    Capacidade_instalada DECIMAL(10, 2),
    Numero_aerogeradores INT,
    Modelo_aerogerador VARCHAR(255),
    Fabricante VARCHAR(255),
    Data_instalacao DATE,
    Situacao_operacional VARCHAR(50),
    Producao_energia TEXT,
    Manutencao TEXT
);

CREATE TABLE Aerogerador (
    ID INT PRIMARY KEY,
    Parque_Eolico_ID INT,
    Marca VARCHAR(255),
    Modelo VARCHAR(255),
    Potencia_nominal DECIMAL(10, 2),
    Diametro_rotor DECIMAL(10, 2),
    Altura_mastro DECIMAL(10, 2),
    Data_instalacao DATE,
    Situacao_operacional VARCHAR(50),
    Dados_producao TEXT,
    Manutencao TEXT,
    FOREIGN KEY (Parque_Eolico_ID) REFERENCES Parque_Eolico(ID)
);

CREATE TABLE Contrato_Compra_Energia (
    ID INT PRIMARY KEY,
    Comprador VARCHAR(255),
    Fornecedor VARCHAR(255),
    Data_assinatura DATE,
    Prazo_vigencia DATE,
    Quantidade_energia DECIMAL(10, 2),
    Preco_energia DECIMAL(10, 2),
    Forma_pagamento VARCHAR(255),
    Penalidades TEXT
);

CREATE TABLE Outras_Entidades (
    ID INT PRIMARY KEY,
    Fornecedor TEXT,
    Cliente TEXT,
    Relatorios TEXT
);


/* Indices criados para melhorar a perfomance do banco */

CREATE INDEX idx_aerogerador_parque_eolico_id ON Aerogerador (Parque_Eolico_ID);
CREATE INDEX idx_outras_entidades_fornecedor ON Outras_Entidades (Fornecedor(255));
CREATE INDEX idx_outras_entidades_cliente ON Outras_Entidades (Cliente);



